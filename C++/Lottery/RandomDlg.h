// RandomDlg.h : ͷ�ļ�
//

#pragma once

#include <winsock2.h>

#pragma comment(lib, "ws2_32")

// CRandomDlg �Ի���
class CRandomDlg : public CDialog
{
// ����
public:
	CRandomDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_RANDOM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

    BOOL    IsExist(const CWordArray& aWordArray,WORD aNewNum);
public:
    afx_msg void OnBnClickedGenerate();

    int m_iMaxNum;
    CString m_strResult;
    short m_wNumber;
    afx_msg void OnBnClickedCancel();
};
