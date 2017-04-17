#include "StdAfx.h"
#include ".\webservmodule.h"


CWebServModule::CWebServModule(CImcDispatcher& aDispatch):
        CNBaseModule(aDispatch,ID_MODULE_WEBSERV)
    
{
    
}

CWebServModule::~CWebServModule(void)
{
}

void CWebServModule::StopReadWebS()
{
    m_WeatherClient.Stop();
}

BOOL CWebServModule::OnInitModule()
{
    if (!m_WeatherClient.Initialize())
    {
        return FALSE;
    }
    
    return TRUE;
}

BOOL CWebServModule::OnStart()
{
    BOOL bFlag = m_WeatherClient.Start();

    if (!bFlag)
    {
        return FALSE;
    }

    return TRUE;
}

// On receive message from other modules.
void CWebServModule::OnRecvIMCMessage(PTImcMsg aImcMsg)
{

}

// On receive message from internal objects.
BOOL CWebServModule::OnRecvInterMessage(PTImcMsg aImcMsg)
{
    return FALSE;
}

void CWebServModule::OnClose()
{
    m_WeatherClient.Terminate();
}

