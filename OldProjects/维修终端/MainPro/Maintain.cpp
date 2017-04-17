// Maintain.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Maintain.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "MaintainDoc.h"
#include "MaintainView.h"
#include "LoginDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaintainApp

BEGIN_MESSAGE_MAP(CMaintainApp, CWinApp)
	//{{AFX_MSG_MAP(CMaintainApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaintainApp construction

CMaintainApp::CMaintainApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMaintainApp object

CMaintainApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMaintainApp initialization

BOOL CMaintainApp::InitInstance()
{
	//检查程序是否已有一个实例启动
	if ( IsOneInstance() )
	{
		::MessageBox(NULL,"程序的一个实例已处于运行状态! 程序启动失败!","警告",MB_ICONEXCLAMATION);
		return FALSE;
	}

	//
	WSADATA		WSAData = { 0 };
	if ( 0 != WSAStartup( WSA_VERSION, &WSAData ) )
	{
		// Tell the user that we could not find a usable
		// WinSock DLL.
		if ( LOBYTE( WSAData.wVersion ) != LOBYTE(WSA_VERSION) ||
			 HIBYTE( WSAData.wVersion ) != HIBYTE(WSA_VERSION) )
			 ::MessageBox(NULL, _T("Incorrect version of WS2_32.dll found"), _T("Error"), MB_OK);

		WSACleanup( );
		return FALSE;
	}
	AfxEnableControlContainer();
	AfxInitRichEdit();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("FJZ-型维修终端"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	if(!initStatus())
	{
		return FALSE;
	}

	m_pDocTemplate = new CMultiDocTemplate(
		IDR_MAINTATYPE,
		RUNTIME_CLASS(CMaintainDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CMaintainView));
	AddDocTemplate(m_pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	pMainFrame->SetWindowText("FZJ-CTC型维修终端");
	
	//创建消息提示框
	pMainFrame->m_pInfPromptDlg = new CInfPromptDlg;
	pMainFrame->m_pInfPromptDlg->Create(CInfPromptDlg::IDD, pMainFrame);

	//发送全场请求帧
	pMainFrame->RequireStationStatus();
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CMaintainApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMaintainApp message handlers


BOOL CMaintainApp::initStatus()
{
	
	//确定系统当前路径
	char cArray[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,cArray);
	m_strExePath.Format("%s\\",cArray);

	//上次打开的站场
	CReadStationInf* pStationInf = CReadStationInf::GetInstance();
//	m_iCurStationNo = GetPrivateProfileInt("System","CurStationID",-1,m_strExePath+STATIONINFOPATHNAME);
	//if ( m_iCurStationNo > pStationInf->GetLength() || m_iCurStationNo < 0 )
	{
		//return FALSE;
	}

	/*/用户登录校验
	CLoginDialog dlg;
	if(dlg.DoModal() != IDOK)
	{
		return FALSE;
	}
	/*/

	return TRUE;
}

int CMaintainApp::ExitInstance() 
{
	CReadStationInf::ReleaseInstance();

	// TODO: Add your specialized code here and/or call the base class
	CoUninitialize();
	return CWinApp::ExitInstance();
}

/*========================================================================
	Name:		获取视图类指针
	----------------------------------------------------------
	Params:		pViewClass 视类型
    ----------------------------------------------------------
	Remarks:	
==========================================================================*/
CView* CMaintainApp::GetView(CRuntimeClass *pViewClass)
{
	CMaintainDoc* pDoc;

	POSITION pos;
	
	pos = m_pDocTemplate->GetFirstDocPosition();
	if (pos == NULL)
	{
		return NULL;
	}
	else 
	{
		pDoc = (CMaintainDoc*)m_pDocTemplate->GetNextDoc(pos);
		if(pDoc==NULL) 
			return NULL;
		pos = pDoc->GetFirstViewPosition();
		CView* pView;
		while(pos != NULL)
		{
			pView=pDoc->GetNextView(pos);
			if(pView->IsKindOf(pViewClass)) 
			{
				return pView;
			}
		}
	}

	return NULL;
}

BOOL CMaintainApp::IsOneInstance()
{
	BOOL bFound = FALSE;
	HANDLE hMutexOneInstantance=CreateMutex(NULL,TRUE,_T("PreventSecondInstance"));
	if( GetLastError() == ERROR_ALREADY_EXISTS )
	{
		bFound=TRUE;
	}
	if( hMutexOneInstantance )
	{
		ReleaseMutex(hMutexOneInstantance);
	}
	
	return bFound;
}
