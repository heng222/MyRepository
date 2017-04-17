#include "StdAfx.h"
#include  "NetLogMgr.h"


//////////////////////////////////////////////////////////////////////////
IMsgNetLog::IMsgNetLog()
{
    iLogType = ELGT_Network;
    memset(byClientIP,0,sizeof(byClientIP));
    uClientPort = 0;
}

IMsgNetLog::IMsgNetLog(TNetEventType aEventType,int aProtocolType,
                         DWORD aComFieldID,DWORD aFrmID)
{
    // Base class initialization.
    SetSourceModule(ID_MODULE_NETWORK);
    SetDestModule(ID_MODULE_USERIF);
    AddDestModule(ID_MODULE_NETWORK);
    AddDestModule(ID_MODULE_DATABASE);

    // 
    iLogType = ELGT_Network;

    // 
    iEventType = aEventType;
    iProtocolType = aProtocolType;
    dwComfieldID = aComFieldID;
    dwFrameID = aFrmID;
    memset(byClientIP,0,sizeof(byClientIP));
    uClientPort = 0;
}

IMsgNetLog& IMsgNetLog::operator= (const IMsgNetLog& other)
{
    if (this!=&other)
    {
        IMsgAppLogs::operator =(other);

        //
        iProtocolType = other.iProtocolType;
        iEventType = other.iEventType;
        dwFrameID = other.dwFrameID;
        dwComfieldID = other.dwComfieldID;
        strUserName = other.strUserName;
        memcpy(byClientIP,other.byClientIP,sizeof(byClientIP));
        uClientPort = other.uClientPort;
        wNumClient = other.wNumClient;
    }

    return *this;
}

IMPLEMENT_SERIAL(IMsgNetLog,IMsgAppLogs,1)

// From IMsgAppLogs

IMsgAppLogs* IMsgNetLog::Duplicate() const
{
    IMsgNetLog* pDump = new IMsgNetLog;
    if (pDump!=NULL)
    {
        pDump->operator =(*this);
    }
    return pDump;
}

void IMsgNetLog::GetLogType_str(CString& strLogType) const
{
    switch(iLogType)
    {

    case ELGT_Network:
        {
            strLogType = _T("网络日志");
        }
        break;

    default:
        {
            IMsgAppLogs::GetLogType_str(strLogType);
        }
    }
}

void IMsgNetLog::Serialize(CArchive& ar)
{
    // 
    IMsgAppLogs::Serialize(ar);

    // 
    if (ar.IsStoring())
    {
        ar  <<iEventType<<iProtocolType<<dwFrameID
            <<strUserName
            <<byClientIP[0]<<byClientIP[1]<<byClientIP[2]<<byClientIP[3]<<uClientPort;
    }
    else
    {
        ar  >>iEventType>>iProtocolType>>dwFrameID
            >>strUserName
            >>byClientIP[0]>>byClientIP[1]>>byClientIP[2]>>byClientIP[3] >>uClientPort;
    }

}

// Member functions
void IMsgNetLog::GetEventType_str(CString& strEvent) const
{
    ASSERT(iLogType==ELGT_Network);

    switch(iEventType)
    {
    case ENLT_NEWCONNECTION:
        {
            strEvent = _T(" 创建一个新连接。");
        }
        break;
    case ENLT_SENDFRAME:
        {
            strEvent = _T(" 发送数据。");
        }
        break;
    case ENLT_RECEIVEFRAME:
        {
            strEvent = _T(" 收到数据。");
        }
        break;
    case ENLT_CLOSECONNECT:
        {
            strEvent = _T(" 连接已无效。");
        }
        break;
    case ENLT_DELCONNECTION:
        {
            strEvent = _T(" 删除一个连接。");
        }
        break;
    default:
        {
            strEvent.Format("未知的网络事件。");
        }
    }
}

// 
void IMsgNetLog::GetStrIp(CString& strIP)
{
    strIP.Format(_T("%d.%d.%d.%d"),byClientIP[0],byClientIP[1],byClientIP[2],byClientIP[3]);
}
void IMsgNetLog::GetStrPort(CString& strPort)
{
    strPort.Format(_T("%d"),uClientPort);
}

//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
CNetLogMgr::CNetLogMgr(void)
{
}

CNetLogMgr::~CNetLogMgr(void)
{
    
}



void CNetLogMgr::GetNetLogList(CNetLogList& aNetLogList)
{

    POSITION pos = m_AppLogList.GetHeadPosition();
    while (pos)
    {
        PIMsgAppLogs pAppLog = m_AppLogList.GetNext(pos);
        if (pAppLog->IsKindOf(RUNTIME_CLASS(IMsgNetLog)))
        {
            aNetLogList.AddTail((PIMsgNetLog)pAppLog);
        }
    }
}

void CNetLogMgr::GetAllLogList(CAppLogList& aAppLogList)
{
    aAppLogList.RemoveAll();
    aAppLogList.AddTail(&m_AppLogList);
}

void  CNetLogMgr::FilterLog(int iEvtType,CString strIPAdd)
{
    CNetLogList netLogList;
    GetNetLogList(netLogList);
    POSITION pos = netLogList.GetHeadPosition();


    POSITION pos1 = pos;
    while (pos)
    {
        pos1 = pos;
        PIMsgNetLog pLog = netLogList.GetNext(pos);

        //
        CString strTmp;
        strTmp.Format("%d.%d.%d.%d",pLog->byClientIP[0],pLog->byClientIP[1],
            pLog->byClientIP[2],pLog->byClientIP[3]);

        if ( (iEvtType!=0 && iEvtType!=pLog->iEventType) ||
            (strTmp!="" && strTmp != strIPAdd) )
        {
            m_AppLogList.RemoveAt(pos);
            delete pLog;
            pos = pos1;
        }
    }
}


void  CNetLogMgr::GetIPAddr(CStringList& strIPAddrList)
{
    CNetLogList netLogList;
    GetNetLogList(netLogList);
    POSITION pos = netLogList.GetHeadPosition();
    while (pos)
    {
        PIMsgNetLog pLog = netLogList.GetNext(pos);
        //
        CString strIPAddr;
        strIPAddr.Format("%d.%d.%d.%d",pLog->byClientIP[0],
            pLog->byClientIP[1],
            pLog->byClientIP[2],
            pLog->byClientIP[3]);
        if (strIPAddrList.Find(strIPAddr)==NULL)
        {
            strIPAddrList.AddTail(strIPAddr);
        }
    }
}
