#pragma once
#include "afxcmn.h"

#include "SortListCtrl.h"
#include "afxdtctl.h"
#include "afxwin.h"
#include "NetLogMgr.h"
#include "Resource.h"

// CNetLogDlg �Ի���

class CNetLogDlg : public CDialog
{
	DECLARE_DYNAMIC(CNetLogDlg)

public:
	CNetLogDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNetLogDlg();

// �Ի�������
	enum { IDD = IDD_DLG_NETLOGVIEW };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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

    // �������ڿؼ��е����ڴ���־�ļ��ж�ȡ��־
    void LoadLogs(void);


public:
    afx_msg void OnDtnCloseupDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
};
