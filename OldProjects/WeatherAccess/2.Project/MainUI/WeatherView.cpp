// WeatherView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "WeatherView.h"
#include ".\weatherview.h"


// CWeatherView

IMPLEMENT_DYNCREATE(CWeatherView, CView)

CWeatherView::CWeatherView()
{
}

CWeatherView::~CWeatherView()
{
}

BEGIN_MESSAGE_MAP(CWeatherView, CView)
    ON_WM_SIZE()
END_MESSAGE_MAP()


// CWeatherView ��ͼ

void CWeatherView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CWeatherView ���

#ifdef _DEBUG
void CWeatherView::AssertValid() const
{
	CView::AssertValid();
}

void CWeatherView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG


// CWeatherView ��Ϣ�������

void CWeatherView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    // TODO: �ڴ˴������Ϣ����������
    CWnd* pChildWnd = GetTopWindow();
    if (pChildWnd)
    {
        pChildWnd->MoveWindow(0,0,cx,cy);
    }
}
