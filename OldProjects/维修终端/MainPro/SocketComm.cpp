///////////////////////////////////////////////////////////////////////////////
//	File:		SocketComm.cpp
//	Version:	1.0
//
//	Author:		peng li
//	E-mail:		magicscape@yahoo.com.cn/magicscape@sina.com.cn
//
//	Implementation of the CSocketComm and associated classes.
//
//	
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <process.h>
#include <crtdbg.h>
#include "SocketComm.h"
#include <fcntl.h>

const DWORD DEFAULT_TIMEOUT = 10L;
struct stMessageProxy
{
  SockAddrIn	address;
  BYTE			data[BUFFER_SIZE];
};

///////////////////////////////////////////////////////////////////////////////
// SockAddrIn Struct

///////////////////////////////////////////////////////////////////////////////
// Copy
SockAddrIn& SockAddrIn::Copy(const SockAddrIn& sin)
{
	memcpy(this, &sin, Size());
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
// IsEqual
bool SockAddrIn::IsEqual(const SockAddrIn& sin)
{
	// Is it Equal? - ignore 'sin_zero'
	return (memcmp(this, &sin, Size()-sizeof(sin_zero)) == 0);
}

///////////////////////////////////////////////////////////////////////////////
// IsGreater
bool SockAddrIn::IsGreater(const SockAddrIn& sin)
{
	// Is it Greater? - ignore 'sin_zero'
	return (memcmp(this, &sin, Size()-sizeof(sin_zero)) > 0);
}

///////////////////////////////////////////////////////////////////////////////
// IsLower
bool SockAddrIn::IsLower(const SockAddrIn& sin)
{
	// Is it Lower? - ignore 'sin_zero'
	return (memcmp(this, &sin, Size()-sizeof(sin_zero)) < 0);
}

///////////////////////////////////////////////////////////////////////////////
// CreateFrom
bool SockAddrIn::CreateFrom(LPCTSTR sAddr, LPCTSTR sService, int nFamily /*=AF_INET*/)
{
	Clear();
	sin_addr.s_addr = htonl( CSocketComm::GetIPAddress(sAddr) );
	sin_port = htons( CSocketComm::GetPortNumber( sService ) );
	sin_family = nFamily;
	return !IsNull();
}

HANDLE CSocketComm::m_hPostMutex = NULL;
///////////////////////////////////////////////////////////////////////////////
// Construct & Destruct
CSocketComm::CSocketComm() :
	m_bServer(false), m_bSmartAddressing(false), m_bBroadcast(false),
	m_hComm(INVALID_HANDLE_VALUE), m_hThread(NULL), m_hMutex(NULL),
	m_bActive(false),m_bConnect(false)
{

}

CSocketComm::~CSocketComm()
{
	StopComm();
}

///////////////////////////////////////////////////////////////////////////////
// Members
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// IsOpenEx
bool CSocketComm::IsOpen() const
{
	return (( INVALID_HANDLE_VALUE != m_hComm )&&(false != m_bConnect));
}

bool CSocketComm::IsOpenEx() const
{
	bool bIsOpenEx = (INVALID_HANDLE_VALUE != m_hComm);
	if (bIsOpenEx)
	{

	}
	else
	{
//		TRACE("IsOpenEx false! %d %d\r\n", m_hComm, this);
	}
	return bIsOpenEx;
}


///////////////////////////////////////////////////////////////////////////////
// IsStart
bool CSocketComm::IsStart() const
{
	return ( NULL != m_hThread );
}


///////////////////////////////////////////////////////////////////////////////
// IsServer
bool CSocketComm::IsServer() const
{
	return m_bServer;
}


///////////////////////////////////////////////////////////////////////////////
// IsBroadcast
bool CSocketComm::IsBroadcast() const
{
	return m_bBroadcast;
}


///////////////////////////////////////////////////////////////////////////////
// IsSmartAddressing
bool CSocketComm::IsSmartAddressing() const
{
	return m_bSmartAddressing;
}


///////////////////////////////////////////////////////////////////////////////
// GetSocket
SOCKET CSocketComm::GetSocket() const
{
	return (SOCKET) m_hComm;
}


///////////////////////////////////////////////////////////////////////////////
// LockList
void CSocketComm::LockList()
{
	if (NULL != m_hMutex)
	{
		WaitForSingleObject(m_hMutex, 5000);
	}
	else
	{
//		TRACE("mute null\r\n");
	}
}


///////////////////////////////////////////////////////////////////////////////
// UnlockList
void CSocketComm::UnlockList()
{
	if (NULL != m_hMutex)
		ReleaseMutex(m_hMutex);
	else
	{
//		TRACE("mute null release\r\n");
	}
}


///////////////////////////////////////////////////////////////////////////////
// AddToList
void CSocketComm::AddToList(const SockAddrIn& saddr_in)
{
	LockList();
	m_AddrList.insert( m_AddrList.end(), saddr_in );
	UnlockList();
}

///////////////////////////////////////////////////////////////////////////////
// RemoveFromList
void CSocketComm::RemoveFromList(const SockAddrIn& saddr_in)
{
	LockList();
	m_AddrList.remove( saddr_in );
	UnlockList();
}

///////////////////////////////////////////////////////////////////////////////
// SetServerState
void CSocketComm::SetServerState(bool bServer)
{
	if (!IsStart())
		m_bServer = bServer;
}


///////////////////////////////////////////////////////////////////////////////
// SetSmartAddressing : Address is included with message
void CSocketComm::SetSmartAddressing(bool bSmartAddressing)
{
	if (!IsStart())
		m_bSmartAddressing = bSmartAddressing;
}

///////////////////////////////////////////////////////////////////////////////
// OnDataReceived
///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//				This function is PURE Virtual, you MUST overwrite it.  This is
//				called every time new data is available.
// PARAMETERS:
///////////////////////////////////////////////////////////////////////////////
void CSocketComm::OnDataReceived(const LPBYTE lpBuffer, DWORD dwCount)
{
}


///////////////////////////////////////////////////////////////////////////////
// OnEvent
///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//				This function reports events & errors
// PARAMETERS:
//		UINT uEvent: can be one of the event value EVT_(events)
///////////////////////////////////////////////////////////////////////////////
void CSocketComm::OnEvent(UINT uEvent)
{
}

///////////////////////////////////////////////////////////////////////////////
// GetPortNumber
///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//				Returns a port number based on service name or port number string
// PARAMETERS:
//	LPCTSTR strServiceName: Service name or port string
///////////////////////////////////////////////////////////////////////////////
USHORT CSocketComm::GetPortNumber( LPCTSTR strServiceName )
{
	LPSERVENT	lpservent;
	USHORT		nPortNumber = 0;

	if ( _istdigit( strServiceName[0] ) ) {
		nPortNumber = (USHORT) _ttoi( strServiceName );
	}
	else {
#ifdef _UNICODE
		char pstrService[HOSTNAME_SIZE];
		WideCharToMultiByte(CP_ACP, 0, pstrService, -1, strServiceName, sizeof(pstrService), NULL, NULL );
#else
		LPCTSTR pstrDevice = strServiceName;
#endif
		// Convert network byte order to host byte order
		if ( (lpservent = getservbyname( pstrDevice, NULL )) != NULL )
			nPortNumber = ntohs( lpservent->s_port );
	}

	return nPortNumber;
}


///////////////////////////////////////////////////////////////////////////////
// GetIPAddress
///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//		Returns an IP address.
//			- It tries to convert the string directly
//			- If that fails, it tries to resolve it as a hostname
// PARAMETERS:
//	LPCTSTR strHostName: host name to get IP address
///////////////////////////////////////////////////////////////////////////////
ULONG CSocketComm::GetIPAddress( LPCTSTR strHostName )
{
	LPHOSTENT	lphostent;
	ULONG		uAddr = INADDR_NONE;
	TCHAR       strLocal[HOSTNAME_SIZE] = { 0 };

	// if no name specified, get local
	if ( NULL == strHostName )
	{
		GetLocalName(strLocal, sizeof(strLocal));
		strHostName = strLocal;
	}

#ifdef _UNICODE
	char strHost[HOSTNAME_SIZE] = { 0 };
	WideCharToMultiByte(CP_ACP, 0, strHostName, -1, strHost, sizeof(strHost), NULL, NULL );
#else
	LPCTSTR strHost = strHostName;
#endif

	// Check for an Internet Protocol dotted address string
	uAddr = inet_addr( strHost );

	if ( (INADDR_NONE == uAddr) && (strcmp( strHost, "255.255.255.255" )) )
	{
		// It's not an address, then try to resolve it as a hostname
		if ( lphostent = gethostbyname( strHost ) )
			uAddr = *((ULONG *) lphostent->h_addr_list[0]);
	}
	
	return ntohl( uAddr );
}


///////////////////////////////////////////////////////////////////////////////
// GetLocalName
///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//				Get local computer name.  Something like: "mycomputer.myserver.net"
// PARAMETERS:
//	LPTSTR strName: name of the computer is returned here
//	UINT nSize: size max of buffer "strName"
///////////////////////////////////////////////////////////////////////////////
bool CSocketComm::GetLocalName(LPTSTR strName, UINT nSize)
{
	if (strName != NULL && nSize > 0)
	{
		char strHost[HOSTNAME_SIZE] = { 0 };

		// get host name, if fail, SetLastError is set
		if (SOCKET_ERROR != gethostname(strHost, sizeof(strHost)))
		{
			struct hostent* hp;
			hp = gethostbyname(strHost);
			if (hp != NULL)	{
				strcpy(strHost, hp->h_name);
			}

			// check if user provide enough buffer
			if (strlen(strHost) > nSize)
			{
				SetLastError(ERROR_INSUFFICIENT_BUFFER);
				return false;
			}

			// Unicode conversion
#ifdef _UNICODE
			return (0 != MultiByteToWideChar(CP_ACP, 0, strHost, -1, strName, nSize, NULL, NULL ));
#else
			_tcscpy(strName, strHost);
			return true;
#endif
		}
	}
	else
		SetLastError(ERROR_INVALID_PARAMETER);
	return false;
}


///////////////////////////////////////////////////////////////////////////////
// GetLocalAddress
///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//				Get TCP address of local computer in dot format ex: "127.0.0.0"
// PARAMETERS:
//	LPTSTR strAddress: pointer to hold address string, must be long enough
//	UINT nSize: maximum size of this buffer
///////////////////////////////////////////////////////////////////////////////
bool CSocketComm::GetLocalAddress(LPTSTR strAddress, UINT nSize)
{
	// Get computer local address
	if (strAddress != NULL && nSize > 0)
	{
		char strHost[HOSTNAME_SIZE] = { 0 };

		// get host name, if fail, SetLastError is called
		if (SOCKET_ERROR != gethostname(strHost, sizeof(strHost)))
		{
			struct hostent* hp;
			hp = gethostbyname(strHost);
			if (hp != NULL && hp->h_addr_list[0] != NULL)
			{
				// Address is four bytes (32-bit)
				if ( hp->h_length < 4)
					return false;

				// Convert address to . format
				strHost[0] = 0;

				// Create Address string
				sprintf(strHost, "%u.%u.%u.%u",
					(UINT)(((PBYTE) hp->h_addr_list[0])[0]),
					(UINT)(((PBYTE) hp->h_addr_list[0])[1]),
					(UINT)(((PBYTE) hp->h_addr_list[0])[2]),
					(UINT)(((PBYTE) hp->h_addr_list[0])[3]));

				// check if user provide enough buffer
				if (strlen(strHost) > nSize)
				{
					SetLastError(ERROR_INSUFFICIENT_BUFFER);
					return false;
				}

			// Unicode conversion
#ifdef _UNICODE
				return (0 != MultiByteToWideChar(CP_ACP, 0, strHost, -1, strAddress,
					nSize, NULL, NULL ));
#else
				_tcscpy(strAddress, strHost);
				return true;
#endif
			}
		}
	}
	else
		SetLastError(ERROR_INVALID_PARAMETER);
	return false;
}


///////////////////////////////////////////////////////////////////////////////
// WaitForConnection
///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//				Wait for a network connection.  Only for connection type of socket
//				This function may fail, in this case it returns "INVALID_SOCKET"
// PARAMETERS:
//	SOCKET sock: a socket capable of receiving new connection (TCP: SOCK_STREAM)
///////////////////////////////////////////////////////////////////////////////
SOCKET CSocketComm::WaitForConnection(SOCKET sock)
{
	// Accept an incoming connection - blocking
	// no information about remote address is returned
	return accept(sock, 0, 0);
}


///////////////////////////////////////////////////////////////////////////////
// ShutdownConnection
///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//				Shutdown a connection and close socket.  This will force all
//				transmission/reception to fail.
// PARAMETERS:
//	SOCKET sock: Socket to close
///////////////////////////////////////////////////////////////////////////////
bool CSocketComm::ShutdownConnection(SOCKET sock)
{
	shutdown(sock, SD_BOTH);
	if (0 == closesocket( sock ))
	{
		return true;
	}
	else
	{
		int nError;
		nError = WSAGetLastError();
//		TRACE("-1 recv lpBuffer %d\r\n",nError);
		return false;
	}
}


///////////////////////////////////////////////////////////////////////////////
// GetSockName
///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//				retrieves the local name for a socket
// PARAMETERS:
//	SockAddrIn& saddr_in: object to store address
///////////////////////////////////////////////////////////////////////////////
bool CSocketComm::GetSockName(SockAddrIn& saddr_in)
{
	if (IsOpenEx())
	{
		int namelen = saddr_in.Size();
		return (SOCKET_ERROR != getsockname(GetSocket(), (LPSOCKADDR)saddr_in, &namelen));
	}

	return false;
}


///////////////////////////////////////////////////////////////////////////////
// GetPeerName
///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//				retrieves the name of the peer to which a socket is connected
// PARAMETERS:
//	SockAddrIn& saddr_in: object to store address
///////////////////////////////////////////////////////////////////////////////
bool CSocketComm::GetPeerName(SockAddrIn& saddr_in)
{
	if (IsOpenEx())
	{
		int namelen = saddr_in.Size();
		return (SOCKET_ERROR != getpeername(GetSocket(), (LPSOCKADDR)saddr_in, &namelen));
	}

	return false;
}


///////////////////////////////////////////////////////////////////////////////
// CreateSocket
///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//				This function creates a new socket for connection (SOCK_STREAM)
//				or an connectionless socket (SOCK_DGRAM).  A connectionless
//				socket should not call "accept()" since it cannot receive new
//				connection.  This is used as SERVER socket
// PARAMETERS:
//	LPCTSTR strServiceName: Service name or port number
//	int nFamily: address family to use (set to AF_INET)
//	int nType: type of socket to create (SOCK_STREAM, SOCK_DGRAM)
//	UINT uOptions: other options to use
///////////////////////////////////////////////////////////////////////////////
bool CSocketComm::CreateSocket(LPCTSTR strip, LPCTSTR strServiceName, int nFamily, int nType, UINT uOptions /* = 0 */)
{
	// Socket is already opened
	if ( IsOpenEx() )
		return false;

	// Create a Socket that is bound to a specific service provide
	// nFamily: (AF_INET)
	// nType: (SOCK_STREAM, SOCK_DGRAM)
	SOCKET sock = socket(nFamily, nType, 0);
	if (INVALID_SOCKET != sock)
	{
		if (uOptions & SO_REUSEADDR)
		{
			// Inform Windows Sockets provider that a bind on a socket should not be disallowed
			// because the desired address is already in use by another socket
			BOOL optval = TRUE;
			if ( SOCKET_ERROR == setsockopt( sock, SOL_SOCKET, SO_REUSEADDR, (char *) &optval, sizeof( BOOL ) ) )
			{
				closesocket( sock );
				return false;
			}
		}

		if (nType == SOCK_DGRAM)
		{
			if (uOptions & SO_BROADCAST)
			{
				// Inform Windows Sockets provider that broadcast messages are allowed
				BOOL optval = TRUE;
				if ( SOCKET_ERROR == setsockopt( sock, SOL_SOCKET, SO_BROADCAST, (char *) &optval, sizeof( BOOL ) ) )
				{
					closesocket( sock );
					return false;
				}

				// we may proceed
				m_bBroadcast = true;
			}

			// we need mutex only for UDP - broadcast socket
		}



		// Associate a local address with the socket
		SockAddrIn sockAddr;
		sockAddr.CreateFrom(strip, strServiceName, nFamily);

		if ( SOCKET_ERROR == bind(sock, (LPSOCKADDR)sockAddr, sockAddr.Size()))
		{
			closesocket( sock );
			m_bBroadcast = false;
			return false;
		}

		// Listen to the socket, only valid for connection socket
		if (SOCK_STREAM == nType)
		{
			if ( SOCKET_ERROR == listen(sock, SOMAXCONN))
			{
				closesocket( sock );
				return false;
			}
		}

		// Success, now we may save this socket
		m_hComm = (HANDLE) sock;
		m_bActive = true;
	}

	return (INVALID_SOCKET != sock);
}





///////////////////////////////////////////////////////////////////////////////
// ConnectTo
///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//				Establish connection with a server service or port
// PARAMETERS:
//	LPCTSTR strDestination: hostname or address to connect (in .dot format)
//	LPCTSTR strServiceName: Service name or port number
//	int nFamily: address family to use (set to AF_INET)
//	int nType: type of socket to create (SOCK_STREAM, SOCK_DGRAM)
///////////////////////////////////////////////////////////////////////////////
bool CSocketComm::ConnectTo(LPCTSTR strDestination, LPCTSTR strServiceName, LPCTSTR strSource, LPCTSTR strSourceServiceName, int nFamily, int nType)
{
	int i;
	unsigned long block = 1;
        DWORD bf;
	// Socket is already opened
	if ( IsOpenEx() )
		return false;


	// Create a Socket that is bound to a specific service provide
	// nFamily: (AF_INET)
	// nType: (SOCK_STREAM, SOCK_DGRAM)
	SOCKET sock = socket(nFamily, nType, 0);
	if (INVALID_SOCKET != sock)
	{
		// Associate a local address with the socket
		SockAddrIn sockAddr;
//		if (false == sockAddr.CreateFrom(strSource, strSourceServiceName, nFamily))
		if (false == sockAddr.CreateFrom(strSource, TEXT("0"), nFamily))
		{
			closesocket( sock );
			return false;
		}

		if ( SOCKET_ERROR == bind(sock, (LPSOCKADDR)sockAddr, sockAddr.Size() ))
		{
			closesocket( sock );
			return false;
		}

		// Now get destination address & port
		sockAddr.CreateFrom( strDestination, strServiceName);

        ioctlsocket(sock,FIONBIO, &block); 

		// try to connect - if fail, server not ready
		if (SOCKET_ERROR == connect( sock, (LPSOCKADDR)sockAddr, sockAddr.Size()))
		{
			int nResult = WSAGetLastError();
              if (nResult == WSAEWOULDBLOCK){// it is in the connect process 
                        struct timeval tv; 
                        fd_set writefds; 
                        tv.tv_sec = 0; 
                        tv.tv_usec = 300; 
                        FD_ZERO(&writefds); 
                        FD_SET(sock, &writefds); 
						int nError = select(sock+1,NULL,&writefds,NULL,&tv);
                        if(nError>0){ 
                                int len=sizeof(int); 
                               //下面的一句一定要，主要针对防火墙 
								i = sizeof(int);
                                getsockopt(sock, SOL_SOCKET, SO_ERROR,(char *)&bf,&i); 
                                if((bf!=0)||(i!=sizeof(int)))
								{
									closesocket( sock );
									return false;
								}
                        }
						else   
						{
							closesocket( sock );
							return false;
						}
                }
				else
				{
					closesocket( sock );
					return false;
				}
		}
		block = 0;
        ioctlsocket(sock,FIONBIO, &block); 
		// Success, now we may save this socket

/*
		if (SOCKET_ERROR == connect( sock, (LPSOCKADDR)sockAddr, sockAddr.Size()))
		{
					closesocket( sock );
					return false;
		}
*/

		m_hComm = (HANDLE) sock;

		OnEvent( EVT_CONSUCCESS ); // connect

		m_bActive = true;
	}
	return (INVALID_SOCKET != sock);
}


///////////////////////////////////////////////////////////////////////////////
// CloseComm
///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//		Close Socket Communication
// PARAMETERS:
//		None
///////////////////////////////////////////////////////////////////////////////
void CSocketComm::CloseComm()
{
	if (IsOpenEx())
	{
		bool bClose = ShutdownConnection((SOCKET)m_hComm);
		if (!bClose)
		{
			int nResult = WSAGetLastError();
		}
		m_hComm = INVALID_HANDLE_VALUE;
		m_bActive = false;
		m_bBroadcast = false;
	}
}


///////////////////////////////////////////////////////////////////////////////
// WatchComm
///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//		Starts Socket Communication Working thread
// PARAMETERS:
//		None
///////////////////////////////////////////////////////////////////////////////
bool CSocketComm::WatchComm()
{
	if (!IsStart())
	{
		if (IsOpenEx())
		{
			m_hMutex = CreateMutex(NULL, FALSE, NULL);
			if (NULL == m_hMutex)
			{
				return false;
			}

			m_hPostMutex = CreateMutex(NULL, FALSE, NULL);
			if (NULL == m_hPostMutex)
			{
				return false;
			}
			
			HANDLE hThread;
			UINT uiThreadId = 0;
			hThread = (HANDLE)_beginthreadex(NULL,	// Security attributes
									  0,	// stack
						SocketThreadProc,	// Thread proc
									this,	// Thread param
						CREATE_SUSPENDED,	// creation mode
							&uiThreadId);	// Thread ID
		   //TRACE("CSocketComm=%x\r\n",uiThreadId);
//			TRACE("hThread CSocketComm::WatchComm %d %d", hThread, m_hComm);

			if ( NULL != hThread)
			{
				//SetThreadPriority(hThread, THREAD_PRIORITY_HIGHEST);
				ResumeThread( hThread );
				m_hThread = hThread;
				return true;
			}
			else
			{
				if (m_hMutex != NULL)
				{
					CloseHandle(m_hMutex);
					m_hMutex = NULL;
				}
			}



		}
	}
	return false;
}


///////////////////////////////////////////////////////////////////////////////
// StopComm
///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//		Close Socket and Stop Communication thread
// PARAMETERS:
//		None
///////////////////////////////////////////////////////////////////////////////
void CSocketComm::StopComm()
{
//	TRACE("StopComm %d\r\n",m_hComm);

	m_bConnect = false;

//	TRACE("CloseComm %d\r\n",m_hComm);
	// Close Socket
	if (IsOpenEx())
	{
		CloseComm();
	}


//	TRACE("Kill Thread %d\r\n",m_hComm);
	// Kill Thread
	if (IsStart())
	{
//		TRACE("Kill Thread IsStart() %d %d\r\n",m_hComm,this);
		if (WaitForSingleObject(m_hThread, 300L) == WAIT_TIMEOUT)
		{
//			TRACE("WaitForSingleObject IsStart() %d %d\r\n",m_hComm,this);
			TerminateThread(m_hThread, 1L);
		}
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	
//	TRACE(" Clear Address list %d\r\n",m_hComm);
	// Clear Address list
	if (!m_AddrList.empty())
		m_AddrList.clear();



//	TRACE("m_hMutex %d\r\n",m_hComm);
	// Destroy Synchronization objects
	if (NULL != m_hMutex)
	{
		CloseHandle( m_hMutex );
		m_hMutex = NULL;
	}
	if (NULL != m_hPostMutex)
	{
		CloseHandle( m_hPostMutex );
		m_hPostMutex = NULL;
	}
//	TRACE("StopComm end %d\r\n",m_hComm);
}


///////////////////////////////////////////////////////////////////////////////
// ReadComm
///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//		Reads the Socket Communication
// PARAMETERS:
//		LPBYTE lpBuffer: buffer to place new data
//		DWORD dwSize: maximum size of buffer
//		DWORD dwTimeout: timeout to use in millisecond
///////////////////////////////////////////////////////////////////////////////
DWORD CSocketComm::ReadComm(LPBYTE lpBuffer, DWORD dwSize, DWORD dwTimeout)
{
	if (( !IsOpenEx() )||( lpBuffer == NULL ))
	{
		return -1;
	}

	BYTE typeBuf[1] = { 0 };	
	BYTE verBuf[1] = { 0 };	
	BYTE lengthBuf[2] = { 0 };	
	
int nLength;
	if (lpBuffer == NULL || dwSize < 1L)
		return 0L;

	fd_set	fdRead  = { 0 };
	TIMEVAL	stTime;
	TIMEVAL	*pstTime = NULL;

	if ( INFINITE != dwTimeout ) {
		stTime.tv_sec = dwTimeout/1000;
		stTime.tv_usec = dwTimeout % 1000;
		pstTime = &stTime;
	}

	SOCKET s = (SOCKET) m_hComm;
	// Set Descriptor
	if ( !FD_ISSET( s, &fdRead ) )
		FD_SET( s, &fdRead );

	// Select function set read timeout
	DWORD dwBytesRead = 0L;
	int res = select( s+1, &fdRead, NULL, NULL, pstTime );
	if ( res > 0)
	{
		if (IsBroadcast() || IsSmartAddressing())
		{
			SockAddrIn sockAddr;
			int nLen = sockAddr.Size();
			int nOffset = IsSmartAddressing() ? nLen : 0; // use offset for Smart addressing
			if ( dwSize < (DWORD) nOffset)	// error - buffer to small
			{
				SetLastError( ERROR_INVALID_USER_BUFFER );
				return -1L;
			}
			LPSTR lpszData = (LPSTR)(lpBuffer + nOffset);
			res = recvfrom( s, lpszData, dwSize-nOffset, 0, (LPSOCKADDR)sockAddr, &nLen);

			// clear 'sin_zero', we will ignore them with 'SockAddrIn' anyway!
			memset(&sockAddr.sin_zero, 0, sizeof(sockAddr.sin_zero));

			// Lock the list...
			LockList();
			m_AddrList.remove( sockAddr );
			
			if ( res >= 0)
			{
				// insert unique address
				m_AddrList.insert(m_AddrList.end(), sockAddr);

				if (IsSmartAddressing())
				{
					memcpy(lpBuffer, &sockAddr, sockAddr.Size());
					res += sockAddr.Size();
				}
			}

			UnlockList(); // unlock this object addresses-list
		}
		else
		{
			res = recv( s, (LPSTR)typeBuf, 1, 0 );
			if (res == -1)
			{
				int nError;
				nError = WSAGetLastError();
//				TRACE("-1 recv typeBuf %d %d %d \r\n",nError, m_hComm, m_hThread);
				return -1;
			}
			else if (res == 0)
			{
//				TRACE("res 0\r\n");
				return -1;
			}
			res = recv( s, (LPSTR)verBuf, 1, 0 );
			if (res == -1)
			{
				int nError;
				nError = WSAGetLastError();
//				TRACE("-1 recv verBuf %d %d\r\n",nError, m_hComm);
				return -1;
			}
			else if (res == 0)
			{
//				TRACE("res 2 0\r\n");
				return -1;
			}
			res = recv( s, (LPSTR)lengthBuf, 2, 0 );
			if (res == -1)
			{
				int nError;
				nError = WSAGetLastError();
//				TRACE("-1 recv lengthBuf %d %d\r\n",nError, m_hComm);
				return -1;
			}
			else if (res == 0)
			{
//				TRACE("res 3 0\r\n");
				return -1;
			}
			nLength = (*(lengthBuf+1))*256+*(lengthBuf) ;
			memcpy (lpBuffer, typeBuf, 1);
			memcpy (lpBuffer+1, verBuf, 1);
			memcpy (lpBuffer+2, lengthBuf, 2);
			if (nLength > 4096)
			{
//					TRACE("4096 recv nLength %d %d\r\n",nLength, m_hComm);
			}

			if (nLength == 0)
			{
				res = 0;
				return 0;
			}
			else
			{
				res = recv( s, (LPSTR)lpBuffer+4, nLength, 0);
				if (res == -1){
					int nError;
					nError = WSAGetLastError();
//					TRACE("-1 recv lpBuffer %d %d\r\n",nError, m_hComm);
					return -1;
				}
				else if (res == 0){
//					TRACE("res 4 0\r\n");
					return -1;
				}
			    int nResLength = res;
				while (res < nLength)
				{
					nResLength = recv( s, (LPSTR)lpBuffer+4+res, nLength-res, 0);
					if (nResLength == -1){
						int nError;
						nError = WSAGetLastError();
//						TRACE("-1 recv lpBuffer2 %d %d\r\n",nError, m_hComm);
						return -1;
					}
					else if (nResLength == 0){
//						TRACE("res 5 0\r\n");
						return -1;
					}
					res += nResLength;
//					TRACE("res<nLength %d %d %d %d %d\r\n", nLength, nResLength, res , m_hComm, this);
				}
			}
			//TRACE("%d %d %s\r\n",nLength,res, lpBuffer+4);
		}

		dwBytesRead = (DWORD)((res >= 0)?(res+4) : (-1L));
	}


	return dwBytesRead;
}


///////////////////////////////////////////////////////////////////////////////
// WriteComm
///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//		Writes data to the Socket Communication
// PARAMETERS:
//		const LPBYTE lpBuffer: data to write
//		DWORD dwCount: maximum characters to write
//		DWORD dwTimeout: timeout to use in millisecond
///////////////////////////////////////////////////////////////////////////////
DWORD CSocketComm::WriteComm(BYTE Buffertype, BYTE BufferVersion, const LPBYTE lpBuffer, DWORD dwCount, DWORD dwTimeout)
{
	// Accept 0 bytes message
	if (!IsOpen() || NULL == lpBuffer)
	{
//		TRACE("IsOpen write Comm failure !!!!!!!!!!!!!!\r\n");
		return -1L;
	}

	fd_set	fdWrite  = { 0 };
	TIMEVAL	stTime;
	TIMEVAL	*pstTime = NULL;

	if ( INFINITE != dwTimeout ) {
		stTime.tv_sec = dwTimeout/1000;
		stTime.tv_usec = dwTimeout % 1000;
		pstTime = &stTime;
	}

	BYTE lpBufferTmp[BUFFER_SIZE] = {0};
	lpBufferTmp[0] = Buffertype;
	lpBufferTmp[1] = BufferVersion;
	memcpy(lpBufferTmp+2, &dwCount, 2);
	memcpy(lpBufferTmp+4, lpBuffer, dwCount);

	SOCKET s = (SOCKET) m_hComm;
	// Set Descriptor
	if ( !FD_ISSET( s, &fdWrite ) )
		FD_SET( s, &fdWrite );

	// Select function set write timeout
	DWORD dwBytesWritten = 0L;
	int res = select( s+1, NULL, &fdWrite, NULL, pstTime );
	if ( res > 0)
	{
		// Send message to peer or broadcast it
		if (IsBroadcast() || IsSmartAddressing())
		{
			// use offset for Smart addressing
			int nOffset = IsSmartAddressing() ? sizeof(SOCKADDR_IN) : 0;
			if (IsSmartAddressing())
			{
				if ( dwCount < sizeof(SOCKADDR_IN))	// error - buffer to small
				{
					SetLastError( ERROR_INVALID_USER_BUFFER );
					return -1L;
				}

				// read socket address from buffer
				SockAddrIn sockAddr;
				sockAddr.SetAddr((PSOCKADDR_IN) lpBuffer);

				// Get Address and send data
				if (sockAddr.sin_addr.s_addr != htonl(INADDR_BROADCAST))
				{
					LPSTR lpszData = (LPSTR)(lpBuffer + nOffset);
					res = sendto( s, lpszData, dwCount-nOffset, 0,
						(LPSOCKADDR)sockAddr, sockAddr.Size());
					dwBytesWritten = (DWORD)((res >= 0)?(res) : (-1));
					return dwBytesWritten;
				}
			}

			// Broadcast send to all connected-peer

			CSockAddrList::iterator iter = m_AddrList.begin();
			for( ; iter != m_AddrList.end(); )
			{
				// Fix v1.3 - nOffset was missing
				res = sendto( s, (LPCSTR)&lpBuffer[nOffset], dwCount-nOffset, 0, (LPSOCKADDR)(*iter), iter->Size());
				if (res < 0)
				{
					CSockAddrList::iterator deladdr = iter;
					++iter;	// get next
					m_AddrList.erase( deladdr );
				}
				else
					++iter;	// get next
			}


			// always return success - UDP
			res = (int) dwCount - nOffset;
		}
		else // Send to peer-connection
		{
			LockList();
			res = send( s, (LPCSTR)lpBufferTmp, dwCount+4, 0);
			UnlockList();
		}

		dwBytesWritten = (DWORD)((res >= 0)?(res) : (-1));
	}

	if(dwBytesWritten == -1)
	{
		int nError;
		nError = WSAGetLastError();
//		TRACE("-1 write Comm failure result %d\r\n",nError);
		OnEvent(EVT_CONDROP);
	}

	return dwBytesWritten;
}


///////////////////////////////////////////////////////////////////////////////
// Run
///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//		This function runs the main thread loop
//		this implementation can be overloaded.
//      This function calls CSocketComm::OnDataReceived() (Virtual Function)
// PARAMETERS:
// NOTES:
//		You should not wait on the thread to end in this function or overloads
///////////////////////////////////////////////////////////////////////////////
void CSocketComm::Run()
{
	stMessageProxy stMsgProxy;
	DWORD	dwBytes  = 0L;
	DWORD	dwTimeout = DEFAULT_TIMEOUT;
	LPBYTE  lpData  = (LPBYTE)&stMsgProxy;
	DWORD	dwSize  = sizeof(stMsgProxy);

	if (!IsSmartAddressing())
	{
		lpData = stMsgProxy.data;
		dwSize = sizeof(stMsgProxy.data);
	}

	// Should we run as server mode
	if (IsServer())
	{
		if (!IsBroadcast())
		{
			SOCKET sock = (SOCKET) m_hComm;
			sock = WaitForConnection( sock );

			// Get new connection socket
			if (sock != INVALID_SOCKET)
			{
				ShutdownConnection( (SOCKET) m_hComm);
				m_hComm = (HANDLE) sock;
				m_bActive = true;
				OnEvent( EVT_CONSUCCESSED ); // connect

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

			}
			else
			{
				// Do not send event if we are closing
				int nError;
				nError = WSAGetLastError();
//				TRACE("Run WaitForConnection fail:%d %d\r\n",nError, m_hComm);
				if (IsOpenEx())
				{
//					TRACE("Run WaitForConnection fail and send fail:\r\n");
					OnEvent( EVT_CONFAILURE ); // wait fail
				}
				return;
			}
		}
	}
	else
		GetPeerName( stMsgProxy.address );


	m_bConnect = true;

	while( IsOpenEx() )
	{
		// Blocking mode: Wait for event
		dwBytes = ReadComm(lpData, dwSize, dwTimeout);

		// Error? - need to signal error
		if (dwBytes == (DWORD)-1L)
		{
			// Do not send event if we are closing
			if (IsOpenEx())
			{
//				TRACE("Run ReadComm fail:\r\n");
				OnEvent( EVT_CONDROP ); // lost connection
			}
			break;
		}

		if (dwBytes > 0L)
		{
			OnDataReceived( lpData, dwBytes);
		}

		Sleep(0);
	}
//	TRACE("Run End  %d %d\r\n", m_hComm, this);
}



///////////////////////////////////////////////////////////////////////////////
// SocketThreadProc
///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//     Socket Thread function.  This function is the main thread for socket
//     communication - Asynchronous mode.
// PARAMETERS:
//     LPVOID pParam : Thread parameter - a CSocketComm pointer
// NOTES:
///////////////////////////////////////////////////////////////////////////////
UINT WINAPI CSocketComm::SocketThreadProc(LPVOID pParam)
{
	CSocketComm* pThis = reinterpret_cast<CSocketComm*>( pParam );
	_ASSERTE( pThis != NULL );

	pThis->Run();

	return (UINT)pThis;
} // end SocketThreadProc


