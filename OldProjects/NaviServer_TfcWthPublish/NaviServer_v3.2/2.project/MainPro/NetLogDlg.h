#pragma once
#include "afxcmn.h"

#include "SortListCtrl.h"
#include "afxdtctl.h"
#include "afxwin.h"
#include "NetLogMgr.h"
#include "Resource.h"

// CNetLogDlg 对话框

class CNetLogDlg : public CDialog
{
	DECLARE_DYNAMIC(CNetLogDlg)

public:
	CNetLogDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNetLogDlg();

// 对话框数据
	enum { IDD = IDD_DLG_NETLOGVIEW };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


protected:
    afx_msg void OnCbnSelchangeCmbAddress();
    afx_msg void OnBnClickedBtnQuery();

    afx_msg void OnBnClickedCheck2();
    afx_msg void OnBnClickedCheck3();


private:

    COleDateTime m_DTSelection;

    //
    CDateTimeCtrl m_ctrlDateTime;
    CComboBox m_ctrlCmbEvent;

    CComboBox m_ctrlCmbIPAddr;

    CButton m_ctrlDateCheck;

    CButton m_ctrlEventCheck;
    CButton m_ctrlIPAddrCheck;

    CSortListCtrl   m_ctrlNLList;

public:
    virtual BOOL OnInitDialog();
    afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMThemeChangedDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);


private:

    CNetLogMgr      m_NetLogMgr;

    // 根据日期控件中的日期从日志文件中读取日志
    void LoadLogs(void);


public:
    afx_msg void OnDtnCloseupDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
};
