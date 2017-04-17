// JYJ.cpp

#include "StdAfx.h"
#include "JYJ.h"

IMPLEMENT_SERIAL(CJYJ,CObject,1)

CJYJ::CJYJ()
{
}

CJYJ::~CJYJ()
{
}

void CJYJ::DrawSlf(CDC *pDC, int mDvcSta)
{
	int r;
	COLORREF iClr;
	int x1,x2,y1,y2,x,y;

	if(m_iType==1)//���߾�Ե��
	{
		mDvcSta==NS_INVALID ? (iClr=CLR_INVALIDATE) : (iClr=LIGHTRED);
         
		CPen newPen(PS_SOLID,1,iClr);
		CPen *pOldPen=pDC->SelectObject(&newPen);
		CBrush brush;
	    brush.CreateSolidBrush (BLACKCOLOR);
		CBrush *pOldBrush=pDC->SelectObject (&brush);
		pDC->SetBkColor (LIGHTRED);
       
		x1=max(m_pt.x ,max(m_pt1.x ,m_pt2.x ));
		x2=min(m_pt.x ,min(m_pt1.x ,m_pt2.x ));
		y1=max(m_pt.y ,max(m_pt1.y ,m_pt2.y ));
        y2=min(m_pt.y ,min(m_pt1.y ,m_pt2.y ));

		x=(m_pt.x +m_pt1.x)/2;
		y=(m_pt.y +m_pt1.y)/2;

		r=max(abs(m_pt.x-m_pt1.x),abs(m_pt.y-m_pt1.y));
		if(m_pt.x==m_pt1.x)
			pDC->Ellipse (x-r/2,y-r/2,x+r*3/4,y+r*3/4);
		else
			pDC->Ellipse (x-r*3/4,y-r*3/4,x+r,y+r);

		pDC->SetBkColor (BLACKCOLOR);
		CPen newPen1(PS_SOLID,1,WHITECOLOR);
		pDC->SelectObject(&newPen1);
		pDC->MoveTo (m_pt);
		pDC->LineTo (m_pt1);      
		
		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);
	}

	else if(m_iType==0)
	{
		iClr=WHITECOLOR;

		CPen newPen(PS_SOLID,1,iClr);
		CPen *pOldPen=pDC->SelectObject(&newPen);

		pDC->MoveTo(m_pt);
		pDC->LineTo(m_pt1);
		pDC->SelectObject(pOldPen);
	}

	else if(m_iType==2)
	{
		iClr=WHITECOLOR;
		CPen newPen(PS_SOLID,1,iClr);
		CPen *pOldPen=pDC->SelectObject(&newPen);

		pDC->MoveTo(m_pt);
		pDC->LineTo(m_pt1);
		pDC->LineTo(m_pt2);
		pDC->SelectObject(pOldPen);
	}

	else if(m_iType==3)
	{
/*
		iClr=BLACKCOLOR;
		CPen newPen(PS_SOLID,1,iClr);
		pDC->SelectObject(&newPen);
		setfillstyle(SOLID_FILL,BLACKCOLOR);
		pDC->PieSlice(m_pt.x,m_pt.y,0,360,1);
		
		iClr=WHITECOLOR;
		CPen newPen1(PS_SOLID,1,iClr);
		pDC->SelectObject(&newPen1);

		setfillstyle(SOLID_FILL,WHITE);
		pDC->PieSlice(m_pt1.x,m_pt1.y,0,360,1);
		pDC->PieSlice(m_pt2.x,m_pt2.y,0,360,1);
*/		
	}




}
