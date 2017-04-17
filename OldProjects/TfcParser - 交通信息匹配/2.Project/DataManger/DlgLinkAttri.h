#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "InterfaceEx.h"
#include <SortListCtrl.h>

// CDlgLinkAttri �Ի���

class CDlgLinkAttri : public CDialog
{
	DECLARE_DYNAMIC(CDlgLinkAttri)

public:
	CDlgLinkAttri(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLinkAttri();

// �Ի�������
    enum { IDD = IDD_DLG_LINKATTRI };


    void    AttachLink(CLinkList* pLinkList);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

    void  AddLinkToList();

private:

    CSortListCtrl m_ctrlList;

    CLinkList*   m_pLinkList;


public:
    virtual BOOL OnInitDialog();
};
