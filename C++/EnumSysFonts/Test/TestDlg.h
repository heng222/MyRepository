// TestDlg.h : 头文件
//



#pragma once


#include "afxwin.h"

#include <list>
#include <string>
#include <algorithm>
#include <vector>
#include "afxcmn.h"

using namespace std;
class CFontInfo
{
public:

	string m_strFontName;
	BOOL m_bRasterFont;
	int operator<(const CFontInfo &other)
	{
		return m_strFontName < other.m_strFontName;
	}
};

// CTestDlg 对话框
class CTestDlg : public CDialog
{

	// Retrieve system's fonts.
	vector<CFontInfo> m_aFontInfo;
	void	FillFontInfo();

	// Callbacks
	static int CALLBACK S_EnumFontFamProcRaster(
		const LOGFONT *lpelf,		// logical-font data
		const TEXTMETRIC *lpntm,	// physical-font data
		DWORD FontType,				// type of font
		LPARAM lParam);				// application-defined data
	static int CALLBACK S_EnumFontProc(										 
		const LOGFONT *lpelfe,
		const TEXTMETRIC *lpntme,  
		DWORD FontType,
		LPARAM lParam);

	static BOOL	AllowFontAsLimited(string strFontName);

// 构造
public:
	CTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	int m_iTimes;
	CComboBox m_FontCombo;

	void UpdateFontSizes(BOOL bResetRasterSize);

	CRichEditCtrl m_RichEdit;
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_FontSizeCombo;
	afx_msg void OnCbnSelchangeCombo2();
public:
	afx_msg void OnBnClickedButton2();
};
