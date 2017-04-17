#pragma once

#include "NetWorkInterface.h"
#include "CommFieldMgr.h"

//////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CSckModule :  public CNBaseModule, public MComFiledMgrObserver
{
public:
    CSckModule(CImcDispatcher& aDispatcher);
    ~CSckModule(void);
public:

    BOOL ConnectToSP();
    void Close();

    BOOL  ConnectToBalServer();
    BOOL  StartPubServcie();
    void  StopPubService();

    // From CNBaseModule
private:

    virtual BOOL OnInitModule();
    virtual BOOL OnStart();
    virtual BOOL OnActive();
    virtual void OnClose();
    virtual void OnRecvIMCMessage(PTImcMsg aImcMsg);
    virtual BOOL OnRecvInterMessage(PTImcMsg aImcMsg);


    // From MComFiledMgrObserver
private:
    virtual void OnCfdMgrRecvFrame(TBaseProtocol* pProtocolFrame,CCommField* pComFiled,CCommFieldMgr* pCfdMgr);


    // New functions
private:

    CCommFieldMgr*  GetFieldMgr(int aProtocolType);

    void OnSendMobileFrame_char(CCommField* pComField,TMobileFrame_Char* pFrame);
    void OnSendMobileFrame_bin(CCommField* pComField,TMobileFrameBin* pFrame);

    void OnRecvMobileFrm_bin(PTMobileFrameBin pProtocolFrame,CCommField* pComField);
    void OnRecvMobileFrm_char(PTMobileFrame_Char pProtocolFrame,CCommField* pComField);

private:

    // 手机通信域管理对象（与手机进行通信：字符协议）
    CCommFieldMgr	m_mobileComfieldMgrChar;
    
    // 手机通信域管理对象（与手机进行通信：二进制协议）
    CCommFieldMgr	m_mobileComfieldMgrBin;

    // SP通信域管理对象（与SP进行通信）
    CCommFieldMgr   m_SpComfieldMgr;

    // 负载均衡管理器
    CCommFieldMgr   m_toBalanceServer;

};
