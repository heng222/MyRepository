// ParsedTfcView.cpp : 实现文件
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


// CParsedTfcView 绘图

void CParsedTfcView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CParsedTfcView 诊断

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


// CParsedTfcView 消息处理程序

int CParsedTfcView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  在此添加您专用的创建代码

    return 0;
}

void CParsedTfcView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码
    CWnd* pChildWnd = GetTopWindow();
    if (pChildWnd)
    {
        pChildWnd->MoveWindow(0,0,cx,cy);
    }
}
