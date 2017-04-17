// PropertysheetObj.cpp : implementation file
//

#include "stdafx.h"
#include "AppConfigSheet.h"
#include "GlobalMacro.h"
#include "InterfaceEx.h"
#include "TSockAddr.h"
#include "UserColors.h"
#include ".\appconfigsheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
//                CPropertyDataBase

IMPLEMENT_DYNCREATE(CPropertyDataBase, CPropertyPage)

CPropertyDataBase::CPropertyDataBase() : CPropertyPage(CPropertyDataBase::IDD)
{
    m_strDataSource = _T("");
    m_strUserID = _T("");
    m_strPwd = _T("");
}

CPropertyDataBase::~CPropertyDataBase()
{
}

void CPropertyDataBase::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_DataSource, m_strDataSource);
    DDX_Text(pDX, IDC_EDIT_Password, m_strUserID);
    DDX_Text(pDX, IDC_EDIT_UserID, m_strPwd);
}


BEGIN_MESSAGE_MAP(CPropertyDataBase, CPropertyPage)

    ON_EN_CHANGE(IDC_EDIT_DataSource, OnEnChangeEditDatasource)
    ON_EN_CHANGE(IDC_EDIT_UserID, OnEnChangeEditUserid)
    ON_EN_CHANGE(IDC_EDIT_Password, OnEnChangeEditPassword)
    ON_WM_PAINT()
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


BOOL CPropertyDataBase::OnInitDialog()
{
    CPropertyPage::OnInitDialog();


    CString strProfilepath = GetExePath()+CString(PATH_CONFIGURE_FILE);

    // 从配置文件中读取数据库参数
    char cTemp[300];
    GetPrivateProfileString(CFG_APPNAME_DATABASE,"DataSource",0,cTemp,300,strProfilepath);
    m_strDataSource = cTemp;
    GetPrivateProfileString(CFG_APPNAME_DATABASE,"UserID",0,cTemp,300,strProfilepath);
    m_strUserID = cTemp;
    GetPrivateProfileString(CFG_APPNAME_DATABASE,"Password",0,cTemp,300,strProfilepath);
    m_strPwd = cTemp;
    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CPropertyDataBase::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: 在此处添加消息处理程序代码
    // 不为绘图消息调用 CPropertyPage::OnPaint()
}

HBRUSH CPropertyDataBase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  在此更改 DC 的任何属性
    //Fill the screen to black color
    // Set the text color to red.
    pDC->SetTextColor(CLR_DARKBLUE);

    // Set the background mode for text to transparent
    // so background will show up.
    pDC->SetBkMode(TRANSPARENT);

    // TODO:  如果默认的不是所需画笔，则返回另一个画笔
    return hbr;
}
void CPropertyDataBase::OnEnChangeEditDatasource()
{
    // TODO:  如果该控件是 RICHEDIT 控件，则它将不会
    // 发送该通知，除非重写 CPropertyPage::OnInitDialog()
    // 函数并调用 CRichEditCtrl().SetEventMask()，
    // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

    // TODO:  在此添加控件通知处理程序代码
    SetModified();    // Enable Apply Now button.

}


void CPropertyDataBase::OnEnChangeEditUserid()
{
    // TODO:  如果该控件是 RICHEDIT 控件，则它将不会
    // 发送该通知，除非重写 CPropertyPage::OnInitDialog()
    // 函数并调用 CRichEditCtrl().SetEventMask()，
    // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

    // TODO:  在此添加控件通知处理程序代码
    SetModified();    // Enable Apply Now button.

}

void CPropertyDataBase::OnEnChangeEditPassword()
{
    // TODO:  如果该控件是 RICHEDIT 控件，则它将不会
    // 发送该通知，除非重写 CPropertyPage::OnInitDialog()
    // 函数并调用 CRichEditCtrl().SetEventMask()，
    // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

    // TODO:  在此添加控件通知处理程序代码
    SetModified();    // Enable Apply Now button.

}


BOOL CPropertyDataBase::OnQueryCancel()
{

    // TODO: 在此添加专用代码和/或调用基类
    /*if (AfxMessageBox("是否保存?", MB_YESNO) == IDNO)
    return FALSE;*/


    return CPropertyPage::OnQueryCancel();
}
void CPropertyDataBase::OnOK()
{
    ShowWindow(SW_HIDE);
    SaveProfileParameters();

    // TODO: 在此添加专用代码和/或调用基类
    CPropertyPage::OnOK();
}

void CPropertyDataBase::SaveProfileParameters()
{

    CString strProfilepath = GetExePath()+CString(PATH_CONFIGURE_FILE);


    WritePrivateProfileString(CFG_APPNAME_DATABASE,"DataSource",m_strDataSource.GetBuffer(0),strProfilepath);
    WritePrivateProfileString(CFG_APPNAME_DATABASE,"UserID",m_strUserID,strProfilepath);
    WritePrivateProfileString(CFG_APPNAME_DATABASE,"Password",m_strPwd,strProfilepath);

}







/////////////////////////////////////////////////////////////////////////////
//                      CPropertyNetwork 

IMPLEMENT_DYNCREATE(CPropertyNetwork, CPropertyPage)

CPropertyNetwork::CPropertyNetwork() : CPropertyPage(CPropertyNetwork::IDD)
, m_uBalSvrPort(0)
, m_uPubSvrPort(0)
, m_iListenType(0)
{
}

CPropertyNetwork::~CPropertyNetwork()
{
}

void CPropertyNetwork::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_IP_BSSERVER, m_ctrlBalSvrIP);
    DDX_Text(pDX, IDC_EDIT_BSPORT, m_uBalSvrPort);
    DDX_Control(pDX, IDC_PUBLISH_IP, m_ctrlPubIP);
    DDX_Text(pDX, IDC_PUBLISH_PORT, m_uPubSvrPort);
    DDX_Control(pDX, IDC_COMB_WTHFLASHTIME, m_ctrlWthFlashTime);
    DDX_Control(pDX, IDC_COMB_TFCFLASHTIME, m_ctrlTfcFlashTime);
    DDX_Radio(pDX, IDC_RBTN_ALLIP, m_iListenType);
}


BEGIN_MESSAGE_MAP(CPropertyNetwork, CPropertyPage)

    ON_NOTIFY(IPN_FIELDCHANGED, IDC_IP_BSSERVER, OnIpnFieldchangedIpBsserver)
    ON_EN_CHANGE(IDC_EDIT_BSPORT, OnEnChangeEditBsport)
    ON_NOTIFY(IPN_FIELDCHANGED, IDC_PUBLISH_IP, OnIpnFieldchangedPublishIp)
    ON_EN_CHANGE(IDC_PUBLISH_PORT, OnEnChangePublishPort)
    ON_WM_PAINT()
    ON_WM_CTLCOLOR()
    ON_BN_CLICKED(IDC_RBTN_ALLIP, OnBnClickedRbtnAllip)
    ON_BN_CLICKED(IDC_RBTN_SPECIFYIP, OnBnClickedRbtnSpecifyip)
END_MESSAGE_MAP()

BOOL CPropertyNetwork::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    // TODO:  在此添加额外的初始化

    m_bkgBrush.CreateSolidBrush (CLR_BKG_1);	//屏幕底色

    // 从配置文件中读取数据库参数
    CString strProfilepath = GetExePath()+CString(PATH_CONFIGURE_FILE);
    char cTemp[300];

    // Attribute of balance server.
    GetPrivateProfileString(CFG_APPNAME_NETWORK,"BALANCE_SERVER_IP",0,cTemp,300,strProfilepath);
    if (CString(cTemp)==CString(_T("0")))
    {
        m_iListenType = 0;
        m_ctrlPubIP.EnableWindow(FALSE);
    }
    else
    {
        m_iListenType = 1;
        m_ctrlPubIP.EnableWindow(TRUE);
    }
    UpdateData(FALSE);
    m_ctrlBalSvrIP.SetAddress(TSockAddr(cTemp).IPAddr()); 
    m_uBalSvrPort = GetPrivateProfileInt(CFG_APPNAME_NETWORK,"BALANCE_SERVER_PORT",0,strProfilepath);
    
    // Attribute of Inf-pub server.
    GetPrivateProfileString(CFG_APPNAME_NETWORK,"MOBILE_IP_CHAR",0,cTemp,300,strProfilepath);
    m_ctrlPubIP.SetAddress(TSockAddr(cTemp).IPAddr()); 
    m_uPubSvrPort = GetPrivateProfileInt(CFG_APPNAME_NETWORK,"MOBILE_PORT_CHAR",0,strProfilepath);

    // 刷新周期
    int iFlashInterval;
    CString strInterval;
    iFlashInterval = GetPrivateProfileInt(CFG_APPNAME_SYSTEM,"WTHFLASHTIME",60,strProfilepath);
    strInterval.Format(_T("%d分钟"),iFlashInterval/60);
    m_ctrlWthFlashTime.SetWindowText(strInterval);

    iFlashInterval = GetPrivateProfileInt(CFG_APPNAME_SYSTEM,"TFCFLASHTIME",60,strProfilepath);
    strInterval.Format(_T("%d分钟"),iFlashInterval/60);
    m_ctrlTfcFlashTime.SetWindowText(strInterval);



    UpdateData(FALSE);


    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}
void CPropertyNetwork::SaveProfileParameters()
{
    DWORD dwIP;
    char* lpcIP;
    CString strPort;

    CString strProfilepath = GetExePath()+CString(PATH_CONFIGURE_FILE);

    m_ctrlBalSvrIP.GetAddress(dwIP);
    lpcIP = TSockAddr(dwIP).DottedDecimal();
    WritePrivateProfileString(CFG_APPNAME_NETWORK,"BALANCE_SERVER_IP",lpcIP,strProfilepath);
    strPort.Format("%d",m_uBalSvrPort);
    WritePrivateProfileString(CFG_APPNAME_NETWORK,"BALANCE_SERVER_PORT",strPort.GetBuffer(0),strProfilepath);

    if (m_iListenType==0)
    {
        lpcIP = "0";
    }
    else
    {
        m_ctrlPubIP.GetAddress(dwIP);
        lpcIP = TSockAddr(dwIP).DottedDecimal();      
    }

    WritePrivateProfileString(CFG_APPNAME_NETWORK,"MOBILE_IP_CHAR",lpcIP,strProfilepath);
    WritePrivateProfileString(CFG_APPNAME_NETWORK,"MOBILE_IP_BIN",lpcIP,strProfilepath);   

    strPort.Format("%d",m_uPubSvrPort);
    WritePrivateProfileString(CFG_APPNAME_NETWORK,"MOBILE_PORT_CHAR",strPort.GetBuffer(0),strProfilepath);

}

void CPropertyNetwork::OnOK()
{
    ShowWindow(SW_HIDE);
    SaveProfileParameters();
    // TODO: 在此添加专用代码和/或调用基类

    CPropertyPage::OnOK();
}
HBRUSH CPropertyNetwork::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  在此更改 DC 的任何属性
    if (pWnd->GetDlgCtrlID()==IDC_STATIC)
    {
        pDC->SetTextColor(CLR_DARKGREEN);
    }

    // Set the background mode for text to transparent
    // so background will show up.
    pDC->SetBkMode(TRANSPARENT);

    // TODO:  如果默认的不是所需画笔，则返回另一个画笔
    //return m_bkgBrush;
    return hbr;
}
void CPropertyNetwork::OnIpnFieldchangedIpBsserver(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
    
    // TODO: 在此添加控件通知处理程序代码

    SetModified();    // Enable Apply Now button.


    *pResult = 0;
}

void CPropertyNetwork::OnEnChangeEditBsport()
{
    SetModified();    // Enable Apply Now button.
}

void CPropertyNetwork::OnIpnFieldchangedPublishIp(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
   
    // TODO: 在此添加控件通知处理程序代码
    SetModified();    // Enable Apply Now button.



    *pResult = 0;
}

void CPropertyNetwork::OnEnChangePublishPort()
{
    SetModified();    // Enable Apply Now button.
}


void CPropertyNetwork::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: 在此处添加消息处理程序代码
    // 不为绘图消息调用 CPropertyPage::OnPaint()
}


void CPropertyNetwork::OnBnClickedRbtnAllip()
{
    m_ctrlPubIP.EnableWindow(FALSE);
}

void CPropertyNetwork::OnBnClickedRbtnSpecifyip()
{
    m_ctrlPubIP.EnableWindow(TRUE);
}



/////////////////////////////////////////////////////////////////////////////
//                           CPropertysheet

IMPLEMENT_DYNAMIC(CAppConfigSheet, CPropertySheet)

CAppConfigSheet::CAppConfigSheet()
	:CPropertySheet("程序配置")
{	
	AddPage(&m_pageDB);
	AddPage(&m_pageNetwork);
}

CAppConfigSheet::CAppConfigSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{	
}

CAppConfigSheet::CAppConfigSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CAppConfigSheet::~CAppConfigSheet()
{
}


BEGIN_MESSAGE_MAP(CAppConfigSheet, CPropertySheet)
	
    ON_WM_PAINT()
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


BOOL CAppConfigSheet::OnInitDialog()
{
    BOOL bResult = CPropertySheet::OnInitDialog();

    // TODO:  在此添加您的专用代码
    CMenu*   pSysMenu   =   GetSystemMenu(FALSE); /*   加最小化按钮到系统菜单   */  
    if   (pSysMenu   !=   NULL)  
    {  
        pSysMenu->AppendMenu(MF_STRING,   SC_MINIMIZE,   "最小化");  
        ModifyStyle(   0,   WS_MINIMIZEBOX   );  
    }

    //
    //m_bkgBrush.CreateSolidBrush (CLR_LIGHTGRAY);	//屏幕底色

    return bResult;
}

void CAppConfigSheet::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: 在此处添加消息处理程序代码
    // 不为绘图消息调用 CPropertySheet::OnPaint()
}


HBRUSH CAppConfigSheet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CPropertySheet::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  在此更改 DC 的任何属性

    ////Fill the screen to black color
    //// Set the text color to red.
    //pDC->SetTextColor(CLR_RED);

    //// Set the background mode for text to transparent
    //// so background will show up.
    //pDC->SetBkMode(TRANSPARENT);

    //return m_bkgBrush;
    return hbr;
}


BOOL CAppConfigSheet::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    // TODO: 在此添加专用代码和/或调用基类

    return CPropertySheet::OnNotify(wParam, lParam, pResult);
}

