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

    // ɾ�����ڵ���־
    TString strPath = lplogPath;
    strPath.append(_T("*.*"));
    CDirectory::DeleteExpiredFiles(strPath, 1);

    // ��������µ���־
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

    // �Ƿ���Ҫ�½���־�ļ�
    TDateTime now;
    if (now.Day != m_logFileCreatedDT.Day
        || now.Month != m_logFileCreatedDT.Month
        || now.Year != m_logFileCreatedDT.Year)
    {
        m_logFileCreatedDT.LoadCurrentDateTime();

        Open();
    }

    // ��ʽ����־�ı������
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

