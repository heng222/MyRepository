// PicTravelView.cpp : CPicTravelView 类的实现
//

#include "stdafx.h"
#include "PicTravel.h"

#include "PicTravelDoc.h"
#include "PicTravelView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CLKBKG RGB(192, 192, 192)
#define INTERVAL 5

// CPicTravelView

IMPLEMENT_DYNCREATE(CPicTravelView, CView)

BEGIN_MESSAGE_MAP(CPicTravelView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_WM_LBUTTONDOWN()
    ON_WM_TIMER()
    ON_WM_SIZE()
END_MESSAGE_MAP()

// CPicTravelView 构造/析构

CPicTravelView::CPicTravelView()
{
	// TODO: 在此处添加构造代码
}

CPicTravelView::~CPicTravelView()
{
    m_dcPic.DeleteDC();
    m_dcCache.DeleteDC();
    m_bmpCache.DeleteObject();
}

BOOL CPicTravelView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}


void CPicTravelView::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    // TODO: 在此添加专用代码和/或调用基类
    try
    {
        m_bmpPic.LoadBitmap(IDB_BITMAP_DEMO);
        m_bmpPic.GetBitmap(&m_bmp);

        m_xIncrease = true;
        m_yIncrease = true;        
        m_xPos = 0;
        m_yPos = 0;

        this->SetTimer(1, INTERVAL, NULL);
    }
    catch (...)
    {
        MessageBox(_T("Error"), _T("Error"), MB_OK);
    }
}

// 更新图片的输出坐标
void CPicTravelView::UpdatePosition()
{
    CRect rectClient;
    GetClientRect(&rectClient);

    int minX = rectClient.left;
    int maxX = rectClient.right;
    int minY = rectClient.top;
    int maxY = rectClient.bottom;

    // 
    if (m_xIncrease)
    {
        if (m_xPos + m_bmp.bmWidth > maxX)
        {
            m_xPos = maxX - m_bmp.bmWidth;
            m_xIncrease = false;
        }
        else
        {
            m_xPos++;
        }
    }
    else
    {
        if (m_xPos < minX) 
        {
            m_xPos = minX;
            m_xIncrease = true;
        }
        else
        {
            m_xPos--;
        }

    }

    // 
    if (m_yIncrease)
    {
        if (m_yPos+m_bmp.bmHeight > maxY)
        {
            m_yPos = maxY - m_bmp.bmHeight;
            m_yIncrease = false;
        }
        else
        {
            m_yPos++;
        }
    } 
    else
    {
        if (m_yPos < minY)
        {
            m_yPos = minY;
            m_yIncrease = true;
        }
        else
        {
            m_yPos--;
        }
    }

}

void CPicTravelView::OnTimer(UINT_PTR nIDEvent)
{
    UpdatePosition();

    // 
    CClientDC dc(this);
    CRect rectClient;
    GetClientRect(&rectClient);

    m_dcCache.FillSolidRect(0, 0, rectClient.Width(), rectClient.Height(), CLKBKG);
    m_dcCache.BitBlt( m_xPos, m_yPos, m_bmp.bmWidth, m_bmp.bmHeight, &m_dcPic, 0, 0, SRCCOPY); 
    dc.BitBlt( 0, 0, rectClient.Width(), rectClient.Height(), &m_dcCache, 0, 0, SRCCOPY); 


    // TODO: 在此添加消息处理程序代码和/或调用默认值
    CView::OnTimer(nIDEvent);
}
// CPicTravelView 绘制

void CPicTravelView::OnDraw(CDC* pDC)
{
	CPicTravelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CPicTravelView 打印

BOOL CPicTravelView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPicTravelView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPicTravelView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清除过程
}


// CPicTravelView 诊断

#ifdef _DEBUG
void CPicTravelView::AssertValid() const
{
	CView::AssertValid();
}

void CPicTravelView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPicTravelDoc* CPicTravelView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPicTravelDoc)));
	return (CPicTravelDoc*)m_pDocument;
}
#endif //_DEBUG


// CPicTravelView 消息处理程序

void CPicTravelView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    CView::OnLButtonDown(nFlags, point);
}



void CPicTravelView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    // 
    CClientDC dc(this);
    CRect rectClient;
    GetClientRect(&rectClient);

    // 
    m_dcPic.DeleteDC();
    m_dcPic.CreateCompatibleDC(&dc);
    m_dcPic.SelectObject(m_bmpPic);


    // 
    m_dcCache.DeleteDC();
    m_dcCache.CreateCompatibleDC(&dc);
    m_bmpCache.DeleteObject();
    m_bmpCache.CreateCompatibleBitmap(&dc, rectClient.Width(), rectClient.Height());
    m_dcCache.SelectObject(&m_bmpCache);
}
