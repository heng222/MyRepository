// ChildFrm.cpp : CChildFrame ���ʵ��
//
#include "stdafx.h"
#include "MainUI.h"

#include "ChildFrm.h"
#include "LogView.h"
#include "RawTfcView.h"
#include "ParsedTfcView.h"
#include ".\childfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
    ON_WM_SIZE()
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

    cs.style &= ~WS_SYSMENU;
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
    VERIFY(m_HSplitter.CreateView(1,0,RUNTIME_CLASS(CLogView),CSize(100,0),pContext));

    VERIFY(m_VSplitter.CreateStatic( &m_HSplitter,1,2,WS_CHILD|WS_VISIBLE,m_HSplitter.IdFromRowCol(0,0)));
    VERIFY(m_VSplitter.CreateView(0,0,RUNTIME_CLASS(CRawTfcView),CSize(500,500),pContext));
    VERIFY(m_VSplitter.CreateView(0,1,RUNTIME_CLASS(CParsedTfcView),CSize(0,500),pContext));

    return TRUE;
    // TODO: �ڴ����ר�ô����/����û���


    //return CMDIChildWnd::OnCreateClient(lpcs, pContext);
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
        m_HSplitter.SetRowInfo(0, cy0 , cymin);//����tree��ͼ�ĸ߶�
        //m_HSplitter.SetRowInfo(0, 0 , 0);//����tree��ͼ�ĸ߶�
    }
    //m_HSplitter.SetColumnInfo(1,10,10);
    m_HSplitter.RecalcLayout();


}
void CChildFrame::OnSize(UINT nType, int cx, int cy)
{
    CMDIChildWnd::OnSize(nType, cx, cy);

    // TODO: �ڴ˴������Ϣ����������
    if(m_HSplitter.GetSafeHwnd() && m_VSplitter.GetSafeHwnd())
    {
        SetLayout();
    }
}
