// ZCTMag1.cpp : implementation file
//

#include "stdafx.h"
#include "ZCTMag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZCTMag


CZCTMag::CZCTMag()
{
	//确定系统当前路径
	//char cTemp[MAX_PATH];
	
	//GetCurrentDirectory(MAX_PATH,cTemp);
	//m_strExePath.Format("%s\\",cTemp);
}

CZCTMag::~CZCTMag()
{
	CReadStationInf::ReleaseInstance();
}

void CZCTMag::ClearStaList()
{
	m_SingleStationWnd.ClearList();
	m_MultiStationWnd.ClearList();
}


/////////////////////////////////////////////////////////////////////////////
// CZCTMag message handlers

void CZCTMag::OnReceive(BYTE *pBuffer)
{
	m_SingleStationWnd.OnReceiveInf(pBuffer);
	m_MultiStationWnd.OnReceiveInf(pBuffer);
}

void CZCTMag::DrawStation(int iStationNo/*=-1*/)
{
	if (iStationNo!=-1) {
		m_SingleStationWnd.DrawStation(iStationNo);
	}
	else{
		m_MultiStationWnd.ShowWindow(SW_SHOW);
	}
}

BOOL CZCTMag::ReadStationInf(int iReadMode,CString strPath)
{
	ClearStaList();

	//
	BOOL bReultValue = TRUE;
	CString strDir;
	
	//const CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	
	//
	DWORD dwShowStyle;
	WORD wOperAttri;
	switch(iReadMode)
	{
		
/* -------- 中心各工作站 -------　*/
	case MODE_DAPING:/*大屏*/
		if (!m_MultiStationWnd.ReadStationInf(CZCTMultiWnd::RM_ALLSTATN,strPath)) {
			return FALSE;
		}
		break;


	case MODE_KONGZHI:/*控制工作站*/
		//读大屏数据
		if (!m_MultiStationWnd.ReadStationInf(CZCTMultiWnd::RM_ALLSTATN,strPath) ) {
			bReultValue = FALSE;
		}

		//读单站数据
		bReultValue = m_SingleStationWnd.ReadStationInf(strPath);
		wOperAttri = m_SingleStationWnd.GetOperAttribute();
		wOperAttri |= CZCTWnd::OPER_FRAMETRANO;
		wOperAttri |= CZCTWnd::OPER_DAOCHABTN;
		wOperAttri |= CZCTWnd::OPER_DIAOCHENAN;
		wOperAttri |= CZCTWnd::OPER_LIECHEBTN;
		m_SingleStationWnd.SetOperAttribute(wOperAttri);
		break;
		
		
	case MODE_ZHUDIAO:/*助调工作站*/
		//读大屏数据
		if (!m_MultiStationWnd.ReadStationInf(CZCTMultiWnd::RM_ALLSTATN,strPath) ) {
			bReultValue = FALSE;
		}
		
		//读单站数据
		bReultValue = m_SingleStationWnd.ReadStationInf(strPath);
		//
		wOperAttri = m_SingleStationWnd.GetOperAttribute();
		wOperAttri |= CZCTWnd::OPER_DAOCHABTN;
		wOperAttri |= CZCTWnd::OPER_DIAOCHENAN;
		m_SingleStationWnd.SetOperAttribute(wOperAttri);
		//
		dwShowStyle = m_SingleStationWnd.GetShowStyle();
		dwShowStyle &= ~CZCTWnd::SHOW_LIECHEBTN;
		m_SingleStationWnd.SetShowStyle(dwShowStyle);
		break;	


	case MODE_ZONGHEWEIXIU:/*综合维修工作站*/
		//读大屏数据
		if (!m_MultiStationWnd.ReadStationInf(CZCTMultiWnd::RM_ALLSTATN,strPath) ) {
			bReultValue = FALSE;
		}

		//读单站数据
		bReultValue = m_SingleStationWnd.ReadStationInf(strPath);
		dwShowStyle = m_SingleStationWnd.GetShowStyle();
		dwShowStyle &= ~CZCTWnd::SHOW_LIECHEBTN;
		dwShowStyle &= ~CZCTWnd::SHOW_DIAOCHEAN;
		m_SingleStationWnd.SetShowStyle(dwShowStyle);
		break;


	case MODE_DIANWUWEIHU:/*电务维护*/
		//读大屏数据
		if (!m_MultiStationWnd.ReadStationInf(CZCTMultiWnd::RM_ALLSTATN,strPath) ) {
			bReultValue = FALSE;
		}
		//读单站数据
		bReultValue = m_SingleStationWnd.ReadStationInf(strPath);
		dwShowStyle = m_SingleStationWnd.GetShowStyle();
		dwShowStyle &= ~CZCTWnd::SHOW_LIECHEBTN;
		dwShowStyle &= ~CZCTWnd::SHOW_DIAOCHEAN;
		m_SingleStationWnd.SetShowStyle(dwShowStyle);
		//
		m_SingleStationWnd.SetOperAttribute(m_SingleStationWnd.GetOperAttribute() & ~CZCTWnd::OPER_FUNCTNBTN);
		break;


	case MODE_JIANCEZHANJI://监测站机
		//读大屏数据
		if (!m_MultiStationWnd.ReadStationInf(CZCTMultiWnd::RM_NEIGHBOR,strPath) ) {
			bReultValue = FALSE;
		}
		//读单站数据
		bReultValue = m_SingleStationWnd.ReadStationInf(strPath,CZCTSingleWnd::RDMD_ACTIVE);
		dwShowStyle = m_SingleStationWnd.GetShowStyle();
		dwShowStyle &= ~CZCTWnd::SHOW_LIECHEBTN;
		dwShowStyle &= ~CZCTWnd::SHOW_DIAOCHEAN;
		m_SingleStationWnd.SetShowStyle(dwShowStyle);
		//
		m_SingleStationWnd.SetOperAttribute(m_SingleStationWnd.GetOperAttribute() & ~CZCTWnd::OPER_FUNCTNBTN);
		m_SingleStationWnd.SetMapMode(MM_TEXT);
		break;


	case MODE_JIANCEZONGDUAN://监测终端
		//读大屏数据
		if (!m_MultiStationWnd.ReadStationInf(CZCTMultiWnd::RM_ALLSTATN,strPath) ) {
			bReultValue = FALSE;
		}
		//读单站数据
		bReultValue = m_SingleStationWnd.ReadStationInf(strPath);
		dwShowStyle = m_SingleStationWnd.GetShowStyle();
		dwShowStyle &= ~CZCTWnd::SHOW_LIECHEBTN;
		dwShowStyle &= ~CZCTWnd::SHOW_DIAOCHEAN;
		m_SingleStationWnd.SetShowStyle(dwShowStyle);
		//
		m_SingleStationWnd.SetOperAttribute(m_SingleStationWnd.GetOperAttribute() & ~CZCTWnd::OPER_FUNCTNBTN);
		//
		m_SingleStationWnd.SetLogicSize(CSize(1050,780));
		break;

		
/* -------- 自律机 --------------*/
	case MODE_ZILVJI:
		break;
		

/* ------- 各终端工作站 ------- */
		//车务终端
	case MODE_CHEWUZONGDUAN:
		//读单站数据
		bReultValue = m_SingleStationWnd.ReadStationInf(strPath,CZCTSingleWnd::RDMD_ACTIVE);
		//
		dwShowStyle = m_SingleStationWnd.GetShowStyle();
		dwShowStyle &= ~CZCTWnd::SHOW_POPMENU;
		m_SingleStationWnd.SetShowStyle(dwShowStyle);
		//
		wOperAttri = m_SingleStationWnd.GetOperAttribute();
		wOperAttri |= CZCTWnd::OPER_DAOCHABTN;
		wOperAttri |= CZCTWnd::OPER_DIAOCHENAN;
		wOperAttri |= CZCTWnd::OPER_FRAMETRANO;
		m_SingleStationWnd.SetOperAttribute(wOperAttri);
		
		//-------读多站数据---------
		if (!m_MultiStationWnd.ReadStationInf(CZCTMultiWnd::RM_NEIGHBOR,strPath)) {
			bReultValue = FALSE;
		}
		break;
		
		//维修终端
	case MODE_WEIXIUZONGDUAN:
		//电务维护终端
	case MODE_WEIHUZONGDUAN:
		//读单站数据
		{
			m_SingleStationWnd.ReadStationInf(strPath,CZCTSingleWnd::RDMD_ACTIVE);
			//
			dwShowStyle = m_SingleStationWnd.GetShowStyle();
			dwShowStyle &= ~CZCTWnd::SHOW_POPMENU;
			dwShowStyle &= ~CZCTWnd::SHOW_DIAOCHEAN;
			dwShowStyle &= ~CZCTWnd::SHOW_LIECHEBTN;
			m_SingleStationWnd.SetShowStyle(dwShowStyle);
			//
			wOperAttri = m_SingleStationWnd.GetOperAttribute();
			wOperAttri &= ~CZCTWnd::OPER_FUNCTNBTN;
			m_SingleStationWnd.SetOperAttribute(wOperAttri);
			
		}
		break;
	}
	//
	return bReultValue;
}


void CZCTMag::Create(CWnd *pParentWnd,HWND hMsgHandle,BOOL bSingle/* = FALSE*/)
{
	//根据bSingle创建指定的车次框
	if (!bSingle) {
		m_MultiStationWnd.Create(pParentWnd);
	}
	else{
		m_SingleStationWnd.Create(pParentWnd,hMsgHandle);
	}
	
}

//////////////////////////////////////////////////////////////////////////
//Show style implement


void CZCTMag::InvalidateInf(BOOL bNewFlag)
{
	m_SingleStationWnd.InvalidateInf(bNewFlag);
	m_MultiStationWnd.InvalidateInf(bNewFlag);
}

CString CZCTMag::GetWcQDNameByID(int iStationID, int iWcQdID)
{
	CZCTWnd* pZCT = m_SingleStationWnd.GetZCTbyNo(iStationID);
	if (pZCT) {
		return pZCT->GetWcQdNameByID(iWcQdID);
	}
	//
	return "";
}

int CZCTMag::GetWcQdIDByName(int iStationID, CString strWcQdName)
{
	CZCTWnd* pZCTWnd = m_SingleStationWnd.GetZCTbyNo(iStationID);
	if (pZCTWnd) {
		return pZCTWnd->GetWcQdIDByName(strWcQdName);
	}
	return 0;
}

int CZCTMag::GetBtnIDbyName(int iStationID, CString strName)
{
	CZCTWnd* pZCTWnd = m_SingleStationWnd.GetZCTbyNo(iStationID);
	if (pZCTWnd) {
		return pZCTWnd->GetBtnIDByName(strName);
	}
	return 0;
}

CString CZCTMag::GetBtnNameByID(int iStationID, int iCommandID)
{
	CZCTWnd* pZCTWnd = m_SingleStationWnd.GetZCTbyNo(iStationID);
	if (pZCTWnd) {
		return pZCTWnd->GetBtnNameByID(iCommandID);
	}
	return "";
}

void CZCTMag::GetWcQdNameList(int iStationID, CStringList &sNameList)
{
	CZCTWnd* pZCTWnd = m_SingleStationWnd.GetZCTbyNo(iStationID);
	if (pZCTWnd) {
		pZCTWnd->GetWcQdNameList(sNameList);
	}
}

void CZCTMag::HideStation(BOOL bSingle)
{
	if (bSingle) {
		m_SingleStationWnd.HideStation();
	}
	else{
		m_MultiStationWnd.ShowWindow(SW_HIDE);
	}
}

void CZCTMag::SetPopupMenu(HMENU hMenu, HWND hMsgHandle)
{
	m_SingleStationWnd.SetPopupMenu(hMenu,hMsgHandle);
	m_MultiStationWnd.SetPopupMenu(hMenu,hMsgHandle);
}

int CZCTMag::GetJLProAccordBtn(const WORD wStationID, const WORD *pBtnList, const int &iBtnNum)
{
	return m_SingleStationWnd.GetJLProAccordBtn(wStationID,pBtnList, iBtnNum);
}
