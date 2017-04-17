// MultStaView.cpp : implementation file
//

#include "stdafx.h"
#include "maintain.h"
#include "MultStaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMaintainApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CMultStaView

IMPLEMENT_DYNCREATE(CMultStaView, CScrollView)

CMultStaView::CMultStaView()
{
}

CMultStaView::~CMultStaView()
{
}


BEGIN_MESSAGE_MAP(CMultStaView, CScrollView)
	//{{AFX_MSG_MAP(CMultStaView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultStaView drawing

void CMultStaView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	//EnableWindow(FALSE);
	// TODO: calculate the total size of this view
	CSize sizeTotal;
	sizeTotal.cx = 1280;
    sizeTotal.cy = 1024;
	SetScrollSizes(MM_TEXT, sizeTotal);

	//
	theApp.m_ZCTMag.Create(this,NULL);
	theApp.m_ZCTMag.DrawStation();
	//theApp.m_ZCTMag.Create(theApp.m_pMainWnd);
}

void CMultStaView::OnDraw(CDC* pDC)
{
	pDC->TextOut(10,10,"void CMultStaView::OnDraw(CDC* pDC)");

/*	CClientDC dc(this);
	////Ìî³äÆÁÄ»µ×É«ÎªºÚÉ«
	
	CBrush brush;
	brush.CreateSolidBrush (RGB(0,0,0));	
	CBrush* pOldBrush = dc.SelectObject (&brush);
	dc.Rectangle (CRect(0,0,1280,1024));
	dc.SelectObject(pOldBrush);
*/
	//
	///CMaintainDoc* pDoc = GetDocument();
	// TODO: add draw code here

}

/////////////////////////////////////////////////////////////////////////////
// CMultStaView diagnostics

#ifdef _DEBUG
void CMultStaView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMultStaView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMaintainDoc* CMultStaView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMaintainDoc)));
	return (CMaintainDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMultStaView message handlers



void CMultStaView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	TRACE("CMultStaView::OnLButtonDown, point.x = %d,point.y = %d\n",point.x,point.y);
	CScrollView::OnLButtonDown(nFlags, point);
}
