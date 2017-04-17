// ZCTSingleWnd.cpp: implementation of the CZCTSingleWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZCTSingleWnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
CZCTSingleWnd::CZCTSingleWnd()
{

}

CZCTSingleWnd::~CZCTSingleWnd()
{
	ClearList();
}
//////////////////////////////////////////////////////////////////////


BOOL CZCTSingleWnd::ReadStationInf(CString strPath,int iReadMode)
{
	BOOL bReultValue = TRUE;
	CString strDir;
	int i;
	
	const CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	
	//单站读取模式
	int iSingStaReadMode = CZCTWnd::RDMD_SYARD | CZCTWnd::RDMD_SFRAM 
		| CZCTWnd::RDMD_DESK | CZCTWnd::RDMD_GUDAO 
		| CZCTWnd::RDMD_MASK | CZCTWnd::RDMD_JINLU;

	CZCTWnd *pZCT;
	
	switch(iReadMode) {

		//读所有站
	case RDMD_READALL:
		for ( i=0; i<pStationInf->GetLength(); i++)
		{
			pZCT = new CZCTWnd;
			pZCT->SetStationID(pStationInf->GetAt(i)->iStationID);
			
			//读数据
			if (strPath.IsEmpty()) {
				strDir = ".\\"+pStationInf->GetAt(i)->strDirectory+"\\";
			}
			else{
				strDir = strPath+pStationInf->GetAt(i)->strDirectory+"\\";
			}
			if (!pZCT->ReadStationInf(strDir,iSingStaReadMode)) {
				bReultValue = FALSE;
			}
			m_SingleStaList.AddTail(pZCT);
		}
		break;

		//读单个站
	case RDMD_ACTIVE:
		{
			pZCT = new CZCTWnd;
			
			pZCT->SetStationID(CReadStationInf::GetActiveStation());
			
			//
			if (strPath.IsEmpty()) {
				strDir = pStationInf->GetDirectory(CReadStationInf::GetActiveStation());
			}
			else{
				strDir = strPath + pStationInf->GetDirectory(CReadStationInf::GetActiveStation());
			}			
			
			if (!pZCT->ReadStationInf(strDir,iSingStaReadMode)) {
				bReultValue = FALSE;
			}
			m_SingleStaList.AddTail(pZCT);
		}
		break;
		
	}
	//
	return bReultValue;
}

void CZCTSingleWnd::ClearList()
{
	while(m_SingleStaList.GetHeadPosition())
	{
		delete m_SingleStaList.RemoveHead();
	}
}

void CZCTSingleWnd::SetShowStyle(DWORD dwNewStyle)
{
	POSITION pos = m_SingleStaList.GetHeadPosition();
	while (pos) {
		CZCTWnd *pZCT = m_SingleStaList.GetNext(pos);
		pZCT->SetZCTStyle(dwNewStyle,FALSE);
	}
}

void CZCTSingleWnd::SetOperAttribute(WORD wNewAttri)
{
	POSITION pos = m_SingleStaList.GetHeadPosition();
	while (pos) {
		CZCTWnd *pZCT = m_SingleStaList.GetNext(pos);
		pZCT->SetOperAttri(wNewAttri);
	}
}

void CZCTSingleWnd::SetMapMode(int nNewMapMode)
{
	POSITION pos = m_SingleStaList.GetHeadPosition();
	while (pos) {
		CZCTWnd *pZCT = m_SingleStaList.GetNext(pos);
		pZCT->SetZCTMapMode(nNewMapMode);
	}
}

DWORD CZCTSingleWnd::GetShowStyle()
{
	POSITION pos = m_SingleStaList.GetHeadPosition();
	while (pos) {
		CZCTWnd *pZCT = m_SingleStaList.GetNext(pos);
		return pZCT->GetZCTStyle();
	}
	return 0;
}

WORD CZCTSingleWnd::GetOperAttribute()
{
	POSITION pos = m_SingleStaList.GetHeadPosition();
	while (pos) {
		CZCTWnd *pZCT = m_SingleStaList.GetNext(pos);
		return pZCT->GetOperAttri();
	}
	return 0;
}


void CZCTSingleWnd::SetLogicSize(CSize newSize)
{
	POSITION pos = m_SingleStaList.GetHeadPosition();
	while (pos) {
		CZCTWnd *pZCT = m_SingleStaList.GetNext(pos);
		pZCT->SetLogicSize(newSize);
	}
}

CZCTWnd* CZCTSingleWnd::GetZCTbyNo(int iStationNo)
{
	POSITION POS = m_SingleStaList.GetHeadPosition();
	while ( POS ){
		CZCTWnd* pZCT = m_SingleStaList.GetNext(POS);
		if ( pZCT->GetStationID() == iStationNo ){
			return pZCT;
		}
	}

	return NULL;
}

void CZCTSingleWnd::OnReceiveInf(LPBYTE pBuffer)
{
	BYTE byFrameKind	= pBuffer[0];//帧类型
	WORD wStation;
	if (byFrameKind==BAODIANXINXI_FRAME_TYPE) {
		memcpy(&wStation,pBuffer+19,2);	
	}
	else{
		memcpy(&wStation,pBuffer+4,2);//取出站码
	}


	//----------------更新缓冲数据内容 -------------//
	CZCTWnd *pZCT  = GetZCTbyNo(wStation);//
	if ( pZCT )	{
		pZCT->OnReceiveInf(pBuffer);
	}
}

void CZCTSingleWnd::DrawStation(int iStationNo)
{
	POSITION pos = m_SingleStaList.GetHeadPosition();
	while(pos)	{
		CZCTWnd* pZCT = m_SingleStaList.GetNext(pos);
		if ( pZCT->GetStationID() == iStationNo )	{
			pZCT->ShowWindow(SW_SHOW);
		}
		else{
			pZCT->ShowWindow(SW_HIDE);
		}
	}
}

void CZCTSingleWnd::Create(CWnd *pParentWnd, HWND hMsgHandle)
{
	POSITION pos = m_SingleStaList.GetHeadPosition();
	while ( pos )
	{
		CZCTWnd * pZCT = m_SingleStaList.GetNext(pos);
		pZCT->Create(pParentWnd,NULL,hMsgHandle);		
	}
}

void CZCTSingleWnd::InvalidateInf(BOOL bNewFlag)
{
	POSITION pos = m_SingleStaList.GetHeadPosition();
	while (pos)	{
		CZCTWnd* pZCT = m_SingleStaList.GetNext(pos);
		pZCT->InvalidateInf(bNewFlag);
	}
}

void CZCTSingleWnd::HideStation()
{
	POSITION pos = m_SingleStaList.GetHeadPosition();
	while (pos)	{
		CZCTWnd* pZCT = m_SingleStaList.GetNext(pos);
		pZCT->ShowWindow(SW_HIDE);
	}
}

void CZCTSingleWnd::SetPopupMenu(HMENU hMenu, HWND hMsgHandle)
{
	POSITION pos = m_SingleStaList.GetHeadPosition();
	while (pos)	{
		CZCTWnd* pZCT = m_SingleStaList.GetNext(pos);
		pZCT->SetPopupMenu(hMenu,hMsgHandle);
	}
}

int CZCTSingleWnd::GetJLProAccordBtn(const WORD wStationID,const WORD *pBtnList, const int &iBtnNum)
{
	CZCTWnd* pZCT = GetZCTbyNo(wStationID);
	return pZCT->GetJLProAccordBtn(pBtnList,iBtnNum);
}
