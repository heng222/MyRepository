#pragma once
#include "resource.h"

// CDlgTfcEvent �Ի���

class CDlgTfcEvent : public CDialog
{
	DECLARE_DYNAMIC(CDlgTfcEvent)

public:
	CDlgTfcEvent(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTfcEvent();

// �Ի�������
	enum { IDD = IDD_DLG_TFC_EVENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
