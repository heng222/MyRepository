//CQjStatus.cpp

#include "stdafx.h"
#include "QjStatus.h"

#define		iRDeng	7

IMPLEMENT_SERIAL(CQjStatus,CObject,1)

CQjStatus::CQjStatus()
{
	m_bLock = FALSE;
}

CQjStatus::~CQjStatus ()
{
}

void CQjStatus::DrawSlf(CDC *pDC,int iDevSta)
{
	if (iDevSta==DS_INVALID) {
		m_bLock = FALSE;
	}

	//
	CPen newPen1(PS_SOLID,1,LIGHTGRAY);
	pDC->SelectObject (&newPen1);
	COLORREF clrLight = m_bLock ? BLUELIGHT_CLR : BLACKLIGHT_CLR;
	
	CBrush brush1(clrLight);
	CBrush *pOldBrush=pDC->SelectObject(&brush1);
	pDC->Ellipse(m_pt.x,m_pt.y-iRDeng,m_pt.x+2*iRDeng,m_pt.y+iRDeng);
	pDC->SelectObject(pOldBrush);
	pDC->SelectStockObject(BLACK_PEN);
	
	/////////////////////////////////
	CFont  font;
	font.CreateFont(16, 0, 0, 0, FW_THIN, false, false, 0,
	                    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
	                    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                    DEFAULT_PITCH | FF_SWISS, "ËÎÌו");
	CFont *pOldFont=pDC->SelectObject(&font);

	pDC->SetTextColor(WHITECOLOR);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextAlign (TA_CENTER);
	pDC->TextOut(m_pt.x,m_pt.y+QJLIGHTRADIUS+6,m_strName);
	pDC->SelectObject(pOldFont);

}

