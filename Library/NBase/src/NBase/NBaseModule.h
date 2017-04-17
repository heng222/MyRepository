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

#include "LogManager.h"

//////////////////////////////////////////////////////////////////////////
   
class CImcDispatcher;

//////////////////////////////////////////////////////////////////////////
// N-Base class for inter-module
class NBASE_EXT_API CNBaseModule : public CObject
{
    friend class CImcDispatcher;

public:

    // None
    const static int ModuleIDNone;
    // system ID
    const static int ModuleIDSys;
    // Reserved!
    const static int ModuleIDReserved;
    // All modules
    const static int ModuleIDAll;

protected:

    int             m_iModuleID;

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

    CNBaseModule(CImcDispatcher&,int aMID);
    virtual ~CNBaseModule()=0;


    // New Function
public:

    //
    int get_MoudleID() const;
    void set_ModuleID(int id);

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
#endif

