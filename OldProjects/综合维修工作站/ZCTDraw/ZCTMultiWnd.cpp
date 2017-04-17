// ZCTMultiWnd.cpp : implementation file
//

#include "stdafx.h"
#include "ReadStationInf.h"
#include "ZCTMultiWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZCTMultiWnd

CZCTMultiWnd::CZCTMultiWnd():m_hPMHandle(NULL)
{
}

CZCTMultiWnd::~CZCTMultiWnd()
{
	ClearList();
}


void CZCTMultiWnd::ClearList()
{
	while(m_MultiStaList.GetHeadPosition())
	{
		delete m_MultiStaList.RemoveHead();
	}
}
BEGIN_MESSAGE_MAP(CZCTMultiWnd, CWnd)
	//{{AFX_MSG_MAP(CZCTMultiWnd)
	ON_WM_PAINT()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CZCTMultiWnd message handlers


void CZCTMultiWnd::OnPaint() 
{
	TRACE("void CZCTMultiWnd::OnPaint() \n");
	CPaintDC dc(this); // device context for painting

	CBrush brush;
	brush.CreateSolidBrush (BLACKCOLOR);	
	CBrush* pOldBrush = dc.SelectObject (&brush);
	
	//Fill the srceen to black color
	dc.Rectangle(CRect(0,0,CS_WIDTH,CS_HEIGHT));
	dc.SelectObject(pOldBrush);
	
	//在父窗口中绘制所有站场图
	POSITION pos = m_MultiStaList.GetHeadPosition();
	while(pos){
		CZCTWnd* pZCT = m_MultiStaList.GetNext(pos);
		pZCT->SetDeviceContext(&dc);
		pZCT->DrawZCT(&dc);
	}
	
	// Do not call CWnd::OnPaint() for painting messages
}

BOOL CZCTMultiWnd::Create(CWnd *pParentWnd)
{
	if ( !CWnd::Create(NULL,"",WS_CHILD,
			CRect(0,0,CS_WIDTH,CS_HEIGHT),pParentWnd,1) ){
		return FALSE;
	}

	//
	POSITION pos = m_MultiStaList.GetHeadPosition();
	while(pos){
		CZCTWnd* pZCT = m_MultiStaList.GetNext(pos);
		if (!pZCT->Create(pParentWnd,this)) {
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CZCTMultiWnd::ReadStationInf(int iReadMode,CString strPath)
{
	BOOL bReultValue = TRUE;
	CZCTWnd *pZCT;
	CString strDir;


	const CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	
	//显示风格
	DWORD dwShowStyle = 0xFFFFFFFF & ~CZCTWnd::SHOW_ALLBUTTON
		& ~CZCTWnd::SHOW_DCNAME & ~CZCTWnd::SHOW_XHJNAME
		&~CZCTWnd::SHOW_WCQDNAME & ~CZCTWnd::SHOW_POPMENU;

	//读取模式
	int iMulStaReadMode = CZCTWnd::RDMD_OFFSET | CZCTWnd::RDMD_MYARD |
						CZCTWnd::RDMD_MASK   | CZCTWnd::RDMD_MFRAM ;

	switch(iReadMode)
	{
	//读所有站数据
	//case RM_JIANCE:
	case RM_ALLSTATN:
		{			
			for ( int i=0; i<pStationInf->GetLength(); i++)	{
				pZCT = new CZCTWnd;
				pZCT->m_dwShowStyle  = dwShowStyle;
				pZCT->m_bSingle = FALSE;
				//pZCT->m_nMapMode = MM_TEXT;
				pZCT->m_iStationNo = pStationInf->GetAt(i)->iStationID;
				
				//读取相关组件数据
				if (strPath.IsEmpty()) {
					strDir = ".\\"+pStationInf->GetAt(i)->strDirectory+"\\";
				}
				else{
					strDir = strPath+pStationInf->GetAt(i)->strDirectory+"\\";
				}
				
				
				if (!pZCT->ReadStationInf(strDir,iMulStaReadMode)) {
					bReultValue = FALSE;
				}
				
				//
				m_MultiStaList.AddTail(pZCT);
			}
			break;
		}

		//读相邻两站数据
	case RM_NEIGHBOR:
		{	
			int iStationID = CReadStationInf::GetActiveStation();
			//----------------自身数据----------
			pZCT = new CZCTWnd;
			pZCT->m_dwShowStyle = dwShowStyle;
			pZCT->m_bSingle = FALSE;
			pZCT->m_iStationNo = iStationID;
			//pZCT->m_nMapMode = MM_TEXT;
			//
			if (strPath.IsEmpty()) {
				strDir = pStationInf->GetDirectory(iStationID);
			}
			else{
				strDir = strPath+pStationInf->GetDirectory(iStationID);
			}
			if(!pZCT->ReadStationInf( strDir,iMulStaReadMode)){
				bReultValue = FALSE;
			}
			
			//
			m_MultiStaList.AddTail(pZCT);
			
			//---------------相邻站---------
			StationNode* pStatNode = pStationInf->GetItem(iStationID);
			int iTempID;
			for( int i=0; i<4; i++)
			{
				iTempID = i>1 ? pStatNode->iUpStationID[i] : pStatNode->iDownStationID[i-2];
				if ( iTempID != -1)	{
					pZCT = new CZCTWnd;
					pZCT->m_dwShowStyle = dwShowStyle;
					pZCT->m_bSingle = FALSE;
					pZCT->m_iStationNo = iTempID;
					
					//读取相关组件数据
					if (strPath.IsEmpty()) {
						strDir = ".\\" + pStationInf->GetItem(iTempID)->strDirectory+"\\";
					}
					else{
						strDir = strPath + pStationInf->GetItem(iTempID)->strDirectory+"\\";
					}
					
					if (!pZCT->ReadStationInf(strDir,iMulStaReadMode)) {
						bReultValue = FALSE;
					}
					//
					m_MultiStaList.AddTail(pZCT);
				}
			}
		}
		break;
	}

	return bReultValue;
}


void CZCTMultiWnd::OnReceiveInf(LPBYTE pBuffer)
{
	BYTE byFrameKind	= pBuffer[0];		//帧类型
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

CZCTWnd* CZCTMultiWnd::GetZCTbyNo(int iStationNo)
{
	POSITION POS = m_MultiStaList.GetHeadPosition();
	while ( POS ){
		CZCTWnd* pZCT = m_MultiStaList.GetNext(POS);
		if ( pZCT->GetStationID() == iStationNo ){
			return pZCT;
		}
	}

	return NULL;
}

void CZCTMultiWnd::SetZCTStyle(DWORD dwStyle)
{
	POSITION pos = m_MultiStaList.GetHeadPosition();
	while (pos){
		CZCTWnd* pZCT = m_MultiStaList.GetNext(pos);
		pZCT->SetZCTStyle(dwStyle);
	}
}

DWORD CZCTMultiWnd::GetZCTStyle()
{
	POSITION pos = m_MultiStaList.GetHeadPosition();
	while (pos){
		CZCTWnd* pZCT = m_MultiStaList.GetNext(pos);
		return pZCT->m_dwShowStyle;
	}
	return 0;
}

void CZCTMultiWnd::SetZCTMapMode(int nMapMode)
{
	POSITION pos = m_MultiStaList.GetHeadPosition();
	while (pos)	{
		CZCTWnd* pZCT = m_MultiStaList.GetNext(pos);
		pZCT->m_nMapMode = nMapMode;
	}
}

int CZCTMultiWnd::GetZCTMapMode()
{
 	POSITION pos = m_MultiStaList.GetHeadPosition();
 	while (pos)	{
 		CZCTWnd* pZCT = m_MultiStaList.GetNext(pos);
 		return pZCT->m_nMapMode;
 	}
 	return 0;
 }

void CZCTMultiWnd::InvalidateInf(BOOL bNewFlag)
{
	POSITION pos = m_MultiStaList.GetHeadPosition();
	while (pos)	{
		CZCTWnd* pZCT = m_MultiStaList.GetNext(pos);
		pZCT->InvalidateInf(bNewFlag);
	}
}


BOOL CZCTMultiWnd::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(pMsg->message)
	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		GetParent()->PostMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
		break;
/*	case WM_CONTEXTMENU:
		{
			POSITION pos = m_MultiStaList.GetHeadPosition();
			while (pos)
			{
				CZCTWnd* pZCT = m_MultiStaList.GetNext(pos);
				pZCT->PostMessage(WM_CONTEXTMENU,pMsg->wParam,pMsg->lParam);
			}
		}
		break;*/
	case WM_COMMAND:
		{
			if (m_hPMHandle) {
				for(UINT i=0; i<m_StationMenu.GetMenuItemCount(); i++){
					if (pMsg->wParam == m_StationMenu.GetMenuItemID(i)) {
						::PostMessage(m_hPMHandle,pMsg->message,pMsg->wParam,pMsg->lParam);
						//
						break;
					}
				}
			}
		}
	}
	return CWnd::PreTranslateMessage(pMsg);
}

void CZCTMultiWnd::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	if (m_StationMenu.GetSafeHmenu()) {
		m_StationMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,point.x,point.y,this);
	}
}

void CZCTMultiWnd::SetPopupMenu(HMENU hMenu, HWND hMsgHandle)
{
	if (hMenu) {
		m_StationMenu.Attach(hMenu);
	}
	else{
		m_StationMenu.CreatePopupMenu();
	}
	m_hPMHandle = hMsgHandle;
}
