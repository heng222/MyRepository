// AuxAppDlg.h : ͷ�ļ�
//

#pragma once
#include "ado.h"

#include "CommonFunc.h"
#include "XMLFile.h"
#include "afxwin.h"
#include "GenericHTTPClient.h"
#include "SortListCtrl.h"
#include "afxcmn.h"

// CAuxAppDlg �Ի���
class CAuxAppDlg : public CDialog
{
// ����
public:

	CAuxAppDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AUXAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:

	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg void OnClose();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnDBTest();
    afx_msg void OnBnClickedGeneric();
    afx_msg void OnBnClickedXML();
    afx_msg void OnBnClickedHttp();
    afx_msg LRESULT OnMyHookProcedure(WPARAM,LPARAM);
    afx_msg void OnEnChangeEdit1();

private:

    CEdit   m_ctrlResult;

private:

    VOID    OnContructor();
    BOOL    OnInitialize();

};
