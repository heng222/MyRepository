#pragma once
#include "afxcmn.h"
#include "Resource.h"
#include "InterfaceEx.h"
#include "afxwin.h"


// CWeatherInfDlg 对话框

class CWeatherInfDlg : public CDialog
{
	DECLARE_DYNAMIC(CWeatherInfDlg)

public:
	CWeatherInfDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWeatherInfDlg();

// 对话框数据
	enum { IDD = IDD_DLG_WEATHER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

    void    AddCityToTree(HTREEITEM hParent,CCityList* pCityList);

private:
    CTreeCtrl m_ctrlTree;
    CImageList m_imageList;
    CString m_strWeather;

public:
    afx_msg void OnBnClickedBtnQuery();
    virtual BOOL OnInitDialog();

private:
    CString m_strCityName;
public:
    afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
private:
    CComboBox m_ctrlPeriod;
};
