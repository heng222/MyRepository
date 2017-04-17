// TestDlg.h : ͷ�ļ�
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

// CTestDlg �Ի���
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

// ����
public:
	CTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
