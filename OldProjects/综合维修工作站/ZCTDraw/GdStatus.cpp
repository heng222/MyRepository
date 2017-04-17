//CGdStatus.cpp

#include "stdafx.h"
#include "GdStatus.h"

#define		iRDeng	7

IMPLEMENT_SERIAL(CGdStatus,CObject,1)

CGdStatus::CGdStatus()
{
	m_bLock = FALSE;
}

CGdStatus::~CGdStatus ()
{
}

void CGdStatus::DrawSlf(CDC *pDC,int mDvcSta)
{
	if ( mDvcSta == DS_INVALID ) {
		m_bLock = FALSE;
	}
	
	//是否处于封锁状态
	COLORREF clrLight = m_bLock ? BLUELIGHT_CLR : BLACKLIGHT_CLR;

	CBrush brush1(clrLight);
	CBrush *pOldBrush=pDC->SelectObject(&brush1);
	CPen newPen1(PS_SOLID,1,LIGHTGRAY);
	pDC->SelectObject (&newPen1);
	pDC->Ellipse(m_pt.x,m_pt.y-iRDeng,m_pt.x+2*iRDeng,m_pt.y+iRDeng);	
	pDC->SelectObject(pOldBrush);
	pDC->SelectStockObject(BLACK_PEN);
	
	//名称
	CFont  font;
	font.CreateFont(16, 0, 0, 0, FW_THIN, false, false, 0,
	                    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
	                    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                    DEFAULT_PITCH | FF_SWISS, "宋体");
	CFont *pOldFont=pDC->SelectObject(&font);
	pDC->SetTextColor(WHITECOLOR);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextAlign (TA_CENTER);
	pDC->TextOut(m_pt.x,m_pt.y+GDLIGHTRADIUS+6,m_strName);
	pDC->SelectObject(pOldFont);

}

BOOL CGdStatus::PtInDevice(CDC* pDC,CPoint pt,int iDeviceType)
{
	CRect rectDevice=CRect(m_pt.x,m_pt.y-GDLIGHTRADIUS,
		m_pt.x+GDLIGHTRADIUS*2,m_pt.y+GDLIGHTRADIUS);
	
	pDC->LPtoDP(rectDevice);
	
	if(rectDevice.PtInRect(pt))	{
		return TRUE;
	}		
	return FALSE;
}

