#pragma once

#include "DlgAppStart.h"
#include "MainFrm.h"


//////////////////////////////////////////////////////////////////////////

class CUIModule :  public CNBaseModule
{
    friend class CModuleDispatch;

public:
    CUIModule(CImcDispatcher& aDispatcher);
    ~CUIModule(void);

    // From CNBaseModule
protected:
    virtual BOOL OnInitModule();
    virtual BOOL OnStart();
    virtual BOOL OnActive();
    virtual void OnRecvIMCMessage(PTImcMsg aImcMsg);
    virtual BOOL OnRecvInterMessage(PTImcMsg aImcMsg);
    virtual void OnClose();

    // New public functions
public:
    CMainFrame*     GetMainWnd();

    // New private functions
private:
    BOOL IsOneInstance();
    void CloseMutex();
    void RestartApplication();
    void EnableFullScreen(BOOL bEnable=TRUE);

    // Member variables
private:
    CMainFrame*     m_pMainFrame;
    HANDLE m_hOneInstance;
    CDlgAppStart m_dlgStart;

};
