// ReceiveQueue.h: interface for the CReceiveQueue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECEIVEQUEUE_H__28913A56_A1B4_4D39_9BEF_2CE5EEC89318__INCLUDED_)
#define AFX_RECEIVEQUEUE_H__28913A56_A1B4_4D39_9BEF_2CE5EEC89318__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ConnectionManage.h"

class CReceiveQueue  
{
public:
	CReceiveQueue();
	virtual ~CReceiveQueue();

	bool WatchCheck();

	void SetMessageWindow(CWnd* pMsgView);
	void SetMessageWnd(CWnd* pMsgWnd);
	CWnd* m_pMsgView;
	CWnd* m_pMsgWnd;
	CObList receiveList;

	bool m_bRun;
	HANDLE m_hThread;
	HANDLE m_hCloseEvent;

	CMessageItem* getFirstReceiveMessage();
	void addReceiveMessage(CMessageItem* messageItem, bool bTail = TRUE);
	void StopWatch();
	void AppendMessage(LPCTSTR strText, int nMessageType );

	static UINT WINAPI ReceiveCheckThreadProc(LPVOID pParam);
	void ReceiveCheck();

	void  unlockSemaphore();
	void  lockSemaphore();
	void  waitSemaphore();
	CSingleLock* SingleLock;
	CSemaphore* Semaphore;
};

#endif // !defined(AFX_RECEIVEQUEUE_H__28913A56_A1B4_4D39_9BEF_2CE5EEC89318__INCLUDED_)
