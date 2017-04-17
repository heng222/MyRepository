#pragma once

#include "Ado.h"
#include "DataModulInterface.h"
#include "LinkParser.h"
#include "TfcInfView.h"
#include "TfcParsedView.h"

/************************************************************************/
/*

*/
/************************************************************************/
class AFX_EXT_CLASS CDataModule : public CNBaseModule
{

public:
	CDataModule(CImcDispatcher& aDispatcher);
	~CDataModule(void);

private:

    enum { EMID=ID_MODULE_DATABASE};

    enum TDBErrType
    {
        EDBET_SUCCESS = 0,
        EDBET_DISCONNTED=10,    // û�����ӵ����ݿ�
        EDBET_NODATA,           // û��ȡ������
    };

    //
    CRITICAL_SECTION m_CriticalSection;

    // Oracle���ݿ����Ӷ���
	CAdoConnection	m_OracleDB;

    CLinkParser     m_linkParser;


    // ԭʼ��ͨ��Ϣ����������ʾ
    CTfcInfMgr  m_TfcInfMgr;
    CTfcInfView m_wndTfcView;

    // ������Ľ�ͨ��Ϣ����������ʾ
    CTfcParsedMgr   m_TfcParsedMgr;
    CTfcParsedView  m_wndTfcParsed;

    // From CNBaseModule
private:
    virtual BOOL OnInitModule();
    virtual BOOL OnStart();
    virtual BOOL OnActive();
    // On receive message from other modules.
    virtual void OnRecvIMCMessage(PTImcMsg aImcMsg);
    // On receive message from internal objects.
    virtual BOOL OnRecvInterMessage(PTImcMsg aImcMsg);
    virtual void OnClose();

    // New private functions
private:
    void GetDBCnntPara(CString& strSource,CString& strUsername,CString& strPwd);
    BOOL ConnectToDB();

public:

	
    void Close(void);

    BOOL IsDBConnected();

	


};
