#pragma once

#include "SortListCtrl.h"
#include "Ado.h"
#include "afxcmn.h"

#include "Resource.h"
// CDlgUsersRegedMgr �Ի���

class CDlgUsersRegedMgr : public CDialog
{
	DECLARE_DYNAMIC(CDlgUsersRegedMgr)

public:
	CDlgUsersRegedMgr(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgUsersRegedMgr();

// �Ի�������
	enum { IDD = IDD_DLG_USERSREGED_MGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
    virtual BOOL OnInitDialog();

    void    InitSubControls();
    
     // �ؼ�����
private:
    CSortListCtrl   m_ctrlList;

    // ��������
private:
    CAdoConnection      m_OracleDB; // ���ݿ����Ӷ���
};
