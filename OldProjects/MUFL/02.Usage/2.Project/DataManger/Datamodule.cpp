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
    aLog.strComments.Format(_T("���ڳ�ʼ����ͨ���������ݴ���ģ�顭��"));
    SendModuleMsg(aLog);*/

    //
    return TRUE;
}
BOOL CDataModule::OnStart()
{
    //
    IMsgAppLogs aLog;
    aLog.strComments.Format(_T("�����������ݴ���ģ�顭��"));
    SendModuleMsg(aLog);

    // 
    if (!CNBaseModule::OnInitModule())
    {
        return FALSE;
    }

#if 0
    IMsgAppLogs aLog;

    //** ���ӵ����ݿ�
    if (::MessageBox(NULL,"�Ƿ����ӵ����ݿ⣿","���ݿ������ʾ",MB_YESNO)== IDYES)
    {
        aLog.strComments.Format(_T("�������ӵ����ݿ⡭��"));
        SendModuleMsg(aLog);

        if (!ConnectToDB())
        {
            aLog.logTime = COleDateTime::GetCurrentTime();
            aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
            aLog.strComments.Format(_T("���ӵ����ݿ�ʧ�ܣ�"));
            SendModuleMsg(aLog);

            if (MessageBox(NULL,"���ӵ����ݿ�ʧ�ܣ��Ƿ����������","��ʾ",MB_ICONQUESTION|MB_YESNO)!=IDYES)
            {
                return FALSE;
            }
            
        }
        else
        {
            aLog.logTime = COleDateTime::GetCurrentTime();
            aLog.strComments.Format(_T("�ɹ����ӵ����ݿ⣡"));
            SendModuleMsg(aLog);
        }
    }
    else
    {
        aLog.logTime = COleDateTime::GetCurrentTime();
        aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
        aLog.strComments.Format(_T("ȡ�������ݿ�����ӣ�"));
        SendModuleMsg(aLog);
    }
#endif

    aLog.logTime = COleDateTime::GetCurrentTime();
    aLog.strComments.Format(_T("���ݴ���ģ����������"));
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
        // ���ݿ���
    case EDB_CONNECTION_STATE:
        {
            BOOL bOldState = m_OracleDB.IsOpen();

            BOOL bFlag = IsDBConnected();
            
            if (!bFlag)
            {
                IMsgAppLogs aLog;
                aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
                aLog.strComments.Format(_T("��⵽���ݿ�����쳣���������ݿ��Ƿ�������ת��"));
                SendModuleMsg(aLog);
                //
                m_OracleDB.Close();
            }

            if (bFlag && !bOldState)
            {
                // ������������
                if (ConnectToDB())
                {
                    IMsgAppLogs aLog;
                    aLog.strComments.Format(_T("�������ӵ����ݿ�ɹ���"));
                    SendModuleMsg(aLog);
                }
                else
                {
                    IMsgAppLogs aLog;
                    aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
                    aLog.strComments.Format(_T("�������ӵ����ݿ�ʧ�ܣ�"));
                    SendModuleMsg(aLog);
                }
            }

            // ���ݿ���ظ�
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
    //�������ļ��ж�ȡ���ݿ����
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

    //** �������ļ��ж�ȡ���ݿ����
    CString strDataSource,strUserID,strPWD;
    GetDBCnntPara(strDataSource,strUserID,strPWD);

    //** ���ӵ����ݿ�
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
    aLog.strComments.Format(_T("�����ͷ����ݡ���"));
    NbsSendModuleMsg(&aLog);
    m_OracleDB.Close();
}

BOOL CDataModule::IsDBConnected()
{
    CAdoConnection testDB;

    // �������ļ��ж�ȡ���ݿ����
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