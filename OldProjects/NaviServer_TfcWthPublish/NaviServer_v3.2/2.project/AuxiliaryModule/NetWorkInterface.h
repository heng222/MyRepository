

#ifndef _NETWORK_INTERFACE_D834KFE89FKDR
#define _NETWORK_INTERFACE_D834KFE89FKDR


//////////////////////////////////////////////////////////////////////////

#include "InterfaceEx.h"
#include "NetLogMgr.h"



//////////////////////////////////////////////////////////////////////////
     


//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// ��Ҫ��UI��ʾ��ͨ��������
class TCommfieldAttrib 
{
public:
    COleDateTime   m_upTime;
    CString		   m_strUserName;
    CNetLogList     m_NetWorkLogList;
    DWORD          m_dwLenDataSent; // the total number of bytes sent
    DWORD          m_dwLenDataRecv;
    //CRITICAL_SECTION m_CriticalSection;

public:
    TCommfieldAttrib()
    {
        //InitializeCriticalSection(&m_CriticalSection);
        m_dwLenDataRecv = 0;
        m_dwLenDataSent = 0;
        m_upTime = COleDateTime::GetCurrentTime();
    }
    ~TCommfieldAttrib()
    {
        while (m_NetWorkLogList.GetHeadPosition())
        {
            delete m_NetWorkLogList.RemoveHead();
        }
        //DeleteCriticalSection(&m_CriticalSection);
    }

    void AddNewLog(PIMsgNetLog pNewLog)
    {
        //EnterCriticalSection(&m_CriticalSection);
        m_NetWorkLogList.AddTail(pNewLog);
        //LeaveCriticalSection(&m_CriticalSection);
    }
};
typedef TCommfieldAttrib* PTCommfieldAtri;



//** �õ�ָ��ͨ���������
struct IMsgRetrivComfldAttri: public TImcMsg
{
    int iProtocolType;  // IN
    DWORD dwComfieldID; // IN

    TCommfieldAttrib* pFieldAttri;

    // 
    IMsgRetrivComfldAttri()
    {
        pFieldAttri = NULL;
        m_wMsgType = ESCK_RETRIEVE_COMLOGS;
        SetSourceModule(ID_MODULE_USERIF);
        SetDestModule(ID_MODULE_NETWORK);
    }
};
typedef IMsgRetrivComfldAttri* PIMsgRetrivComfldAttri;



/************************************************************************/
/* Message = ESCK_CLEAN_UP                                              */
/************************************************************************/
// ��������
class IMsgNetWorkCleanUp : public TImcMsg
{
public:

    // Constructor && Destructor
    IMsgNetWorkCleanUp()
    {
        SetSourceModule(ID_MODULE_USERIF);
        SetDestModule(ID_MODULE_NETWORK);
        m_wMsgType = ESCK_CLEAN_UP;
    }

};
typedef IMsgNetWorkCleanUp* PINetWorkCleanUp;

/************************************************************************/
/* Message = ESCK_SCK_STATE                                             */
/************************************************************************/
// �õ�SCKģ���״̬����ǰ�Ŀͻ���...��
class IMsgGetSckState : public TImcMsg
{
public:
    DWORD       m_dwNumClient;      // ���ӵ�SCK�ͻ��˸���

    // Constructor && Destructor
    IMsgGetSckState()
    {
        SetDestModule(ID_MODULE_NETWORK);
        m_wMsgType = ESCK_SCK_STATE;
    }

    // New functions
};
typedef IMsgGetSckState* PIGetSckState;

/************************************************************************/
/* Message = ESCK_RECV_MOBILEFRAME                                      */
/************************************************************************/
// ��SOCKET���յ�Э��֡
class IMsgFrmRecved : public TImcMsg
{
public:
    DWORD       m_comFiledID;
    void*       m_pFrameBuf;    // Э��֡��TBaseProtocol��ĳһ���ࣩ

public:

    // Constructor && Destructor
    IMsgFrmRecved()
    {
        SetSourceModule(ID_MODULE_NETWORK);
        SetDestModule(ID_MODULE_NETWORK);
        //AddDestModule(ID_MODULE_USERIF);
        m_wMsgType = ESCK_RECV_FRAME;
        m_pFrameBuf = NULL;
    }
    ~IMsgFrmRecved()
    {

    }

};
typedef IMsgFrmRecved*  PIMsgFrmRecved;

/************************************************************************/
/* Message = ESCK_SEND_MOBILEFRAME                                      */
/************************************************************************/
// ��SOCKET����Э��֡
class IMsgFrmSending : public TImcMsg
{
public:
    DWORD  m_comFiledID;
    void*  m_pFrameBuf;    // �����͵�Э��֡��TBaseProtocol��ĳһ���ࣩ

public:

    // Constructor && Destructor
    IMsgFrmSending()
    {
        SetDestModule(ID_MODULE_NETWORK);
        AddDestModule(ID_MODULE_USERIF);
        m_wMsgType = ESCK_SEND_FRAME;
        m_pFrameBuf = NULL;
    }

};
typedef IMsgFrmSending*      PIMsgFrmSending;









//////////////////////////////////////////////////////////////////////////
#endif