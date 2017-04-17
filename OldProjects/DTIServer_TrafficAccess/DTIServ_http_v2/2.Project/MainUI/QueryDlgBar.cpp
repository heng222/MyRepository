// QueryDlgBar.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "QueryDlgBar.h"
#include ".\querydlgbar.h"


// CQueryDlgBar 对话框

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


// CQueryDlgBar 消息处理程序
LRESULT CQueryDlgBar::OnInitDialog ( UINT wParam, LONG lParam)
{
    // <-- with these lines. -->

    LRESULT bRet = HandleInitDialog(wParam, lParam);

    if (!UpdateData(FALSE))
    {
        TRACE0("Warning: UpdateData failed during dialog init.\n");
    }

    SetDlgItemText(IDC_DLGBAR_BTN, _T("按钮(&A)"));

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

    // TODO:  在此添加您专用的创建代码

    return 0;
}

