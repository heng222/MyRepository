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
    aLog.strComments.Format(_T("��ʼ����ͨ���������ݴ���ģ�顭��"));
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


    //** ��ȡ��·IDӳ����Ϣ
    aLog.logTime = COleDateTime::GetCurrentTime();
    aLog.iLogLevel = IMsgAppLogs::ELL_INFORMATION;
    aLog.strComments.Format(_T("��ȡ��·IDӳ����Ϣ����"));
    SendModuleMsg(aLog);
    if (!m_roadIDMgr.ReadMapFile())
    {
        return FALSE;
    }


    //** ��ȡ������Ϣ
    aLog.logTime = COleDateTime::GetCurrentTime();
    aLog.iLogLevel = IMsgAppLogs::ELL_INFORMATION;
    aLog.strComments.Format(_T("��ȡ�����и���������������Ϣ����"));
    SendModuleMsg(aLog);

    if (!m_DistMgr.ReadRgnData())
    {
        aLog.logTime = COleDateTime::GetCurrentTime();
        aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
        aLog.strComments.Format(_T("������������Ϣ��ȡʧ�ܣ�"));
        SendModuleMsg(aLog);

        return FALSE;
    }



    //** ��ȡֱϽ�У�ʡ�ݣ��������Ƽ�ID
    aLog.logTime = COleDateTime::GetCurrentTime();
    aLog.strComments.Format(_T("��ȡȫ��ʡ����Ϣ����"));
    SendModuleMsg(aLog);
    if (!m_CityMgr.ReadInf())
    {
        aLog.logTime = COleDateTime::GetCurrentTime();
        aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
        aLog.strComments.Format(_T("��ȡȫ��ʡ����Ϣʧ�ܣ�"));
        SendModuleMsg(aLog);
        return FALSE;
    }

    //* ���mapcity.can�ļ�
    aLog.logTime = COleDateTime::GetCurrentTime();
    aLog.strComments.Format(_T("��ȡ�����������ݡ���"));
    if ( !m_cityRgnMgr.Open() )
    {
        aLog.strComments += _T("\tʧ�ܣ�");
        return FALSE;
    }
    else
    {
        aLog.strComments += _T("\t�ɹ���");
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
    IMsgAppLogs aLog;
    aLog.strComments.Format(_T("�����ͷ����ݡ���"));
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
    // ���ݿ�����״̬�ظ�
    IMsgDBCntTest msg;
    msg.SetType(IMsgDBCntTest::E_RESPONSE);
    msg.bResult = FALSE;
    NbsSendModuleMsg(&msg);

    //
    IMsgAppLogs aLog;
    aLog.EnableStorage(FALSE);
    aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
    aLog.strComments.Format(_T("��⵽���ݿ�����쳣���������½������ӡ���"));
    SendModuleMsg(aLog);

    BOOL bFlag = ConnectToDB();

    // �����ɹ���
    if (bFlag && IsDBConnected())
    {
        IMsgDBCntTest msg;
        msg.SetType(IMsgDBCntTest::E_RESPONSE);
        msg.bResult = TRUE;
        NbsSendModuleMsg(&msg);

        IMsgAppLogs aLog;
        aLog.EnableStorage(FALSE);
        aLog.strComments.Format(_T("�������ӳɹ���"));
        SendModuleMsg(aLog);
    }
    else
    {
        IMsgAppLogs aLog;
        aLog.EnableStorage(FALSE);
        aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
        aLog.strComments.Format(_T("��������ʧ�ܣ�"));
        SendModuleMsg(aLog);
    }
}
//////////////////////////////////////////////////////////////////////////
// New Functions
void CDataModule::GetDBCnntPara(CString& strSource,CString& strUsername,CString& strPwd) const
{
    //�������ļ��ж�ȡ���ݿ����
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

BOOL CDataModule::IsDBConnected() const
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
BOOL CDataModule::GetDistrictWeather(const char& cFlag,const CString& strAreaID,TWeatherInf& weatherInf) const
{
   /* if (!m_OracleDB.IsOpen())
    {
        return FALSE;
    }*/


    // ȡ��ָ��ʱ�ε�����
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
        records.GetCollect(TI_WT_PUBDATE,weatherInf.publishTime); // ����ʱ��
        // ��������
        records.GetCollect(TI_WT_AREANAME,weatherInf.strDistName);
        // ����״��
        records.GetCollect(TI_WT_WEATHER,weatherInf.strWeatherDes);
        // ����������������
        records.GetCollect(TI_WT_MAXTEMP,weatherInf.fTempMax);
        records.GetCollect(TI_WT_MINTEMP,weatherInf.fTempMin);
        // ��߷�������ͷ���
        records.GetCollect(TI_WT_MAXWINDPOWER,weatherInf.byWindPowerMax);
        records.GetCollect(TI_WT_MINWINDPOWER,weatherInf.byWindPowerMin);
        // ����
        records.GetCollect(TI_WT_WIDDIRECTION,weatherInf.strWindDirec);
        // ���ʪ��
        records.GetCollect(TI_WT_HUMIDITY,weatherInf.byHumidity);
    }
    else
    {
        return FALSE;
    }

    // ���ָ����ʱ��Ϊ���죬��ȡ�����ϵ�������Ϣ��ֻ�õ�������£�
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

// ���������ѯ������Ϣ
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


    // ȡ��ָ��ʱ�ε�����
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
        // ����ʵ��
        records.GetCollect(TI_WM_CURWTH,strWthInf);
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}


// ���ݾ�γ�ȵõ��������
BOOL CDataModule::GetRegionIDByPosition(const TMPoint& ptPos,CString& strAreaID) const
{
    return m_DistMgr.GetDistIDByPos(ptPos,strAreaID);
}

/*
// ����Link����ֹ�������Ʒ�����Ӧ�ĵ�һLink���������� ��������һLink����
*/
void CDataModule::GetSpecifiedLinkTfcInf(TLinkAttri& link)
{
    // ��Ĭ��ֵ
    link.m_iJamLevel = 0;
    link.m_iJamReason = 0;


    // ����Link������ҵ���Link��ID
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


    // �����ݿ���ȡ��Link�Ľ�ͨ����Ϣ
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
// ���ݵ�·���Ƶõ���Ӧ��Link��������ͨ����·��������
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

    // �õ���·��Ӧ��Links
    strSQL.Format(_T("SELECT DISTINCT %s FROM %s WHERE %s LIKE '%%%s%%'"),
        TI_TP_ROADID,T_TRFFICINF_NAME,TI_TP_LINKNAME,
        strRoadName);
    roadIDRecords = m_OracleDB.Execute(strSQL);

    // �����ݿ���ȡ����ӦLink�Ľ�ͨ��Ϣ
    int iCount = roadIDRecords.GetRecordCount();
    TRACE("%s��Ӧ�ļ��·�θ���%d\n",strRoadName,iCount);

    if (iCount<=0)
    {
        return;
    }   


    roadIDRecords.MoveFirst();

    for (int ii=0; ii<iCount; ii++,roadIDRecords.MoveNext())
    {   
        // ȡ����ͨ���·�ε�ID
        DWORD dwRoadID;
        roadIDRecords.GetCollect(TI_TP_ROADID,dwRoadID);

        // ��ѯ��·�εĽ�ͨ״��
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


        // ����·����Ϣ
        PTRawRoadTfcInf pTfcRoad = new TRawRoadTfcInf;
        pTfcRoad->dwRoadID = dwRoadID;
        recdTfc.GetCollect(TI_RT_SPEED,pTfcRoad->fSpeed);
        recdTfc.GetCollect(TI_RT_JAMREASON,pTfcRoad->iJamReason); 
        roadTfcList.AddTail(pTfcRoad);

    }


}



