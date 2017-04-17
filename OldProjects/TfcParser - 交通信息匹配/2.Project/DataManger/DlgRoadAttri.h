#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "InterfaceEx.h"
#include <SortListCtrl.h>

// CDlgRoadAttri �Ի���

class CDlgRoadAttri : public CDialog
{
	DECLARE_DYNAMIC(CDlgRoadAttri)

public:
	CDlgRoadAttri(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgRoadAttri();

// �Ի�������
	enum { IDD = IDD_DLG_ROADATTRI };

protected:


	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


    // �����߳�
    CWinThread* m_pTrdParse;
    //HANDLE      m_hExitEvent;

    static UINT _ThreadParseEntry(LPVOID pParam);

public:

    afx_msg void OnBnClickedBtnParse();

    void    AttachRoad(CTfcRoadList* pRoadList);
    void    AddRoadToList();
    void    OnFinishParsing();

private:

    CSortListCtrl m_ctrlList;
    CString m_strFilePath;

    CTfcRoadList* m_pRoadList;

public:

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedBtnSave();
    afx_msg void OnBnClickedCancel();
//    afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
