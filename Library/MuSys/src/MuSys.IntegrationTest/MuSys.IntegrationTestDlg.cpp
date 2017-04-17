
// MuSys.IntegrationTestDlg.cpp : implementation file
//

#include "stdafx.h"

#include "MuSys.h"

#include "MuSys.IntegrationTest.h"
#include "MuSys.IntegrationTestDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMuSysIntegrationTestDlg dialog




CMuSysIntegrationTestDlg::CMuSysIntegrationTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMuSysIntegrationTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMuSysIntegrationTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMuSysIntegrationTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDOK, &CMuSysIntegrationTestDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMuSysIntegrationTestDlg message handlers

BOOL CMuSysIntegrationTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMuSysIntegrationTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMuSysIntegrationTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMuSysIntegrationTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void DateTime_operatorMinus_test()
{
    TDateTime dt1(_T("2011-2-5 12:00:00"));
    TDateTime dt2(_T("2011-2-4 12:00:00"));

    double days = dt2 - dt1;
}

void DateTime_LoadCurrentDateTime_test()
{
    TDateTime dt;
    TString str = dt.ToString();
}

void FileStream_WriteLine_Test()
{
    TString temp;

    // 测试文本读写
    CFileStream fsText;
    fsText.OpenTextFile(_T("Text.txt"));

    fsText.WriteLine();
    temp = TDateTime().ToString();
    fsText.WriteLine(temp);
    fsText.WriteLine(_T("test wstring 世界你好 - Hello World"));
    fsText.WriteLine(("test string 测试string."));

    fsText.Close();

    // 测试二进制读写
    CFileStream fsBinary;
    fsBinary.OpenBinaryFile(_T("binary.dat"));
    BYTE bytes[5] = {1, 2, 3, 4, 5};
    fsBinary.Write(bytes, sizeof(bytes));
    fsBinary.Close();
}

void Directory_GetFiles_Test()
{
    // 测试返回指定目录的文件列表1
    std::list<TString> files;
    CDirectory::GetFiles(_T("C:\\*.png"), files);


    // 测试返回指定目录的文件列表2
    std::list<TString> files1;
    CDirectory::GetFiles(_T("C:\\*.*"), files1);
}

void Directory_CreateDirectory_Test()
{
    // 测试创建文件夹
    CDirectory::CreateDirectory(_T("C:\\111\\222\\"));
}

void Directory_DeleteExpiredFiles_test()
{
    CDirectory::DeleteExpiredFiles(_T("C:\\111\\*.*"), 1);
}




void FileUtility_Delete_Test()
{
    // 测试删除文件
    CFileUtility::Delete(_T("C:\\shadow.png"));

}

void PathUtility_GetDirectoryName()
{
    TString strPathName = CPathUtility::GetDirectoryName(_T("C:\\111\\*.*"));
}

void CUltraString_Format_test()
{
    TDateTime m_logFileCreatedDT;
    TString m_logFilePath;

    // 创建或打开新的日志
    m_logFilePath = CStringUtility::Format(_T("%s\\diag%04d%02d%02d.log"),
        _T("D:\\Diagnostic"),
        m_logFileCreatedDT.Year,
        m_logFileCreatedDT.Month,
        m_logFileCreatedDT.Day);
}


void CMuSysIntegrationTestDlg::OnBnClickedOk()
{
    //DateTime_LoadCurrentDateTime_test();
    //DateTime_operatorMinus_test();

    FileStream_WriteLine_Test();

    //Directory_GetFiles_Test();

    //Directory_CreateDirectory_Test();

    //FileUtility_Delete_Test();
    
    //PathUtility_GetDirectoryName();
    
    //Directory_DeleteExpiredFiles_test();

    //CUltraString_Format_test();
}
