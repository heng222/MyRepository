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
#ifndef _SERVICE_PROVIDER_PROTOCOL_20071216
#define _SERVICE_PROVIDER_PROTOCOL_20071216
//////////////////////////////////////////////////////////////////////////

#include "afx.h"
#include <BaseProtocol.h>

//////////////////////////////////////////////////////////////////////////
// 与SP通信的协议定义
struct AFX_EXT_CLASS _service_provider_frame : public TBaseProtocol
{
    //
    enum { E_PRO_FLAG = 2};
    //
    enum { EMaxLenFrame = 500}; // 接收缓冲的最大长度

    enum { EFrmDelimiter= '|'}; // 字段分隔符

    enum { EFrameHeader='@' };  // 帧起始标志（@@）
    enum { EFrameTail='#' };    // 帧结束标志(##)

    // Members
    enum { ENumMember= 9 };
    CString         strVersion;     // 协议版本号
    CString         strFrameType;   // 协议类型
    CString         strSPNo;        // SP号码
    CString         strMobilNo;     // 手机号码
    CString         strServcieCode; // 业务代码
    CString         strLinkIdx;     // 链路ID
    CString         strCityName;    // 城市名称
    COleDateTime    cDateTime;      // 消息产生的日期

    enum TCodeFmt
    {
        ESmsWriteToCard = 3,    // 短信写卡操作
        EBinary = 4,            // 二进制信息
        EUCS2 = 8,              // UCS2编码
        EGBK = 15               // GBK编码
    };
    int             iCodeing;       // 编码格式


    // Constructor && Destructor
    _service_provider_frame();
    virtual ~_service_provider_frame();

    // From _base_protocol
    int GetProType();
    CString GetProName();

    // New virtual functions
    //virtual CString GetFrameType() const;
    virtual BOOL ParseBuffer(const CStringList& cStrList,POSITION& posIdx);
    virtual void GetElementList(CStringList& strEleList) const;

    // New functions
    void GetBuffer(CString& strFrame) const;
    

    // Static functions
    static _service_provider_frame* GetInstance(const CString& strFrameType); // 根据命令ID返回相应的命令对象
    static void Encapsulate(CString& strFrame); // 封装协议帧（加入帧头与帧尾）
    static void PellShell(CString& strFrame); // 剥离协议帧的帧头与帧尾
    static void GetDelimiter(CString& strDelimiter); // 得到协议分隔符
};
typedef _service_provider_frame TSpFrame,*PTSpFrame;

/////////////////////////////////////////////////////////////////////////////

// 业务类型
enum TServiceType
{
    EWeatherService= 1,     // 气象业务
    ETrafficService,        // 交通业务
};

// 包月付费定制(包括气象、交通包月业务)
struct AFX_EXT_CLASS _pay_monthly_register : public TSpFrame 
{
    // Members
    static const CString gMsgType;
    int    iServiceType;  // 包月的业务类型

    // Frame's members
    CString         strContent; // 发送的内容

    // Constructor && Destructor
    _pay_monthly_register();

    // From TSpFrame
    //virtual void GetBuffer(CString& strFrame) const;
    virtual BOOL ParseBuffer(const CStringList& cStrList,POSITION& posIdx);
    virtual void GetElementList(CStringList& strEleList) const;

    // New functions

};
typedef _pay_monthly_register TPayMonthlyReg, *PTPayMonthlyReg;

/////////////////////////////////////////////////////////////////////////////
// 包月付费取消
struct AFX_EXT_CLASS _pay_monthly_cancel : public TSpFrame 
{
    // Members
    static const CString gMsgType;
    int    iServiceType;  // 取消的业务类型

    // Frame's members
    CString         strContent;    // 发送的内容

    // Constructor && Destructor
    _pay_monthly_cancel();

    // From TSpFrame
    //virtual void GetBuffer(CString& strFrame) const;
    virtual BOOL ParseBuffer(const CStringList& cStrList,POSITION& posIdx);
    virtual void GetElementList(CStringList& strEleList) const;

    // New functions
};
typedef _pay_monthly_cancel TPayMonthlyCancel, *PTPayMonthlyCancel;

/////////////////////////////////////////////////////////////////////////////
// 

/////////////////////////////////////////////////////////////////////////////
// 

/////////////////////////////////////////////////////////////////////////////
// 


/////////////////////////////////////////////////////////////////////////////
// 


/////////////////////////////////////////////////////////////////////////////
// 

/////////////////////////////////////////////////////////////////////////////
// 


//////////////////////////////////////////////////////////////////////////
#endif