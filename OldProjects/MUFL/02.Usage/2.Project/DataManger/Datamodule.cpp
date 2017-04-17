#include "stdafx.h"
#include "datamodule.h"
#include "GlobalMacro.h"
#include "TableAttrib.h"

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

CDataModule::CDataModule(CImcDispatcher& aDispatcher):
    CNBaseModule(aDispatcher,EMID)
{
    InitializeCriticalSection(&m_CriticalSection);
}

CDataModule::~CDataModule(void)
{
    DeleteCriticalSection(&m_CriticalSection);
}

//////////////////////////////////////////////////////////////////////////
// From CNBaseModule
BOOL CDataModule::OnInitModule()
{
    if (!CNBaseModule::OnInitModule())
    {
        return FALSE;
    }

    //
    /*IMsgAppLogs aLog;
    aLog.strComments.Format(_T("正在初始化交通与气象数据处理模块……"));
    SendModuleMsg(aLog);*/

    //
    return TRUE;
}
BOOL CDataModule::OnStart()
{
    //
    IMsgAppLogs aLog;
    aLog.strComments.Format(_T("正在启动数据处理模块……"));
    SendModuleMsg(aLog);

    // 
    if (!CNBaseModule::OnInitModule())
    {
        return FALSE;
    }

#if 0
    IMsgAppLogs aLog;

    //** 连接到数据库
    if (::MessageBox(NULL,"是否连接到数据库？","数据库操作提示",MB_YESNO)== IDYES)
    {
        aLog.strComments.Format(_T("正在连接到数据库……"));
        SendModuleMsg(aLog);

        if (!ConnectToDB())
        {
            aLog.logTime = COleDateTime::GetCurrentTime();
            aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
            aLog.strComments.Format(_T("连接到数据库失败！"));
            SendModuleMsg(aLog);

            if (MessageBox(NULL,"连接到数据库失败，是否继续启动？","提示",MB_ICONQUESTION|MB_YESNO)!=IDYES)
            {
                return FALSE;
            }
            
        }
        else
        {
            aLog.logTime = COleDateTime::GetCurrentTime();
            aLog.strComments.Format(_T("成功连接到数据库！"));
            SendModuleMsg(aLog);
        }
    }
    else
    {
        aLog.logTime = COleDateTime::GetCurrentTime();
        aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
        aLog.strComments.Format(_T("取消到数据库的连接！"));
        SendModuleMsg(aLog);
    }
#endif

    aLog.logTime = COleDateTime::GetCurrentTime();
    aLog.strComments.Format(_T("数据处理模块已启动。"));
    SendModuleMsg(aLog);

    return TRUE;
}
BOOL CDataModule::OnActive()
{
    if (!CNBaseModule::OnActive())
    {
        return FALSE;
    }

    return TRUE;
}

// On receive message from other modules.
void CDataModule::OnRecvIMCMessage(PTImcMsg aImcMsg)
{
    switch(aImcMsg->GetMsgType())
    {
        // 数据库检测
    case EDB_CONNECTION_STATE:
        {
            BOOL bOldState = m_OracleDB.IsOpen();

            BOOL bFlag = IsDBConnected();
            
            if (!bFlag)
            {
                IMsgAppLogs aLog;
                aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
                aLog.strComments.Format(_T("检测到数据库出现异常！请检测数据库是否正常运转。"));
                SendModuleMsg(aLog);
                //
                m_OracleDB.Close();
            }

            if (bFlag && !bOldState)
            {
                // 立即重新连接
                if (ConnectToDB())
                {
                    IMsgAppLogs aLog;
                    aLog.strComments.Format(_T("重新连接到数据库成功。"));
                    SendModuleMsg(aLog);
                }
                else
                {
                    IMsgAppLogs aLog;
                    aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
                    aLog.strComments.Format(_T("重新连接到数据库失败！"));
                    SendModuleMsg(aLog);
                }
            }

            // 数据库检测回复
            IMsgDBCntTest msg;
            msg.SetType(IMsgDBCntTest::E_RESPONSE);
            msg.bResult = bFlag;
            NbsSendModuleMsg(&msg);
        }
        break;
    }

    // 
    CNBaseModule::OnRecvIMCMessage(aImcMsg);
}

// On receive message from internal objects.
BOOL CDataModule::OnRecvInterMessage(PTImcMsg aImcMsg)
{
    return CNBaseModule::OnRecvInterMessage(aImcMsg);
}

void CDataModule::OnClose()
{
    Close();

    //
    CNBaseModule::OnClose();
}

//////////////////////////////////////////////////////////////////////////
// New Functions
void CDataModule::GetDBCnntPara(CString& strSource,CString& strUsername,CString& strPwd)
{
    //从配置文件中读取数据库参数
    TCHAR cTemp[300];
    GetPrivateProfileString(CFG_APPNAME_DATABASE,_T("DataSource"),0,cTemp,300,GetExePath()+CString(PATH_CONFIGURE_FILE));
    strSource = cTemp;
    GetPrivateProfileString(CFG_APPNAME_DATABASE,_T("UserID"),0,cTemp,300,GetExePath()+CString(PATH_CONFIGURE_FILE));
    strUsername = cTemp;
    GetPrivateProfileString(CFG_APPNAME_DATABASE,_T("Password"),0,cTemp,300,GetExePath()+CString(PATH_CONFIGURE_FILE));
    strPwd = cTemp;
}

BOOL CDataModule::ConnectToDB()
{
    m_OracleDB.Close();

    //** 从配置文件中读取数据库参数
    CString strDataSource,strUserID,strPWD;
    GetDBCnntPara(strDataSource,strUserID,strPWD);

    //** 连接到数据库
    if (!m_OracleDB.ConnectOracle(strDataSource,strUserID,strPWD))
    {
        m_OracleDB.Close();
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

void CDataModule::Close(void)
{
    IMsgAppLogs aLog;

    // 
    aLog.logTime = COleDateTime::GetCurrentTime();
    aLog.strComments.Format(_T("正在释放数据……"));
    NbsSendModuleMsg(&aLog);
    m_OracleDB.Close();
}

BOOL CDataModule::IsDBConnected()
{
    CAdoConnection testDB;

    // 从配置文件中读取数据库参数
    CString strDataSource,strUserID,strPWD;
    GetDBCnntPara(strDataSource,strUserID,strPWD);

    if (testDB.ConnectOracle(strDataSource,strUserID,strPWD))
    {
        testDB.Close();
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}