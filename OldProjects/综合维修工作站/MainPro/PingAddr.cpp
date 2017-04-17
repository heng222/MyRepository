// PingAddr.cpp: implementation of the CPingAddr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PingAddr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int CPingAddr::m_nLock = 0;

CPingAddr::CPingAddr()
{

}

CPingAddr::~CPingAddr()
{

}

u_short CPingAddr::in_cksum(u_short *addr, int len)
{
	register int nleft = len;
	register u_short *w = addr;
	register u_short answer;
	register int sum = 0;

	/*
	 *  Our algorithm is simple, using a 32 bit accumulator (sum),
	 *  we add sequential 16 bit words to it, and at the end, fold
	 *  back all the carry bits from the top 16 bits into the lower
	 *  16 bits.
	 */
	while( nleft > 1 )  {
		sum += *w++;
		nleft -= sizeof(u_short);
	}

	/* mop up an odd byte, if necessary */
	if( nleft == 1 ) {
		u_short	u = 0;

		*(u_char *)(&u) = *(u_char *)w ;
		sum += u;
	}

	/*
	 * add back carry outs from top 16 bits to low 16 bits
	 */
	sum = (sum >> 16) + (sum & 0xffff);	/* add hi 16 to low 16 */
	sum += (sum >> 16);			/* add carry */
	answer = ~sum;				/* truncate to 16 bits */
	return (answer);
}

int CPingAddr::WaitForEchoReply(SOCKET s)
{
	struct timeval Timeout;
	fd_set readfds;

	readfds.fd_count = 1;
	readfds.fd_array[0] = s;
	Timeout.tv_sec = 0;
    Timeout.tv_usec = 500;

	return(select(1, &readfds, NULL, NULL, &Timeout));
}

DWORD CPingAddr::RecvEchoReply(SOCKET s, LPSOCKADDR_IN lpsaFrom, u_char *pTTL) 
{
	ECHOREPLY echoReply;
	int nRet;
	int nAddrLen = sizeof(struct sockaddr_in);

	// Receive the echo reply	
	nRet = recvfrom(s,					// socket
					(LPSTR)&echoReply,	// buffer
					sizeof(ECHOREPLY),	// size of buffer
					MSG_PEEK,					// flags
					(LPSOCKADDR)lpsaFrom,	// From address
					&nAddrLen);			// pointer to address len

	

	// return time sent and IP TTL
	*pTTL = echoReply.ipHdr.TTL;
	return(echoReply.echoRequest.dwTime);   		
}

int CPingAddr::SendEchoRequest(SOCKET s,LPSOCKADDR_IN lpstToAddr) 
{
	static ECHOREQUEST echoReq;
	static int nId = 1;
	static int nSeq = 1;
	int nRet;

	// Fill in echo request
	echoReq.icmpHdr.Type		= ICMP_ECHOREQ;
	echoReq.icmpHdr.Code		= 0;
	echoReq.icmpHdr.Checksum	= 0;
	echoReq.icmpHdr.ID			= nId++;
	echoReq.icmpHdr.Seq			= nSeq++;

	// Fill in some data to send
	for (nRet = 0; nRet < REQ_DATASIZE; nRet++)
		echoReq.cData[nRet] = ' '+nRet;

	// Save tick count when sent
	echoReq.dwTime			= GetTickCount();

	// Put data in packet and compute checksum
	echoReq.icmpHdr.Checksum = in_cksum((u_short *)&echoReq, sizeof(ECHOREQUEST));

	// Send the echo request  								  
	nRet = sendto(s,						/* socket */
				 (LPSTR)&echoReq,			/* buffer */
				 sizeof(ECHOREQUEST),
				 0,							/* flags */
				 (LPSOCKADDR)lpstToAddr, /* destination */
				 sizeof(SOCKADDR_IN));   /* address length */

	return (nRet);
}


BOOL CPingAddr::Ping(LPCSTR pstrHost)
{
	SOCKET	  rawSocket;
	LPHOSTENT lpHost;
	struct    sockaddr_in saDest;
	struct    sockaddr_in saSrc;
	DWORD	  dwTimeSent;
	DWORD	  dwElapsed;
	u_char    cTTL;
	int       nLoop;
	int       nRet;
	BOOL	  nResult;

	while (m_nLock != 0)
	{
		Sleep(10);
	}
	m_nLock = 1;
	// Create a Raw socket
	rawSocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (rawSocket == SOCKET_ERROR) 
	{
		return FALSE;
	}
	
	// Lookup host
	lpHost = gethostbyname(pstrHost);
	if (lpHost == NULL)
	{
		nRet = closesocket(rawSocket);
		return FALSE;
	}
	// Setup destination socket address
	saDest.sin_addr.s_addr = *((u_long FAR *) (lpHost->h_addr));
	saDest.sin_family = AF_INET;
	saDest.sin_port = 0;

	nResult = FALSE;
	// Ping multiple times
	for (nLoop = 0; nLoop < 6; nLoop++)
	{
		// Send ICMP echo request
		SendEchoRequest(rawSocket, &saDest);

		// Use select() to wait for data to be received
		nRet = WaitForEchoReply(rawSocket);
		if (nRet == SOCKET_ERROR)
		{
//			TRACE("select()");
			continue;
		}
		if (!nRet)
		{
//			TRACE("\nTimeOut");
			
			continue;
		}

		// Receive reply
		dwTimeSent = RecvEchoReply(rawSocket, &saSrc, &cTTL);

		// Calculate elapsed time
		dwElapsed = GetTickCount() - dwTimeSent;
		nResult = TRUE;
		break;
	}

	nRet = closesocket(rawSocket);
	m_nLock = 0;
	if (!nResult)
	{
//		TRACE("ping fail\r\n");
	}
	return nResult;
}
