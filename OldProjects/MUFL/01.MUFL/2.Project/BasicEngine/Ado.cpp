/*########################################################################
	Filename: 	ado.cpp
	----------------------------------------------------
	Remarks:	...
	----------------------------------------------------
	Author:		����
	Email:		anyou@sina.com
				anyou@msn.com
	Created:	20/1/2003 19:19
  ########################################################################*/
#include "stdafx.h"
#include "ADO.h"
#include <math.h>
#include "CommonFunc.h"
#include "XTrace.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*########################################################################
			 ------------------------------------------------
					CAdoConnection class ����/��������
			 ------------------------------------------------
  ########################################################################*/

CAdoConnection::CAdoConnection()
{
    CoInitialize(NULL);

	// ���� Connection ����---------------------------
	m_pConnection.CreateInstance("ADODB.Connection");
	#ifdef _DEBUG
	if (m_pConnection == NULL)
	{
		AfxMessageBox(_T("Connection ���󴴽�ʧ��! ��ȷ���Ƿ�ע�Ტ��ʼ����COM����\r\n"));
	}
	#endif
	ASSERT(m_pConnection != NULL);

    //
    m_pObserver = NULL;
}

CAdoConnection::~CAdoConnection()
{
	if (m_pConnection != NULL)
	{
		Release();
	}
}

/*========================================================================
	Name:		���ӵ�����Դ.
	-----------------------------------------------------
	Params:		[lpszConnect]: �����ַ���, ����������Ϣ.
				[lOptions]:	��ѡ. �����÷�������ͬ�������첽�ķ�ʽ��������
						Դ. ����������ĳ������:
		[����]					[˵��] 
		----------------------------------
		adConnectUnspecified	(Ĭ��)ͬ����ʽ������. 
		adAsyncConnect			�첽��ʽ������. Ado�� ConnectComplete ��
						����֪ͨ�Ѿ��������. 
==========================================================================*/
BOOL CAdoConnection::Open(LPCTSTR lpszConnect, long lOptions)
{
	ASSERT(m_pConnection != NULL);
	ASSERT(AfxIsValidString(lpszConnect));
	m_strConnect = lpszConnect;
	if (m_strConnect.IsEmpty())
	{
		ASSERT(FALSE);
		return FALSE;
	}

	if (IsOpen()) Close();

	try
	{
		// �������ݿ� ---------------------------------------------
		return (m_pConnection->Open(_bstr_t(m_strConnect), _T(""), _T(""), lOptions) == S_OK);
	}
	catch (_com_error e)
	{
		XTRACE(_T("Warning: �������ݿⷢ���쳣. ������Ϣ: %s; \n"), e.ErrorMessage());
		XTRACE(_T("%s\r\n"), GetLastErrorText());
		return FALSE;
	} 
	catch (...)
	{
		XTRACE(_T("Warning: �������ݿ�ʱ����δ֪����:"));
	}
	return FALSE;
}

/*========================================================================
	Name:	���� SQL SERVER ���ݿ�. 
	-----------------------------------------------------
	Params:		[dbsrc]:	SQL SERVER ��������.
				[dbname]:	Ĭ�ϵ����ݿ���.
				[user]:		�û���.
				[pass]:		����.
==========================================================================*/
BOOL CAdoConnection::ConnectSQLServer(CString dbsrc, CString dbname, CString user, CString pass, long lOptions)
{
	CString strConnect = _T("Provider=SQLOLEDB.1; Data Source=") + dbsrc + 
						 _T("; Initial Catalog=") + dbname  +
						 _T("; User ID=") + user + 
						 _T("; PWD=") + pass;
	return Open(LPCTSTR(strConnect), lOptions);
}

/*========================================================================
	Name:	���� ACCESS ���ݿ�. 
	-----------------------------------------------------
	Params:		[dbpath]:	MDB ���ݿ��ļ�·����.
				[pass]:		��������.
===========================================================================*/
BOOL CAdoConnection::ConnectAccess(CString dbpath, CString pass, long lOptions)
{
	CString strConnect = _T("Provider=Microsoft.Jet.OLEDB.4.0; Data Source=") + dbpath;
	if (pass != _T("")) 
	{
		strConnect += _T("Jet OLEDB:Database Password=") + pass + _T(";");
	}
	return Open(LPCTSTR(strConnect), lOptions);
}

/*========================================================================
	Name:	ͨ�� udl �ļ��������ݿ�. 
	-----------------------------------------------------
	Params:		[strFileName]:	UDL ���ݿ������ļ�·����.
==========================================================================*/
BOOL CAdoConnection::OpenUDLFile(LPCTSTR strFileName, long lOptions)
{
	CString strConnect = _T("File Name=");
	strConnect += strFileName;
	return Open(LPCTSTR(strConnect), lOptions);
}
/*========================================================================
	Name:	���� Oracle ���ݿ�. 
	-----------------------------------------------------
	Params:		[sid]:	    Oracle��������.
				[user]:		�û���.
				[pass]:		����.
==========================================================================*/
BOOL CAdoConnection::ConnectOracle(CString Sid, CString User, CString Password,long lOptions)
{
//MM_jsjh_STRING = "Provider=MSDAORA.1;Password=JSJH;User ID=JSJH;Data Source=JSJH;Persist Security Info=True"
	CString strConnect = _T("Provider=MSDAORA.1; Data Source=") + Sid + 
						 _T("; User ID=") + User + 
						 _T("; Password=") + Password +
						 _T("; Persist Security Info=True");
	return Open(LPCTSTR(strConnect), lOptions);
}

/*========================================================================
	Name:	�ر�������Դ������.
	-----------------------------------------------------
	Remarks: ʹ�� Close �����ɹر� Connection �����Ա��ͷ����й�����ϵͳ��Դ. 
==========================================================================*/
void CAdoConnection::Close()
{
	try
	{
		if (m_pConnection != NULL && IsOpen()) 
		{
			m_pConnection->Close();
		}
	}
	catch (_com_error e)
	{
		XTRACE(_T("Warning: �ر����ݿⷢ���쳣. ������Ϣ: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
	} 
}

/*========================================================================
	Name:	�ر����Ӳ��ͷŶ���.
	-----------------------------------------------------
	Remarks: �ر����Ӳ��ͷ�connection����.
==========================================================================*/
void CAdoConnection::Release()
{
	if (IsOpen()) Close();
	m_pConnection.Release();
}

/*========================================================================
	Name:		ִ��ָ���Ĳ�ѯ��SQL ��䡢�洢���̵�.
    ----------------------------------------------------------
	Remarks:	��ο� CAdoRecordSet ���Open����. ���ص� Recordset ����ʼ
			��Ϊֻ��������ǰ���α�.
==========================================================================*/
_RecordsetPtr CAdoConnection::Execute(LPCTSTR lpszSQL, long lOptions) const
{
	ASSERT(m_pConnection != NULL);
	ASSERT(AfxIsValidString(lpszSQL));

	try
	{
		return m_pConnection->Execute(_bstr_t(lpszSQL), NULL, lOptions);
	}
	catch (_com_error e)
	{
		XTRACE(_T("Warning: Execute ���������쳣. ������Ϣ: %s \n"), e.ErrorMessage());
        if (m_pObserver!=NULL)
        {
            m_pObserver->OnExecuteFailure();
        }
		return FALSE;
	} 
	return FALSE;
}

/*========================================================================
	Remarks:	��ο� CAdoRecordSet �� Cancel ����.
==========================================================================*/
BOOL CAdoConnection::Cancel()
{
	ASSERT(m_pConnection != NULL);
	try
	{
		return m_pConnection->Cancel();
	}
	catch (_com_error e)
	{
		XTRACE(_T("Warning: Cancel ���������쳣. ������Ϣ: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return FALSE;
	} 
	return FALSE;
}

/*========================================================================
	Name:	ȡ��������Ĵ�����Ϣ.
==========================================================================*/
CString CAdoConnection::GetLastErrorText() const
{
	ASSERT(m_pConnection != NULL);
	CString strErrors;
	try
	{
		if (m_pConnection != NULL)
		{
			ErrorsPtr pErrors = m_pConnection->Errors;
			CString strError;
			for (long n = 0; n < pErrors->Count; n++)
			{
				ErrorPtr pError = pErrors->GetItem(n);
				strError.Format(_T("Description: %s\r\nState: %s, Native: %d, Source: %s\r\n"),
								(LPCTSTR)pError->Description,
								(LPCTSTR)pError->SQLState,
										 pError->NativeError,
								(LPCTSTR)pError->Source);
				strErrors += strError;
			}
		}
		return strErrors;
	}
	catch (_com_error e)
	{
		XTRACE(_T("Warning: GetLastError ���������쳣. ������Ϣ: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return strErrors;
	} 
	return strErrors;
}

ErrorsPtr CAdoConnection::GetErrors() const
{
	ASSERT(m_pConnection != NULL);
	try
	{
		if (m_pConnection != NULL)
		{
			return m_pConnection->Errors;
		}
		return NULL;
	}
	catch (_com_error e)
	{
		XTRACE(_T("Warning: GetErrors ���������쳣. ������Ϣ: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return NULL;
	} 
	return NULL;
}

ErrorPtr CAdoConnection::GetError(long index) const
{
	ASSERT(m_pConnection != NULL);
	try
	{
		if (m_pConnection != NULL)
		{
			ErrorsPtr pErrors =  m_pConnection->Errors;
			if (index >= 0 && index < pErrors->Count)
			{
				return pErrors->GetItem(_variant_t(index));
			}
		}
		return NULL;
	}
	catch (_com_error e)
	{
		XTRACE(_T("Warning: GetError ���������쳣. ������Ϣ: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return NULL;
	} 
	return NULL;
}

/*========================================================================
	Name:		ȡ������ʱ��.
==========================================================================*/
long CAdoConnection::GetConnectTimeOut() const
{
	ASSERT(m_pConnection != NULL);
	try
	{
		return m_pConnection->GetConnectionTimeout();
	}
	catch (_com_error e)
	{
		XTRACE(_T("Warning: GetConnectTimeOut ���������쳣. ������Ϣ: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return -1;
	} 
	return -1;
}

/*========================================================================
	Name:		��������ʱ��.
==========================================================================*/
BOOL CAdoConnection::SetConnectTimeOut(long lTime)
{
	ASSERT(m_pConnection != NULL);
	try
	{
		m_pConnection->PutConnectionTimeout(lTime);
		return TRUE;
	}
	catch (_com_error e)
	{
		XTRACE(_T("Warning: SetConnectTimeOut ���������쳣. ������Ϣ: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return FALSE;
	} 
}

/*========================================================================
	Name:		ȡ��Ĭ�����ݿ������.
==========================================================================*/
CString CAdoConnection::GetDefaultDatabase() const
{
	ASSERT(m_pConnection != NULL);
	try
	{
		return CString(LPCTSTR(_bstr_t(m_pConnection->GetDefaultDatabase())));
	}
	catch (_com_error e)
	{
		XTRACE(_T("Warning: GetDefaultDatabase ���������쳣. ������Ϣ: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return CString(_T(""));
	} 
}

/*========================================================================
	Name:		ȡ�� Connection �����ṩ�ߵ�����.
==========================================================================*/
CString CAdoConnection::GetProviderName() const
{
	ASSERT(m_pConnection != NULL);
	try
	{
		return CString(LPCTSTR(_bstr_t(m_pConnection->GetProvider())));
	}
	catch (_com_error e)
	{
		XTRACE(_T("Warning: GetProviderName ���������쳣. ������Ϣ: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return CString(_T(""));
	} 
}

/*========================================================================
	Name:		ȡ�� ADO �İ汾��
==========================================================================*/
CString CAdoConnection::GetVersion() const
{
	ASSERT(m_pConnection != NULL);
	try
	{
		return CString(LPCTSTR(_bstr_t(m_pConnection->GetVersion())));
	}
	catch (_com_error e)
	{
		XTRACE(_T("Warning: GetVersion ���������쳣. ������Ϣ: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return CString(_T(""));
	} 
}

/*========================================================================
	Name:		ȡ�ö����״̬(ͬ Recordset ����� GetState ����).
	-----------------------------------------------------
	returns:	�������г���֮һ�ĳ�����ֵ.
		[����]				[˵��] 
		----------------------------------
		adStateClosed		ָʾ�����ǹرյ�. 
		adStateOpen			ָʾ�����Ǵ򿪵�. 
	-----------------------------------------------------
	Remarks:		������ʱʹ�� State ����ȡ��ָ������ĵ�ǰ״̬.
==========================================================================*/
long CAdoConnection::GetState() const
{
	ASSERT(m_pConnection != NULL);
	try
	{
		return m_pConnection->GetState();
	}
	catch (_com_error e)
	{
		XTRACE(_T("Warning: GetState �����쳣. ������Ϣ: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return -1;
	} 
	return -1;
}

/*========================================================================
	Name:	������Ӷ����Ƿ�Ϊ��״̬.
==========================================================================*/
BOOL CAdoConnection::IsOpen() const
{
	try
	{
		return (m_pConnection != NULL && (m_pConnection->State & adStateOpen));
	}
	catch (_com_error e)
	{
		XTRACE(_T("Warning: IsOpen ���������쳣. ������Ϣ: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return FALSE;
	} 
	return FALSE;
}

/*========================================================================
	Name:		ȡ���� Connection �������޸����ݵĿ���Ȩ��.
    ----------------------------------------------------------
	returns:	��������ĳ�� ConnectModeEnum ��ֵ.
		[����]				 [˵��] 
		----------------------------------
		adModeUnknown		 Ĭ��ֵ. ����Ȩ����δ���û��޷�ȷ��. 
		adModeRead			 ����Ȩ��Ϊֻ��. 
		adModeWrite			 ����Ȩ��Ϊֻд. 
		adModeReadWrite		 ����Ȩ��Ϊ��/д. 
		adModeShareDenyRead  ��ֹ�����û�ʹ�ö�Ȩ�޴�����. 
		adModeShareDenyWrite ��ֹ�����û�ʹ��дȨ�޴�����. 
		adModeShareExclusive ��ֹ�����û�������. 
		adModeShareDenyNone  ��ֹ�����û�ʹ���κ�Ȩ�޴�����.
    ----------------------------------------------------------
	Remarks: ʹ�� Mode ���Կ����û򷵻ص�ǰ�������ṩ������ʹ�õķ���Ȩ��.
==========================================================================*/
ConnectModeEnum CAdoConnection::GetMode() const
{
	ASSERT(m_pConnection != NULL);
	try
	{
		return m_pConnection->GetMode();
	}
	catch (_com_error e)
	{
		XTRACE(_T("Warning: GetMode �����쳣. ������Ϣ: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return adModeUnknown;
	} 
	return adModeUnknown;
}

/*========================================================================
	Name:		������ Connection ���޸����ݵĿ���Ȩ��. ��ο� GetMode ����.
    ----------------------------------------------------------
	Remarks:	ֻ���ڹر� Connection ����ʱ�������� Mode ����.
==========================================================================*/
BOOL CAdoConnection::SetMode(ConnectModeEnum mode)
{
	ASSERT(m_pConnection != NULL);
	ASSERT(!IsOpen());

	try
	{
		m_pConnection->PutMode(mode);
	}
	catch (_com_error e)
	{
		XTRACE(_T("Warning: SetMode �����쳣. ������Ϣ: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return FALSE;
	} 
	return TRUE;
}

/*========================================================================
    Name:		������Դ��ȡ���ݿ���Ϣ.
	-----------------------------------------------------
	Params:		QueryType  ��Ҫ��Line��ģʽ��ѯ����.
	-----------------------------------------------------
	returns:	���ذ������ݿ���Ϣ�� Recordset ����. Recordset ����ֻ������̬
			�α��.
==========================================================================*/
_RecordsetPtr CAdoConnection::OpenSchema(SchemaEnum QueryType)
{
	ASSERT(m_pConnection != NULL);
	try
	{
		return m_pConnection->OpenSchema(QueryType, vtMissing, vtMissing);
	}
	catch(_com_error e)
	{
		XTRACE(_T("Warning: OpenSchema���������쳣. ������Ϣ: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return NULL;
	} 
	return NULL;
}

/*########################################################################
			  ------------------------------------------------
									������
			  ------------------------------------------------
  ########################################################################*/

/*========================================================================
    Name:		��ʼ������.
	-----------------------------------------------------
	returns:	����֧��Ƕ����������ݿ���˵, ���Ѵ򿪵������е��� BeginTrans 
	��������ʼ�µ�Ƕ������. ����ֵ��ָʾǶ�ײ��: ����ֵΪ 1 ��ʾ�Ѵ򿪶���
	���� (�����񲻱���һ��������Ƕ��), ����ֵΪ 2 ��ʾ�Ѵ򿪵ڶ�������(Ƕ��
	�ڶ��������е�����), ��������.
	-----------------------------------------------------
	Remarks:	һ�������� BeginTrans ����, �ڵ��� CommitTrans �� RollbackTrans
	��������֮ǰ, ���ݿ⽫���������ύ�������κθ���.
		
==========================================================================*/
long CAdoConnection::BeginTrans()
{
	ASSERT(m_pConnection != NULL);
	try
	{
		return m_pConnection->BeginTrans();
	}
	catch (_com_error e)
	{
		XTRACE(_T("Warning: BeginTrans ���������쳣. ������Ϣ: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return -1;
	} 
	return -1;
}

/*========================================================================
    Name:		�����κθ��Ĳ�������ǰ����.
	-----------------------------------------------------
	Remarks:	���� CommitTrans �� RollbackTrans ֻӰ�����´򿪵�����; ��
	�����κθ��߲�����֮ǰ����رջ�ؾ�ǰ����.
==========================================================================*/
BOOL CAdoConnection::CommitTrans()
{
	ASSERT(m_pConnection != NULL);
	try
	{
		return SUCCEEDED(m_pConnection->CommitTrans());
	}
	catch (_com_error e)
	{
		XTRACE(_T("Warning: CommitTrans ���������쳣. ������Ϣ: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return FALSE;
	} 
	return FALSE;
}

/*========================================================================
    Name:		ȡ����ǰ�������������κθ��Ĳ���������.
==========================================================================*/
BOOL CAdoConnection::RollbackTrans()
{
	ASSERT(m_pConnection != NULL);
	try
	{
		return SUCCEEDED(m_pConnection->RollbackTrans());
	}
	catch (_com_error e)
	{
		XTRACE(_T("Warning: RollbackTrans ���������쳣. ������Ϣ: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return FALSE;
	} 
	return FALSE;
}



void CAdoConnection::SetObserver(MAdoConnectionObserver* pObserver)
{
    ASSERT(pObserver!=NULL);
    m_pObserver = pObserver;
}
