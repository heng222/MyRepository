// TfcInfView.cpp : 实现文件
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



// CTfcParsedView 消息处理程序



int CTfcParsedView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CNBMapWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  在此添加您专用的创建代码
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

	// 设置默认字体
	CFont  font;
	int iFontHeight;
	iFontHeight = 12;
	font.CreateFont(iFontHeight,0, 0, 0, FW_THIN, false, false, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, "宋体");


	CFont* pOldFont = pDC->SelectObject(&font);
	pDC->SetTextColor(CLR_BLUE);

	pDC->SetBkMode(TRANSPARENT);

	CPoint ptTL;
	CRect rectClient,ivdRect;
	CString strInf;

	GetClientRect(&rectClient);


	// 显示当前比例尺
	strInf.Format("比例尺 1:%ld",GetRefEngine()->GetCurZoomScale());
	ptTL = CPoint(rectClient.right-120,rectClient.top+30);
	ivdRect = CRect(ptTL,pDC->GetTextExtent(strInf));
    pDC->SetBkMode(OPAQUE);
	/*if (bErase)
	{
		InvalidateRect(&ivdRect);
	}*/
	pDC->TextOut(ptTL.x,ptTL.y,strInf);



	// 显示当前坐标
	TMPoint mapPos;
	GetRefEngine()->DpToLp(m_ptCurrent,mapPos);
	strInf.Format(_T("坐标 %.3f, %.3f"),mapPos.iX/24.0/3600,mapPos.iY/24/3600.0);
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
// 菜单命令响应
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
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    return CNBMapWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CTfcParsedView::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (GetOperationState()==EPER_SELECTION)
    {
        CClientDC dc(this);
        CDC* pDC = &dc;

        // 根据当前点构造选择区域
        int iWidth = 10;
        CRect rectSelection(CPoint(point.x-iWidth/2,point.y-iWidth/2),CSize(iWidth,iWidth));
        TMRect mapRectSelect;
        GetRefEngine()->DrToLr(rectSelection,mapRectSelect);


        // 计算在mapRectSelect中的Link
        CLinkList linkList;
        BOOL bFound = GetRefEngine()->GetLinkByRect(mapRectSelect,linkList);

        
        // 显示选中的Link
        GetRefEngine()->ActiveLink(linkList);
        ReDraw();

        // 显示选中的Link属性
        if (bFound)
        {
            CDlgLinkAttri dlg;
            dlg.AttachLink(&linkList);
            dlg.DoModal();
        }

    }
    // TODO: 在此添加消息处理程序代码和/或调用默认值

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
