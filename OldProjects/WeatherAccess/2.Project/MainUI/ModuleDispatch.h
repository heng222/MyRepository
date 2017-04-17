#pragma once

//////////////////////////////////////////////////////////////////////////

#include "UiModule.h"
#include "WebServModule.h"
#include "DataModule.h"

//////////////////////////////////////////////////////////////////////////
class CModuleDispatch : public CImcDispatcher
{
public:
    CModuleDispatch(void);
    virtual ~CModuleDispatch(void);

    // Inherited from CImcDispather
public:

    void PreInitialization();
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

    CUIModule       m_UIModule;     // UI Module
    CDataModule     m_DataModule;   // DataBase Module
    CWebServModule  m_WebServModule;// WebServÄ£¿é
};
