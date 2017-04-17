#pragma once
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "resource.h"

//////////////////////////////////////////////////////////////////////////
// CPropertyPage1 �Ի���
class CPropertyPage1 : public CPropertyPage
{
    DECLARE_DYNAMIC(CPropertyPage1)

public:
    CPropertyPage1();
    virtual ~CPropertyPage1();

    // �Ի�������
    enum { IDD = IDD_PROPPAGE_1 };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

    DECLARE_MESSAGE_MAP()
};




//////////////////////////////////////////////////////////////////////////
// CPropertyPage2 �Ի���
class CPropertyPage2 : public CPropertyPage
{
    DECLARE_DYNAMIC(CPropertyPage2)

public:
    CPropertyPage2();
    virtual ~CPropertyPage2();

    // �Ի�������
    enum { IDD = IDD_PROPPAGE_2 };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

    DECLARE_MESSAGE_MAP()
};



//////////////////////////////////////////////////////////////////////////
// CSheetConfig
class CSheetConfig : public CPropertySheet
{
	DECLARE_DYNAMIC(CSheetConfig)

public:
	CSheetConfig(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSheetConfig(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CSheetConfig();
public:
    CPropertyPage1  m_dlgPage1;
    CPropertyPage2  m_dlgPage2;

protected:
	DECLARE_MESSAGE_MAP()
};


