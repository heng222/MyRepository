// MainUI.cpp : ����Ӧ�ó��������Ϊ��
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

    // �Ի�������
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

    // ʵ��
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
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)

	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)

END_MESSAGE_MAP()


// CMainUIApp ����
CMainUIApp::CMainUIApp()
{
}


// Ψһ��һ�� CMainUIApp ����
CMainUIApp theApp;


// CMainUIApp ��ʼ��
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
    CString strIncName; // ��˾����
    CString strAppName;// ��������  
    strIncName.LoadString(AFX_IDS_INCNAME);
    SetRegistryKey(strIncName);

    LoadStdProfileSettings();  // Load standard INI file options (including MRU)

    // ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
    // �������ĵ�����ܴ��ں���ͼ֮�������
    CMultiDocTemplate* pDocTemplate;
    pDocTemplate = new CMultiDocTemplate(IDR_MainUITYPE,
        RUNTIME_CLASS(CMainUIDoc),
        RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
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


// �������жԻ����Ӧ�ó�������
void CMainUIApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


/*========================================================================
Name:		��ȡ��ͼ��ָ��
----------------------------------------------------------
Params:		pViewClass ������
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
