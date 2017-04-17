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


// RawTfcView 绘图

void CRawTfcView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// RawTfcView 诊断

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


// RawTfcView 消息处理程序

int CRawTfcView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  在此添加您专用的创建代码

    return 0;
}

void CRawTfcView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码
    CWnd* pChildWnd = GetTopWindow();
    if (pChildWnd)
    {
        pChildWnd->MoveWindow(0,0,cx,cy);
    }
}
