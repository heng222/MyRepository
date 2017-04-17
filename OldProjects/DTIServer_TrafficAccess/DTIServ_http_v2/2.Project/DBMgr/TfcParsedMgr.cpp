#include "StdAfx.h"
#include ".\tfcparsedmgr.h"
#include <CommonFunc.h>
#include "GlobalMacro.h"
#include <UserColors.h>

//////////////////////////////////////////////////////////////////////////

#define     INI_FILE_NAME   _T("TfcRoad2Link.ini")  // 

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

void CTfcParsedMgr::Draw(CDC* pDC) const
{
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
            pLink->DrawLink(pDC,*this);
        }
    }
}


//////////////////////////////////////////////////////////////////////////
// From CMapEngine

BOOL CTfcParsedMgr::OnInitialize(TEgAttri& aAttri,TMRect& mapRect,CSize& sizeGrid)
{
    // �޸ı�����
    aAttri.dwZoomScale = 125000;
    aAttri.dwMaxScale = 500;
    aAttri.dwMinScale = 740000;
    aAttri.fUnitZoom = 1.5;
    aAttri.fPhysicPerLogic = 1000;


    // �޸���������
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
    aLog.strComments.Format(_T("Link�������ڹ�������(��ͼ��Χ(<%d,%ld>,<%ld,%ld>)��ÿ�����С%d*%d��������(%d��%d))����"),
        rectMap.iTl.iX, rectMap.iTl.iY, rectMap.iBr.iX, rectMap.iBr.iY,
        sizeGrid.cx, sizeGrid.cy,   GetGridMgr()->GetNumOfRow(), GetGridMgr()->GetNumOfCol());

    NbsSendModuleMsg(&aLog);
}

void CTfcParsedMgr::OnBuildGrid(PTNBMapGrid pGrid)
{

    CLinkList* pLinkList = new CLinkList;
    SET_LINKLIST(pGrid,pLinkList);

#ifdef _TRACE_GRID_INFO_TFCROAD

    TRACE("����%d���к�%d���к�%d����Χ<(%d,%d),(%d,%d)>\n",
        pGrid->m_wGridID,pGrid->m_wRowID,pGrid->m_wColID,
        pGrid->m_rectExtent.iTl.iX,pGrid->m_rectExtent.iTl.iY,
        pGrid->m_rectExtent.iBr.iX,pGrid->m_rectExtent.iBr.iY);

#endif
}

void CTfcParsedMgr::OnGridsBuilt()
{

    // ��Link������������й���
    IMsgAppLogs aLog;
    aLog.UpdateToCurrentTime();
    aLog.strComments.Format(_T("���ڽ�Link�����������С���"));
    NbsSendModuleMsg(&aLog);

    // ��Link���������

    // 
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
// Functions 

BOOL CTfcParsedMgr::Open()
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
            // ȡ��Road��Ϣ
            CString strRoadInf = GetSFStr((LPCTSTR)strLine,1,"=").c_str();

            // RoadID��ԭID����ID��
            CString strRoadID = GetSFStr((LPCTSTR)strRoadInf,0,",").c_str();
            strRoadID.Trim();
            DWORD dwRoadID = (DWORD)GetNFStr(strRoadInf,1,",");


            // ȡ����Road��Ӧ��Link����
            int iNumLink = (int)GetNFStr(strRoadInf,2,",");

            // ����LinkList
            CLinkList* pLinkList = new CLinkList;
            for (int i=0; i<iNumLink; i++)
            {
                stdFile.ReadString(strLine); // ��һ��Link��¼

                PTLinkAttri pLink = new TLinkAttri;

                int iIndex = 0;

                // RoadID 
                pLink->m_dwRoadID = dwRoadID;

                // LinkID
                pLink->m_strLinkID = GetSFStr((LPCTSTR)strLine,iIndex++,",").c_str();
                // Link����
                pLink->m_strLinkName = GetSFStr((LPCTSTR)strLine,iIndex++,",").c_str();
                pLink->m_strLinkName.Trim("\"");
                // Link��״��
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
                // Link����Ӿ���
                pLink->m_rectExtent = TMRect(pLink->m_arrayPt);

                // �������е�·�ķ�Χ֮�ͣ�=������ͼ�ķ�Χ��
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


CLinkList* CTfcParsedMgr::GetLinksByRoadID(const CString& strRoadID) const
{
    CLinkList* pLinkList = NULL;

    m_mapRoadIDtoLinks.Lookup(strRoadID,pLinkList);

    return pLinkList;
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
