

//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "TSockAddr.h"


//////////////////////////////////////////////////////////////////////////

// constructors. Default
TSockAddr::TSockAddr()
{ 
    sin_family = AF_INET;
    sin_port = 0;
    sin_addr.s_addr = 0; 
}

TSockAddr::TSockAddr(const SOCKADDR& sa)
{ 
    memcpy(this, &sa, sizeof(SOCKADDR));
}

TSockAddr::TSockAddr(const SOCKADDR_IN& sin) 
{ 
    memcpy(this, &sin, sizeof(SOCKADDR_IN));
}

TSockAddr::TSockAddr(const ULONG ulAddr, const USHORT ushPort/* = 0*/) // parameters are host byte ordered
{ 
    sin_family = AF_INET;
    sin_port = htons(ushPort);
    sin_addr.s_addr = htonl(ulAddr); 
}

TSockAddr::TSockAddr(LPCTSTR pchIP, const USHORT ushPort/* = 0*/) // dotted IP addr string
{ 
    sin_family = AF_INET;
    sin_port = htons(ushPort);
    if (_tcslen(pchIP)>0)
    {
#ifdef _UNICODE
        char strIP[MAX_PATH] = {0};
        ::WideCharToMultiByte(
            CP_ACP,
            0,
            pchIP,
            -1,
            strIP,
            MAX_PATH,
            NULL,
            NULL);
        sin_addr.s_addr = inet_addr(strIP); 
#else
        sin_addr.s_addr = inet_addr(pchIP);
#endif
    }
    else
    {
        sin_addr.s_addr = INADDR_ANY;
    }
} // already network byte ordered

TSockAddr::TSockAddr(BYTE* pbyIP,const USHORT ushPort/*=0*/) // array of bytes
{
    sin_family = AF_INET;
    sin_port = htons(ushPort);
    sin_addr.S_un.S_un_b.s_b1 = pbyIP[0];
    sin_addr.S_un.S_un_b.s_b2 = pbyIP[1];
    sin_addr.S_un.S_un_b.s_b3 = pbyIP[2];
    sin_addr.S_un.S_un_b.s_b4 = pbyIP[3];
}

// Return the address in dotted-decimal format
char* TSockAddr::DottedDecimal() const
{ 
    return inet_ntoa(sin_addr); 
} // constructs a new CString object

// Get port and address (even though they're public)
USHORT TSockAddr::Port() const
{ 
    return ntohs(sin_port);
}

ULONG TSockAddr::IPAddr() const
{ 
    return ntohl(sin_addr.s_addr);
}

// operators added for efficiency
const TSockAddr& TSockAddr::operator=(const SOCKADDR& sa)
{ 
    memcpy(this, &sa, sizeof(SOCKADDR));
    return *this; 
}


const TSockAddr& TSockAddr::operator=(const SOCKADDR_IN& sin)
{ 
    memcpy(this, &sin, sizeof(SOCKADDR_IN));
    return *this; 
}