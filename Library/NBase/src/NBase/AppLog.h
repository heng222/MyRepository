

#ifndef _NBASE_APPLOG_H_58PO98UYETHBGY
#define _NBASE_APPLOG_H_58PO98UYETHBGY
//////////////////////////////////////////////////////////////////////////


#include "ImcMessage.h"

//////////////////////////////////////////////////////////////////////////
// Application Log 
class NBASE_EXT_API CAppLog : public CImcMessage
{

public:

    // the level of logs
    enum TLogType
    {
        ELL_INFORMATION,
        ELL_WARNING,
        ELL_ERROR,
    };

    // 根据日志类型获取描述信息
    static TString GetStringLogType(TLogType type);

    // TLogLevel.
    TLogType        iLogType;       

    // the time of log generated.
    TDateTime       timestamp;		

    // Comments.
    CString		    strComments;    

    // Continue to run?
    bool bContinue;

    // Storage attributes
private:

    // TODO
    BOOL      m_bIsStorage;


    // Member functions
public:

    // Constructors && Destructor
    CAppLog();
    CAppLog(const TString& strMsg);
    CAppLog(const CAppLog& aOther);

    virtual ~CAppLog();

    CAppLog& operator= (const CAppLog& other);

    // TODO
    DECLARE_SERIAL(CAppLog)

    // New public functions
public:

    void    UpdateToCurrentTime();

    void    EnableStorage(BOOL bEnable =FALSE );
    BOOL    IsStorage() const;

    // insertion operations
    AFX_API friend CArchive& AFXAPI operator<<(CArchive& ar, const CAppLog* pOb);


    // From TImcMsg
public:

    // virtual functions
    // TODO
    virtual CAppLog* Duplicate() const;
    virtual void Serialize(CArchive& ar);


};

typedef CAppLog* PIMsgAppLogs;
typedef CList<PIMsgAppLogs,PIMsgAppLogs> CAppLogList;

//////////////////////////////////////////////////////////////////////////
#endif