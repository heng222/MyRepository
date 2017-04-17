
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

#include "InterComMsg.h"

//////////////////////////////////////////////////////////////////////////
// 

//////////////////////////////////////////////////////////////////////////
// Application Log 
class NBASE_EXT_API IMsgAppLogs : public TImcMsg
{

public:

    // the kind of logs.
    enum TLogType
    {
        ELGT_System = 0,        // System logs.
        
        ELGT_Reserved = 20,     // Reserved.
    };

    // the level of logs (information¡¢warning¡¢error)
    enum TLogLevel
    {
        ELL_INFORMATION=0,
        ELL_WARNING,
        ELL_ERROR,
        ELL_Reserved=20,        // Reserved
    };

    // Members

    // Common members.
    int             iLogType;       // See TLogType.
    int             iLogLevel;      // See the TLogLevel.
    COleDateTime    logTime;		// the time of log generated.
    CString		    strComments;    // Comments.


    // Storage attributes
private:

    BOOL      m_bIsStorage;


    // Member functions
public:

    // Constructors && Destructor
    IMsgAppLogs();
	IMsgAppLogs(const TString& strMsg);
    IMsgAppLogs(const IMsgAppLogs& aOther);

    virtual ~IMsgAppLogs();

    IMsgAppLogs& operator= (const IMsgAppLogs& other);

    DECLARE_SERIAL(IMsgAppLogs)

    // New public functions
public:

    void    UpdateToCurrentTime();

    void    EnableStorage(BOOL bEnable =FALSE );
    BOOL    IsStorage() const;

    // insertion operations
    AFX_API friend CArchive& AFXAPI operator<<(CArchive& ar, const IMsgAppLogs* pOb);


    // From TImcMsg
public:

    // virtual functions
    virtual IMsgAppLogs* Duplicate() const;
    virtual void Serialize(CArchive& ar);


    // New virtual functions
public:
    virtual void GetLogType_str(CString& strLogType) const; // must be overridden if you added your log type.

};

typedef IMsgAppLogs* PIMsgAppLogs;
typedef CList<PIMsgAppLogs,PIMsgAppLogs> CAppLogList;


//////////////////////////////////////////////////////////////////////////

#define     MAXNUMLOGINCACHE        200
// 
class NBASE_EXT_API CAppLogMgr
{
public:

    enum TLMMode
    {
        ELM_READONLY,
        ELM_WRITEONLY,
    };

    CAppLogMgr(TLMMode aMode=ELM_WRITEONLY);
	virtual ~CAppLogMgr(void);


    // public new functions
public:

    void    SetMode(TLMMode aMode=ELM_READONLY);
    
    void    SetCacheSize(BYTE byNumOfLogsInCache);

    void    SetPath(const CString& strLogPath);
    CString GenerateFileName(void) const;

    void    AddTail(PIMsgAppLogs pLog);

    void    WriteToFile();
    BOOL    ReadFromFile(const CString& strFilePath);

    void    ClearCache();
    void    Close();


    // Private new functions
private:


    // Members
protected:

    TLMMode      m_iMode;
    CAppLogList  m_AppLogList;

private:

    CString		 m_strFilePath;
    CFile		 m_LogFile;
    WORD         m_wNumOfLogsInCache;

    CRITICAL_SECTION  m_CriticalSection;

};
//////////////////////////////////////////////////////////////////////////
//

#endif