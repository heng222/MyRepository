// MainUIView.cpp : CMainUIView ���ʵ��
//

#include "stdafx.h"
#include "MainUI.h"
#include <UserColors.h>
#include "MainUIDoc.h"
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
    ON_WM_CONTEXTMENU()
    ON_COMMAND(ID_LOG_DELETESEL, OnLogDeletesel)
    ON_COMMAND(ID_LOG_CLEAR, OnLogClear)
END_MESSAGE_MAP()

// CMainUIView ����/����

CMainUIView::CMainUIView():m_ctrlList(CSortListCtrl::ECS_INVOKECREATE)
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
    BOOL bFlag = m_ctrlList.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_REPORT,
        CRect(0,0,200,200), this, 1);

    if ( !bFlag )
    {
        return -1;
    }

    //�����еı���
    m_ctrlList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);
    m_ctrlList.SetHeadings( _T("ʱ ��,150;�� ��,100;               ��                     ע,750") );


    //
    //m_LogMenu.LoadMenu(IDR_MENU_LOG);

    return 0;
}

void CMainUIView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    // TODO: �ڴ˴������Ϣ����������

    if (IsWindow(HWND(m_ctrlList)))
    {
        m_ctrlList.MoveWindow(CRect(0,0,cx,cy));
    }
}


void CMainUIView::AddLiveLog(PIMsgAppLogs pNewLog)
{
    // ������ȼ�ΪELL_INFORMATION�������¼�
    if (pNewLog->iLogType!=IMsgAppLogs::ELGT_System && pNewLog->iLogLevel<=IMsgAppLogs::ELL_INFORMATION)
    {
        return;
    }

    // Insert a new line.
    CString strLogType;
    pNewLog->GetLogType_str(strLogType);
    m_ctrlList.InsertItemA(0,pNewLog->logTime.Format(" %Y-%m-%d %H:%M:%S"),
        " "+strLogType, " "+pNewLog->strComments);
    int iClrItem = 0;

    // set color
    COLORREF crText = ::GetSysColor(COLOR_WINDOWTEXT);
    COLORREF crBkgnd = ::GetSysColor(COLOR_WINDOW);

    if (pNewLog->iLogLevel==IMsgAppLogs::ELL_ERROR)
    {
        crText = CLR_BLACK;
        crBkgnd = CLR_RED;
        int iColum = m_ctrlList.GetColumns();
        for (int i=0; i<iColum; i++)
        {
            m_ctrlList.SetItemColor(iClrItem,i,crText,crBkgnd);
        }
    }
    else if (pNewLog->iLogLevel==IMsgAppLogs::ELL_WARNING)
    {
        crText = CLR_BLACK;
        crBkgnd = CLR_YELLOW;
        int iColum = m_ctrlList.GetColumns();
        for (int i=0; i<iColum; i++)
        {
            m_ctrlList.SetItemColor(iClrItem,i,crText,crBkgnd);
        }
    }
    else
    {
        // Set text colors
        switch(pNewLog->iLogType)
        {
        case IMsgAppLogs::ELGT_System:
            {
                crText = CLR_DARKBLUE;
                crBkgnd = CLR_BKG_1;
            }
            break;

        default:
            {
                crText = CLR_DARKGREEN;
                crBkgnd = CLR_BKG_2;
            }

        }
        m_ctrlList.SetItemColor(iClrItem,1,crText,crBkgnd);
    }

    //
    if (m_ctrlList.GetItemCount()>100)
    {
        m_ctrlList.DeleteAllItems();
    }
}

void CMainUIView::OnContextMenu(CWnd* pWnd, CPoint point)
{
    if (pWnd->GetSafeHwnd() == m_ctrlList.GetSafeHwnd())
    {
        CMenu menu;
        menu.LoadMenu(IDR_MENU_LOG);
        CMenu* pMenu = menu.GetSubMenu(0);
        ASSERT(pMenu != NULL);
        pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
    }
}

void CMainUIView::OnLogDeletesel()
{
    int iCount = m_ctrlList.GetSelectedCount();
    POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
    int nItem = m_ctrlList.GetNextSelectedItem(pos)+iCount-1;
    for (int i=0; i<iCount; i++)
    {
        m_ctrlList.DeleteItem(nItem);
        nItem --;
    }
}

void CMainUIView::OnLogClear()
{
    m_ctrlList.DeleteAllItems();
}
