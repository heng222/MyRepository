#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "InterfaceEx.h"
#include <SortListCtrl.h>

// CDlgRoadAttri 对话框

class CDlgRoadAttri : public CDialog
{
	DECLARE_DYNAMIC(CDlgRoadAttri)

public:
	CDlgRoadAttri(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgRoadAttri();

// 对话框数据
	enum { IDD = IDD_DLG_ROADATTRI };

protected:


	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


    // 解析线程
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
