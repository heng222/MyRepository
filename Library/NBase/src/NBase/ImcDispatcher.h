
#ifndef _IMCDISPATHCER_A25F8E419C774724A86497384951B4C2_
#define _IMCDISPATHCER_A25F8E419C774724A86497384951B4C2_

#include "NBaseModule.h"


//////////////////////////////////////////////////////////////////////////
// Management class of modules
class CNBase;

// Inter-Module Dispatcher interface
class CImcDispatcher
{
    friend CNBase;
public:

    // Errors for register
    enum TRegErrType
    {
        // NONE
        ERR_NONE = 0,         
        // unknown error
        ERR_UNKNOWN = 10,        
        // Already exist
        ERR_ALREADYEXIST,   
        // Cannot be used
        ERR_CANNOTUSE,      
        // Invalid ID
        ERR_INVALID,        
    };

    CImcDispatcher();
    virtual ~CImcDispatcher();

public:

    // 
    int AddModule(CNBaseModule* aModule); 

    //
    void RemoveModule(int aModuleID);

    //
    void DispatchMessage(PTImcMsg aIMCMsg, bool asyn = false);

    // 
    BOOL IsExistModule(int aMID);

    // 
    CNBaseModule* FindModule(int aMID);

private:

    enum {EMaxNumMsgQueue = 1024};
    TImcMsgList     m_ImcMsgList;
    CWinThread*		m_pMsgHandleThread;
    HANDLE          m_hMsgSemaphore;
    HANDLE          m_hExitEvent;

    CNBaseModuleList  m_ModuleList;

    CCritSec m_criSection;

public:

    // Initialize all modules. 
    // If success, return 0, or return the Module ID of failure if unsuccessful.
    int Initialize();

    // Return the ID of module that failed to start or return zero when success.
    int Start();

    // active modules
    void Active();

    // close modules
    void Close();

    // 
    void RemoveModuls();

    // terminate
    void Terminate();

protected:

    // on initialize failed
    void OnInitFailure(int aModulID);

    // on start failure
    void OnStartFailure(int aModulID);

    // on the module is active.
    BOOL OnActive();

private:

    void AddMessage(PTImcMsg pNewMsg);

    // 
    static UINT     _MsgHandleThread(LPVOID pParam);

};
//////////////////////////////////////////////////////////////////////////


#endif

