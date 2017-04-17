// RandomDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Random.h"
#include "RandomDlg.h"
#include ".\randomdlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRandomDlg 对话框



CRandomDlg::CRandomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRandomDlg::IDD, pParent)
    , m_iMaxNum(30)
    , m_strResult(_T(""))
    , m_wNumber(7)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRandomDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_MAXNUM, m_iMaxNum);
    DDX_Text(pDX, IDC_EDIT_RESULT, m_strResult);
    DDX_Text(pDX, IDC_EDIT_NUMBER, m_wNumber);
	DDV_MinMaxShort(pDX, m_wNumber, 1, 50);
}

BEGIN_MESSAGE_MAP(CRandomDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(ID_GENERATE, OnBnClickedGenerate)
    ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CRandomDlg 消息处理程序

BOOL CRandomDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRandomDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CRandomDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRandomDlg::OnBnClickedGenerate()
{
    /*double longi = 2334.1234;
    int degree = int(longi) - int(longi)%100;
    double minute = longi - degree;*/


    UpdateData();
    if (m_wNumber>100)
    {
        m_wNumber = 10;
    }

    m_strResult = _T("");
    //srand( (unsigned)time( NULL ) );

    CWordArray wordArray;
    wordArray.SetSize(10);
    WORD temp;
    for (int ii=0; ii<m_wNumber && ii<m_iMaxNum; ii++)
    {
        srand( GetTickCount() );

        temp = (WORD)((rand()%m_iMaxNum)+1);

        if (!IsExist(wordArray,temp))
        {
            wordArray.Add(temp);
            char cResult[10];
            itoa(temp,cResult,10);
            m_strResult = m_strResult+ CString(cResult) + _T(" ");
        }
        else
        {
            ii--;
            continue;
        }
    }


    UpdateData(FALSE);

}

BOOL CRandomDlg::IsExist(const CWordArray& aWordArray,WORD aNewNum)
{
    INT_PTR number = aWordArray.GetCount();
    for (INT_PTR ii=0; ii<number; ii++)
    {
        if (aNewNum==aWordArray[ii])
        {
            return TRUE;
        }
    }
    return FALSE;
}
void CRandomDlg::OnBnClickedCancel()
{
    // TODO: 在此添加控件通知处理程序代码
    OnCancel();
}
