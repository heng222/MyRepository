/*
* ============================================================================
*  Name     : protocol definition
*  Part of  : NaviInt
*  Created  : 19.11.2006 by ZhangHeng
*  Description:
*     
*  Version  :
*  Copyright: Copyright (c) 2007, China SpaceSat. Corp. Ltd.
* ============================================================================
*/

#ifndef _BUSINESS_FRAME_H_A78E4Y2_
#define _BUSINESS_FRAME_H_A78E4Y2_
//////////////////////////////////////////////////////////////////////////
#include <Afxtempl.h>
#include <BaseProtocol.h>
#include <Geometry.h>
#include "InterfaceEx.h"
//////////////////////////////////////////////////////////////////////////


/************************************************************************/
/*  与业务服务器通信协议帧定义 (字符集采用GBK编码)                                                        

/************************************************************************/
/*
	协议包头定义：所有协议的基类，子类继承规则
	1、实现GetCommandID函数返回相应协议帧的命令ID
	2、实现GetBuffer函数(如果需要打包的话)
	3、实现ParseBuffer函数(如果需要解包的话)
*/
/************************************************************************/


	struct AFX_EXT_CLASS _business_com_frame_ : public TBaseProtocol
	{
        // 协议标识
        enum { E_PRO_FLAG = 4};

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


        enum TServiceCode
        {
            ESuccess = 0,           // 成功
            EServiceFailure = 1,    // 服务不成功
            EErr_unknow = 0xFE,     // 原因未知
        };
        BYTE        bySerciveCode;      // 服务结果码

        enum { ElenReserved=4 };  // 预留字段长度
        BYTE  byReserved[ElenReserved];  // 预留

        // Constructor && Destructor
        _business_com_frame_();
        virtual ~_business_com_frame_();

        // From _base_protocol
        int GetProType();
        CString GetProName(); 

        // New virtual functions
        virtual WORD GetCommandID() const;
        virtual void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        virtual BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);

        // New functions

        // Static functions
        static _business_com_frame_* GetInstance(WORD wCommandID); // 根据命令ID返回相应的命令对象
	};

    typedef _business_com_frame_ TBusinessFrm, *PTBusinessFrm;
	

//
//------------------------------  控制协议  -------------------------------------
// 
#if 0

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
#endif

//////////////////////////////////////////////////////////////////////////
// End of file
#endif