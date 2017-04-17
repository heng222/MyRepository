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
	
	//m_pDoc->SetTitle(theApp.m_strStationName+"站场图");
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
	
	//打包发送帧----------------------------
	//站码
	WORD wStation = (WORD)iStationID;
	memcpy(pBuf+wLength,&wStation,2);
	wLength += 2;
	
	//股道号
	memcpy(pBuf+wLength,&iCommandID,2);
	wLength += 2;

	//状态
	pBuf[wLength++] = iGdStatus;

	//来源
	pBuf[wLength++] = LOCAL_MACHINE_CODE;
	
	// 发送
	((CMainFrame*)AfxGetMainWnd())->m_socketClient.WriteComm(GUDAOLOCK_FRAME_TYPE,0x01,pBuf, wLength, INFINITE);
	return true;    
}

BOOL CMaintainView::SendReginCloseOffFrame(int iStationNo,int iCommandID,int iQjStatus)
{
	BYTE pBuf[20];
	WORD wLength = 0;

	// 打包发送帧

	//
	WORD wTemp = (WORD)iStationNo;
	memcpy(pBuf+wLength,&wTemp,2);
	wLength += 2;

	//上下行
	pBuf[wLength++] = (BYTE)iCommandID/100;
	
	//区间号
	wTemp = (WORD)(iCommandID%100);
	memcpy(pBuf+wLength,&wTemp,2);
	wLength += 2;
	
	//状态
	pBuf[wLength++] = iQjStatus; //解封

	//来源
	pBuf[wLength++] = LOCAL_MACHINE_CODE;		
	

	// 发送
	((CMainFrame*)AfxGetMainWnd())->m_socketClient.WriteComm(QUJIANLOCK_FRAME_TYPE,0x01,pBuf, wLength, INFINITE);
	return true;
}

/*
 *	
 */
LRESULT CMaintainView::OnMsgFromStation( WPARAM wParam, LPARAM lParam )
{
	StationMsg* pStaMsg = (StationMsg*)wParam;
	BYTE byMsgType = pStaMsg->byMsgType;	//消息类型
	int iStationID = pStaMsg->iStationID;	//站场ID
	TRACE("Station ID = %d, ",iStationID);
	int iValueRlav = pStaMsg->iValueRelative;	//相关值

	//
	if ( byMsgType == MSGTYPE_FRAME)//车次框消息
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
	else if ( byMsgType == MSGTYPE_FUNCBTN)//功能按钮激活消息
	{
		switch(iValueRlav)
		{
		case (CFuncBtn::GDFS):
			{
				CGdStatus* pGdStatus = (CGdStatus*)lParam;
				int iGDStatus = ( pGdStatus->GetLockSta() )?128:64;
				
				//发送股道封锁帧
				SendTrackCloseOffFrame(iStationID,pGdStatus->m_iCommandID,iGDStatus);
				TRACE("股道封锁: CommandID = %d\n",pGdStatus->m_iCommandID);
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
				TRACE("区间封锁: CommandID = %d\n",pQjStatus->m_iCommandID);
			}
			break;
		case (CFuncBtn::ZDW):
			{
				CAnN* pAnN = (CAnN*)lParam;
				TRACE("总定位 -> %s\n",pAnN->m_strName);
			}
			break;
		case (CFuncBtn::ZFW):
			{
				CAnN* pAnN = (CAnN*)lParam;
				TRACE("总反位-> %s\n",pAnN->m_strName);
			}
			break;
		case (CFuncBtn::DS):
			{
				TRACE("单锁");
				CAnN* pAnN = (CAnN*)lParam;
				TRACE(" ->%s\n",pAnN->m_strName);
			}
			break;
		case (CFuncBtn::DJ):
			{
				CAnN* pAnN = (CAnN*)lParam;
				TRACE("单解 ->%s\n",pAnN->m_strName);
			}
			break;
		case (CFuncBtn::DF):
			{
				TRACE("单封\n");
				CAnN* pAnN = (CAnN*)lParam;
			}
			break;
		case (CFuncBtn::JF):
			{
				TRACE("解封\n");
				CAnN* pAnN = (CAnN*)lParam;
			}
			break;
		case (CFuncBtn::ZRJ):
			{
				TRACE("总人解\n");
				CAnN* pAnN = (CAnN*)lParam;
				TRACE("-->%s\n",pAnN->m_strName);
			}
			break;
		case (CFuncBtn::PDJS):
			{
				TRACE("坡道解锁");
				CAnN* pAnN = (CAnN*)lParam;
				TRACE("-->%s\n",pAnN->m_strName);
			}
			break;
		case (CFuncBtn::QGJ):
			{
				TRACE("区故解");
				int iCommandID = (int)lParam;
				TRACE(" ID = %d\n",iCommandID);
			}
			break;
		case (CFuncBtn::ZQX):
			{
				TRACE("总取消");
				CAnN* pAnN = (CAnN*)lParam;
				TRACE("-->%s\n",pAnN->m_strName);
			}
			break;
		case (CFuncBtn::XYZS):
			{
				TRACE("下引总锁\n");
				BOOL bIsLock = (BOOL)lParam;
				if ( lParam )
				{
					TRACE("-->锁定\n");
				}
				else
				{
					TRACE("-->解锁\n");
				}
			}
			break;
		case (CFuncBtn::SYZS):
			{
				TRACE("上引总锁\n");
				BOOL bIsLock = (BOOL)lParam;
				if ( lParam )
				{
					TRACE("-->锁定\n");
				}
				else
				{
					TRACE("-->解锁\n");
				}
			}
			break;
		case (CFuncBtn::XTDHF):
			{
				TRACE("X停电恢复\n");
			}
			break;
		case (CFuncBtn::STDHF):
			{
				TRACE("S停电恢复\n");
			}
			break;
		case (CFuncBtn::CKXH):
			{
				TRACE("重开信号");
				CAnN* pAnN = (CAnN*)lParam;
				TRACE("-->%s\n",pAnN->m_strName);
			}
			break;
		case (CFuncBtn::JLSP):
			{
				TRACE("进路试排\n");
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
				TRACE("排列进路: ");
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
