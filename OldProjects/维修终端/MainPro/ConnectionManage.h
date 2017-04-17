// ConnectionManage.h: interface for the CConnectionManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECTIONMANAGE_H__84D567D6_9FA8_4739_AAF1_A07D8705BEC7__INCLUDED_)
#define AFX_CONNECTIONMANAGE_H__84D567D6_9FA8_4739_AAF1_A07D8705BEC7__INCLUDED_

#include "SocketManager.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMessageItem :public CObject
{
public:
	BYTE lpBuffer[BUFFER_SIZE];
	DWORD dwCount;
	BYTE Buffertype;
	BYTE BufferVersion;
	DWORD dwTimeout;
	CString strIPM;
	CString strIPB;
	int nSendCount;
	CMessageItem();
	virtual ~CMessageItem();
	CMessageItem& operator=(const CMessageItem& mi) ;

};

class CConnectionManage 
{
public:
	CString getConnectString();
	void SetServerState(bool bServer);
	void SetSmartAddressing(bool bSmartAddressing);	// Set Smart addressing mode
	void CloseComm();		// Close Socket
	void StopComm();		// Stop Socket thread
	DWORD WriteCommDetail(BYTE Buffertype, BYTE BufferVersion, const LPBYTE lpBuffer, DWORD dwCount, DWORD dwTimeout);
	DWORD WriteComm(BYTE Buffertype, BYTE BufferVersion, const LPBYTE lpBuffer, DWORD dwCount, DWORD dwTimeout);
	CString m_strSIPM;
	CString m_strSPortM;
	CString m_strSIPB;
	CString m_strSPortB;
	CString m_strCIPM;
	CString m_strCPortM;
	CString m_strCIPB;
	CString m_strCPortB;
	CString m_strClientName;
	CString m_strServerName;
	bool m_bRun;  //bool for run flag
	CSocketManager m_connectB2B;
	CSocketManager m_connectB2M;
	CSocketManager m_connectM2B;
	CSocketManager m_connectM2M;
	CConnectionManage();
	virtual ~CConnectionManage();
	HANDLE		m_hThread;		// Thread Comm handle
	HANDLE		m_hSendThread;		// Thread Comm handle
	HANDLE		m_hCloseEvent;

	bool IsOpen() ;	// Is Socket valid?
	bool IsOpenB2B() ;	// Is Socket valid?
	bool IsOpenB2M() ;	// Is Socket valid?
	bool IsOpenM2B() ;	// Is Socket valid?
	bool IsOpenM2M() ;	// Is Socket valid?
	bool ConnectTo(LPCTSTR strSipM, LPCTSTR strSportM,
					LPCTSTR strSipB, LPCTSTR strSportB,
					LPCTSTR strCipM, LPCTSTR strCportM,
					LPCTSTR strCipB, LPCTSTR strCportB,
					int nProtocol, int nType);

	bool SingleConnectTo(CSocketManager * pManager ,LPCTSTR strSip, LPCTSTR strSport,
						LPCTSTR strCip, LPCTSTR strCport,
					int nProtocol, int nType);

	bool WatchConnect();
	void ConnectionCheck();
	void SetMessageWindow(CWnd* pMsgView);
	void SetMessageWnd(CWnd* pMsgWnd);
	CObList sendList;
	CObList receiveList;

	CMessageItem* getFirstSendMessage();
	void addSendMessage(CMessageItem* messageItem, bool bTail = true);
	CMessageItem* getFirstReceiveMessage();
	void addReceiveMessage(CMessageItem* messageItem);



	static UINT WINAPI ConnectionCheckThreadProc(LPVOID pParam);
	static UINT WINAPI SendCheckThreadProc(LPVOID pParam);
	static UINT WINAPI ReceiveCheckThreadProc(LPVOID pParam);
	void SendCheck();
	void ReceiveCheck();


	void  unlockSemaphore();
	void  lockSemaphore();
	void  waitSemaphore();
	CSingleLock* SingleLock;
	CSemaphore* Semaphore;

};

#endif // !defined(AFX_CONNECTIONMANAGE_H__84D567D6_9FA8_4739_AAF1_A07D8705BEC7__INCLUDED_)
