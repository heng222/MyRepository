#pragma once
#include "afxwin.h"
#include "Resource.h"


// CDlgAppStart 对话框

class CDlgAppStart : public CDialog
{
	DECLARE_DYNAMIC(CDlgAppStart)

public:
	CDlgAppStart(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAppStart();

// 对话框数据
	enum { IDD = IDD_DLG_APPSTART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    virtual BOOL OnInitDialog();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()

    CStatic m_ctrInf;
    CFont m_font;

    CBrush  m_bkgBrush;

public:
	void SetInf(const CString& strInf);

};
