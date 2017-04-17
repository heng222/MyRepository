/*
* ============================================================================
*  Name     : protocol definition
*  Part of  : Server.dll
*  Created  : 19.11.2006 by H.W.
*  Description:
*     
*  Version  : 1.0.0.2.3
*  Copyright: Copyright (c) 2007, H.W. Corpor.
* ============================================================================
*/

#ifndef _COMMUNICATION_FIELD_OBSERVER_
#define _COMMUNICATION_FIELD_OBSERVER_
//////////////////////////////////////////////////////////////////////////

#include "BaseProtocol.h"
#include "TSockAddr.h"

//////////////////////////////////////////////////////////////////////////

class CIOSocket;

class __declspec(novtable) MIOSckObserver
{
public:
    virtual void OnRecvFrame(TBaseProtocol* pProtocolFrame,CIOSocket* pIoSocket);
    virtual void OnConnectionDown(CIOSocket* pIoSck);
};

//////////////////////////////////////////////////////////////////////////
#endif