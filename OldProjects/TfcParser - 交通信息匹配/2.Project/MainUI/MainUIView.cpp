// MainUIView.cpp : CMainUIView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
    ON_WM_CREATE()
    ON_WM_SIZE()
END_MESSAGE_MAP()

// CMainUIView ����/����

CMainUIView::CMainUIView()
{
	// TODO: �ڴ˴���ӹ������

}

CMainUIView::~CMainUIView()
{
}

BOOL CMainUIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	return CView::PreCreateWindow(cs);
}

// CMainUIView ����

void CMainUIView::OnDraw(CDC* /*pDC*/)
{
	CMainUIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMainUIView ��ӡ

BOOL CMainUIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMainUIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡǰ��Ӷ���ĳ�ʼ��
}

void CMainUIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡ������������
}


// CMainUIView ���

#ifdef _DEBUG
void CMainUIView::AssertValid() const
{
	CView::AssertValid();
}

void CMainUIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMainUIDoc* CMainUIView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainUIDoc)));
	return (CMainUIDoc*)m_pDocument;
}
#endif //_DEBUG


// CMainUIView ��Ϣ�������

void CMainUIView::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    // TODO: �ڴ����ר�ô����/����û���
}

int CMainUIView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  �ڴ������ר�õĴ�������

    return 0;
}

void CMainUIView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    // TODO: �ڴ˴������Ϣ����������
    CWnd* pChildWnd = GetTopWindow();
    if (pChildWnd)
    {
        pChildWnd->MoveWindow(0,0,cx,cy);
    }
}
