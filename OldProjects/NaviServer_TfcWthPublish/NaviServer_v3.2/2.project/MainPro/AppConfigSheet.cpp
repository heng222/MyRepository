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

    // �������ļ��ж�ȡ���ݿ����
    char cTemp[300];
    GetPrivateProfileString(CFG_APPNAME_DATABASE,"DataSource",0,cTemp,300,strProfilepath);
    m_strDataSource = cTemp;
    GetPrivateProfileString(CFG_APPNAME_DATABASE,"UserID",0,cTemp,300,strProfilepath);
    m_strUserID = cTemp;
    GetPrivateProfileString(CFG_APPNAME_DATABASE,"Password",0,cTemp,300,strProfilepath);
    m_strPwd = cTemp;
    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}

void CPropertyDataBase::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: �ڴ˴������Ϣ����������
    // ��Ϊ��ͼ��Ϣ���� CPropertyPage::OnPaint()
}

HBRUSH CPropertyDataBase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  �ڴ˸��� DC ���κ�����
    //Fill the screen to black color
    // Set the text color to red.
    pDC->SetTextColor(CLR_DARKBLUE);

    // Set the background mode for text to transparent
    // so background will show up.
    pDC->SetBkMode(TRANSPARENT);

    // TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
    return hbr;
}
void CPropertyDataBase::OnEnChangeEditDatasource()
{
    // TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
    // ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
    // ���������� CRichEditCtrl().SetEventMask()��
    // ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    SetModified();    // Enable Apply Now button.

}


void CPropertyDataBase::OnEnChangeEditUserid()
{
    // TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
    // ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
    // ���������� CRichEditCtrl().SetEventMask()��
    // ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    SetModified();    // Enable Apply Now button.

}

void CPropertyDataBase::OnEnChangeEditPassword()
{
    // TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
    // ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
    // ���������� CRichEditCtrl().SetEventMask()��
    // ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    SetModified();    // Enable Apply Now button.

}


BOOL CPropertyDataBase::OnQueryCancel()
{

    // TODO: �ڴ����ר�ô����/����û���
    /*if (AfxMessageBox("�Ƿ񱣴�?", MB_YESNO) == IDNO)
    return FALSE;*/


    return CPropertyPage::OnQueryCancel();
}
void CPropertyDataBase::OnOK()
{
    ShowWindow(SW_HIDE);
    SaveProfileParameters();

    // TODO: �ڴ����ר�ô����/����û���
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

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��

    m_bkgBrush.CreateSolidBrush (CLR_BKG_1);	//��Ļ��ɫ

    // �������ļ��ж�ȡ���ݿ����
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

    // ˢ������
    int iFlashInterval;
    CString strInterval;
    iFlashInterval = GetPrivateProfileInt(CFG_APPNAME_SYSTEM,"WTHFLASHTIME",60,strProfilepath);
    strInterval.Format(_T("%d����"),iFlashInterval/60);
    m_ctrlWthFlashTime.SetWindowText(strInterval);

    iFlashInterval = GetPrivateProfileInt(CFG_APPNAME_SYSTEM,"TFCFLASHTIME",60,strProfilepath);
    strInterval.Format(_T("%d����"),iFlashInterval/60);
    m_ctrlTfcFlashTime.SetWindowText(strInterval);



    UpdateData(FALSE);


    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
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
    // TODO: �ڴ����ר�ô����/����û���

    CPropertyPage::OnOK();
}
HBRUSH CPropertyNetwork::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  �ڴ˸��� DC ���κ�����
    if (pWnd->GetDlgCtrlID()==IDC_STATIC)
    {
        pDC->SetTextColor(CLR_DARKGREEN);
    }

    // Set the background mode for text to transparent
    // so background will show up.
    pDC->SetBkMode(TRANSPARENT);

    // TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
    //return m_bkgBrush;
    return hbr;
}
void CPropertyNetwork::OnIpnFieldchangedIpBsserver(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
    
    // TODO: �ڴ���ӿؼ�֪ͨ����������

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
   
    // TODO: �ڴ���ӿؼ�֪ͨ����������
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
    // TODO: �ڴ˴������Ϣ����������
    // ��Ϊ��ͼ��Ϣ���� CPropertyPage::OnPaint()
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
	:CPropertySheet("��������")
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

    // TODO:  �ڴ��������ר�ô���
    CMenu*   pSysMenu   =   GetSystemMenu(FALSE); /*   ����С����ť��ϵͳ�˵�   */  
    if   (pSysMenu   !=   NULL)  
    {  
        pSysMenu->AppendMenu(MF_STRING,   SC_MINIMIZE,   "��С��");  
        ModifyStyle(   0,   WS_MINIMIZEBOX   );  
    }

    //
    //m_bkgBrush.CreateSolidBrush (CLR_LIGHTGRAY);	//��Ļ��ɫ

    return bResult;
}

void CAppConfigSheet::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: �ڴ˴������Ϣ����������
    // ��Ϊ��ͼ��Ϣ���� CPropertySheet::OnPaint()
}


HBRUSH CAppConfigSheet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CPropertySheet::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  �ڴ˸��� DC ���κ�����

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
    // TODO: �ڴ����ר�ô����/����û���

    return CPropertySheet::OnNotify(wParam, lParam, pResult);
}

