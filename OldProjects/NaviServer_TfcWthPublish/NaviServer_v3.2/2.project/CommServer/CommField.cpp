// CommField.cpp: implementation of the CCommField class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <math.h>
#include "CommField.h"



#pragma warning(disable:4311)
#pragma warning(disable:4312)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CCommField::CCommField(DWORD dwID,SOCKET aNewSocket,MIOSckObserver& aObserver,int iType):
	CIOSocket(aNewSocket,aObserver,iType)
{
    //TRACE("FiledID = %d\n",dwFildID);
    //
    //InitializeCriticalSection(&m_CriticalSection);

	m_dwSlfID = dwID;
    //
}

CCommField::~CCommField()
{
    Close();

    //DeleteCriticalSection(&m_CriticalSection);
}

void CCommField::Close()
{   
    // 1. Enter
    //EnterCriticalSection(&m_CriticalSection);


    if (m_iRunningState!=ERS_CLOSED)
    {
		m_iRunningState = ERS_CLOSED;

		CIOSocket::Close();
    }


    // Leaving
    //LeaveCriticalSection(&m_CriticalSection);
}


///////////////////////////////////////////////////////////////////////////////////

DWORD CCommField::GetFieldID(void)
{
	return m_dwSlfID;
}


BOOL CCommField::IsActive() const
{
    return (m_iRunningState==ERS_ACTIVE);
}
void CCommField::Active()
{
    m_iRunningState = ERS_ACTIVE;
}
void CCommField::Invalidate()
{
    m_iRunningState = ERS_INVALID;
}
BOOL CCommField::IsInvalid() const
{
    return (m_iRunningState==ERS_INVALID);
}
BOOL CCommField::IsClosed() const
{
    return (m_iRunningState==ERS_CLOSED);
}
void CCommField::SetUserInf(const CString& strUserName)
{
	m_selfAttri.m_strUserName = strUserName;
}
void CCommField::GetUserInf(CString& strUserName)
{
	strUserName = m_selfAttri.m_strUserName;
}
void CCommField::GetUserInf(char* cUserName)
{
	if (cUserName != NULL)
	{
		strcpy(cUserName,m_selfAttri.m_strUserName.GetBuffer(0));
	}
}

///////////////////////////////////////////////////////////////////////////////

void CCommField::InstanceParser(CBaseFpProvider*& pBfp)
{

    switch(GetProtocolType())
    {
    case TBusinessFrm::E_PRO_FLAG:
        {
            pBfp = new CBusinessFrameMgr;
        }
        break;

    case TMobileFrameBin::E_PRO_FLAG:
        {
            pBfp = new CMobileFrameMgrBin();
        }
        break;

    case TMobileFrame_Char::E_PRO_FLAG:
        {
            pBfp = new CMobileFrameMgrChar();
        }
        break;

    case TSpFrame::E_PRO_FLAG:
        {
            pBfp = new CSPFrameMgr();
        }
        break;
    }

}

BOOL CCommField::PreActive()
{
    if ( !CIOSocket::PreActive() )
    {
        return FALSE;
    }

	Active();

	return TRUE;
}

// 
//void CCommField::OnFinishSendingRawData(DWORD dwLen)
//{
//	m_selfAttri.m_dwLenDataSent += dwLen;
//}

void CCommField::OnRecvRawData(LPBYTE pData, DWORD iLen)
{
    /*if (iLen>0)
    {
        m_selfAttri.m_dwLenDataRecv += iLen;
    }*/


    /* Code for test
#ifdef _DEBUG

    CFile cFile;
    CString strFilePath;
    strFilePath.Format("%d.txt",m_dwSlfID);

    if (cFile.Open(strFilePath,CFile::modeReadWrite|CFile::shareDenyNone) == FALSE)
    {
        cFile.Open(strFilePath,CFile::modeCreate|CFile::modeReadWrite|CFile::shareDenyNone);
    }
    cFile.SeekToEnd();
    cFile.Write(pData,iLen);
    cFile.Close();

#endif
    */
    

	//
	TRACE("\n原始数据(%d): ",iLen);
	for(DWORD i=0 ; i<iLen; i++)
	{
		TRACE("%d,",pData[i]);
	}
	TRACE(_T("\n"));
	//

	BYTE byTest[] = {0,1,0,0,0,5,0,2,2,0,7};
	SendRawData(byTest,sizeof(byTest));

	// to parse the raw data.
	//CIOSocket::OnRecvRawData(pData, iLen);
    
}
void CCommField::OnRecvFrame(TBaseProtocol* pFrame)
{
    // to do something ...

    //
    CIOSocket::OnRecvFrame(pFrame);

}
void CCommField::AddNetLog(const IMsgNetLog& aNewLog)
{
    PIMsgNetLog pNewLog = (PIMsgNetLog)aNewLog.Duplicate();
    m_selfAttri.AddNewLog(pNewLog);
}

PTCommfieldAtri CCommField::GetAttri() 
{
    m_selfAttri.m_dwLenDataRecv = (DWORD)RetrieveDataRecv();
    m_selfAttri.m_dwLenDataSent = (DWORD)RetrieveDataSent();
    return &(m_selfAttri);
}

BOOL CCommField::IsExpired() const
{
    COleDateTimeSpan ts = COleDateTime::GetCurrentTime() - m_selfAttri.m_upTime;
    return fabs(ts.GetTotalSeconds()) >= ETimeIntervalClean;
}

