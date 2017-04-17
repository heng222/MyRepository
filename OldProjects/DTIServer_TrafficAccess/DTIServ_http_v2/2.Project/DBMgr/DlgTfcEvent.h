#pragma once
#include "resource.h"

// CDlgTfcEvent 对话框

class CDlgTfcEvent : public CDialog
{
	DECLARE_DYNAMIC(CDlgTfcEvent)

public:
	CDlgTfcEvent(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTfcEvent();

// 对话框数据
	enum { IDD = IDD_DLG_TFC_EVENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
