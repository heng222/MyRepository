#pragma once
//////////////////////////////////////////////////////////////////////////
#include "NBaseModule.h"
#include "WebService.h"


//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/*
    ���ܣ�
    1����ȡȫ����Ҫ���е�������Ϣ
    2�����������ݹ���ģ��
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
