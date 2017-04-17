

#include "stdafx.h"

#include "WeatherInfDlg.h"
#include "DistrictView.h"
#include "resource.h"
#include "UserColors.h"
#include ".\districtview.h"


//////////////////////////////////////////////////////////////////////////

#define ID_FLASH_CLOCK         100     // 气象信息刷新计时器
#ifdef _DEBUG
    #define FLASH_INTERVAL         (60000)
#else
    #define FLASH_INTERVAL         (3*3600*1000)
#endif

//////////////////////////////////////////////////////////////////////////


IMPLEMENT_DYNAMIC(CDistrictView, CNBMapWnd)

CDistrictView::CDistrictView()
{
    m_pActiveDistrict = NULL;
    m_bInfTip = FALSE;
}

CDistrictView::~CDistrictView()
{
}


BEGIN_MESSAGE_MAP(CDistrictView, CNBMapWnd)
    ON_COMMAND(ID_MENU_INFTIP, OnMapoperInfPrompt)
    ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_MENU_WTHINF, OnMapoperWthinf)
    ON_WM_TIMER()
    ON_WM_CREATE()
    ON_WM_MOUSEWHEEL()
    ON_COMMAND(ID_WTHMENU_FLASHWEATHER, OnWthmenuFlashweather)
END_MESSAGE_MAP()

int CDistrictView::OnCreate(LPCREATESTRUCT lpCreateStruct)
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


	m_Menu.LoadMenu(IDR_POPMENU_WTHVIEW);

	// 
	SetTimer(ID_FLASH_CLOCK,FLASH_INTERVAL,NULL);

    return 0;
}



void CDistrictView::OnDraw(CDC* pDC,CNBMapEngine* /*pEngine*/)
{
    CBJDistrictMgr* pDistMgr = GetRefEngine();

    // Draw all districts
    if (pDistMgr!=NULL)
    {
        pDistMgr->Draw(pDC);
    }

    // Draw active districts
    /*if (m_pActiveDistrict)
    {
        m_pActiveDistrict->DrawRegion(pDC);
        m_pActiveDistrict->DrawName(pDC,*pDistMgr);
    }*/

    ShowTipInf();
}

BOOL CDistrictView::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message == WM_MOUSEMOVE )
    {
        m_tipCtrl.RelayEvent(pMsg); 
    }

    //
    return CNBMapWnd::PreTranslateMessage(pMsg);
}

//////////////////////////////////////////////////////////////////////////
// 菜单命令
void CDistrictView::OnMapoperInfPrompt()
{
    if ( m_bInfTip )
    {
        if (m_pActiveDistrict)
        {
            CDC* pDC = GetMemDC();
            m_pActiveDistrict->SetActive(FALSE);
            m_pActiveDistrict->DrawRegion(pDC,*GetRefEngine());
            m_pActiveDistrict->DrawName(pDC,*GetRefEngine());
            ReleaseMemDC();

            Invalidate();
        }
        m_tipCtrl.UpdateTipText("",this);
    }

    m_bInfTip = !m_bInfTip;
}

void CDistrictView::OnStateChanged(int /*aNewState*/,int /*aOldState*/)
{
    /*if (m_pActiveDistrict)
    {
        CClientDC dc(this);
        m_pActiveDistrict->SetActive(FALSE);
        m_pActiveDistrict->DrawRegion(&dc);
        m_pActiveDistrict->DrawName(&dc,*GetRefEngine());
        m_pActiveDistrict = NULL;
        m_tipCtrl.UpdateTipText("",this);
    }*/
}


void CDistrictView::OnMapoperWthinf()
{
    // Show weather inf dialog
    CWeatherInfDlg dlg;
    dlg.DoModal();
}

void CDistrictView::OnWthmenuFlashweather()
{
    (GetRefEngine())->RetrieveWthInf();
    ShowTipInf(TRUE);
}

//////////////////////////////////////////////////////////////////////////
// 
void CDistrictView::PreContextMenu(CMenu& aMenu)
{
    aMenu.Attach(m_Menu.GetSubMenu(0)->GetSafeHmenu());

    aMenu.CheckMenuItem(ID_MENU_INFTIP,
        m_bInfTip?MF_CHECKED|MF_BYCOMMAND:MF_UNCHECKED|MF_BYCOMMAND );

}


void CDistrictView::OnMouseMove(UINT nFlags, CPoint point)
{
    m_ptCurrent = point;

    // 
    if (GetOperationState()!=EOPER_MOVING)
    {
        ShowTipInf(TRUE);

        //
        if (m_bInfTip)
        {

            CDC* pDC = GetMemDC();
            if (pDC==NULL)
            {
                return;
            }

            TDistrict* pNewDistrict = GetRefEngine()->GetDistrict(point);

            if (m_pActiveDistrict!=NULL && pNewDistrict!=NULL)
            {
                if (m_pActiveDistrict!=pNewDistrict)
                {
                    m_pActiveDistrict->SetActive(FALSE);
                    m_pActiveDistrict->DrawRegion(pDC,*GetRefEngine());
                    m_pActiveDistrict->DrawName(pDC,*GetRefEngine());
                    TMRect mRect = m_pActiveDistrict->m_boxRect;
                    CRect rect;
                    GetRefEngine()->LrToDr(mRect,rect);
                    //InvalidateRect(rect,FALSE);
                    Invalidate();

                    pNewDistrict->SetActive(TRUE);
                    pNewDistrict->DrawRegion(pDC,*GetRefEngine());
                    pNewDistrict->DrawName(pDC,*GetRefEngine());
                }
            }
            else if (m_pActiveDistrict==NULL && pNewDistrict!=NULL)
            {
                pNewDistrict->SetActive(TRUE);
                pNewDistrict->DrawRegion(pDC,*GetRefEngine());
                pNewDistrict->DrawName(pDC,*GetRefEngine());
            }
            else if (m_pActiveDistrict!=NULL && pNewDistrict==NULL)
            {
                m_pActiveDistrict->SetActive(FALSE);
                m_pActiveDistrict->DrawRegion(pDC,*GetRefEngine());
                m_pActiveDistrict->DrawName(pDC,*GetRefEngine());

                m_tipCtrl.UpdateTipText(_T(""),this);
            }
            m_pActiveDistrict = pNewDistrict;

            // Update the text of the TipCtrl.
            if (m_pActiveDistrict!=NULL)
            {
                CString strTipInf=m_pActiveDistrict->m_strDistName+_T("\n\n");

                CWthInfList& wthList = m_pActiveDistrict->m_WthInfList;
                POSITION pos = wthList.GetHeadPosition();
                if (pos)
                {
                    while (pos)
                    {
                        PTWeatherInf pWth = wthList.GetNext(pos);
                        CString strWth;
                        pWth->GetWetherDescription(strWth);
                        strTipInf += strWth;
                        strTipInf += pWth->publishTime.Format("。发布时间 %Y-%m-%d %H:%M:%S");
                        if (pos)
                        {
                            strTipInf += CString("\n\n");
                        }
                    }
                }
                else
                {
                    strTipInf += _T("读取气象信息失败！");
                }

                m_tipCtrl.UpdateTipText(strTipInf,this);
            }

            ReleaseMemDC();
        }
    }

    // 
    CNBMapWnd::OnMouseMove(nFlags, point);
}

void CDistrictView::OnTimer(UINT nIDEvent)
{
    // 
    switch(nIDEvent)
    {
    case ID_FLASH_CLOCK:
        {
            (GetRefEngine())->RetrieveWthInf();
            ShowTipInf(TRUE);
        }
    	break;
    }

    CNBMapWnd::OnTimer(nIDEvent);
}

void CDistrictView::ShowTipInf(BOOL bErase)
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

    pDC->SetBkMode(OPAQUE);

	CPoint ptTL;
	CRect rectClient,ivdRect;
	CString strInf;

    GetClientRect(&rectClient);


    // 显示更新时间
    strInf = (GetRefEngine())->GetFlashTime().Format(_T("刷新时间：%Y-%m-%d %H:%M:%S"));
	ptTL = CPoint(20,30);
	ivdRect = CRect(ptTL,pDC->GetTextExtent(strInf));
	/*if (bErase)
	{
		InvalidateRect(&ivdRect);
	}*/
	pDC->TextOut(ptTL.x,ptTL.y,strInf);



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
        InvalidateRect(&ivdRect);
    }*/
    pDC->TextOut(ptTL.x,ptTL.y,strInf);


    // 
    pDC->SelectObject(pOldFont);

    //
    ReleaseMemDC();

    Invalidate();

}

BOOL CDistrictView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    // 

    return CNBMapWnd::OnMouseWheel(nFlags, zDelta, pt);
}

