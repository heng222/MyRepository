// CommFieldMag.cpp: implementation of the CCommFieldMgr class.
//
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CommFieldMgr.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DWORD CCommFieldMgr::m_nComfCounter = 0;

#pragma warning(disable:4355)
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
CCommFieldMgr::CCommFieldMgr(MComFiledMgrObserver& aObserver):m_Observer(aObserver)
{
    //InitializeCriticalSection(&m_CriticalSection);

}

CCommFieldMgr::~CCommFieldMgr()
{
    //DeleteCriticalSection(&m_CriticalSection);
    m_ClientList.ClearList();
    m_ServerList.ClearList();
}

//////////////////////////////////////////////////////////////////////

void CCommFieldMgr::Clear()
{
    Close();
    m_ClientList.ClearList();
    m_ServerList.ClearList();
}

void CCommFieldMgr::Close()
{	
    //* Close all Communication Fields.
    POSITION pos = m_ServerList.GetHeadPosition();
    while (pos)
    {
        CCommField* pComField = (CCommField*)m_ServerList.GetNext(pos);
        InvalidateCommFiled(pComField);
        pComField->Close();
    }

    pos = m_ClientList.GetHeadPosition();
    while (pos)
    {
        CCommField* pComField = (CCommField*)m_ClientList.GetNext(pos);
        InvalidateCommFiled(pComField);
        pComField->Close();
    }

	//
	CIOSocketMgr::Close();

}

/**
    Must be invoked before Open.
*/
void CCommFieldMgr::InitProfile(TComMgrProfile::TSelfStatus aStatus,
                                TSockAddr aSockAddr,
                                int iProtocolType)
{
    m_comMgrProfile.m_iStatus = aStatus;
    m_comMgrProfile.m_serverAddr = aSockAddr;
    m_comMgrProfile.m_iProType = iProtocolType;
    
}

BOOL CCommFieldMgr::OpenCMG(int iClientPort, CString strClientIPAddr)
{

    if ( m_comMgrProfile.m_iStatus==TComMgrProfile::ECMP_SERVER ) 
    {
        //------------------------- SERVER --------------------------------------
        BOOL bRC = CIOSocketMgr::StartService(m_comMgrProfile.m_serverAddr);
		if (!bRC)
		{
			return FALSE;
		}
	}
	else
    {
        // ------------------------- CLIENT -------------------------------

		// client address
        TSockAddr clientAddr(strClientIPAddr,iClientPort);

        SOCKET nSocket = socket(AF_INET,SOCK_STREAM,0);
        if (nSocket==INVALID_SOCKET )
        {
            return FALSE;
        }

        // create a new instance of CCommField.
        CCommField* pComField = new CCommField(NextFiledID(),nSocket,*this,m_comMgrProfile.m_iProType);
        pComField->SetServerAddr(m_comMgrProfile.m_serverAddr);


        // 
        if (iClientPort>5000 || !strClientIPAddr.IsEmpty())
        {
            pComField->SetClientAddr(clientAddr);
            // bind
            if (bind(nSocket,(LPSOCKADDR)(&clientAddr),sizeof(clientAddr))!=0) 
            {                
                delete pComField;
                return FALSE;
            }
        }

        
        if (!pComField->ActiveIoSck(TRUE))
        {
            TRACE("connect failed!\n");
            delete pComField;
            return FALSE;
        }

        int iLen  =sizeof(clientAddr);
        getsockname(nSocket,(SOCKADDR*)&clientAddr,&iLen);
#ifdef _DEBUG
        CString strIP = clientAddr.DottedDecimal();
        int iPort = clientAddr.Port();
#endif
        pComField->SetClientAddr(clientAddr);


		//
		m_ServerList.AddHead(pComField);
	}
	
	
    //
	return TRUE;
}
//

WORD CCommFieldMgr::GetClientNum(BOOL bAuth)
{
	if (bAuth)
	{
		return m_ClientList.GetAuthCount();
	}
	else
	{
		return (WORD)m_ClientList.GetCount();
	}
}


WORD CCommFieldMgr::GetServerNum(void)
{
    return (WORD)m_ServerList.GetCount();
}


CCommField* CCommFieldMgr::GetCommField(DWORD dwFieldID)
{
    CCommField* pCommField = NULL;
    if (m_comMgrProfile.m_iStatus == TComMgrProfile::ECMP_CLIENT)
    {
        if(m_ServerList.GetCount()>0)
        {
            return (CCommField*)m_ServerList.GetHead();
        }      
    }
    else
    {
        pCommField = m_ClientList.GetCommField(dwFieldID);
    }
    return pCommField;
}


BOOL CCommFieldMgr::InvalidateCommFiled(CCommField* pCommField)
{    
    ASSERT(pCommField!=NULL);

    // 产生新的网络日志 
    IMsgNetLog aLog(IMsgNetLog::ENLT_CLOSECONNECT,
        m_comMgrProfile.m_iProType,pCommField->GetFieldID());
    aLog.wNumClient = GetClientNum(FALSE);
    aLog.GetEventType_str(aLog.strComments);
    pCommField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
    NbsSendModuleMsg(&aLog);

    //
    pCommField->Invalidate();

    return TRUE;
}


void CCommFieldMgr::CleanUp(void)
{
    // 1. 清理无效的连接
	m_ClientList.CleanUp(m_comMgrProfile.m_iProType);

    // 2. 清理N秒没有收发数据的通信域
    // ......

}

void CCommFieldMgr::SendFrame(DWORD dwFieldID,PTBaseProtocol pFrame)
{
    if (m_comMgrProfile.m_iStatus == TComMgrProfile::ECMP_CLIENT)
    {
        SendFrame2All(pFrame);
    }
    else
    {

        CCommField* pCommField = GetCommField(dwFieldID);

        if (pCommField!=NULL && pFrame!=NULL)
        {
            pCommField->SendFrame(pFrame);
        }
    }
}


BOOL CCommFieldMgr::SendRawData2All(LPBYTE lpData, int iDataLen)
{
    if (m_ClientList.GetCount() !=0 || m_ServerList.GetCount() !=0 ) 
    {
        BOOL bResult = m_ClientList.SendAll(lpData,iDataLen);
        bResult &= m_ServerList.SendAll(lpData,iDataLen);
        return bResult;
    }
    else
    {
        return FALSE;
    }
}

BOOL CCommFieldMgr::SendFrame2All(PTBaseProtocol pFrame)
{
    CCommField* pCommField = NULL;

    POSITION pos = m_ClientList.GetHeadPosition();
    while ( pos )
    {
        pCommField = (CCommField*)m_ClientList.GetNext(pos);
        pCommField->SendFrame(pFrame);
    }

    pos = m_ServerList.GetHeadPosition();
    while ( pos )
    {
        pCommField = (CCommField*)m_ClientList.GetNext(pos);
        pCommField->SendFrame(pFrame);
    }

    return TRUE;
}


DWORD CCommFieldMgr::NextFiledID()
{
    m_nComfCounter = (m_nComfCounter+1)%EMaxFildID;
    return m_nComfCounter;
}

void CCommFieldMgr::OnNewConnection(SOCKET aNewSocket,const TSockAddr& clientAddr)
{
	ASSERT(aNewSocket != INVALID_SOCKET );


	// Create a new communication field attached with the specified protocol.
	DWORD dwFldID = NextFiledID();
	CCommField* pComField = NULL;
	try
	{
		pComField = new CCommField(dwFldID,aNewSocket,*this,m_comMgrProfile.m_iProType);
	}
	catch (CMemoryException* e)
	{
		e->ReportError();
		e->Delete();
	}
	catch (CException* e)
	{
		e->ReportError();
		e->Delete();
	}

	if (pComField!=NULL)
	{
		pComField->SetClientAddr(&clientAddr);
		pComField->SetServerAddr(&(m_comMgrProfile.m_serverAddr));
		if ( pComField->ActiveIoSck(FALSE) )
		{
			// 1. Save the instance.
			m_ClientList.AddHead(pComField);

			// 2. Create a new log.
			IMsgNetLog aLog(IMsgNetLog::ENLT_NEWCONNECTION,
				m_comMgrProfile.m_iProType,pComField->GetFieldID());                    
			aLog.wNumClient = GetClientNum(FALSE);
			pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
			aLog.GetEventType_str(aLog.strComments);
            CString strIdentifier;
            strIdentifier.Format("标识符：%d",pComField->GetFieldID());
            aLog.strComments += strIdentifier;                 
			NbsSendModuleMsg(&aLog);
		}
		else
		{
			// Create a new log.
			IMsgNetLog aLog(IMsgNetLog::ENLT_DELCONNECTION,
				m_comMgrProfile.m_iProType,DWORD(aNewSocket)); 
            aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
			aLog.wNumClient = GetClientNum(FALSE);
			pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
			aLog.strComments.Format(_T("检测到一个新连接，激活失败！"));
			NbsSendModuleMsg(&aLog);

			delete pComField;
		}
	}
	else
	{
		TRACE("out of memory!");
	}

}

void CCommFieldMgr::OnConnectionDown(CIOSocket* pIoSocket)
{
	ASSERT(pIoSocket);
	CCommField* pCommField = (CCommField*)pIoSocket;
	InvalidateCommFiled(pCommField);
}

void CCommFieldMgr::OnRecvFrame(TBaseProtocol* pProtocolFrame,CIOSocket* pIoSocket)
{
    m_Observer.OnCfdMgrRecvFrame(pProtocolFrame,(CCommField*)pIoSocket,this);
}
