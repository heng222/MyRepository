/*########################################################################
	���ļ�����: 	ado.h
	����  �ơ�:		ADO ��װ��.
	����  ����:		0.20
	����  �ߡ�:		����
	��E-mail��:		anyou@sina.com
	 ---------------------------------------------------------
	������ʱ�䡿:		20/1/2003 19:08
	���޸�ʱ�䡿:		09/4/2003
	 ---------------------------------------------------------
	���汾��ʷ��:
		[0.20]  :   ��װ�� CAdoCommand ��.
			[-15/4/2003-]
			
		[0.11]  :   ������һЩ bug.
					ɾ�� oleinit() ����, ��Ϊ���ò��ס�
					�����˼�¼����ȡ����.
			[-09/4/2003-]

		[0.10]	:	��Ҫ���� CAdoConnection �� CAdoRecordSet ������, ��װ��
			��ado�ĳ��õĲ�������.
			[-20/1/2003-]
	 ---------------------------------------------------------
	��ʹ��˵����:
		1. ����������ָ�� msado15.dll ��ȫ·��, һ���� "C:\Program Files\
		   Common Files\System\ADO\" Ŀ¼��.
		2. ��ʹ�ñ���֮ǰ����Ҫ��ʼ�� COM ����, ���Ե��� CoInitialize(NULL)  
		   ����ʼ��, �� CoUninitialize() �ͷ�;
		3. ��ʹ�ü�¼������ǰ�����ȵ��� CAdoConnection::Open() �������ݿ�,
		   ���Ӻ�ɸ���� CAdoRecordSet ����ʹ��, �������ر����ݿ�.
		4. ʹ�ü�¼��ִ��SQL���֮ǰ, Ҫʹ�ù������������ SetAdoConnection() 
		   ���������Ӷ���.
		5. �ڱ�������в����������ı��뾯��:
		   warning: unary minus operator applied to unsigned type, result
		   still unsigned
		   �������˾������,������ StdAfx.h �ļ��м�������һ�д����Խ�ֹ
		   �˾���: 	#pragma warning(disable:4146) 
  ########################################################################*/
#if !defined(_ANYOU_COOL_ADO_H)
#define _ANYOU_COOL_ADO_H

#if _MSC_VER > 1000
#pragma once
#endif 
 
// ���� ado �� -----------------------------------------------------------
#pragma warning(disable:4146)
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" named_guids rename("EOF","adoEOF"), rename("BOF","adoBOF")
#pragma warning(default:4146)

using namespace ADODB;  
  

#include <icrsint.h>


class CAdoConnection;
#include <Afxdisp.h>
#include "AdoRecordSet.h"
#include "AdoCommand.h"


//////////////////////////////////////////////////////////////////////////
struct MAdoConnectionObserver 
{
    virtual void OnExecuteFailure() = 0;
};




/*########################################################################
			  ------------------------------------------------
						    CAdoConnection class
			  ------------------------------------------------
  ########################################################################*/
class AFX_EXT_CLASS CAdoConnection
{
// ����/���� ------------------------------------------
public:
	CAdoConnection();
	virtual ~CAdoConnection();

protected:
	void Release();

// ���� -----------------------------------------------
public:
	// ���Ӷ��� ----------------------------------
	_ConnectionPtr& GetConnection() {return m_pConnection;};

	// �쳣��Ϣ ----------------------------------
	CString GetLastErrorText() const;
	ErrorsPtr GetErrors() const;
	ErrorPtr  GetError(long index) const;

	// �����ִ� ----------------------------------
	CString GetConnectionText() const {return m_strConnect;}

	// ������Ϣ ----------------------------------
	CString GetProviderName() const;
	CString GetVersion() const;
	CString GetDefaultDatabase() const;

	// ����״̬ ----------------------------------
	BOOL IsOpen() const;
	long GetState() const;
	
	// ����ģʽ ----------------------------------
	ConnectModeEnum GetMode() const;
	BOOL SetMode(ConnectModeEnum mode);

	// ����ʱ�� ----------------------------------
	long GetConnectTimeOut() const;
	BOOL SetConnectTimeOut(long lTime = 5);
	
	// ����Դ��Ϣ -------------------------------
	_RecordsetPtr OpenSchema(SchemaEnum QueryType);

// ���� -----------------------------------------------
public:
	// ���ݿ����� --------------------------------
	BOOL Open(LPCTSTR lpszConnect =_T(""), long lOptions = adConnectUnspecified);
	BOOL ConnectSQLServer(CString dbsrc, CString dbname, CString user, CString pass, long lOptions = adConnectUnspecified);
	BOOL ConnectAccess(CString dbpath, CString pass = _T(""), long lOptions = adConnectUnspecified);
	BOOL OpenUDLFile(LPCTSTR strFileName, long lOptions = adConnectUnspecified);
	void Close();

	BOOL ConnectOracle(CString Sid, CString User, CString Password,long lOptions = adConnectUnspecified);
// ���� -----------------------------------------------
public:
	// ������ ----------------------------------
	long BeginTrans();
	BOOL RollbackTrans();
	BOOL CommitTrans();

	// ִ�� SQL ��� ------------------------------
	_RecordsetPtr Execute(LPCTSTR strSQL, long lOptions = adCmdText) const;
	BOOL Cancel();

    // �۲���
public:
    void    SetObserver(MAdoConnectionObserver* pObserver);


// ���� -----------------------------------------------
protected:
	CString			m_strConnect;
	_ConnectionPtr	m_pConnection;
    MAdoConnectionObserver* m_pObserver;
};

//////////////////////////////////////////////////////////////////////////
#endif // !defined(_ANYOU_COOL_ADO_H)










































