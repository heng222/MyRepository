// ChildMulFrame.cpp : implementation file
//

#include "stdafx.h"
#include "maintain.h"
#include "ChildMulFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildMulFrame

IMPLEMENT_DYNCREATE(CChildMulFrame, CMDIChildWnd)

CChildMulFrame::CChildMulFrame()
{
}

CChildMulFrame::~CChildMulFrame()
{
}


BEGIN_MESSAGE_MAP(CChildMulFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildMulFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildMulFrame message handlers

BOOL CChildMulFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= WS_MAXIMIZE | WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION| FWS_ADDTOTITLE
		| FWS_PREFIXTITLE | WS_THICKFRAME;
	
	cs.style &= ~WS_SYSMENU;

	return CMDIChildWnd::PreCreateWindow(cs);
}
