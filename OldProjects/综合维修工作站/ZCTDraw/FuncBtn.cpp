//CFuncBtn.cpp

#include "stdafx.h"
#include "FuncBtn.h"


IMPLEMENT_DYNCREATE(CFuncBtn, CObject)

CFuncBtn::CFuncBtn()
{
}

CFuncBtn::~CFuncBtn ()
{
}

void CFuncBtn::DrawSlf (CDC *pDC,int mDvcSta)
{
	COLORREF iClr1,iClr2,iClr3;
	if ( m_iStatus == DS_DOWN || mDvcSta == DS_DOWN)
	{
		iClr1=WHITECOLOR;
		iClr2=DEEPGRAY;
		if (m_iCommandID == SYZS || m_iCommandID == XYZS) {
			iClr3 = DC_BTN_CLR4;
		}
		else{
			iClr3=DA_BTN_CLR2;
		}
	}
	else if( mDvcSta == DS_COMM )
	{
		iClr1=DEEPGRAY;

		iClr2=WHITECOLOR;
		iClr3=DA_BTN_CLR1;	
	}
	else if( mDvcSta == DS_FLASH)
	{
		iClr1=DEEPGRAY;
		iClr2=WHITECOLOR;		
		iClr3=REDCOLOR;
	}

	CBrush brush;
	brush.CreateSolidBrush (iClr3);	
    CBrush *pOldBrush=pDC->SelectObject (&brush);

	CPen newPen1(PS_SOLID,2,iClr1);
	CPen *pOldPen=pDC->SelectObject(&newPen1);
	pDC->Pie(CRect(m_pt.x-FUNBTNRADIUS,m_pt.y-FUNBTNRADIUS,m_pt.x+FUNBTNRADIUS,m_pt.y+FUNBTNRADIUS),CPoint(int(m_pt.x+0.7*FUNBTNRADIUS),int(m_pt.y-0.7*FUNBTNRADIUS)),
		CPoint(int(m_pt.x+0.7*FUNBTNRADIUS),int(m_pt.y-0.7*FUNBTNRADIUS)));
	CPen newPen2(PS_SOLID ,2,iClr2);
	pDC->SelectObject(&newPen2);
	pDC->Pie(CRect(m_pt.x-FUNBTNRADIUS,m_pt.y-FUNBTNRADIUS,m_pt.x+FUNBTNRADIUS,m_pt.y+FUNBTNRADIUS),CPoint(int(m_pt.x+0.7*FUNBTNRADIUS),int(m_pt.y-0.7*FUNBTNRADIUS)),
		CPoint(int(m_pt.x-0.7*FUNBTNRADIUS),int(m_pt.y+0.7*FUNBTNRADIUS)));
	
	CPen newPen3(PS_SOLID,3,iClr3);
	pDC->SelectObject(&newPen3);
	pDC->MoveTo(CPoint(int(m_pt.x+0.7*FUNBTNRADIUS),int(m_pt.y-0.7*FUNBTNRADIUS)));
	pDC->LineTo(CPoint(int(m_pt.x-0.7*FUNBTNRADIUS),int(m_pt.y+0.7*FUNBTNRADIUS)));

	
	CPen newPen5(PS_SOLID,2,BLACKCOLOR);
	pDC->SelectObject (&newPen5);
	pDC->MoveTo(m_pt.x-FUNBTNRADIUS,m_pt.y-FUNBTNRADIUS-1);
	pDC->LineTo(m_pt.x+FUNBTNRADIUS,m_pt.y-FUNBTNRADIUS-1);

	pDC->SelectObject (pOldPen);
	pDC->SelectObject (pOldBrush);


	
	//功能按钮文字
	CFont  font,*pOldFont;
	font.CreateFont(-15, 0, 0, 0, 400, FALSE, FALSE, 0,
	                    ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	                    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                    DEFAULT_PITCH | FF_SWISS, "Arial");
	pOldFont = pDC->SelectObject(&font);

	pDC->SetTextColor(WHITECOLOR);
	pDC->SetBkColor(BLACKCOLOR);
	pDC->SetTextAlign (TA_CENTER);
	pDC->TextOut(m_pt.x,m_pt.y+FUNBTNRADIUS+6,m_strName);	
	pDC->SelectObject(pOldFont);
}
BOOL CFuncBtn::PtInDevice(CDC* pDC,CPoint pt,int iDeviceType)
{
	CRect rectDevice=CRect(m_pt.x-FUNBTNRADIUS,m_pt.y-FUNBTNRADIUS,
						m_pt.x+FUNBTNRADIUS,m_pt.y+FUNBTNRADIUS);
	
	pDC->LPtoDP(rectDevice);
	
	if(rectDevice.PtInRect(pt))	{
		return TRUE;
	}		
	return FALSE;
}
