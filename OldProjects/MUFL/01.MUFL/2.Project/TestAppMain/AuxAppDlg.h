// AuxAppDlg.h : 头文件
//

#pragma once
#include "ado.h"

#include "CommonFunc.h"
#include "XMLFile.h"
#include "afxwin.h"
#include "GenericHTTPClient.h"
#include "SortListCtrl.h"
#include "afxcmn.h"

// CAuxAppDlg 对话框
class CAuxAppDlg : public CDialog
{
// 构造
public:

	CAuxAppDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AUXAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:

	HICON m_hIcon;

	// 生成的消息映射函数
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg void OnClose();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnDBTest();
    afx_msg void OnBnClickedGeneric();
    afx_msg void OnBnClickedXML();
    afx_msg void OnBnClickedHttp();
    afx_msg LRESULT OnMyHookProcedure(WPARAM,LPARAM);
    afx_msg void OnEnChangeEdit1();

private:

    CEdit   m_ctrlResult;

private:

    VOID    OnContructor();
    BOOL    OnInitialize();

};
