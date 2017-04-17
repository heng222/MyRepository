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

    // 注册顺序与模块的初始化顺序有关
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
    strTip.Format(_T("程序初始化失败，模块ID = %d。\n点击确定以退出程序。"),
                    aModulID);

    ::MessageBox(NULL,strTip,"错误",MB_ICONERROR);
}

void CModuleDispatch::OnStartFailure(TModuleID aModulID)
{
    CImcDispatcher::OnStartFailure(aModulID);

    // Add your code after this.

    //
    CString strTip;
    strTip.Format(_T("程序启动失败，模块ID = %d。\n点击确定以退出程序。"),aModulID);

    ::MessageBox(NULL,strTip,"错误",MB_ICONERROR);

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

// 处理来自手机的请求（使用字符协议）
void CModuleDispatch::HandleMobileRequest_char(PTMobileFrame_Char pFrameChar,DWORD dwComfieldID)
{
    
    WORD wCmdID = pFrameChar->wCmdID;

    if (wCmdID==TWeatherReq_Char::ECommandID)
    {

        PTWeatherReq_Char weatherReq = PTWeatherReq_Char(pFrameChar);

        ASSERT(weatherReq->byType==TWeatherReq_Char::ERT_POSITION);

        // 1. 是否在北京
        CString strGBAreaID;
        BOOL bFound = m_DataModule.GetRegionIDByPosition(TMPoint(weatherReq->dwLongitude,weatherReq->dwLatitude),
            strGBAreaID);

        // 2. 判断是不是查询北京的气象信息
        if ( bFound )
        {
            // 根据区域码从数据库中查找相应区域的气象信息
            TWeatherInf weatherInf;
            weatherInf.cPeriodFlag = TWeatherInf::TPeriodCode(weatherReq->byPeriod);
            weatherInf.strDistID = strGBAreaID;
            BOOL bRc = m_DataModule.GetDistrictWeather(char(weatherInf.cPeriodFlag),weatherInf.strDistID,weatherInf);

            // 构建返回指令数据
            TWeatherRsp1_char wthInfRsp;
            wthInfRsp.byFlag = TWeatherRsp1_char::ETF_PRE_POS;
            wthInfRsp.byExcuteRst = (!bRc) ? (TWeatherRsp1_char::EExeFailure) : (TWeatherRsp1_char::EExeSuccess);
            wthInfRsp.dwLongitude = weatherReq->dwLongitude;  //经度
            wthInfRsp.dwLatitude = weatherReq->dwLatitude;   //纬度
            wthInfRsp.weatherInf.cPeriodFlag = TWeatherInf::TPeriodCode(weatherReq->byPeriod);//时段指示码
            wthInfRsp.weatherInf.strDistID = strGBAreaID;
            if (bRc)
            {
                wthInfRsp.weatherInf = weatherInf;
            }
            else
            {
                TRACE("\n没有找到区域%s的天气预报信息！",strGBAreaID);		
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
            // 根据经纬度查找相应的城市ID
            TMPoint pos = TMPoint(weatherReq->dwLongitude,weatherReq->dwLatitude);

            // 根据坐标查询相应城市的气象信息
            BOOL bc = m_DataModule.GetCityWthInfByPos(pos,wthRsp.strCityName,wthRsp.strWthDes);
            wthRsp.byExcuteRst = bc ? TWeatherRsp2_char::EExeSuccess: TWeatherRsp2_char::EExeFailure;
            wthRsp.byPeriod = weatherReq->byPeriod;

            if (!bc)
            {
                wthRsp.byExcuteRst = TWeatherRsp1_char::EExeSuccess;
                wthRsp.strWthDes = " 没有可用的气象信息！";
            }


            // Send Frame to socket.
            IMsgFrmSending sckFrame;
            sckFrame.m_pFrameBuf = &wthRsp;
            sckFrame.m_comFiledID = dwComfieldID;
            NbsSendModuleMsg(&sckFrame);

        }
    }


    // 通过Link起止点请求路况信息<终端做路径规划>
    else if(TTfcReqByPos_char::ECommandID==wCmdID)
    {
        PTTfcReqByPos_char request = PTTfcReqByPos_char(pFrameChar);

        /******************************************************/
        /*  构建实时路况返回指令                              */
        /******************************************************/
        TTfcRsp1_Char trfLivRsp;
        trfLivRsp.byExcuteRst = TTfcRsp1_Char::ESucess;

        //
        POSITION pos = request->linkPosList.GetHeadPosition();
        while (pos)
        {
            PTLinkAttri pRecvLink = request->linkPosList.GetNext(pos);

            // 根据Link起止点与名称得到其相应的交通信息
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

    // 通过道路名称请求实时路况信息指令
    else if(TTfcReqByRoadName_Char::ECommandID==wCmdID)
    {
        PTTfcReqByRoadName_Char request = PTTfcReqByRoadName_Char(pFrameChar);

        /******************************************************/
        /*  构建实时路况返回指令                              */
        /******************************************************/
        TTfcRsp2_Char trfLivRsp; 

        // 根据道路名称与位置查询路况信息
        TMPoint roadPos(request->dwLongitude,request->dwLatitude);
        m_DataModule.GetRoadTfcInfByRoadName(trfLivRsp.m_RoadTfcList,request->strRoadName,roadPos);


        // 指令执行标识
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
            /*  验证用户合法性，并返回信息                      */
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

            //* 1. 根据经纬度找到区域码（国标）
            CString strGBAreaID;
            BOOL bFound = m_DataModule.GetRegionIDByPosition(TMPoint(pWthReq->dwLongitude,pWthReq->dwLatitude),
                strGBAreaID);

            if (bFound)
            {
                /* 2.根据区域码从数据库中查找相应区域的气象信息                        */

                wthInfRsp.weatherInf.cPeriodFlag = TWeatherInf::TPeriodCode(pWthReq->byPeriod);
                wthInfRsp.weatherInf.strDistID = strGBAreaID;

                BOOL bRc = m_DataModule.GetDistrictWeather(char(pWthReq->byPeriod),
                    strGBAreaID,wthInfRsp.weatherInf);

                if (!bRc)
                {
                    TRACE("\n没有找到区域%s的天气预报信息！",strGBAreaID);
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
                // 根据经纬度查找相应的城市ID
                TMPoint pos = TMPoint(pWthReq->dwLongitude,pWthReq->dwLatitude);

                // 根据坐标查询相应城市的气象信息
                BOOL bRc = m_DataModule.GetCityWthInfByPos(pos,wthInfRsp.strDistName,wthInfRsp.strWthDes);
                wthInfRsp.bySerciveCode = bRc?TMobileFrameBin::ESuccess:TMobileFrameBin::EServiceFailure;

                if (!bRc)
                {
                    wthInfRsp.strWthDes.Format(_T("%s: 没有可用的气象信息！"),
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
            /*  构建实时路况返回指令                              */
            /******************************************************/
            TTfcInfRsp2_Bin trfLivRsp; 
            TMPoint linkPos(pTfcReq->dwLongitude,pTfcReq->dwLatitude);
            m_DataModule.GetRoadTfcInfByRoadName(trfLivRsp.m_RoadTfcList,pTfcReq->strRoadName,linkPos);


            // 指令执行标识
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
            /*  构建实时路况返回指令                              */
            /******************************************************/
            TTfcInfRsp1_Bin trfLivRsp;

            //
            POSITION pos = pTfcReq->linkPosList.GetHeadPosition();
            while (pos)
            {
                PTLinkAttri pRecvLink = (PTLinkAttri)(pTfcReq->linkPosList.GetNext(pos));

                // 根据Link起止点与名称得到其相应的交通信息
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
