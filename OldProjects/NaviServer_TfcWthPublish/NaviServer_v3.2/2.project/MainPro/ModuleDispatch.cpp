#include "StdAfx.h"
#include ".\moduledispatch.h"
#include "InterfaceEx.h"
#include "GlobalMacro.h"


#pragma warning(disable:4355)

//////////////////////////////////////////////////////////////////////////

DECLARE_NBASE_DISPATCHER(CModuleDispatch)


//////////////////////////////////////////////////////////////////////////
CModuleDispatch::CModuleDispatch(void):
        m_SckModule(*this),
        m_UIModule(*this),
        m_DataModule(*this)

{
    NbsRegisterDispather(this);

    // ע��˳����ģ��ĳ�ʼ��˳���й�
    Register(&m_UIModule);
    Register(&m_SckModule);
    Register(&m_DataModule);
}

CModuleDispatch::~CModuleDispatch(void)
{
    
}

void CModuleDispatch::OnInitialize()
{
    SetLogPath(GetExePath()+PATH_APP_LOG);
}

void CModuleDispatch::OnInitFailure(TModuleID aModulID)
{
    CImcDispatcher::OnInitFailure(aModulID);

    // Add your code after this.

    //
    CString strTip;
    strTip.Format(_T("�����ʼ��ʧ�ܣ�ģ��ID = %d��\n���ȷ�����˳�����"),
                    aModulID);

    ::MessageBox(NULL,strTip,"����",MB_ICONERROR);
}

void CModuleDispatch::OnStartFailure(TModuleID aModulID)
{
    CImcDispatcher::OnStartFailure(aModulID);

    // Add your code after this.

    //
    CString strTip;
    strTip.Format(_T("��������ʧ�ܣ�ģ��ID = %d��\n���ȷ�����˳�����"),aModulID);

    ::MessageBox(NULL,strTip,"����",MB_ICONERROR);

    //
    m_UIModule.GetMainWnd()->m_bCloseTip = FALSE;
    m_UIModule.GetMainWnd()->PostMessage(WM_CLOSE);
}

BOOL CModuleDispatch::OnActive()
{

    // to do it before this
    return CImcDispatcher::OnActive();
}


void CModuleDispatch::OnClosing()
{
    m_UIModule.m_dlgStart.ShowWindow(SW_SHOW);
}


// Handling before dispatching message.
BOOL CModuleDispatch::PreDispatchMsg(PTImcMsg aIMCMsg)
{
    NB_MSGID wMsgType = aIMCMsg->GetMsgType();
    
    //
    if (ESCK_RECV_FRAME==wMsgType)
    {
        PIMsgFrmRecved pRecvFrame = (PIMsgFrmRecved)aIMCMsg;
        DWORD dwComfieldID = pRecvFrame->m_comFiledID;

        TBaseProtocol* pUnKnowFrame = (TBaseProtocol*)(pRecvFrame->m_pFrameBuf);

        if (pUnKnowFrame->GetProType()==TMobileFrame_Char::E_PRO_FLAG)
        {
            TMobileFrame_Char* pFrameChar = (TMobileFrame_Char*)(pRecvFrame->m_pFrameBuf);
            HandleMobileRequest_char(pFrameChar,dwComfieldID);
        }
        else if (pUnKnowFrame->GetProType()==TMobileFrameBin::E_PRO_FLAG)
        {
            TMobileFrameBin* pFrameBin = (TMobileFrameBin*)(pRecvFrame->m_pFrameBuf);
            HandleMobileRequest_bin(pFrameBin,dwComfieldID);
        }
        else if (pUnKnowFrame->GetProType()==TSpFrame::E_PRO_FLAG)
        {
        }
    }

    return CImcDispatcher::PreDispatchMsg(aIMCMsg);
}

// ���������ֻ�������ʹ���ַ�Э�飩
void CModuleDispatch::HandleMobileRequest_char(PTMobileFrame_Char pFrameChar,DWORD dwComfieldID)
{
    
    WORD wCmdID = pFrameChar->wCmdID;

    if (wCmdID==TWeatherReq_Char::ECommandID)
    {

        PTWeatherReq_Char weatherReq = PTWeatherReq_Char(pFrameChar);

        ASSERT(weatherReq->byType==TWeatherReq_Char::ERT_POSITION);

        // 1. �Ƿ��ڱ���
        CString strGBAreaID;
        BOOL bFound = m_DataModule.GetRegionIDByPosition(TMPoint(weatherReq->dwLongitude,weatherReq->dwLatitude),
            strGBAreaID);

        // 2. �ж��ǲ��ǲ�ѯ������������Ϣ
        if ( bFound )
        {
            // ��������������ݿ��в�����Ӧ�����������Ϣ
            TWeatherInf weatherInf;
            weatherInf.cPeriodFlag = TWeatherInf::TPeriodCode(weatherReq->byPeriod);
            weatherInf.strDistID = strGBAreaID;
            BOOL bRc = m_DataModule.GetDistrictWeather(char(weatherInf.cPeriodFlag),weatherInf.strDistID,weatherInf);

            // ��������ָ������
            TWeatherRsp1_char wthInfRsp;
            wthInfRsp.byFlag = TWeatherRsp1_char::ETF_PRE_POS;
            wthInfRsp.byExcuteRst = (!bRc) ? (TWeatherRsp1_char::EExeFailure) : (TWeatherRsp1_char::EExeSuccess);
            wthInfRsp.dwLongitude = weatherReq->dwLongitude;  //����
            wthInfRsp.dwLatitude = weatherReq->dwLatitude;   //γ��
            wthInfRsp.weatherInf.cPeriodFlag = TWeatherInf::TPeriodCode(weatherReq->byPeriod);//ʱ��ָʾ��
            wthInfRsp.weatherInf.strDistID = strGBAreaID;
            if (bRc)
            {
                wthInfRsp.weatherInf = weatherInf;
            }
            else
            {
                TRACE("\nû���ҵ�����%s������Ԥ����Ϣ��",strGBAreaID);		
            }

            // Send Frame to socket.
            IMsgFrmSending sckFrame;
            sckFrame.m_pFrameBuf = &wthInfRsp;
            sckFrame.m_comFiledID = dwComfieldID;
            NbsSendModuleMsg(&sckFrame);
        }
        else
        {
            TWeatherRsp2_char wthRsp;
            // ���ݾ�γ�Ȳ�����Ӧ�ĳ���ID
            TMPoint pos = TMPoint(weatherReq->dwLongitude,weatherReq->dwLatitude);

            // ���������ѯ��Ӧ���е�������Ϣ
            BOOL bc = m_DataModule.GetCityWthInfByPos(pos,wthRsp.strCityName,wthRsp.strWthDes);
            wthRsp.byExcuteRst = bc ? TWeatherRsp2_char::EExeSuccess: TWeatherRsp2_char::EExeFailure;
            wthRsp.byPeriod = weatherReq->byPeriod;

            if (!bc)
            {
                wthRsp.byExcuteRst = TWeatherRsp1_char::EExeSuccess;
                wthRsp.strWthDes = " û�п��õ�������Ϣ��";
            }


            // Send Frame to socket.
            IMsgFrmSending sckFrame;
            sckFrame.m_pFrameBuf = &wthRsp;
            sckFrame.m_comFiledID = dwComfieldID;
            NbsSendModuleMsg(&sckFrame);

        }
    }


    // ͨ��Link��ֹ������·����Ϣ<�ն���·���滮>
    else if(TTfcReqByPos_char::ECommandID==wCmdID)
    {
        PTTfcReqByPos_char request = PTTfcReqByPos_char(pFrameChar);

        /******************************************************/
        /*  ����ʵʱ·������ָ��                              */
        /******************************************************/
        TTfcRsp1_Char trfLivRsp;
        trfLivRsp.byExcuteRst = TTfcRsp1_Char::ESucess;

        //
        POSITION pos = request->linkPosList.GetHeadPosition();
        while (pos)
        {
            PTLinkAttri pRecvLink = request->linkPosList.GetNext(pos);

            // ����Link��ֹ�������Ƶõ�����Ӧ�Ľ�ͨ��Ϣ
            PTLinkAttri linkInf = new TLinkAttri;
            *linkInf = *pRecvLink;
            m_DataModule.GetSpecifiedLinkTfcInf(*linkInf);

            //
            trfLivRsp.DtiList.AddTail(linkInf);

        }

        // Send Frame to socket.
        IMsgFrmSending sckFrame;
        sckFrame.m_pFrameBuf = &trfLivRsp;
        sckFrame.m_comFiledID = dwComfieldID;
        NbsSendModuleMsg(&sckFrame);
    }

    // ͨ����·��������ʵʱ·����Ϣָ��
    else if(TTfcReqByRoadName_Char::ECommandID==wCmdID)
    {
        PTTfcReqByRoadName_Char request = PTTfcReqByRoadName_Char(pFrameChar);

        /******************************************************/
        /*  ����ʵʱ·������ָ��                              */
        /******************************************************/
        TTfcRsp2_Char trfLivRsp; 

        // ���ݵ�·������λ�ò�ѯ·����Ϣ
        TMPoint roadPos(request->dwLongitude,request->dwLatitude);
        m_DataModule.GetRoadTfcInfByRoadName(trfLivRsp.m_RoadTfcList,request->strRoadName,roadPos);


        // ָ��ִ�б�ʶ
        WORD wDTICount = (WORD)(trfLivRsp.m_RoadTfcList.GetCount());
        trfLivRsp.m_byResult = wDTICount>0 ? TTfcRsp2_Char::ESucess : TTfcRsp2_Char::EFailure;


        // Send Frame to socket.
        IMsgFrmSending sckFrame;
        sckFrame.m_pFrameBuf = &trfLivRsp;
        sckFrame.m_comFiledID = dwComfieldID;
        NbsSendModuleMsg(&sckFrame);
    }

}
void CModuleDispatch::HandleMobileRequest_bin(PTMobileFrameBin pFrameBin,DWORD dwComfieldID)
{
    WORD wCmdID = pFrameBin->wCmdID;

    switch(wCmdID)
    {
        // Login request
    case TLoginReqBin::ECommandID:
        {
            PTLoginReqBin pLogReq = (PTLoginReqBin)pFrameBin;

            /****************************************************/
            /*  ��֤�û��Ϸ��ԣ���������Ϣ                      */
            /****************************************************/
            
            // to check if it's valid.
            TLoginRspBin loginRsp;
            loginRsp.strUserName = pLogReq->strUserName;
            if ( m_AuthenMgr.IsValidPassport(pLogReq->strUserName,
                pLogReq->byRadomAuthen,sizeof(pLogReq->byRadomAuthen)) )
            {
                loginRsp.byLoginRst = TLoginRspBin::ESuccess;
            }
            else
            {
                loginRsp.byLoginRst = TLoginRspBin::EUnknown;
            }

            // Send Frame to socket.
            IMsgFrmSending sckFrame;
            sckFrame.m_pFrameBuf = &loginRsp;
            sckFrame.m_comFiledID = dwComfieldID;
            NbsSendModuleMsg(&sckFrame);
        }
        break;

        // Weather information request by position
    case TWthReqByPosBin::ECommandID:
        {
            TWthRspBin wthInfRsp;

            PTWthReqByPos_bin pWthReq = (PTWthReqByPos_bin)pFrameBin;

            //* 1. ���ݾ�γ���ҵ������루���꣩
            CString strGBAreaID;
            BOOL bFound = m_DataModule.GetRegionIDByPosition(TMPoint(pWthReq->dwLongitude,pWthReq->dwLatitude),
                strGBAreaID);

            if (bFound)
            {
                /* 2.��������������ݿ��в�����Ӧ�����������Ϣ                        */

                wthInfRsp.weatherInf.cPeriodFlag = TWeatherInf::TPeriodCode(pWthReq->byPeriod);
                wthInfRsp.weatherInf.strDistID = strGBAreaID;

                BOOL bRc = m_DataModule.GetDistrictWeather(char(pWthReq->byPeriod),
                    strGBAreaID,wthInfRsp.weatherInf);

                if (!bRc)
                {
                    TRACE("\nû���ҵ�����%s������Ԥ����Ϣ��",strGBAreaID);
                    wthInfRsp.bySerciveCode = TMobileFrameBin::EServiceFailure;
                }

                // Send Frame to socket.
                IMsgFrmSending sckFrame;
                sckFrame.m_pFrameBuf = &wthInfRsp;
                sckFrame.m_comFiledID = dwComfieldID;
                NbsSendModuleMsg(&sckFrame);

            }
            else
            {
                // ���ݾ�γ�Ȳ�����Ӧ�ĳ���ID
                TMPoint pos = TMPoint(pWthReq->dwLongitude,pWthReq->dwLatitude);

                // ���������ѯ��Ӧ���е�������Ϣ
                BOOL bRc = m_DataModule.GetCityWthInfByPos(pos,wthInfRsp.strDistName,wthInfRsp.strWthDes);
                wthInfRsp.bySerciveCode = bRc?TMobileFrameBin::ESuccess:TMobileFrameBin::EServiceFailure;

                if (!bRc)
                {
                    wthInfRsp.strWthDes.Format(_T("%s: û�п��õ�������Ϣ��"),
                        wthInfRsp.strDistName);
                }

                // Send Frame to socket.
                IMsgFrmSending sckFrame;
                sckFrame.m_pFrameBuf = &wthInfRsp;
                sckFrame.m_comFiledID = dwComfieldID;
                NbsSendModuleMsg(&sckFrame);
            }
        }
        break;

        // request traffic information by road name.
    case TTfcReqByRoadNameBin::ECommandID:
        {
            PTTfcReqByRoadNameBin pTfcReq = (PTTfcReqByRoadNameBin)pFrameBin;

            
            /******************************************************/
            /*  ����ʵʱ·������ָ��                              */
            /******************************************************/
            TTfcInfRsp2_Bin trfLivRsp; 
            TMPoint linkPos(pTfcReq->dwLongitude,pTfcReq->dwLatitude);
            m_DataModule.GetRoadTfcInfByRoadName(trfLivRsp.m_RoadTfcList,pTfcReq->strRoadName,linkPos);


            // ָ��ִ�б�ʶ
            WORD wDTICount = WORD(trfLivRsp.m_RoadTfcList.GetCount());
            if (wDTICount>0 )
            {
                trfLivRsp.bySerciveCode = TMobileFrameBin::ESuccess;
            } 
            else
            {
                trfLivRsp.bySerciveCode = TMobileFrameBin::EServiceFailure;
            }


            // Send Frame to socket.
            IMsgFrmSending sckFrame;
            sckFrame.m_pFrameBuf = &trfLivRsp;
            sckFrame.m_comFiledID = dwComfieldID;
            NbsSendModuleMsg(&sckFrame);

        }
        break;

        // request traffic information by link's position
    case TTfcReqByLinkPosBin::ECommandID:
        {
            PTTfcReqByLinkPosBin pTfcReq = (PTTfcReqByLinkPosBin)pFrameBin;

            /******************************************************/
            /*  ����ʵʱ·������ָ��                              */
            /******************************************************/
            TTfcInfRsp1_Bin trfLivRsp;

            //
            POSITION pos = pTfcReq->linkPosList.GetHeadPosition();
            while (pos)
            {
                PTLinkAttri pRecvLink = (PTLinkAttri)(pTfcReq->linkPosList.GetNext(pos));

                // ����Link��ֹ�������Ƶõ�����Ӧ�Ľ�ͨ��Ϣ
                PTLinkAttri linkInf = new TLinkAttri;
                *linkInf = *pRecvLink;
                m_DataModule.GetSpecifiedLinkTfcInf(*linkInf);

                //
                trfLivRsp.m_DtiList.AddTail(linkInf);
            }

            // 
            IMsgFrmSending sckFrame;
            sckFrame.m_pFrameBuf = &trfLivRsp;
            sckFrame.m_comFiledID = dwComfieldID;
            NbsSendModuleMsg(&sckFrame);
        }
        break;
    }
}

// 

CMainFrame* CModuleDispatch::GetMainWnd()
{
    return m_UIModule.GetMainWnd();
}
