#pragma once
//////////////////////////////////////////////////////////////////////////
#include "NBaseModule.h"
#include "WebService.h"


//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/*
    功能：
    1、获取全国主要城市的天气信息
    2、将发送数据管理模块
*/
/************************************************************************/

class AFX_EXT_CLASS CWebServModule : public CNBaseModule
{
public:
    CWebServModule(CImcDispatcher& aDispatch);
    ~CWebServModule(void);


public:
    void    StopReadWebS();

// From CNBaseModule
private:
    virtual BOOL OnInitModule();
    virtual BOOL OnStart();
    // On receive message from other modules.
    virtual void OnRecvIMCMessage(PTImcMsg aImcMsg);
    // On receive message from internal objects.
    virtual BOOL OnRecvInterMessage(PTImcMsg aImcMsg);
    virtual void OnClose();


// Member
private:
    CWeatherClient   m_WeatherClient;
};
