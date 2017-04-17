#pragma once

//////////////////////////////////////////////////////////////////////////

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

    // New public functions
public:
    CMainFrame*   GetMainWnd();

    // Members
private:

    CDataModule     m_DataModule;   // DataBase Module
    CUIModule       m_UIModule;     // UI Module
    //CSckModule      m_SckModule;    // Socket Module
};
