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

#ifndef _PROTOCOLFRAME_H_A7T8E34Y2_
#define _PROTOCOLFRAME_H_A7T8E34Y2_
//////////////////////////////////////////////////////////////////////////
#include <Afxtempl.h>
#include "InterfaceEx.h"
#include <BaseProtocol.h>
#include <Geometry.h>
//////////////////////////////////////////////////////////////////////////


/************************************************************************/
/*  数据帧定义 (字符集采用GBK编码)                                                        

/************************************************************************/
/*
	协议包头定义：所有协议的基类，子类继承规则
	1、实现GetCommandID函数返回相应协议帧的命令ID
	2、实现GetBuffer函数(如果需要打包的话)
	3、实现ParseBuffer函数(如果需要解包的话)
*/
/************************************************************************/
	struct AFX_EXT_CLASS _mobile_comm_frame_bin : public TBaseProtocol
	{
        // 协议标识
        enum { E_PRO_FLAG = 3};

        //
        enum { EMaxLenFrame= 5000 };    // 接收缓冲的最大长度
       
        enum { EEscapeChar = 0x10 };    // 转义字符
        enum { EStartFlag= 0x02};       // 帧起始标记
        enum { EEndFlag = 0x03 };       // 帧结束标记
        enum { ELenFrmHead= 2 };        // 帧头长度
        enum { ELenFrmTail= 2 };        // 帧尾长度

        enum { EVersion= 0x10};         // 协议版本号


        // Members
        BYTE        byVersion;          // 协议版本号
        WORD        wCmdID;             // 指令码
        BYTE        byContentType;      // 内容类型

        enum { ELenPhoenNo= 16 }; // 手机号码在通信帧中占位长度
        BYTE  byMobileNo[ELenPhoenNo];  // 手机号码

        enum TServiceCode
        {
            ESuccess = 0,           // 成功
            EServiceFailure = 1,    // 服务不成功
            EErr_unknow = 0xFE,     // 原因未知
        };
        BYTE        bySerciveCode;      // 服务结果码

        enum { ElenReserved=4 };  // 预留字段长度
        BYTE  byReserved[ElenReserved];  // 预留

        //enum { ELenOfFeeType= 2 };  // 计费类型长度
        //enum TFeeType // 
        //{
        //    EFT_PayMonthly=1,       // 包月计费
        //    EFT_1Dime1Time=2,       // 点播，每次1角
        //    EFT_2Dime1Time=3,       // 点播，每次2角
        //};  
        //BYTE        byFeeType;          // 计费类型

        // Constructor && Destructor
        _mobile_comm_frame_bin();
        virtual ~_mobile_comm_frame_bin();

        // From _base_protocol
        int GetProType();
        CString GetProName(); 

        // New virtual functions
        virtual WORD GetCommandID() const;
        virtual void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        virtual BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);

        // New functions
        //void SetMobileNo(__int64 llMobileNo); // 设置手机号码

        // Static functions
        static _mobile_comm_frame_bin* GetInstance(WORD wCommandID); // 根据命令ID返回相应的命令对象
	};

    typedef _mobile_comm_frame_bin TMobileFrameBin,*PTMobileFrameBin;
	//typedef RPointerArray<_content_header> RContentList;

//
//------------------------------  控制协议  -------------------------------------
// 

    /************************************************************************/
    /*  C1. 登录请求                                                        */
    /************************************************************************/
	struct AFX_EXT_CLASS _login_req_bin : public TMobileFrameBin
	{
        enum { ECommandID = 0x0010 }; // CommandID

        // Members
		CString strUserName;        // 用户名
		CString strUserPwd;         // 用户密码
        BYTE    byRadomAuthen[4];   // 由负载服务器产生的随机码

		// Constructor
		_login_req_bin();
	    
        // from TMobileFrameBin
        WORD GetCommandID() const;
        void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
	    
	};
	typedef _login_req_bin TLoginReqBin,*PTLoginReqBin;



    /************************************************************************/
    /* C2. 登录回复                                                         */
    /************************************************************************/
    struct AFX_EXT_CLASS _login_rsp_bin : public TMobileFrameBin
    {
        enum { ECommandID = 0x0011 }; // CommandID

        enum TLoginRst
        {
            ESuccess= 0,		// 登录成功
            EUserNotExsit= 1,	// 用户名不存在
            EPwdError,		    // 用户密码不正确
            EArrearage,         // 用户欠费
            EUserLoggedOut,     // 用户已注销
            EUserBeenOnLine,    // 用户已在线
            ENotFuncServer,     // 没有可用的功能服务器
            EUnknown = 0xFF,	// 失败原因未知
        };
        CString strUserName;    //
        BYTE byLoginRst;        // 登录结果码

        // Constructor
        _login_rsp_bin();

        // from TMobileFrameBin
        WORD GetCommandID() const;
        void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _login_rsp_bin TLoginRspBin,*PTLoginRspBin;

    /************************************************************************/
    /* C10. 客户端退出                                                      */
    /************************************************************************/
    struct AFX_EXT_CLASS _client_exit_bin : public TMobileFrameBin 
    {
        enum { ECommandID = 0x00EF }; // CommandID

        // Constructor
        _client_exit_bin();

        // from TMobileFrameBin
        WORD GetCommandID() const;
        void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef	_client_exit_bin TClientExitBin,*PTClientExitBin;


//
//----------------------- 业务协议 --------------------------------------
//
    ///////////////////////// － 注册 － /////////////////////////////////

    // REG1. 用户注册请求
    struct _register_request_bin : public TMobileFrameBin
    {
        enum { ECommandID = 0x0100 }; // CommandID

        // Members
        CString     strUserName;        // 用户名
        CString     strUserPwd;         // 用户密码
        CString     strPhoneSimNo;      // 手机SIM卡号
        CString     strSoftwareSerNo;   // 软件序列号
        CString     strPhoneSerNo;      // 手机序列号

        // Constructor
        _register_request_bin();

        // From TMobileFrameBin
        WORD GetCommandID() const;
        //void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _register_request_bin TRegRequestBin, *PTRegRequestBin;

    // REG2. 用户注册回复
    struct _register_response_bin : public TMobileFrameBin
    {
        enum { ECommandID= 0x0101 }; // Command ID

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
        BYTE    byRegRspCode;       // 注册回复码

        // Constructor
        _register_response_bin();

        // From TMobileFrameBin
        WORD GetCommandID() const;
        void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        //BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _register_response_bin TRegisterRspBin,*PTRegisterRspBin;




    ////////////////////////  交通信息  /////////////////////////////////

    // TFC1. 通过道路名称请求实时路况信息指令

    struct AFX_EXT_CLASS _traffic_req_by_roadname_bin : public TMobileFrameBin
    {
        enum { ECommandID=0x0300 };    // 

        // Members
        CString     strRoadName;
        DWORD       dwLongitude;    // longitude of link (unit: 1/24s)
        DWORD       dwLatitude;    // 

        // Constructor
        _traffic_req_by_roadname_bin();

        // From TMobileFrameBin
        WORD GetCommandID() const;
        void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _traffic_req_by_roadname_bin TTfcReqByRoadNameBin,*PTTfcReqByRoadNameBin;


    // TFC2. 通过Link起止点请求实时路况信息指令

    struct AFX_EXT_CLASS _traffic_req_by_linkPos_bin : public TMobileFrameBin
    {
        enum { ECommandID= 0x0301 }; // 

        // Member
        CLinkList    linkPosList;

        // Constructor
        _traffic_req_by_linkPos_bin();
        ~_traffic_req_by_linkPos_bin();

        // From TMobileFrameBin
        WORD GetCommandID() const;
        void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _traffic_req_by_linkPos_bin TTfcReqByLinkPosBin,*PTTfcReqByLinkPosBin;

    // TFC3. 实时路况信息回复1

    struct AFX_EXT_CLASS _tfc_inf_rsp1_bin : public TMobileFrameBin
    {
        enum { ECommandID=0x0310 }; // Command ID

       
        CLinkList  m_DtiList;    // 路况信息链表

        // Constructor && Destructor
        _tfc_inf_rsp1_bin();
        ~_tfc_inf_rsp1_bin(); 

        // From TMobileFrameBin
        WORD GetCommandID() const;
        void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _tfc_inf_rsp1_bin TTfcInfRsp1_Bin,*PTTfcInfRsp1_Bin;

    // TFC4. 实时路况信息回复2

    struct AFX_EXT_CLASS _tfc_inf_rsp2_bin : public TMobileFrameBin 
    {
        enum { ECommandID=0x0311 }; // Command ID

        // Members
        CRoadTfcInfList     m_RoadTfcList;

        // Constructor && Destructor
        _tfc_inf_rsp2_bin();
        ~_tfc_inf_rsp2_bin(); 

        // From TMobileFrameBin
        WORD GetCommandID() const;
        void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _tfc_inf_rsp2_bin TTfcInfRsp2_Bin,*PTTfcInfRsp2_Bin;


    //////////////////////////// 气象信息 ////////////////////////////////////

    // WTH1. 通过坐标请求气象信息
    struct AFX_EXT_CLASS _weather_request_by_position : public TMobileFrameBin
    {
        enum { ECommandID= 0x0400 }; // 


        // Members
        DWORD   dwLongitude;    // longitude (unit: 1/24s)
        DWORD   dwLatitude;     // 
        BYTE    byPeriod;       // 时段指示码
        BYTE    byReserved[4];  // 预留

        // Constructor
        _weather_request_by_position();

        // From _mobile_comm_frame
        WORD GetCommandID() const;
        void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _weather_request_by_position TWthReqByPosBin,*PTWthReqByPos_bin;

    // WTH2. 气象信息回复
    struct AFX_EXT_CLASS _weather_response_bin  : public TMobileFrameBin
    {
        enum { ECommandID= 0x0410 }; // 

        // Frame members  
        TWeatherInf     weatherInf;	        // 天气信息
        CString         strWthDes;
        CString         strDistName;    // District name

        // other members

        // Constructor
        _weather_response_bin();

        // From TMobileFrameBin
        WORD GetCommandID() const;
        void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _weather_response_bin TWthRspBin, *PTWthRspBin;

















//////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
#if 0

/************************************************************************/
/* 4.2 配置参数报告                                                     */
/************************************************************************/
    struct _profile_report : public TContentHead 
    {
        enum {EInterval = 30}; //

        // Member
        DWORD         iInterval;      // 发送检测帧的时间间隔

        // Constructor
        _profile_report();

        // New function

        // from _content_header
        void GetBuffer(TDes8& aBuffer)  const;
        //TBool ParseBuffer(const TDesC8& aBuffer,TInt& aIndex);
    };
    typedef _profile_report TProfileReport,*PTProfileReport;




/************************************************************************/
/* 4.11 会话标识帧                                                      */
/************************************************************************/
	// 会话开始
	struct _session_begin : public _content_header 
	{
		// 会话类型（与会话结束帧类型相同）
		enum TSessionType
		{
			EST_Invalid = 0,		// 无效类型
			EST_MapData = 1,		// ［地图数据请求］会话
			EST_PoiInf = 2,			// ［Poi数据请求］会话
			EST_RoadPlan = 3,		// ［路径规划］会话
		};

		_session_begin(BYTE aSessionType)
		{
			iContentType = aSessionType;
			iCmdID = CMD_SESSION_BEG; 
		}
	};
	typedef		_session_begin		TSessionBegin;

	// 请求会话结束/同意会话结束<会话类型与会话开始帧相同）>
	struct _session_end : public _content_header 
	{
		// Constructor
		_session_end(BYTE aSessionType)
		{ 
			iContentType = aSessionType;
			iCmdID = CMD_SESSION_END; 
		}
	};
	typedef		_session_end		TSessionEnd;	



/************************************************************************/
/* 4.13 POI查询请求                                                     */
/************************************************************************/
	struct _poi_inf_request : public _content_header
	{
		enum { ELenCityID= 8};	// 本内容体中城市代码所占字节数
		enum { EMaxSize= 256};   // 

		// Content Header中的iFlag标志(What requesting by)
		enum TPOIReqFlag
		{ 
			EReqByName= 0,		// 通过名称（汉字）查询
			EReqByPinYin= 1,	// 通过名称（拼音）查询
			EReqByRegion= 2,	// 通过区域与类型查询
			EReqByType= 3,		// 通过类型查询
		};

	public:
		// Member
		TBuf8<ELenCityID>			iCityID;
		DWORD						iNumReq;		// 请求的记录数
		DWORD						iStartPoiID;	// 起始POI的ID


	private:
		TBuf8<EMaxSize>				iBuffer;	// 不同的iContentType值表示不同的意义
	
	public:
		// Constructor
		_poi_inf_request(DWORD aNumberReq);

		// New function
		void SetName(const TDesC8& aName);
		void SetRegion(const TRect& aRegion,DWORD aReqType);
		void SetReqType(DWORD aReqType);

		// from _content_header
		void GetBuffer(TDes8& aBuffer) const;
	};
	typedef _poi_inf_request TPoiInfReq,*PTPoiInfReq;

/************************************************************************/
/* 4.14 POI查询回复                                                     */
/************************************************************************/
	
	// 一条POI数据结构
	struct _poi_inf_record
	{
		enum { EMaxSize= 255 };   // 

		// Member
		TUint32				iPoiID;			// ID
		TUint32				iLong;			// 经度
		TUint32				iLati;			// 纬度
		DWORD				iPoiType;		// POI类型
		HBufC16*            iPoiName;		// Name
		HBufC16*            iPoiAddress;	// Address
        HBufC16*     	    iPoiTel;		// Telephone
		//HBufC16*            iDescription;	// POI描述

		// New function
        void   SetPoiName(const TDes& aName);
		void	GetUniName(TDes& aUniName);
		void	GetUniAddress(TDes& aUniAddr);
		void	GetUniTel(TDes& aUniTel);
		void	GetUniDesc(TDes& aUniDesc);
        void   Copy(const _poi_inf_record& aOther);
		TBool	ParseBuffer(const TDesC8& aBuffer,TInt& aIndex);

        //Constructor && Destructor
        _poi_inf_record();
        ~_poi_inf_record();
	};
	typedef _poi_inf_record TPoiInfRecord,TPoiRecord,*PTPoiInfRecord;
	typedef RPointerArray<_poi_inf_record> RPOIRecordList;

	// POI回复结构体(包含多条_poi_inf_record)
	struct _poi_inf_response : public _content_header
	{
		enum { EMaxNumber=250 }; // 回复的最大记录数

        enum TQueryRusult // 查询结果
        {
            EQR_Sucess = 0,         // 成功
            EQR_Err_Unkonwn = 1,    // 未知
            EQR_Err_BadPara = 2,    // 参数错误
            EQR_ERR_UnExpect = 3,   // 异常
        };

		// Member
		RPOIRecordList	iPOIList;

		// Destructor
		~_poi_inf_response();

        // New function
        void Copy(const _poi_inf_response& aOther);
        void Append(const _poi_inf_response& aOther);

		// from _content_header
		TBool ParseBuffer(const TDesC8& aBuffer,TInt& aIndex);
	};
	typedef _poi_inf_response TPoiInfRsp,*PTPoiInfRsp;

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#endif

	
//////////////////////////////////////////////////////////////////////////
// End of file
#endif