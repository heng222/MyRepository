#include "stdafx.h"
#include <direct.h>
#include "LogManager.h"

using namespace std;
//#pragma warning(disable:4244)
//////////////////////////////////////////////////////////////////////////
//

const TString LOGFOLDER = _T("Diagnostics");

//////////////////////////////////////////////////////////////////////////
////////////////////  Class CAppLogMgr Definition  ///////////////////////
TString CLogManager::LOGPATH = _T("");

CLogManager::CLogManager()
{
    InitializeCriticalSection(&m_CriticalSection);

    CLogManager::LOGPATH = GetDiaglogPath();

    if (!CDirectory::Exists(CLogManager::LOGPATH))
    {
        CDirectory::CreateDirectory(CLogManager::LOGPATH);
    }
}

CLogManager::~CLogManager(void)
{
    Close();

    DeleteCriticalSection(&m_CriticalSection);
}

void CLogManager::Close(void)
{
    m_logFileStream.Close();
}

TString CLogManager::get_CurrentLogFilePath()
{
    return m_logFilePath;
}


TString CLogManager::get_LogPath()
{
    return CLogManager::LOGPATH;
}

TString CLogManager::GetDiaglogPath() const
{
    TCHAR tmpBuf[MAX_PATH];
    CSysUtils::GetProcessHostPath(tmpBuf);
    TString strPath = tmpBuf;
    strPath.append(LOGFOLDER);
    strPath.append(_T("\\"));
    return strPath;
}


void CLogManager::Open()
{
    LPCTSTR lplogPath = CLogManager::LOGPATH.c_str();

    // 删除过期的日志
    TString strPath = lplogPath;
    strPath.append(_T("*.*"));
    CDirectory::DeleteExpiredFiles(strPath, 1);

    // 创建或打开新的日志
    m_logFilePath = CStringUtility::Format(_T("%sdiag%04d%02d%02d.log"),
        lplogPath,
        m_logFileCreatedDT.Year,
        m_logFileCreatedDT.Month,
        m_logFileCreatedDT.Day);

    m_logFileStream.OpenTextFile(m_logFilePath.c_str());
}

void CLogManager::SaveAppLog(CAppLog* pLog)
{
    EnterCriticalSection(&m_CriticalSection);

    // 是否需要新建日志文件
    TDateTime now;
    if (now.Day != m_logFileCreatedDT.Day
        || now.Month != m_logFileCreatedDT.Month
        || now.Year != m_logFileCreatedDT.Year)
    {
        m_logFileCreatedDT.LoadCurrentDateTime();

        Open();
    }

    // 格式化日志文本并输出
    TString text = CStringUtility::Format(_T("[%04d-%02d-%02d %02d:%02d:%02d.%d]\t[%s]\t[TID %ld]\t%s"), 
        pLog->timestamp.Year, pLog->timestamp.Month, pLog->timestamp.Day, 
        pLog->timestamp.Hour, pLog->timestamp.Minute, pLog->timestamp.Second, 
        pLog->timestamp.MilliSeconds,
        CAppLog::GetStringLogType(pLog->iLogType).c_str(), 
        GetCurrentThreadId(), 
        pLog->strComments);

    m_logFileStream.WriteLine(text);

    LeaveCriticalSection(&m_CriticalSection);
}

void CLogManager::Flush()
{
    m_logFileStream.Flush();
}

