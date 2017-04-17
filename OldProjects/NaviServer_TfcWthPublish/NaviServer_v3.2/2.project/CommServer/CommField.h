
/*
* ============================================================================
*  Name     : protocol definition
*  Part of  : NaviInt
*  Created  : 19.11.2006 by ZhangHeng
*  Description:
*     
*  Version  :
*  Copyright: Copyright (c) 2007, China SpaceSat. Corp. Ltd.
* ============================================================================
*/

// CommField.h: interface for the CCommField class.
//
#pragma once

//////////////////////////////////////////////////////////////////////////

#include <IOSocket.h>

#include "MobileFrameMgr_char.h"
#include "MobileFrameMgr_bin.h"
#include "SPFrameMgr.h"
#include "BusinessFrmMgr.h"
#include "NetWorkInterface.h"

//////////////////////////////////////////////////////////////////////////

class CCommField : public CIOSocket
{
    
	friend class CCommFieldMgr;
	friend class CCommFieldList;
public:


    CCommField(DWORD dwID,SOCKET s, MIOSckObserver& aObserver,int iType);

    virtual ~CCommField();

    /**
        Self-role definition
    */
    //enum TSelfRole
    //{
    //    SS_CLIENT,	// as a client
    //    SS_SERVER	// as a server
    //};

    // Time interval for cleaning up
#ifdef _DEBUG
    enum {ETimeIntervalClean=30}; // Unit: second
#else
    enum {ETimeIntervalClean=86400}; // Unit: second
#endif



    /**
        Running state definition
    */
    enum TRuningState
    {
        ERS_OPEN,		// Connected, haven't been certificated
        ERS_ACTIVE,		// Certificated already.
        ERS_INVALID,    // Invalid
        ERS_CLOSED,     // closed
    };


	void Close();

   

private:

	//CRITICAL_SECTION m_CriticalSection;

    // the unique ID(only valid in a same ComfieldMgr)
    DWORD           m_dwSlfID;
    

    // running state
	TRuningState m_iRunningState;
	
    // Client's name when running as a server
	//CString		 m_strUserName;

    TCommfieldAttrib m_selfAttri;


    // Inherited from CIOSocket
protected:	

    virtual void InstanceParser(CBaseFpProvider*& pBfp);
	virtual BOOL PreActive();
    virtual void OnRecvFrame(TBaseProtocol* pFrame);
	virtual void OnRecvRawData(LPBYTE pData,DWORD iLen);
	//virtual void OnFinishSendingRawData(DWORD dwLen);


    // Public functions
public:

    DWORD GetFieldID(void);

    BOOL IsExpired() const;

	/*
		Running state operation.
	*/
    BOOL IsActive() const;
    void Active();
    void Invalidate();
    BOOL IsInvalid() const;
    BOOL IsClosed() const;

	/*
		Users information operation.
	*/
	void SetUserInf(const CString& strUserName);
	void GetUserInf(CString& strUserName);
	void GetUserInf(char* cUserName);

    /**
        Logs
    */
    void AddNetLog(const IMsgNetLog& aNewLog);
    PTCommfieldAtri GetAttri() ;

private:

};
