// PicTravelDoc.cpp : CPicTravelDoc ���ʵ��
//

#include "stdafx.h"
#include "PicTravel.h"

#include "PicTravelDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPicTravelDoc

IMPLEMENT_DYNCREATE(CPicTravelDoc, CDocument)

BEGIN_MESSAGE_MAP(CPicTravelDoc, CDocument)
END_MESSAGE_MAP()


// CPicTravelDoc ����/����

CPicTravelDoc::CPicTravelDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CPicTravelDoc::~CPicTravelDoc()
{
}

BOOL CPicTravelDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CPicTravelDoc ���л�

void CPicTravelDoc::Serialize(CArchive& ar)
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


// CPicTravelDoc ���

#ifdef _DEBUG
void CPicTravelDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPicTravelDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPicTravelDoc ����
