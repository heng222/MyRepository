// NaviServer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "NaviServer.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "NaviServerDoc.h"
#include "LiveLogView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNaviServerApp

BEGIN_MESSAGE_MAP(CNaviServerApp, CWinApp)
	//{{AFX_MSG_MAP(CNaviServerApp)
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
// CNaviServerApp construction

CNaviServerApp::CNaviServerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNaviServerApp object

CNaviServerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CNaviServerApp initialization

BOOL CNaviServerApp::InitInstance()
{

    ::CoInitialize(NULL);

	//
	TRACE("主线程ID= 0x%X\n",AfxGetThread()->m_nThreadID);
 

	AfxEnableControlContainer();

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

    CString strIncName;
    strIncName.LoadString(ID_INDICATOR_CORP);    
	SetRegistryKey(ID_INDICATOR_CORP);

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_NAVISETYPE,
		RUNTIME_CLASS(CNaviServerDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CLiveLogView));
	AddDocTemplate(pDocTemplate);


    //** Initializing... The main MDI Frame window will be created.
    if (!NbsInitialization())
    {
        return FALSE;
    }

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;


	//**  Start...  	    
    NbsStartRunning();


	//
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
void CNaviServerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CNaviServerApp message handlers

/*========================================================================
Name:		获取视图类指针
----------------------------------------------------------
Params:		pViewClass 视类型
----------------------------------------------------------
Remarks:	
==========================================================================*/
CView* CNaviServerApp::GetView(CRuntimeClass *pViewClass)
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

//
int CNaviServerApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	return CWinApp::ExitInstance();
}


