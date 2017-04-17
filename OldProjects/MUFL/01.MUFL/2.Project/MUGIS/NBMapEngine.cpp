

#include "StdAfx.h"
#include ".\nbmapengine.h"
#include <math.h>


#pragma warning(disable:4244)
#pragma warning(disable:4355)


//////////////////////////////////////////////////////////////////////////
// TEgAttri
TEgAttri::TEgAttri()
{
    ptMapCenter = TMPoint(10056009,3447360);  // Coordinates of Tian'an'men
    rectDevice = CRect(0,0,800,600);
    fPhysicPerDevice = 0.33203125; // mm
    fPhysicPerLogic = 1000; // mm
    dwZoomScale=50000;
    fUnitZoom=1.25;
    dwMaxScale=1;
    dwMinScale=DWORD(-1);
    fRoateRadians=0;
}

TEgAttri::~TEgAttri()
{

}

TEgAttri& TEgAttri::operator=(const TEgAttri& aOther)
{
    if (this!=&aOther)
    {
        ptMapCenter = aOther.ptMapCenter;
        fUnitZoom = aOther.fUnitZoom;
        dwMaxScale = aOther.dwMaxScale;
        dwMinScale = aOther.dwMinScale;
        rectDevice = aOther.rectDevice;
        fPhysicPerDevice = aOther.fPhysicPerDevice;
        fPhysicPerLogic = aOther.fPhysicPerLogic;
        dwZoomScale = aOther.dwZoomScale;
        fRoateRadians = aOther.fRoateRadians;
    }
    return *this;
}

//////////////////////////////////////////////////////////////////////////

CNBMapEngine::CNBMapEngine(void):m_GridMgr(*this)
{
}

CNBMapEngine::~CNBMapEngine(void)
{
}

void CNBMapEngine::Close()
{
    m_GridMgr.Close();
}

const MGridManager* CNBMapEngine::GetGridMgr() const
{
    return &m_GridMgr;
}

TMRect CNBMapEngine::GetRectMapActived() const
{
    return m_rectLogicActived;
}

TMPoint CNBMapEngine::GetMapCenter() const
{
    return m_rectLogicActived.Center();
}
//////////////////////////////////////////////////////////////////////////

BOOL CNBMapEngine::Initialize( TEgAttri& aAttri )
{
    TMRect rectMap(0,1,1,0);
    CSize sizeGrid(1,1);

    //
	if (!OnInitialize(aAttri,rectMap,sizeGrid))
	{
		return FALSE;
	}

    //
    m_GridMgr.Initialize(rectMap,sizeGrid);

    //
    m_lEgAttri = aAttri;

	InitMapRect(m_lEgAttri.ptMapCenter,
		m_lEgAttri.rectDevice.Width(),
		m_lEgAttri.rectDevice.Height());

    return TRUE;
}

//BOOL CNBMapEngine::OnInitialize(TEgAttri& aAttri,TMRect& mapRect,CSize& sizeGrid)
//{
//	return FALSE;
//}

void CNBMapEngine::InitMapRect(TMPoint aMapCenter,LONG lWidthOfDevice,LONG lHeightOfDevice)
{
    TLcType widthWR = TransferDeviceunitToLogicunit( lWidthOfDevice );
    TLcType heightWR= TransferDeviceunitToLogicunit( lHeightOfDevice );

    m_rectLogicActived = TMRect(aMapCenter,widthWR,heightWR);

    // 调整转换比例
	AdjustTransferScale();

	OnActivedRectChanged_Reserved();
}

// 计算在当前比例尺下aPixs设备单位对应的逻辑单位
TLcType CNBMapEngine::TransferDeviceunitToLogicunit(int aPixs) const
{
    // 计算aPixs对应的物理尺寸X (米)
    DOUBLE lenActual = (aPixs*m_lEgAttri.fPhysicPerDevice)*(m_lEgAttri.dwZoomScale);

    // 计算物理尺寸X对应的逻辑单位
    TLcType lenMapLen = (TLcType)(lenActual/m_lEgAttri.fPhysicPerLogic);

    return lenMapLen;
}

// 调整转换比例尺
void CNBMapEngine::AdjustTransferScale()
{
    if (m_rectLogicActived.Width() && m_rectLogicActived.Height())
    {
        DOUBLE sx = (m_lEgAttri.rectDevice.Width())/(DOUBLE)(m_rectLogicActived.Width());
        DOUBLE sy = (m_lEgAttri.rectDevice.Height())/(DOUBLE)(m_rectLogicActived.Height());
        m_fTranfScale = min(sx,sy);//
    }
    else
    {
        m_fTranfScale = 1;
    }
}

// 计算当然范围中的网格
void  CNBMapEngine::RearrangeGridActived()
{
    m_listGridActived.RemoveAll();
    m_GridMgr.GetGridByRect(m_rectLogicActived,m_listGridActived);
}

void CNBMapEngine::OnActivedRectChanged_Reserved()
{
    RearrangeGridActived();

    OnActivedRectChanged(m_listGridActived);
}


void CNBMapEngine::LPtToDPt_Reserve(const TMPoint& aLp,CPoint& aDp) const
{
    aDp.x = LONG( (aLp.iX-m_rectLogicActived.iTl.iX)*m_fTranfScale 
        + m_lEgAttri.rectDevice.left );

    aDp.y = LONG( (m_rectLogicActived.iTl.iY-aLp.iY)*m_fTranfScale 
        + m_lEgAttri.rectDevice.top );
}

void CNBMapEngine::DPtToLPt_Reserve(const CPoint& aDp,TMPoint& aLp) const
{
    aLp.iX = TLcType( (aDp.x-m_lEgAttri.rectDevice.left)/m_fTranfScale 
        + m_rectLogicActived.iTl.iX );

    aLp.iY = TLcType( m_rectLogicActived.iTl.iY
        - (aDp.y-m_lEgAttri.rectDevice.top)/m_fTranfScale );
}


void CNBMapEngine::MapOperation(int aEvent,WPARAM wParam,LPARAM lParam)
{

    switch(aEvent)
    {
    case EMO_MOVE_VECTOR:
        {
            TVector* vMove = (TVector*)wParam;

            TMPoint center = m_rectLogicActived.Center();
            center = center + *vMove;
            LONG width = m_rectLogicActived.Width();
            LONG height = m_rectLogicActived.Height();
            m_rectLogicActived = TMRect(center,width,height);

			// 
			OnActivedRectChanged_Reserved();
        }
    	break;

    case EMO_MAP_ZOOMIN:
    case EMO_MAP_ZOOMOUT:
        {

            TMPoint center = *(TMPoint*)(wParam);

            // 调整当前的比例尺
            DWORD newScale;
            if (aEvent==EMO_MAP_ZOOMOUT)
            {
                newScale = DWORD(m_lEgAttri.dwZoomScale*m_lEgAttri.fUnitZoom);
            }
            else
            {
                newScale = DWORD(m_lEgAttri.dwZoomScale/m_lEgAttri.fUnitZoom);
            }

            if ( (newScale<=m_lEgAttri.dwMinScale) && (newScale>=m_lEgAttri.dwMaxScale) )
            {

                // 修改当前的比例尺
                m_lEgAttri.dwZoomScale = newScale;

                // 计算缩放单位
                TLcType width = m_rectLogicActived.Width();
                TLcType height = m_rectLogicActived.Height();

                if (aEvent==EMO_MAP_ZOOMOUT)
                {
                    width = TLcType(width*m_lEgAttri.fUnitZoom);
                    height = TLcType(height*m_lEgAttri.fUnitZoom);
                } 
                else
                {
                    width = TLcType(width/DOUBLE(m_lEgAttri.fUnitZoom));
                    height = TLcType(height/DOUBLE(m_lEgAttri.fUnitZoom));
                }

                // 以中心为基准进行缩放
                m_rectLogicActived = TMRect(center,width,height);

                // 调整转换比例
                AdjustTransferScale();

				// 
				OnActivedRectChanged_Reserved();

            }
        }
        break;

    case EMO_ROTATE_CENTER:
        {
            // 顺时针旋转的角度＝方位角的负值
            m_lEgAttri.fRoateRadians = *(float*)(wParam);

            OnRotatingRadiansChanged(m_lEgAttri.fRoateRadians);
        }
        break;

    case EMO_DEVICERECT_CHANGED:
        {
            ASSERT(wParam!=NULL);

            CRect* pRectNew = (CRect*)wParam;
            m_lEgAttri.rectDevice = pRectNew;

            TMPoint ptNewCenter = m_rectLogicActived.Center();

            /*CPoint ptCenter = pRectNew->CenterPoint();
            DpToLp(ptCenter,ptNewCenter);*/

            InitMapRect(ptNewCenter,pRectNew->Width(),pRectNew->Height());
        }
        break;
    }

}

void CNBMapEngine::OnActivedRectChanged(const CGridList& listGrid)
{
    
}

void CNBMapEngine::OnRotatingRadiansChanged(float aNewRotating)
{

}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//

DWORD CNBMapEngine::GetCurZoomScale() const
{
    return m_lEgAttri.dwZoomScale;
}

DWORD CNBMapEngine::GetMaxZoomScale() const
{
    return m_lEgAttri.dwMaxScale;
}

DWORD CNBMapEngine::GetMinZoomScale() const
{
    return m_lEgAttri.dwMinScale;
}

float CNBMapEngine::GetRotateRadians() const
{
    return m_lEgAttri.fRoateRadians;
}

void CNBMapEngine::GetLogicRect(TMRect& rectLogic) const
{
    rectLogic = m_GridMgr.GetMapRect();
}

void CNBMapEngine::LpToDp(const TMPoint& aLp,CPoint& aDp) const
{
    TMPoint rotateLp = aLp;
    rotateLp.Rotate(m_rectLogicActived.Center(),m_lEgAttri.fRoateRadians);
    LPtToDPt_Reserve(rotateLp,aDp);
}

void CNBMapEngine::DpToLp(const CPoint& aDp,TMPoint& aLp) const
{
    DPtToLPt_Reserve(aDp,aLp);
    aLp.Rotate(m_rectLogicActived.Center(),-m_lEgAttri.fRoateRadians);
}

void CNBMapEngine::LrToDr(const TMRect& aLRect,CRect& aDRect) const
{
    TMRect rotateRect = aLRect;
    rotateRect.Rotate(m_rectLogicActived.Center(),m_lEgAttri.fRoateRadians);
    LPtToDPt_Reserve(rotateRect.iTl,aDRect.TopLeft());
    LPtToDPt_Reserve(rotateRect.iBr,aDRect.BottomRight());
}

void CNBMapEngine::DrToLr(const CRect& aDRect,TMRect& aLRect) const
{
    CPoint topLeft = aDRect.TopLeft();
    CPoint topRight(aDRect.right,aDRect.top);
    CPoint bottomLeft(aDRect.left,aDRect.bottom);
    CPoint bottomright = aDRect.BottomRight();

    TMPoint tlM,trM,blM,brM;
    DpToLp(topLeft,tlM);
    DpToLp(topRight,trM);
    DpToLp(bottomLeft,blM);
    DpToLp(bottomright,brM);

    CMPointVector ptArray;
    ptArray.push_back(tlM);
    ptArray.push_back(trM);
    ptArray.push_back(blM);
    ptArray.push_back(brM);
    aLRect = TMRect(ptArray);
}

DOUBLE CNBMapEngine::DlToLl(DOUBLE dLenDevice) const
{
    CPoint pt1(0,0),pt2((LONG)dLenDevice,0);

    TMPoint mPt1,mPt2;
    DPtToLPt_Reserve(pt1,mPt1);
    DPtToLPt_Reserve(pt2,mPt2);

    return mPt1.Distance(mPt2);
}

DOUBLE CNBMapEngine::LlToDl(DOUBLE dLenLogic) const
{
    TMPoint pt1(0,0),pt2(TLcType(dLenLogic),0);

    CPoint dPt1,dPt2;
    LPtToDPt_Reserve(pt1,dPt1);
    LPtToDPt_Reserve(pt2,dPt2);

    TLcType ndX = dPt1.x - dPt2.x;
    TLcType ndY = dPt2.y - dPt2.y;
    DOUBLE nReturn = sqrt( DOUBLE(ndX)*ndX+DOUBLE(ndY)*ndY );

    return nReturn;
}


//////////////////////////////////////////////////////////////////////////
// From MNBGridMgrObserver

void CNBMapEngine::OnBuildingGrid()
{

}

void CNBMapEngine::OnBuildGrid(PTNBMapGrid pGrid)
{

}

void CNBMapEngine::OnGridsBuilt()
{

}

void CNBMapEngine::OnDestroyGrid(PTNBMapGrid pGrid)
{

}
