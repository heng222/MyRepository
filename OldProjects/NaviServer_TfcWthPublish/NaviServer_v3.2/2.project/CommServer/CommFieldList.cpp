// CommFieldList.cpp: implementation of the CCommFieldList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CommFieldList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommFieldList::CCommFieldList()
{
    InitializeCriticalSection(&m_CriSection);
}

CCommFieldList::~CCommFieldList()
{
	DeleteCriticalSection(&m_CriSection);
}

void CCommFieldList::ClearList()
{
    EnterCriticalSection(&m_CriSection);

	while (GetHeadPosition())
    {
		delete RemoveHead();
	}

    LeaveCriticalSection(&m_CriSection);

}

BOOL CCommFieldList::SendAll(LPBYTE lpData, int iDataLen)
{
	BOOL bResult = TRUE;
	POSITION pos = GetHeadPosition();
	while (pos)
    {
		CCommField* pComField = (CCommField*)GetNext(pos);
		bResult &= pComField->SendRawData(lpData,iDataLen);
	}
	return bResult;
}

//BOOL CCommFieldList::SendExcept(LPBYTE lpData,int iDataLen,SOCKET sExcept)
//{
//	BOOL bResult = TRUE;
//	POSITION pos = GetHeadPosition();
//	while (pos) 
//    {
//		CCommField* pComField = (CCommField*)GetNext(pos);
//		if (pComField->m_hSocket != sExcept )
//		{
//			bResult &= pComField->SendRawData(lpData,iDataLen);
//		}	
//	}
//	return bResult;
//}

BOOL CCommFieldList::Delete(const DWORD& dwFieldID)
{
    EnterCriticalSection(&m_CriSection);

    //
    BOOL rc = FALSE;
	POSITION pos = GetHeadPosition();
	while (pos) 
    {
		CCommField* pComField = (CCommField*)GetAt(pos);
		if (pComField->GetFieldID() == dwFieldID) 
        {
			RemoveAt(pos);
			pComField->Close();
			delete pComField;
            pComField = NULL;
			rc = TRUE;
            break;
		}
		GetNext(pos);
	}

	//
    LeaveCriticalSection(&m_CriSection);

	return rc;
}

void CCommFieldList::AddHead(CCommField* newElement)
{
    EnterCriticalSection(&m_CriSection);
    //
	CObList::AddHead(newElement);
    //
    LeaveCriticalSection(&m_CriSection);
}

CCommField* CCommFieldList::GetCommField(DWORD dwFieldID)
{
    EnterCriticalSection(&m_CriSection);

    //
    BOOL bResult = FALSE;
    CCommField* pComField = NULL;
	POSITION pos = GetHeadPosition();
	while (pos)
    {
		pComField = (CCommField*)GetNext(pos);
		if (pComField->GetFieldID()==dwFieldID)
        {
			bResult = TRUE;
            break;
		}
    }

    //
    LeaveCriticalSection(&m_CriSection);

    //
    if (bResult)
    {
        return pComField;
    }
    else
    {
        return NULL;
    }
}

// 
WORD CCommFieldList::GetAuthCount(void)
{
	WORD wNum = 0;
	CCommField* pComField;
	//
	POSITION pos = GetHeadPosition();
	while (pos)
	{
		pComField = (CCommField*)GetNext(pos);
		if (pComField->IsActive())
		{
			wNum++;
		}
	}
	return wNum;
}

void CCommFieldList::CleanUp(int iType)
{
    EnterCriticalSection(&m_CriSection);

    // 
	CCommField* pComField=NULL;
	POSITION pos = GetHeadPosition();
	POSITION posOld;
	while (pos)
	{
		posOld = pos;
		pComField = (CCommField*)GetNext(pos);

        // 
        BOOL bInvalid = pComField->IsInvalid();
        BOOL bClosed = pComField->IsClosed();
        BOOL bExpired = pComField->IsExpired();
        if (bInvalid)
        {
            // close it when it's been invalidated.
            pComField->Close();
        }
		else if (bClosed&&bExpired)
		{
            // 1. Create a new log.
            IMsgNetLog aLog(IMsgNetLog::ENLT_DELCONNECTION,
                iType,pComField->GetFieldID());
            aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
            aLog.GetEventType_str(aLog.strComments);
            CString strTip;
            strTip.Format(_T(" 原因：Expired(连接时间：%s)。 标识符：%d"),
                pComField->GetAttri()->m_upTime.Format(_T("%Y-%m-%d %H:%M:%S")),pComField->GetFieldID());
            aLog.strComments += strTip;
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            NbsSendModuleMsg(&aLog);

            // 2. delete the object
			RemoveAt(posOld);
			delete pComField;
        }
    }

    LeaveCriticalSection(&m_CriSection);
}
