// GDI+SampleDoc.cpp : CGDISampleDoc ���ʵ��
//

#include "stdafx.h"
#include "GDI+Sample.h"

#include "GDI+SampleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDISampleDoc

IMPLEMENT_DYNCREATE(CGDISampleDoc, CDocument)

BEGIN_MESSAGE_MAP(CGDISampleDoc, CDocument)
END_MESSAGE_MAP()


// CGDISampleDoc ����/����

CGDISampleDoc::CGDISampleDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CGDISampleDoc::~CGDISampleDoc()
{
}

BOOL CGDISampleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CGDISampleDoc ���л�

void CGDISampleDoc::Serialize(CArchive& ar)
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


// CGDISampleDoc ���

#ifdef _DEBUG
void CGDISampleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGDISampleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGDISampleDoc ����
