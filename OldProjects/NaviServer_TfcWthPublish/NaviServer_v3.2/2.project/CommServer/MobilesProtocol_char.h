
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
    ���ֻ��ն�ͨ��ʱ��Э��
*/


/************************************************************************/
/*                                                                      /*
                    < ���ֻ��ն�ͨ�ŵ�����֡�ṹ > 
/*                                                                      */
    struct AFX_EXT_CLASS _mobile_comm_frame_char : public TBaseProtocol
    {
        // Э���ʶ
        enum { E_PRO_FLAG = 1};
        //
        enum { EMaxLenFrame= 4000 };    // ���ջ������󳤶�
        enum { EHeaderFrame= '@'};      // ֡��ʼ���
        enum { ELenCommand= 4 };        // ָ���볤��

#ifdef _NEW_CHAR_PROTOCOL
        enum { EOffBlockSize= 8 };      // Э�����С��Э���ͷ�е�ƫ��
#else
        enum { EOffBlockSize= 6 };      // Э�����С��Э���ͷ�е�ƫ��
#endif
        enum { ESizeBlock= 4 };         // Э�����С��Э���ͷ����ռ�ֽ���

#ifdef _NEW_CHAR_PROTOCOL
        enum { ESizeOfHeader= 28 };     // Э���ͷ��С
#else
        enum { ESizeOfHeader= 26 };     // Э���ͷ��С
#endif

        
        // Members
#ifdef _NEW_CHAR_PROTOCOL
        char        cVersion[2];        // Э��汾��
#endif        
        char        cHeader[2];         // Э���ͷ��ǣ�@@��
        WORD        wCmdID;             // ָ����
        WORD        wBlockSize;         // Э�����С

#ifdef  _NEW_CHAR_PROTOCOL
        enum { ELenOfCellphoneNo= 14 }; // �ֻ�������ͨ��֡��ռλ����
#else
        enum { ELenOfCellphoneNo= 16 }; // �ֻ�������ͨ��֡��ռλ����
#endif
        CString     strMobileNo;        // �ֻ�����

#ifdef _NEW_CHAR_PROTOCOL
        enum { ELenOfFeeType= 2 };      // �Ʒ����ͳ���
        enum TFeeType // 
        {
            EFT_PayMonthly=1,       // ���¼Ʒ�
            EFT_1Dime1Time=2,       // �㲥��ÿ��1��
            EFT_2Dime1Time=3,       // �㲥��ÿ��2��
        };  
        BYTE        byFeeType;          // �Ʒ�����
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
        virtual void CalculateBlockSize(); // ��������(����֡)��Ҫ�̳д˷���

        // New functions
        void SetMobileNo(__int64 llMobileNo); // �����ֻ�����

        // Static functions
        static _mobile_comm_frame_char* GetInstance(WORD wCommandID); // ��������ID������Ӧ���������

    };
    typedef _mobile_comm_frame_char TMobileFrame_Char,*PTMobileFrame_Char;


//3. Э����ṹ
/////////////////////////////////////////////////////////////////////////////////
// REG1. �û�ע������
    struct _register_request_char : public TMobileFrame_Char
    {
        enum { ECommandID = 0x0013 }; // CommandID

        // Members
        CString     strUserName;        // �û���
        CString     strUserPwd;         // �û�����
        CString     strPhoneSimNo;      // �ֻ�SIM����
        CString     strSoftwareSerNo;   // ������к�
        CString     strPhoneSerNo;      // �ֻ����к�

        // Constructor
        _register_request_char();

        // From _mobile_comm_frame
        //void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
        WORD GetCommandID() const;
    };
    typedef _register_request_char TRegRequest_Char, *PTRegRequest_Char;

/////////////////////////////////////////////////////////////////////////////////
// REG2. �û�ע��ظ�
    struct _register_response : public TMobileFrame_Char
    {
        enum { ECommandID= 0x0014 }; // Command ID

        // ע��ظ���
        enum ERegRspCode
        {
            ERR_REG_SUCESS = 0,     // ע��ɹ�
            ERR_USER_ALREAD_EXITS=1,// �û����Ѵ���
            ERR_INVALID_USERNAME=2, // �û������зǷ��ַ�
            ERR_ALREADY_REGISTER=3, // �������ע�� 
            ERR_OTHERS_REASONS=10,  // ��������
        };

        // Members
        enum { ELenRegRspCode=2 }; // �ظ���ĳ���
        WORD    wRegRspCode;       // ע��ظ���

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
// L1. ��¼ָ��
    struct AFX_EXT_CLASS _login_request_char : public TMobileFrame_Char
    {
        enum { ECommandID = 0x0011 }; // CommandID

        // Members
        CString strUserName;     // �û���
        CString strUserPwd;      // �û�����

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
// L2. ��¼����ظ�ָ��
    struct _login_response_char : public TMobileFrame_Char
    {
        enum { ECommandID= 0x0012 }; // 

        // Members
        WORD    wLoginRst;      //��¼�����

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
// TT. �������ָ��(������)
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
// 3.5 �˳�ָ��
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
// WTH1. ������Ϣ����
    struct AFX_EXT_CLASS _weather_request_ : public TMobileFrame_Char
    {
        enum { ECommandID=0x0027 };     // 
        
        // ��������
        enum TReqType
        {
            ERT_POSITION= '3',    // ͨ����γ������
            ERT_CITYNAME = '4',   // ͨ��������������[�������ϡ�]
        };

        // ʱ��ָʾ��
        enum TPeriodCode
        {
            EPer_TodayDaytime = 0x01,           // �������Ԥ��
            EPer_Tonight = 0x02,                // ����ҹ��Ԥ��
            EPer_TomorrowDayTime = 0x03,        // �������Ԥ��
            EPer_Tom_evening = 0x0D,            // ����ҹ��Ԥ��
            EPer_Fr6To9 = 0x04,	                // δ��6-9��Ԥ��
            EPer_Afternoon = 0x05,	            // ��������Ԥ��
            EPer_Fr9To12 = 0x06,	            // δ��9-12��Ԥ��
            EPer_Fr11To14 = 0x07,	            // δ��11-14��Ԥ��
            EPer_Fr14To17 = 0x08,	            // δ��14-17��Ԥ��
            EPer_Fr17To20 = 0x09,	            // δ��17-20��Ԥ��
            EPer_Fr20To23 = 0x0A,	            // δ��20-23��Ԥ��
        };

        // Members
        BYTE    byType;         // ��������,�μ�TReqType 
        DWORD   dwLongitude;    // longitude (unit: 1/24s)
        DWORD   dwLatitude;     // 
        BYTE    byPeriod;       // ʱ��ָʾ��

        // Constructor
        _weather_request_();

        // From _mobile_comm_frame
        virtual WORD GetCommandID() const;
        virtual void CalculateBlockSize();
        virtual void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        virtual BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _weather_request_ TWeatherReq_Char, *PTWeatherReq_Char;


// WTH2. ������Ϣ����1
    struct AFX_EXT_CLASS _weather_response1 : public TMobileFrame_Char
    {
        enum { ECommandID= 0x0025 };    //

        // ָ��ִ�н��
        enum TExcuteFlag
		{
			EExeFailure='0',
            EExeSuccess='1',
        };

        // ���ͱ�ʶ
        enum TTypeFlag
        {
            ETF_LIVE_POS=1,       // ͨ����γ������ʵ��������Ϣ(*������*)
            ETF_LIVE_REG,         // ͨ������������ʵ��������Ϣ (*������*)
            ETF_PRE_REG,          // ͨ������������Ԥ��������Ϣ (*������*)
            ETF_PRE_NAME,         // ͨ��POI��������Ԥ��������Ϣ (*������*)
            ETF_PRE_POS= '5',     // ͨ����γ������Ԥ��������Ϣ
        };

        // Members
        BYTE        byExcuteRst;        // ָ��ִ�н��
        BYTE        byFlag;             // ���ͱ�ʶ

        DWORD       dwLongitude;        // ����(��λ��1/24��)
        DWORD       dwLatitude;         // γ��(��λ��1/24��)

        TWeatherInf     weatherInf;	        // ������Ϣ


        // Constructor
        _weather_response1();

        // From _mobile_comm_frame
        WORD GetCommandID() const;
        void CalculateBlockSize();
        void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _weather_response1 TWeatherRsp1_char,*PTWeatherRsp1_char;

// WTH3.������Ϣ�ظ�2
    struct AFX_EXT_CLASS _weather_response2  : public TMobileFrame_Char
    {
        enum { ECommandID=0x0028 }; // 

        // ָ��ִ�н��
        enum TExcuteFlag
        {
            EExeSuccess = '0',
            EExeFailure = '1',
        };

        // Frame members
        BYTE        byExcuteRst;        // ָ��ִ�н��
        BYTE        byPeriod;	        // ʱ��
        CString     strWthDes;	        // ��������

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
// TFC1. ͨ��Link��ֹ�㼰��������·����Ϣ
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
// TFC2. ͨ����·��������ʵʱ·����Ϣ
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
// TFC4. ʵʱ·����Ϣ����ָ��
    

    // ·����Ϣ�ظ�_1

    struct AFX_EXT_CLASS _traffic_response_1_char : public TMobileFrame_Char
    {
        enum { ECommandID=0x0045 }; // Command ID

        enum ESuccssFlag
        {
            ESucess =  0,
            EFailure = 1,
        };

        enum {EMaxDTI=50};

        BYTE        byExcuteRst;     // ָ��ִ�н����־
        CLinkList   DtiList;         // ·����Ϣ����

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


    // ·����Ϣ�ظ�_2

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
