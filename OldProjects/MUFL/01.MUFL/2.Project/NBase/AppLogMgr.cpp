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
            strLogType = _T("系统日志");
        }
        break;

    default:
        {
            strLogType = _T("未知类型日志");
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

    //清空缓冲
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

	// 是否需要创建新的日志文件
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

	// 缓存是否溢出
	BOOL bCacheFull = (m_AppLogList.GetCount()>=m_wNumOfLogsInCache);
    /*if (bCacheFull)
    {
        TRACE("缓存溢出,保存日志！\n");
    }*/
	

	// 如果缓冲中的数目大于MAXCOUNT或日志产生的日期不一样，
	// 则写入到文件并清空缓冲
	CString strFileName;
	if ( bCacheFull || bCreateNew )
	{
		// 保存缓存中的日志
		WriteToFile();		

		// 如果需要产生新的日志文件
		if (bCreateNew)
		{
            try
            {
                //先关闭旧的日志文件
                if (HANDLE(m_LogFile)!=INVALID_HANDLE_VALUE)
                {
                    m_LogFile.Close();
                }
                //再产生新的日志文件
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

	// 放入缓冲
    if (pItem->IsSynchronous()) // 同步？
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
		// 缓存中没有数据
		goto EXIT_LABEL;
	}
	else
	{
		// 文件还没有打开,则先打开文件
		if ( HANDLE(m_LogFile)==INVALID_HANDLE_VALUE)
		{
            CString strFileName = GenerateFileName();
            CFileFind fileFind;
            if (fileFind.FindFile(strFileName))
            {
                if (!m_LogFile.Open(strFileName,CFile::shareDenyNone|CFile::modeReadWrite))
                {
                    AfxMessageBox(_T("打开日志文件失败！"));
                    goto EXIT_LABEL;
                }
            }
            else
            {
                if (!m_LogFile.Open(strFileName,CFile::modeCreate|CFile::shareDenyNone|CFile::modeReadWrite))
                {
                    AfxMessageBox(_T("创建日志文件失败！"));
                    goto EXIT_LABEL;
                }
            }

		}       

        // 取出保存前日志的个数
        ULONG ulLogCount = 0;
        if (m_LogFile.GetLength()>sizeof(ULONG))
        {
            // 当有日志时，取出原文件中日志的个数
            m_LogFile.SeekToBegin();
            m_LogFile.Read(&ulLogCount,sizeof(ULONG));

            // 修改日志的个数
            m_LogFile.SeekToBegin();
            ulLogCount += m_AppLogList.GetCount();
            m_LogFile.Write(&ulLogCount,sizeof(ULONG));
        }
        else
        {
            ulLogCount = m_AppLogList.GetCount();

            // 没有日志时，保存缓冲中日期的个数
            m_LogFile.SeekToBegin();
            m_LogFile.Write(&ulLogCount,sizeof(ULONG));
        }
        // 将文件指针移动到文件末尾
        m_LogFile.SeekToEnd();


		// 保存新的日志
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

		// 清空保存用缓存
		ClearCache();
	}

EXIT_LABEL:
    LeaveCriticalSection(&m_CriticalSection);

}


// 设置日志保存的路径名
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

// 根据缓存中的日志时间产生一个文件名
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

    // 取出日志个数
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
            TRACE(_T("请为%s添加序列化支持（DECLARE_SERIAL(%s)）！\n"),strClassName,strClassName);
            bRc = FALSE;
            break;
        }
    }
    ar.Close();

    //
    logFile.Close();

    return bRc;
}
