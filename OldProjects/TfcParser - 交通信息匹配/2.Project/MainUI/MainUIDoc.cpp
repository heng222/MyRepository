// MainUIDoc.cpp :  CMainUIDoc ���ʵ��
//

#include "stdafx.h"
#include "MainUI.h"

#include "MainUIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainUIDoc

IMPLEMENT_DYNCREATE(CMainUIDoc, CDocument)

BEGIN_MESSAGE_MAP(CMainUIDoc, CDocument)
END_MESSAGE_MAP()


// CMainUIDoc ����/����

CMainUIDoc::CMainUIDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CMainUIDoc::~CMainUIDoc()
{
}

BOOL CMainUIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
    SetTitle(_T(""));

	return TRUE;
}




// CMainUIDoc ���л�

void CMainUIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CMainUIDoc ���

#ifdef _DEBUG
void CMainUIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMainUIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMainUIDoc ����
