#include "stdafx.h"
#include "datamodule.h"
#include "GlobalMacro.h"

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

CDataModule::CDataModule(CImcDispatcher& aDispatcher):
    CNBaseModule(aDispatcher,EMID)
{
    InitializeCriticalSection(&m_CriticalSection);

    m_wndTfcView.AttachEngine(&m_TfcInfMgr);
    m_wndTfcParsed.AttachEngine(&m_TfcParsedMgr);
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

    // 打开交通路况信息管理器
    if (!m_TfcInfMgr.Open())
    {
        return FALSE;
    }

    // 打开Link管理器
    m_TfcParsedMgr.SetRoadNode(m_TfcInfMgr.GetRoadList());
    if (!m_TfcParsedMgr.Open())
    {
        return FALSE;
    }    

    // 打开解析器
    m_linkParser.AttachRoadList(m_TfcInfMgr.GetRoadList());
    m_linkParser.AttachLinkList(m_TfcParsedMgr.GetLinkList());
    m_linkParser.AttachLinkGridMgr(m_TfcParsedMgr.GetGridMgr());
    if (!m_linkParser.Open())
    {
        return FALSE;
    }
    

    // 
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


    // 
    /*IMsgAppLogs aLog;
    aLog.strComments.Format(_T("正在进行数据匹配……"));
    SendModuleMsg(aLog);*/


    return TRUE;
}

// On receive message from other modules.
void CDataModule::OnRecvIMCMessage(PTImcMsg aImcMsg)
{
    switch(aImcMsg->GetMsgType())
    {
        // 创建原始交通信息视图
    case EMSG_CREATE_TFCRAWVIEW:
        {
            ASSERT(aImcMsg->m_wParam!=NULL);
            CWnd* pParentWnd = (CWnd*)aImcMsg->m_wParam;
            ASSERT(pParentWnd->IsKindOf(RUNTIME_CLASS(CWnd)));

            BOOL bFlag = m_wndTfcView.Create(pParentWnd);

            if (!bFlag)
            {
                IMsgAppLogs aLog;
                aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
                aLog.strComments.Format(_T("原始交通信息显示引擎初始化失败！"));
                NbsSendModuleMsg(&aLog);
            }
        }
        break;

        // 创建解析后的交通信息视图
    case EMSG_CREATE_TFCPARASEVIEW:
        {
            ASSERT(aImcMsg->m_wParam!=NULL);

            CWnd* pParentWnd = (CWnd*)aImcMsg->m_wParam;
            ASSERT(pParentWnd->IsKindOf(RUNTIME_CLASS(CWnd)));

            BOOL bFlag = m_wndTfcParsed.Create(pParentWnd);

            if (!bFlag)
            {
                IMsgAppLogs aLog;
                aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
                aLog.strComments.Format(_T("解析后的交通信息显示引擎初始化失败！"));
                NbsSendModuleMsg(&aLog);
            }
        }
        break;

        // 查找指定道路的解析结果
    case EMSG_PARSE_LOOKUP:
        {
            CString* pStrRoadID = (CString*)(aImcMsg->m_wParam);

            CLinkList linkList;
            BOOL bFound = m_linkParser.LookUpLinks(*pStrRoadID,linkList);

            //
            if (bFound)                 
            {
                m_TfcParsedMgr.MoveLinkToMapCenter(*linkList.GetHead());
                m_TfcParsedMgr.ActiveLink(linkList);
                m_wndTfcParsed.ReDraw();
            }
        }
        break;

        // 开始解析交通道路
    case EMSG_PARSE_START:
        {
            IMsgAppLogs aLog;
            aLog.strComments.Format(_T("开始解析……"));
            NbsSendModuleMsg(&aLog);

            //
            m_linkParser.ParseRoads();            
            
        }
        break;

        // 解析完毕
    case EMSG_PARSE_FINISHED:
        {
            //
            IMsgAppLogs aLog;
            aLog.UpdateToCurrentTime();
            aLog.strComments.Format(_T("解析完毕！"));
            NbsSendModuleMsg(&aLog);
        }
        break;

        // 保存解析结果
    case EMSG_PARSE_STORAGE:
        {
            CString strFilePath = *((CString*)aImcMsg->m_wParam);
            m_linkParser.SaveToTextFile(strFilePath);
            m_linkParser.SaveToBinFile(strFilePath+_T(".rtl"));
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
    char cTemp[300];
    GetPrivateProfileString(CFG_APPNAME_DATABASE,"DataSource",0,cTemp,300,GetExePath()+CString(PATH_CONFIGURE_FILE));
    strSource = cTemp;
    GetPrivateProfileString(CFG_APPNAME_DATABASE,"UserID",0,cTemp,300,GetExePath()+CString(PATH_CONFIGURE_FILE));
    strUsername = cTemp;
    GetPrivateProfileString(CFG_APPNAME_DATABASE,"Password",0,cTemp,300,GetExePath()+CString(PATH_CONFIGURE_FILE));
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

    m_TfcInfMgr.Close();
    m_TfcParsedMgr.Close();

    m_linkParser.Close();


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