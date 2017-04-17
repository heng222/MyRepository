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
/*  ��ҵ�������ͨ��Э��֡���� (�ַ�������GBK����)                                                        

/************************************************************************/
/*
	Э���ͷ���壺����Э��Ļ��࣬����̳й���
	1��ʵ��GetCommandID����������ӦЭ��֡������ID
	2��ʵ��GetBuffer����(�����Ҫ����Ļ�)
	3��ʵ��ParseBuffer����(�����Ҫ����Ļ�)
*/
/************************************************************************/


	struct AFX_EXT_CLASS _business_com_frame_ : public TBaseProtocol
	{
        // Э���ʶ
        enum { E_PRO_FLAG = 4};

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


        enum TServiceCode
        {
            ESuccess = 0,           // �ɹ�
            EServiceFailure = 1,    // ���񲻳ɹ�
            EErr_unknow = 0xFE,     // ԭ��δ֪
        };
        BYTE        bySerciveCode;      // ��������

        enum { ElenReserved=4 };  // Ԥ���ֶγ���
        BYTE  byReserved[ElenReserved];  // Ԥ��

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
        static _business_com_frame_* GetInstance(WORD wCommandID); // ��������ID������Ӧ���������
	};

    typedef _business_com_frame_ TBusinessFrm, *PTBusinessFrm;
	

//
//------------------------------  ����Э��  -------------------------------------
// 
#if 0

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
#endif

//////////////////////////////////////////////////////////////////////////
// End of file
#endif