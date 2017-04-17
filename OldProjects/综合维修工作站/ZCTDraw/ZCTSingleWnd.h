// ZCTSingleWnd.h: interface for the CZCTSingleWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZCTSINGLEWND_H__9F3F2F45_57FC_4246_8D1D_4C68A76DC2D9__INCLUDED_)
#define AFX_ZCTSINGLEWND_H__9F3F2F45_57FC_4246_8D1D_4C68A76DC2D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ZCTWnd.h"
#include "ReadStationInf.h"

class AFX_EXT_CLASS CZCTSingleWnd : public CObject  
{
//
public:
	enum _ReadMode{
		RDMD_READALL,	//全部读取
		RDMD_ACTIVE		//激活的站
	};
	CZCTSingleWnd();
	virtual ~CZCTSingleWnd();
	void	ClearList();
	
//
public:
	void	HideStation();
	void	InvalidateInf(BOOL bNewFlag);
	
	
	void	OnReceiveInf(LPBYTE pBuffer);
	CZCTWnd* GetZCTbyNo(int iStationNo);
	
	
	BOOL	ReadStationInf(CString strPath,int iReadMode=RDMD_READALL);
	void	Create(CWnd *pParentWnd,HWND hMsgHandle);

	/*
	 *	
	 */
	void	DrawStation(int iStationNo);

public:
	int		GetJLProAccordBtn(const WORD wStationID,const WORD *pBtnList, const int &iBtnNum);
	WORD	GetOperAttribute();
	DWORD	GetShowStyle();
	void	SetLogicSize(CSize newSize);
	void	SetPopupMenu(HMENU hMenu, HWND hMsgHandle);
	void	SetMapMode(int nNewMapMode);
	void	SetOperAttribute(WORD wNewAttri);
	void	SetShowStyle(DWORD dwNewStyle);
//
private:
	CZCTWndList m_SingleStaList;
};

#endif // !defined(AFX_ZCTSINGLEWND_H__9F3F2F45_57FC_4246_8D1D_4C68A76DC2D9__INCLUDED_)
