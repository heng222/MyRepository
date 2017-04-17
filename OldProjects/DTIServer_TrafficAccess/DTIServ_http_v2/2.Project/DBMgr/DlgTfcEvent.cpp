// DlgTfcEvent.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgTfcEvent.h"


// CDlgTfcEvent 对话框

IMPLEMENT_DYNAMIC(CDlgTfcEvent, CDialog)
CDlgTfcEvent::CDlgTfcEvent(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTfcEvent::IDD, pParent)
{
}

CDlgTfcEvent::~CDlgTfcEvent()
{
}

void CDlgTfcEvent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTfcEvent, CDialog)
END_MESSAGE_MAP()


// CDlgTfcEvent 消息处理程序
