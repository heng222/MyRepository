#pragma once
//////////////////////////////////////////////////////////////////////////
#include <AppLogMgr.h>


//////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS IMsgNetLog : public IMsgAppLogs	
{
public:

    // the kind of logs.
    enum 
    {
        ELGT_Network = ELGT_Reserved+10,
    };

    // Network event
    enum TNetEventType
    {
        ENLT_NEWCONNECTION=1,	// A client connected up.
        ENLT_SENDFRAME,		    // Sending frame.
        ENLT_RECEIVEFRAME,		// Receiving frame.
        ENLT_CLOSECONNECT,      // close a connection.
        ENLT_DELCONNECTION,		// A client was shut down.

    };



    // the following members only valid when iLogType is ELGT_Network.
    int	            iEventType;	    // See TNetEventType
    int             iProtocolType;  // Protocol type(referring to TBaseProtocol::TProtocolType)
    DWORD		    dwFrameID;		// means ID of the frame when iEventType is CM_IF_RECV_FRAME or CM_IF_RECV_FRAME.                                    
    DWORD           dwComfieldID;   // ID when iEventType is ENLT_NEWCONNECTION or ENLT_DELCONNECTION.
    CString		    strUserName;	// Registered user's name.
    BYTE		    byClientIP[4];  // IP of a client.
    WORD		    uClientPort;    // client PORT
    WORD		    wNumClient;		// the number of clients.

    // 
    IMsgNetLog();
    IMsgNetLog(TNetEventType aEventType,int aProtocolType, DWORD aComFieldID,DWORD aFrmID=0);
    IMsgNetLog& operator= (const IMsgNetLog& other);


    DECLARE_SERIAL(IMsgNetLog)

    // From IMsgAppLogs
    virtual IMsgAppLogs* Duplicate() const;
    virtual void GetLogType_str(CString& strLogType) const;
    virtual void Serialize(CArchive& ar);
    
    // 
    void GetEventType_str(CString& strEvent) const;
    void GetStrIp(CString& strIP);
    void GetStrPort(CString& strPort);


};

typedef IMsgNetLog* PIMsgNetLog;
typedef CList<PIMsgNetLog,PIMsgNetLog> CNetLogList;



//////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CNetLogMgr : public CAppLogMgr
{
public:
    CNetLogMgr(void);
    ~CNetLogMgr(void);

public:

    // 根据事件类型与IP地址过滤日志文件
    void    FilterLog(int iEvtType=0,  CString strIPAddr="");


    // 得到读取缓冲中(m_ReadNLList)所有IP地址
    void    GetIPAddr(CStringList& strIPAddrList);

    // 得到网络日志链表
    void    GetNetLogList(CNetLogList& aNetLogList);

    void    GetAllLogList(CAppLogList& aAppLogList);

protected:

private:

};

//////////////////////////////////////////////////////////////////////////