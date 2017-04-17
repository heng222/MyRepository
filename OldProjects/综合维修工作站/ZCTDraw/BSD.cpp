// BSD.cpp

#include "stdafx.h"
#include "BSD.h"
 

#define ARROW_HALFW    15  /* half width of the arrow image */
#define ARROW_HALFH     6  /* half hight of the arrow image */
#define iRDeng		7
#define iJHeight	7


IMPLEMENT_SERIAL(CBSD,CObject,1)


CBSD::CBSD()
{
	m_iStatus = COL_BLACK;
	m_iTemp = 101;	//接车
}

CBSD::~CBSD ()
{
}

void CBSD::DrawArraw (CDC *pDC,BOOL bFlash)
{
	CPoint point[7];

	//先填充背景有黑色
	CRect rectBgr(CPoint(m_pt.x-ARROW_HALFW,m_pt.y-ARROW_HALFH),
		CSize(ARROW_HALFW*2+2,ARROW_HALFH*2+2));
	pDC->SelectStockObject(BLACK_BRUSH);
	//CPen pent(PS_SOLID,1,REDCOLOR);
	//pDC->SelectObject(&pent);
	pDC->SelectStockObject(BLACK_PEN);
	pDC->Rectangle(rectBgr);

	//再画箭头
/*
	if(m_iDir==1)//←
	{	
		if (m_iTemp == 101) {
			
			point[0].x=m_pt.x-ARROW_HALFW;
			point[2].x=point[1].x=m_pt.x-ARROW_HALFW/3;
			point[6].x=point[5].x=point[2].x;
			point[4].x=point[3].x=m_pt.x+ARROW_HALFW;		
		}
		else{
			point[0].x=m_pt.x+ARROW_HALFW;
			point[6].x=point[5].x=point[2].x=point[1].x=m_pt.x+ARROW_HALFW/3;
			point[4].x=point[3].x=m_pt.x-ARROW_HALFW;
		}
	} 
	else{//→
		if (m_iTemp == 101) {
			point[0].x=m_pt.x+ARROW_HALFW;
			point[6].x=point[5].x=point[2].x=point[1].x=m_pt.x+ARROW_HALFW/3;
			point[4].x=point[3].x=m_pt.x-ARROW_HALFW;
		}
		else{
			point[0].x=m_pt.x-ARROW_HALFW;
			point[2].x=point[1].x=m_pt.x-ARROW_HALFW/3;
			point[6].x=point[5].x=point[2].x;
			point[4].x=point[3].x=m_pt.x+ARROW_HALFW;
		}
		
	}
*/
	if ( (m_iDir==1 && m_iTemp==101) || (m_iDir==0 && m_iTemp==102)) {//←
		point[0].x=m_pt.x-ARROW_HALFW;
		point[2].x=point[1].x=m_pt.x-ARROW_HALFW/3;
		point[6].x=point[5].x=point[2].x;
		point[4].x=point[3].x=m_pt.x+ARROW_HALFW;
	}
	else{//→
		point[0].x=m_pt.x+ARROW_HALFW;
		point[6].x=point[5].x=point[2].x=point[1].x=m_pt.x+ARROW_HALFW/3;
		point[4].x=point[3].x=m_pt.x-ARROW_HALFW;
	}

	point[0].y=m_pt.y;
	point[1].y=m_pt.y-ARROW_HALFH;
	point[3].y=point[2].y=m_pt.y-ARROW_HALFH/2;
	point[5].y=point[4].y=m_pt.y+ARROW_HALFH/2;
	point[6].y=m_pt.y+ARROW_HALFH;

	
	//
	COLORREF iClr;
	MapLgtColor(bFlash,iClr);
	//
	CPen newPen(PS_SOLID,1,iClr==BLACKCOLOR?LIGHTGRAY:iClr);
	pDC->SelectObject (&newPen);
	
	CBrush brush(iClr);
	pDC->SelectObject(&brush);
	//
	pDC->Polygon (point,7);
	//
	pDC->SelectStockObject(BLACK_PEN);
	pDC->SelectStockObject(HOLLOW_BRUSH);
	/////////////////////////////////////
	
	ShowName(pDC,NS_COMM);
}

void CBSD::DrawLight (CDC *pDC,BOOL bLightOnly,BOOL bFlash)
{
	COLORREF iClr1;
	MapLgtColor(bFlash,iClr1);
	CBrush brush1(iClr1);
	CBrush *pOldBrush=pDC->SelectObject(&brush1);
	CPen newPen1(PS_SOLID,1,LIGHTGRAY);
	CPen newPen2(PS_SOLID,2,LIGHTGRAY);
	CPen *pOldPen1=pDC->SelectObject (&newPen1);
	if(bLightOnly)
	{
		pDC->Ellipse(m_pt.x,m_pt.y-iRDeng,m_pt.x+2*iRDeng,m_pt.y+iRDeng);
	}
	else 
	{
		pDC->Ellipse(m_pt.x,m_pt.y-iRDeng,m_pt.x+2*iRDeng,m_pt.y+iRDeng);
		pDC->SelectObject(newPen2);
		pDC->MoveTo(m_pt.x,m_pt.y-iJHeight);
		pDC->LineTo(m_pt.x,m_pt.y+iJHeight);
	}
	pDC->SelectObject(pOldBrush);
	
	//
	ShowName(pDC,NS_COMM);
}

void CBSD::DrawSlf(CDC *pDC,int iDevicSta)
{
	if (iDevicSta==DS_INVALID) {
		m_iStatus = COL_BLACK;
	}

	switch(m_iType)
	{

		//单灯式类型
	case BSD_TYPE_FJD://0
	case BSD_TYPE_TFKZ://5
	case BSD_TYPE_ZDJDQD://10
	case BSD_TYPE_ZDFZ: //11
    case BSD_TYPE_TS://20
	case BSD_TYPE_KZMS://100
		DrawLight(pDC,true,iDevicSta==DS_FLASH);
		break;

		//箭头式
	case BSD_TYPE_CLZC://1
	case BSD_TYPE_JWD://4
	case BSD_TYPE_BZDJC://7
	case BSD_TYPE_BZDFC://8
	case BSD_TYPE_ZDJFC://9
	case BSD_TYPE_TSARR://21
		DrawArraw(pDC,iDevicSta==DS_FLASH);
		break;

		//类型3/6为信号机式
	case BSD_TYPE_CLFS://3
	case BSD_TYPE_TFFS://6
		DrawLight(pDC,false,iDevicSta==DS_FLASH);
		break;

		//直线式
	case BSD_TYPE_CLJJ://2
		{
			CPen newPen(PS_SOLID,2,REDCOLOR);
			CPen *pOldPen=pDC->SelectObject(&newPen);
			pDC->MoveTo(m_pt.x,m_pt.y-iJHeight);
			pDC->LineTo(m_pt.x,m_pt.y+iJHeight);
			pDC->SelectObject(pOldPen);
			//
			ShowName(pDC,NS_COMM);
			break;
		}
	}
}

/* According the light sign's status,return its light color */
void CBSD::MapLgtColor(BOOL bFlash,COLORREF& iClr)
{
	switch(m_iStatus)
	{
	case  COL_BLACK: /*black黑*/
		iClr=BLACKLIGHT_CLR;
		break;
	
		///////
	case  COL_GREEN: /* green 绿*/
		iClr=GREENCOLOR; 
		break;
	case COL_GF:		
		bFlash ? iClr=GREENLIGHT_CLR : iClr=BLACKLIGHT_CLR; 
		break;
	
		//////
	case  COL_RED: /* red */
		iClr=REDLIGHT_CLR;
		break;
	case COL_RF:
		iClr = bFlash ? REDLIGHT_CLR : BLACKLIGHT_CLR;
		break;

		//////
	case  COL_YELLOW: /* yellow */
		iClr=YELLOWLIGHT_CLR; 
		break;
	case COL_YF:
		iClr = bFlash ? YELLOWLIGHT_CLR : BLACKLIGHT_CLR;

		//////
	case COL_WITHE :
		iClr= WHITELIGHT_CLR;
		break;
	case COL_WF:
		iClr = bFlash ? WHITELIGHT_CLR : BLACKLIGHT_CLR;
		break;
	//////
	default:
		iClr=BLACKLIGHT_CLR;
		break;
	}
}

void CBSD::ShowName(CDC *pDC,int iNameSta)
{
	CFont  font;
	font.CreateFont(15, 0, 0, 0, FW_THIN, false, false, 0,
	                    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
	                    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                    DEFAULT_PITCH | FF_SWISS, "宋体");
	CFont *pOldFont=pDC->SelectObject(&font);

	pDC->SetTextColor(WHITECOLOR);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextAlign (TA_CENTER);
    pDC->TextOut(m_T_pt.x,m_T_pt.y,m_strName);
	pDC->SelectObject(pOldFont);
}

BOOL CBSD::GetFlashState()
{
	BOOL bResult = (m_iStatus==COL_WF);
	bResult |= (m_iStatus==COL_RF);
	bResult |= (m_iStatus==COL_GF);
	bResult |= (m_iStatus==COL_YF);
	bResult |= (m_iStatus==COL_YFY);
	return bResult;
}

void CBSD::FreshLight(CDC *pDC,BOOL bLightOnly,BOOL bFlash )
{
	COLORREF iClr1;
	MapLgtColor(bFlash,iClr1);
	CBrush brush1(iClr1);
	CBrush *pOldBrush=pDC->SelectObject(&brush1);
	CPen newPen1(PS_SOLID,1,LIGHTGRAY);
	CPen newPen2(PS_SOLID,2,LIGHTGRAY);
	CPen *pOldPen1=pDC->SelectObject (&newPen1);
	if(bLightOnly)
	{
		pDC->Ellipse(m_pt.x,m_pt.y-iRDeng,m_pt.x+2*iRDeng,m_pt.y+iRDeng);
	}
	else 
	{
		pDC->Ellipse(m_pt.x,m_pt.y-iRDeng,m_pt.x+2*iRDeng,m_pt.y+iRDeng);
		pDC->SelectObject(newPen2);
		pDC->MoveTo(m_pt.x,m_pt.y-iJHeight);
		pDC->LineTo(m_pt.x,m_pt.y+iJHeight);
	}
	pDC->SelectObject(pOldBrush);
}

void CBSD::FreshArraw(CDC *pDC,BOOL bFlash )
{
	COLORREF iClr1;
	MapLgtColor(bFlash,iClr1);
	CPoint point0,point1,point2,point3,point4,point5,point6,point7;
	
	CBrush brush1(iClr1);
	CBrush *pOldBrush=pDC->SelectObject(&brush1);
	
	if(iClr1==COL_GREEN)//&&m_iDir==1)
	{	
		point7.x=point0.x=m_pt.x-ARROW_HALFW;
		
		point2.x=point1.x=m_pt.x-ARROW_HALFW/3;
		
		point6.x=point5.x=point2.x;
		point3.x=m_pt.x+ARROW_HALFW;		
		point4.x=point3.x;
		
	} 
	if(iClr1==COL_YELLOW)//&&m_iDir==0)
	{
		point7.x=point0.x=m_pt.x+ARROW_HALFW;
		point6.x=point5.x=point2.x=point1.x=m_pt.x+ARROW_HALFW/3;
		point4.x=point3.x=m_pt.x-ARROW_HALFW;
	}
	point7.y=point0.y=m_pt.y;
	point1.y=m_pt.y-ARROW_HALFH;
	point3.y=point2.y=m_pt.y-ARROW_HALFH/2;
	point5.y=point4.y=m_pt.y+ARROW_HALFH/2;
	point6.y=m_pt.y+ARROW_HALFH;

	CPen newPen(PS_SOLID,1,LIGHTGRAY);
	CPen *pOldPen=pDC->SelectObject (&newPen);
	pDC->MoveTo(point0);
	pDC->LineTo (point1);
	pDC->LineTo (point2);
	pDC->LineTo (point3);
	pDC->LineTo (point4);
	pDC->LineTo (point5);
	pDC->LineTo (point6);
	pDC->LineTo (point7);
	pDC->LineTo (point0);

	pDC->FloodFill(m_pt.x,m_pt.y,LIGHTGRAY);
	pDC->SelectObject(pOldBrush);
}
void CBSD::FreshBSD(CDC *pDC,BOOL bFlash)
{
	switch(m_iType)
	{
	case BSD_TYPE_FJD:
	case BSD_TYPE_TFKZ:
	case BSD_TYPE_ZDJDQD:
	case BSD_TYPE_ZDFZ: 
	case BSD_TYPE_TS:
	case BSD_TYPE_KZMS:
		FreshLight(pDC,true,bFlash);break;
	case BSD_TYPE_CLZC:
	case BSD_TYPE_JWD:
	case BSD_TYPE_BZDJC:
	case BSD_TYPE_BZDFC:
	case BSD_TYPE_ZDJFC:
	case BSD_TYPE_TSARR:
		FreshArraw(pDC,bFlash);break;
	case BSD_TYPE_CLFS:
	case BSD_TYPE_TFFS:
		FreshLight(pDC,false,bFlash);break;
	}
}