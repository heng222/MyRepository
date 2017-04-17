// MaintainView.cpp : implementation of the CMaintainView class
//

#include "stdafx.h"
#include "Maintain.h"
#include "mainfrm.h"
//#include "MaintainDoc.h"
#include "MaintainView.h"

//#include <fstream.h>
#include <STDIO.H>
#include <afxmt.h>
extern CMaintainApp theApp;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaintainView

IMPLEMENT_DYNCREATE(CMaintainView, CScrollView)

BEGIN_MESSAGE_MAP(CMaintainView, CScrollView)
	//{{AFX_MSG_MAP(CMaintainView)
	ON_COMMAND(ID_OPERATE_CONSTRUCTQUERY, OnOperateConstructquery)
	ON_COMMAND(ID_OPERATOR_CONSTRUCTREQUEST, OnOperatorConstructrequest)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaintainView construction/destruction

CMaintainView::CMaintainView()
{
	// TODO: add construction code here
	
}

CMaintainView::~CMaintainView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMaintainView drawing

void CMaintainView::OnDraw(CDC* pDC)
{
	
	CMaintainDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	
}

void CMaintainView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CMaintainDoc *pDoc = GetDocument();
	
	//m_pDoc->SetTitle(theApp.m_strStationName+"站场图");
	pDoc->SetTitle("");
	
	CSize sizeTotal;
    sizeTotal.cx = 100;
    sizeTotal.cy = 200;
	CSize sizePage(sizeTotal.cx/2,sizeTotal.cy/2);
	CSize sizeLine(sizeTotal.cx/10,sizeTotal.cy/10);
    SetScrollSizes(MM_TEXT, sizeTotal,sizePage,sizeLine);

	//
	
	pDoc->m_ZCTMag.Create(this,NULL,TRUE);

	//画股道、信号灯、股道封锁灯、区间封锁灯....	
	pDoc->m_ZCTMag.DrawStation(CReadStationInf::GetActiveStation());
}

/////////////////////////////////////////////////////////////////////////////
// CMaintainView printing

BOOL CMaintainView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMaintainView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMaintainView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMaintainView diagnostics

#ifdef _DEBUG
void CMaintainView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMaintainView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMaintainDoc* CMaintainView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMaintainDoc)));
	return (CMaintainDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMaintainView message handlers

/*void CMaintainView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	CMenu menu;
  	menu.LoadMenu(IDR_MAINTATYPE);
	CMenu *pMenu = menu.GetSubMenu(1);
	if ( ((CMainFrame*)(theApp.m_pMainWnd))->m_bConnected == FALSE )
	{
		pMenu->EnableMenuItem(ID_OPERATE_REFRESH,MF_GRAYED);
	}
	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y,this);
}
*/
void CMaintainView::OnOperateConstructquery() 
{
	// TODO: Add your command handler code here
	CConstructQuery dlg;
	dlg.DoModal();
}

void CMaintainView::OnOperatorConstructrequest() 
{
	// TODO: Add your command handler code here
	CConstructRequest dlg;
	dlg.DoModal();
}
