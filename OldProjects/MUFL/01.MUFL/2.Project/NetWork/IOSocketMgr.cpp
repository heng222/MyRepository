

//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "IOSocketMgr.h"

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
#pragma warning(disable:4355)
//////////////////////////////////////////////////////////////////////////

extern BOOL g_va_bTraceInf;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
CIOSocketMgr::CIOSocketMgr()
{
    //InitializeCriticalSection(&m_CriticalSection);	
	
	// 
	m_pListenThread = NULL;
	m_hListenSocket = NULL;

}

CIOSocketMgr::~CIOSocketMgr()
{
    //DeleteCriticalSection(&m_CriticalSection);
}

//////////////////////////////////////////////////////////////////////

void CIOSocketMgr::Close()
{
    // Close listening socket.
    if (m_hListenSocket != NULL) 
    {
        shutdown(m_hListenSocket,SD_BOTH);
        closesocket(m_hListenSocket);
        m_hListenSocket = NULL;
    }

    /*if (m_pListenThread != NULL) 
    {
        HANDLE hHandle = m_pListenThread->m_hThread;
        WaitForSingleObject(hHandle,INFINITE);
        m_pListenThread = NULL;
    }*/

}

BOOL CIOSocketMgr::StartService(TSockAddr& serAddr)
{
	if (m_hListenSocket == NULL) 
	{
		m_hListenSocket = socket(AF_INET,SOCK_STREAM,0);
	}
	else
	{
		return FALSE;
	}

	// bind
	if (bind(m_hListenSocket,(LPSOCKADDR)(&serAddr),sizeof(serAddr))!=0) 
	{
        Close();
		return FALSE;
	}

	// start listening.
	listen(m_hListenSocket,5);

	// start listening thread
	m_pListenThread = AfxBeginThread(_ListeningThread,this);

	return TRUE;
}


UINT CIOSocketMgr::_ListeningThread(LPVOID pParam)
{
    if (g_va_bTraceInf)
    {
        TRACE(_T("Listening thread ID= 0x%X\n"),AfxGetThread()->m_nThreadID);
    }

	CIOSocketMgr* pMgrThis = (CIOSocketMgr*)pParam;	
	
    //
	UINT uReturnCode = 0;
    while (TRUE)
    {
		sockaddr_in clientAddr;
		int iAddrLen = sizeof(clientAddr);

        // Accept...
		SOCKET aNewSocket = accept( pMgrThis->m_hListenSocket,
									(sockaddr*)&clientAddr,&iAddrLen);

	
		if (aNewSocket == INVALID_SOCKET )
        {
            if (g_va_bTraceInf)
            {
                TRACE("\nAccept return an invalide SOCKET!\n"); // when close the listening socket.
            }


			uReturnCode = 10L;
			break;
		}
		else
		{
			pMgrThis->OnNewConnection(aNewSocket,clientAddr);
        }
	}

	//
    if (g_va_bTraceInf)
    {
        TRACE("\n\nAttention: Listening thread terminate.ID = 0x%X,rc=%d\n",
            AfxGetThread()->m_nThreadID,uReturnCode);
    }

	return uReturnCode;
}

void CIOSocketMgr::OnNewConnection(SOCKET aSck,const TSockAddr& clientAddr)
{

}
void CIOSocketMgr::OnRecvFrame(TBaseProtocol* pProtocolFrame,CIOSocket* pParam)
{

}
void CIOSocketMgr::OnConnectionDown(CIOSocket* pIoSck)
{

}
