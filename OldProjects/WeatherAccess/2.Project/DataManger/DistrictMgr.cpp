#include "stdafx.h"
#include "DistrictMgr.h"
#include "CommonFunc.h"
#include "GlobalMacro.h"
#include "UserColors.h"

#pragma warning(disable:4244)
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

CBJDistrictMgr::CBJDistrictMgr(void)
{
    m_rectMap.SetNull();
}

CBJDistrictMgr::~CBJDistrictMgr(void)
{
    Close();
}

//////////////////////////////////////////////////////////////////////////
// From CNBMapEngine

BOOL CBJDistrictMgr::OnInitialize(TEgAttri& aAttri,TMRect& mapRect,CSize& sizeGrid)
{

    // 修改比例尺
    aAttri.ptMapCenter = TMPoint(10065600,3478464);
    aAttri.dwZoomScale = 950000;
    aAttri.dwMaxScale = 200000;
    aAttri.dwMinScale = 3300000;
    aAttri.fUnitZoom = 1.5;
    aAttri.fPhysicPerLogic = 1000;


    // 修改网格属性
    mapRect = m_rectMap;
    sizeGrid.cx = 11000;
    sizeGrid.cy = 11000;

    //
    return TRUE;
}


void CBJDistrictMgr::OnActivedRectChanged(const CGridList& listGrid)
{
    TransferLogicalPtsToDevicePts();
}


void CBJDistrictMgr::OnRotatingRadiansChanged(float /*aNewRotating*/)
{
    TransferLogicalPtsToDevicePts();
}


void CBJDistrictMgr::OnBuildingGrid()
{
    TMRect rectMap = GetGridMgr()->GetMapRect();
    CSize sizeGrid = GetGridMgr()->GetGridSize();

    IMsgAppLogs aLog;
    aLog.strComments.Format(_T("北京区域引擎正在构建网格(地图范围(<%d,%ld>,<%ld,%ld>)，每网格大小%d*%d，网格数(%d×%d))……"),
        rectMap.iTl.iX, rectMap.iTl.iY, rectMap.iBr.iX, rectMap.iBr.iY,
        sizeGrid.cx, sizeGrid.cy,   GetGridMgr()->GetNumOfRow(), GetGridMgr()->GetNumOfCol());

    NbsSendModuleMsg(&aLog);
}

void CBJDistrictMgr::OnBuildGrid(PTNBMapGrid pGrid)
{

    //CLinkList* pLinkList = new CLinkList;
    //SET_LINKLIST(pGrid,pLinkList);

#ifdef _TRACE_GRID_INFO_TFCROAD

    TRACE("网格%d，行号%d，列号%d，范围<(%d,%d),(%d,%d)>\n",
        pGrid->m_wGridID,pGrid->m_wRowID,pGrid->m_wColID,
        pGrid->m_rectExtent.iTl.iX,pGrid->m_rectExtent.iTl.iY,
        pGrid->m_rectExtent.iBr.iX,pGrid->m_rectExtent.iBr.iY);

#endif
}

void CBJDistrictMgr::OnGridsBuilt()
{

    // 将Link数据与网格进行关联
    //IMsgAppLogs aLog;
    //aLog.UpdateToCurrentTime();
    //aLog.strComments.Format(_T("正在将Link关联到网格中……"));
    //NbsSendModuleMsg(&aLog);

    //// 将Link与网格关联

    //// 
    //CString key;
    //CLinkList* pLinklist = NULL;
    //for( POSITION pos = m_mapRoadIDtoLinks.GetStartPosition(); pos != NULL; )
    //{
    //    m_mapRoadIDtoLinks.GetNextAssoc( pos, key, pLinklist );

    //    // 
    //    POSITION posSub = pLinklist->GetHeadPosition();
    //    while (posSub)
    //    {
    //        const PTLinkAttri pLink = pLinklist->GetNext(posSub);
    //        CGridList gridList;
    //        GetGridMgr()->GetGridByRect(pLink->m_rectExtent,gridList);

    //        // 
    //        POSITION posGrid = gridList.GetHeadPosition();
    //        while (posGrid)
    //        {
    //            PTNBMapGrid pGrid = gridList.GetNext(posGrid);
    //            CLinkList* pLinkList = RETRIEVE_LINKLIST(pGrid);
    //            pLinkList->AddTail(pLink);
    //        }
    //    }
    //}

}

void CBJDistrictMgr::OnDestroyGrid(PTNBMapGrid pGrid)
{
    /*CLinkList* pLinkList = RETRIEVE_LINKLIST(pGrid);
    pLinkList->RemoveAll();
    delete pLinkList;*/
}


//////////////////////////////////////////////////////////////////////////
// 

BOOL CBJDistrictMgr::ReadRgnData()
{
    CString strFileName = GetExePath() +PATH_DATA_FILE+CString( _T("RegionCode.txt"));

    CStdioFile  stdFile;
    if (!stdFile.Open(strFileName,CFile::modeRead|CFile::shareDenyNone))
    {
        AfxMessageBox(_T("没有找到RegionCode.txt文件"));
        return FALSE;
    }

    //
    int     iNumber = 0;
    CString strLine;

    // 找到区域的个数
    while (stdFile.ReadString(strLine))
    {
        if (strLine.Find(_T("Number"))!=-1)
        {
            iNumber = atoi( GetSFStr((LPCTSTR)strLine,1,"=").c_str() );
            break;
        }
    }

    //
    CString strRegion;
    CString strPoint;
    for (int n=0; n<iNumber; n++)
    {
        TDistrict* pNewRegion = NULL;

        // 寻找 [RegionX]
        BOOL bFileEnd = FALSE;
        strRegion.Format(_T("Region%d"),n+1);
        bFileEnd = !stdFile.ReadString(strLine);
        while (!bFileEnd)
        {
            if (strLine.Find(strRegion)!=-1)
            {
                pNewRegion = new TDistrict;
                pNewRegion->m_strIDistID = GetSFStr((LPCTSTR)strLine,1,_T("=")).c_str();
                pNewRegion->m_strIDistID.Trim(_T(" "));
                break;
            }
            bFileEnd = !stdFile.ReadString(strLine);
        }
        if (bFileEnd)
        {
            return FALSE;
        }

        // 寻找[PointX]
        int iPtIdx = 0;


        BOOL bFlag = FALSE;
        strPoint.Format(_T("Point%d"),n+1);
        while (stdFile.ReadString(strLine))
        {
            if (!bFlag && strLine.Find(strPoint)!=-1) //[Point1]
            {
                WORD wNumPt = (WORD)atoi(GetSFStr((LPCTSTR)strLine,1,_T("=")).c_str());
                pNewRegion->m_ptLogicalPosArray.SetSize(0,wNumPt);
                bFlag = TRUE;
            }
            else if (strLine.Find(_T("Name"))!=-1) // [Name1]
            {
                pNewRegion->m_strDistName = GetSFStr((LPCTSTR)strLine,1,_T("=")).c_str();
                pNewRegion->m_strDistName.Trim();
            }
            else if (strLine.Find(_T("PointEnd"))!=-1) // [PointEnd]
            {
            }
            else if (strLine.Find(_T("RegionEnd"))!=-1) // [RegionEnd]
            {
                CRgn rgn;
                CPoint* ptArray = (CPoint*)pNewRegion->m_ptLogicalPosArray.GetData();
                int iCount = pNewRegion->m_ptLogicalPosArray.GetCount();
                rgn.CreatePolygonRgn(ptArray,iCount,ALTERNATE);
                CRect rect;
                rgn.GetRgnBox(rect);
                pNewRegion->m_boxRect.Copy(rect);

                // 
                m_rectMap += pNewRegion->m_boxRect;


                pNewRegion->m_ptCenter.iX = rect.CenterPoint().x;
                pNewRegion->m_ptCenter.iY = rect.CenterPoint().y;
                    
                m_DistrictList.AddTail(pNewRegion);
                break;
            }
            else
            {
                CString strX,strY;
                strX = GetSFStr((LPCTSTR)strLine,0,_T(" ")).c_str();
                strY = GetSFStr((LPCTSTR)strLine,1,_T(" ")).c_str();
                if (strX.GetLength()!=0 && strY.GetLength()!=0)
                {
                    TMPoint ptPos;
                    ptPos.iX = LONG(atof(strX)*3600*24);
                    ptPos.iY = LONG(atof(strY)*3600*24);
                    pNewRegion->m_ptLogicalPosArray.Add(ptPos);
                    iPtIdx ++;
                }
            }
        }

    }

    stdFile.Close();

    return TRUE;
}

void CBJDistrictMgr::Close()
{
    while (m_DistrictList.GetHeadPosition())
    {
        delete m_DistrictList.RemoveHead();
    }

    // 
    CNBMapEngine::Close();
}

BOOL CBJDistrictMgr::GetDistIDByPos(const TMPoint& ptPos,CString& strAreaID) const
{
    TDistrict* pDist = GetDistrict(ptPos);
    if (pDist!=NULL)
    {
        strAreaID = pDist->m_strIDistID;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

TDistrict* CBJDistrictMgr::GetDistrict(const CPoint& aPt) const
{
    POSITION pos = m_DistrictList.GetHeadPosition();
    while (pos)
    {
        TDistrict* pRegion = m_DistrictList.GetNext(pos);
        CRgn rgn;
        rgn.CreatePolygonRgn(pRegion->m_ptDevicePtArray.GetData(),
                    pRegion->m_ptLogicalPosArray.GetCount(),ALTERNATE);
        if (rgn.PtInRegion(aPt))
        {
            return pRegion;
        }
    }

    return NULL;
}

TDistrict* CBJDistrictMgr::GetDistrict(const TMPoint& ptPos) const
{
    CPoint point(ptPos.iX,ptPos.iY);
    POSITION pos = m_DistrictList.GetHeadPosition();
    while (pos)
    {
        TDistrict* pRegion = m_DistrictList.GetNext(pos);
        CRgn rgn;
        rgn.CreatePolygonRgn((CPoint*)(pRegion->m_ptLogicalPosArray.GetData()),
            pRegion->m_ptLogicalPosArray.GetCount(),ALTERNATE);
        if (rgn.PtInRegion(point))
        {
            return pRegion;
        }
    }

    return NULL;
}

BOOL CBJDistrictMgr::RetrieveWthInf()
{
    BOOL bResult = TRUE;

    POSITION pos = m_DistrictList.GetHeadPosition();
    while (pos)
    {
        TDistrict* pDist = m_DistrictList.GetNext(pos);
        pDist->ClearWthList();
        IMsgRetriveWthInf msg(pDist->m_strIDistID,pDist->m_WthInfList); 
        NbsSendModuleMsg(&msg);
        if (!msg.bSuccess)
        {
            IMsgAppLogs aLog;
            aLog.logTime = COleDateTime::GetCurrentTime();
            aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
            aLog.strComments.Format(_T("读取%s气象信息失败！"),pDist->m_strDistName); 
            NbsSendModuleMsg(&aLog);

            bResult = FALSE;
        }
    }

    m_timeUpdate = COleDateTime::GetCurrentTime();

    return bResult;
}

//////////////////////////////////////////////////////////////////////////
// 

void CBJDistrictMgr::TransferLogicalPtsToDevicePts()
{
    POSITION pos = m_DistrictList.GetHeadPosition();
    while (pos)
    {
        TDistrict* pRegion = (TDistrict*)(m_DistrictList.GetNext(pos));

        // translate the coordinates.
        WORD wCount = pRegion->m_ptLogicalPosArray.GetCount();
        pRegion->m_ptDevicePtArray.SetSize(wCount,1);
        for (WORD ii=0; ii<wCount; ii++)
        {
            TMPoint ptMap = pRegion->m_ptLogicalPosArray[ii];
            CPoint ptScreen;
            LpToDp(ptMap,ptScreen);
            pRegion->m_ptDevicePtArray.SetAt(ii,ptScreen);
        }
    }
}


void CBJDistrictMgr::Draw(CDC* pDC) 
{
    ASSERT(pDC!=NULL);

    //
    POSITION pos = m_DistrictList.GetHeadPosition();
    while (pos)
    {
        TDistrict* pRegion = (TDistrict*)(m_DistrictList.GetNext(pos));
        pRegion->DrawRegion(pDC,*this);
        pRegion->DrawName(pDC,*this);
    }
}


COleDateTime CBJDistrictMgr::GetFlashTime() const
{
    return m_timeUpdate;
}



