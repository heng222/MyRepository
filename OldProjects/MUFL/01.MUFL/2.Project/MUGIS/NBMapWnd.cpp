// NBMapWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "NBMapWnd.h"
#include "UserColors.h"
#include "Resource.h"
#include ".\nbmapwnd.h"


//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
// CNBMapWnd

IMPLEMENT_DYNAMIC(CNBMapWnd, CWnd)



CNBMapWnd::CNBMapWnd()
{
    m_pEngineRef = NULL;
    m_pWndParent = NULL;
    m_iOperState = EOPER_NORMAL;
    m_wNbShowStyle = ESS_GRID;


    InitializeCriticalSection(&m_CriticalSection);
}

CNBMapWnd::~CNBMapWnd()
{
    DeleteCriticalSection(&m_CriticalSection);
}


BEGIN_MESSAGE_MAP(CNBMapWnd, CWnd)

    ON_WM_PAINT()
    ON_WM_CONTEXTMENU()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_SETCURSOR()
    ON_WM_MOUSEWHEEL()
    ON_WM_SIZE()

    ON_COMMAND_RANGE(ID_MAPOPER_START, ID_MAPOPER_RESERVED, OnMenuOperation)

    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


void CNBMapWnd::AttachEngine(CNBMapEngine* pEngine)
{
	m_pEngineRef = pEngine;
}

CNBMapEngine* CNBMapWnd::RetrieveEngine()
{
    return m_pEngineRef;
}

BOOL CNBMapWnd::Create(CWnd* pReferWnd)
{
    ASSERT( pReferWnd != NULL );
    ASSERT(m_pEngineRef!=NULL);

    m_pWndParent = pReferWnd;


    // Get the client rectangle.
    CRect clientRect;
    pReferWnd->GetClientRect(clientRect);

    if ( !CWnd::Create(NULL,_T(""),WS_CHILD|WS_VISIBLE,clientRect,pReferWnd,50) )
    {
        return FALSE;
    }


    // Initialize engine's attributes.
    CClientDC dc(pReferWnd);
    int phyWidth = dc.GetDeviceCaps(HORZSIZE); 
    int iPixWidth = dc.GetDeviceCaps(HORZRES); 
    DOUBLE scale = DOUBLE(phyWidth)/iPixWidth; 
	// Initialize map engine.
    TEgAttri ea;
	ea.fPhysicPerDevice = scale;
    ea.rectDevice = clientRect;
    
    BOOL bFlag = m_pEngineRef->Initialize(ea);
    if (!bFlag)
    {
        return FALSE;
    }



    // Calculate line position  to draw grids.

    const MGridManager* pGridMgr = m_pEngineRef->GetGridMgr();
    int iNumOfRow = pGridMgr->GetNumOfRow();
    int iNumOfCol = pGridMgr->GetNumOfCol();
    int iPtCount = (iNumOfCol+1)*2 + (iNumOfRow+1)*2;
    CSize sizeGrid = pGridMgr->GetGridSize();

    TLcType lXmin = pGridMgr->GetMapRect().iTl.iX;
    TLcType lYmin = pGridMgr->GetMapRect().iBr.iY;

    TLcType lXmax = pGridMgr->GetMapRect().iBr.iX;
    TLcType lYmax = pGridMgr->GetMapRect().iTl.iY;

    m_ptArrayGrid.SetSize(0,iPtCount);

    TMPoint pt1,pt2;
    pt1.iY = lYmin;
    pt2.iY = lYmin+iNumOfRow*sizeGrid.cy;
    for (int i=0; i<=iNumOfCol; i++)
    {
        pt1.iX = lXmin+i*sizeGrid.cx;
        pt2.iX = pt1.iX;

        m_ptArrayGrid.Add(pt1);
        m_ptArrayGrid.Add(pt2);
    }

    pt1.iX = lXmin;
    pt2.iX = lXmin+iNumOfCol*sizeGrid.cx;
    for (int j=0; j<=iNumOfRow; j++)
    {
        pt1.iY = lYmin+j*sizeGrid.cy;

        pt2.iY = pt1.iY;

        m_ptArrayGrid.Add(pt1);
        m_ptArrayGrid.Add(pt2);
    }

    // Determine whether show the grids.
    if (iNumOfCol*iNumOfRow==1)
    {
        m_wNbShowStyle &= ~ESS_GRID;
    }

    // Draw
    ReDraw();

    // 
    return TRUE;
}

void CNBMapWnd::CreateMemDC()
{
    EnterCriticalSection(&m_CriticalSection);

    // Delete the old DC
    m_bmpMemory.DeleteObject();
    m_dcMemory.DeleteDC();

    // Create new
    CRect rectClient;
    GetClientRect(&rectClient);

    CClientDC dc(this);
    CDC* pDC = &dc;

    m_dcMemory.CreateCompatibleDC(pDC);

    m_bmpMemory.CreateCompatibleBitmap(pDC, rectClient.Width(), rectClient.Height());

    m_dcMemory.SelectObject(&m_bmpMemory);
    m_dcMemory.SetBkColor(CLR_WHITE);
    m_dcMemory.SetTextColor(CLR_BLACK);

    m_dcMemory.FillSolidRect(0, 0, rectClient.Width(), rectClient.Height(),CLR_WHITE);// 默认背景色

    // Set default font
    CFont  font;
    int iFontHeight;
    iFontHeight = 16;
    font.CreateFont(iFontHeight,0, 0, 0, FW_NORMAL, false, false, 0,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, _T("宋体"));
    CFont* pOldFont = m_dcMemory.SelectObject(&font);
    m_dcMemory.SetTextColor(RGB(0,0,0));
    m_dcMemory.SetBkMode(TRANSPARENT);

    // Set default pen
    CPen   pen;
    pen.CreatePen(PS_SOLID,1,CLR_BLACK);
    m_dcMemory.SelectObject(&pen);

    // Set default brush
    CBrush brush;
    brush.CreateSolidBrush(CLR_BLACK);
    m_dcMemory.SelectObject(&brush);

    //
    LeaveCriticalSection(&m_CriticalSection);
}

CDC* CNBMapWnd::GetMemDC()
{
    if (m_dcMemory.GetSafeHdc())
    {
        EnterCriticalSection(&m_CriticalSection);
        return &m_dcMemory;
    }
    else
    {
        return NULL;
    }
}

void CNBMapWnd::ReleaseMemDC()
{
    LeaveCriticalSection(&m_CriticalSection);
}


// CNBMapWnd 消息处理程序


BOOL CNBMapWnd::OnEraseBkgnd(CDC* pDC)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    //return TRUE;
    return CWnd::OnEraseBkgnd(pDC);

}

//void CNBMapWnd::Invalidate(BOOL bErase /*= TRUE*/)
//{
//    CWnd::Invalidate(bErase);
//}
//
//void CNBMapWnd::InvalidateRect(LPCRECT lpRect, BOOL bErase /*= TRUE*/)
//{
//    if (bErase)
//    {
//        CRect rect(lpRect);
//        m_dcMemory.FillSolidRect(rect.left,rect.top,  rect.Width(), rect.Height(),CLR_WHITE);// 默认背景色
//    }
//
//    CWnd::Invalidate();
//}

void CNBMapWnd::ReDraw(BOOL bErase/* = TRUE*/)
{
    CDC* pDC = GetMemDC();

    if (pDC->GetSafeHdc()==NULL)
    {
        return;
    }

    // 
    if (bErase)
    {
        // Erase background
        CRect rectClient;
        GetClientRect(&rectClient);
        pDC->FillSolidRect(0, 0, rectClient.Width(), rectClient.Height(),CLR_WHITE);// 默认背景色
    }

    // Draw grid
    if (m_wNbShowStyle&ESS_GRID)
    {
        DrawGrid(pDC);
    }

    // Drawing ...
    OnDraw(pDC,m_pEngineRef);

    // Send WM_PAINT message
    Invalidate(FALSE);

    // 
    ReleaseMemDC();
}

void CNBMapWnd::OnPaint()
{
    CDC* pMemDC = GetMemDC();

    if (pMemDC==NULL)
    {
        return;
    }

    // 
    PAINTSTRUCT ps;
    CDC* pDC = BeginPaint(&ps);

    // 
    CRect rectClient;
    GetClientRect(&rectClient);

    // Copies the bitmap to the device context.
    pDC->BitBlt( m_ptNbEnd.x-m_ptNbStart.x, m_ptNbEnd.y-m_ptNbStart.y,
        rectClient.Width(), rectClient.Height(),pMemDC,0,0,SRCCOPY);

    // 
    EndPaint(&ps);

    // 
    ReleaseMemDC();
}


void CNBMapWnd::DrawGrid(CDC* pDC)
{
    const MGridManager* pGridMgr = m_pEngineRef->GetGridMgr();

    CPen newPen;

    // 设置网格画笔
    newPen.CreatePen(PS_SOLID,1,CLR_LIGHTGRAY);
    CPen* pOldPen = pDC->SelectObject(&newPen);
    

    // 设置字体
    CSize sizeGrid = pGridMgr->GetGridSize();
    int iFontHeight = int(m_pEngineRef->LlToDl(sizeGrid.cy)*0.3); // 字体的高度＝网格的高度×0.8
    CFont  font;
    font.CreateFont(iFontHeight,0, 0, 0, FW_NORMAL, false, false, 0,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, _T("宋体"));
    CFont* pOldFont = pDC->SelectObject(&font);
    pDC->SetTextColor(CLR_LIGHTGRAY);
    pDC->SetBkMode(TRANSPARENT);



    // 绘制网格
    INT_PTR iCount = m_ptArrayGrid.GetCount();
    ASSERT(iCount%2==0);
    CPoint pt1,pt2;

    for (INT_PTR i=0; i<iCount; i+=2)
    {
        m_pEngineRef->LpToDp(m_ptArrayGrid.GetAt(i),pt1);
        m_pEngineRef->LpToDp(m_ptArrayGrid.GetAt(i+1),pt2);
        pDC->MoveTo(pt1);
        pDC->LineTo(pt2);
    }

    // 标注网格编号
    int iNumRow = pGridMgr->GetNumOfRow();
    int iNumCol = pGridMgr->GetNumOfCol();
    for (int i=0; i<iNumRow; i++)
    {
        for (int j=0; j<iNumCol; j++)
        {
            TMRect gridRect = pGridMgr->GetRectByNo(i,j);
            CRect rectGrid;

            m_pEngineRef->LrToDr(gridRect,rectGrid);

            CPoint ptCenter = rectGrid.CenterPoint();


            CString strComment;
            strComment.Format(_T("%d,%d"),i,j);
            CSize size = pDC->GetTextExtent(strComment);
            pDC->TextOut(ptCenter.x-size.cx/2,ptCenter.y,strComment);
        }
    }


    // 
    pDC->SelectObject(pOldPen);
    newPen.DeleteObject();
    pDC->SelectObject(pOldFont);
    font.DeleteObject();
}

void CNBMapWnd::PreContextMenu(CMenu& aMenu)
{
}

void CNBMapWnd::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
    CMenu submenu;

    PreContextMenu(submenu);

    int iOrginCount = 0;

    if (submenu.GetSafeHmenu()!=NULL)
    {
        iOrginCount = submenu.GetMenuItemCount();
        submenu.AppendMenu(MF_SEPARATOR);
    }
    else
    {
        submenu.CreatePopupMenu();
    }
    

    // 添加自身菜单
    UINT nFlags = 0;

    /*nFlags = (m_wOperFlag==EOPER_PREMOVE) ? MF_STRING|MF_CHECKED|MFT_RADIOCHECK : MF_STRING|MF_UNCHECKED;
    submenu.AppendMenu(nFlags,ID_MAPOPER_MOVE,"移动地图(&M)\tCtrl+M");*/
    //pMenu->CheckMenuItem(ID_MAPOPER_MOVE,m_wOperFlag==EOPER_ZOOMOUT?MF_CHECKED|MF_BYCOMMAND:MF_UNCHECKED|MF_BYCOMMAND );
  
    nFlags = (m_iOperState==EOPER_ZOOMIN) ? MF_STRING|MF_CHECKED|MFT_RADIOCHECK : MF_STRING|MF_UNCHECKED;
    submenu.AppendMenu(nFlags,ID_MAPOPER_ZOOMIN,_T("放大地图(&I)\tCtrl+I"));

    nFlags = (m_iOperState==EOPER_ZOOMOUT) ? MF_STRING|MF_CHECKED|MFT_RADIOCHECK : MF_STRING|MF_UNCHECKED;
    submenu.AppendMenu(nFlags,ID_MAPOPER_ZOOMOUT,_T("缩小地图(&O)\tCtrl+O"));


    nFlags = (m_iOperState==EOPER_NORMAL) ? MF_STRING|MF_CHECKED|MFT_RADIOCHECK : MF_STRING|MF_UNCHECKED;
    submenu.AppendMenu(nFlags,ID_MAPOPER_RESET,_T("复位(&R)\tCtrl+R"));

    //
    submenu.AppendMenu(MF_SEPARATOR);

    nFlags = (m_wNbShowStyle&ESS_GRID) ? MF_STRING|MF_CHECKED : MF_STRING|MF_UNCHECKED;
    submenu.AppendMenu(nFlags,ID_MAPOPER_GRID,_T("显示网格(&G)\tCtrl+G"));


    // 弹出菜单
    submenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,point.x,point.y,this);
    
    UINT uPresentCount = submenu.GetMenuItemCount();
    for(UINT i=0; i<uPresentCount-iOrginCount; i++){
        submenu.DeleteMenu(iOrginCount,MF_BYPOSITION);
    }

    submenu.Detach();

}

void CNBMapWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (m_iOperState==EOPER_NORMAL)
    {
        m_iOperState = EOPER_MOVING;
        //SetCursor(AfxGetApp()->LoadCursor(IDC_BTN_DOWN));
        SetStartPosition(point);
        m_ptNbEnd = point;
        SetCapture();
    }
    else if (m_iOperState==EOPER_MOVING)
    {
        // Do nothing...
    }
    else if ((m_iOperState==EOPER_ZOOMIN) || (m_iOperState==EOPER_ZOOMOUT))
    {
        ZoomMap(point,(m_iOperState==EOPER_ZOOMIN));
    }

    CWnd::OnLButtonDown(nFlags, point);
}

void CNBMapWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (m_iOperState==EOPER_MOVING)
    {
        m_ptNbEnd = point;

        //
        SetCursor(AfxGetApp()->LoadCursor(IDC_DISTSEL));

        // 
        m_iOperState = EOPER_NORMAL;

        ReleaseCapture();
        
        if (m_ptNbEnd!=m_ptNbStart)
        {
            MoveMap();
        }
    }

    CWnd::OnLButtonUp(nFlags, point);
}

void CNBMapWnd::OnMouseMove(UINT nFlags, CPoint point)
{
    if (m_iOperState==EOPER_MOVING && nFlags&MK_LBUTTON)
    {
        m_ptNbEnd = point;

        // 移动内存中的DC
        CRect rectClient;
        GetClientRect(&rectClient);
        CClientDC clientDC(this);

        clientDC.FillSolidRect(0, 0, rectClient.Width(), rectClient.Height(),CLR_WHITE);

        //clientDC.BitBlt(point.x-m_ptNbStart.x,point.y-m_ptNbStart.y,
        //    rectClient.Width(), rectClient.Height(),&m_dcMemory,0,0,SRCCOPY);
        //

        Invalidate(FALSE);
    } 
    
    // 
    CWnd::OnMouseMove(nFlags, point);
}

BOOL CNBMapWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
    if (m_iOperState==EOPER_NORMAL || m_iOperState==EOPER_MOVING)
    {
        SetCursor(AfxGetApp()->LoadCursor(IDC_DISTSEL));
        return TRUE;
    }
    /*else if (m_wOperFlag == EOPER_PREMOVE)
    {
        SetCursor(AfxGetApp()->LoadCursor(IDC_BTN_MOVE));
        return TRUE;
    }
    else if ( m_wOperFlag == EOPER_MOVING)
    {
        SetCursor(AfxGetApp()->LoadCursor(IDC_BTN_DOWN));
        return TRUE;
    }*/
    else if (m_iOperState==EOPER_ZOOMIN)
    {
        SetCursor(AfxGetApp()->LoadCursor(IDC_ZOOMIN));
        return TRUE;
    }
    else if (m_iOperState==EOPER_ZOOMOUT)
    {
        SetCursor(AfxGetApp()->LoadCursor(IDC_ZOOMOUT));
        return TRUE;
    }
    else
    {
        SetCursor(AfxGetApp()->LoadCursor(IDC_DISTSEL));
        return TRUE;
    }

    return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CNBMapWnd::SetStartPosition(CPoint newPoint)
{
    m_ptNbStart = newPoint;
}

void CNBMapWnd::MoveMap()
{
    // Building a Vector.
    TMPoint mPtStart,mPtEnd;
    m_pEngineRef->DpToLp(m_ptNbStart,mPtStart);
    m_pEngineRef->DpToLp(m_ptNbEnd,mPtEnd);
    TVector vMove(mPtEnd,mPtStart);

    // Move map along the vector that just building.
    m_pEngineRef->MapOperation(CNBMapEngine::EMO_MOVE_VECTOR,(WPARAM)&vMove);
    
    //
    SetStartPosition(m_ptNbEnd);

    // Drawing ... 
    ReDraw();
}

void CNBMapWnd::ZoomMap(CPoint aCenter,BOOL bZoomIn /* = TRUE */)
{
    TMPoint newCenter;
    m_pEngineRef->DpToLp(aCenter,newCenter);

    if (bZoomIn)
    {
        m_pEngineRef->MapOperation(CNBMapEngine::EMO_MAP_ZOOMIN,(WPARAM)&newCenter);
    }
    else
    {
        m_pEngineRef->MapOperation(CNBMapEngine::EMO_MAP_ZOOMOUT,(WPARAM)&newCenter);
    }

    // Drawing ...
    ReDraw();
}

void CNBMapWnd::OnMenuOperation(UINT nID)
{
    int oldState = m_iOperState;

    switch(nID)
    {
    case ID_MAPOPER_RESET:
        {
            m_iOperState = EOPER_NORMAL;
        }
        break;

    /*case ID_MAPOPER_MOVE:
        {
            m_wOperFlag = EOPER_PREMOVE;
        }        
    	break;*/

    case ID_MAPOPER_ZOOMIN:
        {
            m_iOperState = EOPER_ZOOMIN;
        }
    	break;

    case ID_MAPOPER_ZOOMOUT:
        {
            m_iOperState = EOPER_ZOOMOUT;
        }
        break;

    case ID_MAPOPER_GRID:
        {
            if (m_wNbShowStyle&ESS_GRID)
            {
                m_wNbShowStyle &= ~ESS_GRID;
            }
            else
            {
                m_wNbShowStyle |= ESS_GRID;
            }

            // Drawing ...
            ReDraw();
        }
        break;
    }

    if (oldState!=m_iOperState)
    {
        OnStateChanged(m_iOperState,oldState);
    }
}

void CNBMapWnd::OnStateChanged(int /*aNewState*/,int /*aOldState*/)
{

}

BOOL CNBMapWnd::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
#if 0

    if (/*m_wOperFlag==EOPER_ZOOMIN &&*/ zDelta>0)
    {
        ZoomMap(pt,TRUE);
    }
    else if (/*m_wOperFlag==EOPER_ZOOMOUT && */zDelta<0)
    {
        ZoomMap(pt,FALSE);
    }
#endif
    return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}


void CNBMapWnd::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    // Create a new memory DC according current DC.
    CreateMemDC();

    // 
    if (m_pEngineRef!=NULL)
    {
        CRect rectClient;
        GetClientRect(rectClient);
        m_pEngineRef->MapOperation(CNBMapEngine::EMO_DEVICERECT_CHANGED,(WPARAM)&rectClient);
    }

    //
    ReDraw();

}

void CNBMapWnd::SetOperationState(int aState)
{
    m_iOperState = aState;
}

int CNBMapWnd::GetOperationState() const
{
    return m_iOperState;
}


DWORD CNBMapWnd::GetShowStyle() const
{
    return m_wNbShowStyle;
}








