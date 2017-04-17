#include "StdAfx.h"
#include ".\sckmodule.h"
#include "GlobalMacro.h"

#pragma warning(disable:4355)


#define WSA_VERSION     MAKEWORD(2,0)
//////////////////////////////////////////////////////////////////////////

CSckModule::CSckModule(CImcDispatcher& aDispatcher):
        CNBaseModule(aDispatcher,ID_MODULE_NETWORK),
        m_mobileComfieldMgrChar(*this),
        m_mobileComfieldMgrBin(*this),
        m_SpComfieldMgr(*this),
        m_toBalanceServer(*this)
{
}

CSckModule::~CSckModule(void)
{
    NciCleanup();
    WSACleanup();
}

// 连接到SP
BOOL CSckModule::ConnectToSP()
{

    IMsgAppLogs aLog;

    // to do it...

    //
    CString strFilePath = GetExePath()+CString(PATH_CONFIGURE_FILE);
    char cAddr[MAX_PATH];
    WORD wPort = 0;


    /*********************************************************/
    /*  打开与SP通信通道                                     */
    /*********************************************************/	
#ifdef _DEBUG
    memset(cAddr,0,sizeof(cAddr));
#else
    ::GetPrivateProfileString(CFG_APPNAME_NETWORK,"SP_IP",0,cAddr,MAX_PATH,strFilePath);//"127.0.0.1";
#endif
    wPort = ::GetPrivateProfileInt(CFG_APPNAME_NETWORK,"SP_PORT",9001,strFilePath);

    m_SpComfieldMgr.InitProfile(TComMgrProfile::ECMP_SERVER,TSockAddr(cAddr,wPort),
        TSpFrame::E_PRO_FLAG);

    if(m_SpComfieldMgr.OpenCMG() == FALSE)
    {
        AfxMessageBox("与SP连接不成功！",MB_ICONERROR);
        return FALSE;
    }


    return TRUE;

}

// 连接到负载分配服务器
BOOL CSckModule::ConnectToBalServer()
{
    IMsgAppLogs aLog;

    // to do it...

    // Connected
    if (m_toBalanceServer.GetServerNum()>0)
    {
        return TRUE;
    }

    //
    CString strFilePath = GetExePath()+CString(PATH_CONFIGURE_FILE);
    char cAddr[MAX_PATH];
    WORD wPort = 0;


    /*********************************************************/
    /*  启动与负载均衡服务器的连接                           */
    /*********************************************************/
    aLog.strComments.Format(_T("正在连接到负载均衡器……"));
    SendModuleMsg(aLog);

    ::GetPrivateProfileString(CFG_APPNAME_NETWORK,"BALANCE_SERVER_IP",0,cAddr,MAX_PATH,strFilePath);//"
    wPort = ::GetPrivateProfileInt(CFG_APPNAME_NETWORK,"BALANCE_SERVER_PORT",0,strFilePath);

    m_toBalanceServer.InitProfile(TComMgrProfile::ECMP_CLIENT,TSockAddr(cAddr,wPort),
        TBusinessFrm::E_PRO_FLAG);

    if(m_toBalanceServer.OpenCMG() == FALSE)
    {
        aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
        aLog.UpdateToCurrentTime();
        aLog.strComments.Format(_T("连接到负载均衡器失败!"));
        SendModuleMsg(aLog);

        return FALSE;
    }

    return TRUE;
}

// 启动交通与气象发布服务
BOOL  CSckModule::StartPubServcie()
{
    IMsgAppLogs aLog;
    aLog.strComments.Format(_T("正在启动交通气象发布服务……"));
    SendModuleMsg(aLog);

    // to do it...

    //
    CString strFilePath = GetExePath()+CString(PATH_CONFIGURE_FILE);
    char cAddr[MAX_PATH]={0};
    WORD wPort = 0;

    /*********************************************************/
    /*  打开与手机通信通道——字符协议                       */
    /*********************************************************/	
    ::GetPrivateProfileString(CFG_APPNAME_NETWORK,"MOBILE_IP_CHAR",0,cAddr,MAX_PATH,strFilePath);//"127.0.0.1";
    wPort = ::GetPrivateProfileInt(CFG_APPNAME_NETWORK,"MOBILE_PORT_CHAR",0,strFilePath);

    m_mobileComfieldMgrChar.InitProfile(TComMgrProfile::ECMP_SERVER,TSockAddr(cAddr,wPort),
        TMobileFrame_Char::E_PRO_FLAG);

    if(m_mobileComfieldMgrChar.OpenCMG() == FALSE)
    {
        StopPubService();

        IMsgAppLogs aLog;
        aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
        aLog.strComments.Format(_T("服务启动失败！请在<选项>中检查配置参数。"));
        NbsSendModuleMsg(&aLog);

        ::MessageBox(NULL,aLog.strComments,_T("错误"),MB_ICONWARNING);
        return FALSE;
    }



    /*********************************************************/
    /*  打开与手机通信通道——二进制协议                     */
    /*********************************************************/	
    ::GetPrivateProfileString(CFG_APPNAME_NETWORK,"MOBILE_IP_BIN",0,cAddr,MAX_PATH,strFilePath);
    wPort = ::GetPrivateProfileInt(CFG_APPNAME_NETWORK,"MOBILE_PORT_BIN",0,strFilePath);

    m_mobileComfieldMgrBin.InitProfile( TComMgrProfile::ECMP_SERVER,TSockAddr(cAddr,wPort),
        TMobileFrameBin::E_PRO_FLAG );

    if(m_mobileComfieldMgrBin.OpenCMG() == FALSE)
    {
        StopPubService();

        IMsgAppLogs aLog;
        aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
        aLog.strComments.Format(_T("服务启动失败！请在<选项>中检查配置参数。"));
        NbsSendModuleMsg(&aLog);

        ::MessageBox(NULL,aLog.strComments,_T("错误"),MB_ICONWARNING);
        return FALSE;
    }

    IMsgAppLogs aLog2;
    aLog2.strComments.Format(_T("交通气象发布服务已启动！"));
    SendModuleMsg(aLog2);

    return TRUE;

}

// 停止气象与交通发布服务
void  CSckModule::StopPubService()
{
    m_mobileComfieldMgrChar.Close();
    m_mobileComfieldMgrBin.Close();



    IMsgAppLogs aLog;
    aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
    aLog.strComments.Format(_T("交通与气象发布服务已关闭!"));
    NbsSendModuleMsg(&aLog);
}

//////////////////////////////////////////////////////////////////////////
// From CNBaseModule
BOOL CSckModule::OnInitModule()
{
    if (!CNBaseModule::OnInitModule())
    {
        return FALSE;
    }

    // 
    IMsgAppLogs aLog;
    aLog.strComments.Format(_T("正在初始化网络模块……"));
    SendModuleMsg(aLog);


    // 初始化SOCK环境
    WSADATA		WSAData = { 0 };
    if ( 0 != WSAStartup( WSA_VERSION, &WSAData ) )
    {
        // Tell the user that we could not find a usable
        // WinSock DLL.
        if ( LOBYTE( WSAData.wVersion ) != LOBYTE(WSA_VERSION) ||
            HIBYTE( WSAData.wVersion ) != HIBYTE(WSA_VERSION) )
            ::MessageBox(NULL, _T("Incorrect version of WS2_32.dll found"), _T("Error"), MB_OK);

        WSACleanup( );

        return FALSE;
    }

    //
    NciEnableTipInf(TRUE);

    // Initialize IoCompletion port environment.
    if ( 0 != NciStartup() )
    {
        TRACE0("Initialize IoCompletion port environment failure!\n");
        
        NciCleanup();

        return FALSE;
    }

    // 
    return TRUE;
}

BOOL CSckModule::OnStart()
{
    if (!CNBaseModule::OnStart())
    {
        return FALSE;
    }

    if (!ConnectToBalServer())
    {
        //return FALSE;
    }
    
    /*if (!ConnectToSP())
    {
        return FALSE;
    }*/
    

    return TRUE;
}

BOOL CSckModule::OnActive()
{
    if (!CNBaseModule::OnActive())
    {
        return FALSE;
    }

    return TRUE;
}

CCommFieldMgr*  CSckModule::GetFieldMgr(int aProtocolType)
{
    switch(aProtocolType)
    {
        // 与负载均衡服务器的通信协议
    case TBusinessFrm::E_PRO_FLAG:
        return &m_toBalanceServer;
        break;

        // 与手机终端的通信协议(二进制)
    case TMobileFrameBin::E_PRO_FLAG:
        return &m_mobileComfieldMgrBin;
        break;

        // 与手机终端的通信协议(字符串)
    case TMobileFrame_Char::E_PRO_FLAG:
        return &m_mobileComfieldMgrChar;
        break;

        // 与服务提供商（SP）的通信协议
    case TSpFrame::E_PRO_FLAG:
        return &m_SpComfieldMgr;
        break;

    default:
        return NULL;
        break;
    }
}

//
// On receive message from other modules.
void CSckModule::OnRecvIMCMessage(PTImcMsg aImcMsg)
{
    WORD msgType = aImcMsg->GetMsgType();
    switch(msgType)
    {
    case EMSG_CNNT_BALANCESERVER:
        {
            ConnectToBalServer();
        }
        break;

    case EMSG_TEST_BALANCESERVER:
        {
            if (m_toBalanceServer.GetServerNum()>0)
            {
                aImcMsg->m_wParam = 1;
            }
            else
            {
                aImcMsg->m_wParam = 0;
            }
        }
        break;

    case EMSG_START_SERVICE:
        {
            aImcMsg->m_wParam = (WPARAM)StartPubServcie();
        }
        break;

    case EMSG_STOP_SERVICE:
        {
            StopPubService();
        }
        break;

    case ESCK_SCK_STATE:
        {
            PIGetSckState pSckState = (PIGetSckState)aImcMsg;
            pSckState->m_dwNumClient = m_mobileComfieldMgrBin.GetClientNum(FALSE)+
                m_mobileComfieldMgrChar.GetClientNum(FALSE);
        }
        break;

    case ESCK_CLEAN_UP:
        {
            m_mobileComfieldMgrChar.CleanUp();
            m_mobileComfieldMgrBin.CleanUp();
        }
        break;

    case ESCK_RETRIEVE_COMLOGS:
        {
            PIMsgRetrivComfldAttri pMsgLog = (PIMsgRetrivComfldAttri)aImcMsg;
            CCommFieldMgr* pMgr = GetFieldMgr(pMsgLog->iProtocolType);
            if (pMgr!=NULL)
            {
                CCommField* pComm = pMgr->GetCommField(pMsgLog->dwComfieldID);
                if (pComm!=NULL)
                {
                    pMsgLog->pFieldAttri = pComm->GetAttri();
                }
            }
        }
        break;

    case ESCK_SEND_FRAME:
        {
            PIMsgFrmSending pSckFrame = PIMsgFrmSending(aImcMsg);
            PTBaseProtocol pFrame = (PTBaseProtocol)(pSckFrame->m_pFrameBuf);

            //
            if (pFrame->GetProType()==TMobileFrame_Char::E_PRO_FLAG)
            {
                // 其它处理（产生日志等）
                CCommField* pComField = m_mobileComfieldMgrChar.GetCommField(pSckFrame->m_comFiledID);
                if (pComField!=NULL)
                {
                    OnSendMobileFrame_char(pComField,(PTMobileFrame_Char)pFrame);
                }

                // 发送数据
                m_mobileComfieldMgrChar.SendFrame(pSckFrame->m_comFiledID,pFrame);

            }
            else if (pFrame->GetProType()==TMobileFrameBin::E_PRO_FLAG)
            {
                // 
                CCommField* pComField = m_mobileComfieldMgrBin.GetCommField(pSckFrame->m_comFiledID);
                if (pComField!=NULL)
                {
                    OnSendMobileFrame_bin(pComField,(PTMobileFrameBin)pFrame);
                }

                // 发送数据
                m_mobileComfieldMgrBin.SendFrame(pSckFrame->m_comFiledID,pFrame);

            }
            else if (pFrame->GetProType()==TSpFrame::E_PRO_FLAG)
            {
            }
        }
        break;
    }

    //
    CNBaseModule::OnRecvIMCMessage(aImcMsg);
}

//
// On receive message from internal objects.
BOOL CSckModule::OnRecvInterMessage(PTImcMsg aImcMsg)
{
    NB_MSGID msgType = aImcMsg->GetMsgType();

    switch(msgType)
    {
    case ESYS_NEW_LOG:
        {
            if(((PIMsgAppLogs)aImcMsg)->iLogType==IMsgNetLog::ELGT_Network)
            {
                PIMsgNetLog pLog = PIMsgNetLog(aImcMsg);

                CCommFieldMgr* pMgr = GetFieldMgr(pLog->iProtocolType);
                ASSERT(pMgr!=NULL);

                CCommField* pComFiled = pMgr->GetCommField(pLog->dwComfieldID);
                if (pComFiled!=NULL)
                {
                    pComFiled->AddNetLog(*pLog);
                }
                return TRUE;
            }
        }
        break;
    }

    // 
    return CNBaseModule::OnRecvInterMessage(aImcMsg);
}
void CSckModule::OnClose()
{
    NciCleanup();

    Close();

    //
    CNBaseModule::OnClose();
}
void CSckModule::Close()
{
    IMsgAppLogs aLog;
    aLog.strComments.Format(_T("正在终止服务……"));
    NbsSendModuleMsg(&aLog);

    // 
    StopPubService();

#if 0
    m_SpComfieldMgr.Close();
    m_toBalanceServer.Close();
#endif

}
//////////////////////////////////////////////////////////////////////////
// From ComfieldObserver
// SckMoudle与ComFieldMgr间的接口
void CSckModule::OnCfdMgrRecvFrame(TBaseProtocol* pProtocolFrame,CCommField* pComField,CCommFieldMgr* pCfdMgr)
{

    if (pProtocolFrame->GetProType()==TMobileFrame_Char::E_PRO_FLAG)
    {
        PTMobileFrame_Char pFrame = (PTMobileFrame_Char)pProtocolFrame;
        OnRecvMobileFrm_char(pFrame,pComField);
    }
    if (pProtocolFrame->GetProType()==TMobileFrameBin::E_PRO_FLAG)
    {
        PTMobileFrameBin pFrame = (PTMobileFrameBin)pProtocolFrame;
        OnRecvMobileFrm_bin(pFrame,pComField);
    }
    else if (pProtocolFrame->GetProType()==TSpFrame::E_PRO_FLAG)
    {
        PTSpFrame pFrame = (PTSpFrame)pProtocolFrame;
        //AfxMessageBox(pFrame->strRawData);
    }


    /************************************************************************/
    /* Send the message to other modules(UI).                               */
    /************************************************************************/
    IMsgFrmRecved msg;
    msg.m_pFrameBuf = pProtocolFrame;
    msg.m_comFiledID = pComField->GetFieldID();
    SendModuleMsg(msg);
}



//////////////////////////////////////////////////////////////////////////
// public function


//////////////////////////////////////////////////////////////////////////
// Private functions
void CSckModule::OnRecvMobileFrm_bin(PTMobileFrameBin pFrameBin,CCommField* pComField)
{
    WORD wCmdID = pFrameBin->wCmdID;
    DWORD dwComfildID = pComField->GetFieldID();

    switch(wCmdID)
    {
        // log-on request
    case TLoginReqBin::ECommandID:
        {
            PTLoginReqBin req = (PTLoginReqBin)pFrameBin;

            // create a new log.                       
            IMsgNetLog aLog(IMsgNetLog::ENLT_RECEIVEFRAME,
                pFrameBin->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrBin.GetClientNum(FALSE);
            aLog.strComments.Format(_T("BIN: 收到登录信息。用户名：%s"),req->strUserName);
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);            
        }
        break;

        // 
    case TLoginRspBin::ECommandID:
        {
            PTLoginRspBin rsp = (PTLoginRspBin)pFrameBin;

            // create a new log.                       
            IMsgNetLog aLog(IMsgNetLog::ENLT_RECEIVEFRAME,
                pFrameBin->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrBin.GetClientNum(FALSE);
            aLog.strComments.Format(_T("BIN: 收到回复信息。结果码%d"),rsp->byLoginRst);
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);     
        }
        break;

        // exit request
    case TClientExitBin::ECommandID:
        {
            // 1. create a new log.                      
            IMsgNetLog aLog(IMsgNetLog::ENLT_RECEIVEFRAME,
                pFrameBin->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrBin.GetClientNum(FALSE);
            aLog.strComments.Format(_T("BIN: 收到退出指令"));
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);

            // 2. shut down the filed.
            m_mobileComfieldMgrBin.InvalidateCommFiled(pComField);
        }
        break;

        // register request.
    case TRegRequestBin::ECommandID:
        {
            PTRegRequestBin regReq = PTRegRequestBin(pFrameBin);

            // 1. create a new log.                               
            IMsgNetLog aLog(IMsgNetLog::ENLT_RECEIVEFRAME,
                pFrameBin->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrBin.GetClientNum(FALSE);
            aLog.strComments.Format(_T("BIN: 注册请求。"));           
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
        break;

        // request district weather information
    case TWthReqByPosBin::ECommandID:
        {
            PTWthReqByPos_bin weatherReq = PTWthReqByPos_bin(pFrameBin);

            // 1. create a new log.                          
            IMsgNetLog aLog(IMsgNetLog::ENLT_RECEIVEFRAME,
                pFrameBin->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrBin.GetClientNum(FALSE);
            aLog.strComments.Format(_T("BIN: 请求小区天气预报。经度＝%ld，纬度＝%ld"),
                weatherReq->dwLongitude,weatherReq->dwLatitude);           
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
        break;


        // weather information response
    case TWthRspBin::ECommandID:
        {
            PTWthRspBin pWthRsp = PTWthRspBin(pFrameBin);

            // 1. create a new log.                      
            IMsgNetLog aLog(IMsgNetLog::ENLT_RECEIVEFRAME,
                pFrameBin->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrBin.GetClientNum(FALSE);
            if (pWthRsp->bySerciveCode==TWthRspBin::ESuccess)
            {
                aLog.strComments = pWthRsp->strWthDes;
            }
            else
            {
                aLog.strComments.Format(_T("没有找到可用的气象信息"));
            }            
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
        break;

        // request traffic information by link's position.
    case TTfcReqByLinkPosBin::ECommandID:
        {
            PTTfcReqByPos_char request = PTTfcReqByPos_char(pFrameBin);

            // 1. create a new log.                     
            IMsgNetLog aLog(IMsgNetLog::ENLT_RECEIVEFRAME,
                pFrameBin->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrBin.GetClientNum(FALSE);
            aLog.strComments.Format(_T("BIN:交通信息请求（通过Link起止点坐标）。共%d条"),
                request->linkPosList.GetCount());
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
        break;

        // request traffic information by road name
    case TTfcReqByRoadNameBin::ECommandID:
        {
            PTTfcReqByRoadNameBin request = PTTfcReqByRoadNameBin(pFrameBin);

            // 1. create a new log.                  
            IMsgNetLog aLog(IMsgNetLog::ENLT_RECEIVEFRAME,
                pFrameBin->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrBin.GetClientNum(FALSE);
            aLog.strComments.Format(_T("BIN:交通信息请求（道路名称为%s）。"),
                request->strRoadName);
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
        break;

    case TTfcInfRsp1_Bin::ECommandID:
        {
            PTTfcInfRsp1_Bin pTfcRsp = PTTfcInfRsp1_Bin(pFrameBin);

            // 1. create a new log.                  
            IMsgNetLog aLog(IMsgNetLog::ENLT_RECEIVEFRAME,
                pFrameBin->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrBin.GetClientNum(FALSE);
            if (pTfcRsp->bySerciveCode==TTfcInfRsp1_Bin::ESuccess)
            {
                aLog.strComments.Format(_T("BIN:收到交通信息，Link个数＝%d"),
                    pTfcRsp->m_DtiList.GetCount());
            }
            else
            {
                aLog.strComments.Format(_T("BIN:服务回复：没有找到交通信息！ "));                 
            }
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
        break;

    case TTfcInfRsp2_Bin::ECommandID:
        {
            PTTfcInfRsp2_Bin pTfcRsp = PTTfcInfRsp2_Bin(pFrameBin);

            // 1. create a new log.                  
            IMsgNetLog aLog(IMsgNetLog::ENLT_RECEIVEFRAME,
                pFrameBin->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrBin.GetClientNum(FALSE);
            if (pTfcRsp->bySerciveCode==TTfcInfRsp2_Bin::ESuccess)
            {
                aLog.strComments.Format(_T("BIN:收到交通信息，路段个数＝%d"),
                    pTfcRsp->m_RoadTfcList.GetCount());
            }
            else
            {
                aLog.strComments.Format(_T("BIN:服务回复：没有找到交通信息！ "));                 
            }
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);

        }
        break;

    default:
        {
            // 
            IMsgNetLog aLog(IMsgNetLog::ENLT_RECEIVEFRAME,
                pFrameBin->GetProType(),dwComfildID,wCmdID);
            aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
            aLog.wNumClient = m_mobileComfieldMgrChar.GetClientNum(FALSE);
            aLog.strComments.Format(_T("[BIN]收到未知协议，Command ID＝%d\n"),wCmdID);
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
    }
}

void CSckModule::OnRecvMobileFrm_char(PTMobileFrame_Char pFrameChar,CCommField* pComField)
{    
    WORD wCmdID = pFrameChar->wCmdID;
    DWORD dwComfildID = pComField->GetFieldID();

    switch(wCmdID)
    {
        // 
    case TLoginReq_Char::ECommandID:
        {
            PTLoginReq_Char req = (PTLoginReq_Char)pFrameChar;

            /* 产生新的网络日志(收到数据)                          */
            IMsgNetLog aLog(IMsgNetLog::ENLT_RECEIVEFRAME,
                pFrameChar->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrChar.GetClientNum(FALSE);
            aLog.strComments.Format(_T("CHAR:收到登录信息。用户名：%s"),req->strUserName);
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);

            /*  验证用户合法性，并返回信息                      */
            TLoginRsp_Char loginRsp;
            if (1)
            {
                //验证通过
                pComField->SetUserInf(req->strUserName);
                pComField->Active();

                //设置执行结果码
                loginRsp.wLoginRst = 0;
            }
            else
            {
                //设置执行结果码
                loginRsp.wLoginRst = 0XEEEE;
            }
            pComField->SendFrame(&loginRsp);

            /* 产生新的网络日志(发送数据)                          */
            {
                IMsgNetLog aLog(IMsgNetLog::ENLT_SENDFRAME,
                    loginRsp.GetProType(),dwComfildID);

                aLog.dwFrameID = loginRsp.GetCommandID();
                aLog.wNumClient = m_mobileComfieldMgrChar.GetClientNum(FALSE);
                aLog.strComments.Format(_T("CHAR:发送登录回复信息"));
                pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
                SendModuleMsg(aLog);
            }
        }
        break;

        //退出指令
    case TClientExit_Char::ECommandID:
        {            
            // 1. 产生新的网络日志(收到数据)                                  
            IMsgNetLog aLog(IMsgNetLog::ENLT_RECEIVEFRAME,
                pFrameChar->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrChar.GetClientNum(FALSE);
            aLog.strComments.Format(_T("CHAR:收到退出指令"));
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);

            // 2. 删除与此客户的TCP连接
            m_mobileComfieldMgrChar.InvalidateCommFiled(pComField);
        }
        break;

        // 请求天气信息指令
    case TWeatherReq_Char::ECommandID:
        {
            PTWeatherReq_Char weatherReq = PTWeatherReq_Char(pFrameChar);

            /* 1. 产生新的网络日志(收到数据)                       */
            IMsgNetLog aLog(IMsgNetLog::ENLT_RECEIVEFRAME,
                pFrameChar->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrChar.GetClientNum(FALSE);
            if (weatherReq->byType==TWeatherReq_Char::ERT_POSITION)
            {
                aLog.strComments.Format(_T("CHAR:气象信息请求。经度＝%ld，纬度＝%ld"),
                    weatherReq->dwLongitude,weatherReq->dwLatitude);
            }
            else
            {
                aLog.strComments.Format(_T("CHAR:错误的天气预报请求！"));
            }
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
        break;


        // 天气信息回复1
    case TWeatherRsp1_char::ECommandID:
        {
            PTWeatherRsp1_char pWthRsp = PTWeatherRsp1_char(pFrameChar);

            // 1. create a new log.                      
            IMsgNetLog aLog(IMsgNetLog::ENLT_RECEIVEFRAME,
                pFrameChar->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrBin.GetClientNum(FALSE);
            if (pWthRsp->byExcuteRst==TWeatherRsp1_char::EExeSuccess)
            {
                pWthRsp->weatherInf.GetWetherDescription(aLog.strComments);
            }
            else
            {
                aLog.strComments.Format(_T("服务器回复：没有找到相应坐标的气象信息！"));           
            }
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
        break;

        // 气象信息回复2 
    case TWeatherRsp2_char::ECommandID:
        {
            PTWeatherRsp2_char pWthRsp = PTWeatherRsp2_char(pFrameChar);

            // 1. create a new log.                      
            IMsgNetLog aLog(IMsgNetLog::ENLT_RECEIVEFRAME,
                pFrameChar->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrBin.GetClientNum(FALSE);
            if (pWthRsp->byExcuteRst==TWeatherRsp2_char::EExeSuccess)
            {
                aLog.strComments = pWthRsp->strCityName+pWthRsp->strWthDes;
            }
            else
            {
                aLog.strComments.Format(_T("服务器回复：没有找到'%s'的气象信息！"),pWthRsp->strCityName);
            }
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
        break;

        // 通过Link起止点请求路况信息
    case TTfcReqByPos_char::ECommandID:
        {
            PTTfcReqByPos_char request = PTTfcReqByPos_char(pFrameChar);

            /* 1. 产生新的网络日志(收到数据)                       */            
            IMsgNetLog aLog(IMsgNetLog::ENLT_RECEIVEFRAME,
                pFrameChar->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrChar.GetClientNum(FALSE);
            aLog.strComments.Format(_T("CHAR:交通信息请求（通过Link起止点坐标）。共%d条"),
                request->linkPosList.GetCount());
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
        break;

        // 通过道路名称请求实时路况信息指令
    case TTfcReqByRoadName_Char::ECommandID:
        {
            PTTfcReqByRoadName_Char request = PTTfcReqByRoadName_Char(pFrameChar);

            /* 1. 产生新的网络日志(收到数据)                       */
            IMsgNetLog aLog(IMsgNetLog::ENLT_RECEIVEFRAME,
                pFrameChar->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrChar.GetClientNum(FALSE);
            aLog.strComments.Format(_T("CHAR:交通信息请求（道路名称为%s）。"),
                request->strRoadName);
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
        break;

    default:
        {
            // 
            IMsgNetLog aLog(IMsgNetLog::ENLT_RECEIVEFRAME,
                pFrameChar->GetProType(),dwComfildID,wCmdID);
            aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
            aLog.wNumClient = m_mobileComfieldMgrChar.GetClientNum(FALSE);
            aLog.strComments.Format(_T("[CHAR]收到未知协议，Command ID＝%d\n"),wCmdID);
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
    }
}
void CSckModule::OnSendMobileFrame_char(CCommField* pComField,TMobileFrame_Char* pFrameSendingChar)
{

    ASSERT(pComField!=NULL);
    ASSERT(pFrameSendingChar!=NULL);

    WORD wCmdID = pFrameSendingChar->wCmdID;
    DWORD dwComfildID = pComField->GetFieldID();

    switch(wCmdID)
    {
        // 气象信息请求
    case TWeatherReq_Char::ECommandID:
        {
            PTWeatherReq_Char pReq = (PTWeatherReq_Char)pFrameSendingChar;
            IMsgNetLog aLog(IMsgNetLog::ENLT_SENDFRAME,
                pFrameSendingChar->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrChar.GetClientNum(FALSE);
            aLog.strComments.Format(_T("CHAR:发送气象信息请求。经度：%ld，纬度：%ld。"),
                pReq->dwLongitude,pReq->dwLatitude);
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
        break;

        // 气象信息回复1
    case TWeatherRsp1_char::ECommandID:
        {
            PTWeatherRsp1_char pRsp = (PTWeatherRsp1_char)pFrameSendingChar; 

            /*******************************************************/
            /* 产生新的网络日志(发送数据)                          */
            /*******************************************************/
            IMsgNetLog aLog(IMsgNetLog::ENLT_SENDFRAME,
                pFrameSendingChar->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrChar.GetClientNum(FALSE);
            if (pRsp->byExcuteRst==TWeatherRsp1_char::EExeFailure)
            {
                aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
                aLog.strComments.Format(_T("CHAR:没有找到坐标为x=%ld,y=%ld的天气信息"),
                    pRsp->dwLongitude,pRsp->dwLatitude);
            }
            else
            {
                aLog.strComments.Format(_T("CHAR:发送天气信息,区域%s"),
                    pRsp->weatherInf.strDistName);
            }
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
    	break;

        // 气象信息回复2
    case TWeatherRsp2_char::ECommandID:
        {
            PTWeatherRsp2_char pRsp = (PTWeatherRsp2_char)pFrameSendingChar;

            /*******************************************************/
            /* 产生新的网络日志(发送数据)                          */
            /*******************************************************/
            IMsgNetLog aLog(IMsgNetLog::ENLT_SENDFRAME,
                pFrameSendingChar->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrChar.GetClientNum(FALSE);
            if (pRsp->byExcuteRst==TWeatherRsp2_char::EExeFailure)
            {
                aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
                aLog.strComments.Format(_T("CHAR:没有找到'%s'的天气信息"),pRsp->strCityName);
            }
            else
            {
                aLog.strComments.Format(_T("CHAR:%s，%s"),pRsp->strCityName,pRsp->strWthDes);
            }
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
        break;

        // 路况信息回复1
    case TTfcRsp1_Char::ECommandID:
        {
            PTTfcRsp1_Char pRsp = (PTTfcRsp1_Char)pFrameSendingChar;

            /*******************************************************/
            /* 产生新的网络日志(发送数据)                          */
            /*******************************************************/
            IMsgNetLog aLog(IMsgNetLog::ENLT_SENDFRAME,
                pFrameSendingChar->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrChar.GetClientNum(FALSE);
            if (pRsp->byExcuteRst==TTfcRsp1_Char::EFailure)
            {
                aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
                aLog.strComments.Format(_T("CHAR:没有找到路况信息!"));
            }
            else
            {
                aLog.strComments.Format(_T("CHAR:发送路况信息，共%d条"),pRsp->DtiList.GetCount());
            }
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
        break;

        // 路况信息回复2
    case TTfcRsp2_Char::ECommandID:
        {
            PTTfcRsp2_Char pRsp = (PTTfcRsp2_Char)pFrameSendingChar;

            /*******************************************************/
            /* 产生新的网络日志(发送数据)                          */
            /*******************************************************/
            IMsgNetLog aLog(IMsgNetLog::ENLT_SENDFRAME,
                pFrameSendingChar->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrChar.GetClientNum(FALSE);
            if (pRsp->m_byResult==TTfcRsp1_Char::EFailure)
            {
                aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
                aLog.strComments.Format(_T("CHAR:没有找到路况信息!"));
            }
            else
            {
                aLog.strComments.Format(_T("CHAR:发送路况信息，共%d条"),pRsp->m_RoadTfcList.GetCount());
            }
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
        break;

    default:
        {
            // 
            IMsgNetLog aLog(IMsgNetLog::ENLT_RECEIVEFRAME,
                pFrameSendingChar->GetProType(),dwComfildID,wCmdID);
            aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
            aLog.wNumClient = m_mobileComfieldMgrChar.GetClientNum(FALSE);
            aLog.strComments.Format(_T("[CHAR]发送未知协议，Command ID＝0x%x\n"),wCmdID);
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
    }

}

void CSckModule::OnSendMobileFrame_bin(CCommField* pComField,TMobileFrameBin* pFrameSendingBin)
{
    WORD wCmdID = pFrameSendingBin->wCmdID;
    DWORD dwComfildID = pComField->GetFieldID();

    switch(wCmdID)
    {
    case TLoginRspBin::ECommandID:
        {
            PTLoginRspBin pLogRsp = (PTLoginRspBin)pFrameSendingBin;

            //验证通过
            pComField->SetUserInf(pLogRsp->strUserName);
            pComField->Active();

            /*******************************************************/
            /* 产生新的网络日志(发送数据)                          */
            /*******************************************************/
            IMsgNetLog aLog(IMsgNetLog::ENLT_SENDFRAME,
                pFrameSendingBin->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrChar.GetClientNum(FALSE);
            aLog.strComments.Format(_T("[BIN]发送登录回复信息，结果码(%d)"),pLogRsp->byLoginRst);
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
        break;

        // 通过位置请求气象信息
    case TWthReqByPosBin::ECommandID:
        {
            PTWthReqByPos_bin pWthReq = (PTWthReqByPos_bin)pFrameSendingBin;

            // Create a new log.
            IMsgNetLog aLog(IMsgNetLog::ENLT_SENDFRAME,
                pFrameSendingBin->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrChar.GetClientNum(FALSE);
            aLog.strComments.Format(_T("[BIN]发送气象信息请求，经度：%ld，纬度：%ld。"),
                pWthReq->dwLongitude,pWthReq->dwLatitude );
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);

        }
        break;


        // 气象回复
    case TWthRspBin::ECommandID:
        {
            PTWthRspBin pRsp = (PTWthRspBin)pFrameSendingBin;

            /*******************************************************/
            /* 产生新的网络日志(发送数据)                          */
            /*******************************************************/
            IMsgNetLog aLog(IMsgNetLog::ENLT_SENDFRAME,
                pFrameSendingBin->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrChar.GetClientNum(FALSE);
            if (pRsp->bySerciveCode!=TMobileFrameBin::ESuccess)
            {
                aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
                aLog.strComments.Format(_T("[BIN]没有找到对应的天气预报信息"));
            }
            else
            {
                CString strWthinf;
                pRsp->weatherInf.GetWetherDescription(strWthinf);
                aLog.strComments.Format(_T("[BIN]发送天气信息：%s"),
                    strWthinf);
            }
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
        break;


        // 交通信息回复1
    case TTfcInfRsp1_Bin::ECommandID:
        {
            PTTfcInfRsp1_Bin pRsp = (PTTfcInfRsp1_Bin)pFrameSendingBin;

            /*******************************************************/
            /* 产生新的网络日志(发送数据)                          */
            /*******************************************************/
            IMsgNetLog aLog(IMsgNetLog::ENLT_SENDFRAME,
                pFrameSendingBin->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrChar.GetClientNum(FALSE);
            if (pRsp->bySerciveCode!=TMobileFrameBin::ESuccess)
            {
                aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
                aLog.strComments.Format(_T("[BIN]没有找到路况信息!"));
            }
            else
            {
                aLog.strComments.Format(_T("[BIN]发送路况信息，共%d条"),pRsp->m_DtiList.GetCount());
            }
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
        break;

        // 交通信息回复2
    case TTfcInfRsp2_Bin::ECommandID:
        {
            PTTfcInfRsp2_Bin pRsp = (PTTfcInfRsp2_Bin)pFrameSendingBin;

            /*******************************************************/
            /* 产生新的网络日志(发送数据)                          */
            /*******************************************************/
            IMsgNetLog aLog(IMsgNetLog::ENLT_SENDFRAME,
                pFrameSendingBin->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrChar.GetClientNum(FALSE);
            if (pRsp->bySerciveCode!=TMobileFrameBin::ESuccess)
            {
                aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
                aLog.strComments.Format(_T("[BIN]没有找到路况信息!"));
            }
            else
            {
                aLog.strComments.Format(_T("[BIN]发送路况信息，共%d条"),pRsp->m_RoadTfcList.GetCount());
            }
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
        break;

    default:
        {
            IMsgNetLog aLog(IMsgNetLog::ENLT_SENDFRAME,
                pFrameSendingBin->GetProType(),dwComfildID,wCmdID);
            aLog.wNumClient = m_mobileComfieldMgrChar.GetClientNum(FALSE);
            aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
            aLog.strComments.Format(_T("[BIN]发送未知协议，CommandID＝0x%x"),wCmdID);
            pComField->GetClientAddr(aLog.byClientIP,aLog.uClientPort);
            SendModuleMsg(aLog);
        }
    }
}
