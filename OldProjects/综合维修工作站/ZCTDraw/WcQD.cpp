//WcQD.cpp

#include"stdafx.h"
#include"WcQD.h"

IMPLEMENT_SERIAL(CWcQD,CObject,1)

CWcQD::CWcQD()
{
	
	m_bCanPlQGJ=false;
	m_bCanQGJ=false;
	//m_bHidAble=false;
	m_iStatus=0x80;
}

CWcQD::~CWcQD ()
{
}

void CWcQD::DrawSlf(CDC *pDC,int iDevSta)
{

 	int clrDraw;
 	
 	if ( iDevSta == DS_INVALID) {
 		clrDraw = CLR_INVALIDATE;
 		//m_iStatus=0x80;
 	}
 	else
 	{
 		clrDraw=KONGXIAN_CLR;
		if(m_iStatus&CYAN_BAND){
			clrDraw=ZHENGYONG_CLR;
		}
		if(m_iStatus&WHITE_BAND){
			clrDraw=SUOBI_CLR;
		}
		if(m_iStatus&RED_BAND){
			clrDraw=ZHANYONG_CLR;
		}
 	}
#ifdef _DEBUG
	//clrDraw=SUOBI_CLR;
#endif	
	

 	CPen newPen(PS_SOLID,PENWIDTH,clrDraw); 
    CPen *pOldPen=pDC->SelectObject (&newPen);
 	pDC->MoveTo (m_pt1);
 	pDC->LineTo (m_pt2);
 	pDC->SelectObject (pOldPen);	
 }

void CWcQD::ShowName (CDC *pDC,int iNameSta)
{
	CFont  font;
	font.CreateFont(-9, 4, 0, 0, FW_THIN, FALSE, FALSE, 0,
	                    ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	                    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                    DEFAULT_PITCH | FF_SWISS, "Arial");

	CFont* pOldFont = pDC->SelectObject(&font);

	if (iNameSta==NS_QGJ && m_bCanQGJ) {
		pDC->SetBkColor(REDCOLOR);
		pDC->SetTextColor(WHITECOLOR);
	}
	else{
		pDC->SetBkColor(BLACKCOLOR);
		if(iNameSta != NS_HIDE)
			pDC->SetTextColor(WHITECOLOR);
		else 
			pDC->SetTextColor(BLACKCOLOR);
	}
	
	pDC->SetBkMode(OPAQUE);
	//pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextAlign(TA_LEFT);
	pDC->TextOut (m_pt.x ,m_pt.y,m_strName);
	pDC->SelectObject(pOldFont);
}

//DEL void CWcQD::DrawQGJ (CDC *pDC,BOOL bQGJ)
//DEL {
//DEL 	CPen newPen1(PS_SOLID,1,WHITECOLOR);
//DEL 	CPen *pOldPen=pDC->SelectObject (&newPen1);
//DEL 
//DEL 	CFont  font;
//DEL 	font.CreateFont(-9, 4, 0, 0, 400, FALSE, FALSE, 0,
//DEL 	                    ANSI_CHARSET, OUT_DEFAULT_PRECIS,
//DEL 	                    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
//DEL 	                    DEFAULT_PITCH | FF_SWISS, "Arial");
//DEL 
//DEL 	CFont* pOldFont =  pDC->SelectObject(&font);
//DEL 
//DEL 	
//DEL 	if(bQGJ&&m_bCanQGJ){
//DEL 		pDC->SetBkColor(REDCOLOR);
//DEL 	}
//DEL 	else {
//DEL 		pDC->SetBkColor(BLACKCOLOR);
//DEL 	}
//DEL 	pDC->SetTextColor(WHITECOLOR);
//DEL 	pDC->SetTextAlign(TA_LEFT);
//DEL 	pDC->SetBkMode(OPAQUE);
//DEL 	pDC->TextOut (m_pt.x ,m_pt.y,m_strName);
//DEL 	
//DEL 	pDC->SelectObject(pOldFont);
//DEL 	pDC->SelectObject (pOldPen);
//DEL }

BOOL CWcQD::PtInDevice(CDC* pDC,CPoint pt,int iDeviceType)
{
	if (iDeviceType==DT_NAME) {
		CRect rectDevice=CRect(m_pt.x,m_pt.y,
				m_pt.x+(m_strName.GetLength()+1)*5,	m_pt.y+10);
		pDC->LPtoDP(rectDevice);
		if(rectDevice.PtInRect(pt) && m_bCanQGJ)
		{
			return TRUE;
		}
	}
	return FALSE;
}