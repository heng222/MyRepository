// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "Maintain.h"
#include "MaintainView.h"
#include "MaintainTreeView.h"
#include "MainFrm.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMaintainApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_COMMAND(ID_VIEW_SHOWTREEVIEW, OnViewShowtreeview)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SHOWTREEVIEW, OnUpdateViewShowtreeview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_MAXIMIZE | WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION| FWS_ADDTOTITLE
		| FWS_PREFIXTITLE | WS_THICKFRAME;
	
	cs.style &= ~WS_SYSMENU;

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers
BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	//lpcs->style = WS_EX_TOOLWINDOW | WS_EX_WINDOWEDGE  | WS_EX_DLGMODALFRAME;
	// TODO: Add your specialized code here and/or call the base class
	m_wndSplitter.CreateStatic( this,1,2 );
	m_wndSplitter.CreateView( 0, 0, RUNTIME_CLASS(CMaintainTreeView), CSize(80, 500), pContext );
	m_wndSplitter.CreateView( 0, 1, RUNTIME_CLASS(CMaintainView),	  CSize(100,500), pContext );
	m_bTreeShow = TRUE;
	return TRUE;//return CMDIChildWnd::OnCreateClient(lpcs, pContext);
}

void CChildFrame::OnViewShowtreeview() 
{
	// TODO: Add your command handler code here
	if(m_bTreeShow)
	{
		m_bTreeShow=FALSE;
	}
	else
	{
		m_bTreeShow=TRUE;
	}
	((CMaintainApp*)AfxGetApp())->m_bMove=FALSE;
	ReUpdateWindows();
}
void CChildFrame::ReUpdateWindows()
{
	CMaintainTreeView* pTView;
	CMaintainView* pView;
	int y = ::GetSystemMetrics(SM_CXSCREEN);//1280;


	pTView=(CMaintainTreeView*) m_wndSplitter.GetPane(0,0);
	pView=(CMaintainView*) m_wndSplitter.GetPane(0,1);
	CRect rect;
	GetClientRect(&rect);

	CMaintainApp* pApp=(CMaintainApp*)AfxGetApp();
	if(pTView && pView)
	{
		if(!m_bTreeShow)
		{
			pTView->ShowWindow(SW_HIDE);
			rect.right=y;
			pView->MoveWindow(&rect);
			pApp->m_bMove=TRUE;
		}
		else
		{
			pTView->ShowWindow(SW_RESTORE);
			rect.left+=106;
			rect.right=y;
			pView->MoveWindow(&rect);
			pApp->m_bMove=FALSE;
		}
	}
}

void CChildFrame::OnUpdateViewShowtreeview(CCmdUI* pCmdUI) 
{
	//
	CMaintainView* pView = (CMaintainView*)theApp.GetView(RUNTIME_CLASS(CMaintainView));
	pView->m_Menu.CheckMenuItem(pCmdUI->m_nID,!m_bTreeShow?MF_CHECKED:MF_UNCHECKED);

	//
	pCmdUI->Enable(TRUE); 
	pCmdUI->SetCheck(m_bTreeShow);

	
	//////////////////////////////////////////////////////
//	CMenu menu;
//	menu.LoadMenu(IDR_MAINTATYPE);
//	CMenu* pSubMenu = menu.GetSubMenu(2);
//	pSubMenu->CheckMenuItem(ID_VIEW_SHOWTREEVIEW,!m_bTreeShow?MF_CHECKED:MF_UNCHECKED);
}
