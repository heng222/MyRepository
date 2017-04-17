#pragma once

#include "SortListCtrl.h"
#include "Ado.h"
#include "afxcmn.h"
#include "Resource.h"
#include "afxdtctl.h"
#include "afxwin.h"

// CFeeUsersDlg 对话框

class CFeeUsersDlg : public CDialog
{
	DECLARE_DYNAMIC(CFeeUsersDlg)

public:
	CFeeUsersDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFeeUsersDlg();

// 对话框数据
	enum { IDD = IDD_DLG_FEEUSERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();

public:
    afx_msg void OnBnClickedCheckRegdate();
    afx_msg void OnBnClickedCheckServicecode();
    afx_msg void OnBnClickedCheckCityname();
    afx_msg void OnBnClickedQuery();
    afx_msg void OnClose();

    // Member functions
private:
    void    InitControls(); // 初始化控件变量


    // 控件变量
private:
    CSortListCtrl m_ctrlList;

    CDateTimeCtrl m_ctrlComRegDate;
    CButton m_ctrlCheckRegDate;

    CButton m_ctrlCheckSerCode;
    CComboBox m_ctrlComSerCode;

    CButton m_ctrlCheckCity;
    CComboBox m_ctrlComCity;

    CComboBox m_ctrlComCellphone;
    CButton m_ctrlCheckCellPhone;


    // 其它变量
private:
    CAdoConnection      m_OracleDB; // 数据库连接对象

public:
    afx_msg void OnBnClickedCheckCellphone();
};
