// SelectionTreeView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NaviServer.h"
#include "MainView.h"
#include "SelectionTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CNaviServerApp theApp;
// CSelectionTreeView

IMPLEMENT_DYNCREATE(CSelectionTreeView, CTreeView)

CSelectionTreeView::CSelectionTreeView()
{
}

CSelectionTreeView::~CSelectionTreeView()
{
}

BEGIN_MESSAGE_MAP(CSelectionTreeView, CTreeView)
    ON_WM_CREATE()
    ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnTvnSelchanged)
END_MESSAGE_MAP()


// CSelectionTreeView ���

#ifdef _DEBUG
void CSelectionTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CSelectionTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG


// CSelectionTreeView ��Ϣ�������

BOOL CSelectionTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.style |= TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_SHOWSELALWAYS;


    return CTreeView::PreCreateWindow(cs);
}

int CSelectionTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CTreeView::OnCreate(lpCreateStruct) == -1)
        return -1;


    // 1. Create ImageList and associated it with TreeView
    m_imageList.Create(16,16, ILC_COLOR8|ILC_MASK, 5,1);
    //m_imageList.SetBkColor(::GetSysColor(COLOR_BTNFACE));
    m_imageList.Add(AfxGetApp()->LoadIcon(IDI_BALANCESERVER));
    m_imageList.Add(AfxGetApp()->LoadIcon(IDI_MOBUSER_ACTIVE));
    m_imageList.Add(AfxGetApp()->LoadIcon(IDI_MOBUSER_INVALID));
    m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_WEATHER));
    m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TRAFFIC));

    GetTreeCtrl().SetImageList(&m_imageList, TVSIL_NORMAL);

    // 2. Initialize tree structure with common values
    m_hInsertTvStruc.hParent = NULL;
    m_hInsertTvStruc.hInsertAfter = TVI_LAST;
    m_hInsertTvStruc.item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_PARAM;
    m_hInsertTvStruc.item.hItem = NULL; 
    m_hInsertTvStruc.item.state = 0;
    m_hInsertTvStruc.item.stateMask = 0;
    m_hInsertTvStruc.item.cchTextMax = 20;
    m_hInsertTvStruc.item.cChildren = 0;
    m_hInsertTvStruc.item.lParam = 0;

    return 0;
}
void CSelectionTreeView::OnInitialUpdate()
{
    CTreeView::OnInitialUpdate();

    // 1. Initialize the tree control

    // top level
    m_hInsertTvStruc.item.pszText = "���ؾ��������";
    m_hInsertTvStruc.item.iImage = 0;
    m_hInsertTvStruc.item.iSelectedImage = 0;
    m_hBalanceServer = GetTreeCtrl().InsertItem(&m_hInsertTvStruc);

    m_hInsertTvStruc.item.pszText = "�����ṩ��(SP)";
    m_hInsertTvStruc.item.iImage = 0;
    m_hInsertTvStruc.item.iSelectedImage = 0;
    m_hSpServer = GetTreeCtrl().InsertItem(&m_hInsertTvStruc);

    m_hInsertTvStruc.item.pszText = "�ֻ��ն�(Э��汾V2-BIN)";
    m_hInsertTvStruc.item.iImage = 1;
    m_hInsertTvStruc.item.iSelectedImage = 1;
    m_hMobiles_Bin = GetTreeCtrl().InsertItem(&m_hInsertTvStruc);

    m_hInsertTvStruc.item.pszText = "�ֻ��ն�(Э��汾V1-CHAR)";
    m_hInsertTvStruc.item.iImage = 1;
    m_hInsertTvStruc.item.iSelectedImage = 1;
    m_hMobiles_Char = GetTreeCtrl().InsertItem(&m_hInsertTvStruc);

    /*m_hInsertTvStruc.item.pszText = "������Ϣ";
    m_hInsertTvStruc.item.iImage = 3;
    m_hInsertTvStruc.item.iSelectedImage = 3;
    m_hWthInf = GetTreeCtrl().InsertItem(&m_hInsertTvStruc);*/

    
    // second level(Marge)
    /*tvinsert.hParent = hMom;
    tvinsert.item.pszText = "Bart";
    tvinsert.item.iImage = 4;
    pTree->InsertItem(&tvinsert);*/

    // Second level (Henry)
    /*tvinsert.hParent = hHenry;
    tvinsert.item.lParam = 0x1111;
    tvinsert.item.pszText = "Chary";
    tvinsert.item.iImage = 5;
    pTree->InsertItem(&tvinsert);
    tvinsert.item.lParam = 0;
    tvinsert.item.pszText = "Liang";
    pTree->InsertItem(&tvinsert);*/

    // third level
    /*tvinsert.hParent = hOther;
    tvinsert.item.pszText = "Dogbert";
    tvinsert.item.iImage = 7;
    pTree->InsertItem(&tvinsert);
    tvinsert.item.pszText = "Ratbert";
    pTree->InsertItem(&tvinsert);*/
}


void CSelectionTreeView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

    // TODO: �ڴ���ӿؼ�֪ͨ����������

    HTREEITEM hSelected = pNMTreeView->itemNew.hItem;
    HTREEITEM hParent = GetTreeCtrl().GetParentItem(hSelected);

    if (hSelected != NULL) 
    {
        TV_ITEM item;
        item.mask = TVIF_HANDLE|TVIF_PARAM;
        item.hItem = hSelected;
        VERIFY(GetTreeCtrl().GetItem(&item));

        // Active a corresponding page.
        CMainView* pMainVew = (CMainView*)(theApp.GetView(RUNTIME_CLASS(CMainView)));
        if (pMainVew)
        {
            if (hSelected==m_hBalanceServer)
            {
                pMainVew->ActivePage(CMainSheet::EPN_BALANCESERVER);
            } 
            else if( hSelected==m_hSpServer)
            {
                pMainVew->ActivePage(CMainSheet::EPN_SERVICEPROVIDER);
            }
            /*else if (hSelected==m_hWthInf)
            {
                pMainVew->ActivePage(CMainSheet::EPN_WEATHERPAGE);
            }*/
            else if ( hSelected==m_hMobiles_Bin ||
                hSelected==m_hMobiles_Char || 
                hParent ==m_hMobiles_Char ||
                hParent ==m_hMobiles_Bin)
            {
                pMainVew->ActivePage(CMainSheet::EPN_MOBILECLIENT);
                
                int iProType;
                DWORD dwFldID = DWORD(item.lParam);

                if (hParent==m_hMobiles_Bin)
                {
                    iProType = TMobileFrameBin::E_PRO_FLAG;
                    pMainVew->SetActivedFldID(iProType,dwFldID);
                }
                else if(hParent==m_hMobiles_Char)
                { 
                    iProType = TMobileFrame_Char::E_PRO_FLAG;
                    pMainVew->SetActivedFldID(iProType,dwFldID);
                }

            }
        }
    }

    // 
    *pResult = 0;
}


//////////////////////////////////////////////////////////////////////////
// Private functions
HTREEITEM CSelectionTreeView::FindItem(HTREEITEM hRootItem,LPARAM lParam)
{
    CTreeCtrl& treeCtrl = GetTreeCtrl();
    if (treeCtrl.ItemHasChildren(hRootItem))
    {
        HTREEITEM hChildItem = treeCtrl.GetChildItem(hRootItem);

        while (hChildItem != NULL)
        {
            TV_ITEM item;
            item.mask = TVIF_HANDLE | TVIF_PARAM;
            item.hItem = hChildItem;
            VERIFY(treeCtrl.GetItem(&item));
            if (item.lParam==lParam)
            {                    
                return hChildItem;
            }
            hChildItem = treeCtrl.GetNextItem(hChildItem, TVGN_NEXT);
        }
    }

    return NULL;
}
void CSelectionTreeView::AddNewLogs(PIMsgAppLogs pNewLog)
{
    if (pNewLog->iLogType==IMsgNetLog::ELGT_Network)
    {
        PIMsgNetLog pNetLog = (PIMsgNetLog)pNewLog;
        if ( pNetLog->iProtocolType==TMobileFrameBin::E_PRO_FLAG )
        {
            if (pNetLog->iEventType==IMsgNetLog::ENLT_NEWCONNECTION)
            {
                // Second level     
                m_hInsertTvStruc.hParent = m_hMobiles_Bin;
                m_hInsertTvStruc.item.pszText = TSockAddr(pNetLog->byClientIP).DottedDecimal();
                m_hInsertTvStruc.item.iImage = 1; 
                m_hInsertTvStruc.item.iSelectedImage = 1;
                m_hInsertTvStruc.item.lParam = pNetLog->dwComfieldID;
                GetTreeCtrl().InsertItem(&m_hInsertTvStruc);
            }
            else if (pNetLog->iEventType==IMsgNetLog::ENLT_CLOSECONNECT)
            {
                HTREEITEM hInvalidItem = FindItem(m_hMobiles_Bin,pNetLog->dwComfieldID);
                if (hInvalidItem!=NULL)
                {
                    GetTreeCtrl().SetItemImage(hInvalidItem,2,2);
                }
                else
                {
                    // Logical Error!
                    IMsgAppLogs aLogicalErrorLog;
                    aLogicalErrorLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
                    aLogicalErrorLog.strComments.Format(_T("[BIN]�ر�ͨ������������ͼ��û���ҵ���ʶ��Ϊ%d��㣡"),
                        pNetLog->dwComfieldID);
                }
            }
            else if (pNetLog->iEventType==IMsgNetLog::ENLT_DELCONNECTION)
            {
                HTREEITEM hDelItem = FindItem(m_hMobiles_Bin,pNetLog->dwComfieldID);
                if (hDelItem!=NULL)
                {
                    GetTreeCtrl().DeleteItem(hDelItem);
                }
                else
                {
                    // Logical Error!
                    IMsgAppLogs aLogicalErrorLog;
                    aLogicalErrorLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
                    aLogicalErrorLog.strComments.Format(_T("[BIN]ɾ��ͨ������������ͼ��û���ҵ���ʶ��Ϊ%d��㣡"),
                        pNetLog->dwComfieldID);
                }
            }
        }
        else if (pNetLog->iProtocolType==TMobileFrame_Char::E_PRO_FLAG)
        {
            if (pNetLog->iEventType==IMsgNetLog::ENLT_NEWCONNECTION)
            {
                // Second level     
                m_hInsertTvStruc.hParent = m_hMobiles_Char;
                m_hInsertTvStruc.item.pszText = TSockAddr(pNetLog->byClientIP).DottedDecimal();            
                m_hInsertTvStruc.item.iImage = 1; 
                m_hInsertTvStruc.item.iSelectedImage = 1;
                m_hInsertTvStruc.item.lParam = pNetLog->dwComfieldID;
                GetTreeCtrl().InsertItem(&m_hInsertTvStruc);
            }
            else if (pNetLog->iEventType==IMsgNetLog::ENLT_CLOSECONNECT)
            {
                HTREEITEM hInvalidItem = FindItem(m_hMobiles_Char,pNetLog->dwComfieldID);
                if (hInvalidItem!=NULL)
                {
                    GetTreeCtrl().SetItemImage(hInvalidItem,2,2);
                }
                else
                {
                    // Logical Error!
                    IMsgAppLogs aLogicalErrorLog;
                    aLogicalErrorLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
                    aLogicalErrorLog.strComments.Format(_T("[CHAR]�ر�ͨ������������ͼ��û���ҵ���ʶ��Ϊ%d��㣡"),
                        pNetLog->dwComfieldID);
                }
            }
            else if (pNetLog->iEventType==IMsgNetLog::ENLT_DELCONNECTION)
            {
                HTREEITEM hDelItem = FindItem(m_hMobiles_Char,pNetLog->dwComfieldID);
                if (hDelItem!=NULL)
                {
                    GetTreeCtrl().DeleteItem(hDelItem);
                }
                else
                {
                    // Logical Error!
                    IMsgAppLogs aLogicalErrorLog;
                    aLogicalErrorLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
                    aLogicalErrorLog.strComments.Format(_T("[CHAR]�ر�ͨ������������ͼ��û���ҵ���ʶ��Ϊ%d��㣡"),
                        pNetLog->dwComfieldID);
                }
            }

        }
        else if (pNetLog->iProtocolType==TBusinessFrm::E_PRO_FLAG)
        {
        }
        else if (pNetLog->iProtocolType==TSpFrame::E_PRO_FLAG)
        {
        }
    }
}