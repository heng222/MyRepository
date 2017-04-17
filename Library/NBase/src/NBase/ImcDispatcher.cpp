#include "StdAfx.h"
#include "ImcDispatcher.h"

#pragma warning(disable:4482)

//////////////////////////////////////////////////////////////////////////
// CImcDispatcher
CImcDispatcher::CImcDispatcher()
{
    // Create message-handling thread and other relative matters
    m_hMsgSemaphore = CreateSemaphore(NULL, 0, EMaxNumMsgQueue, NULL);

    m_hExitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    m_pMsgHandleThread = AfxBeginThread(_MsgHandleThread, this);
}

CImcDispatcher::~CImcDispatcher()
{
    Terminate();

    // 
    CloseHandle(m_hMsgSemaphore);
    CloseHandle(m_hExitEvent);
}

void CImcDispatcher::Close()
{
    // 1. 
    POSITION posEnd = m_ModuleList.GetTailPosition();

    while (posEnd)
    {
        CNBaseModule* pModule = m_ModuleList.GetPrev(posEnd);
        pModule->OnClose();
    }
}

void CImcDispatcher::RemoveModuls()
{
    m_ModuleList.RemoveAll();
}

void CImcDispatcher::Terminate()
{
    // 0. First...
    Close();

    RemoveModuls();

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

BOOL CImcDispatcher::IsExistModule(int aMID)
{
    POSITION pos = m_ModuleList.GetHeadPosition();
    while ( pos )
    {
        CNBaseModule* pModule = m_ModuleList.GetNext(pos);
        if (pModule->get_MoudleID() == aMID)
        {            
            return TRUE;
        }
    }
    return FALSE;
}
CNBaseModule* CImcDispatcher::FindModule(int aMID)
{
    POSITION pos = m_ModuleList.GetHeadPosition();
    while ( pos )
    {
        CNBaseModule* pModule = m_ModuleList.GetNext(pos);
        if (pModule->get_MoudleID() == aMID)
        {            
            return pModule;
        }
    }
    return NULL;
}
int CImcDispatcher::AddModule(CNBaseModule* aModule)
{
    if (aModule==NULL)
    {
		return TRegErrType::ERR_INVALID;
    }

    int mID = aModule->get_MoudleID();
    if (IsExistModule(mID))
    {
        return ERR_ALREADYEXIST;
    }

    if (mID == CNBaseModule::ModuleIDAll 
        || mID == CNBaseModule::ModuleIDNone 
        || mID == CNBaseModule::ModuleIDSys)
    {
        return ERR_CANNOTUSE;
    }

    if (mID <= CNBaseModule::ModuleIDReserved)
    {
        return ERR_CANNOTUSE;
    }

    if (mID==CNBaseModule::ModuleIDNone)
    {
        return ERR_INVALID;
    }

    m_ModuleList.AddTail(aModule);
    return ERR_NONE;
}
void CImcDispatcher::RemoveModule(int aModuleID)
{
    POSITION pos = m_ModuleList.GetHeadPosition();
    POSITION prePos = pos;
    while ( pos )
    {
        prePos = pos;
        CNBaseModule* pModule = m_ModuleList.GetNext(pos);
        if (pModule->get_MoudleID() == aModuleID)
        {           
            m_ModuleList.RemoveAt(prePos);
            return;
        }
    }
}
void CImcDispatcher::AddMessage(PTImcMsg pNewMsg)
{
    CAutoLock lock(&m_criSection);

    if (pNewMsg!=NULL)
    {
        m_ImcMsgList.AddTail(pNewMsg);
        ReleaseSemaphore(m_hMsgSemaphore, 1, NULL);        
    }
}


int CImcDispatcher::Initialize()
{
    // Initialize module in order
    int bRc = CNBaseModule::ModuleIDNone;

    CNBaseModule* pModule = NULL;
    POSITION pos = m_ModuleList.GetHeadPosition();
    while ( pos )
    {
        pModule = m_ModuleList.GetNext(pos);
        if (!pModule->OnInitModule())
        {
            bRc = pModule->get_MoudleID();
            OnInitFailure(bRc);
            break;
        }
    }

    return bRc;
}

void CImcDispatcher::Active()
{
    // TODO:
}

void CImcDispatcher::OnInitFailure(int aModulID)
{
    ASSERT(aModulID!=CNBaseModule::ModuleIDNone);

    // Tip
    CAppLog aLog ;
    aLog.iLogType = CAppLog::ELL_ERROR;
    aLog.strComments.Format(_T("程序初始化失败，模块ID = %d。"), aModulID);
    DispatchMessage(&aLog);

    // Find the position that occurs error.
    CNBaseModule* pModule = NULL;
    POSITION pos = m_ModuleList.GetHeadPosition();
    while ( pos )
    {
        pModule = m_ModuleList.GetNext(pos);
        if (!pModule->get_MoudleID()==aModulID)
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

int CImcDispatcher::Start()
{
    int bRc = CNBaseModule::ModuleIDNone;

    CNBaseModule* pModule = NULL;

    // Start up all modules.
    POSITION pos = m_ModuleList.GetHeadPosition();
    while ( pos )
    {
        pModule = m_ModuleList.GetNext(pos);
        if (!pModule->OnStart())
        {
            bRc = pModule->get_MoudleID();
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
            bRc = pModule->get_MoudleID();
            goto EXIT_LABLE;
        }
    }

EXIT_LABLE:

    if (bRc!=CNBaseModule::ModuleIDNone)
    {
        OnStartFailure(bRc);
    }

    return bRc;

}

void CImcDispatcher::OnStartFailure(int aModulID)
{
    ASSERT(aModulID!=CNBaseModule::ModuleIDNone);

    // Tip
    CAppLog aLog ;
    aLog.iLogType = CAppLog::ELL_ERROR;
    aLog.strComments.Format(_T("程序启动失败，模块ID = %d。"), aModulID);
    DispatchMessage(&aLog);

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



void CImcDispatcher::DispatchMessage(PTImcMsg aIMCMsg, bool asyn)
{
    if (aIMCMsg==NULL)
    {
        return;
    }

    if (asyn)
    {
        PTImcMsg pDump = aIMCMsg->Duplicate();
        pDump->SetSynchronous(FALSE);
        pDump->SetAutoDel(TRUE);
        AddMessage(pDump);
    }
    else
    {
        if (aIMCMsg->IsExistDestModule(CNBaseModule::ModuleIDAll))
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
                int destID = aIMCMsg->GetDestMod(ii);
                CNBaseModule* destModule = FindModule(destID);
                if (destModule!=NULL)
                {
                    destModule->OnRecvIMCMessage(aIMCMsg);
                }
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



