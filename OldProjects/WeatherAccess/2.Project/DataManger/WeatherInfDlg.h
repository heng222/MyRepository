#pragma once
#include "afxcmn.h"
#include "Resource.h"
#include "InterfaceEx.h"
#include "afxwin.h"


// CWeatherInfDlg �Ի���

class CWeatherInfDlg : public CDialog
{
	DECLARE_DYNAMIC(CWeatherInfDlg)

public:
	CWeatherInfDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWeatherInfDlg();

// �Ի�������
	enum { IDD = IDD_DLG_WEATHER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
