// PicTravelView.cpp : CPicTravelView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_WM_LBUTTONDOWN()
    ON_WM_TIMER()
    ON_WM_SIZE()
END_MESSAGE_MAP()

// CPicTravelView ����/����

CPicTravelView::CPicTravelView()
{
	// TODO: �ڴ˴���ӹ������
}

CPicTravelView::~CPicTravelView()
{
    m_dcPic.DeleteDC();
    m_dcCache.DeleteDC();
    m_bmpCache.DeleteObject();
}

BOOL CPicTravelView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}


void CPicTravelView::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    // TODO: �ڴ����ר�ô����/����û���
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

// ����ͼƬ���������
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


    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    CView::OnTimer(nIDEvent);
}
// CPicTravelView ����

void CPicTravelView::OnDraw(CDC* pDC)
{
	CPicTravelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CPicTravelView ��ӡ

BOOL CPicTravelView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPicTravelView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPicTravelView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CPicTravelView ���

#ifdef _DEBUG
void CPicTravelView::AssertValid() const
{
	CView::AssertValid();
}

void CPicTravelView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPicTravelDoc* CPicTravelView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPicTravelDoc)));
	return (CPicTravelDoc*)m_pDocument;
}
#endif //_DEBUG


// CPicTravelView ��Ϣ�������

void CPicTravelView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
