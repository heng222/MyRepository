
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
/* 通信域管理类配置参数                                                 */
/************************************************************************/
struct TComMgrProfile 
{
    // 
    enum TSelfStatus
    {
        ECMP_SERVER,    // 服务器
        ECMP_CLIENT,    // 客户端
    };


    // Members
    TSelfStatus                     m_iStatus;        // 身份标识
	
    // m_iStatus==ECMP_Client时，表示需要连接的服务器的地址。
    // m_iStatus==ECMP_SERVER时，表示服务器的监听地址。
    TSockAddr                       m_serverAddr;     

    int    m_iProType;       // 使用的协议类型（见TBaseProtocol定义的协议类型）

public:

    // Constructor
    TComMgrProfile()
    {
        m_iStatus = ECMP_SERVER;
    }

    // New Functions
};


/************************************************************************/
/*                          通信域管理类                                */
/************************************************************************/
class AFX_EXT_CLASS CCommFieldMgr : public CIOSocketMgr
{
public:
	CCommFieldMgr(MComFiledMgrObserver&);
	virtual ~CCommFieldMgr();
	
public:

    // 初始化参数
    void InitProfile( TComMgrProfile::TSelfStatus aStatus,
                      TSockAddr aSockAddr,
                      int iProtocolType);

	/*
		向所有通信域发送数据
	*/
	BOOL SendRawData2All(LPBYTE lpData,int iDataLen);
    BOOL SendFrame2All(PTBaseProtocol pFrame);

	/*
		根据指定的参数打开SOCKET
	*/
	BOOL OpenCMG( int iClientPort=0/*should be greater than 5000 if specified.*/, 
                        CString strClientIPAddr=_T(""));
	/*
		关闭所有连接
	*/
	void Close();

    // 删除所有连接
    void Clear();

private:
    MComFiledMgrObserver&   m_Observer;
    TComMgrProfile  m_comMgrProfile;

private:

    //CRITICAL_SECTION m_CriticalSection;

private:
    // 
    enum {EMaxFildID=(2<<(8*sizeof(int)-1))-1};
    static DWORD           m_nComfCounter; // 通信域计数器
	// 所有客户
	CCommFieldList	m_ClientList;
	// 所有服务器
	CCommFieldList	m_ServerList;

    DWORD   NextFiledID();


public:
	
	/*
		根据ID返回对象指针
	*/
	CCommField* GetCommField(DWORD dwFieldID);

    // 向指定的通信域发送协议帧
    void    SendFrame(DWORD dwFieldID,PTBaseProtocol pFrame);
    
	
	/*
		 关闭一个通信域
	*/
    BOOL InvalidateCommFiled(CCommField* pCommField);

	/*
		返回已经连接的客户数
		bAuth: 为TRUE时，返回已经过认证的用户个数
			   为FALSE时，返回所有连接的用户个数
	*/
	WORD GetClientNum(BOOL bAuth);

    /*
		返回已经连接的服务器数
	*/
	WORD GetServerNum(void);


	// 清理处于断开状态的连接
	void CleanUp(void);

	// From CIoSocketMgr 
protected:
	virtual void OnNewConnection(SOCKET aNewSocket,const TSockAddr& clientAddr);
	virtual void OnConnectionDown(CIOSocket* pIoSocket);
	virtual void OnRecvFrame(TBaseProtocol* pProtocolFrame,CIOSocket* pIoSocket);
};
