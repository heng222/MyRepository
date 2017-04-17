// HanZ.cpp

#include "stdafx.h"
#include "HanZ.h"

IMPLEMENT_SERIAL(CHanZ,CObject,1)

CHanZ::CHanZ()
{

}

CHanZ::~CHanZ ()
{

}

void CHanZ::DrawHZ (CDC *pDC,BOOL bInfInvalid,BOOL bShrink,BOOL bShow)
{
	LOGFONT lf;
	lf.lfWidth = 0;
	lf.lfStrikeOut = 0;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfEscapement = 0;//
	lf.lfItalic = 0;//
	lf.lfUnderline = 0;//
	lf.lfPitchAndFamily = DEFAULT_PITCH | FF_SWISS;
	
	//
	CFont *pOldFont,font;
	if ( m_strText.Right(2) == "վ" )
	{
		strcpy(lf.lfFaceName,"������κ");
		
		pDC->SetTextAlign(TA_LEFT | TA_TOP);
		pDC->SetBkMode(TRANSPARENT);
		
		
		if ( !bShrink ){//����Ҫѹ��
			lf.lfHeight = 45;//����߶�
			font.CreateFontIndirect(&lf);
			pOldFont = pDC->SelectObject(&font);
			
		}
		else{
			lf.lfHeight = 30;//
			font.CreateFontIndirect(&lf);
			pOldFont = pDC->SelectObject(&font);
			
		}
		
		
		pDC->SetTextColor(bInfInvalid ? REDCOLOR : GREENCOLOR);
		
		pDC->SetTextAlign(TA_LEFT);
		pDC->SetBkMode(OPAQUE);
		pDC->TextOut(m_pt.x, m_pt.y, m_strText);
		
	}
	else
	{
		int iClr;
		iClr=WHITECOLOR;
		if(!m_bHidAble) iClr=WHITECOLOR;

		strcpy(lf.lfFaceName,"����");
		lf.lfHeight = 16;//
		font.CreateFontIndirect(&lf);
		pOldFont = pDC->SelectObject(&font);
		//
		
		pDC->SetBkMode(OPAQUE);
		if (bShow) {
			pDC->SetTextColor(WHITECOLOR);
		}
		else{
			pDC->SetTextColor(BLACKCOLOR);
		}
		pDC->SetBkColor(BLACKCOLOR);
		pDC->SetTextAlign(TA_LEFT);
		pDC->TextOut(m_pt.x,m_pt.y,m_strText);
	}
	pDC->SelectObject(pOldFont);
}
void CHanZ::DrawSlf(CDC*pDC,int mDvcSta)
{
	TRACE("void CHanZ::DrawSlf(CDC*pDC,int mDvcSta)\n");
}
