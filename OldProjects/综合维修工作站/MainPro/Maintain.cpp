// Maintain.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Maintain.h"
#include "AppStartDlg.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "MaintainDoc.h"
#include "MaintainView.h"
#include "MultStaView.h"
#include "ChildMulFrame.h"
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

	m_bMove=FALSE;

}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMaintainApp object

CMaintainApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMaintainApp initialization

BOOL CMaintainApp::InitInstance()
{
	BeginWaitCursor();

	//检查程序是否已有一个实例启动
	if ( IsOneInstance() )
	{
		::MessageBox(NULL,"程序的一个实例已处于运行状态!","警告",MB_ICONEXCLAMATION);
		return FALSE;
	}
	
	//
	AfxEnableControlContainer();
	CoInitialize(NULL);
	AfxInitRichEdit();
	
	//
	CAppStartDlg	dlgAppStart;
	dlgAppStart.Create(CAppStartDlg::IDD,NULL);
	dlgAppStart.ShowWindow(SW_SHOW);
	dlgAppStart.SetInformation("程序开始启动...");

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
	SetRegistryKey(_T("FZJ-CTC型综合维修工作站"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	//////////////


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	
	//单站模板
	m_pSingleStaDocTemplate = new CMultiDocTemplate(
		IDR_MAINTATYPE,
		RUNTIME_CLASS(CMaintainDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CMaintainView));
	AddDocTemplate(m_pSingleStaDocTemplate);

	//多站模板
	m_pMultiStatDocTemplate = new CMultiDocTemplate(
		IDR_MAINTATYPE,
		RUNTIME_CLASS(CMaintainDoc),
		RUNTIME_CLASS(CChildMulFrame), // custom MDI child frame
		RUNTIME_CLASS(CMultStaView));
	AddDocTemplate(m_pMultiStatDocTemplate);

	
	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	//
	
	dlgAppStart.SetInformation("正在读取站场信息，请稍候...");
	if(!initStatus())
		return FALSE;

	//
	m_pSingleStaDocTemplate->OpenDocumentFile(NULL);
	//m_pMultiStatDocTemplate->OpenDocumentFile(NULL);

	// Parse command line for standard shell commands, DDE, file open
/*	
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
*/

	
	//创建特定的对话框
	pMainFrame->CreateSpeDialog();

/*		
	dlgAppStart.SetInformation("连接到数据库服务器...");
	//连接到数据库服务器
	if (pMainFrame->ConnectToDBServer() == FALSE)
	{
		dlgAppStart.ShowWindow(SW_HIDE);
		int iResultID = pMainFrame->MessageBox("连接到数据库服务器失败，你可能无法进行关数据库的操作，但程序可以继续启动,若连接应用服务器成功，可以进行行车信息的实时监视。是否继续启动？","错误提示",MB_ICONINFORMATION | MB_YESNO );
		if ( iResultID == IDNO )
		{
			return FALSE;
		}
	}
	
	//连接到应用服务器并请求全场帧
	dlgAppStart.ShowWindow(SW_SHOW);
	dlgAppStart.SetInformation("连接到应用服务器...");
	BOOL bFlag = pMainFrame->ConnectToALServer();
	if ( bFlag == FALSE )
	{
		dlgAppStart.ShowWindow(SW_HIDE);
		int iResultID = pMainFrame->MessageBox("连接到应用服务器失败，你可能无法进行行车信息的实时监视，但程序可以继续启动,是否继续启动？","错误提示",MB_ICONEXCLAMATION | MB_YESNO );
		if ( iResultID == IDNO ){
			return FALSE;
		}
		else{
			pMainFrame->SetConnection(bFlag);
		}
	}
	else{//发送全场请求帧与车次框请求帧
		((CMainFrame*)(theApp.m_pMainWnd))->RequireStationStatus();
	}
//*/	
	
	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	pMainFrame->SetWindowText("FZJ-CTC型综合维修工作站");
	EndWaitCursor();
	dlgAppStart.DestroyWindow();
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
	char cTemp[MAX_PATH];

	//确定系统当前路径
	GetCurrentDirectory(MAX_PATH,cTemp);
	m_strExePath.Format("%s\\",cTemp);


	//数据库参数
	GetPrivateProfileString("Database","DataSource",0,cTemp,MAX_PATH,m_strExePath+STATIONINFOPATHNAME);
	m_strDBDataSource = cTemp;
	GetPrivateProfileString("Database","UserID",0,cTemp,MAX_PATH,m_strExePath+STATIONINFOPATHNAME);
	m_strDBUserID = cTemp;
	GetPrivateProfileString("Database","Password",0,cTemp,MAX_PATH,m_strExePath+STATIONINFOPATHNAME);
	m_strDBPassword = cTemp;

	/*/用户登录校验
	CLoginDialog dlg;
	if(dlg.DoModal() != IDOK)
	{
		return FALSE;
	}
	//*/

	//读站场信息
	m_ZCTMag.ReadStationInf(CZCTMag::MODE_KONGZHI);
	
	return TRUE;
}


int CMaintainApp::ExitInstance() 
{
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

	POSITION pos_Template,pos_Doc,pos_View;
	
	pos_Template = GetFirstDocTemplatePosition();
	while ( pos_Template ) 
	{
		CDocTemplate *pDocTemplate = GetNextDocTemplate(pos_Template);

		//
		pos_Doc = pDocTemplate->GetFirstDocPosition();
		while ( pos_Doc ) 
		{
			CDocument* pDoc = pDocTemplate->GetNextDoc(pos_Doc);

			//
			pos_View = pDoc->GetFirstViewPosition();
			while (pos_View) 
			{
				CView* pView = pDoc->GetNextView(pos_View);
				if(pView->IsKindOf(pViewClass)) 
				{
					return pView;
				}
			}

		}
	}

	return NULL;
}


BOOL CMaintainApp::IsOneInstance()
{
	HANDLE hMutexOneInstantance=CreateMutex(NULL,FALSE,_T("FZJ-CTC型综合维修工作站"));
	return ( GetLastError()==ERROR_ALREADY_EXISTS );
}
