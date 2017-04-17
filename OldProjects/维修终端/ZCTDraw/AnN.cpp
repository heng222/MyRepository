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

	//������ť
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

	//�г���ť
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

	//����ť
	else if(m_iType==BTN_TYPE_CA)
	{
		//������Ӧ�ĵ���״̬����ͬ�Ĵ���
		if ( DAOCHA_ISSK(m_byDCStatus) ){//�Ŀ�
			iClr=DC_BTN_CLR1;
		}
		else if ( DAOCHA_ISDW(m_byDCStatus) ){//��λ
			iClr=DC_BTN_CLR2;
		}
		else if ( DAOCHA_ISFW(m_byDCStatus) ){//��λ
			iClr=DC_BTN_CLR3;
		}
		else{
			iClr=DC_BTN_CLR1;
		}
		//
		if( DAOCHA_ISJC(m_byDCStatus) ){//����
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
	//������ť
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
	 *	�������ļ��в�������ʾ����bShow��Ч
	 */
	if( m_bShow == FALSE ){
		return;
	}

	//
	COLORREF iClr;
	if ( m_iType == BTN_TYPE_CA ){
		if( DAOCHA_ISOFF(m_byDCStatus) ){//����
			iClr = BLUECOLOR;
		}
		else if( DAOCHA_ISLOCK(m_byDCStatus) ){//����	
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
