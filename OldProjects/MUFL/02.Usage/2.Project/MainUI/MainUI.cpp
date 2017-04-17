// MainUI.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include ".\mainui.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "MainUIDoc.h"
#include "MainUIView.h"
#include "LogView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

    // 对话框数据
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    // 实现
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


//#define     WSA_VERSION     MAKEWORD(2,0)

// CMainUIApp

BEGIN_MESSAGE_MAP(CMainUIApp, CWinApp)

	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)

	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)

END_MESSAGE_MAP()


// CMainUIApp 构造
CMainUIApp::CMainUIApp()
{
}


// 唯一的一个 CMainUIApp 对象
CMainUIApp theApp;


// CMainUIApp 初始化
BOOL CMainUIApp::InitInstance()
{

    TRACE(("Main thread ID= 0x%X\n"),AfxGetThread()->m_nThreadID);

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
    CString strIncName; // 公司名称
    CString strAppName;// 程序名称  
    strIncName.LoadString(AFX_IDS_INCNAME);
    SetRegistryKey(strIncName);

    LoadStdProfileSettings();  // Load standard INI file options (including MRU)

    // 注册应用程序的文档模板。文档模板
    // 将用作文档、框架窗口和视图之间的连接
    CMultiDocTemplate* pDocTemplate;
    pDocTemplate = new CMultiDocTemplate(IDR_MainUITYPE,
        RUNTIME_CLASS(CMainUIDoc),
        RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
        RUNTIME_CLASS(CMainUIView));
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
    if (!NbsStartRunning())
    {
        //
    }
    

	//
	return TRUE;
}


// 用于运行对话框的应用程序命令
void CMainUIApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


/*========================================================================
Name:		获取视图类指针
----------------------------------------------------------
Params:		pViewClass 视类型
----------------------------------------------------------
Remarks:	
==========================================================================*/
CView* CMainUIApp::GetView(CRuntimeClass *pViewClass)
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


int CMainUIApp::ExitInstance()
{
    return CWinApp::ExitInstance();
}
