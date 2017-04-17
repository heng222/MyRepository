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
    m_wStyle = ES_TFCNODE;
}

CTfcParsedView::~CTfcParsedView()
{
}


BEGIN_MESSAGE_MAP(CTfcParsedView, CNBMapWnd)
    ON_WM_TIMER()
    ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_LINK_SELECTION, OnLinkSelection)
    ON_WM_SETCURSOR()
    ON_WM_LBUTTONDOWN()
    ON_COMMAND(ID_LINK_TFCNODE, OnLinkTfcnode)
    ON_COMMAND(ID_LINK_NODENAME, OnLinkNodename)
    ON_COMMAND(ID_LINK_DIRECTION, OnLinkDirection)
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
    GetRefEngine()->DrawLink(pDC);

    if (m_wStyle&ES_TFCNODE)
    {
        GetRefEngine()->DrawRoadNode(pDC);
    }

    if (m_wStyle&ES_NODENAME)
    {
        GetRefEngine()->DrawNodeName(pDC);
    }


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
    aMenu.CheckMenuItem(ID_LINK_TFCNODE,m_wStyle&ES_TFCNODE?MF_CHECKED|MF_BYCOMMAND:MF_UNCHECKED|MF_BYCOMMAND );
    aMenu.CheckMenuItem(ID_LINK_NODENAME,m_wStyle&ES_NODENAME?MF_CHECKED|MF_BYCOMMAND:MF_UNCHECKED|MF_BYCOMMAND );
    aMenu.CheckMenuItem(ID_LINK_DIRECTION,m_wStyle&ES_LINKDIRE?MF_CHECKED|MF_BYCOMMAND:MF_UNCHECKED|MF_BYCOMMAND );
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

	pDC->SetBkMode(TRANSPARENT);

	CPoint ptTL;
	CRect rectClient,ivdRect;
	CString strInf;

	GetClientRect(&rectClient);


	// ��ʾ��ǰ������
	strInf.Format("������ 1:%ld",GetRefEngine()->GetCurZoomScale());
	ptTL = CPoint(rectClient.right-120,rectClient.top+30);
	ivdRect = CRect(ptTL,pDC->GetTextExtent(strInf));
    pDC->SetBkMode(OPAQUE);
	/*if (bErase)
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
	ivdRect = CRect(ptTL,pDC->GetTextExtent(strInf));
	if (bErase)
	{
		InvalidateRect(&ivdRect);
	}
	pDC->TextOut(ptTL.x,ptTL.y,strInf);


	// 
	pDC->SelectObject(pOldFont);
    //

    ReleaseMemDC();

    // 
    Invalidate(FALSE);

}


void CTfcParsedView::OnStateChanged(int aNewState,int aOldState)
{

}


void CTfcParsedView::OnMouseMove(UINT nFlags, CPoint point)
{
    m_ptCurrent = point;

    // 
    if (GetOperationState()!=EOPER_MOVING)
    {
        ShowTipInf(TRUE);
    }

    // First call
    CNBMapWnd::OnMouseMove(nFlags, point);

}


//////////////////////////////////////////////////////////////////////////
// �˵�������Ӧ
void CTfcParsedView::OnMenuOperation(UINT nID)
{
    // Add your code here

    // 
    CNBMapWnd::OnMenuOperation(nID);
}

void CTfcParsedView::OnLinkSelection()
{
    SetOperationState(EPER_SELECTION);
}

BOOL CTfcParsedView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
    int iState = GetOperationState();

    if (EPER_SELECTION==iState)
    {
        SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_SELECTION));
        return TRUE;
        //return CWnd::OnSetCursor(pWnd, nHitTest, message);
    }
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

    return CNBMapWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CTfcParsedView::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (GetOperationState()==EPER_SELECTION)
    {
        CClientDC dc(this);
        CDC* pDC = &dc;

        // ���ݵ�ǰ�㹹��ѡ������
        int iWidth = 10;
        CRect rectSelection(CPoint(point.x-iWidth/2,point.y-iWidth/2),CSize(iWidth,iWidth));
        TMRect mapRectSelect;
        GetRefEngine()->DrToLr(rectSelection,mapRectSelect);


        // ������mapRectSelect�е�Link
        CLinkList linkList;
        BOOL bFound = GetRefEngine()->GetLinkByRect(mapRectSelect,linkList);

        
        // ��ʾѡ�е�Link
        GetRefEngine()->ActiveLink(linkList);
        ReDraw();

        // ��ʾѡ�е�Link����
        if (bFound)
        {
            CDlgLinkAttri dlg;
            dlg.AttachLink(&linkList);
            dlg.DoModal();
        }

    }
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

    CNBMapWnd::OnLButtonDown(nFlags, point);
}

void CTfcParsedView::OnLinkTfcnode()
{
    if (m_wStyle&ES_TFCNODE)
    {
        m_wStyle &= ~ES_TFCNODE;
    }
    else
    {
        m_wStyle |= ES_TFCNODE;
    }

    ReDraw();
}

void CTfcParsedView::OnLinkNodename()
{
    if (m_wStyle&ES_NODENAME)
    {
        m_wStyle &= ~ES_NODENAME;
    }
    else
    {
        m_wStyle |= ES_NODENAME;
    }

    ReDraw();
}

void CTfcParsedView::OnLinkDirection()
{ 
    if (m_wStyle&ES_LINKDIRE)
    {
        m_wStyle &= ~ES_LINKDIRE;
    }
    else
    {
        m_wStyle |= ES_LINKDIRE;
    }

    ReDraw();
    
}
