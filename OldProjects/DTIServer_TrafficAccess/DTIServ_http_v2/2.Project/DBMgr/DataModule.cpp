#include "stdafx.h"
#include "DataModule.h"
#include "TableAttrib.h"
#include "GlobalMacro.h"
#include <CommonFunc.h>
#include "InterfaceEx.h"

//////////////////////////////////////////////////////////////////////////

//#ifndef _DEBUG
    #define     _SAVE_TFCINF2DATABSE    // �Ƿ񽫽�ͨ��Ϣ�������
//#endif



//#define     _IMPORT_TFCEVENTDATA_TO_DATABASE        // �Ƿ��뽻ͨ�¼������ݿ���


//////////////////////////////////////////////////////////////////////////
// 

CDataModule::CDataModule(CImcDispatcher& aDis):
        CNBaseModule(aDis,ID_MODULE_DATABASE)
{
    
    //InitializeCriticalSection(&m_CriticalSection);


    m_wndTfcView.AttachEngine(&m_TfcInfMgr);
    m_wndTfcParsed.AttachEngine(&m_TfcParsedMgr);
}

CDataModule::~CDataModule(void)
{
    //DeleteCriticalSection(&m_CriticalSection);


}


BOOL CDataModule::OnInitModule()
{
    if (!CNBaseModule::OnInitModule())
    {
        return FALSE;
    }

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


    // ��ȡLink����
    aLog.iLogLevel = IMsgAppLogs::ELL_INFORMATION;
    aLog.UpdateToCurrentTime();
    aLog.strComments.Format(_T("��ȡ��ͨƥ�����ݡ���"));
    NbsSendModuleMsg(&aLog);
    if (!m_TfcParsedMgr.Open())
    {
        return FALSE;
    }



    // read the traffic events information.
    if (!m_TfcInfMgr.Open())
    {
        return FALSE;
    }

    // ��ȡ

    return TRUE;
}

BOOL CDataModule::OnActive()
{
    if (!CNBaseModule::OnActive())
    {
        return FALSE;
    }

    // 
    m_wndTfcParsed.ReDraw();



#if defined(_IMPORT_TFCEVENTDATA_TO_DATABASE) && defined(_DEBUG)
#pragma message("\n_IMPORT_TFCEVENTDATA_TO_DATABASE defined!\n")

    CStdioFile  tfcEventFile;
    if ( !tfcEventFile.Open(GetExePath()+PATH_DATA_FILE+_T("TEST_TFCEVENT.txt"),CFile::modeRead|CFile::shareDenyNone) )
    {
        return FALSE;
    }

    CString strLine;

    while ( tfcEventFile.ReadString(strLine) )
    {
        int iIdx = 0;
        CString strValue;

        TTfcEventAttri tfcEvent;

        tfcEvent.m_strEventID = GetSFStr(strLine,iIdx++,"@").c_str();
        tfcEvent.m_strEventID.Trim();

        strValue = GetSFStr(strLine,iIdx++,"@").c_str();
        tfcEvent.m_timeAlarm.ParseDateTime(strValue);

        tfcEvent.m_iEventType = (int)GetNFStr(strLine,iIdx++,"@");

        tfcEvent.m_strContent = GetSFStr(strLine,iIdx++,"@").c_str();
        tfcEvent.m_strContent.Trim();

        tfcEvent.m_iHandledState = (int)GetNFStr(strLine,iIdx++,"@");

        tfcEvent.m_iValid = (int)GetNFStr(strLine,iIdx++,"@");

        tfcEvent.m_strCaseAddr = GetSFStr(strLine,iIdx++,"@").c_str();
        tfcEvent.m_strCaseAddr.Trim();

        tfcEvent.m_strPhoneNo = GetSFStr(strLine,iIdx++,"@").c_str();
        tfcEvent.m_strPhoneNo.Trim();

        tfcEvent.m_ptPhonePos.iX = GetFloatFromStr(strLine,iIdx++,"@")*3600*24;
        tfcEvent.m_ptPhonePos.iY = GetFloatFromStr(strLine,iIdx++,"@")*3600*24;

        tfcEvent.m_ptAddrPos.iX = GetFloatFromStr(strLine,iIdx++,"@")*3600*24;
        tfcEvent.m_ptAddrPos.iY = GetFloatFromStr(strLine,iIdx++,"@")*3600*24;

        // Save to database
     
        if (m_OracleDB.IsOpen())
        {
            CString strSQL;
            strSQL.Format( _T("INSERT INTO %s(%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)\
                              VALUES('%s',to_Date('%s','yyyy-mm-dd HH24:mi:ss'),%d,%d,%d,'%s',%d,%d,%d,%d,'%s','%s')"),
                            
                            T_TFC_EVENT_LIVE,

                            TI_TE_EVENTID, TI_TE_ALARMTIME,TI_TE_EVETTYPE,TI_TE_HANLDEDSTATE,
                            TI_TE_VALIDFLAG, TI_TE_PHONENO, 
                            TI_TE_PHONEX,TI_TE_PHONEY,TI_TE_ADDRX,TI_TE_ADDRY,
                            TI_TE_CASEADDR,TI_TE_CONTENT,

                            tfcEvent.m_strEventID,tfcEvent.m_timeAlarm.Format("%Y-%m-%d %H:%M:%S"),tfcEvent.m_iEventType,tfcEvent.m_iHandledState,
                            tfcEvent.m_iValid,tfcEvent.m_strPhoneNo,tfcEvent.m_ptPhonePos.iX,tfcEvent.m_ptPhonePos.iY,
                            tfcEvent.m_ptAddrPos.iX,tfcEvent.m_ptAddrPos.iY,tfcEvent.m_strCaseAddr,tfcEvent.m_strContent

                        );
            m_OracleDB.Execute(strSQL);
        }

    }

    tfcEventFile.Close();

#else
#pragma message("\n_IMPORT_TFCEVENTDATA_TO_DATABASE NOT defined!\n")
#endif

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// From CNbaseModule

void CDataModule::OnRecvIMCMessage(PTImcMsg aImcMsg)
{
    NB_MSGID msgType = aImcMsg->GetMsgType();
    switch(msgType)
    {

    case EMSG_RECV_RAWTFCINF:
        {
            PIMsgRawTrafInf pTrafficInf = (PIMsgRawTrafInf)aImcMsg;

            // ������ʾ
            UpdateTfcViewInf(*pTrafficInf);

            // 

#ifdef _SAVE_TFCINF2DATABSE

            PTRoadIDMap pRoadIDMap = NULL;
            m_roadIDMgr.Lookup(pTrafficInf->m_tfcRawRoadInf.strRoadID,pRoadIDMap);
            ASSERT(pRoadIDMap!=NULL);
            pTrafficInf->m_tfcRawRoadInf.dwRoadID = pRoadIDMap->dwRoadID;

            // ���µ����ݿ�
            UpdateRoadInfo(*pTrafficInf);
#endif

            // ����ԭʼ����

            /***********************************************************************/
            /* 1. ���������������ֹ���ƽ���(����Link�Ĳ������Ը�ֵ)��             */
            /*    ����ֵ�У�LinkID��Link������ꡢLink�յ����ꡢLink��״�����ꡢ   */
            /*    Link���ơ�                                                       */
            /***********************************************************************/
            CLinkList* pLinkList = m_TfcParsedMgr.GetLinksByRoadID(pTrafficInf->m_tfcRawRoadInf.strRoadID);


            /************************************************************************/
            /* 2. ��Link���������Ը�ֵ��������⡣                                  */
            /*    ����ֵ�У��ٶȡ�ӵ�¼���ӵ��ԭ�򡢷���ʱ�䡣                    */
            /************************************************************************/
            if (pLinkList!=NULL)
            {
                POSITION pos = pLinkList->GetHeadPosition();
                while (pos)
                {
                    PTLinkAttri pLink = pLinkList->GetNext(pos);

                    pLink->SetSpeed(int(pTrafficInf->m_tfcRawRoadInf.fSpeed));
                    pLink->m_iJamReason = pTrafficInf->m_tfcRawRoadInf.iJamReason;
                    pLink->m_pubTime = pTrafficInf->m_tfcRawRoadInf.timePublish;

#ifdef _SAVE_TFCINF2DATABSE

#pragma message("\n _SAVE_TFCINF2DATABSE defined!\n")
                    // ���µ����ݿ�
                    UpdateLinkInfo(*pLink);

#endif
                }
            }


        }
        break;

        // ˢ�½�ͨ��Ϣ
    case EMSG_FLASH_TFCRAW:
        {
            m_wndTfcView.ReDraw();
        }
        break;


        // ����ԭʼ��ͨ��Ϣ��ͼ
    case EMSG_CREATE_TFCRAWVIEW:
        {
            PIMsgCreateTfcView pMsg = (PIMsgCreateTfcView)aImcMsg;
            ASSERT(pMsg!=NULL);
            ASSERT(pMsg->pRefWnd!=NULL);
            ASSERT(pMsg->pRefWnd->IsKindOf(RUNTIME_CLASS(CWnd)));
            BOOL bFlag = m_wndTfcView.Create(pMsg->pRefWnd);

            if (!bFlag)
            {
                IMsgAppLogs aLog;
                aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
                aLog.strComments.Format(_T("ԭʼ��ͨ��Ϣ��ʾ�����ʼ��ʧ�ܣ�"));
                NbsSendModuleMsg(&aLog);
            }
        }
        break;

        // ����������Ľ�ͨ��Ϣ��ͼ
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
                 aLog.strComments.Format(_T("������Ľ�ͨ��Ϣ��ʾ�����ʼ��ʧ�ܣ�"));
                 NbsSendModuleMsg(&aLog);
             }
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
    aLog.strComments.Format(_T("���ڹر����ݡ���"));
    NbsSendModuleMsg(&aLog);

    m_TfcInfMgr.Close();
    m_TfcParsedMgr.Close();
    m_OracleDB.Close();
    m_roadIDMgr.Clear();

    //
    CNBaseModule::OnClose();
}

//////////////////////////////////////////////////////////////////////////
// 
void CDataModule::GetDBCnntPara(CString& strSource,CString& strUsername,CString& strPwd) const
{
    // �������ļ��ж�ȡ���ݿ����
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
    //** �������ļ��ж�ȡ���ݿ����
    CString strDataSource,strUserID,strPWD;
    GetDBCnntPara(strDataSource,strUserID,strPWD);

    //** ���ӵ����ݿ�
    if (!m_OracleDB.ConnectOracle(strDataSource,strUserID,strPWD))
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

BOOL CDataModule::UpdateRoadInfo(IMsgRawTrafInf& wsTrafInf)
{
    if (!m_OracleDB.IsOpen())
    {
        return FALSE;
    }

    CString strSQL;
    CAdoRecordSet records; 

    /************************************************************************/
    /* ����ʵ������                                                         */
    /************************************************************************/

    // 1. ������Ӧ�ĵ�·
    strSQL.Format(_T("SELECT %s FROM %s WHERE %s='%s'"), 
         TI_RT_GATHERTIME, T_RAW_TRAFFICNAME,
         TI_RT_ROADID_OLD,wsTrafInf.m_tfcRawRoadInf.strRoadID);

    records = m_OracleDB.Execute(strSQL);

    if (records.GetRecordCount()>0)
    {
        records.MoveFirst();
        COleDateTime tOldTime;
        records.GetCollect(TI_RT_GATHERTIME,tOldTime); // ����ʱ��

        // �жϷ���ʱ���Ƿ�һ��
        if (tOldTime!=wsTrafInf.m_tfcRawRoadInf.timePublish)
        {
            // ��������
            strSQL.Format(_T("UPDATE %s SET %s=%f,%s=to_Date('%s','yyyy-mm-dd HH24:mi:ss') WHERE %s='%s'"), 
                T_RAW_TRAFFICNAME, 
                TI_RT_SPEED, wsTrafInf.m_tfcRawRoadInf.fSpeed,
                TI_RT_GATHERTIME, wsTrafInf.m_tfcRawRoadInf.timePublish.Format(_T("%Y-%m-%d %H:%M:%S")), 
                TI_RT_ROADID_OLD,wsTrafInf.m_tfcRawRoadInf.strRoadID);

            m_OracleDB.Execute(strSQL);
        }
    }
    else
    {
        // ���������ݵ�ʵ����Ϣ����
        strSQL.Format( _T("INSERT INTO %s(%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)\
                          VALUES('%s',%d,'%s',%d,%d,%d,%d,%d,%f,%d,to_Date('%s','yyyy-mm-dd HH24:mi:ss'),'%s','%s',%d,%d,%d,%d)"),

                          T_RAW_TRAFFICNAME,
                          TI_RT_ROADID_OLD,TI_RT_ROADID_NEW,TI_RT_ROADNAME,TI_RT_STARTPOSX,TI_RT_STARTPOSY,
                          TI_RT_ENDPOSX,TI_RT_ENDPOSY,TI_RT_ROADLEVEL,TI_RT_SPEED,
                          TI_RT_JAMREASON,TI_RT_GATHERTIME,
                          TI_RT_STARTNAME,TI_RT_ENDNAME,
                          TI_RT_CORSTAPX,TI_RT_CORSTAPY,TI_RT_CORENDPX,TI_RT_CORENDPY,

                          wsTrafInf.m_tfcRawRoadInf.strRoadID,
                          wsTrafInf.m_tfcRawRoadInf.dwRoadID,
                          wsTrafInf.m_tfcRawRoadInf.strRoadName,
                          wsTrafInf.m_tfcRawRoadInf.ptStartPos.iX, wsTrafInf.m_tfcRawRoadInf.ptStartPos.iY,
                          wsTrafInf.m_tfcRawRoadInf.ptEndPos.iX,wsTrafInf.m_tfcRawRoadInf.ptEndPos.iY,
                          0, // TI_RT_ROADLEVEL
                          wsTrafInf.m_tfcRawRoadInf.fSpeed,
                          wsTrafInf.m_tfcRawRoadInf.iJamReason,
                          wsTrafInf.m_tfcRawRoadInf.timePublish.Format(_T("%Y-%m-%d %H:%M:%S")), 
                          wsTrafInf.m_tfcRawRoadInf.strStartName,wsTrafInf.m_tfcRawRoadInf.strEndName,
                          wsTrafInf.m_tfcRawRoadInf.ptCorStaPos.iX, wsTrafInf.m_tfcRawRoadInf.ptCorStaPos.iY,
                          wsTrafInf.m_tfcRawRoadInf.ptCorEndPos.iX, wsTrafInf.m_tfcRawRoadInf.ptCorEndPos.iY );

        m_OracleDB.Execute(strSQL);
    }

    // ɾ����Ӧ�ĵ�·
    /*strSQL.Format(_T("DELETE FROM %s WHERE %s='%s'"),
        T_RAW_TRAFFICNAME,
        TI_RT_ROADID,wsTrafInf.m_tfcRawRoadInf.strRoadID);*/



   


    /************************************************************************/
    /* ����Ϊ��ʷ����                                                       */
    /************************************************************************/

    // 1. ����Ψһ�Լ��
    strSQL.Format(  _T("SELECT %s FROM %s WHERE %s='%s' AND to_Char(%s,'yyyy-mm-dd HH24:mi:ss') = '%s' "),
        TI_TFCRDH_ROADID, T_TFC_RAWDATA_HISTORY,
        TI_TFCRDH_ROADID, wsTrafInf.m_tfcRawRoadInf.strRoadID,
        TI_TFCRDH_GATHERTIME, wsTrafInf.m_tfcRawRoadInf.timePublish.Format(_T("%Y-%m-%d %H:%M:%S")) );

    records = m_OracleDB.Execute(strSQL);
    if (records.GetRecordCount()>0)
    {
        return TRUE;
    }

    // 2. ���ݱ��浽��ʷ���ݱ���
    strSQL.Format( _T("INSERT INTO %s(%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)\
                      VALUES('%s','%s',%d,%d,%d,%d,%d,%d,%d,to_Date('%s','yyyy-mm-dd HH24:mi:ss'),'%s','%s',%d,%d,%d,%d)"),

                      T_TFC_RAWDATA_HISTORY,
                      TI_TFCRDH_ROADID,TI_TFCRDH_ROADNAME,TI_TFCRDH_STARTPOSX,TI_TFCRDH_STARTPOSY,
                      TI_TFCRDH_ENDPOSX,TI_TFCRDH_ENDPOSY,TI_TFCRDH_ROADLEVEL,TI_TFCRDH_SPEED,
                      TI_TFCRDH_JAMREASON,TI_TFCRDH_GATHERTIME,
                      TI_TFCRDH_STARTNAME,TI_TFCRDH_ENDNAME,
                      TI_TFCRDH_CORSTAPX,TI_TFCRDH_CORSTAPY,TI_TFCRDH_ENDPOSX,TI_TFCRDH_ENDPOSY,

                      wsTrafInf.m_tfcRawRoadInf.strRoadID,
                      wsTrafInf.m_tfcRawRoadInf.strRoadName,
                      wsTrafInf.m_tfcRawRoadInf.ptStartPos.iX, wsTrafInf.m_tfcRawRoadInf.ptStartPos.iY,
                      wsTrafInf.m_tfcRawRoadInf.ptEndPos.iX,wsTrafInf.m_tfcRawRoadInf.ptEndPos.iY,
                      0, // TI_RT_ROADLEVEL
                      int(wsTrafInf.m_tfcRawRoadInf.fSpeed),
                      wsTrafInf.m_tfcRawRoadInf.iJamReason,
                      wsTrafInf.m_tfcRawRoadInf.timePublish.Format(_T("%Y-%m-%d %H:%M:%S")), 
                      wsTrafInf.m_tfcRawRoadInf.strStartName,wsTrafInf.m_tfcRawRoadInf.strEndName,
                      wsTrafInf.m_tfcRawRoadInf.ptCorStaPos.iX, wsTrafInf.m_tfcRawRoadInf.ptCorStaPos.iY,
                      wsTrafInf.m_tfcRawRoadInf.ptCorEndPos.iX, wsTrafInf.m_tfcRawRoadInf.ptCorEndPos.iY );

    m_OracleDB.Execute(strSQL);


    return TRUE;
}


BOOL CDataModule::UpdateLinkInfo(TLinkAttri& linkAttri)
{
    if (!m_OracleDB.IsOpen())
    {
        return FALSE;
    }

    CString strSQL;
    CAdoRecordSet records; 

    /*strSQL.Format( _T("DELETE FROM %s WHERE %s = '%s'"),
        T_TRFFICINF_NAME,
        TI_TP_LINKID, linkAttri.m_strLinkID);*/


    // 1. ������Ӧ��Link�Ƿ����
    strSQL.Format(_T("SELECT %s FROM %s WHERE %s='%s'"), 
        TI_TP_UPDATETIME, T_TRFFICINF_NAME,
        TI_TP_LINKID, linkAttri.m_strLinkID);

    records = m_OracleDB.Execute(strSQL);
    if (records.GetRecordCount()>0)
    {
        records.MoveFirst();
        COleDateTime tOldTime;

        records.GetCollect(TI_TP_UPDATETIME,tOldTime); // ����ʱ��

        // �жϷ���ʱ���Ƿ�һ��
        if (tOldTime!=linkAttri.m_pubTime)
        {
            // ��������
            strSQL.Format(_T("UPDATE %s SET %s=%d,%s=%d,%s=%d,%s=to_Date('%s','yyyy-mm-dd HH24:mi:ss') WHERE %s='%s'"), 
                T_TRFFICINF_NAME, 
                TI_TP_SPEED, linkAttri.m_iSpeed,
                TI_TP_JAMLEVEL, linkAttri.m_iJamLevel,
                TI_TP_JAMREASON, linkAttri.m_iJamReason,
                TI_TP_UPDATETIME, linkAttri.m_pubTime.Format(_T("%Y-%m-%d %H:%M:%S")), 
                TI_TP_LINKID, linkAttri.m_strLinkID);

            m_OracleDB.Execute(strSQL);
        }

    }
    else
    {

        // ����������
        strSQL.Format( _T("INSERT INTO %s(%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)\
                          VALUES(to_Date('%s','yyyy-mm-dd HH24:mi:ss'),'%s',%d,%d,%d,%d,%d,'%s',%d,%d,%d)"),

                          T_TRFFICINF_NAME, //
                          TI_TP_UPDATETIME,TI_TP_LINKID,TI_TP_ROADID,TI_TP_STARTPOSX,TI_TP_STARTPOSY,TI_TP_ENDPOSX,TI_TP_ENDPOSY,
                          TI_TP_LINKNAME,TI_TP_SPEED,TI_TP_JAMLEVEL,TI_TP_JAMREASON,

                          linkAttri.m_pubTime.Format(_T("%Y-%m-%d %H:%M:%S")),
                          linkAttri.m_strLinkID, linkAttri.m_dwRoadID,
                          linkAttri.m_StartPos.iX, linkAttri.m_StartPos.iY,
                          linkAttri.m_EndPos.iX,   linkAttri.m_EndPos.iY,
                          linkAttri.m_strLinkName,
                          linkAttri.m_iSpeed,
                          linkAttri.m_iJamLevel,
                          linkAttri.m_iJamReason );

        m_OracleDB.Execute(strSQL);

    }


#if 0
    // ������ʷ����
    strSQL.Format( _T("INSERT INTO %s(%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)\
                      VALUES(to_Date('%s','yyyy-mm-dd HH24:mi:ss'),'%s',%d,%d,%d,%d,'%s',%d,%d,%d)"),

                      T_TFC_PARSEDDATA_HISTORY, //
                      TI_TFCPDH_UPDATETIME,TI_TFCPDH_LINKID,TI_TFCPDH_ROADID,TI_TFCPDH_STARTPOSX,TI_TFCPDH_STARTPOSY,TI_TFCPDH_ENDPOSX,TI_TFCPDH_ENDPOSY,
                      TI_TFCPDH_LINKNAME,TI_TFCPDH_SPEED,TI_TFCPDH_JAMLEVEL,TI_TFCPDH_JAMREASON,

                      linkAttri.m_pubTime.Format(_T("%Y-%m-%d %H:%M:%S")),
                      linkAttri.m_strLinkID, linkAttri.m_strRoadID,
                      linkAttri.m_StartPos.x, linkAttri.m_StartPos.y,
                      linkAttri.m_EndPos.x,   linkAttri.m_EndPos.y,
                      linkAttri.m_strLinkName,
                      linkAttri.m_iSpeed,
                      linkAttri.m_iJamLevel,
                      linkAttri.m_iJamReason );

    m_OracleDB.Execute(strSQL);
#endif
    
    return TRUE;
}


void CDataModule::UpdateTfcViewInf(IMsgRawTrafInf& wsTrafInf)
{
    // ����·����Ϣ��ˢ��ʱ��
    m_TfcInfMgr.UpdateFlashTime();

    // 
    m_TfcInfMgr.SetAt(wsTrafInf.m_tfcRawRoadInf.strRoadID,&wsTrafInf);

}


#if 0

BOOL CDataModule::RetrieveLinkInfo(CLinkList& aLinkList) const
{
    if (!m_OracleDB.IsOpen())
    {
        return FALSE;
    }

    CString strSQL;
    strSQL.Format( _T("SELECT * FROM %s "),T_TRFFICINF_NAME);

    CAdoRecordSet records; 
    records = m_OracleDB.Execute(strSQL);

    int iCount = records.GetRecordCount();
    if (iCount<=0)
    {
        return FALSE;
    }


    // 
    records.MoveFirst();
    for (int ii=0; ii<iCount; ii++)
    {

        PTLinkAttri pLink = new TLinkAttri;

        try
        {
            records.GetCollect(TI_TP_UPDATETIME,    pLink->m_pubTime);
            records.GetCollect(TI_TP_LINKID,        pLink->m_strLinkID);
            records.GetCollect(TI_TP_ROADID,        pLink->m_strRoadID);
            records.GetCollect(TI_TP_STARTPOSX,     pLink->m_StartPos.iX);
            records.GetCollect(TI_TP_STARTPOSY,     pLink->m_StartPos.iY);
            records.GetCollect(TI_TP_ENDPOSX,       pLink->m_EndPos.iX);
            records.GetCollect(TI_TP_ENDPOSY,       pLink->m_EndPos.iY);
            records.GetCollect(TI_TP_LINKNAME,      pLink->m_strLinkName);
            records.GetCollect(TI_TP_SPEED,         pLink->m_iSpeed);
            records.GetCollect(TI_TP_JAMLEVEL,      pLink->m_iJamLevel);
            records.GetCollect(TI_TP_JAMREASON,     pLink->m_iJamReason);

        }
        catch (CException* e)
        {
            e->Delete();
        	delete pLink;

            records.MoveNext();
            continue;
        }

        // 
        aLinkList.AddTail(pLink);

        records.MoveNext();
    }

    return TRUE;

}
#endif