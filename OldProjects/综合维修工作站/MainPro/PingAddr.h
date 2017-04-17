// PingAddr.h: interface for the CPingAddr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PINGADDR_H__BAA8B0E8_EE53_4146_8C84_12E9184FCBF4__INCLUDED_)
#define AFX_PINGADDR_H__BAA8B0E8_EE53_4146_8C84_12E9184FCBF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define ICMP_ECHOREPLY	0
#define ICMP_ECHOREQ	8

#include "winsock2.h"

// IP Header -- RFC 791
typedef struct tagIPHDR
{
	u_char  VIHL;			// Version and IHL
	u_char	TOS;			// Type Of Service
	short	TotLen;			// Total Length
	short	ID;				// Identification
	short	FlagOff;		// Flags and Fragment Offset
	u_char	TTL;			// Time To Live
	u_char	Protocol;		// Protocol
	u_short	Checksum;		// Checksum
	struct	in_addr iaSrc;	// Internet Address - Source
	struct	in_addr iaDst;	// Internet Address - Destination
}IPHDR, *PIPHDR;


// ICMP Header - RFC 792
typedef struct tagICMPHDR
{
	u_char	Type;			// Type
	u_char	Code;			// Code
	u_short	Checksum;		// Checksum
	u_short	ID;				// Identification
	u_short	Seq;			// Sequence
	char	Data;			// Data
}ICMPHDR, *PICMPHDR;


#define REQ_DATASIZE 32		// Echo Request Data size

// ICMP Echo Request
typedef struct tagECHOREQUEST
{
	ICMPHDR icmpHdr;
	DWORD	dwTime;
	char	cData[REQ_DATASIZE];
}ECHOREQUEST, *PECHOREQUEST;


// ICMP Echo Reply
typedef struct tagECHOREPLY
{
	IPHDR	ipHdr;
	ECHOREQUEST	echoRequest;
	char    cFiller[256];
}ECHOREPLY, *PECHOREPLY;

class CPingAddr  
{
public:
	CPingAddr();
	virtual ~CPingAddr();
private:
	static u_short in_cksum(u_short *addr, int len);
	static int WaitForEchoReply(SOCKET s);
	static DWORD RecvEchoReply(SOCKET s, LPSOCKADDR_IN lpsaFrom, u_char *pTTL) ;
	static int SendEchoRequest(SOCKET s,LPSOCKADDR_IN lpstToAddr) ;
	static int m_nLock;
public:
	static BOOL Ping(LPCSTR pstrHost);
};

#endif // !defined(AFX_PINGADDR_H__BAA8B0E8_EE53_4146_8C84_12E9184FCBF4__INCLUDED_)
