// DlgAppStart.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NaviServer.h"
#include "DlgAppStart.h"
#include "UserColors.h"


// CDlgAppStart �Ի���

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


// CDlgAppStart ��Ϣ�������

BOOL CDlgAppStart::OnInitDialog()
{
    CDialog::OnInitDialog();

    //
    CBitmap bmpLog;
    bmpLog.LoadBitmap(IDB_BMP_LOG);
    m_bkgBrush.CreatePatternBrush(&bmpLog);
    //m_bkgBrush.CreateSolidBrush(CLR_BKG_1);

    // ����Ĭ������
    m_font.CreateFont(18,0, 0, 0, FW_NORMAL, false, false, 0,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, "����");
    m_ctrInf.SetFont(&m_font);

    return TRUE;
}

HBRUSH CDlgAppStart::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  �ڴ˸��� DC ���κ�����

    // Set the text color to red.
    pDC->SetTextColor(CLR_BLACK);

    // Set the background mode for text to transparent
    // so background will show up.
    pDC->SetBkMode(TRANSPARENT);


    // TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
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
    
    // ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

    //CRect   rect; 
    //GetWindowRect(&rect);//�õ��ͻ������� 

    //CDC   memDC; 
    //CBitmap   bmp; 
    //bmp.LoadBitmap(IDB_BMP_LOG);//�������ͼƬ��Դ 
    //memDC.CreateCompatibleDC(&dc); 
    //memDC.SelectObject(&bmp); 
    ////�ɽ�BitBlt()��������StretchBlt(),����StretchBlt�����ɲ���MSDN���˵�� 
    //dc.SetStretchBltMode(COLORONCOLOR); 
    //dc.StretchBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0, 341,345,SRCCOPY);//400��300�ɸ�����ͼƬ�ľ����С���ı� 
    //memDC.DeleteDC(); 

}
