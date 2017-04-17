// DlgAppStart.cpp : 实现文件
//

#include "stdafx.h"
#include "NaviServer.h"
#include "DlgAppStart.h"
#include "UserColors.h"


// CDlgAppStart 对话框

IMPLEMENT_DYNAMIC(CDlgAppStart, CDialog)
CDlgAppStart::CDlgAppStart(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAppStart::IDD, pParent)
{
}

CDlgAppStart::~CDlgAppStart()
{
}

void CDlgAppStart::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STA_INF, m_ctrInf);
}


BEGIN_MESSAGE_MAP(CDlgAppStart, CDialog)
    ON_WM_CTLCOLOR()
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgAppStart 消息处理程序

BOOL CDlgAppStart::OnInitDialog()
{
    CDialog::OnInitDialog();

    //
    CBitmap bmpLog;
    bmpLog.LoadBitmap(IDB_BMP_LOG);
    m_bkgBrush.CreatePatternBrush(&bmpLog);
    //m_bkgBrush.CreateSolidBrush(CLR_BKG_1);

    // 设置默认字体
    m_font.CreateFont(18,0, 0, 0, FW_NORMAL, false, false, 0,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, "黑体");
    m_ctrInf.SetFont(&m_font);

    return TRUE;
}

HBRUSH CDlgAppStart::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  在此更改 DC 的任何属性

    // Set the text color to red.
    pDC->SetTextColor(CLR_BLACK);

    // Set the background mode for text to transparent
    // so background will show up.
    pDC->SetBkMode(TRANSPARENT);


    // TODO:  如果默认的不是所需画笔，则返回另一个画笔
    return m_bkgBrush;
    //return hbr;
}
void CDlgAppStart::SetInf(const CString& strInf)
{
    m_ctrInf.SetWindowText(strInf);
}

void CDlgAppStart::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    
    // 不为绘图消息调用 CDialog::OnPaint()

    //CRect   rect; 
    //GetWindowRect(&rect);//得到客户区区域 

    //CDC   memDC; 
    //CBitmap   bmp; 
    //bmp.LoadBitmap(IDB_BMP_LOG);//加载你的图片资源 
    //memDC.CreateCompatibleDC(&dc); 
    //memDC.SelectObject(&bmp); 
    ////可将BitBlt()函数换成StretchBlt(),关于StretchBlt函数可查阅MSDN相关说明 
    //dc.SetStretchBltMode(COLORONCOLOR); 
    //dc.StretchBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0, 341,345,SRCCOPY);//400×300可根据你图片的具体大小来改变 
    //memDC.DeleteDC(); 

}
