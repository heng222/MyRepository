// JT.cpp

#include "stdafx.h"
#include "JT.h"

IMPLEMENT_SERIAL(CJT,CObject,1)

CJT::CJT()
{

}

CJT::~CJT ()
{

}

void CJT::DrawSlf(CDC *pDC,int mDvcSta)
{
	
	CPen newPen,newPen1;
	if (mDvcSta == NS_INVALID) {
		newPen.CreatePen(PS_SOLID,1,CLR_INVALIDATE);
		newPen1.CreatePen(PS_SOLID,2,CLR_INVALIDATE);
	}
	else
	{
		newPen.CreatePen(PS_SOLID,1,WHITECOLOR);
		newPen1.CreatePen(PS_SOLID,2,KONGXIAN_CLR);
	}
	CPen *pOldPen=pDC->SelectObject(&newPen);

	// ¿ª¿ÚÏòÓÒ
	int deltaX;
    if(m_iDir==0)
		deltaX=JT_W;
	else
		deltaX=-JT_W;

	switch(m_iType)
	{
	case 0:
		pDC->MoveTo(m_pt.x+deltaX,m_pt.y-JT_HALF_H);
		pDC->LineTo(m_pt.x,m_pt.y-JT_HALF_H);
		pDC->LineTo(m_pt.x,m_pt.y+JT_HALF_H);
		pDC->LineTo(m_pt.x+deltaX,m_pt.y+JT_HALF_H);
		break;
	case 1:  // draw with a bow
		pDC->SelectObject(&newPen1);
		pDC->MoveTo(m_pt.x,m_pt.y);
		pDC->LineTo(m_pt.x+deltaX,m_pt.y-JT_HALF_H);
		pDC->LineTo(m_pt.x+deltaX,m_pt.y+JT_HALF_H);
		pDC->LineTo(m_pt.x+deltaX*2,m_pt.y);
		pDC->LineTo(m_pt.x+deltaX*4,m_pt.y);
		
		pDC->SelectObject(&newPen);//
		pDC->MoveTo(m_pt.x+deltaX*5,m_pt.y-JT_HALF_H);
		pDC->LineTo(m_pt.x+deltaX*4,m_pt.y-JT_HALF_H);
		pDC->LineTo(m_pt.x+deltaX*4,m_pt.y+JT_HALF_H);
		pDC->LineTo(m_pt.x+deltaX*5,m_pt.y+JT_HALF_H);
		break;
	}
	pDC->SelectObject(pOldPen);
}