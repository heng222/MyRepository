 // MaintainView.cpp : implementation of the CMaintainView class
//

#include "stdafx.h"
#include "Maintain.h"
#include "mainfrm.h"
#include "MaintainView.h"
#include "ChildFrm.h"

extern CMaintainApp theApp;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaintainView

IMPLEMENT_DYNCREATE(CMaintainView, CScrollView)

BEGIN_MESSAGE_MAP(CMaintainView, CScrollView)
	//{{AFX_MSG_MAP(CMaintainView)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_MESSAGE(UM_FORMSTATION, OnMsgFromStation )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaintainView construction/destruction

CMaintainView::CMaintainView()
{
	// TODO: add construction code here

}

CMaintainView::~CMaintainView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMaintainView drawing

void CMaintainView::OnDraw(CDC* pDC)
{
	CMaintainDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	//pDC->SetViewportOrg(CPoint(0,0));
	//pDC->SetWindowOrg(CPoint(0,0));
	pDC->TextOut(10,10,"void CMaintainView::OnDraw(CDC* pDC)");
}

void CMaintainView::OnInitialUpdate()
{	
	CScrollView::OnInitialUpdate();

	CMaintainDoc *m_pDoc=GetDocument();
	
	//m_pDoc->SetTitle(theApp.m_strStationName+"վ��ͼ");
	m_pDoc->SetTitle("");
	
	CSize sizeTotal;
	sizeTotal.cx = 1280;//1024-200;
    sizeTotal.cy = 1024;//768-200;
	CSize sizePage(sizeTotal.cx/2,sizeTotal.cy/2);
	CSize sizeLine(sizeTotal.cx/10,sizeTotal.cy/10);
    SetScrollSizes(MM_TEXT, sizeTotal,sizePage,sizeLine);
	ScrollToPosition(CPoint(0,0));

	//////////////////////////////////////////////////////////////////////////
	theApp.m_ZCTMag.Create(this,GetSafeHwnd(),TRUE);
#ifdef _DEBUG
	m_Menu.LoadMenu(IDR_MAINTATYPE);
	HMENU hmnu = m_Menu.GetSubMenu(2)->GetSafeHmenu();
	theApp.m_ZCTMag.SetPopupMenu(hmnu,AfxGetMainWnd()->GetSafeHwnd());
#endif
	theApp.m_ZCTMag.DrawStation(CReadStationInf::GetActiveStation());
}

/////////////////////////////////////////////////////////////////////////////
// CMaintainView printing

BOOL CMaintainView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMaintainView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMaintainView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMaintainView diagnostics

#ifdef _DEBUG
void CMaintainView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMaintainView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMaintainDoc* CMaintainView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMaintainDoc)));
	return (CMaintainDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMaintainView message handlers
	
BOOL CMaintainView::SendTrackCloseOffFrame (int iStationID,int iCommandID,int iGdStatus)
{
	BYTE pBuf[20];
	WORD wLength = 0;
	
	//�������֡----------------------------
	//վ��
	WORD wStation = (WORD)iStationID;
	memcpy(pBuf+wLength,&wStation,2);
	wLength += 2;
	
	//�ɵ���
	memcpy(pBuf+wLength,&iCommandID,2);
	wLength += 2;

	//״̬
	pBuf[wLength++] = iGdStatus;

	//��Դ
	pBuf[wLength++] = LOCAL_MACHINE_CODE;
	
	// ����
	((CMainFrame*)AfxGetMainWnd())->m_socketClient.WriteComm(GUDAOLOCK_FRAME_TYPE,0x01,pBuf, wLength, INFINITE);
	return true;    
}

BOOL CMaintainView::SendReginCloseOffFrame(int iStationNo,int iCommandID,int iQjStatus)
{
	BYTE pBuf[20];
	WORD wLength = 0;

	// �������֡

	//
	WORD wTemp = (WORD)iStationNo;
	memcpy(pBuf+wLength,&wTemp,2);
	wLength += 2;

	//������
	pBuf[wLength++] = (BYTE)iCommandID/100;
	
	//�����
	wTemp = (WORD)(iCommandID%100);
	memcpy(pBuf+wLength,&wTemp,2);
	wLength += 2;
	
	//״̬
	pBuf[wLength++] = iQjStatus; //���

	//��Դ
	pBuf[wLength++] = LOCAL_MACHINE_CODE;		
	

	// ����
	((CMainFrame*)AfxGetMainWnd())->m_socketClient.WriteComm(QUJIANLOCK_FRAME_TYPE,0x01,pBuf, wLength, INFINITE);
	return true;
}

/*
 *	
 */
LRESULT CMaintainView::OnMsgFromStation( WPARAM wParam, LPARAM lParam )
{
	StationMsg* pStaMsg = (StationMsg*)wParam;
	BYTE byMsgType = pStaMsg->byMsgType;	//��Ϣ����
	int iStationID = pStaMsg->iStationID;	//վ��ID
	TRACE("Station ID = %d, ",iStationID);
	int iValueRlav = pStaMsg->iValueRelative;	//���ֵ

	//
	if ( byMsgType == MSGTYPE_FRAME)//���ο���Ϣ
	{
		CString Str = *(CString*)lParam;
		TRACE("The Frame ID = %d,Content = '%s'\n",iValueRlav,Str);
		//MessageBox("Click the frame!");
	}
	else if ( byMsgType == MSGTYPE_STANCHNG)
	{
		TRACE("Station Show ID = %d\n",iStationID);
		//theApp.m_iCurStationID = iStationID;
	}
	else if ( byMsgType == MSGTYPE_FUNCBTN)//���ܰ�ť������Ϣ
	{
		switch(iValueRlav)
		{
		case (CFuncBtn::GDFS):
			{
				CGdStatus* pGdStatus = (CGdStatus*)lParam;
				int iGDStatus = ( pGdStatus->GetLockSta() )?128:64;
				
				//���͹ɵ�����֡
				SendTrackCloseOffFrame(iStationID,pGdStatus->m_iCommandID,iGDStatus);
				TRACE("�ɵ�����: CommandID = %d\n",pGdStatus->m_iCommandID);
			}
			break;
			
		case (CFuncBtn::QJFS):
			{				
				CQjStatus* pQjStatus = (CQjStatus*)lParam;
				int iQJStatus = ( pQjStatus->GetLockSta() )?128:64;
				
				if( pQjStatus->m_iStationNo1 == pQjStatus->m_iStationNo2 )
				{
					SendReginCloseOffFrame(iStationID,pQjStatus->m_iCommandID,iQJStatus);
				}
				else
				{
					SendReginCloseOffFrame(iStationID,pQjStatus->m_iCommandID,iQJStatus);
					SendReginCloseOffFrame(pQjStatus->m_iStationNo2,pQjStatus->m_iCommandID2,iQJStatus);
				}
				TRACE("�������: CommandID = %d\n",pQjStatus->m_iCommandID);
			}
			break;
		case (CFuncBtn::ZDW):
			{
				CAnN* pAnN = (CAnN*)lParam;
				TRACE("�ܶ�λ -> %s\n",pAnN->m_strName);
			}
			break;
		case (CFuncBtn::ZFW):
			{
				CAnN* pAnN = (CAnN*)lParam;
				TRACE("�ܷ�λ-> %s\n",pAnN->m_strName);
			}
			break;
		case (CFuncBtn::DS):
			{
				TRACE("����");
				CAnN* pAnN = (CAnN*)lParam;
				TRACE(" ->%s\n",pAnN->m_strName);
			}
			break;
		case (CFuncBtn::DJ):
			{
				CAnN* pAnN = (CAnN*)lParam;
				TRACE("���� ->%s\n",pAnN->m_strName);
			}
			break;
		case (CFuncBtn::DF):
			{
				TRACE("����\n");
				CAnN* pAnN = (CAnN*)lParam;
			}
			break;
		case (CFuncBtn::JF):
			{
				TRACE("���\n");
				CAnN* pAnN = (CAnN*)lParam;
			}
			break;
		case (CFuncBtn::ZRJ):
			{
				TRACE("���˽�\n");
				CAnN* pAnN = (CAnN*)lParam;
				TRACE("-->%s\n",pAnN->m_strName);
			}
			break;
		case (CFuncBtn::PDJS):
			{
				TRACE("�µ�����");
				CAnN* pAnN = (CAnN*)lParam;
				TRACE("-->%s\n",pAnN->m_strName);
			}
			break;
		case (CFuncBtn::QGJ):
			{
				TRACE("���ʽ�");
				int iCommandID = (int)lParam;
				TRACE(" ID = %d\n",iCommandID);
			}
			break;
		case (CFuncBtn::ZQX):
			{
				TRACE("��ȡ��");
				CAnN* pAnN = (CAnN*)lParam;
				TRACE("-->%s\n",pAnN->m_strName);
			}
			break;
		case (CFuncBtn::XYZS):
			{
				TRACE("��������\n");
				BOOL bIsLock = (BOOL)lParam;
				if ( lParam )
				{
					TRACE("-->����\n");
				}
				else
				{
					TRACE("-->����\n");
				}
			}
			break;
		case (CFuncBtn::SYZS):
			{
				TRACE("��������\n");
				BOOL bIsLock = (BOOL)lParam;
				if ( lParam )
				{
					TRACE("-->����\n");
				}
				else
				{
					TRACE("-->����\n");
				}
			}
			break;
		case (CFuncBtn::XTDHF):
			{
				TRACE("Xͣ��ָ�\n");
			}
			break;
		case (CFuncBtn::STDHF):
			{
				TRACE("Sͣ��ָ�\n");
			}
			break;
		case (CFuncBtn::CKXH):
			{
				TRACE("�ؿ��ź�");
				CAnN* pAnN = (CAnN*)lParam;
				TRACE("-->%s\n",pAnN->m_strName);
			}
			break;
		case (CFuncBtn::JLSP):
			{
				TRACE("��·����\n");
				CAnNList* pAnNlist = (CAnNList*)lParam;
				POSITION pos = pAnNlist->GetHeadPosition();
				while (pos)
				{
					CAnN* pAnN = pAnNlist->GetNext(pos);
					TRACE(" %s",pAnN->m_strName);
				}
				TRACE("\n");
			}
			break;
		case (CFuncBtn::PLJL):
			{
				TRACE("���н�·: ");
				CAnNList* pAnNlist = (CAnNList*)lParam;
				POSITION pos = pAnNlist->GetHeadPosition();
				while (pos)
				{
					CAnN* pAnN = pAnNlist->GetNext(pos);
					TRACE(" %s",pAnN->m_strName);
				}
				CString strFrameContent = *((CString*)pStaMsg->m_pAttachValue);
				TRACE(",Frame Content is '%s' .",strFrameContent);
				TRACE("\n");
			}
			break;
		}	
	}
	//////////////////////////////////////////////////////////////////////////

	return 0;
}

void CMaintainView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CScrollView::OnPrepareDC(pDC, pInfo);
}


void CMaintainView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//TRACE("void CMaintainView::OnLButtonDown(); nFlags = %d, point.x = %d; point.y = %d\n",nFlags,point.x,point.y);
	CScrollView::OnLButtonDown(nFlags, point);
}

void CMaintainView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//TRACE("CMaintainView::OnRButtonDown\n");
	CScrollView::OnRButtonDown(nFlags, point);
}

void CMaintainView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	TRACE("CMaintainView::OnContextMenu\n");
}
