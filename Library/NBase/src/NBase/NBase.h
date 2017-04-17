

#ifndef __NBAE_H_DE9B599373C5_
#define __NBAE_H_DE9B599373C5_

//////////////////////////////////////////////////////////////////////////

#include "LogManager.h"
#include "INBaseObserver.h"
#include "NBaseModule.h"

//////////////////////////////////////////////////////////////////////////

class NBASE_EXT_API CNBase
{
private:

    /// <summary>
    /// Dispather
    /// </summary>
    static CImcDispatcher _dispatcher;

    /// <summary>
    /// AppLog handlers
    /// </summary>
    //static AppLogEventHandler _appLogEventHandler;

    /// <summary>
    /// NBASE observer
    /// </summary>
    static INBaseObserver* _observer;

    /// <summary>
    /// Log manager
    /// </summary>
    static CLogManager _logMgr;


    // Ӧ�ó���ĵ�ǰ·��
    static TString _exePath;

    /// <summary>
    /// ��־�ı��漶��
    /// Information: ��ʾ�������е���־��
    /// Warning: ��ʾֻ��������ΪWarning��Error����־��
    /// Error����ʾֻ��������ΪRunTimeError����־��
    /// </summary>
    static CAppLog::TLogType LogRecordLevel;

    /// <summary>
    /// the days for hold logs
    /// </summary>
    static unsigned short _logExpiredDays;

    /// <summary>        
    /// Append diagnostic information if the file already exists.
    /// </summary>
    static bool AppendToExsit;


//"properties"
public:

    /// <summary>
    /// ��ȡ��ǰӦ�ó����·��
    /// </summary>
    static TString get_ExePath();

    /// <summary>
    /// Get/Set the days for holding logs. (1 ~ 90)
    /// </summary>
    static unsigned short get_LogExpiredDays();
    static void set_LogExpiredDays(unsigned short value);

    /// <summary>
    /// Get the current diagnostic file path.
    /// </summary>
    static TString get_DiagFilePath();


//#region "public methods"
public:


    /// <summary>
    /// Initialize NBase Library
    /// </summary>
    /// <param name="obs">NBase observer</param>
    static void Initialize(INBaseObserver* obs);


    /// <summary>
    /// Register a module to NBASE lib
    /// </summary>
    /// <param name="module">NBaseModule object</param>
    /// <param name="ID">the module's ID</param>
    static void Register(CNBaseModule* module, int ID);
    

    /// <summary>
    /// Launch NBASE.
    /// No exception throws.
    /// </summary>
    static bool Launch();

    /// <summary>
    /// Terminat NBASE
    /// </summary>
    static void Terminate();

    /// <summary>
    /// transfer message synchronously.
    /// </summary>
    /// <param name="msg">the message to send.</param>
    static void SendMessage(PTImcMsg msg);

    /// <summary>
    /// transfer message asynchronously.
    /// </summary>
    /// <param name="msg">the message to post.</param>
    static void PostMessage(CImcMessage* msg);


    /// <summary>
    /// Save an application log
    /// </summary>
    /// <param name="log">An application log to save.</param>
    static void SaveAppLog(CAppLog* log);

    /// <summary>
    /// Notify an application log.
    /// </summary>
    /// <param name="log">The log to notify.</param>
    static void NotifyAppLog(CAppLog* log);

    /// <summary>
    /// Flush all cached log to file.
    /// </summary>
    static void FlushAppLog();

};


//////////////////////////////////////////////////////////////////////////
#endif