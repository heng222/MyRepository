#include "StdAfx.h"
#include "Uimodule.h"
#include "resource.h"
#include "GlobalMacro.h"
#include "DlgAppStart.h"
#include "MainUI.h"

//////////////////////////////////////////////////////////////////////////

CUIModule::CUIModule(CImcDispatcher& aDispatcher):
        CNBaseModule(aDispatcher,ID_MODULE_USERIF)
{
    m_pMainFrame = NULL;
    m_hOneInstance = NULL;
}

CUIModule::~CUIModule(void)
{
    if (m_dlgStart.GetSafeHwnd())
    {
        m_dlgStart.DestroyWindow();
    }
}

//////////////////////////////////////////////////////////////////////////
// From CNBaseModule

BOOL CUIModule::OnInitModule()
{
    if ( !CNBaseModule::OnInitModule())
    {
        return FALSE;
    }

    //
    m_dlgStart.Create(CDlgAppStart::IDD,NULL);
    m_dlgStart.ShowWindow(SW_SHOW);

    //
    IMsgAppLogs aLog;
    aLog.strComments.Format(_T("正在初始化UI模块……"));
    SendModuleMsg(aLog);

    // 检查程序是否已有一个实例启动
    if ( IsOneInstance() )
    {
        ::MessageBox(NULL,_T("程序的一个实例已处于运行状态!"),_T("警告"),MB_ICONEXCLAMATION);
        return FALSE;
    }

    // Create main MDI Frame window
    m_pMainFrame = new CMainFrame();
    if (!m_pMainFrame->LoadFrame(IDR_MAINFRAME))
    {
        return FALSE;
    }
    theApp.m_pMainWnd = m_pMainFrame;

    return TRUE;
}

BOOL CUIModule::OnStart()
{
    if (!CNBaseModule::OnStart())
    {
        return FALSE;
    }

    IMsgAppLogs aLog;
    aLog.strComments.Format(_T("正在启动UI模块……"));
    SendModuleMsg(aLog);

    // 
    m_pMainFrame->ShowWindow(SW_SHOWNORMAL);
    m_pMainFrame->UpdateWindow();


    aLog.logTime = COleDateTime::GetCurrentTime();
    aLog.strComments.Format(_T("UI模块已启动！"));
    SendModuleMsg(aLog);

    return TRUE;
}

BOOL CUIModule::OnActive()
{
    if (!CNBaseModule::OnActive())
    {
        return FALSE;
    }

    m_dlgStart.ShowWindow(SW_HIDE);

    m_pMainFrame->ActiveEvents();

    return TRUE;
}

void CUIModule::OnRecvIMCMessage(PTImcMsg aImcMsg)
{
    WORD wMsgType = aImcMsg->GetMsgType();
    if (ESYS_NEW_LOG == wMsgType)
    {
        // Receive a new log
        PIMsgAppLogs pLogOrigin = (PIMsgAppLogs)(aImcMsg);
        ASSERT(pLogOrigin!=NULL);

        // Show the message
        if (m_dlgStart.GetSafeHwnd())
        {
            m_dlgStart.SetFocus();
            m_dlgStart.SetInf(pLogOrigin->strComments);
        }

		// Send the msg to MainFrame.
        if (m_pMainFrame->GetSafeHwnd())
        {
            m_pMainFrame->SendMessage(UM_NEW_IMCMSG,(WPARAM)aImcMsg,0);
        }
    }
    else if (EDB_CONNECTION_STATE==wMsgType)
    {
        // send the msg to MainFrame.
        if (m_pMainFrame->GetSafeHwnd())
        {
            m_pMainFrame->SendMessage(UM_NEW_IMCMSG,(WPARAM)aImcMsg,0);
        }
    }

    //
    CNBaseModule::OnRecvIMCMessage(aImcMsg);
}

BOOL CUIModule::OnRecvInterMessage(PTImcMsg aImcMsg)
{
    WORD wMsgType = aImcMsg->GetMsgType();

    if (ESYS_RESTART_APP == wMsgType)
    {
        RestartApplication();
        return TRUE;
    }

    return CNBaseModule::OnRecvInterMessage(aImcMsg);
}

void CUIModule::OnClose()
{
    CloseMutex();

    //
    CNBaseModule::OnClose();
}


//////////////////////////////////////////////////////////////////////////
// public functions

CMainFrame* CUIModule::GetMainWnd()
{
    return m_pMainFrame;
}

//////////////////////////////////////////////////////////////////////////
// Private functions

BOOL CUIModule::IsOneInstance()
{
    CString strAppName;
    strAppName.LoadString(AFX_IDS_APP_TITLE);
    m_hOneInstance=CreateMutex(NULL,FALSE,strAppName);
    return ( GetLastError()==ERROR_ALREADY_EXISTS );
}
void CUIModule::CloseMutex()
{
    if (m_hOneInstance!=NULL)
    {
        CloseHandle(m_hOneInstance);
        m_hOneInstance = NULL;
    }
}
void CUIModule::RestartApplication()
{

    // close all the modules
    TImcMsg exitMsg(ESYS_CLOSE_ALLMODULS);
    NbsSendModuleMsg(&exitMsg);

    // close the main frame.
    m_pMainFrame->m_bCloseTip = FALSE;
    m_pMainFrame->ShowWindow(SW_HIDE);
    m_pMainFrame->PostMessage(WM_CLOSE);

    // create another instance
    STARTUPINFO startup;  
    GetStartupInfo(&startup);  

    TCHAR szPath[MAX_PATH];  
    GetModuleFileName(AfxGetApp()->m_hInstance,   szPath,   sizeof(szPath)); 

    LPTSTR szCmdLine = GetCommandLine();   

    PROCESS_INFORMATION   info;   
    CreateProcess(szPath, szCmdLine, NULL, NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&startup, &info);   

}

void CUIModule::EnableFullScreen(BOOL bEnable/*=TRUE*/)
{
    
}










