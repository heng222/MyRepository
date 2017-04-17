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
        m_WebServModule(*this)

{
    NbsRegisterDispather(this);

    // ע��˳����ģ��ĳ�ʼ��˳���й�
    Register(&m_UIModule);
    Register(&m_DataModule);
    Register(&m_WebServModule);
}

CModuleDispatch::~CModuleDispatch(void)
{
    
}

void CModuleDispatch::PreInitialization()
{
    SetLogPath(GetExePath()+PATH_APP_LOG);
}

void CModuleDispatch::OnInitFailure(TModuleID aModulID)
{
    CImcDispatcher::OnInitFailure(aModulID);

    // Add your code after this.

    //
    CString strTip;
    strTip.Format(_T("�����ʼ��ʧ�ܣ�ģ��ID = %d��\n���ȷ�����˳�����"),
                    aModulID);

    ::MessageBox(NULL,strTip,"����",MB_ICONERROR);
}

void CModuleDispatch::OnStartFailure(TModuleID aModulID)
{
    CImcDispatcher::OnStartFailure(aModulID);

    // Add your code after this.

    //
    CString strTip;
    strTip.Format(_T("��������ʧ�ܣ�ģ��ID = %d��\n���ȷ�����˳�����"),aModulID);

    ::MessageBox(NULL,strTip,"����",MB_ICONERROR);

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


// �ڷַ���Ϣǰ����
BOOL CModuleDispatch::PreDispatchMsg(PTImcMsg aIMCMsg)
{
    NB_MSGID wMsgType = aIMCMsg->GetMsgType();
    
    // 
    /*if (wMsgType == ESCK_RECV_FRAME)
    {
        PIMsgFrmRecved pRecvFrame = (PIMsgFrmRecved)aIMCMsg;
    }*/

    return CImcDispatcher::PreDispatchMsg(aIMCMsg);
}


CMainFrame* CModuleDispatch::GetMainWnd()
{
    return m_UIModule.GetMainWnd();
}
