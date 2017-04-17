// NaviServerDoc.cpp : implementation of the CNaviServerDoc class
//

#include "stdafx.h"
#include "NaviServer.h"

#include "NaviServerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNaviServerDoc

IMPLEMENT_DYNCREATE(CNaviServerDoc, CDocument)

BEGIN_MESSAGE_MAP(CNaviServerDoc, CDocument)
	//{{AFX_MSG_MAP(CNaviServerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNaviServerDoc construction/destruction

CNaviServerDoc::CNaviServerDoc()
{
	// TODO: add one-time construction code here

}

CNaviServerDoc::~CNaviServerDoc()
{
}

BOOL CNaviServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
    CString strAppName;
    strAppName.LoadString(AFX_IDS_APP_TITLE);
    SetTitle(strAppName);

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CNaviServerDoc serialization

void CNaviServerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CNaviServerDoc diagnostics

#ifdef _DEBUG
void CNaviServerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNaviServerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNaviServerDoc commands
