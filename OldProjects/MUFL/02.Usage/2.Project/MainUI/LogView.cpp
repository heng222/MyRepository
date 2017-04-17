// LogView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "LogView.h"

#include "MainUIDoc.h"
#include <UserColors.h>


// CLogView

IMPLEMENT_DYNCREATE(CLogView, CView)

CLogView::CLogView():m_ctrlList(CSortListCtrl::ECS_INVOKECREATE)
{
}

CLogView::~CLogView()
{
}

BEGIN_MESSAGE_MAP(CLogView, CView)
    ON_WM_CONTEXTMENU()
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_COMMAND(ID_LOG_DELETESEL, OnLogDeletesel)
    ON_COMMAND(ID_LOG_CLEAR, OnLogClear)
END_MESSAGE_MAP()


// CLogView ��ͼ

void CLogView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CLogView ���

#ifdef _DEBUG
void CLogView::AssertValid() const
{
	CView::AssertValid();
}

void CLogView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMainUIDoc* CLogView::GetDocument() const // �ǵ��԰汾��������
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainUIDoc)));
    return (CMainUIDoc*)m_pDocument;
}

#endif //_DEBUG


// CLogView ��Ϣ�������

void CLogView::OnContextMenu(CWnd* pWnd, CPoint point)
{
    if (pWnd->GetSafeHwnd() == m_ctrlList.GetSafeHwnd())
    {
        CMenu menu;
        menu.LoadMenu(IDR_LOG_OPERATION);
        CMenu* pMenu = menu.GetSubMenu(0);
        ASSERT(pMenu != NULL);
        pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
    }
}

void CLogView::OnLogDeletesel()
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

void CLogView::OnLogClear()
{
    m_ctrlList.DeleteAllItems();
}


int CLogView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  �ڴ������ר�õĴ�������
    BOOL bFlag = m_ctrlList.Create(WS_CHILD|WS_VISIBLE|LVS_REPORT,
        CRect(0,0,200,200), this, 100);

    if ( !bFlag )
    {
        return -1;
    }

    //�����еı���
    m_ctrlList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);
    m_ctrlList.SetHeadings( _T("ʱ ��,150;�� ��,100;               ��                     ע,750") );

    return 0;
}

void CLogView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    // TODO: �ڴ˴������Ϣ����������
    if (IsWindow(HWND(m_ctrlList)))
    {
        m_ctrlList.MoveWindow(CRect(0,0,cx,cy));
    }
}

void CLogView::AddLiveLog(PIMsgAppLogs pNewLog)
{
    // ֻ����ϵͳ�¼���ȼ�����ELL_INFORMATION�������¼�(�����¼��������¼���)
    if ( pNewLog->iLogType!=IMsgAppLogs::ELGT_System && 
         pNewLog->iLogLevel<=IMsgAppLogs::ELL_INFORMATION )
    {
        return;
    }


    // Add a new line.
    CString strLogType;
    pNewLog->GetLogType_str(strLogType);
    m_ctrlList.InsertItemA(0,pNewLog->logTime.Format(_T(" %Y-%m-%d %H:%M:%S")),
        _T(" ")+strLogType, _T(" ")+pNewLog->strComments);
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