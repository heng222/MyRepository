// MaintainTreeView.cpp : implementation file
//

#include "stdafx.h"
#include "Maintain.h"
#include "MainFrm.h"
#include "MaintainTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMaintainApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CMaintainTreeView

IMPLEMENT_DYNCREATE(CMaintainTreeView, CTreeView)

CMaintainTreeView::CMaintainTreeView()
{
}

CMaintainTreeView::~CMaintainTreeView()
{
}


BEGIN_MESSAGE_MAP(CMaintainTreeView, CTreeView)
	//{{AFX_MSG_MAP(CMaintainTreeView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaintainTreeView drawing

void CMaintainTreeView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMaintainTreeView diagnostics

#ifdef _DEBUG
void CMaintainTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CMaintainTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMaintainTreeView message handlers

int CMaintainTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_ImageList.Create (IDB_STATION, 32, 1, RGB(0,255,0));
	GetTreeCtrl().SetImageList (&m_ImageList, TVSIL_NORMAL);
	GetTreeCtrl().SetBkColor(RGB(164,164,164));
	return 0;
}

BOOL CMaintainTreeView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style=WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | TVS_SINGLEEXPAND|TVIS_BOLD; //|TVS_HASLINES|TVS_LINESATROOT
	return CTreeView::PreCreateWindow(cs);
}

void CMaintainTreeView::OnInitialUpdate() 
{
	CTreeView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	HTREEITEM hRoot;//树控制项目句柄
	TV_INSERTSTRUCT TCItem;//插入数据项数据结构
	CString m_strTemp;
	
	int i,l;
	//l=theApp.m_strlName[0].GetCount();
	const CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	l = pStationInf->GetLength();
	for(i=0;i<l;i++)//增加各站场
	{
		TCItem.hParent=TVI_ROOT;//增加根项
		TCItem.hInsertAfter=TVI_LAST;//在最后项之后
		TCItem.item.mask=TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE;//设屏蔽
		m_strTemp = pStationInf->GetName(i,FALSE);//theApp.m_strlName[0].GetAt(theApp.m_strlName[0].FindIndex(i));
		TCItem.item.pszText=m_strTemp.GetBuffer(m_strTemp.GetLength());
		m_strTemp.ReleaseBuffer();
		TCItem.item.lParam=i;//序号
		TCItem.item.iImage=0;//正常图标
		TCItem.item.iSelectedImage=1;//选中时图标
		hRoot=GetTreeCtrl().InsertItem(&TCItem);//返回根项句柄
	}

	//MFC
	HTREEITEM hItem = GetItemByName(GetTreeCtrl().GetSafeHwnd(),NULL, 
		pStationInf->GetName(CReadStationInf::GetActiveStation()));
	if (hItem != NULL)
        GetTreeCtrl().SelectItem(hItem);
/*
	//SDK
	HTREEITEM hItem;
    hItem = GetItemByName(hWndTreeCtrl, NULL, "Jeff");
    if (hItem != NULL)
        SendMessage(hWndTreeCtrl, TVM_SELECTITEM, TVGN_CARET,(LPARAM)hItem);
*/
}

void CMaintainTreeView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	const CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	//
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	int i,l,z=0;
	CString strText;
	HTREEITEM hItem;
	hItem=GetTreeCtrl().GetSelectedItem();

	char ch[100];
	TV_ITEM tv;
	tv.mask=TVIF_TEXT|TVIF_HANDLE;
	tv.hItem=hItem;
	tv.pszText=ch;//字串指针指向字符数组
	tv.cchTextMax=100;
	GetTreeCtrl().GetItem(&tv);
	strText=ch;
	hItem=GetTreeCtrl().GetParentItem(hItem);
	if(hItem==NULL)
	{
		//l=theApp.m_strlName[0].GetCount();
		l = pStationInf->GetLength();
		for(i=0;i<l;i++)
		{
			if(strText == pStationInf->GetName(i,FALSE))//theApp.m_strlName[0].GetAt(theApp.m_strlName[0].FindIndex(i)))
			{
				z=i+1;
				break;
			}
		}
		//
		int iOldID = CReadStationInf::GetActiveStation();
		int iNewID = pStationInf->GetStationID(z-1);
		if(z>0 && iOldID != iNewID )
		{
			pStationInf->SetActiveStation(iNewID);
			
			//画股道、信号灯、股道封锁灯、区间封锁灯....	
			theApp.m_ZCTMag.DrawStation(CReadStationInf::GetActiveStation());
			((CMainFrame*)AfxGetMainWnd())->RequireStationStatus();
		}
	}
	*pResult = 0;
}

#define MAXTEXTLEN 50

HTREEITEM CMaintainTreeView::GetItemByName(HWND hWnd, HTREEITEM hItem,LPCTSTR szItemName)
{
    // If hItem is NULL, start search from root item.
	if (hItem == NULL)
        hItem = (HTREEITEM)::SendMessage(hWnd, TVM_GETNEXTITEM,TVGN_ROOT, 0);
	while (hItem != NULL)
    {
        char szBuffer[MAXTEXTLEN+1];
        TV_ITEM item;
		
        item.hItem = hItem;
        item.mask = TVIF_TEXT | TVIF_CHILDREN;
        item.pszText = szBuffer;
        item.cchTextMax = MAXTEXTLEN;
		::SendMessage(hWnd, TVM_GETITEM, 0, (LPARAM)&item);
		
        // Did we find it?
        if (lstrcmp(szBuffer, szItemName) == 0)
            return hItem;
		
        // Check whether we have child items.
        if (item.cChildren)
        {
            // Recursively traverse child items.
            HTREEITEM hItemFound, hItemChild;
			
			hItemChild = (HTREEITEM)::SendMessage(hWnd, TVM_GETNEXTITEM,TVGN_CHILD, (LPARAM)hItem);
			hItemFound = GetItemByName(hWnd, hItemChild, szItemName);
			
            // Did we find it?
            if (hItemFound != NULL)
                return hItemFound;
        }
		
        // Go to next sibling item.
		hItem = (HTREEITEM)::SendMessage(hWnd, TVM_GETNEXTITEM,TVGN_NEXT, (LPARAM)hItem);
    }
    // Not found.
    return NULL;
}
