
/*
* ============================================================================
*  Name     : protocol definition
*  Part of  : NaviInt
*  Created  : 19.11.2006 by ZhangHeng
*  Description:
*     
*  Version  :
*  Copyright: Copyright (c) 2007, China SpaceSat. Corp. Ltd.
* ============================================================================
*/


//
#pragma once
#include <IOSocketMgr.h>


#include "afx.h"
#include "InterfaceEx.h"
#include "CommFieldList.h"

//////////////////////////////////////////////////////////////////////////
struct MComFiledMgrObserver
{
    virtual void OnCfdMgrRecvFrame(TBaseProtocol* pProtocolFrame,CCommField* pComFiled,CCommFieldMgr* pCfdMgr)=0;
};


/************************************************************************/
/* ͨ������������ò���                                                 */
/************************************************************************/
struct TComMgrProfile 
{
    // 
    enum TSelfStatus
    {
        ECMP_SERVER,    // ������
        ECMP_CLIENT,    // �ͻ���
    };


    // Members
    TSelfStatus                     m_iStatus;        // ��ݱ�ʶ
	
    // m_iStatus==ECMP_Clientʱ����ʾ��Ҫ���ӵķ������ĵ�ַ��
    // m_iStatus==ECMP_SERVERʱ����ʾ�������ļ�����ַ��
    TSockAddr                       m_serverAddr;     

    int    m_iProType;       // ʹ�õ�Э�����ͣ���TBaseProtocol�����Э�����ͣ�

public:

    // Constructor
    TComMgrProfile()
    {
        m_iStatus = ECMP_SERVER;
    }

    // New Functions
};


/************************************************************************/
/*                          ͨ���������                                */
/************************************************************************/
class AFX_EXT_CLASS CCommFieldMgr : public CIOSocketMgr
{
public:
	CCommFieldMgr(MComFiledMgrObserver&);
	virtual ~CCommFieldMgr();
	
public:

    // ��ʼ������
    void InitProfile( TComMgrProfile::TSelfStatus aStatus,
                      TSockAddr aSockAddr,
                      int iProtocolType);

	/*
		������ͨ����������
	*/
	BOOL SendRawData2All(LPBYTE lpData,int iDataLen);
    BOOL SendFrame2All(PTBaseProtocol pFrame);

	/*
		����ָ���Ĳ�����SOCKET
	*/
	BOOL OpenCMG( int iClientPort=0/*should be greater than 5000 if specified.*/, 
                        CString strClientIPAddr=_T(""));
	/*
		�ر���������
	*/
	void Close();

    // ɾ����������
    void Clear();

private:
    MComFiledMgrObserver&   m_Observer;
    TComMgrProfile  m_comMgrProfile;

private:

    //CRITICAL_SECTION m_CriticalSection;

private:
    // 
    enum {EMaxFildID=(2<<(8*sizeof(int)-1))-1};
    static DWORD           m_nComfCounter; // ͨ���������
	// ���пͻ�
	CCommFieldList	m_ClientList;
	// ���з�����
	CCommFieldList	m_ServerList;

    DWORD   NextFiledID();


public:
	
	/*
		����ID���ض���ָ��
	*/
	CCommField* GetCommField(DWORD dwFieldID);

    // ��ָ����ͨ������Э��֡
    void    SendFrame(DWORD dwFieldID,PTBaseProtocol pFrame);
    
	
	/*
		 �ر�һ��ͨ����
	*/
    BOOL InvalidateCommFiled(CCommField* pCommField);

	/*
		�����Ѿ����ӵĿͻ���
		bAuth: ΪTRUEʱ�������Ѿ�����֤���û�����
			   ΪFALSEʱ�������������ӵ��û�����
	*/
	WORD GetClientNum(BOOL bAuth);

    /*
		�����Ѿ����ӵķ�������
	*/
	WORD GetServerNum(void);


	// �����ڶϿ�״̬������
	void CleanUp(void);

	// From CIoSocketMgr 
protected:
	virtual void OnNewConnection(SOCKET aNewSocket,const TSockAddr& clientAddr);
	virtual void OnConnectionDown(CIOSocket* pIoSocket);
	virtual void OnRecvFrame(TBaseProtocol* pProtocolFrame,CIOSocket* pIoSocket);
};
