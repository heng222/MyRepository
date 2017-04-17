// ddmlxdDlg.h : header file
//

#if !defined(AFX_DDMLXDDLG_H__174B1C76_1ADA_4D15_9B57_1B177759E8CA__INCLUDED_)
#define AFX_DDMLXDDLG_H__174B1C76_1ADA_4D15_9B57_1B177759E8CA__INCLUDED_

#include "Maintain.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "SortListCtrl.h"
#include "RailwayBureau.h"

class CMainFrame;
/////////////////////////////////////////////////////////////////////////////
// CDdmlxdDlg dialog
class CDdmlxdDlg : public CDialog
{
// Construction
public:
	
	void ShowResponse();
	void SetComKind(BYTE wComKind);
	void ShowDetailedInf();
	
	void SetChecked(BOOL bChecked);
	void SetRCDateTime(COleDateTime tDT);

public:
	void SetRCDateTime(CTime tDT);

	void SetOrder(int iOrder);
	WORD GetComKind();

	CDdmlxdDlg(CWnd* pParent = NULL);	// standard constructor
	
	CAdoRecordSet m_adoSet;
	// Dialog Data
	//{{AFX_DATA(CDdmlxdDlg)
	enum { IDD = IDD_OPERATE_DIALOG };
	CComboBox	m_ctrlSendDispatchID;
	CComboBox	m_ctrlRecSubBureau;
	CComboBox	m_ctrlRecBureau;
	CComboBox	m_ctrlSendSubBureau;
	CComboBox	m_ctrlSendBureau;
	CEdit	m_ctrlDestination;
	CSortListCtrl	m_ctrlCFStation;
	CComboBox	m_ctrlTitle;
	CDateTimeCtrl	m_ctrlSendTime;
	CRichEditCtrl	m_ctrlEdit;
	CListCtrl	m_ctrlList;
	CString	m_strContent;
	CString	m_strStation;
	CString	m_strCopyFor;
	CString	m_strDestination;
	CString	m_strChecker;
	CString	m_strCheckTime;
	int		m_iDisNum;
	COleDateTime	m_tSendTime;
	CString	m_strTitle;
	CString	m_strDispatcher;
	CString	m_strOrgReceive;
	CString	m_strOrgSend;
	CString	m_strSendDispatchID;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDdmlxdDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDdmlxdDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSend();
	afx_msg void OnDsend();
	afx_msg void OnSelchangeTiltle();
	afx_msg void OnOperateExtend();
	virtual void OnCancel();
	afx_msg void OnSelchangeComboDdmlReceivebureau();
	afx_msg void OnSelchangeComboDdmlSendbureau();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:

	//������ʱ��
	COleDateTime m_tDateTime;

	//�˵������������ݿ�����Ӧ�ļ�¼���
	int m_iOrder;

	//���������Ƿ������
	BOOL m_bChecked;

	//����ָ���Ƿ�������(1)���ǿ�ͨ����(2)
	WORD m_wComKind;

	CRailwayBureau m_Bureau;

	CMainFrame*		m_pMainFrame;

private:
	//��������ͨ���������ŵ����ݿ���
	//�ڵ�������ϴ����е���ֱ���´�ʱʹ��
	void AddNewData();
	//�������֡
	void SendDisComFrame(int iStatus);
	
	void StoreComOrder();

	//�������״̬������Ӧ�ؼ��Ŀ���״̬
	void UpdateCtrlComponet();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DDMLXDDLG_H__174B1C76_1ADA_4D15_9B57_1B177759E8CA__INCLUDED_)
