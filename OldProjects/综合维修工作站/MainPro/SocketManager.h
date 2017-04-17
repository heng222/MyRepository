// SocketManager.h: interface for the CSocketManager class.
//
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_SOCKETMANAGER_H__7403BD71_338A_4531_BD91_3D7E5B505793__INCLUDED_)
#define AFX_SOCKETMANAGER_H__7403BD71_338A_4531_BD91_3D7E5B505793__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SocketComm.h"

#define WM_UPDATE_CONNECTION	WM_APP+0x1234
#define WM_SOCKETGETCHAR	WM_APP+0x1235
#define WM_CTCRECEIVE	WM_APP+0x1236

struct stMessageProxy
{
  SockAddrIn address;
  BYTE byData[BUFFER_SIZE];
};

class CSocketManager : public CSocketComm  
{
public:
	CSocketManager();
	virtual ~CSocketManager();

	void SetMessageWindow(CWnd* m_pMsgView);
	void SetMessageWnd(CWnd* pMsgWnd);
	void AppendMessage(LPCTSTR strText );
public:
	CString getConnectString();

	virtual void OnDataReceived(const LPBYTE lpBuffer, DWORD dwCount);
	virtual void OnEvent(UINT uEvent);

protected:
	void DisplayData(const LPBYTE lpData, DWORD dwCount, const SockAddrIn& sfrom);
	CWnd* m_pMsgView;
	CWnd* m_pMsgWnd;
};

#endif // !defined(AFX_SOCKETMANAGER_H__7403BD71_338A_4531_BD91_3D7E5B505793__INCLUDED_)
