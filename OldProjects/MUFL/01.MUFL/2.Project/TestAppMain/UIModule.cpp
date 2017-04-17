#include "StdAfx.h"
#include ".\uimodule.h"

CUIModule::CUIModule(CImcDispatcher& aDispatcher):
        CNBaseModule(aDispatcher,ID_MODULE_USERIF)
{
}

CUIModule::~CUIModule(void)
{
}

//////////////////////////////////////////////////////////////////////////
// From CNBaseModule
BOOL CUIModule::OnInitModule()
{
    return TRUE;
}
void CUIModule::OnStart()
{

}
// On receive message from other modules.
void CUIModule::OnRecvIMCMessage(PTImcMsg aImcMsg)
{

}
// On receive message from internal objects.
BOOL CUIModule::OnRecvInterMessage(PTImcMsg aImcMsg)
{
    return FALSE;
}
void CUIModule::OnClose()
{

}

//////////////////////////////////////////////////////////////////////////
// public function


//////////////////////////////////////////////////////////////////////////
// Private function
