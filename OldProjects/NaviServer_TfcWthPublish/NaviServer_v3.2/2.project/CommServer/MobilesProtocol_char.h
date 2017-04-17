
/*
* ============================================================================
*  Name     : protocol definition
*  Part of  : NaviInt
*  Created  : 19.11.2006 by ZhangHeng
*  Description:
*     
*  Version  :
*  Copyright: Copyright (c) 2007, China SpaceSat. Cor. Ltd.
* ============================================================================
*/
#pragma once

//#include <Afxdisp.h>
#include <Afxtempl.h>
#include <BaseProtocol.h>
#include "InterfaceEx.h"


//////////////////////////////////////////////////////////////////////////
/*
    与手机终端通信时的协议
*/


/************************************************************************/
/*                                                                      /*
                    < 与手机终端通信的数据帧结构 > 
/*                                                                      */
    struct AFX_EXT_CLASS _mobile_comm_frame_char : public TBaseProtocol
    {
        // 协议标识
        enum { E_PRO_FLAG = 1};
        //
        enum { EMaxLenFrame= 4000 };    // 接收缓冲的最大长度
        enum { EHeaderFrame= '@'};      // 帧起始标记
        enum { ELenCommand= 4 };        // 指令码长度

#ifdef _NEW_CHAR_PROTOCOL
        enum { EOffBlockSize= 8 };      // 协议体大小在协议包头中的偏移
#else
        enum { EOffBlockSize= 6 };      // 协议体大小在协议包头中的偏移
#endif
        enum { ESizeBlock= 4 };         // 协议体大小在协议包头中所占字节数

#ifdef _NEW_CHAR_PROTOCOL
        enum { ESizeOfHeader= 28 };     // 协议包头大小
#else
        enum { ESizeOfHeader= 26 };     // 协议包头大小
#endif

        
        // Members
#ifdef _NEW_CHAR_PROTOCOL
        char        cVersion[2];        // 协议版本号
#endif        
        char        cHeader[2];         // 协议包头标记（@@）
        WORD        wCmdID;             // 指令码
        WORD        wBlockSize;         // 协议体大小

#ifdef  _NEW_CHAR_PROTOCOL
        enum { ELenOfCellphoneNo= 14 }; // 手机号码在通信帧中占位长度
#else
        enum { ELenOfCellphoneNo= 16 }; // 手机号码在通信帧中占位长度
#endif
        CString     strMobileNo;        // 手机号码

#ifdef _NEW_CHAR_PROTOCOL
        enum { ELenOfFeeType= 2 };      // 计费类型长度
        enum TFeeType // 
        {
            EFT_PayMonthly=1,       // 包月计费
            EFT_1Dime1Time=2,       // 点播，每次1角
            EFT_2Dime1Time=3,       // 点播，每次2角
        };  
        BYTE        byFeeType;          // 计费类型
#endif    

        // Constructor && Destructor
        _mobile_comm_frame_char();
        virtual ~_mobile_comm_frame_char();

        // From _base_protocol
        int GetProType();
        CString GetProName(); 

        // New virtual functions
        virtual void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        virtual BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
        virtual WORD GetCommandID() const;
        virtual void CalculateBlockSize(); // 部分子类(发送帧)需要继承此方法

        // New functions
        void SetMobileNo(__int64 llMobileNo); // 设置手机号码

        // Static functions
        static _mobile_comm_frame_char* GetInstance(WORD wCommandID); // 根据命令ID返回相应的命令对象

    };
    typedef _mobile_comm_frame_char TMobileFrame_Char,*PTMobileFrame_Char;


//3. 协议体结构
/////////////////////////////////////////////////////////////////////////////////
// REG1. 用户注册请求
    struct _register_request_char : public TMobileFrame_Char
    {
        enum { ECommandID = 0x0013 }; // CommandID

        // Members
        CString     strUserName;        // 用户名
        CString     strUserPwd;         // 用户密码
        CString     strPhoneSimNo;      // 手机SIM卡号
        CString     strSoftwareSerNo;   // 软件序列号
        CString     strPhoneSerNo;      // 手机序列号

        // Constructor
        _register_request_char();

        // From _mobile_comm_frame
        //void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
        WORD GetCommandID() const;
    };
    typedef _register_request_char TRegRequest_Char, *PTRegRequest_Char;

/////////////////////////////////////////////////////////////////////////////////
// REG2. 用户注册回复
    struct _register_response : public TMobileFrame_Char
    {
        enum { ECommandID= 0x0014 }; // Command ID

        // 注册回复码
        enum ERegRspCode
        {
            ERR_REG_SUCESS = 0,     // 注册成功
            ERR_USER_ALREAD_EXITS=1,// 用户名已存在
            ERR_INVALID_USERNAME=2, // 用户名含有非法字符
            ERR_ALREADY_REGISTER=3, // 此软件已注册 
            ERR_OTHERS_REASONS=10,  // 其它错误
        };

        // Members
        enum { ELenRegRspCode=2 }; // 回复码的长度
        WORD    wRegRspCode;       // 注册回复码

        // Constructor
        _register_response();

        // From TMobileFrame
        void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        //virtual BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
        WORD GetCommandID() const;
        void CalculateBlockSize();
    };
    typedef _register_response TRegisterRsp,*PTRegisterRsp;

/////////////////////////////////////////////////////////////////////////////////
// L1. 登录指令
    struct AFX_EXT_CLASS _login_request_char : public TMobileFrame_Char
    {
        enum { ECommandID = 0x0011 }; // CommandID

        // Members
        CString strUserName;     // 用户名
        CString strUserPwd;      // 用户密码

        // Constructor
        _login_request_char();

        // From TMobileFrameChar
        virtual void CalculateBlockSize();
        virtual void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        virtual BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
        virtual WORD GetCommandID() const;

    };
    typedef _login_request_char TLoginReq_Char,*PTLoginReq_Char;


/////////////////////////////////////////////////////////////////////////////////
// L2. 登录结果回复指令
    struct _login_response_char : public TMobileFrame_Char
    {
        enum { ECommandID= 0x0012 }; // 

        // Members
        WORD    wLoginRst;      //登录结果码

        // Constructor
        _login_response_char();

        // From TMobileFrame
        virtual void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        //virtual BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
        virtual WORD GetCommandID() const;
        virtual void CalculateBlockSize();
    };
    typedef _login_response_char TLoginRsp_Char,*PTLoginRsp_Char;


/////////////////////////////////////////////////////////////////////////////////
// TT. 检测在线指令(已作废)
    struct  _online_test : public TMobileFrame_Char
    {
        enum { ECommandID=0 };        // 

        // Constructor
        _online_test();

        // From TMobileFrame
        virtual WORD GetCommandID() const;

    };
    typedef _online_test TOnlineTest,*PTOnlineTest;



/////////////////////////////////////////////////////////////////////////////////
// 3.5 退出指令
    struct AFX_EXT_CLASS _client_exit_char : public TMobileFrame_Char 
    {
        enum { ECommandID=0x0015 };          // 

        //Constructor
        _client_exit_char();

        // From _mobile_comm_frame
        virtual WORD GetCommandID() const;
        virtual void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        virtual BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _client_exit_char TClientExit_Char,*PTClientExit_Char;


/////////////////////////////////////////////////////////////////////////////////
//###############################################################################
// WTH1. 气象信息请求
    struct AFX_EXT_CLASS _weather_request_ : public TMobileFrame_Char
    {
        enum { ECommandID=0x0027 };     // 
        
        // 请求类型
        enum TReqType
        {
            ERT_POSITION= '3',    // 通过经纬度请求
            ERT_CITYNAME = '4',   // 通过城市名称请求[×已作废×]
        };

        // 时段指示码
        enum TPeriodCode
        {
            EPer_TodayDaytime = 0x01,           // 今天白天预报
            EPer_Tonight = 0x02,                // 今天夜间预报
            EPer_TomorrowDayTime = 0x03,        // 明天白天预报
            EPer_Tom_evening = 0x0D,            // 明天夜间预报
            EPer_Fr6To9 = 0x04,	                // 未来6-9点预报
            EPer_Afternoon = 0x05,	            // 今天下午预报
            EPer_Fr9To12 = 0x06,	            // 未来9-12点预报
            EPer_Fr11To14 = 0x07,	            // 未来11-14点预报
            EPer_Fr14To17 = 0x08,	            // 未来14-17点预报
            EPer_Fr17To20 = 0x09,	            // 未来17-20点预报
            EPer_Fr20To23 = 0x0A,	            // 未来20-23点预报
        };

        // Members
        BYTE    byType;         // 请求类型,参见TReqType 
        DWORD   dwLongitude;    // longitude (unit: 1/24s)
        DWORD   dwLatitude;     // 
        BYTE    byPeriod;       // 时段指示码

        // Constructor
        _weather_request_();

        // From _mobile_comm_frame
        virtual WORD GetCommandID() const;
        virtual void CalculateBlockSize();
        virtual void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        virtual BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _weather_request_ TWeatherReq_Char, *PTWeatherReq_Char;


// WTH2. 天气信息返回1
    struct AFX_EXT_CLASS _weather_response1 : public TMobileFrame_Char
    {
        enum { ECommandID= 0x0025 };    //

        // 指令执行结果
        enum TExcuteFlag
		{
			EExeFailure='0',
            EExeSuccess='1',
        };

        // 类型标识
        enum TTypeFlag
        {
            ETF_LIVE_POS=1,       // 通过经纬度请求实况气象信息(*已作废*)
            ETF_LIVE_REG,         // 通过区域码请求实况气象信息 (*已作废*)
            ETF_PRE_REG,          // 通过区域码请求预报气象信息 (*已作废*)
            ETF_PRE_NAME,         // 通过POI名称请求预报气象信息 (*已作废*)
            ETF_PRE_POS= '5',     // 通过经纬度请求预报气象信息
        };

        // Members
        BYTE        byExcuteRst;        // 指令执行结果
        BYTE        byFlag;             // 类型标识

        DWORD       dwLongitude;        // 经度(单位：1/24秒)
        DWORD       dwLatitude;         // 纬度(单位：1/24秒)

        TWeatherInf     weatherInf;	        // 天气信息


        // Constructor
        _weather_response1();

        // From _mobile_comm_frame
        WORD GetCommandID() const;
        void CalculateBlockSize();
        void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _weather_response1 TWeatherRsp1_char,*PTWeatherRsp1_char;

// WTH3.气象信息回复2
    struct AFX_EXT_CLASS _weather_response2  : public TMobileFrame_Char
    {
        enum { ECommandID=0x0028 }; // 

        // 指令执行结果
        enum TExcuteFlag
        {
            EExeSuccess = '0',
            EExeFailure = '1',
        };

        // Frame members
        BYTE        byExcuteRst;        // 指令执行结果
        BYTE        byPeriod;	        // 时段
        CString     strWthDes;	        // 天气描述

        // other members
        CString     strCityName;

        // Constructor
        _weather_response2();

        // New functions

        // From _mobile_comm_frame
        virtual WORD GetCommandID() const;
        virtual void CalculateBlockSize();
        virtual void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        virtual BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _weather_response2 TWeatherRsp2_char, *PTWeatherRsp2_char;
    

/////////////////////////////////////////////////////////////////////////////////
//###############################################################################
// TFC1. 通过Link起止点及名称请求路况信息
    struct _traffic_req_by_linkPosition_char : public TMobileFrame_Char 
    {
        enum { ECommandID=0x0040 }; // 

        // Member
        CLinkList    linkPosList;

        // Constructor
        _traffic_req_by_linkPosition_char();
        ~_traffic_req_by_linkPosition_char();

        // From _mobile_comm_frame
        virtual WORD GetCommandID() const;
        //virtual void CalculateBlockSize();
        //virtual void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        virtual BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _traffic_req_by_linkPosition_char TTfcReqByPos_char,*PTTfcReqByPos_char;

/////////////////////////////////////////////////////////////////////////////////
// TFC2. 通过道路名称请求实时路况信息
    struct _traffic_req_by_roadname_char : public TMobileFrame_Char
    {
        enum { ECommandID=0x0041 };    // 

        // Members
        CString     strRoadName;
        DWORD       dwLongitude;   // longitude of link (unit: 1/24s)
        DWORD       dwLatitude;    // 
        
        // Constructor
        _traffic_req_by_roadname_char();

        // From _mobile_comm_frame
        virtual WORD GetCommandID() const;
        //virtual void CalculateBlockSize();
        //virtual void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        virtual BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _traffic_req_by_roadname_char TTfcReqByRoadName_Char,*PTTfcReqByRoadName_Char;



/////////////////////////////////////////////////////////////////////////////////
// TFC4. 实时路况信息返回指令
    

    // 路况信息回复_1

    struct AFX_EXT_CLASS _traffic_response_1_char : public TMobileFrame_Char
    {
        enum { ECommandID=0x0045 }; // Command ID

        enum ESuccssFlag
        {
            ESucess =  0,
            EFailure = 1,
        };

        enum {EMaxDTI=50};

        BYTE        byExcuteRst;     // 指令执行结果标志
        CLinkList   DtiList;         // 路况信息链表

        //Constructor && Destructor
        _traffic_response_1_char();
        ~_traffic_response_1_char(); 
        
        // From _mobile_comm_frame
        virtual WORD GetCommandID() const;
        virtual void CalculateBlockSize();
        virtual void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        //virtual BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _traffic_response_1_char TTfcRsp1_Char,*PTTfcRsp1_Char;


    // 路况信息回复_2

    struct AFX_EXT_CLASS _traffic_response_2_char : public TMobileFrame_Char
    {
        enum { ECommandID=0x0046 }; // Command ID

        enum
        {
            ESucess = 0,
            EFailure = 1,
        };

        enum { EMaxNum=200 };

        // Members
        BYTE                m_byResult;
        CRoadTfcInfList     m_RoadTfcList;

        // Constructor && Destructor
        _traffic_response_2_char();
        ~_traffic_response_2_char(); 

        // New functions
        void    ClearList();

        // From _mobile_comm_frame
        virtual WORD GetCommandID() const;
        virtual void CalculateBlockSize();
        virtual void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        //virtual BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);

    };
    typedef _traffic_response_2_char TTfcRsp2_Char,*PTTfcRsp2_Char;

/////////////////////////////////////////////////////////////////////////////////
