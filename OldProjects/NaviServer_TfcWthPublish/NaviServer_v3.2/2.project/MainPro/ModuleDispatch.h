#pragma once

//////////////////////////////////////////////////////////////////////////
#include "AuthenMgr.h"
#include "SckModule.h"
#include "UiModule.h"
#include "datamodule.h"

//////////////////////////////////////////////////////////////////////////
class CModuleDispatch : public CImcDispatcher
{
public:
    CModuleDispatch(void);
    virtual ~CModuleDispatch(void);

    // Inherited from CImcDispather
public:
    void OnInitialize();
    void OnInitFailure(TModuleID aModulID);
    void OnStartFailure(TModuleID aModulID);
    BOOL OnActive();
    BOOL PreDispatchMsg(PTImcMsg aIMCMsg);
    void OnClosing();

    // New private functions
private:
    void    HandleMobileRequest_bin(PTMobileFrameBin pFrameBin,DWORD dwComfieldID);
    void    HandleMobileRequest_char(PTMobileFrame_Char pFrameChar,DWORD dwComfieldID);

    // New public functions
public:
    CMainFrame*   GetMainWnd();

    // Members
private:
    CAuthenMgr      m_AuthenMgr;    // Users Authentication Manager

    CDataModule     m_DataModule;   // DataBase Module
    CUIModule       m_UIModule;     // UI Module
    CSckModule      m_SckModule;    // Socket Module
};
