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

int CZCTMag::m_iObjectNum = 0;

CZCTMag::CZCTMag()
{
	//ȷ��ϵͳ��ǰ·��
	char cTemp[MAX_PATH];
	
	GetCurrentDirectory(MAX_PATH,cTemp);
	m_strExePath.Format("%s\\",cTemp);

	//////////////////////////////////////////Just for Debug
	if ( m_iObjectNum == 0 )
	{
		m_iObjectNum ++;
	}
	else
	{
		CString strInf;
		strInf.Format("ERROR: m_iObjectNum = %d",m_iObjectNum);
		AfxMessageBox(strInf);
	}////////////////////////////////////////
}

CZCTMag::~CZCTMag()
{
	ClearStaList();
	CReadStationInf::ReleaseInstance();

	///////////////////////////////////
	if ( m_iObjectNum == 1)
	{
		m_iObjectNum --;
	}/////////////////////////////////

}

void CZCTMag::ClearStaList()
{
	while(m_SingleStaList.GetHeadPosition())
	{
		delete m_SingleStaList.RemoveHead();
	}
	//
	m_MultiStationWnd.ClearList();

}

CZCTWnd* CZCTMag::GetZCTbyNo(int iStationNo)
{
	
	CZCTWndList* pList = &m_SingleStaList;

	//
	POSITION POS = pList->GetHeadPosition();
	while ( POS )
	{
		CZCTWnd* pZCT = pList->GetNext(POS);
		
		//
		if ( pZCT->GetStationID() == iStationNo )
		{
			return pZCT;
		}
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CZCTMag message handlers

void CZCTMag::OnReceive(BYTE *pBuffer)
{
	BYTE byFrameKind	= pBuffer[0];		//֡����
	WORD wStation;
	if (byFrameKind==BAODIANXINXI_FRAME_TYPE) {
		memcpy(&wStation,pBuffer+19,2);	
	}
	else{
		memcpy(&wStation,pBuffer+4,2);//ȡ��վ��
	}
	

	//----------------���»����������� -------------//
	CZCTWnd *pSingleZCT = GetZCTbyNo(wStation);//
	if ( pSingleZCT )	{
		pSingleZCT->OnReceiveInf(pBuffer);
	}
	//
	m_MultiStationWnd.OnReceiveInf(pBuffer);
}

void CZCTMag::DrawStation(int iStationNo/*=-1*/)
{
	POSITION pos;
	if ( iStationNo != -1 )//������վ
	{
		//�Ҹ�վ��ΪiStationNo��վ����Ȼ����ʾ
		pos = m_SingleStaList.GetHeadPosition();
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
	else//����վ
	{
		m_MultiStationWnd.ShowWindow(SW_SHOW);
	}
}

BOOL CZCTMag::ReadStationInf(int iReadMode/*,int iStationNo*/)
{
	ClearStaList();

	//
	CString strDir;
	int i,iStationNo = CReadStationInf::GetActiveStation();
	CZCTWnd *pZCT;
	const CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	
	//��վ��ȡģʽ
	int iSingStaReadMode = CZCTWnd::RDMD_SYARD | CZCTWnd::RDMD_SFRAM 
		| CZCTWnd::RDMD_DESK | CZCTWnd::RDMD_GUDAO 
		| CZCTWnd::RDMD_MASK | CZCTWnd::RDMD_JINLU;

	switch(iReadMode)
	{
		
/* -------- ���ĸ�����վ -------��*/
	case MODE_DAPING:/*����*/
		if (!m_MultiStationWnd.ReadStationInf(CZCTMultiWnd::RM_ALLSTATN)) {
			return FALSE;
		}
		break;
	case MODE_KONGZHI:/*���ƹ���վ*/
	case MODE_ZHUDIAO:/*��������վ*/
	case MODE_ZONGHEWEIXIU:/*�ۺ�ά�޹���վ*/
	case MODE_DIANWUWEIHU:/*����ά��*/
	case MODE_JIANCE:////���
		//����վ����
		for ( i=0; i<pStationInf->GetLength(); i++)
		{
			//
			pZCT = new CZCTWnd;
			pZCT->m_iStationNo = pStationInf->GetAt(i)->iStationID;
			
			//
			if ( iReadMode == MODE_ZONGHEWEIXIU)
			{
				pZCT->m_dwShowStyle &= ~CZCTWnd::SHOW_LIECHEBTN;
				pZCT->m_dwShowStyle &= ~CZCTWnd::SHOW_DIAOCHEAN;
				//
				iSingStaReadMode &= ~CZCTWnd::RDMD_JINLU;
			}
			else if (  iReadMode == MODE_DIANWUWEIHU )
			{
				pZCT->m_dwShowStyle &= ~CZCTWnd::SHOW_LIECHEBTN;
				pZCT->m_dwShowStyle &= ~CZCTWnd::SHOW_DIAOCHEAN;
				//
				iSingStaReadMode &= ~CZCTWnd::RDMD_DESK;
				iSingStaReadMode &= ~CZCTWnd::RDMD_JINLU;
				//
				pZCT->m_wOperatorAttr &= ~CZCTWnd::OPER_FUNCTNBTN;
			}
			else if ( iReadMode == MODE_ZHUDIAO)
			{
				pZCT->m_dwShowStyle &= ~CZCTWnd::SHOW_LIECHEBTN;
				pZCT->m_wOperatorAttr |= CZCTWnd::OPER_DAOCHABTN;
				pZCT->m_wOperatorAttr |= CZCTWnd::OPER_DIAOCHENAN;
			}
			else if ( iReadMode == MODE_KONGZHI )
			{
				pZCT->m_wOperatorAttr |= CZCTWnd::OPER_FRAMETRANO;
				pZCT->m_wOperatorAttr |= CZCTWnd::OPER_DAOCHABTN;
				pZCT->m_wOperatorAttr |= CZCTWnd::OPER_DIAOCHENAN;
				pZCT->m_wOperatorAttr |= CZCTWnd::OPER_LIECHEBTN;
			}
			else if ( iReadMode == MODE_JIANCE) {
				pZCT->m_dwShowStyle &= ~CZCTWnd::SHOW_LIECHEBTN;
				pZCT->m_dwShowStyle &= ~CZCTWnd::SHOW_DIAOCHEAN;
				//
				iSingStaReadMode &= ~CZCTWnd::RDMD_GUDAO;
				iSingStaReadMode &= ~CZCTWnd::RDMD_SFRAM;
				iSingStaReadMode &= ~CZCTWnd::RDMD_DESK;
				iSingStaReadMode &= ~CZCTWnd::RDMD_JINLU;
				//
				pZCT->m_wOperatorAttr &= ~CZCTWnd::OPER_FUNCTNBTN;
				//
				pZCT->m_nMapMode = MM_TEXT;
			}

			//������
			strDir = ".\\"+pStationInf->GetAt(i)->strDirectory+"\\";
			if (!pZCT->ReadStationInf(strDir,iSingStaReadMode)) {
				delete pZCT;
				return FALSE;
			}
			m_SingleStaList.AddTail(pZCT);
		}
		
		//����������
		if (!m_MultiStationWnd.ReadStationInf(iReadMode==MODE_JIANCE ? 
				CZCTMultiWnd::RM_JIANCHE : CZCTMultiWnd::RM_ALLSTATN) ) {
			return FALSE;
		}
		
		
		break;
		
/* -------- ���ɻ� --------------*/
	case MODE_ZILVJI:
		break;
		
/* ------- ���ն˹���վ ------- */
		//�����ն�
	case MODE_CHEWUZONGDUAN:
		{
			ASSERT(iStationNo != -1);
			//-------����վ����
			pZCT = new CZCTWnd;
			
			pZCT->m_iStationNo = iStationNo;
			pZCT->m_dwShowStyle &= ~CZCTWnd::SHOW_POPMENU;
			pZCT->m_wOperatorAttr |= CZCTWnd::OPER_DAOCHABTN;
			pZCT->m_wOperatorAttr |= CZCTWnd::OPER_DIAOCHENAN;
			pZCT->m_wOperatorAttr |= CZCTWnd::OPER_FRAMETRANO;
			
			//
			strDir = pStationInf->GetDirectory(iStationNo);
			if (!pZCT->ReadStationInf(strDir,iSingStaReadMode)) {
				delete pZCT;
				return FALSE;
			}
			m_SingleStaList.AddTail(pZCT);
			
			
			//-------����վ����
			if (!m_MultiStationWnd.ReadStationInf(CZCTMultiWnd::RM_NEIGHBOR,iStationNo)) {
				return FALSE;
			}
		}
		//////////////////////////////////////////////////////////////////////////
		break;
		
		//ά���ն�
	case MODE_WEIXIUZONGDUAN:
		//����ά���ն�
	case MODE_WEIHUZONGDUAN:
		//����վ����
		{
			ASSERT(iStationNo != -1);
			pZCT = new CZCTWnd;
			strDir = pStationInf->GetDirectory(iStationNo);
			
			//
			//pZCT->m_dwShowStyle &= ~CZCTWnd::SHOW_POPMENU;
			pZCT->m_dwShowStyle &= ~CZCTWnd::SHOW_DIAOCHEAN;
			pZCT->m_dwShowStyle &= ~CZCTWnd::SHOW_LIECHEBTN;
			pZCT->m_wOperatorAttr &= ~CZCTWnd::OPER_FUNCTNBTN;
			
			//
			pZCT->m_iStationNo = iStationNo;
			
			//
			iSingStaReadMode &= ~CZCTWnd::RDMD_DESK;
			iSingStaReadMode &= ~CZCTWnd::RDMD_JINLU;
			if (!pZCT->ReadStationInf(strDir,iSingStaReadMode)) {
				delete pZCT;
				return FALSE;
			}
			m_SingleStaList.AddTail(pZCT);
		}
		break;
	}
	//
	return TRUE;
}


void CZCTMag::Create(CWnd *pParentWnd,HWND hMsgHandle,BOOL bSingle/* = FALSE*/)
{
	//����bSingle����ָ���ĳ��ο�
	if (!bSingle) {
		m_MultiStationWnd.Create(pParentWnd);
	}
	else
	{
		POSITION pos = m_SingleStaList.GetHeadPosition();
		while ( pos )
		{
			CZCTWnd * pZCT = m_SingleStaList.GetNext(pos);
			pZCT->Create(pParentWnd,NULL,hMsgHandle);		
		}
	}
	
}

//////////////////////////////////////////////////////////////////////////
//Show style implement
void CZCTMag::SetZCTStyle(DWORD dwStyle, int iStationID/*=-1*/)
{
	if ( iStationID == -1){
		m_MultiStationWnd.SetZCTStyle(dwStyle);
	}
	else{
		CZCTWnd* pZCT = GetZCTbyNo(iStationID);
		if (pZCT) {
			pZCT->SetZCTStyle(dwStyle);
		}		
	}
}

DWORD CZCTMag::GetZCTStyle(int iStationID/*=-1*/)
{
	if( iStationID == -1 ){
		return m_MultiStationWnd.GetZCTStyle();
	}
	else{
		CZCTWnd* pZCT = GetZCTbyNo(iStationID);
		if (pZCT) {
			return pZCT->m_dwShowStyle;
		}
	}

	//
	return 0;
}

void CZCTMag::SetZCTMapMode(int nMapMode, int iStationID/*=-1*/)
{
	if ( iStationID == -1){
		m_MultiStationWnd.SetZCTMapMode(nMapMode);
	}
	else{
		CZCTWnd* pZCT = GetZCTbyNo(iStationID);
		if (pZCT) {
			pZCT->m_nMapMode = nMapMode;
		}
		
	}
}

int CZCTMag::GetZCTMapMode(int iStationID)
{
	if( iStationID == -1 ){
		return m_MultiStationWnd.GetZCTMapMode();
	}
	else{
		CZCTWnd* pZCT = GetZCTbyNo(iStationID);
		if (pZCT) {
			return pZCT->m_nMapMode;
		}
	}

	//
	return 0;
}

void CZCTMag::InvalidateInf(BOOL bNewFlag)
{
	m_MultiStationWnd.InvalidateInf(bNewFlag);
	
	//
	POSITION pos = m_SingleStaList.GetHeadPosition();
	while (pos)	{
		CZCTWnd* pZCT = m_SingleStaList.GetNext(pos);
		pZCT->InvalidateInf(bNewFlag);
	}
}

CString CZCTMag::GetWcQDNameByID(int iStationID, int iWcQdID)
{
	CZCTWnd* pZCTWnd = GetZCTbyNo(iStationID);
	if (pZCTWnd) {
		return pZCTWnd->GetWcQdNameByID(iWcQdID);
	}
	//
	return "";
}

int CZCTMag::GetWcQdIDByName(int iStationID, CString strWcQdName)
{
	CZCTWnd* pZCTWnd = GetZCTbyNo(iStationID);
	if (pZCTWnd) {
		return pZCTWnd->GetWcQdIDByName(strWcQdName);
	}
	return 0;
}

int CZCTMag::GetBtnIDbyName(int iStationID, CString strName)
{
	CZCTWnd* pZCTWnd = GetZCTbyNo(iStationID);
	if (pZCTWnd) {
		return pZCTWnd->GetBtnIDByName(strName);
	}
	return 0;
}

CString CZCTMag::GetBtnNameByID(int iStationID, int iCommandID)
{
	CZCTWnd* pZCTWnd = GetZCTbyNo(iStationID);
	if (pZCTWnd) {
		return pZCTWnd->GetBtnNameByID(iCommandID);
	}
	return "";
}

void CZCTMag::GetWcQdNameList(int iStationID, CStringList &sNameList)
{
	CZCTWnd* pZCTWnd = GetZCTbyNo(iStationID);
	if (pZCTWnd) {
		pZCTWnd->GetWcQdNameList(sNameList);
	}
}

void CZCTMag::HideStation(BOOL bSingle)
{
	if (bSingle) {
		POSITION pos = m_SingleStaList.GetHeadPosition();
		while (pos)	{
			CZCTWnd* pZCT = m_SingleStaList.GetNext(pos);
			pZCT->ShowWindow(SW_HIDE);
		}
	}
	else{
		m_MultiStationWnd.ShowWindow(SW_HIDE);
	}
}

void CZCTMag::SetPopupMenu(HMENU hMenu, HWND hMsgHandle)
{
	POSITION pos = m_SingleStaList.GetHeadPosition();
	while (pos)	{
		CZCTWnd* pZCT = m_SingleStaList.GetNext(pos);
		pZCT->SetPopupMenu(hMenu,hMsgHandle);
	}
	//
	m_MultiStationWnd.SetPopupMenu(hMenu,hMsgHandle);
}
