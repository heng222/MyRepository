// TfcInfView.cpp : 实现文件
//

#include "stdafx.h"
#include "Resource.h"
#include "UserColors.h"
#include "InterfaceEx.h"
#include ".\tfcinfview.h"

//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
// CTfcInfView

IMPLEMENT_DYNAMIC(CTfcInfView, CNBMapWnd)
CTfcInfView::CTfcInfView()
{
    m_bShowNodeName = FALSE;
}

CTfcInfView::~CTfcInfView()
{
}


BEGIN_MESSAGE_MAP(CTfcInfView, CNBMapWnd)
    ON_WM_TIMER()
    ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_TFCROAD_PARSE, OnTfcroadParse)
    ON_WM_LBUTTONDOWN()
    ON_COMMAND(ID_TFCROAD_NODENAME, OnTfcroadNodename)
    ON_COMMAND(ID_TFCROAD_SELECTROAD, OnTfcroadSelectroad)
    ON_WM_SETCURSOR()
END_MESSAGE_MAP()



// CTfcInfView 消息处理程序



int CTfcInfView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CNBMapWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    //create tool tip
    if (!m_tipCtrl.Create(this,WS_POPUP|WS_EX_TOOLWINDOW|TTS_ALWAYSTIP) )
    {
        return -1;
    }
    m_tipCtrl.SetMaxTipWidth(200);
    m_tipCtrl.AddTool(this);
    m_tipCtrl.SetTipTextColor(CLR_BLACK);  // 
    m_tipCtrl.SetDelayTime(200);           // 


    m_Menu.LoadMenu(IDR_MENU_TFCROAD);


    // 创建道路解析对话框
    m_dlgRoadAttri.AttachRoad(GetRefEngine()->GetRoadList());
    if ( !m_dlgRoadAttri.Create(CDlgRoadAttri::IDD,this) )
    {
        return -1;
    }
    m_dlgRoadAttri.AddRoadToList();

    return 0;
}


void CTfcInfView::OnDraw(CDC* pDC,CNBMapEngine* /*pEngine*/)
{
    GetRefEngine()->DrawTfcStream(pDC,m_bShowNodeName);


    ShowTipInf();
}


BOOL CTfcInfView::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message == WM_MOUSEMOVE )
    {
        m_tipCtrl.RelayEvent(pMsg); 
    }

    return CNBMapWnd::PreTranslateMessage(pMsg);
}


void CTfcInfView::OnTimer(UINT nIDEvent)
{


    CNBMapWnd::OnTimer(nIDEvent);
}

void CTfcInfView::PreContextMenu(CMenu& aMenu)
{
    aMenu.Attach(m_Menu.GetSubMenu(0)->GetSafeHmenu());
    
    //
    aMenu.CheckMenuItem(ID_TFCROAD_NODENAME,m_bShowNodeName?MF_CHECKED|MF_BYCOMMAND:MF_UNCHECKED|MF_BYCOMMAND );
    //aMenu.CheckMenuItem(ID_TFCROAD_SELECTROAD,MF_CHECKED|MF_BYCOMMAND);
}



void CTfcInfView::ShowTipInf(BOOL bErase)
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
	pDC->SetTextColor(CLR_DARKGREEN);

    pDC->SetBkMode(TRANSPARENT);
    pDC->SetBkMode(OPAQUE);

	CPoint ptTL;
	CRect rectClient,ivdRect;
	CString strInf;

	GetClientRect(&rectClient);


	// 显示当前比例尺
	strInf.Format("比例尺 1:%ld",GetRefEngine()->GetCurZoomScale());
	ptTL = CPoint(rectClient.right-120,rectClient.top+30);
	ivdRect = CRect(ptTL,pDC->GetTextExtent(strInf));
	/*if (bErase)
	{
		InvalidateRect(&ivdRect);
	}*/
	pDC->TextOut(ptTL.x,ptTL.y,strInf);



	// 显示当前坐标
	TMPoint mapPos;
	GetRefEngine()->DpToLp(m_ptCurrent,mapPos);
	strInf.Format(_T("坐标 %.3f, %.3f"),mapPos.iX/24.0/3600,mapPos.iY/24/3600.0);
	//pDC->SetBkMode(OPAQUE);
	ptTL = CPoint(rectClient.right-140,rectClient.bottom-30);
	ivdRect = CRect(ptTL,pDC->GetTextExtent(strInf));
	/*if (bErase)
	{
        CNBMapWnd::InvalidateRect(&ivdRect);
	}*/
	pDC->TextOut(ptTL.x,ptTL.y,strInf);


	// 
    pDC->SelectObject(pOldFont);

    ReleaseMemDC();

    //
    Invalidate();

}


void CTfcInfView::OnStateChanged(int aNewState,int aOldState)
{

}

void CTfcInfView::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (GetOperationState()==EPER_SELECTION)
    {
        CClientDC dc(this);

        // 得到选中的道路
        CTfcRoadList roadList;
        TMPoint mPt;
        GetRefEngine()->DpToLp(point,mPt);
        GetRefEngine()->GetRoadByPoint(mPt,roadList);

        //
        GetRefEngine()->SetActivedRoad(roadList);
        ReDraw();


        // 显示选中的道路，提示用户选择要解析的道路
        POSITION pos = roadList.GetHeadPosition();
        PTRawRoadTfcInf pRoad = NULL;
        while (pos)
        {
            pRoad = roadList.GetNext(pos);

        }

        // 解析指定的道路
        if (pRoad!=NULL)
        {
            TImcMsg msg(EMSG_PARSE_LOOKUP,ID_MODULE_DATABASE,ID_MODULE_DATABASE);
            msg.m_wParam = (WPARAM)(&(pRoad->strRoadID));
            NbsSendModuleMsg(&msg);

            TRACE("解析道路（%s-%s）\n",pRoad->strStartName,pRoad->strEndName);
        }
    }


    // TODO: 在此添加消息处理程序代码和/或调用默认值

    CNBMapWnd::OnLButtonDown(nFlags, point);
}

void CTfcInfView::OnMouseMove(UINT nFlags, CPoint point)
{

    m_ptCurrent = point;

	// 
    if (GetOperationState()!=EOPER_MOVING)
    {
        ShowTipInf(TRUE);
    }

	// 
	CNBMapWnd::OnMouseMove(nFlags, point);

}

//////////////////////////////////////////////////////////////////////////
// 菜单命令响应


void CTfcInfView::OnTfcroadParse()
{
    // 显示
    m_dlgRoadAttri.ShowWindow(SW_NORMAL);

}

void CTfcInfView::OnTfcroadNodename()
{
    m_bShowNodeName = !m_bShowNodeName;

    ReDraw();
}

void CTfcInfView::OnTfcroadSelectroad()
{
     SetOperationState(EPER_SELECTION);
}

BOOL CTfcInfView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
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
