// DoubleConnection.cpp: implementation of the CDoubleConnection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DoubleConnection.h"

#include <atlconv.h>
#include <process.h>
#include "ini.h"
#include "Maintain.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
extern CMaintainApp theApp;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDoubleConnection::CDoubleConnection()
{
	m_strSIPM1 = "";
	m_strSPortM1 = "";
	m_strSIPB1 = "";
	m_strSPortB1 = "";
	m_strSIPM2 = "";
	m_strSPortM2 = "";
	m_strSIPB2 = "";
	m_strSPortB2 = "";
	m_strCIPM = "";
	m_strCPortM = "";
	m_strCIPB = "";
	m_strCPortB = "";
	m_strClientName = "";
	m_strServerName = "";

}

CDoubleConnection::~CDoubleConnection()
{
	CloseComm();
	StopComm();

}

bool CDoubleConnection::IsOpen()
{
	return (m_connect1.IsOpen()||m_connect2.IsOpen());
}


bool CDoubleConnection::ConnectTo(LPCTSTR strSipM1, LPCTSTR strSportM1,
				LPCTSTR strSipB1, LPCTSTR strSportB1,
				LPCTSTR strSipM2, LPCTSTR strSportM2,
				LPCTSTR strSipB2, LPCTSTR strSportB2,
				LPCTSTR strCipM, LPCTSTR strCportM,
				LPCTSTR strCipB, LPCTSTR strCportB,
				int nProtocol, int nType)
{
		m_strSIPM1  = strSipM1;
		m_strSPortM1 =strSportM1;
		m_strSIPB1= strSipB1;
		m_strSPortB1 =strSportB1;
		m_strSIPM2  = strSipM2;
		m_strSPortM2 =strSportM2;
		m_strSIPB2= strSipB2;
		m_strSPortB2 =strSportB2;
		m_strCIPM =strCipM;
		m_strCPortM =strCportM;
		m_strCIPB =strCipB;
		m_strCPortB =strCportB;

		bool bsuccess1 = m_connect1.ConnectTo(m_strSIPM1,m_strSPortM1,m_strSIPB1,m_strSPortB1,m_strCIPM,m_strCPortM,m_strCIPB,m_strCPortB,nProtocol,nType);
		Sleep(50);
		bool bsuccess2 = m_connect2.ConnectTo(m_strSIPM2,m_strSPortM2,m_strSIPB2,m_strSPortB2,m_strCIPM,m_strCPortM,m_strCIPB,m_strCPortB,nProtocol,nType);
		Sleep(50);
		return (bsuccess1||bsuccess2);
}


bool CDoubleConnection::IniConnectTo(int nProtocol, int nType)
{
		CIniReader iniFile(theApp.m_strExePath+"ini\\ip.ini");
		m_strSIPM1 = iniFile.getKeyValue("ip1","server1");
		m_strSIPB1 = iniFile.getKeyValue("ip2","server1");
		m_strSPortM1 = iniFile.getKeyValue("port1","server1");
		m_strSPortB1 = iniFile.getKeyValue("port2","server1");
		m_strSIPM2 = iniFile.getKeyValue("ip1","server2");
		m_strSIPB2 = iniFile.getKeyValue("ip2","server2");
		m_strSPortM2 = iniFile.getKeyValue("port1","server2");
		m_strSPortB2 = iniFile.getKeyValue("port2","server2");
		m_strCIPM =iniFile.getKeyValue("ip1","client");
		m_strCIPB = iniFile.getKeyValue("ip2","client");
		m_strCPortM =iniFile.getKeyValue("port1","client");
		m_strCPortB =iniFile.getKeyValue("port2","client");

		bool bsuccess1 = m_connect1.ConnectTo(m_strSIPM1,m_strSPortM1,m_strSIPB1,m_strSPortB1,m_strCIPM,m_strCPortM,m_strCIPB,m_strCPortB,nProtocol,nType);
		Sleep(50);
		bool bsuccess2 = m_connect2.ConnectTo(m_strSIPM2,m_strSPortM2,m_strSIPB2,m_strSPortB2,m_strCIPM,m_strCPortM,m_strCIPB,m_strCPortB,nProtocol,nType);
		Sleep(50);
		return (bsuccess1||bsuccess2);
}

DWORD CDoubleConnection::WriteComm(BYTE Buffertype, BYTE BufferVersion, const LPBYTE lpBuffer, DWORD dwCount, DWORD dwTimeout)
{
	return WriteCommDetail(Buffertype,BufferVersion,lpBuffer, dwCount, dwTimeout);
}

DWORD CDoubleConnection::WriteComm(LPBYTE lpBuffer, DWORD dwCount, DWORD dwTimeout)
{
	return WriteCommDetail(*lpBuffer,*(lpBuffer+1),lpBuffer+4, dwCount, dwTimeout);
}

void CDoubleConnection::SetServerState(bool bServer)
{
	m_connect1.SetServerState(bServer);
	m_connect2.SetServerState(bServer);
}

void CDoubleConnection::SetSmartAddressing(bool bSmartAddressing)	// Set Smart addressing mode
{
	m_connect1.SetSmartAddressing(bSmartAddressing);
	m_connect2.SetSmartAddressing(bSmartAddressing);
}

void CDoubleConnection::CloseComm()
{
	m_connect1.CloseComm();
	m_connect2.CloseComm();
}


void CDoubleConnection::StopComm()
{
	m_connect1.StopComm();
	m_connect2.StopComm();
}

void CDoubleConnection::SetMessageWindow(CWnd* pMsgView)
{
	m_connect1.SetMessageWindow(pMsgView);
	m_connect2.SetMessageWindow(pMsgView);
}

void CDoubleConnection::SetMessageWnd(CWnd* pMsgWnd)
{
	m_connect1.SetMessageWnd(pMsgWnd);
	m_connect2.SetMessageWnd(pMsgWnd);
}

DWORD CDoubleConnection::WriteCommDetail(BYTE Buffertype, BYTE BufferVersion, const LPBYTE lpBuffer, DWORD dwCount, DWORD dwTimeout)
{
	bool bSuccess = TRUE;
	int nCount = 0;
	if (m_connect1.IsOpen())
	{
		nCount = m_connect1.WriteComm(Buffertype,BufferVersion,lpBuffer, dwCount, dwTimeout);
	}
	if (m_connect2.IsOpen())
	{
		nCount = m_connect2.WriteComm(Buffertype,BufferVersion,lpBuffer, dwCount, dwTimeout);
	}
	return nCount;
}

CString CDoubleConnection::getConnectString()
{
	/*
	CString strReturn;
	strReturn = "";
	if (IsOpenB2B())
	{
		strReturn = strReturn + "b-b:" + m_connectB2B.getConnectString()+"\r\n";
	}
	if (IsOpenB2M())
	{
		strReturn = strReturn + "b-m:" + m_connectB2M.getConnectString()+"\r\n";
	}
	if (IsOpenM2B())
	{
		strReturn = strReturn + "m-b:" + m_connectM2B.getConnectString()+"\r\n";
	}
	if (IsOpenM2M())
	{
		strReturn = strReturn + "m-m:" + m_connectM2M.getConnectString()+"\r\n";
	}
	return strReturn;
	*/
	return "";
}

