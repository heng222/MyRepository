// QueryDlgBar.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "QueryDlgBar.h"
#include ".\querydlgbar.h"


// CQueryDlgBar �Ի���

IMPLEMENT_DYNAMIC(CQueryDlgBar, CDialogBar)
CQueryDlgBar::CQueryDlgBar()
{
}

CQueryDlgBar::~CQueryDlgBar()
{
}

void CQueryDlgBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CQueryDlgBar, CDialogBar)
    ON_WM_CREATE()
    ON_MESSAGE(WM_INITDIALOG, OnInitDialog )    // <-- Add this line.
END_MESSAGE_MAP()


// CQueryDlgBar ��Ϣ�������
LRESULT CQueryDlgBar::OnInitDialog ( UINT wParam, LONG lParam)
{
    // <-- with these lines. -->

    LRESULT bRet = HandleInitDialog(wParam, lParam);

    if (!UpdateData(FALSE))
    {
        TRACE0("Warning: UpdateData failed during dialog init.\n");
    }

    SetDlgItemText(IDC_DLGBAR_BTN, _T("��ť(&A)"));

    return bRet;
}

BOOL CQueryDlgBar::CreateSelf(CWnd* pParentWnd,UINT nStyle)
{
    //return CDialogBar::Create(pParentWnd, nIDTemplate,nStyle,nID);
    return CDialogBar::Create(pParentWnd, IDD,nStyle,1);
}

//
int CQueryDlgBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDialogBar::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  �ڴ������ר�õĴ�������

    return 0;
}

