#pragma once

#include "stdafx.h"
#include "Resource.h"
// CQueryDlgBar �Ի���

class CQueryDlgBar : public CDialogBar
{
	DECLARE_DYNAMIC(CQueryDlgBar)

public:
    CQueryDlgBar();   // ��׼���캯��
    virtual ~CQueryDlgBar();

    BOOL CreateSelf(CWnd* pParentWnd,UINT nStyle);

public:

// �Ի�������
	enum { IDD = IDD_DIALOGBAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
    afx_msg LRESULT OnInitDialog ( UINT, LONG );   // <-Add this line.

    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
