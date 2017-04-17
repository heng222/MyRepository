
#include "stdafx.h"
#include "NBase.h"
#include "ImcDispatcher.h"

//////////////////////////////////////////////////////////////////////////

//
CImcDispatcher CNBase::_dispatcher;
CLogManager CNBase::_logMgr;
INBaseObserver* CNBase::_observer = NULL;
TString CNBase::_exePath = _T(".\\");


CAppLog::TLogType CNBase::LogRecordLevel = CAppLog::ELL_INFORMATION;

USHORT CNBase::_logExpiredDays = 5;

bool CNBase::AppendToExsit = false;


/// <summary>
/// 获取当前应用程序的路径
/// </summary>
TString CNBase::get_ExePath()
{
    return _exePath;
}

/// <summary>
/// Get/Set the days for holding logs. (1 ~ 90)
/// </summary>
USHORT CNBase::get_LogExpiredDays()
{
    return _logExpiredDays;
}
void CNBase::set_LogExpiredDays(USHORT value)
{
    if (value < 1)
    {
        _logExpiredDays = 1;
    }
    else if (value > 90)
    {
        _logExpiredDays = 90;
    }
    else
    {
        _logExpiredDays = value;
    }
}

/// <summary>
/// Get the current diagnostic file path.
/// </summary>
TString CNBase::get_DiagFilePath()
{
    return _logMgr.get_CurrentLogFilePath(); 
}





/// <summary>
/// Initialize NBase Library
/// </summary>
/// <param name="obs">NBase observer</param>
void CNBase::Initialize(INBaseObserver* obs)
{
    // set observer
    _observer = obs;

    // 1: Retrieve the appliation folder
    TCHAR tmpBuf[MAX_PATH];
    CSysUtils::GetProcessHostPath(tmpBuf);
    _exePath = tmpBuf;

    // create dispather
    //_dispatcher = new ImcDispatcher();

    // 2: 打开日志文件
    _logMgr.Open();

    // keep log
    // TODO
    /*string tip = (obs != NULL) ? obs.ToString() : "NULL";
    AppLog.CreateLogAndNotify(AppLog.Type.Information,
        "NBASE.Initialize(" + tip + ")");*/

}


void CNBase::Register(CNBaseModule* module, int ID)
{
    try
    {
        /*AppLog.CreateLogAndNotify(AppLog.Type.Information,
            "NBASE.Register(" + module.ToString() + "," + ID.ToString() + ")");*/

        if (_dispatcher.IsExistModule(ID))
        {
            throw std::exception("The moudle has been registered already!");
        }

        if (CNBaseModule::ModuleIDReserved >= ID)
        {
            // todo:
            //std::string message = "Module ID must be greater than NBaseModule.ReservedID(";
            //message.append(CNBaseModule::ModuleIDReserved);
            //throw std::exception( + NBaseModule.ReservedID + ")!");
        }

        module->set_ModuleID(ID);
        _dispatcher.AddModule(module);
    }
    catch (...)
    {
        throw std::exception("NBase register module failed!");            	
    }
}


bool CNBase::Launch()
{
    try
    {
        //AppLog.CreateLogAndNotify(AppLog.Type.Information,
            //"NBASE.Launch()");

        if (_observer != NULL)
        {
            _observer->OnLaunching();
        }

        int pass = _dispatcher.Initialize();

        if (pass == 0 && _observer != NULL)
        {
            _observer->OnStarting();
        }

        if (pass = 0)
        {
            pass = _dispatcher.Start();
        }

        if (pass)
        {
            _dispatcher.Active();
        }

        if (pass == 0 && _observer != NULL)
        {
            _observer->OnLaunched();
        }

        return pass==0;
    }
    catch (...)
    {
        //AppLog log = AppLog.CreateLog(AppLog.Type.InitFailure,ex.Message);
        //SaveAppLog(log);
        //NBASE.Terminate();
        return false;
    }
}

void CNBase::Terminate()
{
    try
    {
        _dispatcher.Close();

        if (_observer != NULL)
        {
            _observer->OnTerminate();
        }

        //AppLog.CreateLogAndNotify(AppLog.Type.Information,
            //"NBASE.Terminate()");

        
        _logMgr.Close();

        //_appLogEventHandler = NULL;
        _observer = NULL;

    }
    catch (...)
    {
        // just ignore
    }
}

void CNBase::SendMessage(PTImcMsg msg)
{
    if (msg->GetMsgType() <= CImcMessage::ReservedID)
    {
        // TODO:
        //throw std::exception("Message ID must be greater than ImcMessage.ReservedID(" + CImcMessage::ReservedID + ")!");
        throw std::exception("Message ID must be greater than ImcMessage.ReservedID!");
    }

    bool handled = false;
    if (_observer != NULL)
    {
        handled = _observer->PreDispatchMessage(msg);
    }

    if (!handled)
    {
        msg->SetSynchronous(TRUE);
        _dispatcher.DispatchMessage(msg, false);
    }
}

void CNBase::PostMessage(PTImcMsg msg)
{
    if (msg->GetMsgType() <= CImcMessage::ReservedID)
    {
        // TODO:
        //throw std::exception("Message ID must be greater than ImcMessage.ReservedID(" + CImcMessage::ReservedID + ")!");
        throw std::exception("Message ID must be greater than ImcMessage.ReservedID!");
    }

    bool handled = false;
    if (_observer != NULL)
    {
        handled = _observer->PreDispatchMessage(msg);
    }

    if (!handled)
    {
        msg->SetSynchronous(FALSE);
        _dispatcher.DispatchMessage(msg, true);
    }
}


void CNBase::SaveAppLog(CAppLog* log)
{
    // TODO:
    /*if (log == NULL)
    {
        throw new ArgumentNullException();
    }

    if (_logMgr == NULL)
    {
        throw new Exception("请先调用NBASE.Initialize");
    }*/

    try
    {
        if ((int)log->GetMsgType() >= (int)LogRecordLevel)
        {
            _logMgr.SaveAppLog(log);
        }
    }
    catch (...)
    {
        throw std::exception("保存日志失败。");
    }
}

void CNBase::NotifyAppLog(CAppLog* log)
{
    /*if (log == NULL)
    {
        throw new ArgumentNullException();
    }

    if (_logMgr == NULL)
    {
        throw new Exception("请先调用NBASE.Initialize");
    }*/

    // to save log.
    try
    {
        SaveAppLog(log);
    }
    catch (...)
    {
        // ignore
    }

    // 
    //if (_appLogEventHandler != NULL)
    //{
    //    Delegate[] operators = _appLogEventHandler.GetInvocationList();
    //    foreach (Delegate item in operators)
    //    {
    //        try
    //        {
    //            item.DynamicInvoke(log);
    //        }
    //        catch (System.Exception /*ex*/)
    //        {
    //            // ignore.
    //        }
    //    }
    //}

    //
    try
    {
        if (_observer != NULL)
        {
            _observer->OnRevcAppLog(log);
        }
    }
    catch (...)
    {
        // ignore
    }

}

/// <summary>
/// Flush all cached log to file.
/// </summary>
void CNBase::FlushAppLog()
{
    _logMgr.Flush();
}
