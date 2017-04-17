#include "stdafx.h"
#include "datamodule.h"
#include "GlobalMacro.h"
#include "TableAttrib.h"
#include "DataModulInterface.h"

//////////////////////////////////////////////////////////////////////////

#define         _TFC_REQUEST_VIA_NAME_V2

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
    m_OracleDB.SetObserver(this);

    //
    IMsgAppLogs aLog;
    aLog.strComments.Format(_T("初始化交通与气象数据处理模块……"));
    SendModuleMsg(aLog);


    //
    return TRUE;
}
BOOL CDataModule::OnStart()
{
    if (!CNBaseModule::OnStart())
    {
        return FALSE;
    }
    // 
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


    //** 读取道路ID映射信息
    aLog.logTime = COleDateTime::GetCurrentTime();
    aLog.iLogLevel = IMsgAppLogs::ELL_INFORMATION;
    aLog.strComments.Format(_T("读取道路ID映射信息……"));
    SendModuleMsg(aLog);
    if (!m_roadIDMgr.ReadMapFile())
    {
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

    //* 检测mapcity.can文件
    aLog.logTime = COleDateTime::GetCurrentTime();
    aLog.strComments.Format(_T("读取城市区域数据……"));
    if ( !m_cityRgnMgr.Open() )
    {
        aLog.strComments += _T("\t失败！");
        return FALSE;
    }
    else
    {
        aLog.strComments += _T("\t成功！");
    }
    NbsSendModuleMsg(&aLog);
    

    return TRUE;
}

BOOL CDataModule::OnActive()
{
    if (!CNBaseModule::OnActive())
    {
        return FALSE;
    }
    
    //
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
    IMsgAppLogs aLog;
    aLog.strComments.Format(_T("正在释放数据……"));
    NbsSendModuleMsg(&aLog);

    // 
    m_OracleDB.Close();
    m_DistMgr.Close();
    m_TfcInfMgr.Close();
    m_CityMgr.ClearList();
    m_roadIDMgr.Clear();

    //
    CNBaseModule::OnClose();
}

void CDataModule::OnExecuteFailure()
{
    // 数据库连接状态回复
    IMsgDBCntTest msg;
    msg.SetType(IMsgDBCntTest::E_RESPONSE);
    msg.bResult = FALSE;
    NbsSendModuleMsg(&msg);

    //
    IMsgAppLogs aLog;
    aLog.EnableStorage(FALSE);
    aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
    aLog.strComments.Format(_T("检测到数据库出现异常！正在重新建立连接……"));
    SendModuleMsg(aLog);

    BOOL bFlag = ConnectToDB();

    // 重连成功？
    if (bFlag && IsDBConnected())
    {
        IMsgDBCntTest msg;
        msg.SetType(IMsgDBCntTest::E_RESPONSE);
        msg.bResult = TRUE;
        NbsSendModuleMsg(&msg);

        IMsgAppLogs aLog;
        aLog.EnableStorage(FALSE);
        aLog.strComments.Format(_T("重新连接成功。"));
        SendModuleMsg(aLog);
    }
    else
    {
        IMsgAppLogs aLog;
        aLog.EnableStorage(FALSE);
        aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
        aLog.strComments.Format(_T("重新连接失败！"));
        SendModuleMsg(aLog);
    }
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


PTCityStruton CDataModule::GetCityByPos(DWORD dwLongi,DWORD dwLati) const
{
    WORD wCityIndex = m_cityRgnMgr.GetDistIdxByPos(dwLongi,dwLati);
    if (wCityIndex==CDistrictRgnMgr::EINVALID_DISTID)
    {
        return NULL;
    }
    else
    {
        PTCityStruton pCity = m_CityMgr.GetCityByIndex(wCityIndex);
        return pCity;
    }
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
BOOL CDataModule::GetDistrictWeather(const char& cFlag,const CString& strAreaID,TWeatherInf& weatherInf) const
{
   /* if (!m_OracleDB.IsOpen())
    {
        return FALSE;
    }*/


    // 取出指定时段的气温
    CString strSQL;
    strSQL.Format(_T("SELECT * FROM %s WHERE %s='%c' AND %s='%s'"),
        T_WTHTABLE_NAME,
        TI_WT_PERIOD,cFlag,
        TI_WT_AREAID,strAreaID);


    CAdoRecordSet records;
    records = m_OracleDB.Execute(strSQL);
    int count = records.GetRecordCount();
    records.MoveFirst();
    if (count>0)
    {
        CString strTemp;
        records.GetCollect(TI_WT_PUBDATE,weatherInf.publishTime); // 发布时间
        // 区域名称
        records.GetCollect(TI_WT_AREANAME,weatherInf.strDistName);
        // 天气状况
        records.GetCollect(TI_WT_WEATHER,weatherInf.strWeatherDes);
        // 最高气温与最低气温
        records.GetCollect(TI_WT_MAXTEMP,weatherInf.fTempMax);
        records.GetCollect(TI_WT_MINTEMP,weatherInf.fTempMin);
        // 最高风力与最低风力
        records.GetCollect(TI_WT_MAXWINDPOWER,weatherInf.byWindPowerMax);
        records.GetCollect(TI_WT_MINWINDPOWER,weatherInf.byWindPowerMin);
        // 风向
        records.GetCollect(TI_WT_WIDDIRECTION,weatherInf.strWindDirec);
        // 相对湿度
        records.GetCollect(TI_WT_HUMIDITY,weatherInf.byHumidity);
    }
    else
    {
        return FALSE;
    }

    // 如果指定的时段为白天，则取出晚上的天气信息（只用到最低气温）
    strSQL.Format(_T("SELECT * FROM %s WHERE %s='%c' AND %s='%s'"),
        T_WTHTABLE_NAME,
        TI_WT_PERIOD,char(TWeatherInf::EPer_Tonight),
        TI_WT_AREAID,strAreaID);
    records = m_OracleDB.Execute(strSQL);
    count = records.GetRecordCount();
    records.MoveFirst();
    if (count>0)
    {
        records.GetCollect(TI_WT_MINTEMP,weatherInf.fTempMin);
    }

    return TRUE;
}

// 根据坐标查询气象信息
BOOL CDataModule::GetCityWthInfByPos(const TMPoint& poiPos,CString& strCityName,CString& strWthInf) const
{
    //
    PTCityStruton pCity = GetCityByPos(DWORD(poiPos.iX),DWORD(poiPos.iY));
    if (pCity==NULL)
    {
        return FALSE;
    }
    else
    {
        strCityName = pCity->m_strCityName;
    }

    //
    /*if (!m_OracleDB.IsOpen())
    {
        return FALSE;
    }*/


    // 取出指定时段的气温
    CString strCityID = pCity->m_strCityID;
    CString strSQL;
    strSQL.Format(_T("SELECT %s FROM %s WHERE %s='%s'"),
        TI_WM_CURWTH,
        T_WTH_MAINCITYS,
        TI_WM_CITYCODE,strCityID);

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


// 根据经纬度得到区域编码
BOOL CDataModule::GetRegionIDByPosition(const TMPoint& ptPos,CString& strAreaID) const
{
    return m_DistMgr.GetDistIDByPos(ptPos,strAreaID);
}

/*
// 根据Link的起止点与名称返回相应的单一Link的所有属性 （解析单一Link请求）
*/
void CDataModule::GetSpecifiedLinkTfcInf(TLinkAttri& link)
{
    // 置默认值
    link.m_iJamLevel = 0;
    link.m_iJamReason = 0;


    // 根据Link的起点找到此Link的ID
    CLinkList linkList;
    BOOL bFlag= m_TfcInfMgr.GetLinkByPoint(link.m_StartPos,linkList);

    if (!bFlag)
    {
        return;
    }

    // 
    POSITION pos = linkList.GetHeadPosition();
    link.m_strLinkID = linkList.GetNext(pos)->m_strLinkID;


    if (!m_OracleDB.IsOpen())
    {
        return;
    }


    // 从数据库中取出Link的交通流信息
    CString strSQL;
    strSQL.Format(_T("SELECT * FROM %s WHERE %s='%s'"),
        T_TRFFICINF_NAME,
        TI_TP_LINKID,link.m_strLinkID);

    CAdoRecordSet records;
    records = m_OracleDB.Execute(strSQL);
    int count = records.GetRecordCount();
    records.MoveFirst();

    if (count>0)
    {
        records.GetCollect(TI_TP_SPEED,link.m_iSpeed);
        records.GetCollect(TI_TP_JAMLEVEL,link.m_iJamLevel);
        records.GetCollect(TI_TP_JAMREASON,link.m_iJamReason);
    }
}


/*
// 根据道路名称得到相应的Link链表（解析通过道路名称请求）
*/ 
void CDataModule::GetRoadTfcInfByRoadName(CRoadTfcInfList& roadTfcList,
                                          const CString& strRoadName,TMPoint roadPos)
{
    if ( strRoadName.IsEmpty() )
    {
        return;
    }

    CString strSQL;
    CAdoRecordSet roadIDRecords;

    // 得到道路相应的Links
    strSQL.Format(_T("SELECT DISTINCT %s FROM %s WHERE %s LIKE '%%%s%%'"),
        TI_TP_ROADID,T_TRFFICINF_NAME,TI_TP_LINKNAME,
        strRoadName);
    roadIDRecords = m_OracleDB.Execute(strSQL);

    // 从数据库中取出相应Link的交通信息
    int iCount = roadIDRecords.GetRecordCount();
    TRACE("%s对应的检测路段个数%d\n",strRoadName,iCount);

    if (iCount<=0)
    {
        return;
    }   


    roadIDRecords.MoveFirst();

    for (int ii=0; ii<iCount; ii++,roadIDRecords.MoveNext())
    {   
        // 取出交通检测路段的ID
        DWORD dwRoadID;
        roadIDRecords.GetCollect(TI_TP_ROADID,dwRoadID);

        // 查询此路段的交通状况
        strSQL.Format(_T("SELECT %s,%s FROM %s WHERE %s=%d"),
            TI_RT_SPEED,TI_RT_JAMREASON,T_RAW_TRAFFICNAME,
            TI_RT_ROADID_NEW,dwRoadID);

        CAdoRecordSet recdTfc;
        recdTfc = m_OracleDB.Execute(strSQL);

        int nNum = recdTfc.GetRecordCount();
        if (nNum<=0)
        {
            continue;
        }
        recdTfc.MoveFirst();


        // 构造路况信息
        PTRawRoadTfcInf pTfcRoad = new TRawRoadTfcInf;
        pTfcRoad->dwRoadID = dwRoadID;
        recdTfc.GetCollect(TI_RT_SPEED,pTfcRoad->fSpeed);
        recdTfc.GetCollect(TI_RT_JAMREASON,pTfcRoad->iJamReason); 
        roadTfcList.AddTail(pTfcRoad);

    }


}



