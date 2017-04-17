// MainUIView.cpp : CMainUIView 类的实现
//

#include "stdafx.h"
#include "MainUI.h"
#include <UserColors.h>
#include "MainUIDoc.h"
#include ".\mainuiview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainUIView

IMPLEMENT_DYNCREATE(CMainUIView, CView)

BEGIN_MESSAGE_MAP(CMainUIView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_CONTEXTMENU()
    ON_COMMAND(ID_LOG_DELETESEL, OnLogDeletesel)
    ON_COMMAND(ID_LOG_CLEAR, OnLogClear)
END_MESSAGE_MAP()

// CMainUIView 构造/析构

CMainUIView::CMainUIView():m_ctrlList(CSortListCtrl::ECS_INVOKECREATE)
{
	// TODO: 在此处添加构造代码

}

CMainUIView::~CMainUIView()
{
}

BOOL CMainUIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return CView::PreCreateWindow(cs);
}

// CMainUIView 绘制

void CMainUIView::OnDraw(CDC* /*pDC*/)
{
	CMainUIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMainUIView 打印

BOOL CMainUIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMainUIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印前添加额外的初始化
}

void CMainUIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印后添加清除过程
}


// CMainUIView 诊断

#ifdef _DEBUG
void CMainUIView::AssertValid() const
{
	CView::AssertValid();
}

void CMainUIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMainUIDoc* CMainUIView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainUIDoc)));
	return (CMainUIDoc*)m_pDocument;
}
#endif //_DEBUG


// CMainUIView 消息处理程序

void CMainUIView::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    // TODO: 在此添加专用代码和/或调用基类
}

int CMainUIView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  在此添加您专用的创建代码
    BOOL bFlag = m_ctrlList.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_REPORT,
        CRect(0,0,200,200), this, 1);

    if ( !bFlag )
    {
        return -1;
    }

    //设置列的标题
    m_ctrlList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);
    m_ctrlList.SetHeadings( _T("时 间,150;类 型,100;               备                     注,750") );


    //
    //m_LogMenu.LoadMenu(IDR_MENU_LOG);

    return 0;
}

void CMainUIView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码

    if (IsWindow(HWND(m_ctrlList)))
    {
        m_ctrlList.MoveWindow(CRect(0,0,cx,cy));
    }
}


void CMainUIView::AddLiveLog(PIMsgAppLogs pNewLog)
{
    // 不处理等级为ELL_INFORMATION的网络事件
    if (pNewLog->iLogType!=IMsgAppLogs::ELGT_System && pNewLog->iLogLevel<=IMsgAppLogs::ELL_INFORMATION)
    {
        return;
    }

    // Insert a new line.
    CString strLogType;
    pNewLog->GetLogType_str(strLogType);
    m_ctrlList.InsertItemA(0,pNewLog->logTime.Format(" %Y-%m-%d %H:%M:%S"),
        " "+strLogType, " "+pNewLog->strComments);
    int iClrItem = 0;

    // set color
    COLORREF crText = ::GetSysColor(COLOR_WINDOWTEXT);
    COLORREF crBkgnd = ::GetSysColor(COLOR_WINDOW);

    if (pNewLog->iLogLevel==IMsgAppLogs::ELL_ERROR)
    {
        crText = CLR_BLACK;
        crBkgnd = CLR_RED;
        int iColum = m_ctrlList.GetColumns();
        for (int i=0; i<iColum; i++)
        {
            m_ctrlList.SetItemColor(iClrItem,i,crText,crBkgnd);
        }
    }
    else if (pNewLog->iLogLevel==IMsgAppLogs::ELL_WARNING)
    {
        crText = CLR_BLACK;
        crBkgnd = CLR_YELLOW;
        int iColum = m_ctrlList.GetColumns();
        for (int i=0; i<iColum; i++)
        {
            m_ctrlList.SetItemColor(iClrItem,i,crText,crBkgnd);
        }
    }
    else
    {
        // Set text colors
        switch(pNewLog->iLogType)
        {
        case IMsgAppLogs::ELGT_System:
            {
                crText = CLR_DARKBLUE;
                crBkgnd = CLR_BKG_1;
            }
            break;

        default:
            {
                crText = CLR_DARKGREEN;
                crBkgnd = CLR_BKG_2;
            }

        }
        m_ctrlList.SetItemColor(iClrItem,1,crText,crBkgnd);
    }

    //
    if (m_ctrlList.GetItemCount()>100)
    {
        m_ctrlList.DeleteAllItems();
    }
}

void CMainUIView::OnContextMenu(CWnd* pWnd, CPoint point)
{
    if (pWnd->GetSafeHwnd() == m_ctrlList.GetSafeHwnd())
    {
        CMenu menu;
        menu.LoadMenu(IDR_MENU_LOG);
        CMenu* pMenu = menu.GetSubMenu(0);
        ASSERT(pMenu != NULL);
        pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
    }
}

void CMainUIView::OnLogDeletesel()
{
    int iCount = m_ctrlList.GetSelectedCount();
    POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
    int nItem = m_ctrlList.GetNextSelectedItem(pos)+iCount-1;
    for (int i=0; i<iCount; i++)
    {
        m_ctrlList.DeleteItem(nItem);
        nItem --;
    }
}

void CMainUIView::OnLogClear()
{
    m_ctrlList.DeleteAllItems();
}
