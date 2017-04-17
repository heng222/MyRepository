
/*
* ============================================================================
*  Name     : Internal module communication
*  Part of  : Auxiliary module
*  Created  : 19.11.2006 by Henry
*  Description: Free
*     
*  Version  : 1.2
*  Copyright: Copyright (c) 2007-2010. DCL-CHARY Network Corporation Ltd.
* ============================================================================
*/

#ifndef _NBASE_APPLICATION_LOGMANGER_38FKEIR
#define _NBASE_APPLICATION_LOGMANGER_38FKEIR
//////////////////////////////////////////////////////////////////////////

#include "AppLog.h"

//////////////////////////////////////////////////////////////////////////


// 日志管理器
#ifdef _DEBUG
class NBASE_EXT_API CLogManager
#else
class CLogManager
#endif
{
    static TString LOGPATH;

public:


    CLogManager();
	~CLogManager(); 


    // public new functions
public:

    // 打开
    void Open();
    // 保存日志
    void SaveAppLog(CAppLog* pLog);
    // 将缓冲中内容写入文件
    void Flush();
    // 关闭
    void Close();
    // 获取当前日志文件的绝对路径
    TString get_CurrentLogFilePath();
    // 获取日志目录
    static TString get_LogPath();


    // Private new functions
private:

    TString GetDiaglogPath() const;


    // Members
private:

    // sync lock
    CRITICAL_SECTION  m_CriticalSection;

    // 
    CFileStream m_logFileStream;

    // 
    TDateTime   m_logFileCreatedDT;

    // 当前日志文件的绝对路径 
    TString m_logFilePath;

};
//////////////////////////////////////////////////////////////////////////
//

#endif