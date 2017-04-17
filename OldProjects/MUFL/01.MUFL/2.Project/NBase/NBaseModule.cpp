#include "StdAfx.h"
#include "NBaseModule.h"

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// CNBaseModule
// Constructor && Destructor
CNBaseModule::CNBaseModule(CImcDispatcher& aObeserver,TModuleID aMID):
    m_IMCDispatcher(aObeserver),
    m_iModuleID(aMID)
{
    m_iMState = EMS_NONE;
}
CNBaseModule::~CNBaseModule()
{

}

void CNBaseModule::SendModuleMsg(TImcMsg& aImcMsg)
{
    m_IMCDispatcher.AddMsg(&aImcMsg);
}
TModuleID CNBaseModule::GetMoudleID() const
{
    return m_iModuleID;
}
BOOL CNBaseModule::OnInitModule()
{
    m_iMState = EMS_INITLIALIZING;
    return TRUE;
}
BOOL CNBaseModule::OnStart()
{
    m_iMState = EMS_STARTING;
    return TRUE;
}
BOOL CNBaseModule::OnActive()
{
    m_iMState = EMS_ACTIVED;
    // to do...
    return TRUE;
}
void CNBaseModule::OnClose()
{
    m_iMState = EMS_CLOSED;
}
void CNBaseModule::OnRecvIMCMessage(PTImcMsg /*aImcMsg*/)
{
    
}
BOOL CNBaseModule::OnRecvInterMessage(PTImcMsg /*aImcMsg*/)
{
    return FALSE; // Not handle
}


//////////////////////////////////////////////////////////////////////////
// CImcDispatcher
CImcDispatcher::CImcDispatcher()
{
	NbsRegisterDispather(this);

    // Create message-handling thread and other relative matters
    m_hMsgSemaphore = CreateSemaphore(NULL,0,EMaxNumMsgQueue,NULL);

    m_hExitEvent = CreateEvent(NULL,TRUE,FALSE,NULL);

    m_pMsgHandleThread = AfxBeginThread(_MsgHandleThread,this);
    ASSERT(m_pMsgHandleThread!=NULL);
}

CImcDispatcher::~CImcDispatcher()
{
    Terminate();

    // 
    IMsgAppLogs aLog;
    aLog.strComments.Format(_T("保存日志……"));
    AddMsg(&aLog);
    m_AppLogMgr.Close();

    // 
    CloseHandle(m_hMsgSemaphore);
    CloseHandle(m_hExitEvent);

    //
    aLog.logTime = COleDateTime::GetCurrentTime();
    aLog.strComments.Format(_T("IT'S OVER!"));
    AddMsg(&aLog);
}

void CImcDispatcher::CloseMods()
{
    OnClosing();

    // 1. 
    POSITION posEnd = m_ModuleList.GetTailPosition();

    while (posEnd)
    {
        CNBaseModule* pModule = m_ModuleList.GetPrev(posEnd);
        pModule->OnClose();
    }

    //
    OnClosed();
}

void CImcDispatcher::RemoveModuls()
{
    m_ModuleList.RemoveAll();
}

void CImcDispatcher::Terminate()
{
    // 0. First...
    CloseMods();

    RemoveModuls();

    //
    OnTerminating();

    // 1. Terminate the thread.
    if (m_pMsgHandleThread != NULL) 
    {
        HANDLE hHandle = m_pMsgHandleThread->m_hThread;
        SetEvent(m_hExitEvent);

        if (WaitForSingleObject(hHandle,INFINITE)==WAIT_TIMEOUT) 
        {
            delete m_pMsgHandleThread;
        }
        m_pMsgHandleThread = NULL;
    }

    // 2. delete all the messages that have not handled.
    while (m_ImcMsgList.GetHeadPosition())
    {
        PTImcMsg pMsg = m_ImcMsgList.GetHead();
        TRACE(_T("\nUnhandled message ID = 0x%X"),pMsg->GetMsgType());
        delete m_ImcMsgList.RemoveHead();
    }
   
}

BOOL CImcDispatcher::IsExistModule(TModuleID aMID)
{
    POSITION pos = m_ModuleList.GetHeadPosition();
    while ( pos )
    {
        CNBaseModule* pModule = m_ModuleList.GetNext(pos);
        if (pModule->GetMoudleID() == aMID)
        {            
            return TRUE;
        }
    }
    return FALSE;
}
CNBaseModule* CImcDispatcher::FindModule(TModuleID aMID)
{
    POSITION pos = m_ModuleList.GetHeadPosition();
    while ( pos )
    {
        CNBaseModule* pModule = m_ModuleList.GetNext(pos);
        if (pModule->GetMoudleID() == aMID)
        {            
            return pModule;
        }
    }
    return NULL;
}
int CImcDispatcher::Register(CNBaseModule* aModule)
{
    if (aModule==NULL)
    {
        return ERR_INVALID;
    }

    TModuleID mID = aModule->GetMoudleID();
    if (IsExistModule(mID))
    {
        return ERR_ALREADYEXIST;
    }

    if (mID==ID_MODULE_ALL || mID==ID_MODULE_NONE || mID==ID_MODULE_SYS)
    {
        return ERR_CANNOTUSE;
    }

    if (mID<=ID_MODULE_RESERVED)
    {
        return ERR_CANNOTUSE;
    }

    if (mID==ID_MODULE_NONE)
    {
        return ERR_INVALID;
    }

    m_ModuleList.AddTail(aModule);
    return ERR_NONE;
}
void CImcDispatcher::UnRegister(TModuleID aModuleID)
{
    POSITION pos = m_ModuleList.GetHeadPosition();
    POSITION prePos = pos;
    while ( pos )
    {
        prePos = pos;
        CNBaseModule* pModule = m_ModuleList.GetNext(pos);
        if (pModule->GetMoudleID() == aModuleID)
        {           
            m_ModuleList.RemoveAt(prePos);
            return;
        }
    }
}
void CImcDispatcher::AddMsg(PTImcMsg pNewMsg)
{
    if (pNewMsg!=NULL)
    {
        if (pNewMsg->IsSynchronous())
        {
            DispatchMessage(pNewMsg);
        }
        else 
        {
            PTImcMsg pDump = pNewMsg->Duplicate();
            pDump->SetSynchronous(FALSE);
            pDump->SetAutoDel(TRUE);
            m_ImcMsgList.AddTail(pDump);
            ReleaseSemaphore(m_hMsgSemaphore,1,NULL);
        }
    }
}

void CImcDispatcher::SetLogPath(LPCTSTR lpcsPath)
{
    m_AppLogMgr.SetPath(lpcsPath);
}

void CImcDispatcher::SetLogCacheSize(BYTE nNumOfLog)
{
    m_AppLogMgr.SetCacheSize(nNumOfLog);
}

BOOL CImcDispatcher::OnActive()
{
    IMsgAppLogs aLog;
    aLog.strComments.Format(_T("-= 程序已正常启动！欢迎使用！=-"));
    AddMsg(&aLog);

    return TRUE;
}
void CImcDispatcher::OnClosing()
{

}
void CImcDispatcher::OnClosed()
{

}
void CImcDispatcher::OnTerminating()
{

}


void CImcDispatcher::OnInitialize()
{
    // do something here
}

TModuleID CImcDispatcher::Initialize()
{
    OnInitialize();

    // Initialize module in order
    TModuleID bRc = ID_MODULE_NONE;

    CNBaseModule* pModule = NULL;
    POSITION pos = m_ModuleList.GetHeadPosition();
    while ( pos )
    {
        pModule = m_ModuleList.GetNext(pos);
        if (!pModule->OnInitModule())
        {
            bRc = pModule->GetMoudleID();
            OnInitFailure(bRc);
            break;
        }
    }

    return bRc;
}

void CImcDispatcher::OnInitFailure(TModuleID aModulID)
{
    ASSERT(aModulID!=ID_MODULE_NONE);

    // Tip
    IMsgAppLogs aLog ;
    aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
    aLog.strComments.Format(_T("程序初始化失败，模块ID = %d。"), aModulID);
    AddMsg(&aLog);

    // Find the position that occurs error.
    CNBaseModule* pModule = NULL;
    POSITION pos = m_ModuleList.GetHeadPosition();
    while ( pos )
    {
        pModule = m_ModuleList.GetNext(pos);
        if (!pModule->GetMoudleID()==aModulID)
        {
            break;
        }
    }

    // close
    if (pos==NULL)
    {
        pos = m_ModuleList.GetTailPosition();
    }
    else
    {
        m_ModuleList.GetPrev(pos);
    }

    while ( pos )
    {
        pModule = m_ModuleList.GetPrev(pos);
        pModule->OnClose();
    }

    // 
    RemoveModuls();

    //
    Terminate();
    

}

TModuleID CImcDispatcher::StartRunMod()
{
    TModuleID bRc = ID_MODULE_NONE;

    CNBaseModule* pModule = NULL;

    // Start up all modules.
    POSITION pos = m_ModuleList.GetHeadPosition();
    while ( pos )
    {
        pModule = m_ModuleList.GetNext(pos);
        if (!pModule->OnStart())
        {
            bRc = pModule->GetMoudleID();
            goto EXIT_LABLE;
        }
    }

    // Active all modules
    pos = m_ModuleList.GetHeadPosition();
    while ( pos )
    {
        pModule = m_ModuleList.GetNext(pos);
        if (!pModule->OnActive())
        {
            bRc = pModule->GetMoudleID();
            goto EXIT_LABLE;
        }
    }

EXIT_LABLE:

    if (bRc!=ID_MODULE_NONE)
    {
        OnStartFailure(bRc);
    }
    else
    {
        if (!OnActive())
        {
            return ID_MODULE_SYS;
        }
    }

    return bRc;

}

void CImcDispatcher::OnStartFailure(TModuleID aModulID)
{
    ASSERT(aModulID!=ID_MODULE_NONE);

    // Tip
    IMsgAppLogs aLog ;
    aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
    aLog.strComments.Format(_T("程序启动失败，模块ID = %d。"), aModulID);
    AddMsg(&aLog);

    // 
    CNBaseModule* pModule = NULL;
    POSITION pos = m_ModuleList.GetTailPosition();

    while ( pos )
    {
        pModule = m_ModuleList.GetPrev(pos);
        pModule->OnClose();
    }

    RemoveModuls();

    //
    Terminate();

}


BOOL CImcDispatcher::PreDispatchMsg(PTImcMsg aImcMsg)
{
    BOOL bHandled = FALSE;

    NB_MSGID wMsgID = aImcMsg->GetMsgType();

    switch(wMsgID)
    {

    case ESYS_NEW_LOG:
        {
            // Receive a new log
            PIMsgAppLogs pNewLog = (PIMsgAppLogs)(aImcMsg);
            if (pNewLog->IsStorage())
            {
                // Save the new log
                m_AppLogMgr.AddTail(pNewLog);
            }

            bHandled = FALSE; // Set false to let other modules to handle.
        }
        break;

    case ESYS_CLOSE_ALLMODULS:
        {
            CloseMods();

            bHandled = TRUE;
        }
        break;

    case ESYS_RESTART_APP:
        {
            //bHandled = TRUE;
        }
        break;
    }

    return bHandled;
}

void CImcDispatcher::DispatchMessage(PTImcMsg aIMCMsg)
{
    if (aIMCMsg==NULL)
    {
        return;
    }

    // 1.
    if (PreDispatchMsg(aIMCMsg))
    {
        return;
    }
    if (aIMCMsg->IsExistDestModule(ID_MODULE_NONE))
    {
        return;
    }

    // 2.
    if (aIMCMsg->IsExistDestModule(aIMCMsg->GetSourceModul()))
    {
        CNBaseModule* destModule = FindModule(aIMCMsg->GetSourceModul());
        if (destModule!=NULL)
        {
            if (destModule->OnRecvInterMessage(aIMCMsg))
            {
                aIMCMsg->DelDestModule(aIMCMsg->GetSourceModul());
            }
        }
    }

    // 3.
    if (aIMCMsg->IsExistDestModule(ID_MODULE_ALL))
    {
        POSITION pos = m_ModuleList.GetHeadPosition();
        while ( pos )
        {
            CNBaseModule* destModule = m_ModuleList.GetNext(pos);
            destModule->OnRecvIMCMessage(aIMCMsg);
        }
    }
    else
    {
        BYTE number = aIMCMsg->GetNumDestMod();
        for (int ii=0; ii<number; ii++)
        {
            TModuleID destID = aIMCMsg->GetDestMod(ii);
            CNBaseModule* destModule = FindModule(destID);
            if (destModule!=NULL)
            {
                destModule->OnRecvIMCMessage(aIMCMsg);
            }
        }
    }
}
UINT CImcDispatcher::_MsgHandleThread(LPVOID pParam)
{
    ::CoInitialize(NULL);

	HANDLE hSafeEvent = ::CreateEvent(NULL,TRUE,TRUE,NULL); // to protect the msg list

    // 
    CImcDispatcher* pObject = (CImcDispatcher*)pParam;

    HANDLE hHandle[2] = {pObject->m_hExitEvent,pObject->m_hMsgSemaphore};
    DWORD dwNumHandle = sizeof(hHandle)/sizeof(hHandle[0]); 

    BOOL bRC = 0L;
    while (TRUE)
    {
		DWORD dwRc = ::WaitForMultipleObjects(dwNumHandle,hHandle,FALSE,INFINITE) - WAIT_OBJECT_0;

		if ( ::WaitForSingleObject(hSafeEvent,INFINITE)==WAIT_OBJECT_0 )
        {
			::ResetEvent(hSafeEvent);

            if (dwRc==0)
            {
                bRC = 1L;
                break;
            }
            else if (dwRc==1) 
            {
                if (pObject->m_ImcMsgList.IsEmpty())
                {
                    bRC = 2L;
                    break;
                }
                else
                {
                    PTImcMsg pMsg = pObject->m_ImcMsgList.RemoveHead();
                    try
                    {
                        pObject->DispatchMessage(pMsg);
                        pMsg->AutoDelete();
                    }
                    catch (CException* e)
                    {
                        e->ReportError();
                        e->Delete();
                        pMsg->AutoDelete();
                    }
                    SetEvent(hSafeEvent);
                }
            }
        }
    }

    pObject->m_pMsgHandleThread = NULL;

    ::CoUninitialize();

    return bRC;
}



//////////////////////////////////////////////////////////////////////////

// 
struct TAfxNBase 
{
public:
    CImcDispatcher* m_pImcDispather;

public:
    // 
    TAfxNBase();
    ~TAfxNBase();
};
typedef TAfxNBase* PTAfxNBase;


// Global variables 
TAfxNBase g_afxNBaseObject;

TAfxNBase::TAfxNBase()
{
    m_pImcDispather = NULL;
}
TAfxNBase::~TAfxNBase()
{

}


BOOL NbsRegisterDispather(CImcDispatcher* aDispather)
{
    if (aDispather!=NULL)
    {
        g_afxNBaseObject.m_pImcDispather = aDispather;
        return TRUE;
    }
    return FALSE;
}

int NbsRegisterModule(CNBaseModule* aModule)
{
	if (g_afxNBaseObject.m_pImcDispather!=NULL)
	{
		return g_afxNBaseObject.m_pImcDispather->Register(aModule);
	}
	else
	{
		return CImcDispatcher::ERR_UNKNOWN;
	}
}

void NbsSendModuleMsg(PTImcMsg aIMCMsg)
{
    if (g_afxNBaseObject.m_pImcDispather!=NULL)
    {
        g_afxNBaseObject.m_pImcDispather->AddMsg(aIMCMsg);
    }
    else
    {
        TRACE(_T("\nPlease call NbsRegisterDispather before call NbsSendModuleMsg\n"));
    }
}
void NbsUnregisterDispatch(BOOL bRelease)
{
    if (bRelease)
    {
        delete g_afxNBaseObject.m_pImcDispather;
    }

    g_afxNBaseObject.m_pImcDispather = NULL;
}
BOOL NbsInitialization()
{
    if (g_afxNBaseObject.m_pImcDispather!=NULL)
    {
        return (g_afxNBaseObject.m_pImcDispather->Initialize()==ID_MODULE_NONE);
    }
    else
    {
        TRACE(_T("\nPlease call NbsRegisterDispather before call NbsSendModuleMsg\n"));
        return FALSE;
    }
}
BOOL NbsStartRunning()
{
    if (g_afxNBaseObject.m_pImcDispather!=NULL)
    {
        return (g_afxNBaseObject.m_pImcDispather->StartRunMod()==ID_MODULE_NONE);
    }
    else
    {
        TRACE(_T("\nPlease call NbsRegisterDispather before call NbsSendModuleMsg\n"));
        return FALSE;
    }
}

void NbsTermination()
{
    if (g_afxNBaseObject.m_pImcDispather!=NULL)
    {
        g_afxNBaseObject.m_pImcDispather->Terminate();
    }
}










