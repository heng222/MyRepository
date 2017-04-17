// AnN.cpp

#include "stdafx.h"
#include "AnN.h"
#include "DaoC.h"

IMPLEMENT_SERIAL(CAnN,CObject,1)

CAnN::CAnN()
{
	m_byDCStatus = DCST_SK;
}

CAnN::~CAnN()
{

}
void CAnN::DrawSlf(CDC* pDC,int mDvcSta)
{
	COLORREF iClr,iClr1,iClr2;
	iClr1=DEEPGRAY;
	iClr2=WHITECOLOR;

	//调车按钮
	if(m_iType== BTN_TYPE_DA)
	{
		if(mDvcSta != DS_DOWN){
			pDC->Draw3dRect (CRect(m_pt.x,m_pt.y,m_pt.x+AN_WIDTH,m_pt.y+AN_HEIGHT),iClr2,iClr1);
			iClr=DA_BTN_CLR1;
		}
		else{
			pDC->Draw3dRect (CRect(m_pt.x,m_pt.y,m_pt.x+AN_WIDTH,m_pt.y+AN_HEIGHT),iClr1,iClr2);
			iClr=DA_BTN_CLR2;
		}
	}

	//列车按钮
	else if(m_iType==BTN_TYPE_LA)
	{
		if(mDvcSta != DS_DOWN){
			pDC->Draw3dRect (CRect(m_pt.x,m_pt.y,m_pt.x+AN_WIDTH,m_pt.y+AN_HEIGHT),iClr2,iClr1);
			iClr=LA_BTN_CLR1;

		}
		else{
			pDC->Draw3dRect (CRect(m_pt.x,m_pt.y,m_pt.x+AN_WIDTH,m_pt.y+AN_HEIGHT),iClr1,iClr2);
			iClr=LA_BTN_CLR2;
		}
	}

	//道岔按钮
	else if(m_iType==BTN_TYPE_CA)
	{
		//根据相应的道岔状态做不同的处理
		if ( DAOCHA_ISSK(m_byDCStatus) ){//四开
			iClr=DC_BTN_CLR1;
		}
		else if ( DAOCHA_ISDW(m_byDCStatus) ){//定位
			iClr=DC_BTN_CLR2;
		}
		else if ( DAOCHA_ISFW(m_byDCStatus) ){//反位
			iClr=DC_BTN_CLR3;
		}
		else{
			iClr=DC_BTN_CLR1;
		}
		//
		if( DAOCHA_ISJC(m_byDCStatus) ){//挤岔
			iClr=DC_BTN_CLR4;
		}
		
		
		//
		if(mDvcSta != DS_DOWN){
			pDC->Draw3dRect (CRect(m_pt.x,m_pt.y,m_pt.x+AN_WIDTH,m_pt.y+AN_HEIGHT),iClr2,iClr1);
		}
		else{
			pDC->Draw3dRect (CRect(m_pt.x,m_pt.y,m_pt.x+AN_WIDTH,m_pt.y+AN_HEIGHT),iClr1,iClr2);
		}
	}
	//其它按钮
	else{
		if(mDvcSta != DS_DOWN){
			pDC->Draw3dRect (CRect(m_pt.x,m_pt.y,m_pt.x+AN_WIDTH,m_pt.y+AN_HEIGHT),iClr2,iClr1);
			iClr=QT_BTN_CLR1;			
		}
	    else{
			pDC->Draw3dRect (CRect(m_pt.x,m_pt.y,m_pt.x+AN_WIDTH,m_pt.y+AN_HEIGHT),iClr1,iClr2);
			iClr=QT_BTN_CLR2;
		}
	}
	//
	if (mDvcSta == DS_INVALID) {
		iClr = CLR_INVALIDATE;
	}
	//
	pDC->FillSolidRect (CRect(m_pt.x+1,m_pt.y+1,m_pt.x+AN_WIDTH-1,m_pt.y+AN_HEIGHT-1),iClr);

}

void CAnN::ShowName (CDC *pDC,int iState)
{
	/*
	 *	若配置文件中不允许显示，则bShow无效
	 */
	if( m_bShow == FALSE ){
		return;
	}

	//
	COLORREF iClr;
	if ( m_iType == BTN_TYPE_CA ){
		if( DAOCHA_ISOFF(m_byDCStatus) ){//单封
			iClr = BLUECOLOR;
		}
		else if( DAOCHA_ISLOCK(m_byDCStatus) ){//单锁	
			iClr = REDCOLOR;
		}
		else{
			iClr = WHITECOLOR;
		}
	}
	else{
		iClr = (iState==NS_COMM) ? WHITECOLOR : BLACKCOLOR;
	}

	//
	CFont  font;
	font.CreateFont(-10, 6, 0, 0, FW_LIGHT, false, false, 0,
	                    ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	                    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                    DEFAULT_PITCH | FF_SWISS, "Arial");
	CFont *pOldFont=pDC->SelectObject(&font);
	pDC->SetBkColor(BLACKCOLOR);
	pDC->SetTextColor(iClr);
	pDC->SetTextAlign(TA_CENTER);
	iState==DS_COMM ? pDC->SetBkMode(TRANSPARENT) : pDC->SetBkMode(OPAQUE);
	pDC->TextOut(m_pt.x+m_deltaX,m_pt.y+m_deltaY-AN_HEIGHT+2,m_strName);
	pDC->SelectObject(pOldFont);
}
