// XinHJ.cpp

#include "StdAfx.h"
#include "XinHJ.h"

IMPLEMENT_SERIAL(CXinHJ,CObject,1)

CXinHJ::CXinHJ(): m_bHigh(FALSE),m_iStatus(COL_RED),bZoom(FALSE)
{}

CXinHJ::~CXinHJ()
{}

void CXinHJ::DrawSlf(CDC *pDC,int iDevState)
{
	if(m_iType==XT_INVALID) return;

	//-----------------------
	COLORREF iClr1/*信号机1的颜色*/,iClr2/*信号机2的颜色*/;
	if ( iDevState==DS_INVALID){
		iClr1 = BLACKCOLOR;
		iClr2 = BLACKCOLOR;
	}
	else
	{
		MapLgtColor(iDevState==DS_FLASH,iClr1,iClr2);
		if(iClr2==BLUELIGHT_CLR||iClr2==REDLIGHT_CLR){
			iClr2 = (m_iForBidClr==1) ? REDLIGHT_CLR : BLUELIGHT_CLR;
		}
	}

	//
	CBrush brush1(iClr1),brush2(iClr2);
	
   	//-------
	CPen newPen1(PS_SOLID,1,LIGHTGRAY);//信号机边缘
	CPen newPen2(PS_SOLID,2,LIGHTGRAY);//信号柱
	
	int iJHeight=0,iRDeng=0;// 画 "|"
	//是否缩放
	pDC->SelectObject (&newPen2);
	if(bZoom){
		pDC->MoveTo(m_pt.x,m_pt.y-iRJ/2);
		pDC->LineTo(m_pt.x,m_pt.y+iRJ/2);
		//
		m_iDir==XD_RIGHT ? iJHeight=JHeight/2 : iJHeight=-JHeight/2;
		iRDeng=RDeng/2;
	}
	else{
		pDC->MoveTo(m_pt.x,m_pt.y-iRJ);
		pDC->LineTo(m_pt.x,m_pt.y+iRJ);
		//
		m_iDir==XD_RIGHT ? iJHeight=JHeight : iJHeight = -JHeight;
		iRDeng=RDeng;
	}

	//
	pDC->SelectObject(&brush2);
	
	//方向向右
	if(m_iDir==XD_RIGHT)
	{
		if(m_bHigh)
		{
			//画"－"　＜|－＞
			pDC->MoveTo(m_pt.x,m_pt.y);
			pDC->LineTo(m_pt.x+iJHeight,m_pt.y);
			
			//
			pDC->SelectObject (&newPen1);
			//为列车信号机
			if(m_iType==XT_LIECHE)
			{
			    pDC->Ellipse(m_pt.x+iJHeight,m_pt.y-iRDeng,m_pt.x+iJHeight+2*iRDeng,
				    m_pt.y+iRDeng);
				//
				pDC->SelectObject (&brush1);
			    pDC->Ellipse(m_pt.x+iJHeight+2*iRDeng,m_pt.y-iRDeng,m_pt.x+iJHeight+4*iRDeng,
				    m_pt.y+iRDeng);
			}
			//为调车信号机
			else if(m_iType==XT_DIAOCHE){
			    pDC->Ellipse(m_pt.x+iJHeight,m_pt.y-iRDeng,m_pt.x+iJHeight+2*iRDeng,m_pt.y+iRDeng);
			}
		}
		else 
		{
			pDC->SelectObject (&newPen1);
			//为列车信号机
			if(m_iType==XT_LIECHE){
			    pDC->Ellipse(m_pt.x,m_pt.y-iRDeng,m_pt.x+2*iRDeng,m_pt.y+iRDeng);
			    
				//
				pDC->SelectObject (&brush1);
				pDC->Ellipse(m_pt.x+2*iRDeng,m_pt.y-iRDeng,m_pt.x+4*iRDeng,m_pt.y+iRDeng);
			}
			//为调车信号机
			else if(m_iType==XT_DIAOCHE){
			    pDC->Ellipse(m_pt.x,m_pt.y-iRDeng,m_pt.x+2*iRDeng,m_pt.y+iRDeng);
			}

		}
	}
	
	//方向向左
	else if (m_iDir == XD_LEFT) 
	{
		if(m_bHigh)
		{
			//画 " － "
			pDC->MoveTo(m_pt.x,m_pt.y);
			pDC->LineTo(m_pt.x+iJHeight,m_pt.y);

			//
            pDC->SelectObject (&newPen1);
			//为列车信号机
			if(m_iType==XT_LIECHE)
			{
				pDC->Ellipse(m_pt.x+iJHeight-2*iRDeng,m_pt.y-iRDeng,m_pt.x+iJHeight,
				   m_pt.y+iRDeng);
				
				pDC->SelectObject (&brush1);
				pDC->Ellipse(m_pt.x+iJHeight-4*iRDeng,m_pt.y-iRDeng,m_pt.x+iJHeight-2*iRDeng,
					m_pt.y+iRDeng);
			}
			//为调车信号机
			else if(m_iType==XT_DIAOCHE){
				pDC->Ellipse(m_pt.x+iJHeight-2*iRDeng,m_pt.y-iRDeng,m_pt.x+iJHeight,
				   m_pt.y+iRDeng);
			}
		}
		//为矮柱
		else
		{
			pDC->SelectObject (&newPen1);
			//为列车信号机
			if(m_iType==XT_LIECHE)
			{
				pDC->Ellipse(m_pt.x-2*iRDeng,m_pt.y-iRDeng,m_pt.x,m_pt.y+iRDeng);

				pDC->SelectObject (&brush1);
				pDC->Ellipse(m_pt.x-4*iRDeng,m_pt.y-iRDeng,m_pt.x-2*iRDeng,m_pt.y+iRDeng);
               
			}
			//为调车信号机
			else if(m_iType==XT_DIAOCHE){
				pDC->Ellipse(m_pt.x-2*iRDeng,m_pt.y-iRDeng,m_pt.x,m_pt.y+iRDeng);				
			}
		}
	}

	pDC->SelectStockObject(BLACK_PEN);
	pDC->SelectStockObject(BLACK_BRUSH);	
		
}

/* According the light sign's status,return its light color */
void CXinHJ::MapLgtColor(BOOL bFlash,COLORREF& iClr1,COLORREF& iClr2)
{
	switch(m_iStatus)
	{
	case  COL_BLACK: /*black*/
		iClr1 = iClr2 = BLACKLIGHT_CLR;
		return;
	case  COL_WITHE: /* white */
		if(m_iType==XT_LIECHE)
		{
		  iClr1=WHITELIGHT_CLR;
		  iClr2=BLACKLIGHT_CLR;
		}
		else{
			iClr2=WHITELIGHT_CLR;
		}
		  return;
	case  COL_BLUE: /* blue */
		if(m_iType==XT_LIECHE)
		{
			iClr1=BLUELIGHT_CLR; 
			iClr2=BLACKLIGHT_CLR;
		}
		else
		{
			iClr2=BLUELIGHT_CLR; 
		}
		
		return;
	case  COL_GREEN: /* green */
	case 0x1f: /* green b1 */
	case 0x21: /* green b3 */
		iClr1=GREENLIGHT_CLR; 
		iClr2=BLACKLIGHT_CLR;
		return;
	case  COL_DG: /* double green */
		iClr1=iClr2=GREENLIGHT_CLR; return;
	case COL_GY: /* green yellow */
	case 0x27: /* green yellow b1 */
	case 0x29: /* green yellow b3 */
		iClr1=GREENLIGHT_CLR; iClr2=YELLOWLIGHT_CLR; return;
	case  COL_RED: /* red */
		iClr2=REDLIGHT_CLR;
		iClr1=BLACKLIGHT_CLR;
		return;
	case  COL_RW: /* red white */
		iClr2=REDLIGHT_CLR;
		iClr1=WHITELIGHT_CLR;
		return;
	case  COL_YELLOW: /* yellow */
	case 0x19: /* yellow b3 */
		iClr1=YELLOWLIGHT_CLR; 
		iClr2=BLACKLIGHT_CLR;
		return;
	case  COL_DY: /* double yellow */
		iClr1=iClr2=YELLOWLIGHT_CLR; return;
	case  COL_FB: /* filament broken */
		bFlash ? iClr2=REDLIGHT_CLR : iClr2=BLACKLIGHT_CLR;
		iClr1=BLACKLIGHT_CLR;
		return;
	case COL_WF: /* white flash */
		bFlash ? iClr1=WHITELIGHT_CLR : iClr1 = BLACKLIGHT_CLR; 
		iClr2=BLACKLIGHT_CLR;
		return;
	case COL_RF: /* red flash */
		bFlash ? iClr1=REDLIGHT_CLR : iClr1=BLACKLIGHT_CLR;
		iClr2=BLACKLIGHT_CLR;
		return;
	case COL_GF: /* green flash */
		bFlash ? iClr1=GREENLIGHT_CLR : iClr1=BLACKLIGHT_CLR;
		iClr2=BLACKLIGHT_CLR;
		return;
	case COL_YF: /* yellow flash */
		bFlash ? iClr1=YELLOWLIGHT_CLR : iClr1=BLACKLIGHT_CLR; 
		iClr2=BLACKLIGHT_CLR;
		return;
	case COL_YFY: /* yellow flash yellow */
		bFlash ? iClr1=YELLOWLIGHT_CLR : iClr1=BLACKLIGHT_CLR;
		iClr2=YELLOWLIGHT_CLR; return;
	default:
		iClr2=REDLIGHT_CLR;
		iClr1=BLACKLIGHT_CLR;
		return;
	}
}

void CXinHJ::ShowName(CDC *pDC,int iNameState)
{
	if(m_iType==XT_INVALID){return;}

	//
	CFont  font,*pOldFont;
	font.CreateFont(-14, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0,
	                    ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	                    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                    DEFAULT_PITCH | FF_SWISS, "Arial");
	pOldFont = pDC->SelectObject(&font);
	
	COLORREF iClr = (iNameState==NS_COMM) ? WHITECOLOR : BLACKCOLOR;

	pDC->SetTextColor(iClr);
	pDC->SetTextAlign(TA_LEFT);
	//pDC->SetBkColor(BLACKCOLOR);
	//iNameState==NS_HIDE ? pDC->SetBkMode(OPAQUE) : pDC->SetBkMode(TRANSPARENT);
	pDC->SetBkMode(TRANSPARENT);
	if(m_iDir==XD_RIGHT){
		pDC->TextOut(m_pt.x+m_iTx-2,m_pt.y+m_iTy-iRJ-4,m_strName);
	}
	else{
		pDC->TextOut(m_pt.x+m_iTx-14,m_pt.y+m_iTy-iRJ+2,m_strName);
	}
	pDC->SelectObject(pOldFont);
}

BOOL CXinHJ::GetFlashState()
{
	BOOL bResult = (m_iStatus==COL_WF);
	bResult |= (m_iStatus==COL_RF);
	bResult |= (m_iStatus==COL_GF);
	bResult |= (m_iStatus==COL_YF);
	bResult |= (m_iStatus==COL_YFY);
	bResult |= (m_iStatus==COL_FB);
	return bResult;
}
