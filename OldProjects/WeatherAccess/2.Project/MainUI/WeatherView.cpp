// WeatherView.cpp : 实现文件
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


// CWeatherView 绘图

void CWeatherView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CWeatherView 诊断

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


// CWeatherView 消息处理程序

void CWeatherView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码
    CWnd* pChildWnd = GetTopWindow();
    if (pChildWnd)
    {
        pChildWnd->MoveWindow(0,0,cx,cy);
    }
}
