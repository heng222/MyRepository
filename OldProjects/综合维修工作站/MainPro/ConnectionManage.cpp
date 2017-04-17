// ConnectionManage.cpp: implementation of the CConnectionManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ConnectionManage.h"
#include <atlconv.h>
#include <process.h>
#include "ini.h"
#include "pingaddr.h"



CMessageItem::CMessageItem()
{
	dwCount = 0;
	Buffertype = 0;
	BufferVersion = 0;
	dwTimeout = 0;
	strIPM = "";
	strIPB = "";
	nSendCount = 0;
}

CMessageItem::~CMessageItem()
{

}

CMessageItem& CMessageItem::operator=(const CMessageItem& mi) 
{ 
	this->dwCount = mi.dwCount;
	this->Buffertype = mi.Buffertype;
	this->BufferVersion = mi.BufferVersion;
	this->dwTimeout = mi.dwTimeout;
	this->nSendCount = mi.nSendCount;
	memcpy(this->lpBuffer, mi.lpBuffer, BUFFER_SIZE);
	this->strIPM = mi.strIPM;
	this->strIPB = mi.strIPB;
	return *this; 
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CConnectionManage::CConnectionManage()
{
	m_bRun = false;
	m_hThread = NULL;
	m_strSIPM = "";
	m_strSPortM = "";
	m_strSIPB = "";
	m_strSPortB = "";
	m_strCIPM = "";
	m_strCPortM = "";
	m_strCIPB = "";
	m_strCPortB = "";
	m_strClientName = "";
	m_strServerName = "";
	m_hCloseEvent = NULL;
	Semaphore = new CSemaphore(1,1);
	SingleLock = new CSingleLock(Semaphore);
}

CConnectionManage::~CConnectionManage()
{
	StopComm();
	delete SingleLock;
	delete Semaphore;
}


bool CConnectionManage::IsOpen()
{
	return (IsOpenB2B()||IsOpenB2M()||IsOpenM2B()||IsOpenM2M());
}

bool CConnectionManage::IsOpenB2B()
{
	return m_connectB2B.IsOpen();
}

bool CConnectionManage::IsOpenB2M()
{
	return m_connectB2M.IsOpen();
}

bool CConnectionManage::IsOpenM2B()
{
	return m_connectM2B.IsOpen();
}

bool CConnectionManage::IsOpenM2M()
{
	return m_connectM2M.IsOpen();
}

bool CConnectionManage::ConnectTo(LPCTSTR strSipM, LPCTSTR strSportM,
				LPCTSTR strSipB, LPCTSTR strSportB,
				LPCTSTR strCipM, LPCTSTR strCportM,
				LPCTSTR strCipB, LPCTSTR strCportB,
				int nProtocol, int nType)
{

	if (!m_bRun)
	{
		m_strSIPM  = strSipM;
		m_strSPortM =strSportM;
		m_strSIPB= strSipB;
		m_strSPortB =strSportB;
		m_strCIPM =strCipM;
		m_strCPortM =strCportM;
		m_strCIPB =strCipB;
		m_strCPortB =strCportB;



		bool bsuccessMM = SingleConnectTo(&m_connectM2M,m_strSIPM,m_strSPortM,m_strCIPM,"1731",nProtocol,nType);
		Sleep(120);
		bool bsuccessBM = SingleConnectTo(&m_connectB2M,m_strSIPB,m_strSPortB,m_strCIPM,"1633",nProtocol,nType);
		Sleep(120);
		bool bsuccessMB = SingleConnectTo(&m_connectM2B,m_strSIPM,m_strSPortM,m_strCIPB,"1632",nProtocol,nType);
		Sleep(120);
		bool bsuccessBB = SingleConnectTo(&m_connectB2B,m_strSIPB,m_strSPortB,m_strCIPB,"1634",nProtocol,nType);
		Sleep(120);
	//	return bsuccessMM;
		m_bRun = true;
		WatchConnect();
		return (bsuccessMM||bsuccessMB||bsuccessBM||bsuccessBB);
	}
	return false;
}

void CConnectionManage::ConnectionCheck() 
{
	while (m_bRun == true)
	{
		if (!IsOpenB2B())
		{
			bool bsuccessBB = SingleConnectTo(&m_connectB2B,m_strSIPB,m_strSPortB,m_strCIPB,m_strCPortB, AF_INET, SOCK_STREAM);
		}
		else
		{
			if (!CPingAddr::Ping(m_strSIPB))
			{
				m_connectB2B.OnEvent(EVT_CONDROP);
			}
		}
		if (!IsOpenB2M())
		{
			bool bsuccessBM = SingleConnectTo(&m_connectB2M,m_strSIPB,m_strSPortB,m_strCIPM,m_strCPortM, AF_INET, SOCK_STREAM);
		}
		else
		{
			if (!CPingAddr::Ping(m_strSIPB))
			{
				m_connectB2M.OnEvent(EVT_CONDROP);
			}
		}
		if (!IsOpenM2B())
		{
			bool bsuccessMB = SingleConnectTo(&m_connectM2B,m_strSIPM,m_strSPortM,m_strCIPB,m_strCPortB, AF_INET, SOCK_STREAM);
		}
		else
		{
			if (!CPingAddr::Ping(m_strSIPM))
			{
				m_connectM2B.OnEvent(EVT_CONDROP);
			}
		}
		if (!IsOpenM2M())
		{
			bool bsuccessMM = SingleConnectTo(&m_connectM2M,m_strSIPM,m_strSPortM,m_strCIPM,m_strCPortM, AF_INET, SOCK_STREAM);
		}
		else
		{
			if (!CPingAddr::Ping(m_strSIPM))
			{
				m_connectM2M.OnEvent(EVT_CONDROP);
			}
		}
		WaitForSingleObject(m_hCloseEvent, 4000L);
	}
}

DWORD CConnectionManage::WriteComm(BYTE Buffertype, BYTE BufferVersion, const LPBYTE lpBuffer, DWORD dwCount, DWORD dwTimeout)
{
	CMessageItem mi;
	mi.dwCount = dwCount;
	mi.Buffertype = Buffertype;
	mi.BufferVersion = BufferVersion;
	mi.dwTimeout = dwTimeout;
	memcpy(mi.lpBuffer, lpBuffer, dwCount);
	this->addSendMessage(&mi);
//	TRACE("add %d %d %d\r\n", Buffertype, BufferVersion, dwCount);
	return 0;
//	return WriteCommDetail(Buffertype,BufferVersion,lpBuffer, dwCount, dwTimeout);
}

bool CConnectionManage::SingleConnectTo(CSocketManager * pManager ,LPCTSTR strSip, LPCTSTR strSport,
					LPCTSTR strCip, LPCTSTR strCport,
				int nProtocol, int nType)
{
	BYTE byBuffer[256] = { 0 };
	bool bSuccess = pManager->ConnectTo( strSip, strSport, strCip, strCport, AF_INET, SOCK_STREAM); // TCP
	CString strMsg;
	if (bSuccess)
	{
		if(pManager->WatchComm())
		{
			return TRUE;
		}
		else
		{
			pManager->OnEvent(EVT_CONDROP);
//			TRACE("ConnectTo fail %s  %d\r\n",strSip,pManager);
		}
	}
//	TRACE("ConnectTo fail with connect %s  %d\r\n",strSip,pManager);
	return FALSE;
}


void CConnectionManage::SetServerState(bool bServer)
{
	m_connectB2B.SetServerState(bServer);
	m_connectB2M.SetServerState(bServer);
	m_connectM2B.SetServerState(bServer);
	m_connectM2M.SetServerState(bServer);
}

void CConnectionManage::SetSmartAddressing(bool bSmartAddressing)	// Set Smart addressing mode
{
	m_connectB2B.SetSmartAddressing(bSmartAddressing);
	m_connectB2M.SetSmartAddressing(bSmartAddressing);
	m_connectM2B.SetSmartAddressing(bSmartAddressing);
	m_connectM2M.SetSmartAddressing(bSmartAddressing);

}

void CConnectionManage::CloseComm()
{
	m_connectB2B.CloseComm();
	m_connectB2M.CloseComm();
	m_connectM2B.CloseComm();
	m_connectM2M.CloseComm();

}


void CConnectionManage::StopComm()
{
	m_bRun = false;
	// Kill Thread
	if (m_hThread != NULL)
	{
		SetEvent(m_hCloseEvent);
		if (WaitForSingleObject(m_hThread, 30L) == WAIT_TIMEOUT)
			TerminateThread(m_hThread, 30L);
		CloseHandle(m_hThread);
		m_hThread = NULL;
		CloseHandle(m_hCloseEvent);
		m_hCloseEvent = NULL;
	}
	m_connectB2B.StopComm();
	m_connectB2M.StopComm();
	m_connectM2B.StopComm();
	m_connectM2M.StopComm();

	while (!sendList.IsEmpty())
	{
		CMessageItem * item  = (CMessageItem *)sendList.RemoveHead();
		if (item != NULL)
			delete item;
	}
}

void CConnectionManage::SetMessageWindow(CWnd* pMsgView)
{
	m_connectB2B.SetMessageWindow(pMsgView);
	m_connectB2M.SetMessageWindow(pMsgView);
	m_connectM2B.SetMessageWindow(pMsgView);
	m_connectM2M.SetMessageWindow(pMsgView);
}

void CConnectionManage::SetMessageWnd(CWnd* pMsgWnd)
{
	m_connectB2B.SetMessageWnd(pMsgWnd);
	m_connectB2M.SetMessageWnd(pMsgWnd);
	m_connectM2B.SetMessageWnd(pMsgWnd);
	m_connectM2M.SetMessageWnd(pMsgWnd);
}

DWORD CConnectionManage::WriteCommDetail(BYTE Buffertype, BYTE BufferVersion, const LPBYTE lpBuffer, DWORD dwCount, DWORD dwTimeout)
{
	bool bSuccess = TRUE;
	if (IsOpenB2B())
	{
		return m_connectB2B.WriteComm(Buffertype,BufferVersion,lpBuffer, dwCount, dwTimeout);
	}
	if (IsOpenB2M())
	{
		return m_connectB2M.WriteComm(Buffertype,BufferVersion,lpBuffer, dwCount, dwTimeout);
	}
	if (IsOpenM2B())
	{
		return m_connectM2B.WriteComm(Buffertype,BufferVersion,lpBuffer, dwCount, dwTimeout);
	}
	if (IsOpenM2M())
	{
		return m_connectM2M.WriteComm(Buffertype,BufferVersion,lpBuffer, dwCount, dwTimeout);
	}
	return -1;
}

CString CConnectionManage::getConnectString()
{
	CString strReturn;
	strReturn = "";
	if (IsOpenB2B())
	{
		strReturn = strReturn + "b-b:" + m_connectB2B.getConnectString()+"\r\n";
	}
	if (IsOpenB2M())
	{
		strReturn = strReturn + "b-m:" + m_connectB2M.getConnectString()+"\r\n";
	}
	if (IsOpenM2B())
	{
		strReturn = strReturn + "m-b:" + m_connectM2B.getConnectString()+"\r\n";
	}
	if (IsOpenM2M())
	{
		strReturn = strReturn + "m-m:" + m_connectM2M.getConnectString()+"\r\n";
	}
	return strReturn;
}

bool CConnectionManage::WatchConnect()
{
		m_hCloseEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
		if (m_hCloseEvent == NULL)
		{
			return false;
		}
		HANDLE hThread;
		UINT uiThreadId = 0;
		hThread = (HANDLE)_beginthreadex(NULL,	// Security attributes
								  0,	// stack
    		ConnectionCheckThreadProc,	// Thread proc
								this,	// Thread param
					CREATE_SUSPENDED,	// creation mode
						&uiThreadId);	// Thread ID
//		TRACE("hThread WatchConnect %d %d", hThread, this);

		if ( NULL != hThread)
		{
			//SetThreadPriority(hThread, THREAD_PRIORITY_HIGHEST);
			ResumeThread( hThread );
			m_hThread = hThread;
//				return true;
		}

		HANDLE hSendThread;
		UINT uiSendThreadId = 1;
		hSendThread = (HANDLE)_beginthreadex(NULL,	// Security attributes
								  0,	// stack
    		SendCheckThreadProc,	// Thread proc
								this,	// Thread param
					CREATE_SUSPENDED,	// creation mode
						&uiSendThreadId);	// Thread ID

		if ( NULL != hSendThread)
		{
			//SetThreadPriority(hThread, THREAD_PRIORITY_HIGHEST);
			ResumeThread( hSendThread );
			m_hSendThread = hSendThread;
//				return true;
		}

	return false;
}


UINT WINAPI CConnectionManage::ConnectionCheckThreadProc(LPVOID pParam)
{
	CConnectionManage* pThis = reinterpret_cast<CConnectionManage*>( pParam );
	_ASSERTE( pThis != NULL );

	pThis->ConnectionCheck();

	return 1L;
} // end SocketThreadProc



CMessageItem* CConnectionManage::getFirstSendMessage()
{
	CMessageItem* mi = NULL;
	lockSemaphore();
	if (sendList.IsEmpty())
	{
		return NULL;
	}
	else
	{
		POSITION point,currentPoint;
		point = sendList.GetHeadPosition();
		currentPoint = point;
		mi = (CMessageItem *)sendList.GetNext(point);
		if (mi != NULL)
		{
			sendList.RemoveAt(currentPoint);
		}
		unlockSemaphore();
		return mi;
	}
	unlockSemaphore();
	return NULL;
}

void CConnectionManage::addSendMessage(CMessageItem* messageItem, bool bTail)
{
	if(messageItem != NULL)
	{		
		if (messageItem->nSendCount <= 3)
		{
			CMessageItem * miInsert = new CMessageItem();
			*miInsert = *messageItem;
			miInsert->nSendCount = miInsert->nSendCount + 1;
			lockSemaphore();
			if(bTail){
				sendList.AddTail(miInsert);
			}else{
				sendList.AddHead(miInsert);
			}
			unlockSemaphore();
		}
	}

}

CMessageItem* CConnectionManage::getFirstReceiveMessage()
{
	CMessageItem* mi;
	if (receiveList.IsEmpty())
	{
		return NULL;
	}
	else
	{
		POSITION point,currentPoint;
		point = sendList.GetHeadPosition();
		currentPoint = point;
		mi = (CMessageItem *)receiveList.GetNext(point);
		if (mi != NULL)
		{
			receiveList.RemoveAt(currentPoint);
		}
		return mi;
	}
	return NULL;
}

void CConnectionManage::addReceiveMessage(CMessageItem* messageItem)
{
	if(messageItem != NULL)
	{
		CMessageItem * miInsert = new CMessageItem();
		*miInsert = *messageItem;
		receiveList.AddTail(miInsert);
	}
}




UINT WINAPI CConnectionManage::SendCheckThreadProc(LPVOID pParam)
{
	CConnectionManage* pThis = reinterpret_cast<CConnectionManage*>( pParam );
	_ASSERTE( pThis != NULL );

	pThis->SendCheck();

	return 1L;
} // end SocketThreadProc

UINT WINAPI CConnectionManage::ReceiveCheckThreadProc(LPVOID pParam)
{
	CConnectionManage* pThis = reinterpret_cast<CConnectionManage*>( pParam );
	_ASSERTE( pThis != NULL );

	pThis->ReceiveCheck();

	return 1L;
} // end SocketThreadProc


void CConnectionManage::SendCheck() 
{
	while (m_bRun == true)
	{
		while (!sendList.IsEmpty())
		{
			CMessageItem* mi = getFirstSendMessage();
			if (mi != NULL)
			{
				if(WriteCommDetail(mi->Buffertype, mi->BufferVersion, mi->lpBuffer, mi->dwCount, mi->dwTimeout) == -1)
				{
					addSendMessage(mi);
				}
				else
				{
	//				TRACE("write %d %d %d\r\n", mi->Buffertype, mi->BufferVersion, mi->dwCount);
				}
				delete mi;
			}
			Sleep(0);
		}
		WaitForSingleObject(m_hCloseEvent, 1L);
	}
}


void CConnectionManage::ReceiveCheck() 
{
	while (m_bRun == true)
	{
		CMessageItem* mi = getFirstReceiveMessage();
		if (mi != NULL)
		{

		}
		WaitForSingleObject(m_hCloseEvent, 10L);
	}
}



void CConnectionManage::waitSemaphore()
{
	while(this->SingleLock->IsLocked())
	{
		WaitForSingleObject(m_hCloseEvent, 1L);
	}
}

void CConnectionManage::lockSemaphore()
{	
	if(this->SingleLock->IsLocked())
	{
		waitSemaphore();
	}
	this->SingleLock->Lock();
}

void CConnectionManage::unlockSemaphore()
{
	this->SingleLock->Unlock();
}


