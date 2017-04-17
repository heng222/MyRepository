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

    // �ֻ�ͨ�������������ֻ�����ͨ�ţ��ַ�Э�飩
    CCommFieldMgr	m_mobileComfieldMgrChar;
    
    // �ֻ�ͨ�������������ֻ�����ͨ�ţ�������Э�飩
    CCommFieldMgr	m_mobileComfieldMgrBin;

    // SPͨ������������SP����ͨ�ţ�
    CCommFieldMgr   m_SpComfieldMgr;

    // ���ؾ��������
    CCommFieldMgr   m_toBalanceServer;

};
