// MaintainDoc.cpp : implementation of the CMaintainDoc class
//

#include "stdafx.h"
#include "Maintain.h"
#include "mainfrm.h"
#include "MaintainDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMaintainApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CMaintainDoc

IMPLEMENT_DYNCREATE(CMaintainDoc, CDocument)

BEGIN_MESSAGE_MAP(CMaintainDoc, CDocument)
	//{{AFX_MSG_MAP(CMaintainDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaintainDoc construction/destruction

CMaintainDoc::CMaintainDoc()
{
	// TODO: add one-time construction code here
}

CMaintainDoc::~CMaintainDoc()
{

}

BOOL CMaintainDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMaintainDoc serialization

void CMaintainDoc::Serialize(CArchive& ar)
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
// CMaintainDoc diagnostics

#ifdef _DEBUG
void CMaintainDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMaintainDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMaintainDoc commands

