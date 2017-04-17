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

	//�������Ƿ�����һ��ʵ������
	if ( IsOneInstance() )
	{
		::MessageBox(NULL,"�����һ��ʵ���Ѵ�������״̬!","����",MB_ICONEXCLAMATION);
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
	dlgAppStart.SetInformation("����ʼ����...");

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
	SetRegistryKey(_T("FZJ-CTC���ۺ�ά�޹���վ"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	//////////////


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	
	//��վģ��
	m_pSingleStaDocTemplate = new CMultiDocTemplate(
		IDR_MAINTATYPE,
		RUNTIME_CLASS(CMaintainDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CMaintainView));
	AddDocTemplate(m_pSingleStaDocTemplate);

	//��վģ��
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
	
	dlgAppStart.SetInformation("���ڶ�ȡվ����Ϣ�����Ժ�...");
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

	
	//�����ض��ĶԻ���
	pMainFrame->CreateSpeDialog();

/*		
	dlgAppStart.SetInformation("���ӵ����ݿ������...");
	//���ӵ����ݿ������
	if (pMainFrame->ConnectToDBServer() == FALSE)
	{
		dlgAppStart.ShowWindow(SW_HIDE);
		int iResultID = pMainFrame->MessageBox("���ӵ����ݿ������ʧ�ܣ�������޷����й����ݿ�Ĳ�������������Լ�������,������Ӧ�÷������ɹ������Խ����г���Ϣ��ʵʱ���ӡ��Ƿ����������","������ʾ",MB_ICONINFORMATION | MB_YESNO );
		if ( iResultID == IDNO )
		{
			return FALSE;
		}
	}
	
	//���ӵ�Ӧ�÷�����������ȫ��֡
	dlgAppStart.ShowWindow(SW_SHOW);
	dlgAppStart.SetInformation("���ӵ�Ӧ�÷�����...");
	BOOL bFlag = pMainFrame->ConnectToALServer();
	if ( bFlag == FALSE )
	{
		dlgAppStart.ShowWindow(SW_HIDE);
		int iResultID = pMainFrame->MessageBox("���ӵ�Ӧ�÷�����ʧ�ܣ�������޷������г���Ϣ��ʵʱ���ӣ���������Լ�������,�Ƿ����������","������ʾ",MB_ICONEXCLAMATION | MB_YESNO );
		if ( iResultID == IDNO ){
			return FALSE;
		}
		else{
			pMainFrame->SetConnection(bFlag);
		}
	}
	else{//����ȫ������֡�복�ο�����֡
		((CMainFrame*)(theApp.m_pMainWnd))->RequireStationStatus();
	}
//*/	
	
	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	pMainFrame->SetWindowText("FZJ-CTC���ۺ�ά�޹���վ");
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

	//ȷ��ϵͳ��ǰ·��
	GetCurrentDirectory(MAX_PATH,cTemp);
	m_strExePath.Format("%s\\",cTemp);


	//���ݿ����
	GetPrivateProfileString("Database","DataSource",0,cTemp,MAX_PATH,m_strExePath+STATIONINFOPATHNAME);
	m_strDBDataSource = cTemp;
	GetPrivateProfileString("Database","UserID",0,cTemp,MAX_PATH,m_strExePath+STATIONINFOPATHNAME);
	m_strDBUserID = cTemp;
	GetPrivateProfileString("Database","Password",0,cTemp,MAX_PATH,m_strExePath+STATIONINFOPATHNAME);
	m_strDBPassword = cTemp;

	/*/�û���¼У��
	CLoginDialog dlg;
	if(dlg.DoModal() != IDOK)
	{
		return FALSE;
	}
	//*/

	//��վ����Ϣ
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
	Name:		��ȡ��ͼ��ָ��
	----------------------------------------------------------
	Params:		pViewClass ������
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
	HANDLE hMutexOneInstantance=CreateMutex(NULL,FALSE,_T("FZJ-CTC���ۺ�ά�޹���վ"));
	return ( GetLastError()==ERROR_ALREADY_EXISTS );
}
