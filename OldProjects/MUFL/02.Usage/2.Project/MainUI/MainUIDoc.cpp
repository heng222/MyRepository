// MainUIDoc.cpp :  CMainUIDoc 类的实现
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


// CMainUIDoc 构造/析构

CMainUIDoc::CMainUIDoc()
{
	// TODO: 在此添加一次性构造代码

}

CMainUIDoc::~CMainUIDoc()
{
}

BOOL CMainUIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
    SetTitle(_T(""));

	return TRUE;
}




// CMainUIDoc 序列化

void CMainUIDoc::Serialize(CArchive& ar)
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


// CMainUIDoc 诊断

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


// CMainUIDoc 命令
