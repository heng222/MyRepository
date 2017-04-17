// BaseElement.cpp: implementation of the CBaseElement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaseElement.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBaseElement::CBaseElement()
{
	
}

CBaseElement::~CBaseElement()
{
}

void CBaseElement::DrawSlf(CDC *pDC,int mDvcSta)
{
	TRACE("void CBaseElement::DrawSlf(CDC,int)\n");
}

void CBaseElement::ShowName(CDC *pDC, int iState)
{
	TRACE("void CBaseElement::ShowName(CDC *pDC, int iState)\n");
}

int CBaseElement::GetCommandID()
{
	TRACE("int CBaseElement::GetCommandID()\n");
	return 0;
}

int CBaseElement::GetType()
{
	TRACE("int CBaseElement::GetType()\n");
	return 0;
}
