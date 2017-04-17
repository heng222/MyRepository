#include "stdafx.h"
#include <CommonFunc.h>
#include "DataModule.h"
#include "GlobalMacro.h"
#include "TableAttrib.h"
#include "InterfaceEx.h"
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////


// 北京气象预报文件的检测时间间隔
#ifdef _DEBUG
    #define             INTERVALTIME        (60*1000)  // 60秒
#else
    #define             INTERVALTIME        (120*1000) // 120秒
#endif


//////////////////////////////////////////////////////////////////////////

CDataModule::CDataModule(CImcDispatcher& aDispatcher):
    CNBaseModule(aDispatcher,ID_MODULE_DATABASE)
{
    InitializeCriticalSection(&m_CriticalSection);
    m_hExitEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
    m_pThread = NULL;

    // 
    m_wndRegionView.AttachEngine(&m_DistMgr);
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
    char cTemp[300];

    //**  设置小区气象数据检测路径 
    ::GetPrivateProfileString(CFG_APPNAME_WEATHER,CFG_ITEM_WEATHER_PATH,0,cTemp,300,GetExePath()+CString(PATH_CONFIGURE_FILE));
    m_PreWeatherInf.SetFilePath(CString(cTemp));

    //
    return TRUE;
}

BOOL CDataModule::OnStart()
{
    if (!CNBaseModule::OnStart())
    {
        return FALSE;
    }

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
    
    //**  读取北京小区编码对应文件
    if ( !m_AreaIDMgr.ReadFile(GetExePath()+PATH_AREAID) )
    {
        AfxMessageBox("没有找到区域编码的配置文件！",MB_ICONERROR);
        return FALSE;
    }

    //** 读取直辖市，省份，城市名称及ID
    aLog.logTime = COleDateTime::GetCurrentTime();
    aLog.strComments.Format(_T("读取全国省份信息……"));
    SendModuleMsg(aLog);
    if (!m_CityMgr.ReadInf())
    {
        aLog.logTime = COleDateTime::GetCurrentTime();
        aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
        aLog.strComments.Format(_T("读取全国省份信息失败！"));
        SendModuleMsg(aLog);
        return FALSE;
    }

    //** 读取区域信息
    aLog.logTime = COleDateTime::GetCurrentTime();
    aLog.iLogLevel = IMsgAppLogs::ELL_INFORMATION;
    aLog.strComments.Format(_T("读取北京市各行政区的区域信息……"));
    SendModuleMsg(aLog);

    if (!m_DistMgr.ReadRgnData())
    {
        aLog.logTime = COleDateTime::GetCurrentTime();
        aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
        aLog.strComments.Format(_T("北京市区域信息读取失败！"));
        SendModuleMsg(aLog);

        return FALSE;
    }
    

    return TRUE;
}

BOOL CDataModule::OnActive()
{
    if ( !CNBaseModule::OnActive() )
    {
        return FALSE;
    }

    // 
    IMsgAppLogs aLog;


    //** 从数据库中读取所有市区的气象信息
    aLog.logTime = COleDateTime::GetCurrentTime();
    aLog.strComments.Format(_T("获取北京市区气象信息"));
    NbsSendModuleMsg(&aLog);
    BOOL bFlag = m_DistMgr.RetrieveWthInf();
    if (!bFlag)
    {
        aLog.logTime = COleDateTime::GetCurrentTime();
        aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
        aLog.strComments.Format(_T("获取气象信息失败！"));
        SendModuleMsg(aLog);
    }

    // 启动小区气象检测线程
    m_pThread = AfxBeginThread(_ThreadEntry,this);

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

        // 
    case EWEBS_NEW_WEATHERINF:
        {
            PIMsgCityWthInf pMsg = (PIMsgCityWthInf)aImcMsg;
            StoreCityWthInf(pMsg);
        }
    	break;


        // 创建气象信息提示视图
    case EMSG_CREATE_RGNVIEW:
        {
            CWnd *pWnd = (CWnd*)(aImcMsg->m_wParam);
            BOOL bFlag = m_wndRegionView.Create(pWnd);

            if (!bFlag)
            {
                IMsgAppLogs aLog;
                aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
                aLog.strComments.Format(_T("气象信息显示引擎初始化失败！"));
                NbsSendModuleMsg(&aLog);
            }
        }
        break;

        // 刷新北京市所有小区的气象信息
    case EMSG_RETRIVE_DISTWTHINF:
        {
            PIMsgRetriveWthInf pWthInf = (PIMsgRetriveWthInf)aImcMsg;
            pWthInf->bSuccess = GetDistWthAllPeriod(pWthInf->strDistrictID,pWthInf->m_wthInf);
        }
        break;

        // 获取指定城市的气象信息
    case EMSG_RETRIVE_CITYWTHINF:
        {
            PIMsgRetriveCityWthInf pMsg = (PIMsgRetriveCityWthInf)aImcMsg;
            GetCityWthInfByName(pMsg->strCityName,pMsg->strWthInf);
        }
        break;


        // 获取全国省份、直辖市及各城市的属性信息
    case EMSG_RETRIVE_CITYS:
        {
            PIMsgRetrieveCityInf pCity = PIMsgRetrieveCityInf(aImcMsg);
            m_CityMgr.GetCityInf(pCity->m_cityInf);
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
    // First: terminate the thread.
    SetEvent(m_hExitEvent);
    if (m_pThread!=NULL)
    {
        WaitForSingleObject(m_pThread->m_hThread,1000);
        m_pThread = NULL;
    }
    CloseHandle(m_hExitEvent);
    
    // Then ....
    m_OracleDB.Close();
    m_AreaIDMgr.ClearInf();	
    m_PreWeatherInf.ClearList();
    m_DistMgr.Close();
    m_CityMgr.ClearList();
    
    //
    CNBaseModule::OnClose();
}

//////////////////////////////////////////////////////////////////////////
// New Functions
void CDataModule::GetDBCnntPara(CString& strSource,CString& strUsername,CString& strPwd) const
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


// 更新北京气象预报信息
int CDataModule::UpdateBjWthInf(void)
{
    //检测文件是否更改
    if (m_PreWeatherInf.IsFileChange() == FALSE)
    {
        return -1;
    }
    else
    {
        IMsgAppLogs aLog;
        aLog.logTime = COleDateTime::GetCurrentTime();
        aLog.strComments.Format(_T("检测到新的小区气象信息！"));
        NbsSendModuleMsg(&aLog);
    }

    //读取气象预报数据
    if (!m_PreWeatherInf.ReadFile())
    {
        IMsgAppLogs aLog;
        aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
        aLog.strComments.Format(_T("读取小区气象数据文件%s失败！"),m_PreWeatherInf.GetPath());
        NbsSendModuleMsg(&aLog);

        return -1;
    }
    else
    {
        IMsgAppLogs aLog;        
        aLog.strComments.Format(_T("读取小区气象成功！"));
        NbsSendModuleMsg(&aLog);
    }

    //
    if (!m_OracleDB.IsOpen())
    {
        IMsgAppLogs aLog;
        aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
        aLog.strComments.Format(_T("更新小区气象失败！（没有连接到数据库）"));
        NbsSendModuleMsg(&aLog);

        return -1;
    }

    //将气象数据保存到数据库
    POSITION pos = m_PreWeatherInf.GetHeadPosition();
    while (pos)
    {
        PTWeatherInf pWthInf = (PTWeatherInf)m_PreWeatherInf.GetNext(pos);
        //
        CString strSQL;
        CStringList areaGBKList;

        // 转换成国标码
        m_AreaIDMgr.TransferID(pWthInf->strDistID,FALSE,areaGBKList);
        POSITION pp = areaGBKList.GetHeadPosition();
        while (pp)
        {
            CString strAreaGBK = areaGBKList.GetNext(pp);
            CString strAreaName;
            m_AreaIDMgr.GetAreaName(strAreaGBK,strAreaName);
            //删除旧的数据...... 
            //strSQL.Format(_T("DELETE FROM %s WHERE AREA_ID='%s' AND PERIOD='%c'"),
            //T_WTHTABLE_NAME,pWthInf->cAreaID,pWthInf->cFlag);
            strSQL.Format(_T("DELETE FROM %s WHERE AREA_ID='%s' AND PERIOD='%c'"),
                T_WTHTABLE_NAME,strAreaGBK,char(pWthInf->cPeriodFlag));
            m_OracleDB.Execute(strSQL);
            //保存新的数据 
            strSQL.Format(_T("INSERT INTO %s(PUB_DATE,PERIOD,AREA_ID,WEATHER,\
                          TEMPERATURE_MIN,TEMPERATURE_MAX,\
                          WIND_DIRECTION,WIND_POWER_MIN,WIND_POWER_MAX,HUMIDITY,AREA_NAME)\
                          VALUES(to_Date('%s','yyyy-mm-dd HH24:mi:ss'),'%c','%s',\
                          '%s',%.1f,%.1f,'%s',%d,%d,%d,'%s')"),
						  T_WTHTABLE_NAME,
                          pWthInf->publishTime.Format("%Y-%m-%d %H:%M:%S"),
                          char(pWthInf->cPeriodFlag),
                          /*pWthInf->cAreaID,*/
                          strAreaGBK,
                          pWthInf->strWeatherDes,
                          pWthInf->fTempMin,
                          pWthInf->fTempMax,
                          pWthInf->strWindDirec,
                          pWthInf->byWindPowerMin,pWthInf->byWindPowerMax,
                          pWthInf->byHumidity,
                          strAreaName);
            m_OracleDB.Execute(strSQL);
        }        
    }

    //
    IMsgAppLogs aLog;
    aLog.iLogLevel = m_PreWeatherInf.GetCount()>0 ? IMsgAppLogs::ELL_INFORMATION : IMsgAppLogs::ELL_ERROR;
    aLog.strComments.Format(_T("更新%d条小区气象数据!"),m_PreWeatherInf.GetCount());
    NbsSendModuleMsg(&aLog);

    //
    return (int)m_PreWeatherInf.GetCount();
}

// 
BOOL CDataModule::StoreCityWthInf(PIMsgCityWthInf pNewWthInf)
{
    if (!m_OracleDB.IsOpen())
    {
        return FALSE;
    }

    try
    {
        CString strSQL;


        // 1. Delete old data.
        strSQL.Format(_T("DELETE FROM %s WHERE CITY_CODE='%s'"),T_WTH_MAINCITYS,pNewWthInf->strCityCode);
        m_OracleDB.Execute(strSQL);


        // 2. Insert the new data.
        strSQL.Format(_T("INSERT INTO %s(CITY_CODE,UPDATE_STAMP,CITY_NAME,PROVINCE,\
                         TODAY_TEMP_MIN,TODAY_TEMP_MAX,\
                         TODAY_WEATHER_DES,TODAY_WINDDIRECTION,TODAY_WINDPOWER_MIN,\
                         TODAY_WINDPOWER_MAX,TODAY_HUMIDITY,CUR_WEATHER_DES,LIFE_INDEX)\
                         VALUES('%s',to_Date('%s','yyyy-mm-dd HH24:mi:ss'),'%s','%s',\
                         %.1f,%.1f,'%s','%s',%d,%d,%d,'%s','%s')"),

                         T_WTH_MAINCITYS,
                         pNewWthInf->strCityCode,    // 城市代码
                         pNewWthInf->publishTime.Format("%Y-%m-%d %H:%M:%S"),// 更新日期
                         pNewWthInf->strCityName,    // 城市名称
                         pNewWthInf->strProvince,    // 城市所在省份
                         pNewWthInf->fTodMinTemper,  // 当天的最低气温
                         pNewWthInf->fTodMaxTemper,  // 当天的最高气温
                         pNewWthInf->strTodWthDes,   // 当天的天气概况
                         pNewWthInf->strTodWindDir,  // 当天的风向
                         pNewWthInf->iTodMinWindPow, // 当天的最小风力
                         pNewWthInf->iTodMaxWindPow, // 当天的最大风力
                         pNewWthInf->iTodHumidity,   // 当天的空气湿度
                         pNewWthInf->strCurWthDes,   // 实况天气描述
                         pNewWthInf->strLifeIndex    // 生活指数
                         
        );
        //TRACE("\n\n%s\n",strSQL);
        m_OracleDB.Execute(strSQL);
    }
    catch (...)
    {
    	
    }

    return TRUE;
}

// 在市气象局编码与国标编码之间进行转换
void CDataModule::TransferAreaID(const CString& strAreaID, 
                              BOOL bDirection,CStringList& strList)
{
    return m_AreaIDMgr.TransferID(strAreaID,bDirection,strList);
}



UINT CDataModule::_ThreadEntry(LPVOID pParam)
{
    CoInitialize(NULL);
    CDataModule* pObject = (CDataModule*)pParam;

    while (TRUE)
    {

        int iNum = pObject->UpdateBjWthInf();

        // Wait ……
        if (WaitForSingleObject(pObject->m_hExitEvent,INTERVALTIME)==WAIT_OBJECT_0)
        {
            break;
        }

    }

    // 
    pObject->m_pThread = NULL;
    return 0L;
}




BOOL CDataModule::GetCityWthInfByName(const CString& strCityName, CString& strWthInf) const
{
    /*if (!m_OracleDB.IsOpen())
    {
    return FALSE;
    }*/

    // 取出指定时段的气温
    CString strSQL;
    strSQL.Format(_T("SELECT * FROM %s WHERE %s='%s'"),
        T_WTH_MAINCITYS,
        TI_WM_CITYNAME,strCityName);

    CAdoRecordSet records;
    records = m_OracleDB.Execute(strSQL);
    int count = records.GetRecordCount();
    records.MoveFirst();
    if (count>0)
    {
        // 天气实况
        records.GetCollect(TI_WM_CURWTH,strWthInf);
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}



BOOL CDataModule::GetDistWthAllPeriod(const CString& strDistID,CWthInfList& wthList) const
{
    /*if (!m_OracleDB.IsOpen())
    {
    return FALSE;
    }*/

    // 取出指定时段的气温
    CString strSQL;
    strSQL.Format(_T("SELECT * FROM %s WHERE %s='%s'"),
        T_WTHTABLE_NAME,
        TI_WT_AREAID,strDistID);

    CAdoRecordSet records;
    records = m_OracleDB.Execute(strSQL);
    int iCount = records.GetRecordCount();

    if (iCount<=0)
    {
        return FALSE;
    }


    records.MoveFirst();
    for (int ii=0; ii<iCount; ii++)
    {
        TWeatherInf* pWthInf = new TWeatherInf;
        pWthInf->strDistID = strDistID;

        try
        {
            CString strTemp;
            records.GetCollect(TI_WT_PUBDATE,pWthInf->publishTime); // 发布时间
            records.GetCollect(TI_WT_PERIOD,strTemp); // 时段
            pWthInf->cPeriodFlag = (TWeatherInf::TPeriodCode)(strTemp.GetBuffer(0)[0]);
            records.GetCollect(TI_WT_AREANAME,pWthInf->strDistName);// 区域名称
            records.GetCollect(TI_WT_WEATHER,pWthInf->strWeatherDes);// 天气状况
            records.GetCollect(TI_WT_MAXTEMP,pWthInf->fTempMax);// 最高气温
            records.GetCollect(TI_WT_MINTEMP,pWthInf->fTempMin);// 最低气温
            records.GetCollect(TI_WT_MAXWINDPOWER,pWthInf->byWindPowerMax);// 最高风力
            records.GetCollect(TI_WT_MINWINDPOWER,pWthInf->byWindPowerMin);// 最低风力
            records.GetCollect(TI_WT_WIDDIRECTION,pWthInf->strWindDirec); // 风向
            records.GetCollect(TI_WT_HUMIDITY,pWthInf->byHumidity);       // 相对湿度

            wthList.AddTail(pWthInf);
        }
        catch (CException* e)
        {
            e->ReportError();
            e->Delete();
            delete pWthInf;
        }

        records.MoveNext();
    }

    return TRUE;
}

BOOL CDataModule::IsDBConnected() const
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