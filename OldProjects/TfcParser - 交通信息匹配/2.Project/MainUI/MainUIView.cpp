// MainUIView.cpp : CMainUIView 类的实现
//

#include "stdafx.h"
#include "MainUI.h"

#include "MainUIDoc.h"
#include "MainUIView.h"
#include ".\mainuiview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainUIView

IMPLEMENT_DYNCREATE(CMainUIView, CView)

BEGIN_MESSAGE_MAP(CMainUIView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
    ON_WM_CREATE()
    ON_WM_SIZE()
END_MESSAGE_MAP()

// CMainUIView 构造/析构

CMainUIView::CMainUIView()
{
	// TODO: 在此处添加构造代码

}

CMainUIView::~CMainUIView()
{
}

BOOL CMainUIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return CView::PreCreateWindow(cs);
}

// CMainUIView 绘制

void CMainUIView::OnDraw(CDC* /*pDC*/)
{
	CMainUIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMainUIView 打印

BOOL CMainUIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMainUIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印前添加额外的初始化
}

void CMainUIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印后添加清除过程
}


// CMainUIView 诊断

#ifdef _DEBUG
void CMainUIView::AssertValid() const
{
	CView::AssertValid();
}

void CMainUIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMainUIDoc* CMainUIView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainUIDoc)));
	return (CMainUIDoc*)m_pDocument;
}
#endif //_DEBUG


// CMainUIView 消息处理程序

void CMainUIView::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    // TODO: 在此添加专用代码和/或调用基类
}

int CMainUIView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  在此添加您专用的创建代码

    return 0;
}

void CMainUIView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码
    CWnd* pChildWnd = GetTopWindow();
    if (pChildWnd)
    {
        pChildWnd->MoveWindow(0,0,cx,cy);
    }
}
