/*
* ============================================================================
*  Name     : protocol definition
*  Part of  : Server.dll
*  Created  : 19.11.2006 by H.W.
*  Description:
*     
*  Version  : 1.0.0.2.3
*  Copyright: Copyright (c) 2007, Microsoft Corp.
* ============================================================================
*/
#pragma once

#include <winsock2.h>


//////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS TSockAddr : public sockaddr_in 
{
public:
    // constructors. Default
    TSockAddr();

    TSockAddr(const SOCKADDR& sa);

    TSockAddr(const SOCKADDR_IN& sin) ;

    TSockAddr(const ULONG ulAddr, const USHORT ushPort = 0);

    TSockAddr(LPCTSTR pchIP, const USHORT ushPort = 0) ;

    TSockAddr(BYTE* pbyIP,const USHORT ushPort=0);

    // Return the address in dotted-decimal format
    char* DottedDecimal() const;

    // Get port and address (even though they're public)
    USHORT Port() const;

    ULONG IPAddr() const;

    // operators added for efficiency
    const TSockAddr& operator=(const SOCKADDR& sa);

    const TSockAddr& operator=(const SOCKADDR_IN& sin);

    operator SOCKADDR()
    { 
        return *((LPSOCKADDR) this);
    }

    operator LPSOCKADDR()
    { 
        return (LPSOCKADDR) this;
    }

    operator LPSOCKADDR_IN()
    { 
        return (LPSOCKADDR_IN) this;
    }
};



