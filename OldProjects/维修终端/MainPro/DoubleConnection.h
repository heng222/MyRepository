// DoubleConnection.h: interface for the CDoubleConnection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOUBLECONNECTION_H__2486035C_0EFB_409E_A031_8DDA5B0C400C__INCLUDED_)
#define AFX_DOUBLECONNECTION_H__2486035C_0EFB_409E_A031_8DDA5B0C400C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ConnectionManage.h"

class CDoubleConnection  
{
public:
	CDoubleConnection();
	virtual ~CDoubleConnection();
public:
	CString getConnectString();
	void SetServerState(bool bServer);
	void SetSmartAddressing(bool bSmartAddressing);	// Set Smart addressing mode
	void CloseComm();		// Close Socket
	void StopComm();		// Stop Socket thread
	DWORD WriteCommDetail(BYTE Buffertype, BYTE BufferVersion, const LPBYTE lpBuffer, DWORD dwCount, DWORD dwTimeout);
	DWORD WriteComm(BYTE Buffertype, BYTE BufferVersion, const LPBYTE lpBuffer, DWORD dwCount, DWORD dwTimeout);
	DWORD WriteComm(LPBYTE lpBuffer, DWORD dwCount, DWORD dwTimeout);
	CString m_strSIPM1;
	CString m_strSPortM1;
	CString m_strSIPB1;
	CString m_strSPortB1;
	CString m_strCIPM;
	CString m_strCPortM;
	CString m_strCIPB;
	CString m_strCPortB;
	CString m_strClientName;
	CString m_strServerName;
	CString m_strSIPM2;
	CString m_strSPortM2;
	CString m_strSIPB2;
	CString m_strSPortB2;
	CConnectionManage m_connect1;
	CConnectionManage m_connect2;

	bool IsOpen() ;	// Is Socket valid?
	bool IsOpenB2B() ;	// Is Socket valid?
	bool IsOpenB2M() ;	// Is Socket valid?
	bool IsOpenM2B() ;	// Is Socket valid?
	bool IsOpenM2M() ;	// Is Socket valid?
	bool ConnectTo(LPCTSTR strSipM1, LPCTSTR strSportM1,
					LPCTSTR strSipB1, LPCTSTR strSportB1,
					LPCTSTR strSipM2, LPCTSTR strSportM2,
					LPCTSTR strSipB2, LPCTSTR strSportB2,
					LPCTSTR strCipM, LPCTSTR strCportM,
					LPCTSTR strCipB, LPCTSTR strCportB,
					int nProtocol, int nType);
	bool IniConnectTo(int nProtocol, int nType);

	void SetMessageWindow(CWnd* pMsgView);
	void SetMessageWnd(CWnd* pMsgWnd);

	static UINT WINAPI ConnectionCheckThreadProc(LPVOID pParam);
};

#endif // !defined(AFX_DOUBLECONNECTION_H__2486035C_0EFB_409E_A031_8DDA5B0C400C__INCLUDED_)
