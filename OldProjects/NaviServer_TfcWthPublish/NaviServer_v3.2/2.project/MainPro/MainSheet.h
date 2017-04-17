#pragma once
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "resource.h"
#include "afxcmn.h"
#include "SortListCtrl.h"
#include "afxwin.h"
#include "InterfaceEx.h"
#include "NetLogMgr.h"

//////////////////////////////////////////////////////////////////////////
// CBlanceServerPage 对话框
class CBlanceServerPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CBlanceServerPage)

public:
    CBlanceServerPage();
    virtual ~CBlanceServerPage();

    // 对话框数据
    enum { IDD = IDD_PROPPAGE_BALANCESERVER };

protected:

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()

public:

    afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnBnClickedBtnConnect();

private:

    enum { EHeightGapGT= 2}; // 

    CStatic  m_ctrlGroup;
    CStatic  m_ctrlCntState;
    CIPAddressCtrl m_ctrlBalSvrIP;
    short  m_uBalSvrPort;

};




//////////////////////////////////////////////////////////////////////////
// CMobileClientPage 对话框
class CMobileClientPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CMobileClientPage)

public:
    CMobileClientPage();
    virtual ~CMobileClientPage();

    // 对话框数据
    enum { IDD = IDD_PROPPAGE_MOBILECLIENT };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()

    virtual BOOL OnInitDialog();
    afx_msg void OnSize(UINT nType, int cx, int cy);


private:
    // Group-control's attribute
    enum TGroupCtrlAtrri
    {
        ELA_Height_fixed = 200,
    };

    enum { EHeightGapGT= 2}; // 

    CStatic m_ctrlGroup;

    CImageList m_imageList;

    CSortListCtrl m_ctrlListLogs;
    CEdit m_ctrlUserName;
    CEdit m_ctrlUpTime;
    CEdit m_ctrlDataSent;
    CEdit m_ctrlDataRecved;

    // New private members
private:
    int     m_iProtocolType;
    DWORD   m_activedComFiledID;

    // New public functions
public:
    void AddNewNetLog(PIMsgNetLog pNetLog);
    void SetActivedComField(int aProType,DWORD dwID);

};

//////////////////////////////////////////////////////////////////////////
// CPageWeather 对话框
class CWeatherPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CWeatherPage)

public:
    CWeatherPage();
    virtual ~CWeatherPage();

    // 对话框数据
    enum { IDD = IDD_PROPPAGE_WEATHER };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};


//////////////////////////////////////////////////////////////////////////
// CTrafficPage 对话框

class CTrafficPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CTrafficPage)

public:
    CTrafficPage();
    virtual ~CTrafficPage();

    // 对话框数据
    enum { IDD = IDD_PROPPAGE_TRAFFIC };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};


//////////////////////////////////////////////////////////////////////////
// CMainSheet
class CMainSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMainSheet)

public:
    enum TPageName
    {
        EPN_BALANCESERVER,
        EPN_SERVICEPROVIDER,
        EPN_MOBILECLIENT,
        EPN_WEATHERPAGE,
    };
	CMainSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMainSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CMainSheet();

public:
    CBlanceServerPage  m_blanceserverPage;
    CMobileClientPage  m_mobilesPage;
    //CWeatherPage       m_weatherPage;

protected:
	DECLARE_MESSAGE_MAP()

public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual BOOL OnInitDialog();
    afx_msg void OnSize(UINT nType, int cx, int cy);

    // New private members
private:
    CToolTipCtrl* m_ToolTipCtrl;
    CImageList m_imageList;

    // New public functions
public:
    void ActivePage(TPageName aPageName);
    void AddNetLog(PIMsgNetLog pNewLog);
    void SetActivedFldID(int aProType,DWORD dwID);
};


