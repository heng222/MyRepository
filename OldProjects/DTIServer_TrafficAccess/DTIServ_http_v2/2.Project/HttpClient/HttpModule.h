
#pragma once

#include <CommonFunc.h>
#include "Wininet.h"

#include "DataModulInterface.h"
#include "Afxinet.h"


//////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CHttpModule :  public CNBaseModule
{
public:
    CHttpModule(CImcDispatcher& aDispatcher);
    ~CHttpModule(void);


    // From CNBaseModule
private:
    virtual BOOL OnInitModule();
    virtual BOOL OnStart();
    virtual BOOL OnActive();
    virtual void OnRecvIMCMessage(PTImcMsg aImcMsg);
    virtual BOOL OnRecvInterMessage(PTImcMsg aImcMsg);
    virtual void OnClose();

private:
    BOOL    RequestData(CString& strXML);
    BOOL    ParseData();
    void    CheckTfcInf();

    BOOL    CreateMifData();

protected:
    CWinThread* m_pThread;
    HANDLE      m_hExitEvent;
private:
    static UINT _ThreadEntry(LPVOID pParam);


private:
    CInternetSession* m_pIntSession;
    CHttpConnection* m_pConnection;
};
