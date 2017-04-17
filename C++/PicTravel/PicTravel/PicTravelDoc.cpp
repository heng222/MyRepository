// PicTravelDoc.cpp : CPicTravelDoc 类的实现
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


// CPicTravelDoc 构造/析构

CPicTravelDoc::CPicTravelDoc()
{
	// TODO: 在此添加一次性构造代码

}

CPicTravelDoc::~CPicTravelDoc()
{
}

BOOL CPicTravelDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CPicTravelDoc 序列化

void CPicTravelDoc::Serialize(CArchive& ar)
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


// CPicTravelDoc 诊断

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


// CPicTravelDoc 命令
