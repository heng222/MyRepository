// ChildFrm.cpp : CChildFrame 类的实现
//
#include "stdafx.h"
#include "MainUI.h"

#include "ChildFrm.h"
#include ".\childfrm.h"

#include "WeatherView.h"
#include "MainUIView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
END_MESSAGE_MAP()


// CChildFrame 构造/析构

CChildFrame::CChildFrame()
{
	// TODO: 在此添加成员初始化代码
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
    cs.style |= WS_MAXIMIZE | WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION| FWS_ADDTOTITLE
        | FWS_PREFIXTITLE | WS_THICKFRAME;

    //cs.style &= ~WS_SYSMENU;
    return TRUE;
}


// CChildFrame 诊断

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


// CChildFrame 消息处理程序

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{

    VERIFY(m_HSplitter.CreateStatic(this,2,1));
    VERIFY(m_HSplitter.CreateView(0,0,RUNTIME_CLASS(CWeatherView),CSize(100,500),pContext));
    VERIFY(m_HSplitter.CreateView(1,0,RUNTIME_CLASS(CMainUIView),CSize(100,100),pContext));

    return TRUE;
    // TODO: 在此添加专用代码和/或调用基类

    //return CMDIChildWnd::OnCreateClient(lpcs, pContext);
}
