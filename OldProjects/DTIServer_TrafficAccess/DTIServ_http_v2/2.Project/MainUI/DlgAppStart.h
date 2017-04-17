#pragma once
#include "afxwin.h"
#include "Resource.h"


// CDlgAppStart �Ի���

class CDlgAppStart : public CDialog
{
	DECLARE_DYNAMIC(CDlgAppStart)

public:
	CDlgAppStart(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAppStart();

// �Ի�������
	enum { IDD = IDD_DLG_APPSTART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
