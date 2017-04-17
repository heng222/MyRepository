#include "StdAfx.h"
#include ".\tfcparsedmgr.h"
#include "GlobalMacro.h"

//////////////////////////////////////////////////////////////////////////


#define         MIN_DISTANCE        5 // 像素

//////////////////////////////////////////////////////////////////////////
CTfcParsedMgr::CTfcParsedMgr(void)
{
    m_pRoadList = NULL;
    m_rectMap.SetNull();
}

CTfcParsedMgr::~CTfcParsedMgr(void)
{
}



void CTfcParsedMgr::Close()
{
    m_linkList.ClearList();

    CNBMapEngine::Close();
}


//////////////////////////////////////////////////////////////////////////
// From CMapEngine

BOOL CTfcParsedMgr::OnInitialize(TEgAttri& aAttri,TMRect& mapRect,CSize& sizeGrid)
{
    // 修改比例尺
    aAttri.dwZoomScale = 125000;
    aAttri.dwMaxScale = 500;
    aAttri.dwMinScale = 740000;
    aAttri.fUnitZoom = 1.5;
    aAttri.fPhysicPerLogic = 1000;

    // 修改网格属性
    mapRect = m_rectMap;
    sizeGrid.cx = 1000;
    sizeGrid.cy = 1000;

    return TRUE;
}

void CTfcParsedMgr::OnActivedRectChanged(const CGridList& listGrid)
{

}

void CTfcParsedMgr::OnRotatingRadiansChanged(float aNewRotating)
{

}


void CTfcParsedMgr::OnBuildingGrid()
{
    TMRect rectMap = GetGridMgr()->GetMapRect();
    CSize sizeGrid = GetGridMgr()->GetGridSize();

    IMsgAppLogs aLog;
    aLog.strComments.Format(_T("Link引擎正在构建网格(地图范围(<%d,%ld>,<%ld,%ld>)，每网格大小%d*%d，网格数(%d×%d))……"),
        rectMap.iTl.iX, rectMap.iTl.iY, rectMap.iBr.iX, rectMap.iBr.iY,
        sizeGrid.cx, sizeGrid.cy,   GetGridMgr()->GetNumOfRow(), GetGridMgr()->GetNumOfCol());

    NbsSendModuleMsg(&aLog);
}

void CTfcParsedMgr::OnBuildGrid(PTNBMapGrid pGrid)
{

    CLinkList* pLinkList = new CLinkList;
    SET_LINKLIST(pGrid,pLinkList);

#ifdef _TRACE_GRID_INFO_TFCROAD

    TRACE("网格%d，行号%d，列号%d，范围<(%d,%d),(%d,%d)>\n",
        pGrid->m_wGridID,pGrid->m_wRowID,pGrid->m_wColID,
        pGrid->m_rectExtent.iTl.iX,pGrid->m_rectExtent.iTl.iY,
        pGrid->m_rectExtent.iBr.iX,pGrid->m_rectExtent.iBr.iY);

#endif
}

void CTfcParsedMgr::OnGridsBuilt()
{

    // 将Link数据与网格进行关联
    IMsgAppLogs aLog;
    aLog.UpdateToCurrentTime();
    aLog.strComments.Format(_T("正在将Link关联到网格中……"));
    NbsSendModuleMsg(&aLog);

    // 将Link与网格关联
    POSITION pos = m_linkList.GetHeadPosition();
    while (pos)
    {
        PTLinkAttri pLink = m_linkList.GetNext(pos);

        CGridList gridList;
        GetGridMgr()->GetGridByRect(pLink->m_rectExtent,gridList);

        // 
        POSITION posGrid = gridList.GetHeadPosition();
        while (posGrid)
        {
            PTNBMapGrid pGrid = gridList.GetNext(posGrid);
            CLinkList* pLinkList = RETRIEVE_LINKLIST(pGrid);
            pLinkList->AddTail(pLink);
        }
    }

}

void CTfcParsedMgr::OnDestroyGrid(PTNBMapGrid pGrid)
{
    CLinkList* pLinkList = RETRIEVE_LINKLIST(pGrid);
    pLinkList->RemoveAll();
    delete pLinkList;
}

//////////////////////////////////////////////////////////////////////////
// New functions

BOOL CTfcParsedMgr::Open()
{
    // 读取Link数据

    IMsgAppLogs aLog;
    aLog.strComments.Format(_T("读取Link数据"));
    NbsSendModuleMsg(&aLog);

    if (!ReadLink())
    {
        return FALSE;
    }

    return TRUE;
}

BOOL CTfcParsedMgr::ReadLink()
{
    IMsgAppLogs aLog1;
    aLog1.strComments.Format(_T("正在解析mid文件……"));
    NbsSendModuleMsg(&aLog1);

    // 读取MID文件
    CStdioFile midFile;

    CString strFileName = GetExePath()+PATH_DATA_FILE+"TfcLink.mid";
    if ( !midFile.Open( strFileName, CFile::modeRead|CFile::shareDenyNone) )
    {
        IMsgAppLogs aLog;
        aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
        aLog.strComments.Format(_T("无法打开%s……"),strFileName);
        NbsSendModuleMsg(&aLog);
        return FALSE;
    }

    CString strLine;

    PTLinkAttri pLink = NULL;

    while (midFile.ReadString(strLine))
    {
        if (!strLine.IsEmpty())
        {
            pLink = new TLinkAttri;

            int   iIndex = 0;

            // Map ID
            pLink->m_dwMapID = (DWORD)GetNFStr(strLine,iIndex++,",");

            // Link ID
            pLink->m_dwLinkID = (DWORD)GetNFStr(strLine,iIndex++,",");

            // Link名称
            pLink->m_strLinkName = GetSFStr((LPCTSTR)strLine,iIndex++,_T(",")).c_str();

            // Link等级
            pLink->m_iLinkLevel = (int)GetNFStr(strLine,iIndex++,",");

            // Link的交通流
            pLink->m_iTrafficFlow = (int)GetNFStr(strLine,iIndex++,",");

            // 保存
            m_linkList.AddTail(pLink);
        }
    }


    midFile.Close();


    // 读取MIF文件

    CStdioFile mifFile;
    strFileName = GetExePath()+PATH_DATA_FILE+"TfcLink.mif";
    if ( !mifFile.Open( strFileName, CFile::modeRead|CFile::shareDenyNone) )
    {
        IMsgAppLogs aLog;
        aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
        aLog.strComments.Format(_T("无法打开%s……"),strFileName);
        NbsSendModuleMsg(&aLog);
        return FALSE;
    }

    IMsgAppLogs aLog2;
    aLog2.strComments.Format(_T("正在解析mif文件……"));
    NbsSendModuleMsg(&aLog2);


    POSITION pos = m_linkList.GetHeadPosition();

#ifdef _DEBUG
    //int iCount =0;
#endif

    while (mifFile.ReadString(strLine))
    {
        if (strLine.Find("Pline") != -1)
        {
#ifdef _DEBUG
            /*iCount ++;
            if (iCount==5301)
            {
                int a = 2;
                int b;
                b =a;
            }*/
#endif            

            pLink = m_linkList.GetNext(pos);

            int iNumPoint = (int)GetNFStr(strLine,1," ");
            pLink->m_arrayPt.SetSize(0,iNumPoint);

            for (int i=0; i<iNumPoint; i++)
            {
                mifFile.ReadString(strLine);

                TMPoint point;
                point.iX = LONG(GetFloatFromStr(strLine,0," ")*3600*24);
                point.iY = LONG(GetFloatFromStr(strLine,1," ")*3600*24);

                pLink->m_arrayPt.Add(point);
            }
            pLink->m_rectExtent = TMRect(pLink->m_arrayPt);

            // 计算所有道路的范围之和（=整个地图的范围）
            m_rectMap += TMRect(pLink->m_rectExtent);
        }
    }

    mifFile.Close();

    return TRUE;
}



//////////////////////////////////////////////////////////////////////////
// 查找距离点Point最近的Link

BOOL CTfcParsedMgr::GetLinkByPoint(TMPoint point,CLinkList& aLinkList)
{
    PTNBMapGrid pGrid = GetGridMgr()->GetGridByPoint(point);

    if (pGrid==NULL)
    {
        return FALSE;
    }

    DOUBLE fMinDistance = -1;
    PTLinkAttri pLinkFound = NULL;

    CLinkList* pList = RETRIEVE_LINKLIST(pGrid);

    // 查找距离点Point最近的Link
    POSITION pos = pList->GetHeadPosition();
    while (pos)
    {
        PTLinkAttri pLink = pList->GetNext(pos);
        DOUBLE fDis = pLink->MinDistance(point);

        if (fMinDistance==-1 || fDis<fMinDistance)
        {
            fMinDistance = fDis;
            pLinkFound = pLink;
            if (fDis<=1E-6)
            {
                break;
            }
        }
    }

    ASSERT(pLinkFound!=NULL);

    //
    aLinkList.AddTail(pLinkFound);
    return TRUE;

}

// 返回与指定区域相交的Link
BOOL CTfcParsedMgr::GetLinkByRect(TMRect aRect,CLinkList& aLinkList)
{
    CGridList gridList;

    GetGridMgr()->GetGridByRect(aRect,gridList);

    if (gridList.GetCount()==0)
    {
        return FALSE;
    }

    POSITION posGrid = gridList.GetHeadPosition();

    while (posGrid)
    {
        PTNBMapGrid pGrid = gridList.GetNext(posGrid);

        // 
        DOUBLE fMinDistance = -1;
        PTLinkAttri pLinkFound = NULL;

        CLinkList* pList = RETRIEVE_LINKLIST(pGrid);

        // 查找与aRect相交的Link
        POSITION posLink = pList->GetHeadPosition();
        while (posLink)
        {
            PTLinkAttri pLink = pList->GetNext(posLink);

            BOOL bFlag = pLink->IsIntersects(aRect);

            if(bFlag)
            {
                aLinkList.AddTail(pLink);
            }

        }
    }

    if (aLinkList.GetCount()==0)
    {
        return FALSE;
    }

    return TRUE;
}

void CTfcParsedMgr::MoveLinkToMapCenter(const TLinkAttri& aLink)
{
    TMPoint ptOldCenter = GetMapCenter();
    TMPoint ptNewCenter = aLink.m_arrayPt.GetAt(0);
    TVector vAlong(ptOldCenter,ptNewCenter);
    MapOperation(EMO_MOVE_VECTOR,WPARAM(&vAlong));
}

void CTfcParsedMgr::ActiveLink(CLinkList& linkList)
{
    m_linkActived.RemoveAll();

    POSITION pos = linkList.GetHeadPosition();
    while (pos)
    {
        m_linkActived.AddTail(linkList.GetNext(pos));
    }
}

void CTfcParsedMgr::DrawLink(CDC* pDC) const
{

    CPen newPen;
    CBrush brush;
    COLORREF lineClr;
    lineClr = CLR_DEEPGRAY;

    newPen.CreatePen(PS_SOLID,3,lineClr);
    //brush.CreateSolidBrush(CLR_BKG_2);

    CPen* pOldPen = pDC->SelectObject(&newPen);
    //CBrush* pOldBrush = pDC->SelectObject(&brush);

    // 画所有的Link
    POSITION pos = m_linkList.GetHeadPosition();

    while (pos)
    {
        const PTLinkAttri pLink = m_linkList.GetNext(pos);
        pLink->DrawLink(pDC,*this);
    }

    // 画激活状态的Link
    CPen penActive;
    penActive.CreatePen(PS_SOLID,3,CLR_RED);
    pDC->SelectObject(&penActive);
    pos = m_linkActived.GetHeadPosition();

    while (pos)
    {
        const PTLinkAttri pLink = m_linkActived.GetNext(pos);
        pLink->DrawLink(pDC,*this);
    }


    //
    pDC->SelectObject(pOldPen);
    //pDC->SelectObject(pOldBrush);
}

void CTfcParsedMgr::DrawRoadNode(CDC* pDC) const
{
    if (m_pRoadList==NULL)
    {
        return;
    }

    CPen newPen;
    CPen* pOldPen;
    CBrush brush;
    CBrush* pOldBrush = NULL;

    // 画节点
    newPen.CreatePen(PS_SOLID,1,CLR_DARKGREEN);
    pOldPen = pDC->SelectObject(&newPen);
    brush.CreateSolidBrush(CLR_RED);
    pOldBrush = pDC->SelectObject(&brush);

    POSITION pos = m_pRoadList->GetHeadPosition();
    while (pos)
    {
        const PTRawRoadTfcInf pRoad = m_pRoadList->GetNext(pos);
        pRoad->DrawNode(pDC,*this);
    }
    pDC->SelectObject(pOldPen);
    newPen.DeleteObject();
    pDC->SelectObject(pOldBrush);
    brush.DeleteObject();

}

void CTfcParsedMgr::DrawNodeName(CDC* pDC) const
{
    CFont font;
    CFont* pOldFont;

    // 画节点名称
    int iFontHeight;
    iFontHeight = 12;
    font.CreateFont(iFontHeight,0, 0, 0, FW_THIN, false, false, 0,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, "宋体");

    pOldFont = pDC->SelectObject(&font);
    pDC->SetTextColor(CLR_BLACK);
    pDC->SetBkMode(TRANSPARENT);


    POSITION pos = m_pRoadList->GetHeadPosition();
    while (pos)
    {
        const PTRawRoadTfcInf pRoad = m_pRoadList->GetNext(pos);
        pRoad->DrawRoadName(pDC,*this);
    }

    pDC->SelectObject(pOldFont);
    font.DeleteObject();
}



