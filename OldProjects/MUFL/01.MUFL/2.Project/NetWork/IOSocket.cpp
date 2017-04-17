
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IOSocket.h"


#pragma warning(disable:4311)
#pragma warning(disable:4312)

//////////////////////////////////////////////////////////////////////////
BOOL        g_va_bTraceInf = TRUE;


HANDLE	    g_va_hCompletionPort = NULL;
HANDLE	    g_va_hRcvThrdsExitEvent = NULL;
BYTE        g_va_byRecvThredNum = 0;
CWinThread*	g_va_pRecvThread[20] = {NULL};


void        g_fn_CreateReceiverThreads();
UINT        g_fn_RecvThread(LPVOID pParam);


// 
int NciStartup()
{
    if (g_va_hCompletionPort!=NULL)
    {
        return 1;
    }

    g_va_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,0);
    if (g_va_hCompletionPort == NULL) 
    {
        if (g_va_bTraceInf)
        {
            TRACE("Create completion port failure!\n");
        }
        return 2;
    }

    // 
    g_va_hRcvThrdsExitEvent = CreateEvent(NULL,TRUE,FALSE,NULL);

    //
    g_fn_CreateReceiverThreads();

    return 0;
}


void NciCleanup()
{
    // Active Exit event
    if (g_va_hRcvThrdsExitEvent!=NULL)
    {
        SetEvent(g_va_hRcvThrdsExitEvent);
    }

    // Terminate receiving threads
    BYTE ii=0;
    int iCount = 0;
    while (ii!=g_va_byRecvThredNum && iCount<=g_va_byRecvThredNum*20)
    {
        if (g_va_pRecvThread[ii]!=NULL)
        {
            HANDLE hHandle = g_va_pRecvThread[ii]->m_hThread;
            LPOVERLAPPED lpOverlapped = NULL;
            PostQueuedCompletionStatus(g_va_hCompletionPort,0,NULL,lpOverlapped);
            WaitForSingleObject(hHandle,100);
        }
        else
        {
            ii++;
        }

        iCount ++;
    }
    g_va_byRecvThredNum = 0;

    //
    if (g_va_hRcvThrdsExitEvent!=NULL)
    {
        CloseHandle(g_va_hRcvThrdsExitEvent);
        g_va_hRcvThrdsExitEvent = NULL;
    }


    // Close the I/O Completion port.
    if (g_va_hCompletionPort != NULL) 
    {
        CloseHandle(g_va_hCompletionPort);
        g_va_hCompletionPort = NULL;
    }
}

void NciEnableTipInf(BOOL bEnable)
{
    g_va_bTraceInf = bEnable;
}

//////////////////////////////////////////////////////////////////////////
// 
void g_fn_CreateReceiverThreads()
{
    SYSTEM_INFO  sysinfo;
    GetSystemInfo(&sysinfo);
    g_va_byRecvThredNum = (BYTE)(sysinfo.dwNumberOfProcessors * 2+2);

    if (g_va_bTraceInf)
    {
        TRACE("Number of CPU£½%d, Number of receiving thread=%d\n",
            sysinfo.dwNumberOfProcessors,g_va_byRecvThredNum);
    }

    for (BYTE i=0; i<g_va_byRecvThredNum; i++)
    {
        int* pParam = new int(i);
        g_va_pRecvThread[i] = AfxBeginThread(g_fn_RecvThread,pParam,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED);
        g_va_pRecvThread[i]->ResumeThread();

        if (g_va_bTraceInf)
        {
            TRACE("Launch receiveing thread 0x%X\n",g_va_pRecvThread[i]->m_nThreadID);
        }
    }  
}

UINT g_fn_RecvThread(LPVOID pParam)
{
    int iIndex = *(int*)pParam;

    delete (int *)pParam;

    UINT uRC = 0;

    // Loop forever on getting packets from the I/O completion port.
    for (;;)
    {
        DWORD   dwNumRead = 0;
        DWORD	dwKey = 0;
        LPOVERLAPPED lpOverlapped=NULL;


        BOOL bResult = GetQueuedCompletionStatus(
            g_va_hCompletionPort,
            &dwNumRead,
            &dwKey,
            &lpOverlapped,
            INFINITE);

        // 
        if (WaitForSingleObject(g_va_hRcvThrdsExitEvent,0) == WAIT_OBJECT_0 ) 
        {
            uRC = 0;
            break;
        }

        // 
#pragma warning(disable:4312)
        CIOSocket*	pIoSocket = reinterpret_cast<CIOSocket*>(dwKey);
#pragma warning(default:4312)

        //
        if ( bResult==FALSE  && lpOverlapped==NULL )
        {
            if (g_va_bTraceInf)
            {
                TRACE("\nThreadFunc - Illegal call to GetQueuedCompletionStatus\n");
                TRACE("\nE:GetQueued1,LastError = %d\n",GetLastError());
            }

            uRC = 10L;
            break;
        }
        else if ( bResult==FALSE && lpOverlapped!=NULL )
        {
            // This happens occasionally instead of end-of-file. Not sure why.

            // ERROR_NETNAME_DELETED=64: The specified network name is no longer available.
            /* ERROR_OPERATION_ABORTED=995: The I/O operation has been aborted 
            because of either a thread exit or an application request.
            */

            DWORD dwErrCode = GetLastError();
            if (g_va_bTraceInf)
            {
                TRACE("\nW:GetQueued2,LastError = %d\n",dwErrCode);
            }
            if (dwErrCode==ERROR_NETNAME_DELETED && pIoSocket!=NULL)
            {
                pIoSocket->m_Observer.OnConnectionDown(pIoSocket);
                //pIoSocket->OnRecvRawData(pIoSocket->m_byInBuffer,0);
            }
            uRC = dwErrCode;

        }
        else if ( dwNumRead==0 )
        {
            // Caused by close(SOCKET).
            DWORD dwErrCode = GetLastError();

            if (g_va_bTraceInf)
            {
                TRACE("\nW:GetQueued3,LastError = %d\n",dwErrCode);
            }

            if ( pIoSocket!=NULL )
            {
                pIoSocket->m_Observer.OnConnectionDown(pIoSocket);
                //pIoSocket->OnRecvRawData(pIoSocket->m_byInBuffer,0);
            }

            //
            uRC = 30L;
        }
        else
        {
            ASSERT(pIoSocket!=NULL);

            if (pIoSocket!=NULL)
            {
                // Got a valid data block!
                // Save the data to our buffer.
                pIoSocket->OnRecvRawData(pIoSocket->m_byInBuffer,dwNumRead);

                // Continue Reading the socket;
                pIoSocket->Recv();
            }

        }
    }

    if (g_va_bTraceInf)
    {
        TRACE(_T("\nA receiveing thread terminate. Index=%d£¬Thread ID = 0x%X£¬Rc = %d\n\n"),
                iIndex,AfxGetThread()->m_nThreadID,uRC);
    }

    g_va_pRecvThread[iIndex] = NULL;

    return uRC;
}



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#pragma warning(disable:4312)

CIOSocket::CIOSocket(SOCKET aNewSocket,MIOSckObserver&  aObserver,int iType):
	m_Observer(aObserver)
{
    InitializeCriticalSection(&m_CSRecvBuffer);


    ASSERT(aNewSocket!=INVALID_SOCKET);
    m_hSocket = aNewSocket;

    m_iStatus = ETS_UNKOWN;

    m_pFrameParser = NULL;
    m_iProType = iType;

    m_lDataSent = 0;
    m_lDataRecv = 0;

	/************************************************************************/
	/*  Initialize OVERLAPPED                                               */
	/************************************************************************/
	// receive
	memset(&m_overLappedIn,0,sizeof(m_overLappedIn));
	m_overLappedIn.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	// sending
	memset(&m_overLappedOut,0,sizeof(m_overLappedOut));
	m_overLappedOut.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	m_overLappedOut.hEvent = (HANDLE)((DWORD)m_overLappedOut.hEvent|0x01);

}

CIOSocket::~CIOSocket()
{
    Close();
    DeleteCriticalSection(&m_CSRecvBuffer);
}

void CIOSocket::Close()
{   
    m_iStatus = ETS_UNKOWN;

	if (m_hSocket != NULL) 
	{
		shutdown(m_hSocket,SD_BOTH);
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;
	}

    if (m_pFrameParser!=NULL)
    {
        delete m_pFrameParser;
        m_pFrameParser = NULL;
    }

    m_lDataRecv = 0;
    m_lDataSent = 0;

	/*if (m_overLappedIn.hEvent!=NULL)
	{
	CloseHandle(m_overLappedIn.hEvent);
	memset(&m_overLappedIn,0,sizeof(m_overLappedIn));
	}

	if (m_overLappedOut.hEvent!=NULL)
	{
	CloseHandle(m_overLappedOut.hEvent);
	memset(&m_overLappedOut,0,sizeof(m_overLappedOut));
	}*/
}


///////////////////////////////////////////////////////////////////////////////////

void CIOSocket::SetClientAddr(const sockaddr_in* pNewAdd)
{
	memcpy(&m_clientAddr,pNewAdd,sizeof(sockaddr_in));
}

void CIOSocket::SetClientAddr(CString strIPAdd, unsigned short uPort/*=0*/)
{
	m_clientAddr = TSockAddr((LPCTSTR)strIPAdd,uPort);
}
void CIOSocket::SetServerAddr(CString strIPAdd,unsigned short uPort)
{
    m_serverAddr = TSockAddr((LPCTSTR)strIPAdd,uPort);
}
void CIOSocket::SetServerAddr(const sockaddr_in* pNewAddr)
{
    m_serverAddr = *pNewAddr;
}

void CIOSocket::GetClientAddr(LPBYTE pClientIP,u_short& uPort) const
{
	pClientIP[0] = m_clientAddr.sin_addr.S_un.S_un_b.s_b1;
	pClientIP[1] = m_clientAddr.sin_addr.S_un.S_un_b.s_b2;
	pClientIP[2] = m_clientAddr.sin_addr.S_un.S_un_b.s_b3;
	pClientIP[3] = m_clientAddr.sin_addr.S_un.S_un_b.s_b4;
	//
	uPort = ntohs(m_clientAddr.sin_port);
}

void CIOSocket::GetClientAddr(CString& strIP,CString& strPort) const
{
	strIP.Format(_T("%d.%d.%d.%d"),
		m_clientAddr.sin_addr.S_un.S_un_b.s_b1,
		m_clientAddr.sin_addr.S_un.S_un_b.s_b2,
		m_clientAddr.sin_addr.S_un.S_un_b.s_b3,
		m_clientAddr.sin_addr.S_un.S_un_b.s_b4);
	//
	strPort.Format(_T("%d"),ntohs(m_clientAddr.sin_port));
}
void CIOSocket::GetServerAddr(LPBYTE pClientIP,u_short& uPort) const
{
	pClientIP[0] = m_serverAddr.sin_addr.S_un.S_un_b.s_b1;
	pClientIP[1] = m_serverAddr.sin_addr.S_un.S_un_b.s_b2;
	pClientIP[2] = m_serverAddr.sin_addr.S_un.S_un_b.s_b3;
	pClientIP[3] = m_serverAddr.sin_addr.S_un.S_un_b.s_b4;
	//
	uPort = ntohs(m_serverAddr.sin_port);
}
void CIOSocket::GetServerAddr(CString& strIP,CString& strPort) const
{
    strIP = m_serverAddr.DottedDecimal();
    strPort.Format(_T("%d"),ntohs(m_serverAddr.sin_port));
}

// Retrieve the bytes of data that have sent and received.
__int64  CIOSocket::RetrieveDataSent() const
{
    return m_lDataSent;
}
__int64  CIOSocket::RetrieveDataRecv() const
{
    return m_lDataRecv;
}

//////////////////////////////////////////////////////////////////////////
//
int CIOSocket::GetProtocolType() const
{
    return m_iProType;
}

//////////////////////////////////////////////////////////////////////////
// 

BOOL CIOSocket::PreActive()
{
	return (m_pFrameParser!=NULL);
}

BOOL CIOSocket::ActiveIoSck(BOOL bClient)
{
    ASSERT(g_va_hCompletionPort!=NULL);
    if (g_va_hCompletionPort==NULL)
    {
        return FALSE;
    }

    if(m_hSocket==INVALID_SOCKET)
    {
        return FALSE;
    }

    m_iStatus = bClient ? ETS_CLIENT : ETS_SERVER;

    InstanceParser(m_pFrameParser);

	if (!PreActive())
	{
		return FALSE;
	}


	if (m_iStatus==ETS_CLIENT)
	{
        int iRC = connect(m_hSocket,m_serverAddr,sizeof(TSockAddr));
        if (iRC!=0)
        {
            return FALSE;
        }
	}
	
	// Associate the socket with the completion port.
	if ( CreateIoCompletionPort( (HANDLE)m_hSocket,
		                           g_va_hCompletionPort,(DWORD)this,0)==NULL )
    {
		TRACE(_T("Error: Associate the socket with the completion port failure!\n"));
		return FALSE;
	}

	// start receiving data from socket with overlapped I/O
	Recv();

	//
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// 
void CIOSocket::SendFrame(PTBaseProtocol pFrame)
{
    int wLenFrame = 0;
    if (m_pFrameParser!=NULL)
    {
        WORD wMaxLen = m_pFrameParser->GetMaxLenFrame();
        BYTE* pFrameBuf = new BYTE[wMaxLen];
        memset(pFrameBuf,0,wMaxLen);

        m_pFrameParser->BuildPacket(pFrame,pFrameBuf,wLenFrame);
        SendRawData(pFrameBuf,wLenFrame);

        delete[] pFrameBuf;
    }
}

DWORD CIOSocket::SendRawData(const BYTE *buf, DWORD len)
{
	DWORD dwWriteOnce = 0;
	DWORD dwWriteNumAll = 0;

    if (m_hSocket!=INVALID_SOCKET)
    {
        while (dwWriteNumAll != len)
        {
            if ( !WriteFile((HANDLE)m_hSocket,
                buf+dwWriteOnce,
                len,
                &dwWriteOnce,
                &m_overLappedOut))
            {
                break;
            }

            dwWriteNumAll += dwWriteOnce;
        }

        OnFinishSendingRawData(dwWriteNumAll);
    }

    m_lDataSent += dwWriteNumAll;
	return dwWriteNumAll;
}


void CIOSocket::OnFinishSendingRawData(DWORD dwLen)
{
    // do something...
}

int CIOSocket::Recv()
{
	DWORD   dwNumRead = 0;

    if (m_hSocket!=INVALID_SOCKET)
    {
        BOOL rc = ReadFile((HANDLE)m_hSocket,m_byInBuffer,
            sizeof(m_byInBuffer),&dwNumRead,&m_overLappedIn);
        if (dwNumRead!=0) 
        {
            // Attention£ºthe data could be invalid, so do nothing here£¡
        }
    }

	return dwNumRead;
}

void CIOSocket::OnRecvRawData(LPBYTE pData, DWORD iLen)
{
    m_lDataRecv += iLen;

	// to parse the raw data.
	if (m_pFrameParser!=NULL && iLen>0)
	{
        // 
        EnterCriticalSection(&m_CSRecvBuffer);

        CBaseProtocolList frameList;
        m_pFrameParser->ParseRawData(pData,(WORD)iLen,frameList);

        LeaveCriticalSection(&m_CSRecvBuffer);

        // 
        POSITION pos = frameList.GetHeadPosition();
        while (pos)
        {
            TBaseProtocol* pFrame = frameList.GetNext(pos);
            OnRecvFrame(pFrame);
            pFrame->AutoDel();
        }
	}
}

void CIOSocket::OnRecvFrame(TBaseProtocol* pFrame)
{
    ASSERT(pFrame!=NULL);
	// Comment
	// to add your code if you wanna do something...

	/**********************************************************/
	/*  send it to Observer                                   */
	/**********************************************************/
	m_Observer.OnRecvFrame(pFrame,this);

}