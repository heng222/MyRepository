// ParsedTfcView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "ParsedTfcView.h"
#include ".\parsedtfcview.h"


// CParsedTfcView

IMPLEMENT_DYNCREATE(CParsedTfcView, CView)

CParsedTfcView::CParsedTfcView()
{
}

CParsedTfcView::~CParsedTfcView()
{
}

BEGIN_MESSAGE_MAP(CParsedTfcView, CView)
    ON_WM_CREATE()
    ON_WM_SIZE()
END_MESSAGE_MAP()


// CParsedTfcView ��ͼ

void CParsedTfcView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CParsedTfcView ���

#ifdef _DEBUG
void CParsedTfcView::AssertValid() const
{
	CView::AssertValid();
}

void CParsedTfcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG


// CParsedTfcView ��Ϣ�������

int CParsedTfcView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  �ڴ������ר�õĴ�������

    return 0;
}

void CParsedTfcView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    // TODO: �ڴ˴������Ϣ����������
    CWnd* pChildWnd = GetTopWindow();
    if (pChildWnd)
    {
        pChildWnd->MoveWindow(0,0,cx,cy);
    }
}
