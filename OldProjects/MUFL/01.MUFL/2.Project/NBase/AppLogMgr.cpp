#include "stdafx.h"
#include <direct.h>
#include "AppLogMgr.h"

#pragma warning(disable:4244)
//////////////////////////////////////////////////////////////////////////
//

// Constructor
IMsgAppLogs::IMsgAppLogs()
{
    //
    m_wMsgType = ESYS_NEW_LOG;
    SetDestModule(ID_MODULE_USERIF);
    AddDestModule(ID_MODULE_DATABASE);

    //
    iLogType = ELGT_System;
    iLogLevel = ELL_INFORMATION;
    logTime = COleDateTime::GetCurrentTime();


    EnableStorage(TRUE);

}

IMsgAppLogs::IMsgAppLogs(const IMsgAppLogs& aOther)
{
    *this = aOther;
}

IMsgAppLogs::IMsgAppLogs(const TString& strMsg)
{
	//
	m_wMsgType = ESYS_NEW_LOG;
	SetDestModule(ID_MODULE_USERIF);
	AddDestModule(ID_MODULE_DATABASE);

	//
	iLogType = ELGT_System;
	iLogLevel = ELL_INFORMATION;
	logTime = COleDateTime::GetCurrentTime();
	strComments = strMsg.c_str();


	EnableStorage(TRUE);

}


IMsgAppLogs::~IMsgAppLogs()
{
}

IMPLEMENT_SERIAL(IMsgAppLogs,TImcMsg,1)

// 
IMsgAppLogs& IMsgAppLogs::operator= (const IMsgAppLogs& other)
{
    if (this != &other)
    {
        TImcMsg::operator =(other);

        iLogType = other.iLogType;
        iLogLevel = other.iLogLevel;
        logTime = other.logTime;
        strComments = other.strComments;
        m_bIsStorage = other.m_bIsStorage;
    }

    return *this;
}

// From TImcMsg

IMsgAppLogs* IMsgAppLogs::Duplicate() const
{
    IMsgAppLogs* pDump = new IMsgAppLogs;
    if (pDump!=NULL)
    {
        *pDump = *this;
    }
    return pDump;
}

void IMsgAppLogs::Serialize(CArchive& ar)
{
    if ( ar.IsStoring() )
    {
        ar<<iLogType<<iLogLevel<<logTime<<strComments;
    }
    else
    {
        ar>>iLogType>>iLogLevel>>logTime>>strComments;
    }
}

// New Functions

void IMsgAppLogs::UpdateToCurrentTime()
{
    logTime = COleDateTime::GetCurrentTime();
}

void IMsgAppLogs::EnableStorage(BOOL bEnable/* =FALSE */)
{
    m_bIsStorage = bEnable;
}

BOOL IMsgAppLogs::IsStorage() const
{
    return m_bIsStorage;
}

// insertion operations
CArchive& AFXAPI operator<<(CArchive& ar, const IMsgAppLogs* pOb)
{
    ar<<pOb->iLogType<<pOb->iLogLevel<<pOb->logTime<<pOb->strComments;
    return ar;
}


// Virtual functions

void IMsgAppLogs::GetLogType_str(CString& strLogType) const
{
    switch(iLogType)
    {
    case ELGT_System:
        {
            strLogType = _T("ϵͳ��־");
        }
        break;

    default:
        {
            strLogType = _T("δ֪������־");
        }
    }
}


//////////////////////////////////////////////////////////////////////////
////////////////////  Class CAppLogMgr Definition  ///////////////////////


CAppLogMgr::CAppLogMgr(CAppLogMgr::TLMMode aMode):
                m_iMode(aMode)
{
    InitializeCriticalSection(&m_CriticalSection);
    m_strFilePath = _T(".\\"); // Set default directory

#ifdef _DEBUG
    m_wNumOfLogsInCache = 10;
#else
    m_wNumOfLogsInCache = 20;
#endif

}

CAppLogMgr::~CAppLogMgr(void)
{
    Close();

    //
    if (HANDLE(m_LogFile)!=INVALID_HANDLE_VALUE)
    {
        m_LogFile.Close();
    }

    DeleteCriticalSection(&m_CriticalSection);
}

void CAppLogMgr::ClearCache(void)
{
    EnterCriticalSection(&m_CriticalSection);

    POSITION pos = m_AppLogList.GetHeadPosition();
	while (m_AppLogList.GetHeadPosition())
	{
        PIMsgAppLogs pLog = m_AppLogList.RemoveHead();
        delete pLog;
	}

    //
    LeaveCriticalSection(&m_CriticalSection);
}

void CAppLogMgr::Close(void)
{
	WriteToFile();

    //��ջ���
	ClearCache();
    
}

void CAppLogMgr::SetMode(CAppLogMgr::TLMMode aMode/*=ELM_READONLY*/)
{
    m_iMode = aMode;
}

void CAppLogMgr::AddTail(PIMsgAppLogs pItem)
{
    if (m_iMode!=ELM_WRITEONLY)
    {
        return;
    }

    // 
    EnterCriticalSection(&m_CriticalSection);

	// �Ƿ���Ҫ�����µ���־�ļ�
	BOOL bCreateNew = FALSE;
	PIMsgAppLogs pLog;
	if (m_AppLogList.GetCount() != 0)
	{
		POSITION pos = m_AppLogList.GetHeadPosition();
		pLog = (PIMsgAppLogs)m_AppLogList.GetNext(pos);
		if (pItem->logTime.GetDay() != pLog->logTime.GetDay())
		{
			bCreateNew = TRUE;
		}
	}

	// �����Ƿ����
	BOOL bCacheFull = (m_AppLogList.GetCount()>=m_wNumOfLogsInCache);
    /*if (bCacheFull)
    {
        TRACE("�������,������־��\n");
    }*/
	

	// ��������е���Ŀ����MAXCOUNT����־���������ڲ�һ����
	// ��д�뵽�ļ�����ջ���
	CString strFileName;
	if ( bCacheFull || bCreateNew )
	{
		// ���滺���е���־
		WriteToFile();		

		// �����Ҫ�����µ���־�ļ�
		if (bCreateNew)
		{
            try
            {
                //�ȹرվɵ���־�ļ�
                if (HANDLE(m_LogFile)!=INVALID_HANDLE_VALUE)
                {
                    m_LogFile.Close();
                }
                //�ٲ����µ���־�ļ�
                strFileName = pItem->logTime.Format(_T("%Y-%m-%d.nel"));
                m_LogFile.Open(m_strFilePath+strFileName,
                    CFile::modeCreate|CFile::shareDenyNone|CFile::modeReadWrite);
            }
            catch (CException* e)
            {
                e->ReportError();
                e->Delete();
            }
		}
	}

	// ���뻺��
    if (pItem->IsSynchronous()) // ͬ����
    {
        PIMsgAppLogs pNewLog = pItem->Duplicate();
        ASSERT(pNewLog!=NULL);
        m_AppLogList.AddTail(pNewLog);
    }
    else
    {
        pItem->SetAutoDel(FALSE);
        m_AppLogList.AddTail(pItem);
    }


    LeaveCriticalSection(&m_CriticalSection);

}


void CAppLogMgr::WriteToFile(void)
{
    if (m_iMode!=ELM_WRITEONLY)
    {
        return;
    }


    EnterCriticalSection(&m_CriticalSection);

	if (m_AppLogList.GetCount()<=0)
	{
		// ������û������
		goto EXIT_LABEL;
	}
	else
	{
		// �ļ���û�д�,���ȴ��ļ�
		if ( HANDLE(m_LogFile)==INVALID_HANDLE_VALUE)
		{
            CString strFileName = GenerateFileName();
            CFileFind fileFind;
            if (fileFind.FindFile(strFileName))
            {
                if (!m_LogFile.Open(strFileName,CFile::shareDenyNone|CFile::modeReadWrite))
                {
                    AfxMessageBox(_T("����־�ļ�ʧ�ܣ�"));
                    goto EXIT_LABEL;
                }
            }
            else
            {
                if (!m_LogFile.Open(strFileName,CFile::modeCreate|CFile::shareDenyNone|CFile::modeReadWrite))
                {
                    AfxMessageBox(_T("������־�ļ�ʧ�ܣ�"));
                    goto EXIT_LABEL;
                }
            }

		}       

        // ȡ������ǰ��־�ĸ���
        ULONG ulLogCount = 0;
        if (m_LogFile.GetLength()>sizeof(ULONG))
        {
            // ������־ʱ��ȡ��ԭ�ļ�����־�ĸ���
            m_LogFile.SeekToBegin();
            m_LogFile.Read(&ulLogCount,sizeof(ULONG));

            // �޸���־�ĸ���
            m_LogFile.SeekToBegin();
            ulLogCount += m_AppLogList.GetCount();
            m_LogFile.Write(&ulLogCount,sizeof(ULONG));
        }
        else
        {
            ulLogCount = m_AppLogList.GetCount();

            // û����־ʱ�����滺�������ڵĸ���
            m_LogFile.SeekToBegin();
            m_LogFile.Write(&ulLogCount,sizeof(ULONG));
        }
        // ���ļ�ָ���ƶ����ļ�ĩβ
        m_LogFile.SeekToEnd();


		// �����µ���־
        CArchive ar(&m_LogFile,CArchive::store);
		PIMsgAppLogs pLog = NULL;
		POSITION pos = m_AppLogList.GetHeadPosition();
		while (pos)
		{
			pLog = (PIMsgAppLogs)m_AppLogList.GetNext(pos);
            CString strClassName(pLog->GetRuntimeClass()->m_lpszClassName);
            ar<<strClassName;
            pLog->Serialize(ar);
		}
        ar.Close();
		//

		// ��ձ����û���
		ClearCache();
	}

EXIT_LABEL:
    LeaveCriticalSection(&m_CriticalSection);

}


// ������־�����·����
void CAppLogMgr::SetPath(const CString& strExePath)
{
    m_strFilePath = strExePath; 

    // Create a new directory if not exist.
#if defined(UNICODE) || defined(_UNICODE)
    _wmkdir(m_strFilePath);
#else
    _mkdir(m_strFilePath);
#endif
    
}

void CAppLogMgr::SetCacheSize(BYTE byNumOfLogsInCache)
{
    if (MAXNUMLOGINCACHE>=byNumOfLogsInCache)
    {
        m_wNumOfLogsInCache = byNumOfLogsInCache;
    }
    else
    {
        m_wNumOfLogsInCache = 50;
    }
}

// ���ݻ����е���־ʱ�����һ���ļ���
CString CAppLogMgr::GenerateFileName(void) const
{
	CString strFileName;
	if (m_AppLogList.GetCount()>0)
	{
		POSITION pos = m_AppLogList.GetHeadPosition();
		PIMsgAppLogs log = (PIMsgAppLogs)m_AppLogList.GetNext(pos);
		strFileName = log->logTime.Format(_T("%Y-%m-%d.nel"));
		strFileName = m_strFilePath + strFileName;
	}
	return strFileName;
}

BOOL CAppLogMgr::ReadFromFile(const CString& strFilePath)
{
    if (m_iMode!=ELM_READONLY)
    {
        return FALSE;
    }

    CFile logFile;
    if (!logFile.Open(strFilePath,CFile::shareDenyNone|CFile::modeRead))
    {
        return FALSE;
    }

    //
    BOOL bRc = TRUE;

    //
    ClearCache();

    // ȡ����־����
    ULONG ulLogCount = 0;
    logFile.Read(&ulLogCount,sizeof(ULONG));

    //
    CArchive ar(&logFile,CArchive::load);

    for (ULONG ui=0; ui<ulLogCount; ui++)
    {
        CString strClassName;
        ar>>strClassName;
        CRuntimeClass* pRtClass = CRuntimeClass::FromName(strClassName);

        if (pRtClass)
        {
            PIMsgAppLogs pLog = (IMsgAppLogs*)pRtClass->CreateObject(strClassName);

            if (pLog)
            {
                pLog->Serialize(ar);
                m_AppLogList.AddTail(pLog);
            }
            else
            {
                AfxThrowMemoryException();
            }
        }
        else
        {
            TRACE(_T("��Ϊ%s������л�֧�֣�DECLARE_SERIAL(%s)����\n"),strClassName,strClassName);
            bRc = FALSE;
            break;
        }
    }
    ar.Close();

    //
    logFile.Close();

    return bRc;
}
