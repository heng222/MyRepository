// MainView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NaviServer.h"
#include "MainView.h"
#include ".\mainview.h"


// CMainView

IMPLEMENT_DYNCREATE(CMainView, CView)

CMainView::CMainView(): m_mainSheet(_T("MainSheet"))
{
}

CMainView::~CMainView()
{
}

BEGIN_MESSAGE_MAP(CMainView, CView)
    ON_WM_CREATE()
    ON_WM_SIZE()
END_MESSAGE_MAP()


// CMainView ��ͼ

void CMainView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CMainView ���

#ifdef _DEBUG
void CMainView::AssertValid() const
{
	CView::AssertValid();
}

void CMainView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG


// CMainView ��Ϣ�������

void CMainView::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    // TODO: �ڴ����ר�ô����/����û���
    m_mainSheet.ShowWindow(SW_MAXIMIZE);
}

int CMainView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  �ڴ������ר�õĴ�������
    if( !m_mainSheet.Create(this, WS_BORDER|WS_CHILD|WS_VISIBLE, 0)) 
        return -1;

    return 0;
}

void CMainView::OnSize(UINT nType, int cx, int cy)
{   
    CView::OnSize(nType, cx, cy);

    // Resize the sheet
    CWnd *psheet = GetWindow(GW_CHILD);//m_mainSheet��resultview��Ψһ�����Ӵ���
    if(psheet != NULL)
    {
        /*CRect rect;
        GetWindowRect(&rect);*/
        //psheet->ScreenToClient(&rect);
        psheet->SetWindowPos(NULL, 0, 0, cx,cy,/*rect.Width() , rect.Height() ,*/
            SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);

        // Resize the tab
        CWnd *ptab = m_mainSheet.GetTabControl();
        if(ptab != NULL)
        {
            ptab->SetWindowPos(NULL, 0, 0,cx,cy, /*rect.Width(), rect.Height(),*/
                SWP_NOZORDER /*| SWP_NOACTIVATE*/);

            // ��PropertySheet�Զ�����page�Ĵ�С
            m_mainSheet.SetActivePage(m_mainSheet.GetActiveIndex());
        }
    }
}


//////////////////////////////////////////////////////////////////////////
// 
void CMainView::AddNewLogs(PIMsgAppLogs pNewLog)
{
    if (pNewLog->iLogType==IMsgNetLog::ELGT_Network)
    {
        m_mainSheet.AddNetLog((PIMsgNetLog)pNewLog);

    }
}
int CMainView::GetPageCount() const
{
    return m_mainSheet.GetPageCount();
}
void CMainView::ActivePage(CMainSheet::TPageName nPagename)
{
    m_mainSheet.ActivePage(nPagename);
}
void CMainView::ActivePage(int iIdx)
{
    m_mainSheet.SetActivePage(iIdx);
}
void CMainView::SetActivedFldID(int aProType,DWORD dwID)
{
    m_mainSheet.SetActivedFldID(aProType,dwID);
}

