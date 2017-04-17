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
/*  ����֡���� (�ַ�������GBK����)                                                        

/************************************************************************/
/*
	Э���ͷ���壺����Э��Ļ��࣬����̳й���
	1��ʵ��GetCommandID����������ӦЭ��֡������ID
	2��ʵ��GetBuffer����(�����Ҫ����Ļ�)
	3��ʵ��ParseBuffer����(�����Ҫ����Ļ�)
*/
/************************************************************************/
	struct AFX_EXT_CLASS _mobile_comm_frame_bin : public TBaseProtocol
	{
        // Э���ʶ
        enum { E_PRO_FLAG = 3};

        //
        enum { EMaxLenFrame= 5000 };    // ���ջ������󳤶�
       
        enum { EEscapeChar = 0x10 };    // ת���ַ�
        enum { EStartFlag= 0x02};       // ֡��ʼ���
        enum { EEndFlag = 0x03 };       // ֡�������
        enum { ELenFrmHead= 2 };        // ֡ͷ����
        enum { ELenFrmTail= 2 };        // ֡β����

        enum { EVersion= 0x10};         // Э��汾��


        // Members
        BYTE        byVersion;          // Э��汾��
        WORD        wCmdID;             // ָ����
        BYTE        byContentType;      // ��������

        enum { ELenPhoenNo= 16 }; // �ֻ�������ͨ��֡��ռλ����
        BYTE  byMobileNo[ELenPhoenNo];  // �ֻ�����

        enum TServiceCode
        {
            ESuccess = 0,           // �ɹ�
            EServiceFailure = 1,    // ���񲻳ɹ�
            EErr_unknow = 0xFE,     // ԭ��δ֪
        };
        BYTE        bySerciveCode;      // ��������

        enum { ElenReserved=4 };  // Ԥ���ֶγ���
        BYTE  byReserved[ElenReserved];  // Ԥ��

        //enum { ELenOfFeeType= 2 };  // �Ʒ����ͳ���
        //enum TFeeType // 
        //{
        //    EFT_PayMonthly=1,       // ���¼Ʒ�
        //    EFT_1Dime1Time=2,       // �㲥��ÿ��1��
        //    EFT_2Dime1Time=3,       // �㲥��ÿ��2��
        //};  
        //BYTE        byFeeType;          // �Ʒ�����

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
        //void SetMobileNo(__int64 llMobileNo); // �����ֻ�����

        // Static functions
        static _mobile_comm_frame_bin* GetInstance(WORD wCommandID); // ��������ID������Ӧ���������
	};

    typedef _mobile_comm_frame_bin TMobileFrameBin,*PTMobileFrameBin;
	//typedef RPointerArray<_content_header> RContentList;

//
//------------------------------  ����Э��  -------------------------------------
// 

    /************************************************************************/
    /*  C1. ��¼����                                                        */
    /************************************************************************/
	struct AFX_EXT_CLASS _login_req_bin : public TMobileFrameBin
	{
        enum { ECommandID = 0x0010 }; // CommandID

        // Members
		CString strUserName;        // �û���
		CString strUserPwd;         // �û�����
        BYTE    byRadomAuthen[4];   // �ɸ��ط����������������

		// Constructor
		_login_req_bin();
	    
        // from TMobileFrameBin
        WORD GetCommandID() const;
        void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
	    
	};
	typedef _login_req_bin TLoginReqBin,*PTLoginReqBin;



    /************************************************************************/
    /* C2. ��¼�ظ�                                                         */
    /************************************************************************/
    struct AFX_EXT_CLASS _login_rsp_bin : public TMobileFrameBin
    {
        enum { ECommandID = 0x0011 }; // CommandID

        enum TLoginRst
        {
            ESuccess= 0,		// ��¼�ɹ�
            EUserNotExsit= 1,	// �û���������
            EPwdError,		    // �û����벻��ȷ
            EArrearage,         // �û�Ƿ��
            EUserLoggedOut,     // �û���ע��
            EUserBeenOnLine,    // �û�������
            ENotFuncServer,     // û�п��õĹ��ܷ�����
            EUnknown = 0xFF,	// ʧ��ԭ��δ֪
        };
        CString strUserName;    //
        BYTE byLoginRst;        // ��¼�����

        // Constructor
        _login_rsp_bin();

        // from TMobileFrameBin
        WORD GetCommandID() const;
        void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _login_rsp_bin TLoginRspBin,*PTLoginRspBin;

    /************************************************************************/
    /* C10. �ͻ����˳�                                                      */
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
//----------------------- ҵ��Э�� --------------------------------------
//
    ///////////////////////// �� ע�� �� /////////////////////////////////

    // REG1. �û�ע������
    struct _register_request_bin : public TMobileFrameBin
    {
        enum { ECommandID = 0x0100 }; // CommandID

        // Members
        CString     strUserName;        // �û���
        CString     strUserPwd;         // �û�����
        CString     strPhoneSimNo;      // �ֻ�SIM����
        CString     strSoftwareSerNo;   // ������к�
        CString     strPhoneSerNo;      // �ֻ����к�

        // Constructor
        _register_request_bin();

        // From TMobileFrameBin
        WORD GetCommandID() const;
        //void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _register_request_bin TRegRequestBin, *PTRegRequestBin;

    // REG2. �û�ע��ظ�
    struct _register_response_bin : public TMobileFrameBin
    {
        enum { ECommandID= 0x0101 }; // Command ID

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
        BYTE    byRegRspCode;       // ע��ظ���

        // Constructor
        _register_response_bin();

        // From TMobileFrameBin
        WORD GetCommandID() const;
        void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        //BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _register_response_bin TRegisterRspBin,*PTRegisterRspBin;




    ////////////////////////  ��ͨ��Ϣ  /////////////////////////////////

    // TFC1. ͨ����·��������ʵʱ·����Ϣָ��

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


    // TFC2. ͨ��Link��ֹ������ʵʱ·����Ϣָ��

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

    // TFC3. ʵʱ·����Ϣ�ظ�1

    struct AFX_EXT_CLASS _tfc_inf_rsp1_bin : public TMobileFrameBin
    {
        enum { ECommandID=0x0310 }; // Command ID

       
        CLinkList  m_DtiList;    // ·����Ϣ����

        // Constructor && Destructor
        _tfc_inf_rsp1_bin();
        ~_tfc_inf_rsp1_bin(); 

        // From TMobileFrameBin
        WORD GetCommandID() const;
        void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _tfc_inf_rsp1_bin TTfcInfRsp1_Bin,*PTTfcInfRsp1_Bin;

    // TFC4. ʵʱ·����Ϣ�ظ�2

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


    //////////////////////////// ������Ϣ ////////////////////////////////////

    // WTH1. ͨ����������������Ϣ
    struct AFX_EXT_CLASS _weather_request_by_position : public TMobileFrameBin
    {
        enum { ECommandID= 0x0400 }; // 


        // Members
        DWORD   dwLongitude;    // longitude (unit: 1/24s)
        DWORD   dwLatitude;     // 
        BYTE    byPeriod;       // ʱ��ָʾ��
        BYTE    byReserved[4];  // Ԥ��

        // Constructor
        _weather_request_by_position();

        // From _mobile_comm_frame
        WORD GetCommandID() const;
        void GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const;
        BOOL ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex);
    };
    typedef _weather_request_by_position TWthReqByPosBin,*PTWthReqByPos_bin;

    // WTH2. ������Ϣ�ظ�
    struct AFX_EXT_CLASS _weather_response_bin  : public TMobileFrameBin
    {
        enum { ECommandID= 0x0410 }; // 

        // Frame members  
        TWeatherInf     weatherInf;	        // ������Ϣ
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
/* 4.2 ���ò�������                                                     */
/************************************************************************/
    struct _profile_report : public TContentHead 
    {
        enum {EInterval = 30}; //

        // Member
        DWORD         iInterval;      // ���ͼ��֡��ʱ����

        // Constructor
        _profile_report();

        // New function

        // from _content_header
        void GetBuffer(TDes8& aBuffer)  const;
        //TBool ParseBuffer(const TDesC8& aBuffer,TInt& aIndex);
    };
    typedef _profile_report TProfileReport,*PTProfileReport;




/************************************************************************/
/* 4.11 �Ự��ʶ֡                                                      */
/************************************************************************/
	// �Ự��ʼ
	struct _session_begin : public _content_header 
	{
		// �Ự���ͣ���Ự����֡������ͬ��
		enum TSessionType
		{
			EST_Invalid = 0,		// ��Ч����
			EST_MapData = 1,		// �۵�ͼ��������ݻỰ
			EST_PoiInf = 2,			// ��Poi��������ݻỰ
			EST_RoadPlan = 3,		// ��·���滮�ݻỰ
		};

		_session_begin(BYTE aSessionType)
		{
			iContentType = aSessionType;
			iCmdID = CMD_SESSION_BEG; 
		}
	};
	typedef		_session_begin		TSessionBegin;

	// ����Ự����/ͬ��Ự����<�Ự������Ự��ʼ֡��ͬ��>
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
/* 4.13 POI��ѯ����                                                     */
/************************************************************************/
	struct _poi_inf_request : public _content_header
	{
		enum { ELenCityID= 8};	// ���������г��д�����ռ�ֽ���
		enum { EMaxSize= 256};   // 

		// Content Header�е�iFlag��־(What requesting by)
		enum TPOIReqFlag
		{ 
			EReqByName= 0,		// ͨ�����ƣ����֣���ѯ
			EReqByPinYin= 1,	// ͨ�����ƣ�ƴ������ѯ
			EReqByRegion= 2,	// ͨ�����������Ͳ�ѯ
			EReqByType= 3,		// ͨ�����Ͳ�ѯ
		};

	public:
		// Member
		TBuf8<ELenCityID>			iCityID;
		DWORD						iNumReq;		// ����ļ�¼��
		DWORD						iStartPoiID;	// ��ʼPOI��ID


	private:
		TBuf8<EMaxSize>				iBuffer;	// ��ͬ��iContentTypeֵ��ʾ��ͬ������
	
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
/* 4.14 POI��ѯ�ظ�                                                     */
/************************************************************************/
	
	// һ��POI���ݽṹ
	struct _poi_inf_record
	{
		enum { EMaxSize= 255 };   // 

		// Member
		TUint32				iPoiID;			// ID
		TUint32				iLong;			// ����
		TUint32				iLati;			// γ��
		DWORD				iPoiType;		// POI����
		HBufC16*            iPoiName;		// Name
		HBufC16*            iPoiAddress;	// Address
        HBufC16*     	    iPoiTel;		// Telephone
		//HBufC16*            iDescription;	// POI����

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

	// POI�ظ��ṹ��(��������_poi_inf_record)
	struct _poi_inf_response : public _content_header
	{
		enum { EMaxNumber=250 }; // �ظ�������¼��

        enum TQueryRusult // ��ѯ���
        {
            EQR_Sucess = 0,         // �ɹ�
            EQR_Err_Unkonwn = 1,    // δ֪
            EQR_Err_BadPara = 2,    // ��������
            EQR_ERR_UnExpect = 3,   // �쳣
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