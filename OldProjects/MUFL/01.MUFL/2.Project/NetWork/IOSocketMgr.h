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
//
#pragma once

#include "IOSocket.h"


// Class CIOSocketMgr

class AFX_EXT_CLASS CIOSocketMgr : public MIOSckObserver
{
public:

	CIOSocketMgr();
    virtual ~CIOSocketMgr()=0;

	// New public functions
public:

    void Close();
	
    // New virtual functions
protected:

    virtual void OnNewConnection(SOCKET aSck,const TSockAddr& clientAddr);

    // From MComFiledObserver
protected:

    virtual void OnRecvFrame(TBaseProtocol* pProtocolFrame,CIOSocket* pParam);
    virtual void OnConnectionDown(CIOSocket* pIoSck);

	// protected 
protected:

	BOOL StartService(TSockAddr& serAddr);

private:

	// Listening socket
	SOCKET			m_hListenSocket;

	// listening thread pointer
	CWinThread*		m_pListenThread;
	// listening thread entry
	static UINT     _ListeningThread(LPVOID pParam);

};
//////////////////////////////////////////////////////////////////////////

