#if !defined(AFX_ZCTMULTIWND_H__D6975AA2_0970_448B_B41B_69E24E037483__INCLUDED_)
#define AFX_ZCTMULTIWND_H__D6975AA2_0970_448B_B41B_69E24E037483__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZCTMultiWnd.h : header file
//
#include "ZCTWnd.h"

/////////////////////////////////////////////////////////////////////////////
//多站窗口
// CZCTMultiWnd window

class CZCTMultiWnd : public CWnd
{
// Construction
public:
	enum ReadMode//读取模式
	{
		RM_ALLSTATN,	/*读所有站*/
		RM_NEIGHBOR,	/*读相邻两站*/
		RM_JIANCHE		//读监测中大屏数据
	};

	enum CanvasSize//大屏尺寸
	{
		CS_WIDTH  = 1280/**/,
		CS_HEIGHT = 1024/**/
	};
	CZCTMultiWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZCTMultiWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetPopupMenu(HMENU hMenu, HWND hMsgHandle);
	void	InvalidateInf(BOOL bNewFlag);
	int		GetZCTMapMode();
	void	SetZCTMapMode(int nMapMode);
	DWORD	GetZCTStyle();
	void	SetZCTStyle(DWORD dwStyle);
	CZCTWnd* GetZCTbyNo(int iStationNo);
	void	OnReceiveInf(LPBYTE pBuffer);
	void	ClearList();
	BOOL	ReadStationInf(int iReadMode,int iStationID=-1);
	BOOL	Create(CWnd* pParentWnd);
	virtual ~CZCTMultiWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CZCTMultiWnd)
	afx_msg void OnPaint();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	/*
	 *	多站场图数据
	 */
	CZCTWndList		m_MultiStaList;
	/*
	 *	
	 */
	CMenu	m_StationMenu;
	/*
	 *	
	 */
	HWND	m_hPMHandle;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZCTMULTIWND_H__D6975AA2_0970_448B_B41B_69E24E037483__INCLUDED_)
