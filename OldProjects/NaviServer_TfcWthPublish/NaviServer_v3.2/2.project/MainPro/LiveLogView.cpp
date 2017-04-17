// NaviServerView.cpp : implementation of the CNaviServerView class
//

#include "stdafx.h"
#include "NaviServerDoc.h"
#include "LiveLogView.h"
#include "UserColors.h"
#include "MainFrm.h"
#include ".\livelogview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNaviServerView

IMPLEMENT_DYNCREATE(CLiveLogView, CFormView)

BEGIN_MESSAGE_MAP(CLiveLogView, CFormView)
	//{{AFX_MSG_MAP(CNaviServerView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_LOG_DELETESEL, OnLogMenuDelSel)
	ON_COMMAND(ID_LOG_CLEAR, OnLogClear)
	ON_WM_SIZE()
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNaviServerView construction/destruction

CLiveLogView::CLiveLogView()
	: CFormView(CLiveLogView::IDD)
{
	//{{AFX_DATA_INIT(CNaviServerView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here
}

CLiveLogView::~CLiveLogView()
{
}

void CLiveLogView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNaviServerView)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
}

BOOL CLiveLogView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CLiveLogView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	//ResizeParentToFit();

	//设置列的标题
	m_ctrlList.SetExtendedStyle(LVS_EX_GRIDLINES | 
					LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);
	m_ctrlList.SetHeadings( _T("时 间,150;类 型,100;               备                     注,750") );
	m_ctrlList.LoadColumnInfo();

	CRect rect;
	GetClientRect(rect);
	m_ctrlList.MoveWindow(&rect);

	//
	m_LogMenu.LoadMenu(IDR_MENU_LOG);

}

/////////////////////////////////////////////////////////////////////////////
// CNaviServerView printing

BOOL CLiveLogView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLiveLogView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLiveLogView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLiveLogView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CNaviServerView diagnostics

#ifdef _DEBUG
void CLiveLogView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLiveLogView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CNaviServerDoc* CLiveLogView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNaviServerDoc)));
	return (CNaviServerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNaviServerView message handlers

void CLiveLogView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
	if (pWnd->GetSafeHwnd() == m_ctrlList.GetSafeHwnd())
	{
		CMenu* pMenu = m_LogMenu.GetSubMenu(0);
		ASSERT(pMenu != NULL);
		pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
	}
}

// 弹出菜单－删除选中的行
void CLiveLogView::OnLogMenuDelSel()
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
// 弹出菜单－删除所有日志
void CLiveLogView::OnLogClear()
{
	m_ctrlList.DeleteAllItems();
}


void CLiveLogView::OnSize(UINT nType, int cx, int cy)
{
    CFormView::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码
    if (IsWindow(HWND(m_ctrlList)))
    {
        m_ctrlList.MoveWindow(CRect(0,0,cx,cy));
    }
}


BOOL CLiveLogView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll)
{
    // TODO: 在此添加专用代码和/或调用基类

    return CFormView::OnScroll(nScrollCode, nPos, bDoScroll);
}


void CLiveLogView::AddLiveLog(PIMsgAppLogs pNewLog)
{
    // 不处理等级为ELL_INFORMATION的网络事件
    if (pNewLog->iLogType==IMsgNetLog::ELGT_Network && pNewLog->iLogLevel<=IMsgAppLogs::ELL_INFORMATION)
    {
        return;
    }

    // Add a new line.
    CString strLogType;
    pNewLog->GetLogType_str(strLogType);
    m_ctrlList.InsertItemA(0,pNewLog->logTime.Format(" %Y-%m-%d %H:%M:%S"),
        " "+strLogType, " "+pNewLog->strComments);
    //m_ctrlList.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
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

HBRUSH CLiveLogView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);


    // TODO:  如果默认的不是所需画笔，则返回另一个画笔
    return hbr;
}
