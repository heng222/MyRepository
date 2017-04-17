#pragma once

#include "SortListCtrl.h"
#include "Ado.h"
#include "afxcmn.h"

#include "Resource.h"
// CDlgUsersRegedMgr 对话框

class CDlgUsersRegedMgr : public CDialog
{
	DECLARE_DYNAMIC(CDlgUsersRegedMgr)

public:
	CDlgUsersRegedMgr(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgUsersRegedMgr();

// 对话框数据
	enum { IDD = IDD_DLG_USERSREGED_MGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
    virtual BOOL OnInitDialog();

    void    InitSubControls();
    
     // 控件变量
private:
    CSortListCtrl   m_ctrlList;

    // 其它变量
private:
    CAdoConnection      m_OracleDB; // 数据库连接对象
};
