//

#include "stdafx.h"
#include "MainUI.h"
#include "RawTfcView.h"


// RawTfcView

IMPLEMENT_DYNCREATE(CRawTfcView, CView)

CRawTfcView::CRawTfcView()
{
}

CRawTfcView::~CRawTfcView()
{
}

BEGIN_MESSAGE_MAP(CRawTfcView, CView)
    ON_WM_CREATE()
    ON_WM_SIZE()
END_MESSAGE_MAP()


// RawTfcView ��ͼ

void CRawTfcView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// RawTfcView ���

#ifdef _DEBUG
void CRawTfcView::AssertValid() const
{
	CView::AssertValid();
}

void CRawTfcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG


// RawTfcView ��Ϣ�������

int CRawTfcView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  �ڴ������ר�õĴ�������

    return 0;
}

void CRawTfcView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    // TODO: �ڴ˴������Ϣ����������
    CWnd* pChildWnd = GetTopWindow();
    if (pChildWnd)
    {
        pChildWnd->MoveWindow(0,0,cx,cy);
    }
}
