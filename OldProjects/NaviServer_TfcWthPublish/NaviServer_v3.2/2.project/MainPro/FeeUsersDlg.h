#pragma once

#include "SortListCtrl.h"
#include "Ado.h"
#include "afxcmn.h"
#include "Resource.h"
#include "afxdtctl.h"
#include "afxwin.h"

// CFeeUsersDlg �Ի���

class CFeeUsersDlg : public CDialog
{
	DECLARE_DYNAMIC(CFeeUsersDlg)

public:
	CFeeUsersDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFeeUsersDlg();

// �Ի�������
	enum { IDD = IDD_DLG_FEEUSERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();

public:
    afx_msg void OnBnClickedCheckRegdate();
    afx_msg void OnBnClickedCheckServicecode();
    afx_msg void OnBnClickedCheckCityname();
    afx_msg void OnBnClickedQuery();
    afx_msg void OnClose();

    // Member functions
private:
    void    InitControls(); // ��ʼ���ؼ�����


    // �ؼ�����
private:
    CSortListCtrl m_ctrlList;

    CDateTimeCtrl m_ctrlComRegDate;
    CButton m_ctrlCheckRegDate;

    CButton m_ctrlCheckSerCode;
    CComboBox m_ctrlComSerCode;

    CButton m_ctrlCheckCity;
    CComboBox m_ctrlComCity;

    CComboBox m_ctrlComCellphone;
    CButton m_ctrlCheckCellPhone;


    // ��������
private:
    CAdoConnection      m_OracleDB; // ���ݿ����Ӷ���

public:
    afx_msg void OnBnClickedCheckCellphone();
};
