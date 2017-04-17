#pragma once

//////////////////////////////////////////////////////////////////////////

#include "UIModule.h"
#include "HttpModule.h"
//#include "MapModule.h"
#include "DataModule.h"
#include "ModuleDispatch.h"

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
    CUIModule           m_UIModule;
    CDataModule         m_DataModule;           // ���ݿ�ģ��
    //CWebServModule      m_WebServModule;    // WebServģ��
    CHttpModule         m_HttpModule;       // Httpģ��
};
