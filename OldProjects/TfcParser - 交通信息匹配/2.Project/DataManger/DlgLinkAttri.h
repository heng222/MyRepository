#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "InterfaceEx.h"
#include <SortListCtrl.h>

// CDlgLinkAttri 对话框

class CDlgLinkAttri : public CDialog
{
	DECLARE_DYNAMIC(CDlgLinkAttri)

public:
	CDlgLinkAttri(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLinkAttri();

// 对话框数据
    enum { IDD = IDD_DLG_LINKATTRI };


    void    AttachLink(CLinkList* pLinkList);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

    void  AddLinkToList();

private:

    CSortListCtrl m_ctrlList;

    CLinkList*   m_pLinkList;


public:
    virtual BOOL OnInitDialog();
};
