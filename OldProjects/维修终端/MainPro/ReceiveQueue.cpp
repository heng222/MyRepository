// ReceiveQueue.cpp: implementation of the CReceiveQueue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReceiveQueue.h"
#include "MainFrm.h"
#include <process.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReceiveQueue::CReceiveQueue()
{
	m_bRun = false;
	m_hThread = NULL;
	m_hCloseEvent = NULL;
	Semaphore = new CSemaphore(1,1);
	SingleLock = new CSingleLock(Semaphore);
}

CReceiveQueue::~CReceiveQueue()
{
	StopWatch();
	delete SingleLock;
	delete Semaphore;
}


void CReceiveQueue::StopWatch()
{
	m_bRun = false;
	// Kill Thread
	if (m_hThread != NULL)
	{
		SetEvent(m_hCloseEvent);
		if (WaitForSingleObject(m_hThread, 30L) == WAIT_TIMEOUT)
			TerminateThread(m_hThread, 30L);
		CloseHandle(m_hThread);
		m_hThread = NULL;
		CloseHandle(m_hCloseEvent);
		m_hCloseEvent = NULL;
	}
	
	while (!receiveList.IsEmpty())
	{
		CMessageItem * item  = (CMessageItem *)receiveList.RemoveHead();
		if (item != NULL)
			delete item;
	}

}

void CReceiveQueue::SetMessageWindow(CWnd* pMsgView)
{
	m_pMsgView = pMsgView;
}

void CReceiveQueue::SetMessageWnd(CWnd* pMsgWnd)
{
	m_pMsgWnd = pMsgWnd;
}

bool CReceiveQueue::WatchCheck()
{
		m_hCloseEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
		if (m_hCloseEvent == NULL)
		{
			return false;
		}
		m_bRun = true;
		HANDLE hThread;
		UINT uiThreadId = 0;
		hThread = (HANDLE)_beginthreadex(NULL,	// Security attributes
								  0,	// stack
    		ReceiveCheckThreadProc,	// Thread proc
								this,	// Thread param
					CREATE_SUSPENDED,	// creation mode
						&uiThreadId);	// Thread ID
//		TRACE("hThread WatchConnect %d %d", hThread, this);

		if ( NULL != hThread)
		{
			//SetThreadPriority(hThread, THREAD_PRIORITY_HIGHEST);
			ResumeThread( hThread );
			m_hThread = hThread;
//				return true;
		}

	return false;
}


CMessageItem* CReceiveQueue::getFirstReceiveMessage()
{
	CMessageItem* mi = NULL;
	lockSemaphore();
	if (receiveList.IsEmpty())
	{
		return NULL;
	}
	else
	{
		POSITION point,currentPoint;
		point = receiveList.GetHeadPosition();
		currentPoint = point;
		mi = (CMessageItem *)receiveList.GetNext(point);
		if (mi != NULL)
		{
			receiveList.RemoveAt(currentPoint);
		}
		unlockSemaphore();
		return mi;
	}
	unlockSemaphore();
	return NULL;
}

void CReceiveQueue::addReceiveMessage(CMessageItem* messageItem, bool bTail)
{
	if(messageItem != NULL)
	{
		CMessageItem * miInsert = new CMessageItem();
		*miInsert = *messageItem;
		miInsert->nSendCount = miInsert->nSendCount + 1;
		if (miInsert->nSendCount <= 20)
		{
			lockSemaphore();
			if(bTail){
				receiveList.AddTail(miInsert);
			}else{
				receiveList.AddHead(miInsert);
			}
			unlockSemaphore();
		}
	}
}



UINT WINAPI CReceiveQueue::ReceiveCheckThreadProc(LPVOID pParam)
{
	CReceiveQueue* pThis = reinterpret_cast<CReceiveQueue*>( pParam );
	_ASSERTE( pThis != NULL );

	pThis->ReceiveCheck();

	return 1L;
} // end SocketThreadProc


void CReceiveQueue::AppendMessage(LPCTSTR strText, int nMessageType )
{


	if (NULL == m_pMsgWnd)
		return;

	CString strTextMain = strText;

}

void CReceiveQueue::ReceiveCheck() 
{	
	while (m_bRun == true)
	{
		while (!receiveList.IsEmpty())
		{
			CMessageItem* mi = getFirstReceiveMessage();
			if (mi != NULL)
			{
				if (m_pMsgView != NULL)
				{
					memcpy(((CMainFrame*)m_pMsgView)->BufferTmp, mi->lpBuffer, mi->dwCount);
					((CMainFrame*)m_pMsgView)->OnReceive();
				}

				delete mi;
			}
			Sleep(0);
		}
		WaitForSingleObject(m_hCloseEvent, 1L);
		//Sleep(0);
	}
}


void CReceiveQueue::waitSemaphore()
{
	while(this->SingleLock->IsLocked())
	{
		WaitForSingleObject(m_hCloseEvent, 1L);
	}
}

void CReceiveQueue::lockSemaphore()
{	
	if(this->SingleLock->IsLocked())
	{
		waitSemaphore();
	}
	this->SingleLock->Lock();
}

void CReceiveQueue::unlockSemaphore()
{
	this->SingleLock->Unlock();
}

