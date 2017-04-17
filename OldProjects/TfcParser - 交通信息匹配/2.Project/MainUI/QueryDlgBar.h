#pragma once

#include "stdafx.h"
#include "Resource.h"
// CQueryDlgBar 对话框

class CQueryDlgBar : public CDialogBar
{
	DECLARE_DYNAMIC(CQueryDlgBar)

public:
    CQueryDlgBar();   // 标准构造函数
    virtual ~CQueryDlgBar();

    BOOL CreateSelf(CWnd* pParentWnd,UINT nStyle);

public:

// 对话框数据
	enum { IDD = IDD_DIALOGBAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
    afx_msg LRESULT OnInitDialog ( UINT, LONG );   // <-Add this line.

    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
