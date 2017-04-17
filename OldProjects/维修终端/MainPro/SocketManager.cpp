// SocketManager.cpp: implementation of the CSocketManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <atlconv.h>
//#include "SocketManager.h"
//#include "SyncSocket.h"
#include "mainfrm.h"
//#include "StatusLink.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
/*
const UINT EVT_CONSUCCESS = 0x0000;	// Connection established
const UINT EVT_CONFAILURE = 0x0001;	// General failure - Wait Connection failed
const UINT EVT_CONDROP	  = 0x0002;	// Connection dropped
const UINT EVT_ZEROLENGTH = 0x0003;	// Zero length message
*/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CSocketManager::CSocketManager()
: m_pMsgView(NULL),m_pMsgWnd(NULL)
{

}

CSocketManager::~CSocketManager()
{

}


void CSocketManager::DisplayData(const LPBYTE lpData, DWORD dwCount, const SockAddrIn& sfrom)
{
	CString strData;
	memcpy(strData.GetBuffer(dwCount), A2CT((LPSTR)lpData), dwCount);
	strData.ReleaseBuffer();

	SockAddrIn addrin;
	GetPeerName( addrin );	
	LONG  uAddr = addrin.GetIPAddr();
	BYTE* sAddr = (BYTE*) &uAddr;
	short nPort = ntohs( addrin.GetPort() );
	CString strAddr;
	// Address is stored in network format...
	strAddr.Format(_T("%u.%u.%u.%u"),
				(UINT)(sAddr[0]), (UINT)(sAddr[1]),
				(UINT)(sAddr[2]), (UINT)(sAddr[3]));	

	if (m_pMsgView != NULL)
	{
		CMessageItem mi;
		mi.dwCount = dwCount;
		mi.Buffertype = BYTE(*lpData);
		mi.BufferVersion =  BYTE(*(lpData+1));
		mi.dwTimeout = INFINITE;
		mi.strIPM = strAddr;
		memcpy(mi.lpBuffer, lpData, dwCount);

		(((CMainFrame *)m_pMsgView)->m_receiveQueue).addReceiveMessage(&mi,true);
	}


}


void CSocketManager::AppendMessage(LPCTSTR strText)
{

	if (NULL == m_pMsgWnd)
		return;

	CString strTextMain = strText;

}


void CSocketManager::SetMessageWindow(CWnd* pMsgView)
{
	m_pMsgView = pMsgView;
}

void  CSocketManager::SetMessageWnd(CWnd* pMsgWnd)
{
	m_pMsgWnd = pMsgWnd;
}


void CSocketManager::OnDataReceived(const LPBYTE lpBuffer, DWORD dwCount)
{
	LPBYTE lpData = lpBuffer;
	SockAddrIn origAddr;
	stMessageProxy msgProxy;
	if (IsSmartAddressing())
	{
		dwCount = __min(sizeof(msgProxy), dwCount);
		memcpy(&msgProxy, lpBuffer, dwCount);
		origAddr = msgProxy.address;
		if (IsServer())
		{
			// broadcast message to all
			msgProxy.address.sin_addr.s_addr = htonl(INADDR_BROADCAST);
			WriteComm(255,1,(const LPBYTE)&msgProxy, dwCount, 0L);
		}
		dwCount -= sizeof(msgProxy.address);
		lpData = msgProxy.byData;
	}
	
	if (lpBuffer[0] == 0xe0)
	{
//		CSyncSocket * pReceive = CSyncSocket::GetInstance();
//		pReceive->receiveBuffer(lpBuffer+4,dwCount-4);
	}
	else if (lpBuffer[0] == 0xd0)
	{
//		CStatusLink * pReceive = CStatusLink::GetInstance();
//		pReceive->ReceiveStatus(lpBuffer,dwCount);
	}
	else
	{
		// Display data to message list
		DisplayData( lpData, dwCount, origAddr );
	}
	// Display data to message list
//	DisplayData( lpData, dwCount, origAddr );
}

///////////////////////////////////////////////////////////////////////////////
// OnEvent
// Send message to parent window to indicate connection status
void CSocketManager::OnEvent(UINT uEvent)
{
	if (NULL == m_pMsgView)
		return;

	CWnd* pParent = m_pMsgView;
	if (!::IsWindow( pParent->GetSafeHwnd()))
		return;

	

	switch( uEvent )
	{
		case EVT_CONSUCCESS:
//			AppendMessage( _T("Connection Established\r\n"),1 );
			break;
		case EVT_CONFAILURE:
			if (!m_bConnect)
				return;
			m_bConnect = false;
//			AppendMessage( _T("Connection Failed\r\n"),1 );
//	StopComm();
			break;
		case EVT_CONDROP:
			if (!m_bConnect)
				return;
			m_bConnect = false;
//			AppendMessage( _T("Connection Abandonned\r\n"),1 );
//	StopComm();
			break;
		case EVT_ZEROLENGTH:
//			AppendMessage( _T("Zero Length Message\r\n"),1 );
			break;
		default:
//			TRACE("Unknown Socket event\n");
			break;
	}

	pParent->PostMessage( WM_UPDATE_CONNECTION, uEvent, (LPARAM) this);

}

CString CSocketManager::getConnectString()
{
	if (IsOpen())
	{
		SockAddrIn addrin;
		GetPeerName( addrin );	
		LONG  uAddr = addrin.GetIPAddr();
		BYTE* sAddr = (BYTE*) &uAddr;
		short nPort = ntohs( addrin.GetPort() );
		CString strAddr;
		// Address is stored in network format...
		strAddr.Format(_T("IP: %u.%u.%u.%u, Port: %d"),
					(UINT)(sAddr[0]), (UINT)(sAddr[1]),
					(UINT)(sAddr[2]), (UINT)(sAddr[3]), nPort);	
		return strAddr;
	}
	else
	{
		return "NULL";
	}
}
