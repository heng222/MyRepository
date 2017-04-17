#pragma once

#include "Ado.h"
#include "DataModulInterface.h"

/************************************************************************/
/*
	ģ��˵����

    ʵ�ֹ��ܣ�
        1��
        2��
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



    // From CNBaseModule
private:

    virtual BOOL OnInitModule();
    virtual BOOL OnStart();
    virtual BOOL OnActive();
    virtual void OnRecvIMCMessage(PTImcMsg aImcMsg);
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
