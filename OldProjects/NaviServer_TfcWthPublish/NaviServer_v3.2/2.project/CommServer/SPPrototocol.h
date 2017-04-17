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
// ��SPͨ�ŵ�Э�鶨��
struct AFX_EXT_CLASS _service_provider_frame : public TBaseProtocol
{
    //
    enum { E_PRO_FLAG = 2};
    //
    enum { EMaxLenFrame = 500}; // ���ջ������󳤶�

    enum { EFrmDelimiter= '|'}; // �ֶηָ���

    enum { EFrameHeader='@' };  // ֡��ʼ��־��@@��
    enum { EFrameTail='#' };    // ֡������־(##)

    // Members
    enum { ENumMember= 9 };
    CString         strVersion;     // Э��汾��
    CString         strFrameType;   // Э������
    CString         strSPNo;        // SP����
    CString         strMobilNo;     // �ֻ�����
    CString         strServcieCode; // ҵ�����
    CString         strLinkIdx;     // ��·ID
    CString         strCityName;    // ��������
    COleDateTime    cDateTime;      // ��Ϣ����������

    enum TCodeFmt
    {
        ESmsWriteToCard = 3,    // ����д������
        EBinary = 4,            // ��������Ϣ
        EUCS2 = 8,              // UCS2����
        EGBK = 15               // GBK����
    };
    int             iCodeing;       // �����ʽ


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
    static _service_provider_frame* GetInstance(const CString& strFrameType); // ��������ID������Ӧ���������
    static void Encapsulate(CString& strFrame); // ��װЭ��֡������֡ͷ��֡β��
    static void PellShell(CString& strFrame); // ����Э��֡��֡ͷ��֡β
    static void GetDelimiter(CString& strDelimiter); // �õ�Э��ָ���
};
typedef _service_provider_frame TSpFrame,*PTSpFrame;

/////////////////////////////////////////////////////////////////////////////

// ҵ������
enum TServiceType
{
    EWeatherService= 1,     // ����ҵ��
    ETrafficService,        // ��ͨҵ��
};

// ���¸��Ѷ���(�������󡢽�ͨ����ҵ��)
struct AFX_EXT_CLASS _pay_monthly_register : public TSpFrame 
{
    // Members
    static const CString gMsgType;
    int    iServiceType;  // ���µ�ҵ������

    // Frame's members
    CString         strContent; // ���͵�����

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
// ���¸���ȡ��
struct AFX_EXT_CLASS _pay_monthly_cancel : public TSpFrame 
{
    // Members
    static const CString gMsgType;
    int    iServiceType;  // ȡ����ҵ������

    // Frame's members
    CString         strContent;    // ���͵�����

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