

/*
* ============================================================================
*  Name     : protocol definition
*  Part of  : Server.dll
*  Created  : 19.11.2006 by Henry.
*  Description:
*     
*  Version  : 1.0.0.2.3
*  Copyright: Copyright (c) 2007, H.W. Corp.
* ============================================================================
*/

#ifndef _NABSE_IOCOMPLENTATIONPORT_IOSOCKET_E9DFDKIE
#define _NABSE_IOCOMPLENTATIONPORT_IOSOCKET_E9DFDKIE
//////////////////////////////////////////////////////////////////////////


#include "TSockAddr.h"
#include "BaseFpProvider.h"
#include "MIOSckObserver.h"


// Import WINSOCK2 library
#include <winsock2.h>
#pragma comment(lib, "ws2_32")

// 
#ifndef _NETWORK_PROJECT_
    #ifdef _DEBUG
        #ifdef _UNICODE
            #define _NETWORK_LIB_ "NetworkUD"
        #else
            #define _NETWORK_LIB_ "NetworkD"
        #endif
    #else
        #ifdef _UNICODE
            #define _NETWORK_LIB_ "NetworkU"
        #else
            #define _NETWORK_LIB_ "Network"
        #endif
    #endif

    #pragma  comment(lib,_NETWORK_LIB_)
#endif


/************************************************************************/
/*            Class CIOSocket Definition                                */
/************************************************************************/
class AFX_EXT_CLASS CIOSocket : public CObject
{
    
	friend class CIOSocketMgr;
    friend UINT  g_fn_RecvThread(LPVOID pParam);

public:
    
    CIOSocket(SOCKET socket,MIOSckObserver&  aObserver,int iType);

	virtual ~CIOSocket();

    enum TStatus 
    {
        ETS_UNKOWN,
        ETS_SERVER=10,
        ETS_CLIENT,
    };

private:

    CIOSocket(const CIOSocket& objectSrc);            // no implementation
    void operator=(const CIOSocket& objectSrc);       // no implementation

    // new virtual protected functions
protected:	

    virtual void InstanceParser(CBaseFpProvider*& pBfp)=0;
	virtual BOOL PreActive();
	virtual void OnFinishSendingRawData(DWORD dwLen);
	virtual void OnRecvRawData(LPBYTE pRawData,DWORD iLen);
	virtual void OnRecvFrame(TBaseProtocol* pFrame);


protected:

    int Recv();


    // Public functions
public:

    BOOL  ActiveIoSck(BOOL bClient);
    void  Close();

    // Send data
    DWORD SendRawData(const BYTE* buf, DWORD len);
	void  SendFrame(PTBaseProtocol pFrame);
    
    // Retrieve the corresponding protocol .
    int  GetProtocolType() const;

	// Address operation
	void  SetClientAddr(CString strIPAdd,unsigned short uPort=0);
	void  SetClientAddr(const sockaddr_in* pNewAdd);
	void  SetServerAddr(CString strIPAdd,unsigned short uPort);
	void  SetServerAddr(const sockaddr_in* pNewAdd);	
	void  GetClientAddr(CString& strIP,CString& strPort) const;
	void  GetClientAddr(LPBYTE pClientIP,u_short& uPort) const;	
	void  GetServerAddr(LPBYTE pClientIP,u_short& uPort) const;
	void  GetServerAddr(CString& strIP,CString& strPort) const;

    // Retrieve the bytes of data that have sent and received.
    __int64  RetrieveDataSent() const;
    __int64  RetrieveDataRecv() const;


private:    

    TStatus     m_iStatus;

    SOCKET		m_hSocket;

    TSockAddr	m_clientAddr;
    TSockAddr	m_serverAddr;	

    OVERLAPPED	m_overLappedOut;
    OVERLAPPED	m_overLappedIn;
    BYTE		m_byInBuffer[100];

    // Attributes
    __int64     m_lDataSent;
    __int64     m_lDataRecv;

private:

    MIOSckObserver&  m_Observer;

    int  m_iProType; // Corresponding protocol.

    CBaseFpProvider* m_pFrameParser; // Frame parser

    CRITICAL_SECTION m_CSRecvBuffer; // to protect the recv buffer.
};

//////////////////////////////////////////////////////////////////////////

extern "C++" AFX_EXT_API  int   NciStartup();
extern "C++" AFX_EXT_API  void  NciCleanup();
extern "C++" AFX_EXT_API  void  NciEnableTipInf(BOOL bEnable);

//////////////////////////////////////////////////////////////////////////
//

#endif
