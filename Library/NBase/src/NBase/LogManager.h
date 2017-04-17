
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


// ��־������
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

    // ��
    void Open();
    // ������־
    void SaveAppLog(CAppLog* pLog);
    // ������������д���ļ�
    void Flush();
    // �ر�
    void Close();
    // ��ȡ��ǰ��־�ļ��ľ���·��
    TString get_CurrentLogFilePath();
    // ��ȡ��־Ŀ¼
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

    // ��ǰ��־�ļ��ľ���·�� 
    TString m_logFilePath;

};
//////////////////////////////////////////////////////////////////////////
//

#endif