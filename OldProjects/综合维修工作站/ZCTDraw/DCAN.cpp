// DCAN.cpp

#include "stdafx.h"
#include "DCAN.h"

IMPLEMENT_SERIAL(CDCAN,CObject,1)

CDCAN::CDCAN()
{
}

CDCAN::~CDCAN ()
{
}

void CDCAN::ShowName(CDC* pDC,int iState)
{
	CFont  font;
	font.CreateFont(-10, 6, 0, 0, 400, FALSE, FALSE, 0,
	                    ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	                    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                    DEFAULT_PITCH | FF_SWISS, "Arial");

	CFont *pOldFont=pDC->SelectObject(&font);
	pDC->SetBkColor((iState==NS_QGJ) ? REDCOLOR :BLACKCOLOR);
	
	if(iState!=NS_HIDE)
		pDC->SetTextColor(WHITECOLOR);
	else
		pDC->SetTextColor(BLACKCOLOR);

	pDC->SetTextAlign(TA_LEFT);
	pDC->SetBkMode(OPAQUE);
	pDC->TextOut(m_pt.x,m_pt.y-2,m_DCText);
	pDC->SelectObject(pOldFont);
}
BOOL CDCAN::PtInDevice(CDC* pDC,CPoint pt,int iDeviceType)
{
	if (iDeviceType == DT_NAME) {		
		CRect rectDevice=CRect(m_pt.x,m_pt.y,m_pt.x+10,m_pt.y+10);
		
		pDC->LPtoDP(rectDevice);
		if(rectDevice.PtInRect(pt))	{
			return TRUE;
		}
	}
	return FALSE;
}