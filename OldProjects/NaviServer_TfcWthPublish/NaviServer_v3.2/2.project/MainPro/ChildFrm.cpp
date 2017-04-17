// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "NaviServer.h"
#include "MainView.h"
#include "LiveLogView.h"
#include "SelectionTreeView.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
    ON_WM_SIZE()
    ON_WM_CREATE()
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

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.style |= WS_MAXIMIZE | WS_CHILD | WS_VISIBLE | WS_OVERLAPPED /*| WS_CAPTION| FWS_ADDTOTITLE*/
		| FWS_PREFIXTITLE | WS_THICKFRAME;

	cs.style &= ~WS_SYSMENU;
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

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  在此添加您专用的创建代码

    return 0;
}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
    VERIFY(m_HSplitter.CreateStatic(this,2,1));
    VERIFY(m_HSplitter.CreateView(1,0,RUNTIME_CLASS(CLiveLogView),CSize(100,100),pContext));

    VERIFY(m_VSplitter.CreateStatic( &m_HSplitter,1,2,WS_CHILD|WS_VISIBLE,m_HSplitter.IdFromRowCol(0,0)));
    VERIFY(m_VSplitter.CreateView(0,0,RUNTIME_CLASS(CSelectionTreeView),CSize(CSelectionTreeView::ETA_OriginalWidth,0),pContext));
    VERIFY(m_VSplitter.CreateView(0,1,RUNTIME_CLASS(CMainView),CSize(0,CMainView::EOriginHeight),pContext));

    // TODO: 在此添加专用代码和/或调用基类
    return TRUE;
    //return CMDIChildWnd::OnCreateClient(lpcs, pContext);
}

BOOL CChildFrame::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message==WM_MOUSEMOVE)
    {
        CPoint cursorPt(LOWORD(pMsg->lParam),HIWORD(pMsg->lParam));
        if ((pMsg->hwnd == m_HSplitter.GetSafeHwnd()) &&
            (cursorPt.y<CMainView::EMinHeight) )
        {
            return TRUE;
        }
        else if (pMsg->hwnd == m_VSplitter.GetSafeHwnd())
        {
            CRect clientRect;
            GetClientRect(clientRect);
            if ( cursorPt.x<CSelectionTreeView::ETA_MinWidth ||
                 clientRect.right-cursorPt.x<CMainView::EMinWidth )
            {
                return TRUE;
            }
        }
    }

    return CMDIChildWnd::PreTranslateMessage(pMsg);
}

void CChildFrame::OnSize(UINT nType, int cx, int cy)
{
    CMDIChildWnd::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码
    if(m_HSplitter.GetSafeHwnd() && m_VSplitter.GetSafeHwnd())
    {
        SetLayout();
    }
}

void CChildFrame::SetLayout()
{
    int cy0, cy1, cymin, cy;
    m_HSplitter.GetRowInfo(0, cy0, cymin);
    m_HSplitter.GetRowInfo(1, cy1, cymin);
    cy = cy0 + cy1;
    int minCy0 = (int)(cy * 0.75);

    if(cy0 != minCy0)
    {
        cy0 = minCy0;
        m_HSplitter.SetRowInfo(0, cy0 , cymin);//设置tree视图的高度
        //m_HSplitter.SetRowInfo(0, 0 , 0);//设置tree视图的高度
    }
    //m_HSplitter.SetColumnInfo(1,10,10);
    m_HSplitter.RecalcLayout();


}


void CChildFrame::ShowView(CChildFrame::TViewID viewID)
{

    switch(viewID)
    {
    case EVI_TREEVIEW:
        {

        }
    	break;
    case EVI_LIVLOGVIEW:
        {
            
        }
        break;
    case EVI_MAINVIEW:
        {

        }
        break;
    }
}


void CChildFrame::HideView(CChildFrame::TViewID viewID)
{

}
