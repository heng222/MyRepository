// SheetConfig.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SheetConfig.h"


// CSheetConfig

IMPLEMENT_DYNAMIC(CSheetConfig, CPropertySheet)
CSheetConfig::CSheetConfig(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CSheetConfig::CSheetConfig(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
    AddPage(&m_dlgPage1);
    AddPage(&m_dlgPage2);
}

CSheetConfig::~CSheetConfig()
{
}


BEGIN_MESSAGE_MAP(CSheetConfig, CPropertySheet)
END_MESSAGE_MAP()


// CSheetConfig ��Ϣ�������


//////////////////////////////////////////////////////////////////////////
// CPropertyPage1 �Ի���

IMPLEMENT_DYNAMIC(CPropertyPage1, CPropertyPage)
CPropertyPage1::CPropertyPage1()
	: CPropertyPage(CPropertyPage1::IDD)
{
}

CPropertyPage1::~CPropertyPage1()
{
}

void CPropertyPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPropertyPage1, CPropertyPage)
END_MESSAGE_MAP()


// CPropertyPage1 ��Ϣ�������


//////////////////////////////////////////////////////////////////////////
// CPropertyPage2 �Ի���

IMPLEMENT_DYNAMIC(CPropertyPage2, CPropertyPage)
CPropertyPage2::CPropertyPage2()
	: CPropertyPage(CPropertyPage2::IDD)
{
}

CPropertyPage2::~CPropertyPage2()
{
}

void CPropertyPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPropertyPage2, CPropertyPage)
END_MESSAGE_MAP()


// CPropertyPage2 ��Ϣ�������
