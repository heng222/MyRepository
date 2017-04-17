#pragma once
#include "imc.h"

//////////////////////////////////////////////////////////////////////////

class CUIModule :  public CNBaseModule
{
public:
    CUIModule(CImcDispatcher& aDispatcher);
    ~CUIModule(void);


    // From CNBaseModule
private:
    virtual BOOL OnInitModule();
    virtual void OnStart();
    // On receive message from other modules.
    virtual void OnRecvIMCMessage(PTImcMsg aImcMsg);
    // On receive message from internal objects.
    virtual BOOL OnRecvInterMessage(PTImcMsg aImcMsg);
    virtual void OnClose();

private:

};
