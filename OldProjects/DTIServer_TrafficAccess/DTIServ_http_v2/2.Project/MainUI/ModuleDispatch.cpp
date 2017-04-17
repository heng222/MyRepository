#include "StdAfx.h"
#include ".\moduledispatch.h"
#include "InterfaceEx.h"
#include "GlobalMacro.h"


#pragma warning(disable:4355)


//////////////////////////////////////////////////////////////////////////

DECLARE_NBASE_DISPATCHER(CModuleDispatch)


//////////////////////////////////////////////////////////////////////////
CModuleDispatch::CModuleDispatch(void):
            m_UIModule(*this),
            m_DataModule(*this),
            /*m_WebServModule(*this),*/
            m_HttpModule(*this)

{
    NbsRegisterDispather(this);

    // 注册顺序与模块的初始化顺序有关
    Register(&m_UIModule);
    Register(&m_DataModule);
    Register(&m_HttpModule);
    //Register(&m_WebServModule);
}

CModuleDispatch::~CModuleDispatch(void)
{
    
}

void CModuleDispatch::OnInitialize()
{
    SetLogPath(GetExePath()+PATH_APP_LOG);
}

void CModuleDispatch::OnInitFailure(TModuleID aModulID)
{
    CImcDispatcher::OnInitFailure(aModulID);

    // Add your code after this.

    //
    CString strTip;
    strTip.Format(_T("程序初始化失败，模块ID = %d。\n点击确定以退出程序。"),
                    aModulID);

    ::MessageBox(NULL,strTip,"错误",MB_ICONERROR);
}

void CModuleDispatch::OnStartFailure(TModuleID aModulID)
{
    CImcDispatcher::OnStartFailure(aModulID);

    // Add your code after this.

    //
    CString strTip;
    strTip.Format(_T("程序启动失败，模块ID = %d。\n点击确定以退出程序。"),aModulID);

    ::MessageBox(NULL,strTip,"错误",MB_ICONERROR);

    //
    m_UIModule.GetMainWnd()->m_bCloseTip = FALSE;
    m_UIModule.GetMainWnd()->PostMessage(WM_CLOSE);
}

BOOL CModuleDispatch::OnActive()
{

    // to do it before this
    return CImcDispatcher::OnActive();
}


void CModuleDispatch::OnClosing()
{
    m_UIModule.m_dlgStart.ShowWindow(SW_SHOW);
}


// 在分发消息前处理
BOOL CModuleDispatch::PreDispatchMsg(PTImcMsg aIMCMsg)
{
    NB_MSGID wMsgType = aIMCMsg->GetMsgType();
    
    return CImcDispatcher::PreDispatchMsg(aIMCMsg);
}

CMainFrame* CModuleDispatch::GetMainWnd()
{
    return m_UIModule.GetMainWnd();
}
