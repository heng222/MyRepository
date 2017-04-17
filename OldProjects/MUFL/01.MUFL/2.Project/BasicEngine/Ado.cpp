/*########################################################################
	Filename: 	ado.cpp
	----------------------------------------------------
	Remarks:	...
	----------------------------------------------------
	Author:		成真
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
					CAdoConnection class 构造/析构函数
			 ------------------------------------------------
  ########################################################################*/

CAdoConnection::CAdoConnection()
{
    CoInitialize(NULL);

	// 创建 Connection 对象---------------------------
	m_pConnection.CreateInstance("ADODB.Connection");
	#ifdef _DEBUG
	if (m_pConnection == NULL)
	{
		AfxMessageBox(_T("Connection 对象创建失败! 请确认是否注册并初始化了COM环境\r\n"));
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
	Name:		连接到数据源.
	-----------------------------------------------------
	Params:		[lpszConnect]: 连接字符串, 包含连接信息.
				[lOptions]:	可选. 决定该方法是以同步还是异步的方式连接数据
						源. 可以是如下某个常量:
		[常量]					[说明] 
		----------------------------------
		adConnectUnspecified	(默认)同步方式打开连接. 
		adAsyncConnect			异步方式打开连接. Ado用 ConnectComplete 事
						件来通知已经完成连接. 
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
		// 连接数据库 ---------------------------------------------
		return (m_pConnection->Open(_bstr_t(m_strConnect), _T(""), _T(""), lOptions) == S_OK);
	}
	catch (_com_error e)
	{
		XTRACE(_T("Warning: 连接数据库发生异常. 错误信息: %s; \n"), e.ErrorMessage());
		XTRACE(_T("%s\r\n"), GetLastErrorText());
		return FALSE;
	} 
	catch (...)
	{
		XTRACE(_T("Warning: 连接数据库时发生未知错误:"));
	}
	return FALSE;
}

/*========================================================================
	Name:	连接 SQL SERVER 数据库. 
	-----------------------------------------------------
	Params:		[dbsrc]:	SQL SERVER 服务器名.
				[dbname]:	默认的数据库名.
				[user]:		用户名.
				[pass]:		密码.
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
	Name:	连接 ACCESS 数据库. 
	-----------------------------------------------------
	Params:		[dbpath]:	MDB 数据库文件路径名.
				[pass]:		访问密码.
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
	Name:	通过 udl 文件连接数据库. 
	-----------------------------------------------------
	Params:		[strFileName]:	UDL 数据库连接文件路径名.
==========================================================================*/
BOOL CAdoConnection::OpenUDLFile(LPCTSTR strFileName, long lOptions)
{
	CString strConnect = _T("File Name=");
	strConnect += strFileName;
	return Open(LPCTSTR(strConnect), lOptions);
}
/*========================================================================
	Name:	连接 Oracle 数据库. 
	-----------------------------------------------------
	Params:		[sid]:	    Oracle服务器名.
				[user]:		用户名.
				[pass]:		密码.
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
	Name:	关闭与数据源的连接.
	-----------------------------------------------------
	Remarks: 使用 Close 方法可关闭 Connection 对象以便释放所有关联的系统资源. 
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
		XTRACE(_T("Warning: 关闭数据库发生异常. 错误信息: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
	} 
}

/*========================================================================
	Name:	关闭连接并释放对象.
	-----------------------------------------------------
	Remarks: 关闭连接并释放connection对象.
==========================================================================*/
void CAdoConnection::Release()
{
	if (IsOpen()) Close();
	m_pConnection.Release();
}

/*========================================================================
	Name:		执行指定的查询、SQL 语句、存储过程等.
    ----------------------------------------------------------
	Remarks:	请参考 CAdoRecordSet 类的Open方法. 返回的 Recordset 对象始
			终为只读、仅向前的游标.
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
		XTRACE(_T("Warning: Execute 方法发生异常. 错误信息: %s \n"), e.ErrorMessage());
        if (m_pObserver!=NULL)
        {
            m_pObserver->OnExecuteFailure();
        }
		return FALSE;
	} 
	return FALSE;
}

/*========================================================================
	Remarks:	请参考 CAdoRecordSet 类 Cancel 方法.
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
		XTRACE(_T("Warning: Cancel 方法发生异常. 错误信息: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return FALSE;
	} 
	return FALSE;
}

/*========================================================================
	Name:	取得最后发生的错误信息.
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
		XTRACE(_T("Warning: GetLastError 方法发生异常. 错误信息: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
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
		XTRACE(_T("Warning: GetErrors 方法发生异常. 错误信息: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
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
		XTRACE(_T("Warning: GetError 方法发生异常. 错误信息: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return NULL;
	} 
	return NULL;
}

/*========================================================================
	Name:		取得连接时间.
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
		XTRACE(_T("Warning: GetConnectTimeOut 方法发生异常. 错误信息: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return -1;
	} 
	return -1;
}

/*========================================================================
	Name:		设置连接时间.
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
		XTRACE(_T("Warning: SetConnectTimeOut 方法发生异常. 错误信息: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return FALSE;
	} 
}

/*========================================================================
	Name:		取得默认数据库的名称.
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
		XTRACE(_T("Warning: GetDefaultDatabase 方法发生异常. 错误信息: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return CString(_T(""));
	} 
}

/*========================================================================
	Name:		取得 Connection 对象提供者的名称.
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
		XTRACE(_T("Warning: GetProviderName 方法发生异常. 错误信息: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return CString(_T(""));
	} 
}

/*========================================================================
	Name:		取得 ADO 的版本号
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
		XTRACE(_T("Warning: GetVersion 方法发生异常. 错误信息: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return CString(_T(""));
	} 
}

/*========================================================================
	Name:		取得对象的状态(同 Recordset 对象的 GetState 方法).
	-----------------------------------------------------
	returns:	返回下列常量之一的长整型值.
		[常量]				[说明] 
		----------------------------------
		adStateClosed		指示对象是关闭的. 
		adStateOpen			指示对象是打开的. 
	-----------------------------------------------------
	Remarks:		可以随时使用 State 属性取得指定对象的当前状态.
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
		XTRACE(_T("Warning: GetState 发生异常. 错误信息: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return -1;
	} 
	return -1;
}

/*========================================================================
	Name:	检测连接对象是否为打开状态.
==========================================================================*/
BOOL CAdoConnection::IsOpen() const
{
	try
	{
		return (m_pConnection != NULL && (m_pConnection->State & adStateOpen));
	}
	catch (_com_error e)
	{
		XTRACE(_T("Warning: IsOpen 方法发生异常. 错误信息: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return FALSE;
	} 
	return FALSE;
}

/*========================================================================
	Name:		取得在 Connection 对象中修改数据的可用权限.
    ----------------------------------------------------------
	returns:	返回以下某个 ConnectModeEnum 的值.
		[常量]				 [说明] 
		----------------------------------
		adModeUnknown		 默认值. 表明权限尚未设置或无法确定. 
		adModeRead			 表明权限为只读. 
		adModeWrite			 表明权限为只写. 
		adModeReadWrite		 表明权限为读/写. 
		adModeShareDenyRead  防止其他用户使用读权限打开连接. 
		adModeShareDenyWrite 防止其他用户使用写权限打开连接. 
		adModeShareExclusive 防止其他用户打开连接. 
		adModeShareDenyNone  防止其他用户使用任何权限打开连接.
    ----------------------------------------------------------
	Remarks: 使用 Mode 属性可设置或返回当前连接上提供者正在使用的访问权限.
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
		XTRACE(_T("Warning: GetMode 发生异常. 错误信息: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return adModeUnknown;
	} 
	return adModeUnknown;
}

/*========================================================================
	Name:		设置在 Connection 中修改数据的可用权限. 请参考 GetMode 方法.
    ----------------------------------------------------------
	Remarks:	只能在关闭 Connection 对象时方可设置 Mode 属性.
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
		XTRACE(_T("Warning: SetMode 发生异常. 错误信息: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return FALSE;
	} 
	return TRUE;
}

/*========================================================================
    Name:		从数据源获取数据库信息.
	-----------------------------------------------------
	Params:		QueryType  所要运Line的模式查询类型.
	-----------------------------------------------------
	returns:	返回包含数据库信息的 Recordset 对象. Recordset 将以只读、静态
			游标打开.
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
		XTRACE(_T("Warning: OpenSchema方法发生异常. 错误信息: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return NULL;
	} 
	return NULL;
}

/*########################################################################
			  ------------------------------------------------
									事务处理
			  ------------------------------------------------
  ########################################################################*/

/*========================================================================
    Name:		开始新事务.
	-----------------------------------------------------
	returns:	对于支持嵌套事务的数据库来说, 在已打开的事务中调用 BeginTrans 
	方法将开始新的嵌套事务. 返回值将指示嵌套层次: 返回值为 1 表示已打开顶层
	事务 (即事务不被另一个事务所嵌套), 返回值为 2 表示已打开第二层事务(嵌套
	在顶层事务中的事务), 依次类推.
	-----------------------------------------------------
	Remarks:	一旦调用了 BeginTrans 方法, 在调用 CommitTrans 或 RollbackTrans
	结束事务之前, 数据库将不再立即提交所作的任何更改.
		
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
		XTRACE(_T("Warning: BeginTrans 方法发生异常. 错误信息: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return -1;
	} 
	return -1;
}

/*========================================================================
    Name:		保存任何更改并结束当前事务.
	-----------------------------------------------------
	Remarks:	调用 CommitTrans 或 RollbackTrans 只影响最新打开的事务; 在
	处理任何更高层事务之前必须关闭或回卷当前事务.
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
		XTRACE(_T("Warning: CommitTrans 方法发生异常. 错误信息: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return FALSE;
	} 
	return FALSE;
}

/*========================================================================
    Name:		取消当前事务中所作的任何更改并结束事务.
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
		XTRACE(_T("Warning: RollbackTrans 方法发生异常. 错误信息: %s; File: %s; Line: %d\n"), e.ErrorMessage(), _T(__FILE__), __LINE__);
		return FALSE;
	} 
	return FALSE;
}



void CAdoConnection::SetObserver(MAdoConnectionObserver* pObserver)
{
    ASSERT(pObserver!=NULL);
    m_pObserver = pObserver;
}
