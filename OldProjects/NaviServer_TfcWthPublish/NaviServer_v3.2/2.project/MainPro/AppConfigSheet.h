#pragma once

#include "Resource.h"
#include "afxcmn.h"
#include "afxwin.h"

//////////////////////// CPropertyPage1 //////////////////////////////////////////////////
class CPropertyDataBase : public CPropertyPage
{
    DECLARE_DYNCREATE(CPropertyDataBase)

    // Construction
public:
    CPropertyDataBase();
    ~CPropertyDataBase();


    enum { IDD = IDD_PAGE_DB };
    CString	m_strDataSource;
    CString	m_strUserID;
    CString	m_strPwd;


protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Implementation
protected:
    DECLARE_MESSAGE_MAP()
    void SaveProfileParameters();

public:
    virtual BOOL OnInitDialog();
    virtual BOOL OnQueryCancel();
    virtual void OnOK();
    afx_msg void OnEnChangeEditDatasource();
    afx_msg void OnEnChangeEditUserid();
    afx_msg void OnEnChangeEditPassword();
    afx_msg void OnPaint();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
//////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CPropertyPage2
class CPropertyNetwork : public CPropertyPage
{
    DECLARE_DYNCREATE(CPropertyNetwork)

    // Construction
public:
    CPropertyNetwork();
    ~CPropertyNetwork();
    enum { IDD = IDD_PAGE_NETWORK };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


    // Implementation
protected:
    DECLARE_MESSAGE_MAP()

    void SaveProfileParameters();

private:
    CBrush m_bkgBrush;

    // 负载均衡IP
    CIPAddressCtrl m_ctrlBalSvrIP;
    UINT m_uBalSvrPort;

    // 信息发布的服务的IP
    CIPAddressCtrl m_ctrlPubIP;
    UINT m_uPubSvrPort;

    // 交通与气象刷新周期
    CComboBox m_ctrlWthFlashTime;
    CComboBox m_ctrlTfcFlashTime;

public:
    virtual BOOL OnInitDialog();
    afx_msg void OnIpnFieldchangedIpBsserver(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnEnChangeEditBsport();
    afx_msg void OnIpnFieldchangedPublishIp(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnEnChangePublishPort();
    afx_msg void OnPaint();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    virtual void OnOK();


public:
    afx_msg void OnBnClickedRbtnAllip();
    afx_msg void OnBnClickedRbtnSpecifyip();
private:
    int m_iListenType;
};
/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
// CPropertysheetObj

class CAppConfigSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CAppConfigSheet)

// Construction
public:
	CAppConfigSheet();
	CAppConfigSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CAppConfigSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

	CPropertyDataBase GetPage1();
	CPropertyNetwork GetPage2();

// Attributes
public:

// Operations
public:
    //CBrush m_bkgBrush;
	CPropertyDataBase m_pageDB;
	CPropertyNetwork m_pageNetwork;

// Implementation
public:
	virtual ~CAppConfigSheet();

	// Generated message map functions
protected:
	
	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
    virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};

/////////////////////////////////////////////////////////////////////////////
