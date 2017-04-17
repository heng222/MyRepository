// ChildFrm.cpp : CChildFrame ���ʵ��
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


// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
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


// CChildFrame ���

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


// CChildFrame ��Ϣ�������

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{

    VERIFY(m_HSplitter.CreateStatic(this,2,1));
    VERIFY(m_HSplitter.CreateView(0,0,RUNTIME_CLASS(CWeatherView),CSize(100,500),pContext));
    VERIFY(m_HSplitter.CreateView(1,0,RUNTIME_CLASS(CMainUIView),CSize(100,100),pContext));

    return TRUE;
    // TODO: �ڴ����ר�ô����/����û���

    //return CMDIChildWnd::OnCreateClient(lpcs, pContext);
}
