#include "StdAfx.h"
#include ".\tfcparsedmgr.h"
#include <CommonFunc.h>
#include "GlobalMacro.h"
#include <UserColors.h>

//////////////////////////////////////////////////////////////////////////

#define     INI_FILE_NAME   _T("TfcRoad2Link.ini")  // 

#define         MIN_DISTANCE        5 // 像素

//////////////////////////////////////////////////////////////////////////
CTfcParsedMgr::CTfcParsedMgr(void)
{
    m_rectMap.SetNull();
}

CTfcParsedMgr::~CTfcParsedMgr(void)
{
}



void CTfcParsedMgr::Close()
{
    // 
    CString key;
    CLinkList* pa;
    for( POSITION pos = m_mapRoadIDtoLinks.GetStartPosition(); pos != NULL; )
    {
        m_mapRoadIDtoLinks.GetNextAssoc( pos, key, pa );

        pa->ClearList();
        pa->RemoveAll();

        delete pa;
    }
    m_mapRoadIDtoLinks.RemoveAll();

    //
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
//#ifdef _DEBUG
//    POSITION pos = listGrid.GetHeadPosition();
//    while (pos)
//    {
//        PTNBMapGrid pGrid = listGrid.GetNext(pos);
//        TRACE("GRID(%d,%d)\n",pGrid->m_wRowID,pGrid->m_wColID);
//    }
//#endif
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
}

void CTfcParsedMgr::OnGridsBuilt()
{

    // 将Link数据与网格进行关联
    IMsgAppLogs aLog;
    aLog.UpdateToCurrentTime();
    aLog.strComments.Format(_T("正在将Link关联到网格中……"));
    NbsSendModuleMsg(&aLog);

    // 将Link与网格关联
    CString key;
    CLinkList* pLinklist = NULL;
    for( POSITION pos = m_mapRoadIDtoLinks.GetStartPosition(); pos != NULL; )
    {
        m_mapRoadIDtoLinks.GetNextAssoc( pos, key, pLinklist );

        // 
        POSITION posSub = pLinklist->GetHeadPosition();
        while (posSub)
        {
            const PTLinkAttri pLink = pLinklist->GetNext(posSub);
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
    CString strFilePath = GetExePath()+PATH_DATA_FILE+INI_FILE_NAME;

    CStdioFile stdFile;
    if ( !stdFile.Open(strFilePath,CFile::modeRead|CFile::shareDenyNone))
    {
        return FALSE;
    }

    //
    CString strLine;

    while (stdFile.ReadString(strLine))
    {
        if (strLine.Find(_T("Road="))!=-1)
        {
            // 取出Road信息
            CString strRoadInf = GetSFStr((LPCTSTR)strLine,1,"=").c_str();

            // RoadID（原ID与新ID）
            CString strRoadID = GetSFStr((LPCTSTR)strRoadInf,0,",").c_str();
            strRoadID.Trim();
            DWORD dwRoadID = (DWORD)GetNFStr(strRoadInf,1,",");


            // 取出此Road对应的Link个数
            int iNumLink = (int)GetNFStr(strRoadInf,2,",");

            // 构建LinkList
            CLinkList* pLinkList = new CLinkList;
            for (int i=0; i<iNumLink; i++)
            {
                stdFile.ReadString(strLine); // 读一条Link记录

                PTLinkAttri pLink = new TLinkAttri;

                int iIndex = 0;

                // RoadID 
                pLink->m_dwRoadID = dwRoadID;

                // LinkID
                pLink->m_strLinkID = GetSFStr((LPCTSTR)strLine,iIndex++,",").c_str();
                // Link名称
                pLink->m_strLinkName = GetSFStr((LPCTSTR)strLine,iIndex++,",").c_str();
                pLink->m_strLinkName.Trim("\"");
                // Link形状点
                int iNumPt = (int)GetNFStr(strLine,iIndex++,",");
                pLink->m_arrayPt.SetSize(iNumPt);
                for (int jj=0; jj<iNumPt; jj++)
                {
                    TMPoint shapePt;
                    shapePt.iX = (TLcType)GetNFStr(strLine,iIndex++,",");
                    shapePt.iY = (TLcType)GetNFStr(strLine,iIndex++,",");
                    pLink->m_arrayPt.SetAt(jj,shapePt);

                    //
                    if (jj==0)
                    {
                        pLink->m_StartPos = shapePt;
                    }
                    else if (jj==iNumPt-1)
                    {
                        pLink->m_EndPos = shapePt;
                    }
                }
                // Link的外接矩形
                pLink->m_rectExtent = TMRect(pLink->m_arrayPt);

                // 计算所有道路的范围之和（=整个地图的范围）
                m_rectMap += TMRect(pLink->m_rectExtent);

                // 
                pLinkList->AddTail(pLink);
            }

            //
            m_mapRoadIDtoLinks.SetAt(strRoadID,pLinkList);
        }
    }

    //
    stdFile.Close();

    return TRUE;
}

void CTfcParsedMgr::UpdateLinkInf(CString strRoadID,int iSpeed)
{
    // 
    CLinkList* pLinkList = NULL;
    m_mapRoadIDtoLinks.Lookup(strRoadID,pLinkList);
    if (pLinkList==NULL)
    {
        return;
    }

    POSITION pos = pLinkList->GetHeadPosition();
    while (pos)
    {
        PTLinkAttri pLink = pLinkList->GetNext(pos);
        pLink->SetSpeed((iSpeed));
    }
}



//////////////////////////////////////////////////////////////////////////

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

    //
    if (pLinkFound!=NULL && fMinDistance<1E-6)
    {
        aLinkList.AddTail(pLinkFound);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
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



