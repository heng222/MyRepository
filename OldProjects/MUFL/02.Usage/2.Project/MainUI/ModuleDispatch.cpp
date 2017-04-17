#include "StdAfx.h"
#include ".\moduledispatch.h"
#include "InterfaceEx.h"
#include "GlobalMacro.h"


#pragma warning(disable:4355)


//////////////////////////////////////////////////////////////////////////

DECLARE_NBASE_DISPATCHER(CModuleDispatch)


//////////////////////////////////////////////////////////////////////////
CModuleDispatch::CModuleDispatch(void):
        /*m_SckModule(*this),*/
        m_UIModule(*this),
        m_DataModule(*this)

{
    //NbsRegisterDispather(this);


	int rc;
    // ע��˳����ģ��ĳ�ʼ��˳���й�
	rc = Register(&m_UIModule);
    ASSERT(rc==CImcDispatcher::ERR_NONE);

	/*rc = Register(&m_SckModule);
    ASSERT(rc==CImcDispatcher::ERR_NONE);*/

	rc = Register(&m_DataModule);
    ASSERT(rc==CImcDispatcher::ERR_NONE);
}

CModuleDispatch::~CModuleDispatch(void)
{
    
}

void CModuleDispatch::OnInitialize()
{
	IMsgAppLogs aLog(_T("void CModuleDispatch::OnInitialize()"));
	NbsSendModuleMsg(&aLog);

	//
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

    ::MessageBox(NULL,strTip,_T("����"),MB_ICONERROR);
}

void CModuleDispatch::OnStartFailure(TModuleID aModulID)
{
    CImcDispatcher::OnStartFailure(aModulID);

    // Add your code after this.

    //
    CString strTip;
    strTip.Format(_T("��������ʧ�ܣ�ģ��ID = %d��\n���ȷ�����˳�����"),aModulID);

    ::MessageBox(NULL,strTip,_T("����"),MB_ICONERROR);

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
    if (m_UIModule.m_dlgStart.GetSafeHwnd()!=NULL)
    {
        m_UIModule.m_dlgStart.ShowWindow(SW_SHOW);
    }
    
}


// �ڷַ���Ϣǰ����
BOOL CModuleDispatch::PreDispatchMsg(PTImcMsg aIMCMsg)
{
    /*NB_MSGID wMsgType = aIMCMsg->GetMsgType();
    
    // 
    if (wMsgType == )
    {
          = ()aIMCMsg;
    }*/

    return CImcDispatcher::PreDispatchMsg(aIMCMsg);
}


CMainFrame* CModuleDispatch::GetMainWnd()
{
    return m_UIModule.GetMainWnd();
}
