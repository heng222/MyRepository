// TfcInfView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Resource.h"
#include "InterfaceEx.h"
#include "TfcParsedView.h"
#include ".\tfcparsedview.h"

//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
// CTfcParsedView

IMPLEMENT_DYNAMIC(CTfcParsedView, CNBMapWnd)
CTfcParsedView::CTfcParsedView()
{
}

CTfcParsedView::~CTfcParsedView()
{
}


BEGIN_MESSAGE_MAP(CTfcParsedView, CNBMapWnd)
    ON_WM_TIMER()
    ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_TFC_FLASHIMMEDIATELY, OnTfcFlash)
    ON_COMMAND(ID_TFC_FLASHMANUAL, OnTfcManuflash)
END_MESSAGE_MAP()



// CTfcParsedView ��Ϣ�������



int CTfcParsedView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CNBMapWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  �ڴ������ר�õĴ�������
    //create tool tip
    if (!m_tipCtrl.Create(this,WS_POPUP|WS_EX_TOOLWINDOW|TTS_ALWAYSTIP) )
    {
        return -1;
    }
    m_tipCtrl.SetMaxTipWidth(200);
    m_tipCtrl.AddTool(this);
    m_tipCtrl.SetTipTextColor(CLR_BLACK);  // 
    m_tipCtrl.SetDelayTime(200);           // 


    m_Menu.LoadMenu(IDR_MENU_TFCPARSED);


    return 0;
}


void CTfcParsedView::OnDraw(CDC* pDC,CNBMapEngine* /*pEngine*/)
{
    GET_SELF_ENGIN()->Draw(pDC);


    //
    ShowTipInf();
}


BOOL CTfcParsedView::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message == WM_MOUSEMOVE )
    {
        m_tipCtrl.RelayEvent(pMsg); 
    }

    return CNBMapWnd::PreTranslateMessage(pMsg);
}


void CTfcParsedView::OnTimer(UINT nIDEvent)
{


    CNBMapWnd::OnTimer(nIDEvent);
}

void CTfcParsedView::PreContextMenu(CMenu& aMenu)
{
    aMenu.Attach(m_Menu.GetSubMenu(0)->GetSafeHmenu());
    //
    //aMenu.CheckMenuItem(ID_POPMENU_NODENAME,m_bShowNodeName?MF_CHECKED|MF_BYCOMMAND:MF_UNCHECKED|MF_BYCOMMAND );
}



void CTfcParsedView::ShowTipInf(BOOL bErase)
{
    CDC* pDC = GetMemDC();
    if (pDC==NULL)
    {
        return;
    }

	// ����Ĭ������
	CFont  font;
	int iFontHeight;
	iFontHeight = 12;
	font.CreateFont(iFontHeight,0, 0, 0, FW_THIN, false, false, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, "����");


	CFont* pOldFont = pDC->SelectObject(&font);
	pDC->SetTextColor(CLR_BLUE);

    //pDC->SetBkMode(TRANSPARENT);
    pDC->SetBkMode(OPAQUE);

	CPoint ptTL;
	CRect rectClient,ivdRect;
	CString strInf;

	GetClientRect(&rectClient);

#if 0
	// ��ʾ����ʱ��
	COleDateTime uTime = GetRefEngine()->GetUpdateTime(); 

	if (uTime.GetStatus()!=COleDateTime::invalid && uTime.GetStatus()!=COleDateTime::null)
	{
		strInf = uTime.Format(_T("����ʱ�䣺%Y-%m-%d %H:%M:%S"));
	}
	else
	{
		strInf.Format(_T("����ʱ�䣺��Ч"));
	}
	ptTL = CPoint(20,30);
	ivdRect = CRect(ptTL,pDC->GetTextExtent(strInf));
	if (bErase)
	{
		InvalidateRect(&ivdRect);
	}
	pDC->TextOut(ptTL.x,ptTL.y,strInf);

	// ��ʾˢ��ʱ��
    COleDateTime timeFlash = GetRefEngine()->GetFlashTime();
    if (timeFlash.GetStatus()==COleDateTime::valid)
    {
        strInf = timeFlash.Format(_T("ˢ��ʱ�䣺%Y-%m-%d %H:%M:%S"));
    }
    else
    {
        strInf.Format(_T("ˢ��ʱ�䣺��Ч"));
    }
	ptTL.x = ivdRect.left;
	ptTL.y = ivdRect.bottom + ivdRect.Height();
	ivdRect = CRect(ptTL,pDC->GetTextExtent(strInf));
	if (bErase)
	{
		InvalidateRect(&ivdRect);
	}
	pDC->TextOut(ptTL.x,ptTL.y,strInf);
#endif


	// ��ʾ��ǰ������
	strInf.Format("������ 1:%ld",GetRefEngine()->GetCurZoomScale());
	ptTL = CPoint(rectClient.right-120,rectClient.top+30);
	/*ivdRect = CRect(ptTL,pDC->GetTextExtent(strInf));
	if (bErase)
	{
		InvalidateRect(&ivdRect);
	}*/
	pDC->TextOut(ptTL.x,ptTL.y,strInf);



	// ��ʾ��ǰ����
	TMPoint mapPos;
	GetRefEngine()->DpToLp(m_ptCurrent,mapPos);
	strInf.Format(_T("���� %.3f, %.3f"),mapPos.iX/24.0/3600,mapPos.iY/24/3600.0);
	pDC->SetBkMode(OPAQUE);
	ptTL = CPoint(rectClient.right-140,rectClient.bottom-30);
	/*ivdRect = CRect(ptTL,pDC->GetTextExtent(strInf));
	if (bErase)
	{
		InvalidateRect(&ivdRect);
	}*/
	pDC->TextOut(ptTL.x,ptTL.y,strInf);


	// 
	pDC->SelectObject(pOldFont);

    //
    ReleaseMemDC();

    //
    Invalidate();
}


void CTfcParsedView::OnStateChanged(TOperateState aNewState,TOperateState aOldState)
{

}


void CTfcParsedView::OnMouseMove(UINT nFlags, CPoint point)
{
    m_ptCurrent = point;

    if (GetOperationState()!=EOPER_MOVING)
    {
        ShowTipInf(TRUE);
    }
 //   //
 //   PTTfcEventAttri pNewEvent = GetRefEngine()->GetTfcEvent(point);
 //   if ( pNewEvent!=NULL && m_pActiveEvent!=NULL )
 //   {
 //       if (pNewEvent!=m_pActiveEvent)
 //       {

 //           CRect rect = m_pActiveEvent->GetDeviceRect(*GetRefEngine());
 //           m_pActiveEvent->SetActive(FALSE);
 //           InvalidateRect(rect);

 //           pNewEvent->SetActive(TRUE);
 //           rect = pNewEvent->GetDeviceRect(*GetRefEngine());
 //           InvalidateRect(rect);
 //       }
 //   }
 //   else if (pNewEvent!=NULL && m_pActiveEvent==NULL)
 //   {
 //       pNewEvent->SetActive(TRUE);
 //       CRect rect = pNewEvent->GetDeviceRect(*GetRefEngine());
 //       //pNewEvent->DrawSelf(&dc,*GetRefEngine());
 //       InvalidateRect(rect);
 //   }
 //   else if (pNewEvent==NULL && m_pActiveEvent!=NULL )
 //   {
 //       CRect rect = m_pActiveEvent->GetDeviceRect(*GetRefEngine());
 //       m_pActiveEvent->SetActive(FALSE);
 //       //m_pActiveEvent->DrawSelf(&dc,*GetRefEngine());
 //       InvalidateRect(rect);

 //       m_tipCtrl.UpdateTipText(_T(""),this);
 //   }

 //   m_pActiveEvent = pNewEvent;

 //   if (m_pActiveEvent!=NULL)
 //   {
 //       CString strTipInf1,strTipInf2;

 //       strTipInf1.Format(_T("�¼��ص㣺%s"),m_pActiveEvent->m_strCaseAddr);
 //       strTipInf2.Format(_T("\n�¼�������%s"),m_pActiveEvent->m_strContent);

 //       m_tipCtrl.UpdateTipText(strTipInf1+strTipInf2,this);
 //   }


    // Default Call
    CNBMapWnd::OnMouseMove(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////
// �˵�������Ӧ


void CTfcParsedView::OnTfcFlash()
{
    ReDraw();
}

void CTfcParsedView::OnTfcManuflash()
{
    // 
}
