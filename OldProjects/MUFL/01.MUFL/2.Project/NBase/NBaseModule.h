/*
* ============================================================================
*  Name     : protocol definition
*  Part of  : Server.dll
*  Created  : 19.11.2006 by H.R.
*  Description:
*     
*  Version  : 1.0.0.2.3
*  Copyright: Copyright (c) 2007, H.W. Corpor.
* ============================================================================
*/
#ifndef _NBASEMODULE_2R8934UIWE356__
#define _NBASEMODULE_2R8934UIWE356__
//////////////////////////////////////////////////////////////////////////

#include "AppLogMgr.h"

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// N-Base class for inter-module
class NBASE_EXT_API CNBaseModule : public CObject
{
    friend class CImcDispatcher;

protected:

    TModuleID             m_iModuleID;

    // Module state definition
    enum TMState
    {
        EMS_NONE,
        EMS_INITLIALIZING,
        EMS_STARTING,
        EMS_ACTIVED,
        EMS_CLOSED,
    };
    TMState m_iMState;

private:

    CImcDispatcher&       m_IMCDispatcher;


protected:

    CNBaseModule(CImcDispatcher&,TModuleID aMID);
    virtual ~CNBaseModule()=0;


    // New Function
public:

    // Send a message to the specific modules.
    void SendModuleMsg(TImcMsg& aImcMsg);

    //
    TModuleID GetMoudleID() const;

    // Virtual function
protected:

    // On initialization
    virtual BOOL OnInitModule();

    // Start running module
    virtual BOOL OnStart();

    // On active
    virtual BOOL OnActive();

    // On receive message from other modules.
    virtual void OnRecvIMCMessage(PTImcMsg aImcMsg);

    // On receive message from internal objects. Return TRUE if the message is handled.
    virtual BOOL OnRecvInterMessage(PTImcMsg aImcMsg);

    // On Close module.
    virtual void OnClose();

};
typedef CTypedPtrList<CObList,CNBaseModule*> CNBaseModuleList;


//////////////////////////////////////////////////////////////////////////
// Management class of modules

// Inter-Module Dispatcher interface
class NBASE_EXT_API CImcDispatcher
{
public:

    // Errors for register
    enum TRegErrType
    {
        ERR_NONE=0,         // NONE
		ERR_UNKNOWN=10,		// unknown error
        ERR_ALREADYEXIST,   // Already exist
        ERR_CANNOTUSE,      // Cannot be used
        ERR_INVALID,        // Invalid ID
    };

    CImcDispatcher();
    virtual ~CImcDispatcher()=0;

public:

    int Register(CNBaseModule* aModule); 
    void UnRegister(TModuleID aModuleID);
    void AddMsg(PTImcMsg pNewMsg);
    void SetLogPath(LPCTSTR lpcsPath);
    void SetLogCacheSize(BYTE nNumOfLog);

private:

    BOOL               IsExistModule(TModuleID aMID);
    CNBaseModule*      FindModule(TModuleID aMID);

private:

    enum {EMaxNumMsgQueue = 1024};
    TImcMsgList     m_ImcMsgList;
    CWinThread*		m_pMsgHandleThread;
    static UINT     _MsgHandleThread(LPVOID pParam);
    HANDLE          m_hMsgSemaphore;
    HANDLE          m_hExitEvent;

    CNBaseModuleList  m_ModuleList;

protected:

    CAppLogMgr        m_AppLogMgr;  // Application log manager 

public:

    // Initialize all modules. 
    // If success, return 0, or return the Module ID of failure if unsuccessful.
    TModuleID Initialize();

    // Return the ID of module that failed to start or return zero when success.
    TModuleID StartRunMod();

	// 
    void CloseMods();

	// 
    void RemoveModuls();

	// 
    void Terminate();

protected:

    // on initialize
    virtual void OnInitialize();

	// on initialize failed
    virtual void OnInitFailure(TModuleID aModulID);

	// on start failure
    virtual void OnStartFailure(TModuleID aModulID);

	// on the module is active.
    virtual BOOL OnActive();

	// on closing
    virtual void OnClosing();

	// on closed
    virtual void OnClosed();

	// on terminating
    virtual void OnTerminating();

    // 
    virtual BOOL PreDispatchMsg(PTImcMsg aImcMsg);

private:

    void DispatchMessage(PTImcMsg aIMCMsg);

};


//////////////////////////////////////////////////////////////////////////

// Global functions
extern "C++" AFX_EXT_API BOOL NbsRegisterDispather(CImcDispatcher* aDispather);

extern "C++" AFX_EXT_API int NbsRegisterModule(CNBaseModule* aModule);

extern "C++" AFX_EXT_API BOOL NbsInitialization();

extern "C++" AFX_EXT_API BOOL NbsStartRunning();

extern "C++" AFX_EXT_API void NbsSendModuleMsg(PTImcMsg aIMCMsg);

extern "C++" AFX_EXT_API void NbsTermination();

extern "C++" AFX_EXT_API void NbsUnregisterDispatch(BOOL bRelease);


// Dispatcher definition and register
#define DECLARE_NBASE_DISPATCHER(nbase_dispatch_name) \
    nbase_dispatch_name _gNbsDispather;

//////////////////////////////////////////////////////////////////////////
#endif

