#include "StdAfx.h"
#include "NBaseModule.h"
#include "ImcDispatcher.h"

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// CNBaseModule

const int CNBaseModule::ModuleIDNone = 0x0000;
const int CNBaseModule::ModuleIDSys = 0x0001;
const int CNBaseModule::ModuleIDReserved = 0x0010;
const int CNBaseModule::ModuleIDAll = 0xFFFF;

// Constructor && Destructor
CNBaseModule::CNBaseModule(CImcDispatcher& aObeserver,int aMID):
    m_IMCDispatcher(aObeserver),
    m_iModuleID(aMID)
{
    m_iMState = EMS_NONE;
}
CNBaseModule::~CNBaseModule()
{

}


int CNBaseModule::get_MoudleID() const
{
    return m_iModuleID;
}

void CNBaseModule::set_ModuleID(int id)
{
    m_iModuleID = id;
}

BOOL CNBaseModule::OnInitModule()
{
    m_iMState = EMS_INITLIALIZING;
    return TRUE;
}
BOOL CNBaseModule::OnStart()
{
    m_iMState = EMS_STARTING;
    return TRUE;
}
BOOL CNBaseModule::OnActive()
{
    m_iMState = EMS_ACTIVED;
    // to do...
    return TRUE;
}
void CNBaseModule::OnClose()
{
    m_iMState = EMS_CLOSED;
}
void CNBaseModule::OnRecvIMCMessage(PTImcMsg /*aImcMsg*/)
{
    
}
BOOL CNBaseModule::OnRecvInterMessage(PTImcMsg /*aImcMsg*/)
{
    return FALSE; // Not handle
}









