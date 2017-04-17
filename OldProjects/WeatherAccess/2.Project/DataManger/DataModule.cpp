#include "stdafx.h"
#include <CommonFunc.h>
#include "DataModule.h"
#include "GlobalMacro.h"
#include "TableAttrib.h"
#include "InterfaceEx.h"
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////


// ��������Ԥ���ļ��ļ��ʱ����
#ifdef _DEBUG
    #define             INTERVALTIME        (60*1000)  // 60��
#else
    #define             INTERVALTIME        (120*1000) // 120��
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

    //**  ����С���������ݼ��·�� 
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
    
    //**  ��ȡ����С�������Ӧ�ļ�
    if ( !m_AreaIDMgr.ReadFile(GetExePath()+PATH_AREAID) )
    {
        AfxMessageBox("û���ҵ��������������ļ���",MB_ICONERROR);
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


    //** �����ݿ��ж�ȡ����������������Ϣ
    aLog.logTime = COleDateTime::GetCurrentTime();
    aLog.strComments.Format(_T("��ȡ��������������Ϣ"));
    NbsSendModuleMsg(&aLog);
    BOOL bFlag = m_DistMgr.RetrieveWthInf();
    if (!bFlag)
    {
        aLog.logTime = COleDateTime::GetCurrentTime();
        aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
        aLog.strComments.Format(_T("��ȡ������Ϣʧ�ܣ�"));
        SendModuleMsg(aLog);
    }

    // ����С���������߳�
    m_pThread = AfxBeginThread(_ThreadEntry,this);

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

        // 
    case EWEBS_NEW_WEATHERINF:
        {
            PIMsgCityWthInf pMsg = (PIMsgCityWthInf)aImcMsg;
            StoreCityWthInf(pMsg);
        }
    	break;


        // ����������Ϣ��ʾ��ͼ
    case EMSG_CREATE_RGNVIEW:
        {
            CWnd *pWnd = (CWnd*)(aImcMsg->m_wParam);
            BOOL bFlag = m_wndRegionView.Create(pWnd);

            if (!bFlag)
            {
                IMsgAppLogs aLog;
                aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
                aLog.strComments.Format(_T("������Ϣ��ʾ�����ʼ��ʧ�ܣ�"));
                NbsSendModuleMsg(&aLog);
            }
        }
        break;

        // ˢ�±���������С����������Ϣ
    case EMSG_RETRIVE_DISTWTHINF:
        {
            PIMsgRetriveWthInf pWthInf = (PIMsgRetriveWthInf)aImcMsg;
            pWthInf->bSuccess = GetDistWthAllPeriod(pWthInf->strDistrictID,pWthInf->m_wthInf);
        }
        break;

        // ��ȡָ�����е�������Ϣ
    case EMSG_RETRIVE_CITYWTHINF:
        {
            PIMsgRetriveCityWthInf pMsg = (PIMsgRetriveCityWthInf)aImcMsg;
            GetCityWthInfByName(pMsg->strCityName,pMsg->strWthInf);
        }
        break;


        // ��ȡȫ��ʡ�ݡ�ֱϽ�м������е�������Ϣ
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
    //�������ļ��ж�ȡ���ݿ����
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


// ���±�������Ԥ����Ϣ
int CDataModule::UpdateBjWthInf(void)
{
    //����ļ��Ƿ����
    if (m_PreWeatherInf.IsFileChange() == FALSE)
    {
        return -1;
    }
    else
    {
        IMsgAppLogs aLog;
        aLog.logTime = COleDateTime::GetCurrentTime();
        aLog.strComments.Format(_T("��⵽�µ�С��������Ϣ��"));
        NbsSendModuleMsg(&aLog);
    }

    //��ȡ����Ԥ������
    if (!m_PreWeatherInf.ReadFile())
    {
        IMsgAppLogs aLog;
        aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
        aLog.strComments.Format(_T("��ȡС�����������ļ�%sʧ�ܣ�"),m_PreWeatherInf.GetPath());
        NbsSendModuleMsg(&aLog);

        return -1;
    }
    else
    {
        IMsgAppLogs aLog;        
        aLog.strComments.Format(_T("��ȡС������ɹ���"));
        NbsSendModuleMsg(&aLog);
    }

    //
    if (!m_OracleDB.IsOpen())
    {
        IMsgAppLogs aLog;
        aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
        aLog.strComments.Format(_T("����С������ʧ�ܣ���û�����ӵ����ݿ⣩"));
        NbsSendModuleMsg(&aLog);

        return -1;
    }

    //���������ݱ��浽���ݿ�
    POSITION pos = m_PreWeatherInf.GetHeadPosition();
    while (pos)
    {
        PTWeatherInf pWthInf = (PTWeatherInf)m_PreWeatherInf.GetNext(pos);
        //
        CString strSQL;
        CStringList areaGBKList;

        // ת���ɹ�����
        m_AreaIDMgr.TransferID(pWthInf->strDistID,FALSE,areaGBKList);
        POSITION pp = areaGBKList.GetHeadPosition();
        while (pp)
        {
            CString strAreaGBK = areaGBKList.GetNext(pp);
            CString strAreaName;
            m_AreaIDMgr.GetAreaName(strAreaGBK,strAreaName);
            //ɾ���ɵ�����...... 
            //strSQL.Format(_T("DELETE FROM %s WHERE AREA_ID='%s' AND PERIOD='%c'"),
            //T_WTHTABLE_NAME,pWthInf->cAreaID,pWthInf->cFlag);
            strSQL.Format(_T("DELETE FROM %s WHERE AREA_ID='%s' AND PERIOD='%c'"),
                T_WTHTABLE_NAME,strAreaGBK,char(pWthInf->cPeriodFlag));
            m_OracleDB.Execute(strSQL);
            //�����µ����� 
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
    aLog.strComments.Format(_T("����%d��С����������!"),m_PreWeatherInf.GetCount());
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
                         pNewWthInf->strCityCode,    // ���д���
                         pNewWthInf->publishTime.Format("%Y-%m-%d %H:%M:%S"),// ��������
                         pNewWthInf->strCityName,    // ��������
                         pNewWthInf->strProvince,    // ��������ʡ��
                         pNewWthInf->fTodMinTemper,  // ������������
                         pNewWthInf->fTodMaxTemper,  // ������������
                         pNewWthInf->strTodWthDes,   // ����������ſ�
                         pNewWthInf->strTodWindDir,  // ����ķ���
                         pNewWthInf->iTodMinWindPow, // �������С����
                         pNewWthInf->iTodMaxWindPow, // �����������
                         pNewWthInf->iTodHumidity,   // ����Ŀ���ʪ��
                         pNewWthInf->strCurWthDes,   // ʵ����������
                         pNewWthInf->strLifeIndex    // ����ָ��
                         
        );
        //TRACE("\n\n%s\n",strSQL);
        m_OracleDB.Execute(strSQL);
    }
    catch (...)
    {
    	
    }

    return TRUE;
}

// ��������ֱ�����������֮�����ת��
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

        // Wait ����
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

    // ȡ��ָ��ʱ�ε�����
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
        // ����ʵ��
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

    // ȡ��ָ��ʱ�ε�����
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
            records.GetCollect(TI_WT_PUBDATE,pWthInf->publishTime); // ����ʱ��
            records.GetCollect(TI_WT_PERIOD,strTemp); // ʱ��
            pWthInf->cPeriodFlag = (TWeatherInf::TPeriodCode)(strTemp.GetBuffer(0)[0]);
            records.GetCollect(TI_WT_AREANAME,pWthInf->strDistName);// ��������
            records.GetCollect(TI_WT_WEATHER,pWthInf->strWeatherDes);// ����״��
            records.GetCollect(TI_WT_MAXTEMP,pWthInf->fTempMax);// �������
            records.GetCollect(TI_WT_MINTEMP,pWthInf->fTempMin);// �������
            records.GetCollect(TI_WT_MAXWINDPOWER,pWthInf->byWindPowerMax);// ��߷���
            records.GetCollect(TI_WT_MINWINDPOWER,pWthInf->byWindPowerMin);// ��ͷ���
            records.GetCollect(TI_WT_WIDDIRECTION,pWthInf->strWindDirec); // ����
            records.GetCollect(TI_WT_HUMIDITY,pWthInf->byHumidity);       // ���ʪ��

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