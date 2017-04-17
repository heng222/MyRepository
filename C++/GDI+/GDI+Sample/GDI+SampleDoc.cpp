// GDI+SampleDoc.cpp : CGDISampleDoc 类的实现
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


// CGDISampleDoc 构造/析构

CGDISampleDoc::CGDISampleDoc()
{
	// TODO: 在此添加一次性构造代码

}

CGDISampleDoc::~CGDISampleDoc()
{
}

BOOL CGDISampleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CGDISampleDoc 序列化

void CGDISampleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CGDISampleDoc 诊断

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


// CGDISampleDoc 命令
