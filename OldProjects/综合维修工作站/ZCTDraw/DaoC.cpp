// DaoC.cpp
#include "stdafx.h"
#include "DaoC.h"


IMPLEMENT_SERIAL(CDaoC,CObject,1)

#define DC_LOCK_CLR			LIGHTRED     //单锁
#define DC_OFF_CLR			LIGHTBLUE	//单封

CDaoC::CDaoC():m_iStatus(DCST_SK)
{
	SinAlpha=.5;
	CosAlpha=.5;
	m_iRWCBand=0x10;
	bZoom=FALSE;
}

CDaoC::~CDaoC ()
{
}


void CDaoC::DrawGeneralDC(CDC *pDC,BOOL bInfInvalid)
{
	
	int clrDraw;
	
	BOOL bFw=IsFW();
	BOOL bDw=IsDW();
	
	//
	if ( bInfInvalid ) {
		m_iStatus = DCST_SK;
		clrDraw = CLR_INVALIDATE;
	}
	else
	{
		clrDraw = KONGXIAN_CLR;
		if(m_iRWCBand&CYAN_BAND){
			clrDraw=ZHENGYONG_CLR;
		}
		if(m_iRWCBand&WHITE_BAND){
			clrDraw=SUOBI_CLR;
		}
		if(m_iRWCBand&RED_BAND){
			clrDraw=ZHANYONG_CLR;
		}
		
	}
	
	
	if(!bDw) 
		//if(0) 
	{
		DrawDcc(pDC,/*m_pt.x,m_pt.y,*/m_deltaB.x,m_deltaB.y,
			IsSK()?clrDraw:KONGXIAN_CLR,BLACKCOLOR,FALSE,FALSE);
	}
	else
	{
		DrawDcc(pDC,/*m_pt.x,m_pt.y,*/m_deltaB.x,m_deltaB.y,clrDraw,clrDraw,FALSE,
			FALSE);
	}
	if(!bFw)
		//if(1)
	{
		DrawDcc(pDC,/*m_pt.x,m_pt.y,*/m_deltaC.x,m_deltaC.y,
			IsSK()?clrDraw:KONGXIAN_CLR,BLACKCOLOR,FALSE,FALSE);
	}
	else
	{
		DrawDcc(pDC,/*m_pt.x,m_pt.y,*/m_deltaC.x,m_deltaC.y,clrDraw,clrDraw,FALSE,
			FALSE);
	}
	
	
	//
	DrawDcc(pDC,/*m_pt.x,m_pt.y,*/m_deltaA.x,m_deltaA.y,clrDraw,clrDraw,TRUE,FALSE);
	

	
	
	//单封单锁时画小圆点
	int x,y;
	if(bZoom){
		x=(int)((DC_POINT/1)*CosAlpha+.5);
		y=(int)((DC_POINT/1)*SinAlpha+.5);
	}
	else{
		x=(int)(DC_POINT*CosAlpha+.5);
		y=(int)(DC_POINT*SinAlpha+.5);
	}
	
	if(m_deltaB.y!=0){
		if(m_deltaB.x<0) x=-x;
		if(m_deltaB.y<0) y=-y;
	}
	else{
		if(m_deltaC.x<0) x=-x;
		if(m_deltaC.y<0) y=-y;
	}

	//
	if(IsLocked()) {
		clrDraw=DC_LOCK_CLR;
	}
	else if(IsOffed()){
		clrDraw=DC_OFF_CLR;
	}
	else{
		clrDraw=BLACKCOLOR;
	}
	CPen newPen(PS_SOLID,2,clrDraw);
	pDC->SelectObject(&newPen);
	pDC->Pie(CRect(m_pt.x+x-2,m_pt.y+y-2,m_pt.x+x+2,m_pt.y+y+2),CPoint(m_pt.x+x+2,
		m_pt.y+y),CPoint(m_pt.x+x+2,m_pt.y+y));
	pDC->SelectStockObject(BLACK_PEN);
}


/* Draw a DaoCha's c location */
void CDaoC::DrawDcc(CDC *pDC,/*int x,int y,*/int deltaX,int deltaY,
					int iClr,int iClr0,BOOL bIsCJ,BOOL bCXOnly)
{
	int deltaGapX,deltaGapY;
	int deltaMidX;
	float DrawSlope;

	if(deltaX==0||deltaY==0)
	{
		deltaMidX=deltaX;
		if(bIsCJ) 
		{
			deltaGapX=deltaGapY=0;
		}
		else
		{
			if(bZoom)
			{
				deltaGapX=deltaX>0?min(deltaX,CX_RADIUS/2):max(deltaX,-CX_RADIUS/2);
				deltaGapY=deltaY>0?min(deltaY,CX_RADIUS/2):max(deltaY,-CX_RADIUS/2);
			}
			else
			{
				deltaGapX=deltaX>0?min(deltaX,CX_RADIUS):max(deltaX,-CX_RADIUS);
				deltaGapY=deltaY>0?min(deltaY,CX_RADIUS):max(deltaY,-CX_RADIUS);
			}
		}
	} 
	else
	{
		DrawSlope=(float)fabs((float)deltaY/deltaX);
		if(DrawSlope<fSlope)
		{
			DrawSlope=fSlope;
			deltaMidX=(int)(abs(deltaY)/fSlope+0.5);
			if(deltaX<0) deltaMidX=-deltaMidX;
		} 
		else deltaMidX=deltaX;

		if(!bIsCJ)
		{
			if(bZoom)
			{
				deltaGapX=(int)((CX_RADIUS/2)*sqrt(1/(1+fSlope*fSlope))+.5);
				if(deltaGapX==0) deltaGapY=CX_RADIUS/2;
				else deltaGapY=(int)(deltaGapX*fSlope+.5);
			}
			else 
			{
				deltaGapX=(int)(CX_RADIUS*sqrt(1/(1+fSlope*fSlope))+.5);
				if(deltaGapX==0) deltaGapY=CX_RADIUS;
				else deltaGapY=(int)(deltaGapX*fSlope+.5);
			}

			if(deltaX<0) deltaGapX=-deltaGapX;
			if(deltaY<0) deltaGapY=-deltaGapY;
		} 
		else {
			deltaGapX=deltaGapY=0;
		}
	}

	if(deltaGapX!=0||deltaGapY!=0)
	{
		CPen newPen(PS_SOLID,PENWIDTH,iClr0);
		CPen *pOldPen=pDC->SelectObject(&newPen);

		pDC->MoveTo(m_pt.x,m_pt.y);
		pDC->LineTo(m_pt.x+deltaGapX,m_pt.y+deltaGapY);
		pDC->SelectObject(pOldPen);
	}

	//
	if(!bCXOnly)
	{
		CPen newPen1(PS_SOLID,PENWIDTH,iClr);
		CPen *pOldPen=pDC->SelectObject(&newPen1);

		if(deltaX>=0)//Modified On 2004.8.24
		{
			pDC->MoveTo(m_pt.x+deltaGapX,m_pt.y+deltaGapY);
			if(deltaMidX!=deltaX)
			{
				pDC->LineTo(m_pt.x+deltaMidX,m_pt.y+deltaY);
			}
			pDC->LineTo(m_pt.x+deltaX,m_pt.y+deltaY);	
		}		
		else if(deltaX<0)
		{
			pDC->MoveTo(m_pt.x+deltaX,m_pt.y+deltaY);
		
			if(deltaMidX!=deltaX)
			{
				pDC->LineTo(m_pt.x+deltaMidX,m_pt.y+deltaY);
			}
			pDC->LineTo(m_pt.x+deltaGapX,m_pt.y+deltaGapY);
		}

        pDC->SelectObject(pOldPen);
	}
	
}

void CDaoC::DrawTGQ(CDC *pDC,int mDvcSta)
{
	CPoint point[2][3];//point[0]旧区域,point[1]新区域
	COLORREF iClr;
	if(IsFW()){
		point[1][0] = m_pt;
		point[1][1].x = m_pt.x+m_deltaA.x;	
		point[1][1].y = m_pt.y+m_deltaA.y;
		point[1][2].x = m_pt.x+m_deltaB.x;	
		point[1][2].y = m_pt.y+m_deltaB.y;
		//
		point[0][0].x = m_pt.x;
		point[0][0].y = m_pt.y + m_deltaC.y;
		point[0][1].x = m_pt.x+m_deltaA.x;
		point[0][1].y = m_pt.y+m_deltaA.y+m_deltaC.y;
		point[0][2].x = m_pt.x+m_deltaB.x;
		point[0][2].y = m_pt.y+m_deltaB.y+m_deltaC.y;
	}
	else{
		point[1][0].x = m_pt.x;
		point[1][0].y = m_pt.y + m_deltaC.y;
		point[1][1].x = m_pt.x+m_deltaA.x;
		point[1][1].y = m_pt.y+m_deltaA.y+m_deltaC.y;
		point[1][2].x = m_pt.x+m_deltaB.x;
		point[1][2].y = m_pt.y+m_deltaB.y+m_deltaC.y;
		//
		point[0][0] = m_pt;
		point[0][1].x = m_pt.x+m_deltaA.x;	
		point[0][1].y = m_pt.y+m_deltaA.y;
		point[0][2].x = m_pt.x+m_deltaB.x;	
		point[0][2].y = m_pt.y+m_deltaB.y;
	}

	//先用黑色画旧区域
	CBrush brhOld(BLACKCOLOR);
	CRgn oldRgn;
	oldRgn.CreatePolygonRgn(point[0],3,WINDING);
	pDC->FillRgn(&oldRgn,&brhOld);
	
	
	//再用指定的颜色画新区域
	switch(mDvcSta) {
	case DS_INVALID:
		iClr = CLR_INVALIDATE;
		break;
	case DS_HIDE:
		iClr = BLACKCOLOR;
		break;
	case DS_FLASH:
		iClr = REDCOLOR;
		break;
	default:
		iClr = KONGXIAN_CLR;
	}

	CBrush brushNew(iClr);
	CRgn newRgn;
	newRgn.CreatePolygonRgn(point[1],3,WINDING);
	pDC->FillRgn(&newRgn,&brushNew);
}
void CDaoC::DrawSlf(CDC* pDC, int mDvcSta)
{
	if ( m_iType == DT_TUOGUIQI) {
		DrawTGQ(pDC,mDvcSta);
	}
	else if ( m_iType == DT_GENERAL) {
		DrawGeneralDC(pDC,mDvcSta==DS_INVALID);
	}
}
