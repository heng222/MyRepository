// NQD.cpp

#include "stdafx.h"
#include "NQD.h"

IMPLEMENT_SERIAL(CNQD,CObject,1)

CNQD::CNQD()
{

}

CNQD::~CNQD ()
{
}

void CNQD::DrawSlf (CDC *pDC,int mDvcSta)
{
	COLORREF	clr = mDvcSta==NS_INVALID ? CLR_INVALIDATE : KONGXIAN_CLR;
	CPen newPen(PS_SOLID,PENWIDTH,clr);
	CPen *pOldPen=pDC->SelectObject (&newPen);

	pDC->MoveTo (m_pt1);
	pDC->LineTo (m_pt2);
	pDC->SelectObject (pOldPen);
}
