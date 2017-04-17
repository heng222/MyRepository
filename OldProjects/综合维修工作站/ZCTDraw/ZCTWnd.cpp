// ZCTWnd.cpp : implementation file
//
#include "stdafx.h"
#include "ZCTWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//##################################################################################
//##################################################################################


//##################################################################################
//父窗口弹出菜单ID范围(0x8000 ~ 0xBFFF)-------------------------------------
#define ID_PTM_START	0x8000		//起始ID
#define ID_PTM_END		0xBFFF		//终止ID

//---------------------------------------------------------------------------
//站场图弹出菜单(自定义ID范围0xc000 ~ 0xc050)
#define ID_PM_START			0xc000		//
#define ID_PM_END			0xc050		//

//显示方式(0xa000 ~ 0xa010)
#define ID_SHOW_START		ID_PM_START
#define ID_SHOW_DAOCHANAME	0xc000		//道岔按钮名称
#define ID_SHOW_WUCHAQNAME	0xc001		//无岔区段名称
#define ID_SHOW_XINHAONAME	0xc002		//信号机名称
#define ID_SHOW_FRAMENO		0xc003		//车次框
#define ID_SHOW_PMHANZI		0xc004		//屏幕汉字
#define ID_SHOW_BSHIDENG	0Xc005		//表示灯
#define ID_SHOW_GDLIGHT		0xc006		//股道封锁灯
#define ID_SHOW_QJLIGHT		0xc007		//区间封锁灯
#define ID_SHOW_BTNNAME		0xc008		//调车、列车按钮名称
#define ID_SHOW_END			0xc010

//映射模式ID(0xa011 ~ 0xa019)
#define ID_MM_START			(ID_SHOW_END+1)
#define ID_MM_TEXT			ID_MM_START	//实际尺寸
#define ID_MM_ANISOTROPIC	0xc012		//理想尺寸
#define ID_MM_ISOTROPIC		0xc013		//自由缩放
#define ID_MM_END			0xc019
//
#define MAXZOOMIN		3			//可放大的最大倍数
#define STEPZOOM		(1/4.0)		//缩放基本单位
#define MAXZOOMOUT		(1/5.0)		//可缩小的最大倍数
//
#define ID_SK_START			(ID_MM_END+1)
#define ID_SK_ZOOMOUT		ID_SK_START		//缩小站场图
#define ID_SK_ZOOMIN		0xc01B			//放大站场图
#define ID_SK_END			0xc020
//##################################################################################

//##################################################################################
//站场图显示所用数据名称(当前目录在\ini\StationInf.ini中定义)
#define FILENAME_OFFSET		"offset.dat"	//
#define FILENAME_SYARD		"yard.dat"		//
#define FILENAME_MYARD		"yard_M.dat"	//
#define FILENAME_MASK		"mask.ini"		//
#define FILENAME_SFRAME		"frame.dat"		//
#define FILENAME_MFRAME		"frame_M.dat"	//
#define FILENAME_GUDAO		"gd.dat"		//
#define FILENAME_DESK		"desk.dat"		//	
#define FILENAME_JINLU		"jl.ini"		//	
//##################################################################################

// CZCTWnd
IMPLEMENT_DYNCREATE(CZCTWnd, CWnd)

CZCTWnd::CZCTWnd():m_hPMHandle(NULL),m_pTempDevice(NULL),m_sLogicalCanvas(1280,1024),
	m_dwShowStyle(0xFFFFFFFF),	m_wOperatorAttr(OPER_FUNCTNBTN),
	m_nMapMode(MM_ANISOTROPIC),	m_bSingle(TRUE),m_sizeShrink(1,1),
	m_iStationNo(0),m_sizeExcursion(0,0),m_iMouseFlag(MSFL_INVALID),
	m_pFuncBtnLast(NULL),m_pFuncBtnActive(NULL),m_hMsgHandle(NULL),
	m_pReferenceWnd(NULL),m_pCanvasWnd(NULL),m_fStationShrink(1.0),
#ifdef _DEBUG
	m_bInfIvlid(FALSE)
#else
	m_bInfIvlid(TRUE)
#endif
	
{
	//
	m_strPassword[0] = "123";
	m_strPassword[1] = "456";
	
	//
	m_InterlockJuge.SetInf(this);

	//确定系统当前路径
//	char cTemp[MAX_PATH];
//	GetCurrentDirectory(MAX_PATH,cTemp);
//	m_strCurWorkDirec.Format("%s\\",cTemp);
}

CZCTWnd::~CZCTWnd()
{
	DeleteObject();
}

BEGIN_MESSAGE_MAP(CZCTWnd, CWnd)
	//{{AFX_MSG_MAP(CZCTWnd)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_SETCURSOR()
	ON_WM_CONTEXTMENU()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_LBTNDOWN_ONFRAME,OnMsgFromFrameNo)
	ON_COMMAND_RANGE(ID_PM_START, ID_PM_END, OnPopMenu)
	ON_UPDATE_COMMAND_UI_RANGE(ID_PM_START,ID_PM_END,OnUpdateDeviceName)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZCTWnd diagnostics

#ifdef _DEBUG
void CZCTWnd::AssertValid() const
{
	CWnd::AssertValid();
}

void CZCTWnd::Dump(CDumpContext& dc) const
{
	CWnd::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CZCTWnd message handlers

BOOL CZCTWnd::ReadDesk(CString strFileName)
{
	FILE *fp = fopen(strFileName,"r");
	if (fp == NULL)	{
		TRACE("Can not open the file: %s !\n",strFileName);
		return FALSE;
	}

	//
	char strLine[256];
	int iFuncBtnNums,iTempData;
	fgetline(strLine,256,fp);
	sscanf(strLine,"%d",&iFuncBtnNums );
	
	for(int i=0;i<iFuncBtnNums;i++)
	{
		CFuncBtn *pBtn=new CFuncBtn;
		//
		pBtn->m_Index = i+1;
		
		//
		
		fgetline(strLine,256,fp);
	    sscanf(strLine,"%d %d %x %d %x %d %d %d %s",
			&pBtn->m_pt .x,&pBtn->m_pt .y,&pBtn->m_iType ,
			&pBtn->m_iCommandID ,&pBtn->m_iOffset ,/*&pBtn->m_iClr0*/ &iTempData,
			/*&pBtn->m_iClr1*/&iTempData ,/*&pBtn->m_iFlash*/&iTempData,pBtn->m_strName.GetBuffer(50)
			);
		pBtn->m_strName.ReleaseBuffer();
		//	
		m_FuncBtnList.AddTail(pBtn);
	}
	fclose(fp);

	return TRUE;
}

BOOL CZCTWnd::ReadGd(CString strFileName)
{
	FILE *fp = fopen(strFileName,"r");
	if (fp==NULL)	{
		return FALSE;
	}

	//读股道封锁灯数据
	int i,iGdStatusNums;
	char strLine[256];
	fgetline(strLine,256,fp);
	sscanf(strLine,"%d",&iGdStatusNums );

	for(i=0;i<iGdStatusNums;i++){
		CGdStatus *pBtn=new CGdStatus;
		pBtn->m_strName .Empty();
		fgetline(strLine,256,fp);
	    sscanf(strLine,"%d %d %d %10s",
			&pBtn->m_pt .x,&pBtn->m_pt .y,
			&pBtn->m_iCommandID ,
			pBtn->m_strName .GetBuffer(30)
			);
		pBtn->m_strName .ReleaseBuffer();

		//
		m_GdStatusList.AddTail(pBtn);
	}

	//读区间封锁灯数据
	fgetline(strLine,256,fp);
	int iQjStatusNums;
	sscanf(strLine,"%d",&iQjStatusNums );
	
	for(i=0;i<iQjStatusNums;i++)
	{
		CQjStatus *pBtn=new CQjStatus;
		pBtn->m_strName .Empty();
		fgetline(strLine,256,fp);
	    sscanf(strLine,"%d %d %d %d %d %d %d %d %10s",
			&pBtn->m_pt .x,&pBtn->m_pt .y,&pBtn->m_iCommandID ,
			&pBtn->m_iStationNo1 ,&pBtn->m_iXHNo1 ,
			&pBtn->m_iStationNo2 ,&pBtn->m_iXHNo2,&pBtn->m_iCommandID2,pBtn->m_strName .GetBuffer(30));
		pBtn->m_strName .ReleaseBuffer();

		//
		m_QjStatusList.AddTail(pBtn);
	}

	fclose(fp);

	return TRUE;
}

BOOL CZCTWnd::ReadOffset(CString strFileName)
{
	FILE *fp = fopen(strFileName,"r");
	if (fp==NULL){
		return FALSE;
	}

	//
	char strLine[256];	
	fgetline(strLine,256,fp);
	sscanf(strLine,"%d %d %d %d",
		&m_sizeExcursion.cx,&m_sizeExcursion.cy,
		&m_sizeShrink.cx,&m_sizeShrink.cy
		);

	fclose(fp);
	return TRUE;
}

BOOL CZCTWnd::ReadYard(CString strFileName)
{
	FILE *fp;
	if ( (fp=fopen(strFileName,"r")) == NULL){
		TRACE("Can not open %s!\n",strFileName);
		return FALSE;
	}
	
	//Start Read the station Information
	char strLine[256];
	int i;int iTempData;
	
	//Read Password
	fgetline(strLine,256,fp);

	//Read <Xscale, Yscale>
	float fYscale,fXscale;
	fgetline(strLine,256,fp);
	sscanf(strLine,"%d %d",&fXscale,&fYscale);


	float fDefaultSlope;
    if(fXscale==0) fDefaultSlope=(float)3.4;  // max float number
	else fDefaultSlope=(float)fabs(fYscale/fXscale);
	
	float SinAlpha=(float)sin(atan(fDefaultSlope)/2);
	float CosAlpha=(float)cos(atan(fDefaultSlope)/2);
	

	//读道岔
	fgetline(strLine,256,fp);
	int iDCNums;
	sscanf(strLine,"%d",&iDCNums);
	for( i=0;i<iDCNums;i++)
	{
		CDaoC *pDaoC=new CDaoC;
		
		pDaoC->SinAlpha=SinAlpha;
	    pDaoC->CosAlpha=CosAlpha;
		pDaoC->fSlope =fDefaultSlope;

		fgetline(strLine,256,fp);
		sscanf(strLine,"%d %d %d %d %d %d %d %d %d %d %d %d %x %s",
			&pDaoC->m_pt.x,&pDaoC->m_pt.y,&pDaoC->m_deltaA.x,&pDaoC->m_deltaA.y,
			&pDaoC->m_deltaB.x,&pDaoC->m_deltaB.y,
			&pDaoC->m_deltaC.x,&pDaoC->m_deltaC.y,
			&pDaoC->m_iIndex,&pDaoC->m_iALink,&pDaoC->m_iBLink,&pDaoC->m_iCLink,
			&pDaoC->m_iType,pDaoC->m_strName.GetBuffer(30)	);
		pDaoC->m_strName.ReleaseBuffer();

		/*
		#ifdef _DEBUG
			if ( pDaoC->m_iIndex == 14){
				pDaoC->m_iDir = 0x03;
			}
		#endif
		//*/
		
		//大屏时信号机要进行缩放
		pDaoC->bZoom = !m_bSingle;
		
		//
		pDaoC->m_pt.x=pDaoC->m_pt.x/m_sizeShrink.cx+m_sizeExcursion.cx;
		pDaoC->m_pt.y=pDaoC->m_pt.y/m_sizeShrink.cy+m_sizeExcursion.cy;
		pDaoC->m_deltaA.x=pDaoC->m_deltaA.x/m_sizeShrink.cx;
		pDaoC->m_deltaA.y=pDaoC->m_deltaA.y/m_sizeShrink.cy;
		pDaoC->m_deltaB.x=pDaoC->m_deltaB.x/m_sizeShrink.cx;
		pDaoC->m_deltaB.y=pDaoC->m_deltaB.y/m_sizeShrink.cy;
		pDaoC->m_deltaC.x=pDaoC->m_deltaC.x/m_sizeShrink.cx;
		pDaoC->m_deltaC.y=pDaoC->m_deltaC.y/m_sizeShrink.cy;
		
		//
		m_DCList.AddTail(pDaoC);
	}

	//读信号机
	fgetline(strLine,256,fp);
	int iXHNums;
	sscanf(strLine,"%d",&iXHNums);

	LXNums=0;//重新初始化
	DXNums=0;
	for(i=0;i<iXHNums;i++)
	{
		CXinHJ *pXHJ=new CXinHJ();

		fgetline(strLine,256,fp);
		sscanf(strLine,
			"%d %d %d %d %d %d %d %d %d %d %d %s",
			&pXHJ->m_pt.x,&pXHJ->m_pt.y,&pXHJ->m_iDir,
			&pXHJ->m_iType ,&pXHJ->m_bHigh,&pXHJ->m_iForBidClr ,
			&pXHJ->m_iLXIndex ,&pXHJ->m_iDXIndex,&iTempData,
			&pXHJ->m_iTx ,&pXHJ->m_iTy ,pXHJ->m_strName.GetBuffer(40));
		pXHJ->m_strName.ReleaseBuffer();
		
		//
		pXHJ->m_pt.x=pXHJ->m_pt.x/m_sizeShrink.cx+m_sizeExcursion.cx;
		pXHJ->m_pt.y=pXHJ->m_pt.y/m_sizeShrink.cy+m_sizeExcursion.cy;
		pXHJ->m_iTx=pXHJ->m_iTx/m_sizeShrink.cx;
		pXHJ->m_iTy=pXHJ->m_iTy/m_sizeShrink.cy;

        if(!m_bSingle)	{
			pXHJ->bZoom =TRUE;
		}

		if(pXHJ->m_iLXIndex!=0  ){
			LXNums++;
		}
        if(pXHJ->m_iDXIndex !=0){
			DXNums++;
		}

/*		
#ifdef _DEBUG
			if (pXHJ->m_iLXIndex == 1) {
				pXHJ->m_iStatus = COL_RF;
			}
			else if(pXHJ->m_iLXIndex == 2){
				pXHJ->m_iStatus = COL_WF;
			}
			else if(pXHJ->m_iLXIndex == 3){
				pXHJ->m_iStatus = COL_GF;
			}
			else if(pXHJ->m_iLXIndex == 4){
				pXHJ->m_iStatus = COL_YF;
			}
			else if(pXHJ->m_iLXIndex == 5){
				pXHJ->m_iStatus = COL_YFY;
			}
			else if(pXHJ->m_iLXIndex == 6){
				pXHJ->m_iStatus = COL_FB;
			}
#endif
//*/
			
		m_XHJList.AddTail(pXHJ);
	}

	// WuDianLu_QuDuan
	fgetline(strLine,256,fp);
	int iNQDNums;
	sscanf(strLine,"%d",&iNQDNums);
	for(i=0;i<iNQDNums;i++)
	{
		CNQD *pNQD=new CNQD;
		fgetline(strLine,256,fp);
		sscanf(strLine,"%d %d %d %d",
			&pNQD->m_pt1.x,&pNQD->m_pt1.y,&pNQD->m_pt2.x,&pNQD->m_pt2.y);

		//
		pNQD->m_pt1.x=pNQD->m_pt1.x/m_sizeShrink.cx+m_sizeExcursion.cx;
		pNQD->m_pt1.y=pNQD->m_pt1.y/m_sizeShrink.cy+m_sizeExcursion.cy;
		pNQD->m_pt2.x=pNQD->m_pt2.x/m_sizeShrink.cx+m_sizeExcursion.cx;
		pNQD->m_pt2.y=pNQD->m_pt2.y/m_sizeShrink.cy+m_sizeExcursion.cy;
		
		//
		m_NQDList.AddTail(pNQD);
	}

	// 无岔区段
	fgetline(strLine,256,fp);
	int iWCQDNums;
	sscanf(strLine,"%d",&iWCQDNums);
	for(i=0;i<iWCQDNums;i++)
	{
		CWcQD *pWcQD=new CWcQD;

		fgetline(strLine,256,fp);
		sscanf(	strLine,

			#ifdef PDSYS
			"%d %d %d %d %d %d %d %d %d %d %d %s",
			#else
			"%d %d %d %d %d %d %d %d %d %d %s",
			#endif

			&pWcQD->m_pt1.x,&pWcQD->m_pt1.y,&pWcQD->m_pt2.x,&pWcQD->m_pt2.y,
			&pWcQD->m_iIndex,&pWcQD->m_pt.x,&pWcQD->m_pt.y,
			/*&pWcQD->m_bHidAble*/&iTempData,&pWcQD->m_bCanQGJ,

			#ifdef PDSYS
			&pWcQD->m_bCanPlQGJ,
			#endif
			
		    &pWcQD->m_iCommandID,pWcQD->m_strName.GetBuffer(40)
			);

		pWcQD->m_strName.ReleaseBuffer();

		//		
		pWcQD->m_pt1.x=pWcQD->m_pt1.x/m_sizeShrink.cx+m_sizeExcursion.cx;
		pWcQD->m_pt1.y=pWcQD->m_pt1.y/m_sizeShrink.cy+m_sizeExcursion.cy;
		pWcQD->m_pt2.x=pWcQD->m_pt2.x/m_sizeShrink.cx+m_sizeExcursion.cx;
		pWcQD->m_pt2.y=pWcQD->m_pt2.y/m_sizeShrink.cy+m_sizeExcursion.cy;
		pWcQD->m_pt.x=pWcQD->m_pt.x/m_sizeShrink.cx+m_sizeExcursion.cx;
		pWcQD->m_pt.y=pWcQD->m_pt.y/m_sizeShrink.cy+m_sizeExcursion.cy;
		
		//
		m_WcQDList.AddTail(pWcQD);
	}
	int iii = GetWcQdValidNums();
	//读绝缘结
	int iJYJNums;
	fgetline(strLine,256,fp);
	sscanf(strLine,"%d",&iJYJNums);

	for(i=0;i<iJYJNums;i++)	{
		CJYJ *pJYJ=new CJYJ;
		fgetline(strLine,256,fp);
		sscanf(strLine,"%d %d %d %d %d %d %d",
			&pJYJ->m_iType,&pJYJ->m_pt.x,&pJYJ->m_pt.y,
			&pJYJ->m_pt1.x,&pJYJ->m_pt1.y,&pJYJ->m_pt2.x,&pJYJ->m_pt2.y);

		//
		pJYJ->m_pt.x=pJYJ->m_pt.x/m_sizeShrink.cx+m_sizeExcursion.cx;
		pJYJ->m_pt.y=pJYJ->m_pt.y/m_sizeShrink.cy+m_sizeExcursion.cy;
		pJYJ->m_pt1.x=pJYJ->m_pt1.x/m_sizeShrink.cx+m_sizeExcursion.cx;
		pJYJ->m_pt1.y=pJYJ->m_pt1.y/m_sizeShrink.cy+m_sizeExcursion.cy;
		pJYJ->m_pt2.x=pJYJ->m_pt2.x/m_sizeShrink.cx+m_sizeExcursion.cx;
		pJYJ->m_pt2.y=pJYJ->m_pt2.y/m_sizeShrink.cy+m_sizeExcursion.cy;
		
		//
		m_JYJList.AddTail(pJYJ);
	}

	//读尽头线数据
	fgetline(strLine,256,fp);
	int iJTNums;
	sscanf(strLine,"%d",&iJTNums);
	
	for(i=0;i<iJTNums;i++){
		CJT *pJT=new CJT;
		fgetline(strLine,256,fp);
		sscanf(strLine,"%d %d %d %d",
			&pJT->m_pt.x,&pJT->m_pt.y,&pJT->m_iType,&pJT->m_iDir);

		//
		pJT->m_pt.x=pJT->m_pt.x/m_sizeShrink.cx+m_sizeExcursion.cx;
		pJT->m_pt.y=pJT->m_pt.y/m_sizeShrink.cy+m_sizeExcursion.cy;
		
		//
		m_JTList.AddTail(pJT);
	}


	//读屏幕汉字
	int iHZNums;
	fgetline(strLine,256,fp);
	sscanf(strLine,"%d",&iHZNums);
	for(i=0;i<iHZNums;i++)
	{
		CHanZ *pHZ=new CHanZ;
		fgetline(strLine,256,fp);
		sscanf(strLine,"%d %d %d %s",
			&pHZ->m_pt.x,&pHZ->m_pt.y,&pHZ->m_bHidAble,
			pHZ->m_strText.GetBuffer(50)
			);

		pHZ->m_strText.ReleaseBuffer();

		//
		pHZ->m_pt.x=pHZ->m_pt.x/m_sizeShrink.cx+m_sizeExcursion.cx;
		pHZ->m_pt.y=pHZ->m_pt.y/m_sizeShrink.cy+m_sizeExcursion.cy;
		
		//
		m_HZList.AddTail(pHZ);
	}

	//读按钮数据
	int iDCDevOffset;
	fgetline(strLine,256,fp);
	sscanf(strLine,"%d",&iDCDevOffset);
	fgetline(strLine,256,fp);
	int iBtnNums;
	sscanf(strLine,"%d",&iBtnNums);

	for(i=0;i<iBtnNums;i++)	{
		CAnN *pAN=new CAnN;
		fgetline(strLine,256,fp);
		sscanf(strLine,"%d %d %x %d %u %u %d %d %d %d %s",
			&pAN->m_pt.x,&pAN->m_pt.y,&pAN->m_iType,&pAN->m_iCommandID,
			&pAN->m_iRelate1,&pAN->m_iRelate2,&pAN->m_deltaX,
			&pAN->m_deltaY,&pAN->m_bShow,&pAN->m_bHidAble,pAN->m_strName.GetBuffer(40)
			);
		pAN->m_strName.ReleaseBuffer();
    	
		//
		pAN->m_pt.x=pAN->m_pt.x/m_sizeShrink.cx+m_sizeExcursion.cx;
		pAN->m_pt.y=pAN->m_pt.y/m_sizeShrink.cy+m_sizeExcursion.cy;
		
		
		
/*
#ifdef _DEBUG
		if ( pAN->m_iRelate1 == 14 || pAN->m_iRelate2 == 14)
		{
			pAN->m_byDCStatus = 3;
		}
#endif
//*/
		
		m_ANList.AddTail(pAN);
	}
	

	//道岔按钮
	int iDCANNums;
	fgetline(strLine,256,fp);
	sscanf(strLine,"%d",&iDCANNums);

	for(i=0;i<iDCANNums;i++){
		CDCAN *pDCAN=new CDCAN;
		fgetline(strLine,256,fp);
		sscanf(strLine,	"%d %d %s %d %d %s",
			&pDCAN->m_pt.x,&pDCAN->m_pt.y,pDCAN->m_DCText,
			&pDCAN->m_QD_Index,
			&pDCAN->m_iCommandID,pDCAN->m_QDName);
		//		
		pDCAN->m_pt.x=pDCAN->m_pt.x/m_sizeShrink.cx+m_sizeExcursion.cx;
		pDCAN->m_pt.y=pDCAN->m_pt.y/m_sizeShrink.cy+m_sizeExcursion.cy;
	
		//
		m_DCANList.AddTail(pDCAN);
	}	

	//Fang Hu DaoCha
	int iFHDC;
	fgetline(strLine,256,fp);
	fgetline(strLine,256,fp);
	sscanf(strLine,"%d",&iFHDC);
	for(i=0;i<iFHDC;i++)
		fgetline(strLine,256,fp);
	
	// DCQDMAP	    
	fgetline(strLine,256,fp);
	sscanf(strLine,"%d",&iDCQDMaps);

	for(i=0;i<iDCQDMaps;i++){
		fgetline(strLine,256,fp);
		sscanf(strLine,"%d %d",&DCQDMap[i].QD_INDEX,&DCQDMap[i].iPrDC);
	}
	
	// JiaoChaHuanWei
	fgetline(strLine,256,fp);
	sscanf(strLine,"%d",&iJCHWNums );
	
	for(i=0;i<iJCHWNums;i++){
		fgetline(strLine,256,fp);
		sscanf(strLine,"%d %d %d %d",&JCHW[i].dc1,&JCHW[i].DWZG1,&JCHW[i].dc2,&JCHW[i].DWZG2);

	}

	// BiaoShiDeng
	int iBSDNums;
	fgetline(strLine,256,fp);
	sscanf(strLine,"%d",&iBSDNums);

	for(i=0;i<iBSDNums;i++)	{
		CBSD *pBSD=new CBSD;
		//
		pBSD->m_wBSDNo = i+1;
		fgetline(strLine,256,fp);
		sscanf(strLine,"%d %d %d %d %d %d %d %d %20s",&pBSD->m_iType,
			&pBSD->m_pt.x,&pBSD->m_pt.y,&pBSD->m_iDir,&pBSD->m_iIndex,
			&pBSD->m_T_pt.x,&pBSD->m_T_pt.y,&pBSD->m_bHidAble,pBSD->m_strName.GetBuffer(40));
		pBSD->m_strName.ReleaseBuffer();

		//
		pBSD->m_pt.x=pBSD->m_pt.x/m_sizeShrink.cx+m_sizeExcursion.cx;
		pBSD->m_pt.y=pBSD->m_pt.y/m_sizeShrink.cy+m_sizeExcursion.cy;
		pBSD->m_T_pt.x=pBSD->m_T_pt.x/m_sizeShrink.cx+m_sizeExcursion.cx;
		pBSD->m_T_pt.y=pBSD->m_T_pt.y/m_sizeShrink.cy+m_sizeExcursion.cy;
		
		//
		m_BSDList.AddTail(pBSD);
	}

	//
	fclose(fp);
		
	return TRUE;
}

BOOL CZCTWnd::Create(CWnd *pReferWnd,CWnd*pCanvasWnd,HWND hMsgHandle)
{
	m_hMsgHandle = hMsgHandle;

	//
	ASSERT( pReferWnd != NULL );
	m_pReferenceWnd = pReferWnd;

	//
	if (m_bSingle){
		if (!CWnd::Create(NULL,"",WS_CHILD,
				CRect(0,0,m_sLogicalCanvas.cx,m_sLogicalCanvas.cy),
				pReferWnd,m_iStationNo+5000)) {
			return FALSE;
		} 
		//
		m_pCanvasWnd = this;
	}
	else{
		if (!CWnd::Create(NULL,"",WS_CHILD,
				CRect(0,0,5,5),pCanvasWnd,m_iStationNo+5100)) {
			return FALSE;
		}
		
		//
		m_pCanvasWnd = pCanvasWnd;

		//Start the timer
		SetTimer(ID_CLOCK_BTNFLASH,TIMERBTNFSHELAPSE,NULL);
	}

	//Create the  Frames that show the train's number.
	//Set the parent window .
	//车次框的父窗口为站场图的画布窗口
	if ( !m_FrameTrainNoList.CreateFrames(m_pCanvasWnd) ) {
		return FALSE;
	}
	
	return TRUE;
}

void CZCTWnd::DrawZCT(CDC* pDC/* = NULL*/)
{
	if ( GetSafeHwnd() == NULL ){
		return;
	}

	//
	//CClientDC dc(m_pCanvasWnd);
	CWindowDC dc(m_pCanvasWnd);
	if ( pDC == NULL )
	{
		pDC = &dc;
		SetDeviceContext(pDC);
	}

	// 画道岔名称
	POSITION pos=m_DCANList.GetHeadPosition();
	while(pos)
	{
		CDCAN *pDCAN = m_DCANList.GetNext(pos);
		//若正在进行区故解操作
		if ( m_pFuncBtnActive && m_pFuncBtnActive->m_iCommandID == CFuncBtn::QGJ){
			//pDCAN->DrawDCAN(pDC,TRUE,TRUE);
			pDCAN->ShowName(pDC,NS_QGJ);
		}
		else{
			//pDCAN->DrawDCAN(pDC,m_dwShowStyle & SHOW_DCNAME,FALSE);
			pDCAN->ShowName(pDC,m_dwShowStyle&SHOW_DCNAME ? NS_COMM : NS_HIDE);
		}			
	}

	// 画信号机
	pos=m_XHJList.GetHeadPosition();
	while(pos)	{
		CXinHJ *pXHJ=(CXinHJ *)m_XHJList.GetNext(pos);
		
		//画信号机名称
		pXHJ->ShowName (pDC,m_dwShowStyle & SHOW_XHJNAME ? NS_COMM : NS_HIDE);
		//
		//pXHJ->DrawXHJ(pDC/*,FALSE*/);
		pXHJ->DrawSlf(pDC,m_bInfIvlid?DS_INVALID:DS_COMM);
	}

	// 画道岔
	pos = m_DCList.GetHeadPosition();
	while(pos)	{
		CDaoC *pDaoC=(CDaoC *)m_DCList.GetNext(pos);
		//if (m_iStationNo == 4) {
			//pDaoC->DrawDC(pDC,m_bInfIvlid);
		//}
		pDaoC->DrawSlf(pDC,m_bInfIvlid?DS_INVALID:DS_COMM);
		
	}
	
	//无电路区段
	pos=m_NQDList .GetHeadPosition();
	while(pos)	{
		CNQD *pNQD=(CNQD *)m_NQDList.GetNext(pos);
		pNQD->DrawSlf(pDC,m_bInfIvlid?NS_INVALID:NS_COMM);
	}


	//画无岔区段
	pos=m_WcQDList .GetHeadPosition();
	while(pos!=NULL)
	{
		CWcQD *pWcQD=(CWcQD *)m_WcQDList.GetNext(pos);

		BOOL bFlag = FALSE;
		if ( m_pFuncBtnActive){	//若正在区故解
			if ( m_pFuncBtnActive->m_iCommandID == CFuncBtn::QGJ){
				bFlag = TRUE;
				pWcQD->ShowName(pDC,NS_QGJ);
			}
		}
		else{
			pWcQD->ShowName (pDC,m_dwShowStyle&SHOW_WCQDNAME?NS_COMM:NS_HIDE);
		}
		pWcQD->DrawSlf(pDC,m_bInfIvlid?DS_INVALID:DS_COMM);
	}
	
	
	//画尽头线
	pos=m_JTList.GetHeadPosition();
	while(pos)	{
		CJT *pJT = m_JTList.GetNext(pos);
		pJT->DrawSlf(pDC,m_bInfIvlid?NS_INVALID:NS_COMM);
	}
	

	// 画屏幕汉字
	pos=m_HZList.GetHeadPosition();
	while(pos)	{
		CHanZ *pHZ = m_HZList.GetNext(pos);
		pHZ->DrawHZ(pDC,m_bInfIvlid,!m_bSingle,m_dwShowStyle & SHOW_PMHANZI);
	}

	
	// 画按钮
	pos=m_ANList.GetHeadPosition();
	while(pos)
	{
		CAnN *pAN = m_ANList.GetNext(pos);
		BOOL bFlag;
		if (pAN->m_iType==CAnN::BTN_TYPE_DA) {
			bFlag = (m_dwShowStyle & SHOW_DIAOCHEAN);
		}
		else if (pAN->m_iType==CAnN::BTN_TYPE_LA) {
			bFlag = (m_dwShowStyle & SHOW_LIECHEBTN);
		}
		else if (pAN->m_iType==CAnN::BTN_TYPE_CA) {
			bFlag = m_dwShowStyle & SHOW_DAOCHAAN;
		}
		else if (pAN->m_iType==CAnN::BTN_TYPE_YA) {
			bFlag = m_dwShowStyle & SHOW_LIECHEBTN;
		}
		else{
			bFlag = m_dwShowStyle & SHOW_OTHERBTN;
		}

		if ( bFlag ){//可操作列车按钮时，显示所有按钮
			pAN->DrawSlf(pDC,m_bInfIvlid ? DS_INVALID : DS_COMM );
			pAN->ShowName(pDC,m_dwShowStyle&SHOW_ANNAME ? NS_COMM : NS_HIDE);
		}
	}


	//画表示灯
	if ( m_dwShowStyle & SHOW_BSHIDENG )
	{
		pos=m_BSDList.GetHeadPosition();
		while(pos)
		{
			CBSD *pBSD = m_BSDList.GetNext(pos);
			pBSD->DrawSlf(pDC,m_bInfIvlid ? DS_INVALID : DS_COMM);
		}
	}

	//画桌面上的功能按钮
	if ( m_dwShowStyle & SHOW_GNENGAN)
	{
		pos=m_FuncBtnList.GetHeadPosition();
		while(pos!=NULL)
		{
			CFuncBtn *pFuncBtn = m_FuncBtnList.GetNext(pos);
			pFuncBtn->DrawSlf(pDC,DS_COMM);
		}
	}


	//画绝缘结
	pos=m_JYJList.GetHeadPosition();
	while(pos)
	{
		CJYJ *pJYJ = m_JYJList.GetNext(pos);
		pJYJ->DrawSlf(pDC,m_bInfIvlid?NS_INVALID:NS_COMM);
	}
	

	//画股道状态灯
	if ( m_dwShowStyle & SHOW_GDLIGHT )
	{
		pos=m_GdStatusList.GetHeadPosition();
		while(pos)
		{
			CGdStatus *pGdStatus = m_GdStatusList.GetNext(pos);
			pGdStatus->DrawSlf(pDC,m_bInfIvlid?DS_INVALID:DS_COMM);
		}
	}
	
	
	//画区间状态灯
	if ( m_dwShowStyle & SHOW_QJLIGHT )
	{
		pos=m_QjStatusList.GetHeadPosition();
		while(pos)
		{
			CQjStatus *pQjStatus = m_QjStatusList.GetNext(pos);
			pQjStatus->DrawSlf(pDC,m_bInfIvlid?DS_INVALID:DS_COMM);
		}
	}

	//画车次框
	if (m_dwShowStyle & SHOW_FRAMENO) {
		m_FrameTrainNoList.ShowFrames(pDC,SW_SHOW);
	}
	else{
		m_FrameTrainNoList.ShowFrames(pDC,SW_HIDE);
	}
	
}

//更新站场状态
void CZCTWnd::UpdateZCT (int iFrameType,CDC* pDC /*= NULL*/)
{
	if ( GetSafeHwnd() == NULL ){
		return;
	}

	//
	CClientDC dc(m_pCanvasWnd);
	if ( pDC == NULL )
	{
		pDC = &dc;
		SetDeviceContext(pDC);
	}

	//
 	POSITION pos;
    
	//变化帧或全场帧
	if ( iFrameType == STATIONINFO_FRAME_TYPE || 
		iFrameType == STATIONCHANGE_FRAME_TYPE)
	{
		//重画道岔
		pos=m_DCList.GetHeadPosition();
		while(pos)
		{
			CDaoC *pDaoC=(CDaoC *)m_DCList.GetNext(pos);
			//pDaoC->RefreshDC (pDC,FALSE);		
			pDaoC->DrawSlf(pDC,DS_COMM);
		}
		
		
		//重画信号机
		pos=m_XHJList.GetHeadPosition();
		while(pos)
		{
			CXinHJ *pXHJ=(CXinHJ *)m_XHJList.GetNext(pos);
			pXHJ->DrawSlf(pDC,DS_COMM);
		}
		
		
		//重画无岔区段
		pos=m_WcQDList .GetHeadPosition();
		while(pos)
		{
			CWcQD *pWcQD=(CWcQD *)m_WcQDList.GetNext(pos);
			pWcQD->DrawSlf(pDC,DS_COMM);
		}
		
		
		//重画表示灯
		if ( m_dwShowStyle & SHOW_BSHIDENG)
		{
			pos=m_BSDList.GetHeadPosition();
			while(pos)
			{
				CBSD *pBSD=(CBSD *)m_BSDList.GetNext(pos);
				pBSD->DrawSlf(pDC,DS_COMM);
			}
		}
		
		//重画道岔按钮
		if ( m_dwShowStyle & SHOW_DAOCHAAN )
		{			
			pos=m_ANList.GetHeadPosition();
			while(pos)
			{
				CAnN *pAN = m_ANList.GetNext(pos);
				if (pAN->m_iType==CAnN::BTN_TYPE_CA)
				{
					pAN->DrawSlf(pDC,DS_COMM);
					pAN->ShowName(pDC,NS_COMM);
				}
			}
		}
		
		//重画被擦除的绝缘结	
		pos=m_JYJList.GetHeadPosition();
		while(pos!=NULL)
		{
			CJYJ *pJYJ = m_JYJList.GetNext(pos);
			pJYJ->DrawSlf(pDC,NS_COMM);
		}

		//重画桌面上的功能按钮
		if ( m_dwShowStyle & SHOW_GNENGAN)
		{
			pos=m_FuncBtnList.GetHeadPosition();
			while(pos!=NULL){
				CFuncBtn *pFuncBtn = m_FuncBtnList.GetNext(pos);
				if (pFuncBtn->m_iCommandID == CFuncBtn::SYZS ||
					pFuncBtn->m_iCommandID == CFuncBtn::XYZS) {
					pFuncBtn->DrawSlf (pDC,DS_COMM);
				}
			}
		}
	}

	//股道状态帧
	else if (iFrameType == GUDAOLOCK_FRAME_TYPE ||
		iFrameType == GUDAOALLLOCK_FRAME_TYPE)
	{
		//画股道状态灯
		if ( m_dwShowStyle & SHOW_GDLIGHT )
		{
			pos=m_GdStatusList.GetHeadPosition();
			while(pos!=NULL)
			{
				CGdStatus *pGdStatus = m_GdStatusList.GetNext(pos);
				pGdStatus->DrawSlf(pDC,DS_COMM);
			}
		}
	}

	//区间状态帧
	else if ( iFrameType == QUJIANLOCK_FRAME_TYPE || 
		iFrameType == QUJIANALLLOCK_FRAME_TYPE)
	{
		//画区间状态灯
		if ( m_dwShowStyle & SHOW_QJLIGHT )
		{
			pos=m_QjStatusList.GetHeadPosition();
			while(pos!=NULL)
			{
				CQjStatus *pQjStatus = m_QjStatusList.GetNext(pos);
				pQjStatus->DrawSlf(pDC,DS_COMM);
			}
		}
	}

}

DWORD CZCTWnd::SetZCTStyle(DWORD dwNewStyle,BOOL bRedraw/* = TRUE*/)
{
	DWORD _dwOldStyle = m_dwShowStyle;
	m_dwShowStyle = dwNewStyle;

	//
	if ( bRedraw )
	{
		//m_bSingle ? Invalidate() : m_pCanvasWnd->Invalidate();
		m_pCanvasWnd->Invalidate();
	}
	
	return _dwOldStyle;
	
}
int CZCTWnd::SetZCTMapMode( int nNewMapMode)
{
	int oldMapMode = m_nMapMode;
	m_nMapMode = nNewMapMode;
	return oldMapMode;
}

WORD CZCTWnd::SetOperAttri(WORD wNewAttri)
{
	WORD wOldAttri = m_wOperatorAttr;
	m_wOperatorAttr = wNewAttri;
	return wOldAttri;
}

void CZCTWnd::PrintZCT(CPoint ptOrigin,CSize SizeZoom)
{
	CClientDC dc(this);
	CDC* pDC = &dc;
	int iOldMode=pDC->SetMapMode(MM_ANISOTROPIC);  //转换坐标映射方式
	CSize size(m_sLogicalCanvas);
	pDC->SetWindowExt(size);  //确定窗口大小

	//得到实际设备每逻辑英寸的像素数量
	int xLogPixPerInch=pDC->GetDeviceCaps(LOGPIXELSX);
	int yLogPixPerInch=pDC->GetDeviceCaps(LOGPIXELSY);

	//得到设备坐标和逻辑坐标的比例
	long xExt=(long )size.cx * xLogPixPerInch/96 ;
	long yExt=(long )size.cy * yLogPixPerInch/96 ;
	pDC->SetViewportExt((int)(xExt*SizeZoom.cx /size.cx ),
		(int )(yExt*SizeZoom.cy /size.cy));

	//
	m_dwShowStyle &= ~SHOW_XINHAOJI;
	m_dwShowStyle &= ~SHOW_DIAOCHEAN;
	m_dwShowStyle &= ~SHOW_DCNAME;
	m_dwShowStyle &= ~SHOW_GNENGAN;
	m_dwShowStyle &= ~SHOW_PMHANZI;

	pDC->SetViewportOrg(ptOrigin.x ,ptOrigin.y );
	
	Invalidate();
    
	pDC->SetMapMode(iOldMode); 
	
	m_dwShowStyle |= SHOW_XINHAOJI;
	m_dwShowStyle |= SHOW_DIAOCHEAN;
	m_dwShowStyle |= SHOW_DCNAME;
	m_dwShowStyle |= SHOW_GNENGAN;
	m_dwShowStyle |= SHOW_PMHANZI;

	Invalidate();
}

void CZCTWnd::UpdateGdStatus(int iGdNo, int iGdStatus)
{
	POSITION pos = m_GdStatusList.GetHeadPosition();
	while( pos )	{
		CGdStatus *pGdStatus = m_GdStatusList.GetNext(pos);
		if(pGdStatus->m_iCommandID == iGdNo)		{
			pGdStatus->SetLockSta(iGdStatus==64);
			break;
		}
	}
}

void CZCTWnd::UpdateQjStatus(int iYHH, int iXHNo, int iQjStatus)
{
	POSITION pos = m_QjStatusList.GetHeadPosition();
	while(pos!=NULL){
		CQjStatus *pQjStatus = m_QjStatusList.GetNext(pos);
		if( pQjStatus->m_iCommandID == iYHH*100+iXHNo )	{
			pQjStatus->SetLockSta(iQjStatus == 64);
			break;
		}
	}
}


BOOL CZCTWnd::IsZLMode()
{
	POSITION pos = m_BSDList.GetHeadPosition();
	while (pos) {
		CBSD* pBsd = m_BSDList.GetNext(pos);
		if (pBsd->m_iType == BSD_TYPE_KZMS && pBsd->m_iStatus == COL_GREEN) {
			return TRUE;
		}
	}
	return FALSE;
}
CXinHJ* CZCTWnd::GetXHJByAn(CAnN *pAnN)
{
	int iType = pAnN->m_iType;
	int iXinHJID = pAnN->m_iRelate1;

	POSITION pos = m_XHJList.GetHeadPosition();
	while ( pos )
	{
		CXinHJ* pXinHJ = m_XHJList.GetNext(pos);
		if ( iType == CAnN::BTN_TYPE_LA || iType == CAnN::BTN_TYPE_YA){
			if ( pXinHJ->m_iLXIndex == iXinHJID ){
				return pXinHJ;
			}
		}
		else if ( iType == CAnN::BTN_TYPE_DA){
			if ( pXinHJ->m_iDXIndex == iXinHJID ){
				return pXinHJ;
			}
		}

	}
	//
	return NULL;
}
CAnN* CZCTWnd::GetBtnByDC(CDaoC* pDaoC)
{
	int iCommandID = pDaoC->m_iIndex;
	POSITION pos = m_ANList.GetHeadPosition();
	while (pos)
	{
		CAnN* pAnN = m_ANList.GetNext(pos);
		if (pAnN->m_iType==CAnN::BTN_TYPE_CA){
			if ( iCommandID == pAnN->m_iRelate1 || iCommandID == pAnN->m_iRelate2)	{
				return pAnN;
			}
		}
	}
	return NULL;
}
void CZCTWnd::SetDeviceContext(CDC* pDC)
{
	pDC->SetMapMode(m_nMapMode);

	if ( m_nMapMode == MM_ANISOTROPIC || m_nMapMode == MM_ISOTROPIC)
	{
		pDC->SetWindowOrg(0,0);

		if (m_nMapMode == MM_ISOTROPIC) {
			pDC->SetWindowExt(int(m_sLogicalCanvas.cx/m_fStationShrink),
				int(m_sLogicalCanvas.cy/m_fStationShrink));	//logic coordinates
		}
		else{
			pDC->SetWindowExt(m_sLogicalCanvas.cx,m_sLogicalCanvas.cy);	//logic coordinates
		}
		
		
		CRect cViewExt;//视口范围
		m_pReferenceWnd->GetClientRect(&cViewExt);
		pDC->SetViewportOrg(0,0);
		pDC->SetViewportExt(cViewExt.Width(),cViewExt.Height());	//Device coordinates
	}
}


void CZCTWnd::OnTimer(UINT nIDEvent) 
{
	//return;
	CClientDC dc(m_pCanvasWnd);
	CDC* pDC = &dc;
	SetDeviceContext(pDC);

	POSITION pos;
	//
	if ( nIDEvent == ID_CLOCK_BTNFLASH)
	{
		//处于激活状态的功能按钮闪烁
		if ( m_pFuncBtnActive )	{
			m_pFuncBtnActive->DrawSlf(pDC,m_bFlashFlag ? DS_FLASH : DS_COMM);
		}
		
		//处于激活状态的调列车按钮及其相关的信号机名称闪烁
		DrawActiveBtn(pDC,m_bFlashFlag);

		//表示灯闪烁		
		if ( m_dwShowStyle & SHOW_BSHIDENG)
		{
			POSITION pos= m_BSDList.GetHeadPosition();
			while(pos){
				CBSD *pBSD = m_BSDList.GetNext(pos);
				if (pBSD->GetFlashState()) {
					pBSD->DrawSlf(pDC,m_bFlashFlag?DS_FLASH:DS_HIDE);
				}
			}
		}


		//道岔挤岔闪烁
		pos = m_DCList.GetHeadPosition();
		while ( pos ){
			CDaoC* pDaoC = m_DCList.GetNext(pos);
			if ( pDaoC->IsJC() )	{
				if (pDaoC->m_iType==CDaoC::DT_TUOGUIQI) {
					pDaoC->DrawSlf(pDC,m_bFlashFlag?DS_FLASH:DS_HIDE);
				}
				else{
					COLORREF clr = m_bFlashFlag ? REDCOLOR : BLACKCOLOR;
					pDaoC->DrawDcc(pDC,	pDaoC->m_deltaB.x,pDaoC->m_deltaB.y,clr,clr,FALSE,TRUE);
					//
					pDaoC->DrawDcc(pDC,	pDaoC->m_deltaC.x,pDaoC->m_deltaC.y,clr,clr,FALSE,TRUE);
				}
			}
		}

		//信号机闪烁
		pos = m_XHJList.GetHeadPosition();
		while (pos) {
			CXinHJ* pXHJ = m_XHJList.GetNext(pos);
			if (pXHJ->GetFlashState()) {
				pXHJ->DrawSlf(pDC,m_bFlashFlag?DS_FLASH:DS_COMM);
			}
		}
		
		//
		m_bFlashFlag = !m_bFlashFlag;
	}
	//TRACE("m_bSingle = %d, m_iStationNo = %d \n",m_bSingle,m_iStationNo);

	// TODO: Add your message handler code here and/or call default
	CWnd::OnTimer(nIDEvent);
}

void CZCTWnd::OnReceiveInf(LPBYTE pInfBuf)
{
	BYTE byFrameKind	= pInfBuf[0];		//帧类型
	BYTE byVersion		= pInfBuf[1];		//数据版本号

	BOOL bRcvInf = (byFrameKind==STATIONINFO_FRAME_TYPE)|| (byFrameKind==STATIONCHANGE_FRAME_TYPE);
	bRcvInf |= byFrameKind == GUDAOLOCK_FRAME_TYPE;
	bRcvInf |= byFrameKind == QUJIANLOCK_FRAME_TYPE;
	bRcvInf |= byFrameKind == GUDAOALLLOCK_FRAME_TYPE;
	bRcvInf |= byFrameKind == QUJIANALLLOCK_FRAME_TYPE;
	bRcvInf |= byFrameKind == TRAINFRAMEALL_FRAME_TYPE;
	bRcvInf |= byFrameKind == TRAINFRAMECHANGE_FRAME_TYPE;
	bRcvInf |= byFrameKind == BAODIANXINXI_FRAME_TYPE;
#ifdef _DEBUG
	bRcvInf |= byFrameKind == 0x99;
#endif

	if (!bRcvInf) {//不是站场图处理的信息，则返回
		return;
	}

	WORD wStation;
	if (byFrameKind==BAODIANXINXI_FRAME_TYPE) {
		memcpy(&wStation,pInfBuf+19,2);	
	}
	else
	{
		memcpy(&wStation,pInfBuf+4,2);//取出站码
	}
	
	//
	//ASSERT(wStation == m_iStationNo);

	//----------------更新缓冲数据内容 -------------//
	if (byFrameKind==STATIONINFO_FRAME_TYPE 
		|| byFrameKind==STATIONCHANGE_FRAME_TYPE) //全场帧或变化帧
	{
		UpdateZCTSource(pInfBuf) ;
		//
		UpdateZCT(byFrameKind);
	}
	
	else if (byFrameKind==GUDAOLOCK_FRAME_TYPE)//单个股道解/封锁帧
	{
		int iGdNo =*(WORD *)(pInfBuf+6);	//股道号
		int iGdStatus =pInfBuf[8];		//状态(64：封锁；128：解锁)
		UpdateGdStatus(iGdNo,iGdStatus);
		//
		UpdateZCT(byFrameKind);
	}
	
	else if (byFrameKind==QUJIANLOCK_FRAME_TYPE) //单个区间解/封锁帧
	{
		int iYHH =pInfBuf[6];		//上(1)下(2)行
		int iXHNo = *(WORD *)(pInfBuf+7);	//区间号
		int iQjStatus = pInfBuf[9];	//状态
		UpdateQjStatus(iYHH,iXHNo,iQjStatus);
		//
		UpdateZCT(byFrameKind);
	}
	else if (byFrameKind==GUDAOALLLOCK_FRAME_TYPE) //股道全部封锁帧
	{		
		int iGDNUMS=pInfBuf[6];	//封锁的股道数目
		if(iGDNUMS!=0)	{	
			for(int i=0;i<iGDNUMS;i++)	{
				int iGDNo = *(WORD *)(pInfBuf+7+i*2);
				UpdateGdStatus(iGDNo,64);
			}
		}
		//
		UpdateZCT(byFrameKind);
	}
	
	else if (byFrameKind == QUJIANALLLOCK_FRAME_TYPE) //区间全部封锁帧
	{
		int Length;		//数据长度
		Length=pInfBuf[3]*256+pInfBuf[2];	
		if(Length > 5)
		{
			int iSXNUMS =pInfBuf[6];		//下行区间封锁数
			for(int i=0;i<iSXNUMS;i++)	{
				int iSXQJNo = pInfBuf[7+i];
				UpdateQjStatus(1,iSXQJNo,64);
			}
			
			int iXXNUMS =pInfBuf[7+iSXNUMS];	//上行区间封锁数
			for(int j=0;j<iXXNUMS;j++)	{
				int iXXQJNo=pInfBuf[8+iSXNUMS+j];
				UpdateQjStatus(/*pDC,*/2,iXXQJNo,64);
			}
		}
		//
		UpdateZCT(byFrameKind);
	}

	//车次框修改帧、车次队列帧、车次框变化帧(0x05)
	else if (byFrameKind == TRAINFRAMECHANGE_FRAME_TYPE) 
	{
		int iFrameNo = *(WORD *)(pInfBuf+7);
		CString strFrameInfo;
		memcpy(strFrameInfo.GetBuffer(8),(pInfBuf+9),8);
		strFrameInfo.ReleaseBuffer();
		m_FrameTrainNoList.UpdateFrameInf(iFrameNo,strFrameInfo,pInfBuf[17]);
	}
	//车次框全部帧(0x52)
	else if (byFrameKind == TRAINFRAMEALL_FRAME_TYPE)
	{
		WORD wDatalen=pInfBuf[3]*256+pInfBuf[2];
		
		//清空所有车次框内容
		m_FrameTrainNoList.ClearFrameContent();
		
		//增加新的内容
		for(int i=0;i<(wDatalen-3)/11;i++)	{
			int iFrameNo=*(WORD *)(pInfBuf+7+i*11);
			CString strFrameInfo;
			memcpy(strFrameInfo.GetBuffer(8),(pInfBuf+9+i*11),8);
			strFrameInfo.ReleaseBuffer();
			m_FrameTrainNoList.UpdateFrameInf(iFrameNo,strFrameInfo,pInfBuf[17+i*11]);
		}
	}
	//报点信息(0x0c)
	else if (byFrameKind == BAODIANXINXI_FRAME_TYPE)
	{
		//早晚点
		int iTimeExcur = pInfBuf[10] - pInfBuf[17];//单位：分
		//运行方向
		BYTE byDirection = pInfBuf[23];
		//股道号
		WORD wGdID;	
		memcpy(&wGdID,pInfBuf+21,sizeof(WORD));
		//根据股道号找到车次框ID
		int iFrameID = m_FrameTrainNoList.GetFrameIDBySectRel(wGdID);
		m_FrameTrainNoList.UpadateTimeExcur(iFrameID,byDirection,iTimeExcur);
	}

//////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	if (byFrameKind == 0x99) {
		m_FrameTrainNoList.ClearFrameContent();
	}
#endif
	
	//
	//m_bInfIvlid = FALSE;
}



BOOL CZCTWnd::UpdateZCTStatus(LPBYTE pBuffer,WORD nBSDNum)
{
	BYTE byStateDate,bt1;


	TRY
	{
		POSITION pos;
		int j=1;
		for(int i=0;i<LXNums;i++)  //列信域
		{
			memcpy(&byStateDate,pBuffer+i+4,1);
			pos=m_XHJList.GetHeadPosition();
			while(pos){
				CXinHJ *pXHJ = m_XHJList.GetNext(pos);
				if(pXHJ->m_iLXIndex == j) {
					pXHJ->m_iStatus = byStateDate;
					j++;
					break;
				}
			}
		}
		int k=1;
		for(int i=0;i<DXNums ;i++)  //调信域
		{
			memcpy(&byStateDate,pBuffer+LXNums+i+5,1);
			
			pos=m_XHJList.GetHeadPosition();
			while(pos!=NULL){
				CXinHJ *pXHJ=(CXinHJ *)m_XHJList.GetNext(pos);
				if(pXHJ->m_iDXIndex == k) {
					pXHJ->m_iStatus = byStateDate;					
					k++;
					break;
				}
			}
		}

		//道岔域
		j=1;
		
		int iDCNums = m_DCList.GetCount();
		int iWcQdValidNum = GetWcQdValidNums();
		pos=m_DCList.GetHeadPosition();
		for(int i=0;i<iDCNums;i++){
			//bt1=0;
			memcpy(&byStateDate,pBuffer+LXNums+DXNums+iDCQDMaps+iWcQdValidNum+i+7,1);
			//bt1=byStateDate;
			while(pos!=NULL){
				CDaoC *pDaoC=(CDaoC *)m_DCList.GetNext(pos);
				if(pDaoC->m_iIndex ==j)	{
					pDaoC->m_iStatus=byStateDate;	
					//pDaoC->m_iStatus=byStateDate&0x03;	
					//pDaoC->m_bOffed =(byStateDate&0x08)>>3;
					//pDaoC->m_bLocked =((byStateDate&0x04)>>2) | ((byStateDate&0x20)>>5);

					//找到相应的道岔按钮并置相应位
					CAnN* pAnN = GetBtnByDC(pDaoC);
					if ( pAnN )	{
						pAnN->m_byDCStatus = byStateDate;
					}
					
					j++;
					break;
				}
			}
		}

		
		//道岔区段域
		j=1;
		int nTest = iDCQDMaps;
		for( int i=0;i<iDCQDMaps ;i++)	{
			memcpy(&byStateDate,pBuffer+LXNums+DXNums+i+6,1);
			bt1=0;
			if(DCQDMap[i].QD_INDEX>0) bt1=byStateDate;
			if((bt1&0x0C)==0x04) SetRWCBand(DCQDMap[i].iPrDC,RED_BAND,TRUE);
			if((bt1&0x0C)==0x08) SetRWCBand(DCQDMap[i].iPrDC,RED_BAND,FALSE);
			if((bt1&0x03)==0x01) SetRWCBand(DCQDMap[i].iPrDC,WHITE_BAND,TRUE);
			if((bt1&0x03)==0x02) SetRWCBand(DCQDMap[i].iPrDC,WHITE_BAND,FALSE);
			if((bt1&0x30)==0x10) SetRWCBand(DCQDMap[i].iPrDC,CYAN_BAND,TRUE);
			if((bt1&0x30)==0x20) SetRWCBand(DCQDMap[i].iPrDC,CYAN_BAND,FALSE);

			j++;
		}

		RemoveJCHWBand();

		//无岔区段域
		pos=m_WcQDList.GetHeadPosition();
		for(int i=0;i<iWcQdValidNum;i++)
		{
			//bt1=0;
			memcpy(&byStateDate,pBuffer+LXNums+DXNums+iDCQDMaps+i+6,1);
			//bt1=byStateDate;

			while(pos){
				CWcQD *pWcQD=(CWcQD *)m_WcQDList.GetNext(pos);
				if(pWcQD->m_iIndex == j) {
					if((byStateDate&0x0C)==0x08) pWcQD->m_iStatus&=~RED_BAND;
					if((byStateDate&0x0C)==0x04) pWcQD->m_iStatus|=RED_BAND;
					if((byStateDate&0x03)==0x02) pWcQD->m_iStatus&=~WHITE_BAND;
					if((byStateDate&0x03)==0x01) pWcQD->m_iStatus|=WHITE_BAND;
					if((byStateDate&0x30)==0x20) pWcQD->m_iStatus&=~CYAN_BAND;
					if((byStateDate&0x30)==0x10) pWcQD->m_iStatus|=CYAN_BAND;

					//将Index相同的值全改变状态
					POSITION posNext = m_WcQDList.GetHeadPosition();
					while(posNext)
					{
						CWcQD *pNextWcQD=m_WcQDList.GetNext(posNext);
						if(pNextWcQD->m_iIndex == j) 
						{
							if((byStateDate&0x0C)==0x08) pNextWcQD->m_iStatus&=~RED_BAND;
							if((byStateDate&0x0C)==0x04) pNextWcQD->m_iStatus|=RED_BAND;
							if((byStateDate&0x03)==0x02) pNextWcQD->m_iStatus&=~WHITE_BAND;
							if((byStateDate&0x03)==0x01) pNextWcQD->m_iStatus|=WHITE_BAND;
							if((byStateDate&0x30)==0x20) pNextWcQD->m_iStatus&=~CYAN_BAND;
							if((byStateDate&0x30)==0x10) pNextWcQD->m_iStatus|=CYAN_BAND;
						}
					}
					j++;
					break;
				}
			}
		}
		

		//表示灯域
		int n=1;
		pos=m_BSDList.GetHeadPosition();
		for(int i=0;i<m_BSDList.GetCount();i++)
		{
			//bt1=0;
			memcpy(&byStateDate,pBuffer+LXNums+DXNums+iDCQDMaps+iWcQdValidNum+iDCNums+i+8,1);
			//bt1=byStateDate;
			while(pos){
				CBSD *pBSD=m_BSDList.GetNext(pos);
				if(pBSD->m_wBSDNo ==n)	{
					pBSD->m_iStatus = byStateDate;
					n++;
					break;
				}
			}
		}

		//功能灯域
		n=1;
		pos=m_FuncBtnList.GetHeadPosition();
		for(int i=0;i<m_FuncBtnList.GetCount();i++)	{
			memcpy(&byStateDate,pBuffer+LXNums+DXNums+iDCQDMaps+iWcQdValidNum+iDCNums+nBSDNum+i+9,1);
			while(pos){
				CFuncBtn *pFuncBtn = m_FuncBtnList.GetNext(pos);
				if(pFuncBtn->m_Index ==n){
					if(pFuncBtn->m_iCommandID == CFuncBtn::SYZS 
						|| pFuncBtn->m_iCommandID == CFuncBtn::XYZS)
					{
						if (byStateDate) {//为1表示按下,为0表示抬起
							pFuncBtn->m_iStatus = DS_DOWN;
						}
						else{
							pFuncBtn->m_iStatus = DS_COMM;
						}
							
					}
					n++;
					break;
				}
			}
		}

	}
	CATCH(CException, e)
	{
		char szBuf[100];
		e->GetErrorMessage(szBuf,100);
		return false;
	}
	END_CATCH
	return TRUE;
}

BOOL CZCTWnd::UpdateZCTSource(LPBYTE pBuffer)
{
	BYTE byFrame = pBuffer[0];
	if (byFrame == 0x02 || byFrame == 0x03){
		WORD wDataLen = *(WORD*)(pBuffer+2);
		WORD wStationNo = *(WORD*)(pBuffer+4);
		BYTE byDataBuf[1024] = {0};
		memcpy(byDataBuf,pBuffer+6,wDataLen-2);
		m_ParseStaInfo.TransactData(this, byDataBuf, wDataLen-2, byFrame);

		LPBYTE lpBuf = m_ParseStaInfo.GetInfoTabOutBuf();
		WORD nBsdTblSum = m_ParseStaInfo.GetBsdTblSum();

		return UpdateZCTStatus(lpBuf, nBsdTblSum);
	}
	return FALSE;
}


void CZCTWnd::SetRWCBand(short iDC,BYTE btClr,BOOL bIsSet)
{
	POSITION pos=m_DCList.GetHeadPosition();
	CDaoC *pDaoC;
	while(pos!=NULL)
	{
		pDaoC=(CDaoC *)m_DCList.GetNext(pos);
		if(pDaoC->m_iIndex ==iDC+1)	{
			break;
		}
	}

	if(bIsSet) pDaoC->m_iRWCBand|=btClr;
	else pDaoC->m_iRWCBand&=~btClr;

	if(pDaoC->m_iALink>0) SetRWCBand(pDaoC->m_iALink-1,btClr,bIsSet);
	if(pDaoC->m_iBLink>0)	{
		if(pDaoC->IsDW() || pDaoC->IsSK() || pDaoC->IsJC())
			SetRWCBand(pDaoC->m_iBLink-1,btClr,bIsSet);
		else SetRWCBand(pDaoC->m_iBLink-1,btClr,FALSE);
	}
	if(pDaoC->m_iCLink>0)	{
		if(pDaoC->IsFW() || pDaoC->IsSK() || pDaoC->IsJC())
			SetRWCBand(pDaoC->m_iCLink-1,btClr,bIsSet);
		else SetRWCBand(pDaoC->m_iCLink-1,btClr,FALSE);
	}
}

void CZCTWnd::RemoveJCHWBand()
{
	int i,iDC1,iDC2;
	BOOL bZG1,bZG2;
	POSITION pos;

	for(i=0;i<iJCHWNums;i++)	{
		iDC1=JCHW[i].dc1;//(pDoc->JCHW1[i]).DC1;
		iDC2=JCHW[i].dc2;
		bZG1=bZG2=FALSE;
		CDaoC *pDaoC1;
		CDaoC *pDaoC2;
		CDaoC *pDaoC;

		pos=m_DCList.GetHeadPosition();
		while(pos!=NULL)
		{
			pDaoC=(CDaoC *)(m_DCList).GetNext(pos);
			if(pDaoC->m_iIndex ==iDC1+1){
				pDaoC1=pDaoC;
				continue;
			}
			else if(pDaoC->m_iIndex ==iDC2+1)	{
				pDaoC2=pDaoC;
				continue;
			}
		}

		if(JCHW[i].DWZG1)	{
			if(pDaoC1->IsDW()) 		bZG1=TRUE;
		} 
		else if(pDaoC1->IsFW()) {
			bZG1=TRUE;
		}

		if(JCHW[i].DWZG2){
			if(pDaoC2->IsDW()) 
				bZG2=TRUE;
		} 
		else if(pDaoC2->IsFW()) 
			bZG2=TRUE;

		if(bZG1==TRUE && bZG2==FALSE)
			pDaoC1->m_iRWCBand =0;
		if(bZG1==FALSE && bZG2==TRUE)
			pDaoC2->m_iRWCBand =0;
	}
}

char* CZCTWnd::fgetline(char* strLine,int n,FILE* fp)
{
	do	{
		if(fgets(strLine,n,fp)==NULL)
			return NULL;
		ltrim(strLine);
	} while(strLine[0]=='\n'||strLine[0]=='#');
	return strLine;
}

void CZCTWnd::ltrim (char *str)
{
	int i,j=strlen(str);
	for(i=0;i<j;i++)
		if(str[i]!=' '&&str[i]!='\t') break;
	memmove(str,str+i,j-i+1);
}


void CZCTWnd::DeleteObject() 
{
	while(m_DCList.GetHeadPosition())		{delete m_DCList.RemoveHead();}
	while(m_XHJList.GetHeadPosition())		{delete m_XHJList.RemoveHead();}
	while(m_NQDList.GetHeadPosition())		{delete m_NQDList.RemoveHead();}
	while(m_WcQDList.GetHeadPosition())		{delete m_WcQDList.RemoveHead();}
    while(m_JYJList.GetHeadPosition())		{delete m_JYJList.RemoveHead();}
	while(m_JTList.GetHeadPosition())		{delete m_JTList.RemoveHead();}
	while(m_HZList.GetHeadPosition())		{delete m_HZList.RemoveHead();}
	while(m_ANList.GetHeadPosition())		{delete m_ANList.RemoveHead();}
	while(m_DCANList.GetHeadPosition())		{delete m_DCANList.RemoveHead();}
	while(m_BSDList.GetHeadPosition())		{delete m_BSDList.RemoveHead();}
	while(m_FuncBtnList.GetHeadPosition())	{delete m_FuncBtnList.RemoveHead();}
	while(m_GdStatusList.GetHeadPosition())	{delete m_GdStatusList.RemoveHead();}
	while(m_QjStatusList.GetHeadPosition())	{delete m_QjStatusList.RemoveHead();}
	m_ParseStaInfo.ReleaseTables();
}

void CZCTWnd::DrawQGJ(CDC* pDC,BOOL bIsQGJ)
{	
	CBaseElement* pDevice;
	int iState = bIsQGJ ? NS_QGJ : NS_COMM;
	
	//画无岔区段名称
	POSITION pos=m_WcQDList .GetHeadPosition();
	while(pos){
		pDevice = m_WcQDList.GetNext(pos);
		pDevice->ShowName(pDC,iState);
	}
	
	//画道岔名称
	pos=m_DCANList.GetHeadPosition();
	while(pos){
		pDevice = m_DCANList.GetNext(pos);
		pDevice->ShowName(pDC,iState);	
	}
}

void CZCTWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	//若当前鼠标已被捕获 || 信息中断 ||　大屏显示 || 不为自律模式
	//则返回 
	if ( GetCapture() || !m_bSingle || m_bInfIvlid){// || !IsZLMode())	{
		CWnd::OnMouseMove(nFlags, point);
		return;
	}
	CClientDC dc(m_pCanvasWnd);
	CDC* pDC = &dc;
	SetDeviceContext(pDC);                        

	//检测当前鼠标位置是否在桌面功能按钮里
	if ( m_wOperatorAttr & OPER_FUNCTNBTN)
	{
		if ( PtInDevices(pDC,point,MSFL_FUNTBTN) ) {
			m_iMouseFlag = MSFL_FUNTBTN;
			return;
		}
	}
	
	// 检测当前鼠标位置是否在调车或列车或道岔或引导按钮里

	//根据条件检测当前鼠标位置是否在调车按钮里
	//没有功能按钮激活或激活的功能按钮为总人解或总取消或重开信号时，bCanOperDLBtn为真(可操作调列车按钮)
	BOOL bCanOperDLBtn;
	BOOL bCanOperDaoChaBtn = FALSE;
	if ( m_pFuncBtnActive == NULL)	{
		bCanOperDLBtn = TRUE;//
		bCanOperDaoChaBtn = FALSE;//
	}
	else{
		bCanOperDLBtn  = m_pFuncBtnActive->m_iCommandID == CFuncBtn::ZRJ; 
		bCanOperDLBtn |= m_pFuncBtnActive->m_iCommandID == CFuncBtn::ZQX;
		bCanOperDLBtn |= m_pFuncBtnActive->m_iCommandID == CFuncBtn::CKXH;
		//
		bCanOperDaoChaBtn = m_pFuncBtnActive->m_iCommandID == CFuncBtn::ZDW;
		bCanOperDaoChaBtn |= m_pFuncBtnActive->m_iCommandID == CFuncBtn::ZFW;
		bCanOperDaoChaBtn |= m_pFuncBtnActive->m_iCommandID == CFuncBtn::DS;
		bCanOperDaoChaBtn |= m_pFuncBtnActive->m_iCommandID == CFuncBtn::DJ;
		bCanOperDaoChaBtn |= m_pFuncBtnActive->m_iCommandID == CFuncBtn::DF;
		bCanOperDaoChaBtn |= m_pFuncBtnActive->m_iCommandID == CFuncBtn::JF;
	}
	
	//
	if ( (bCanOperDLBtn || bCanOperDaoChaBtn) && PtInDevices(pDC,point,MSFL_DLCHEAN) )
	{
		if (bCanOperDLBtn) {
			
			if( (m_pTempDevice->GetType()==CAnN::BTN_TYPE_DA) 
				&& (m_wOperatorAttr & OPER_DIAOCHENAN) )/*调车按钮可操作*/	
			{
				if (m_wOperatorAttr & OPER_LIECHEBTN) /*可操作列车按钮且第一个按钮必须为列车/引导按钮*/
				{
					if ( m_AnNActiveList.GetCount() > 0 ){
						int iAnType = m_AnNActiveList.GetHead()->m_iType;
						if ( iAnType==CAnN::BTN_TYPE_LA || iAnType==CAnN::BTN_TYPE_YA ) {
							m_iMouseFlag = MSFL_DLCHEAN;
							return;
						}
					}
				}
				else{
					m_iMouseFlag = MSFL_DLCHEAN;
					return;
				}
			}
			else if( (m_pTempDevice->GetType()==CAnN::BTN_TYPE_LA) 
				&& (m_wOperatorAttr&OPER_LIECHEBTN) ){//列车按钮可操作
				m_iMouseFlag = MSFL_DLCHEAN;
				return;
			}
			else if ( (m_pTempDevice->GetType()==CAnN::BTN_TYPE_YA) 
				&& (m_wOperatorAttr&OPER_LIECHEBTN) ) {//引导按钮可操作
				m_iMouseFlag = MSFL_DLCHEAN;
				return;
			}
		}
		//根据条件检测当前鼠标位置是否在道岔按钮里
		else{ 
			if((m_pTempDevice->GetType()==CAnN::BTN_TYPE_CA) && (m_wOperatorAttr & OPER_DAOCHABTN) ){
				m_iMouseFlag = MSFL_DAOCHAN;
				return;				
			}
		}

	}

	//检测当前鼠标位置是否在股道封锁灯里
	if ( m_pFuncBtnActive != NULL && 
		 m_pFuncBtnActive->m_iCommandID == CFuncBtn::GDFS)
	{
		if ( PtInDevices(pDC,point,MSFL_GDLIGHT) ){
			m_iMouseFlag = MSFL_GDLIGHT;
			return;
		}
	}


	//检测当前鼠标位置是否在区间封锁灯里
	if( m_pFuncBtnActive != NULL && 
		m_pFuncBtnActive->m_iCommandID == CFuncBtn::QJFS )
	{
		if(PtInDevices(pDC,point,MSFL_QJLIGHT)){			
			m_iMouseFlag = MSFL_QJLIGHT;
			return;
		}
	}
	
	//若区故解按钮处于激活状态
	if ( m_pFuncBtnActive && m_pFuncBtnActive->m_iCommandID == CFuncBtn::QGJ)
	{
		//检测当前鼠标位置是否在无岔区段名称里
		if ( PtInDevices(pDC,point,MSFL_WCQDNAME) )	{	
			m_iMouseFlag = MSFL_WCQDNAME;
			return;
		}

		//检测当前鼠标位置是否道岔名称里
		if( PtInDevices(pDC,point,MSFL_DCQDNAME) )	{	
			m_iMouseFlag = MSFL_DCQDNAME;
			return;
		}
	}

	m_iMouseFlag = MSFL_INVALID;
	// TODO: Add your message handler code here and/or call default
	CWnd::OnMouseMove(nFlags, point);
}



void CZCTWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//if the station in multiple mode,then return.
	if ( m_bSingle == FALSE ){
		CWnd::OnLButtonDown(nFlags, point);
		return;
	}
	//
	CClientDC dc(m_pCanvasWnd);
	CDC* pDC = &dc;
	SetDeviceContext(pDC);

	if ( m_iMouseFlag )	{
		SetCapture();
		SetCursor(AfxGetApp()->LoadCursor(IDC_LBTN_DOWN));
	}
	
	//鼠标位置在桌面功能按钮里
	if ( m_iMouseFlag == MSFL_FUNTBTN)	{
		m_pTempDevice->DrawSlf(pDC,DS_DOWN);
	}
	//在调列车按钮里或道岔按钮里
	else if ( m_iMouseFlag == MSFL_DLCHEAN || m_iMouseFlag == MSFL_DAOCHAN)	{
		m_pTempDevice->DrawSlf(pDC,DS_DOWN);
	}

	// TODO: Add your message handler code here and/or call default
	CWnd::OnLButtonDown(nFlags, point);
}

void CZCTWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//if the station in multiple mode,then return.
	if ( m_bSingle == FALSE ){
		return;
	}

	//释放鼠标
	ReleaseCapture();

	//更改设备场景
	CClientDC dc(m_pCanvasWnd);
	CDC* pDC = &dc;
	SetDeviceContext(pDC);
	
	//The message that would be sent to the parent.
	StationMsg sStaMsg;
	sStaMsg.iStationID = m_iStationNo;
	sStaMsg.byMsgType = MSGTYPE_FUNCBTN;

	/* --------------   鼠标位置在桌面功能按钮里 --------------------------*/	
	if ( m_iMouseFlag == MSFL_FUNTBTN )	
	{

		//重画上次激活的按钮为初始状态
		if ( m_pFuncBtnActive )	{
			m_pFuncBtnActive->DrawSlf(&dc,DS_COMM);
		}
		
		//得到当前(鼠标点击的)功能按钮的ID
		int	iFuncBtnCmdID = m_pTempDevice->GetCommandID();
		sStaMsg.iValueRelative = iFuncBtnCmdID;

		/*
		 *	若按下的是上引总锁按钮或是下引总锁按钮，则弹起
			时不闪烁，并根据条件(m_iStatus)决定是否复位
		 */
		if ( iFuncBtnCmdID == CFuncBtn::XYZS || iFuncBtnCmdID == CFuncBtn::SYZS)
		{
			CString strTitle = "S引总锁";
			if (iFuncBtnCmdID == CFuncBtn::XYZS) {
				strTitle = "X引总锁";
			}
			//密码验证
			CPassWordDlg dlg(m_strPassword[0],strTitle);
			if (dlg.DoModal() == IDOK) {
				CPassWordDlg dlg(m_strPassword[1],strTitle);
				if (dlg.DoModal() == IDOK) {
					if ( ((CFuncBtn*)(m_pTempDevice))->m_iStatus == DS_DOWN ){
						::SendMessage(m_hMsgHandle,UM_FORMSTATION,(WPARAM)&sStaMsg,FALSE);
					}
					else{
						::SendMessage(m_hMsgHandle,UM_FORMSTATION,(WPARAM)&sStaMsg,TRUE);	
					}
				}
			}
		}
		/*
		 *	若按下的是X停电恢复或S停电恢复按钮，则弹起时不闪烁,恢复原始状态
		 */
		else if (iFuncBtnCmdID == CFuncBtn::XTDHF || iFuncBtnCmdID == CFuncBtn::STDHF)
		{
			CString strTitle = "S停电恢复";
			if (iFuncBtnCmdID == CFuncBtn::XTDHF) {
				strTitle = "X停电恢复";
			}
			//密码验证
			CPassWordDlg dlg(m_strPassword[0],strTitle);
			if (dlg.DoModal() == IDOK) {
				CPassWordDlg dlg(m_strPassword[1],strTitle);
				if (dlg.DoModal() == IDOK) {
					::SendMessage(m_hMsgHandle,UM_FORMSTATION,(WPARAM)&sStaMsg,0);
				}
			}
		}
		/*
		 *	若按下的是进路试排或排列进路按钮，则弹起时不闪烁，恢复原始状态
		 */
		else if( iFuncBtnCmdID == CFuncBtn::JLSP || iFuncBtnCmdID == CFuncBtn::PLJL )
		{
			//判断进路是否存在
			CString strCause,strFrameContent;
			if (m_InterlockJuge.IsExistER(strCause,strFrameContent,iFuncBtnCmdID)) {
				sStaMsg.m_pAttachValue = &strFrameContent;
				::SendMessage(m_hMsgHandle,UM_FORMSTATION,(WPARAM)&sStaMsg,(LPARAM)&m_AnNActiveList);	
			}
			else
			{
				TRACE("%s\n",strCause);
				MessageBox(strCause,"警告!",MB_ICONEXCLAMATION);
			}
		}

		/*
		 	按下的按钮是区故解，则将道岔名称和无岔区段名称以红底白字显示。
			区故解按钮闪烁
		*/
		else if(iFuncBtnCmdID == CFuncBtn::QGJ)
		{
			BOOL bFlag = (m_pFuncBtnLast != NULL) && (m_pFuncBtnLast->m_iCommandID==CFuncBtn::QGJ);
			if ( bFlag == FALSE ) {	
				//密码验证
				CPassWordDlg dlg(m_strPassword[0],"区故解");
				if (dlg.DoModal() == IDOK) {
					CPassWordDlg dlg(m_strPassword[1],"区故解");
					if(dlg.DoModal() == IDOK){
						bFlag = TRUE;			
					}
				}
			}

			//
			if ( bFlag )
			{
				m_dwShowStyle |= SHOW_WCQDNAME;
				m_dwShowStyle |= SHOW_DCNAME;
				
				//重新设置激活的按钮为当前按下的按钮
				m_pFuncBtnActive = (CFuncBtn*)m_pTempDevice;
				
				//画无岔区段名称(红底白字显示)	//画道岔名称(红底白字显示)
				DrawQGJ(pDC,TRUE);
			}
		}
		/*
		 *	按下的是清除按钮	
		 */
		else if ( iFuncBtnCmdID == CFuncBtn::QCAN )
		{
			//若上次激活的功能按钮为区故解，则
			if ( m_pFuncBtnActive && m_pFuncBtnActive->m_iCommandID == CFuncBtn::QGJ )
			{
				//恢复无岔区段名称为正常状态//恢复道岔名称为正常状态
				DrawQGJ(pDC,FALSE);
			}

			//置当前激活的按钮为空
			m_pFuncBtnActive = NULL;
		}

		//
		else 
		{
			//密码验证
			/*CPassWordDlg dlg(m_strPassword[0]);
			if (dlg.DoModal() != IDOK) {
				goto END_LBTNUP;
			}*/
			
			//重新设置激活的按钮为当前按下的按钮
			m_pFuncBtnActive = (CFuncBtn*)m_pTempDevice;
		}

		//保存上次操作的功能按钮
		m_pFuncBtnLast = (CFuncBtn*)m_pTempDevice;

		//重画功能按钮
		m_pTempDevice->DrawSlf(pDC,DS_COMM);
		
		//清除激活的按钮链表
		DrawActiveBtn(pDC,TRUE);
		m_AnNActiveList.RemoveAll();
	}
	
	/*------------  当前鼠标位置在股道封锁灯里  -------------------------*/
	else if( m_iMouseFlag == MSFL_GDLIGHT )
	{
		sStaMsg.iValueRelative = CFuncBtn::GDFS;
		::SendMessage(m_hMsgHandle,UM_FORMSTATION,(WPARAM)&sStaMsg,(LPARAM)m_pTempDevice);
		
/*
#ifdef _DEBUG
		((CGdStatus*)m_pTempDevice)->SetLockSta(!((CGdStatus*)m_pTempDevice)->GetLockSta());
		m_pTempDevice->DrawSlf(pDC,DS_COMM);
#endif
//*/
		m_pFuncBtnActive->DrawSlf(&dc,DS_COMM);
		m_pFuncBtnActive = NULL;
	}

	/* ---------- 当前鼠标位置在区间封锁灯里 ----------------------------*/
	else if( m_iMouseFlag == MSFL_QJLIGHT )
	{
		sStaMsg.iValueRelative = CFuncBtn::QJFS;
		::SendMessage(m_hMsgHandle,UM_FORMSTATION,(WPARAM)&sStaMsg,(LPARAM)m_pTempDevice);
		
		//
		m_pFuncBtnActive->DrawSlf(&dc,DS_COMM);
		m_pFuncBtnActive = NULL;
	}
	
	/*---------------当前鼠标位置在调车或列车按钮里----------------------*/
	else if ( m_iMouseFlag == MSFL_DLCHEAN )
	{
		BOOL bConfirm;
		if (m_pTempDevice->GetType() == CAnN::BTN_TYPE_YA) {	
			//密码验证
			CPassWordDlg dlg(m_strPassword[0]);
			if (dlg.DoModal() == IDOK) {
				bConfirm = TRUE;
			}
			else{
				bConfirm = FALSE;
			}
		}
		else{
			bConfirm = TRUE;
		}
		if (bConfirm) {
			if ( m_pFuncBtnActive == NULL)	{
				//加入闪烁按钮链表
				m_AnNActiveList.AddTail((CAnN*)m_pTempDevice);
			}
			else{
				BOOL bFlag = m_pFuncBtnActive->m_iCommandID == CFuncBtn::ZRJ;//总人解
				bFlag |= m_pFuncBtnActive->m_iCommandID == CFuncBtn::CKXH;//重开信号
				bFlag |= m_pFuncBtnActive->m_iCommandID == CFuncBtn::ZQX;//总取消
				bFlag |= m_pFuncBtnActive->m_iCommandID == CFuncBtn::PDJS;//坡道解锁
				//
				if ( bFlag ){
					sStaMsg.iValueRelative = m_pFuncBtnActive->m_iCommandID;
					::SendMessage(m_hMsgHandle,UM_FORMSTATION,(WPARAM)&sStaMsg,(LPARAM)m_pTempDevice);
					
					//
					m_pFuncBtnActive->DrawSlf(pDC,DS_COMM);
					m_pFuncBtnActive = NULL;
				}
			}
		}
		
		//恢复正常显示
		m_pTempDevice->DrawSlf(pDC,DS_COMM);
	}

	/*-------------------当前鼠标位置在道岔按钮里-------------------------*/
	else if ( m_iMouseFlag == MSFL_DAOCHAN )	{
		//向父窗口发消息
		sStaMsg.iValueRelative = m_pFuncBtnActive->m_iCommandID;
		::SendMessage(m_hMsgHandle,UM_FORMSTATION,(WPARAM)&sStaMsg,(LPARAM)m_pTempDevice);
		
		//恢复正常显示
		m_pTempDevice->DrawSlf(pDC,DS_COMM);

		//将处于激活状态的功能按钮(指ZDW,ZFW等与道岔按钮有关的功能按钮)恢复正常
		m_pFuncBtnActive->DrawSlf(pDC,DS_COMM);
		m_pFuncBtnActive = NULL;
	}

	/*-----------------位置在无岔区段名称里------------*/
	/*-----------------位置在道岔名称里----------------*/
	else if (m_iMouseFlag == MSFL_WCQDNAME || m_iMouseFlag == MSFL_DCQDNAME)
	{
		sStaMsg.iValueRelative = CFuncBtn::QGJ;
	
		//向父窗口发消息
		::SendMessage(m_hMsgHandle,UM_FORMSTATION,(WPARAM)&sStaMsg,(LPARAM)(m_pTempDevice->GetCommandID()));
		//恢复无岔区段名称为正常状态
		//恢复道岔名称为正常状态
		DrawQGJ(pDC,FALSE);
		
		//
		m_pFuncBtnActive->DrawSlf(pDC,DS_COMM);
		m_pFuncBtnActive = NULL;
	}

	//	
	m_iMouseFlag = MSFL_INVALID;
	
	// TODO: Add your message handler code here and/or call default
	CWnd::OnLButtonUp(nFlags, point);
}

void CZCTWnd::OnPaint()
{
	TRACE("void CZCTWnd::OnPaint()\n");
	if ( !m_bSingle ){
		return;
	}

	//
	CPaintDC dc(m_pCanvasWnd); // device context for painting
	CDC* pDC = &dc;
	
	//Fill the srceen to black color
	CBrush brush;
	brush.CreateSolidBrush (BLACKCOLOR);	//屏幕底色
	CBrush* pOldBrush=pDC->SelectObject (&brush);

	pDC->Rectangle (CRect(CPoint(0,0),m_sLogicalCanvas));
	pDC->SelectObject(pOldBrush);

	//Change the Device context
	SetDeviceContext(pDC);

	//Draw the station graphics
	DrawZCT(pDC);
	
	// Do not call CWnd::OnPaint() for painting messages
}

BOOL CZCTWnd::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	switch(pMsg->message) 
	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		m_pReferenceWnd->PostMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
		break;
	case WM_COMMAND://弹出菜单命令
		{
			CMenu *pMenu = CMenu::FromHandle(m_hPUMenu);
			if (m_hPMHandle) {
				for(UINT i=0; i<pMenu->GetMenuItemCount(); i++){
					if (pMsg->wParam == pMenu->GetMenuItemID(i)) {
						::PostMessage(m_hPMHandle,pMsg->message,pMsg->wParam,pMsg->lParam);
						//
						break;
					}
				}
			}
		}
	//default:
		//TRACE("%x,%x,%x\n",pMsg->message,pMsg->wParam,pMsg->lParam);
	}
	
	return CWnd::PreTranslateMessage(pMsg);
}
LRESULT CZCTWnd::OnMsgFromFrameNo( WPARAM wParam, LPARAM lParam )
{
	if ( !m_bInfIvlid && IsZLMode() ) {//信息有效且处于自律模式时				
		StationMsg sStaMsg;
		sStaMsg.iStationID = m_iStationNo;
		sStaMsg.byMsgType = MSGTYPE_FRAME;
		sStaMsg.iValueRelative = ((CFrameTrainNo*)wParam)->GetFrameID();
		CString strContent = ((CFrameTrainNo*)wParam)->GetContent();
		::SendMessage(m_hMsgHandle,UM_FORMSTATION,(WPARAM)&sStaMsg,(LPARAM)&strContent);
	}
	
	return 0;
}
void CZCTWnd::initialization(BOOL bShow/* = TRUE*/)
{
	if ( GetSafeHwnd() == FALSE ){
		return;
	}
	if ( bShow ) {
		SetTimer(ID_CLOCK_BTNFLASH,TIMERBTNFSHELAPSE,NULL);
	}
	else {
		//先停止计时器
		KillTimer(ID_CLOCK_BTNFLASH);

		//取消处于激活状态的功能按钮
		m_pFuncBtnActive = NULL;

		//取消处于激活状态的调、列车按钮
		m_AnNActiveList.RemoveAll();
	}
}

void CZCTWnd::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CWnd::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	if (bShow){
		StationMsg sStaMsg;
		sStaMsg.iStationID = m_iStationNo;
		sStaMsg.byMsgType = MSGTYPE_STANCHNG;
		sStaMsg.iValueRelative = bShow;
		::SendMessage(m_hMsgHandle,UM_FORMSTATION,(WPARAM)&sStaMsg,0);
	}
	else{
		TRACE("Hide ID = %d\n",m_iStationNo);
	}

	//
	initialization(bShow);
}

void CZCTWnd::DrawActiveBtn(CDC* pDC,BOOL bShow)
{
	POSITION pos = m_AnNActiveList.GetHeadPosition();
	while (pos) {
		//
		CAnN* pAnN = m_AnNActiveList.GetNext(pos);
		pAnN->DrawSlf(pDC,bShow ? DS_COMM : DS_DOWN);
		pAnN->ShowName(pDC,bShow ? NS_COMM : NS_HIDE);

		//
		CXinHJ* pXinHJ = GetXHJByAn(pAnN);
		if ( pXinHJ ){
			pXinHJ->ShowName(pDC,bShow?NS_COMM:NS_HIDE);
		}
	}
}

BOOL CZCTWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if ( m_iMouseFlag != MSFL_INVALID){
		SetCursor(AfxGetApp()->LoadCursor(IDC_LBTN_UP));
		return TRUE;
	}
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

int CZCTWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}
void CZCTWnd::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	//光标置“手”状或光标位置不在站场图里时，不弹出菜单
	if (pWnd != this || m_iMouseFlag != MSFL_INVALID){//|| pPopMenu->GetMenuItemCount()>11) {
		return;
	}
	
	//
	CMenu* pPopMenu = CMenu::FromHandle(m_hPUMenu);
	int iOrginCount = pPopMenu->GetMenuItemCount();
	if (m_dwShowStyle&SHOW_POPMENU) {

		UINT nFlags;
		//----------------显示风格-------------------
		
		if (iOrginCount>0) {
			pPopMenu->AppendMenu(MF_SEPARATOR);
		}
		nFlags = m_dwShowStyle&SHOW_DCNAME ? MF_STRING|MF_CHECKED : MF_STRING|MF_UNCHECKED;
		pPopMenu->AppendMenu(nFlags,ID_SHOW_DAOCHANAME,"道岔名称(&D)\t");
		//
		nFlags = m_dwShowStyle&SHOW_WCQDNAME ? MF_STRING|MF_CHECKED : MF_STRING|MF_UNCHECKED;
		pPopMenu->AppendMenu(nFlags,ID_SHOW_WUCHAQNAME,"无岔区段名称(&W)\t");
		//
		nFlags = m_dwShowStyle&SHOW_XHJNAME ? MF_STRING|MF_CHECKED : MF_STRING|MF_UNCHECKED;
		pPopMenu->AppendMenu(nFlags,ID_SHOW_XINHAONAME,"信号机名称(&X)\t");
		//
		nFlags = m_dwShowStyle&SHOW_FRAMENO ? MF_STRING|MF_CHECKED : MF_STRING|MF_UNCHECKED;
		pPopMenu->AppendMenu(nFlags,ID_SHOW_FRAMENO,"车次框(&C)\t");
		//
		nFlags = m_dwShowStyle&SHOW_PMHANZI ? MF_STRING|MF_CHECKED : MF_STRING|MF_UNCHECKED;
		pPopMenu->AppendMenu(nFlags,ID_SHOW_PMHANZI,"屏幕汉字(&P)\t");
		//
		nFlags = m_dwShowStyle&SHOW_ANNAME ? MF_STRING|MF_CHECKED : MF_STRING|MF_UNCHECKED;
		pPopMenu->AppendMenu(nFlags,ID_SHOW_BTNNAME,"按钮名称(&B)\t");
		
		//--------------映射模式-----------
		pPopMenu->AppendMenu(MF_SEPARATOR);
		nFlags = (m_nMapMode==MM_TEXT) ? (MF_STRING|MF_CHECKED|MFT_RADIOCHECK) : (MF_STRING|MF_UNCHECKED);
		pPopMenu->AppendMenu(nFlags,ID_MM_TEXT,"实际尺寸(&A)\t");
		//
		nFlags = (m_nMapMode==MM_ANISOTROPIC) ? (MF_STRING|MF_CHECKED|MFT_RADIOCHECK) : (MF_STRING|MF_UNCHECKED);
		pPopMenu->AppendMenu(nFlags,ID_MM_ANISOTROPIC,"理想尺寸(&I)\t");
		
		//子菜单
		CMenu popSubMenu;
		popSubMenu.CreateMenu();
		popSubMenu.AppendMenu(MF_STRING,ID_SK_ZOOMIN,"放大站场图(&+)\t");
		popSubMenu.AppendMenu(MF_STRING,ID_SK_ZOOMOUT,"缩小站场图(&-)\t");
		//弹出菜单
		nFlags = (m_nMapMode==MM_ISOTROPIC) ? (MF_STRING|MF_CHECKED|MFT_RADIOCHECK|MF_POPUP) : (MF_STRING|MF_UNCHECKED|MF_POPUP);
		pPopMenu->AppendMenu(nFlags,(UINT)(HMENU)popSubMenu,"自由缩放(&S)\t");
		
		//-------------------------------------------------
		//--------------缩放比例---------------
		//pPopMenu->AppendMenu(MF_SEPARATOR);
		//nFlags = MF_STRING;
		//(m_nMapMode != MM_ISOTROPIC) ? (nFlags |= MF_GRAYED) : (nFlags |= MF_ENABLED);
		//pPopMenu->AppendMenu(nFlags,ID_SK_ZOOMIN,"放大站场图＋\t");
		//pPopMenu->AppendMenu(nFlags,ID_SK_ZOOMOUT,"缩小站场图－\t");
	}
	pPopMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,point.x,point.y,this);

	UINT uPresentCount = pPopMenu->GetMenuItemCount();
	for(UINT i=0; i<uPresentCount-iOrginCount; i++){
		pPopMenu->DeleteMenu(iOrginCount,MF_BYPOSITION);
	}
}
void CZCTWnd::OnPopMenu(UINT nID)
{
//	UINT nFlags;
	if ((nID>=ID_SHOW_START) && (nID<=ID_SHOW_END)) {//显示按钮
		DWORD dwTemp;
		switch(nID) {
		case ID_SHOW_DAOCHANAME:
			dwTemp = SHOW_DCNAME;
			break;			
		case ID_SHOW_WUCHAQNAME:
			dwTemp = SHOW_WCQDNAME;
			break;			
		case ID_SHOW_BTNNAME:
			dwTemp = SHOW_ANNAME;
			break;			
		case ID_SHOW_XINHAONAME:
			dwTemp = SHOW_XHJNAME;
			break;			
		case ID_SHOW_FRAMENO:
			dwTemp = SHOW_FRAMENO;
			break;			
		case ID_SHOW_PMHANZI:
			dwTemp = SHOW_PMHANZI;
			break;
		case ID_SHOW_BSHIDENG:
			dwTemp = SHOW_BSHIDENG;
			break;
		case ID_SHOW_GDLIGHT:
			dwTemp = SHOW_GDLIGHT;
			break;
		case ID_SHOW_QJLIGHT:
			dwTemp = SHOW_QJLIGHT;
			break;
		}
		
		//
		(m_dwShowStyle & dwTemp) ? (m_dwShowStyle &= ~dwTemp) : (m_dwShowStyle |= dwTemp);
		//nFlags = m_dwShowStyle&dwTemp ? MF_STRING|MF_CHECKED : MF_STRING|MF_UNCHECKED;
		//m_StationMenu.CheckMenuItem(nID,nFlags);
		//
		DrawZCT();
	}
	else if (nID>=ID_MM_START && nID<=ID_MM_END) {
		int nNewMapMode;
		switch(nID) {
		case ID_MM_TEXT:
			nNewMapMode = MM_TEXT;
			break;
		case ID_MM_ISOTROPIC:
			nNewMapMode = MM_ISOTROPIC;
			break;
		case ID_MM_ANISOTROPIC:
			nNewMapMode = MM_ANISOTROPIC;
			break;
		}
		
		//
		//m_StationMenu.CheckMenuRadioItem(ID_MM_START,ID_MM_END,nID,MF_STRING|MF_CHECKED|MFT_RADIOCHECK);
		//
		if (m_nMapMode != nNewMapMode) {
			m_nMapMode = nNewMapMode;
			Invalidate();
		}
	}
	else if (nID>=ID_SK_START && nID<=ID_SK_END) {
		//
		m_nMapMode = MM_ISOTROPIC;
		//m_StationMenu.CheckMenuRadioItem(ID_MM_START,ID_MM_END,ID_MM_ISOTROPIC,MF_STRING|MF_CHECKED|MFT_RADIOCHECK);
		//
		switch(nID) {
		case ID_SK_ZOOMOUT:
			if (m_fStationShrink - STEPZOOM > MAXZOOMOUT) {
				m_fStationShrink -= STEPZOOM;
			}
			break;
		case ID_SK_ZOOMIN:
			if (m_fStationShrink + STEPZOOM < MAXZOOMIN) {
				m_fStationShrink += STEPZOOM;
			}
			break;
		}
		Invalidate();
	}
}
void CZCTWnd::OnUpdateDeviceName(CCmdUI* pCmdUI)
{
	/*
	UINT nFlags;
	switch(pCmdUI->m_nID) {
	case ID_SHOW_DAOCHANAME:
		nFlags = m_dwShowStyle&SHOW_DCNAME ? MF_STRING|MF_UNCHECKED : MF_STRING|MF_CHECKED;
		m_StationMenu.CheckMenuItem(ID_SHOW_DAOCHANAME,nFlags);
		//pCmdUI->SetCheck(m_dwShowStyle&SHOW_WCQDNAME);
		break;
	case ID_SHOW_WUCHAQNAME:
		break;
	default:;
	}*/
}
BOOL CZCTWnd::InvalidateInf(BOOL bFlag)
{
	BOOL bOldFlag = m_bInfIvlid;
	m_bInfIvlid = bFlag;

	//
	m_FrameTrainNoList.InvalidateInf(bFlag);

	//重画整个站场图
	if (GetSafeHwnd()) {
		initialization(!bFlag);
		m_pCanvasWnd->Invalidate();
	}
	return bOldFlag;
}

CString CZCTWnd::GetWcQdNameByID(int iIndex)
{
	POSITION pos = m_WcQDList.GetHeadPosition();
	while (pos) {
		CWcQD* pWcQD = m_WcQDList.GetNext(pos);
		if (pWcQD->m_iIndex == iIndex) {
			return pWcQD->m_strName;
		}
	}
	return "";
}

int CZCTWnd::GetWcQdIDByName(CString strName)
{
	POSITION pos = m_WcQDList.GetHeadPosition();
	while (pos) {
		CWcQD* pWcQD = m_WcQDList.GetNext(pos);
		if (pWcQD->m_strName == strName) {
			return pWcQD->m_iIndex;
		}
	}
	return 0;
}

CString CZCTWnd::GetBtnNameByID(int iCommandID)
{
	POSITION pos = m_ANList.GetHeadPosition();
	while (pos) {
		CAnN* pAnN = m_ANList.GetNext(pos);
		if (pAnN->m_iCommandID == iCommandID) {
			return pAnN->m_strName;
		}
	}
	return "";
}

int CZCTWnd::GetBtnIDByName(CString strName)
{
	POSITION pos = m_ANList.GetHeadPosition();
	while (pos) {
		CAnN* pAnN = m_ANList.GetNext(pos);
		if (pAnN->m_strName == strName) {
			return pAnN->m_iCommandID;
		}
	}
	return 0;
}

void CZCTWnd::GetWcQdNameList(CStringList &sNameList)
{
	POSITION pos = m_WcQDList.GetHeadPosition();
	while (pos) {
		CWcQD* pWcQD = m_WcQDList.GetNext(pos);
		sNameList.AddTail(pWcQD->m_strName);
	}
}

BOOL CZCTWnd::ReadStationInf(CString strPath, int iReadMode)
{
	DeleteObject();
	//
	BOOL bReadValue = TRUE;
	//offset.dat必须首先读取
	if (iReadMode & RDMD_OFFSET) {
		if (!ReadOffset(strPath+FILENAME_OFFSET)) {
			TRACE("Read offset.dat failure!\n");
			bReadValue = FALSE;
		}
	}

	//
	if (iReadMode & RDMD_SYARD) {
		if (!ReadYard(strPath+FILENAME_SYARD)) {
			TRACE("Read yard.dat failure!\n");
			bReadValue = FALSE;
		}
	}
	//
	if (iReadMode & RDMD_MYARD) {
		if (!ReadYard(strPath+FILENAME_MYARD)) {
			TRACE("Read yard_m.dat failure!\n");
			bReadValue = FALSE;
		}
	}
	//
	if (iReadMode & RDMD_MASK) {
		if (!m_ParseStaInfo.ReadMask(strPath+FILENAME_MASK)) {
			TRACE("Read mask.ini failure!\n");
			bReadValue = FALSE;
		}
	}
	//
	if (iReadMode & RDMD_SFRAM) {
		if ( !m_FrameTrainNoList.ReadFrameInf(strPath+FILENAME_SFRAME,
				m_sizeShrink,m_sizeExcursion) ) {
			TRACE("Read frame.dat failure!\n");
			bReadValue = FALSE;
		}
	}
	//
	if (iReadMode & RDMD_MFRAM) {
		if (!m_FrameTrainNoList.ReadFrameInf(strPath+FILENAME_MFRAME,
				m_sizeShrink,m_sizeExcursion)) {
			TRACE("Read frame_M.dat failure!\n");
			bReadValue = FALSE;
		}
	}
	//
	if (iReadMode & RDMD_GUDAO) {
		if (!ReadGd(strPath+FILENAME_GUDAO)) {
			TRACE("Read gd.dat failure!\n");
			bReadValue = FALSE;
		}
	}
	//
	if (iReadMode & RDMD_DESK) {
		if (!ReadDesk(strPath+FILENAME_DESK)) {
			TRACE("Read desk.dat failure!\n");
			bReadValue = FALSE;
		}
	}
	
	//
	if (iReadMode & RDMD_JINLU) {
		if ( !m_InterlockJuge.m_EntRailWay.ReadERFile(strPath+FILENAME_JINLU) ) {
			TRACE("Read jl.ini failure!\n");
			bReadValue = FALSE;
		}
		if ( !m_InterlockJuge.m_PasRailWay.ReadFile(strPath+FILENAME_JINLU)) {
			TRACE("Read 'pass way' jl.ini failure!\n");
			bReadValue = FALSE;
		}
	}
	
	return bReadValue;
}


void CZCTWnd::SetPopupMenu(HMENU hMenu,HWND hMsgHandle)
{
	ASSERT( hMenu != NULL);
	m_hPUMenu = hMenu;
	m_hPMHandle = hMsgHandle;
	/*
	if (hMenu) {
		m_StationMenu.Attach(hMenu);
	}
	else{
		m_StationMenu.CreatePopupMenu();
	}*/
}


int CZCTWnd::GetWcQdValidNums()
{
	int iWcQdIndex[200]={0},iWCQDNums=0;
	POSITION pos = m_WcQDList.GetHeadPosition();
	while (pos) 
	{
		CWcQD* pWcQd = m_WcQDList.GetNext(pos);

		//
		int i;
		for(i=0; i<iWCQDNums; i++){
			if (pWcQd->m_iIndex == iWcQdIndex[i]) {
				break;
			}
		}

		//
		if (i == iWCQDNums) 
		{
			iWcQdIndex[iWCQDNums] = pWcQd->m_iIndex;
			iWCQDNums++;
			continue;
		}
		
	}
	//
	return iWCQDNums;
}
BOOL CZCTWnd::PtInDevices(CDC* pDC,CPoint pt,int iFlag)
{
	CObList* pList = NULL;
	int iDevcieType;
		
	switch(iFlag) {
	case MSFL_FUNTBTN:
		iDevcieType = DT_SELF;
		pList = &m_FuncBtnList;
		break;

	case MSFL_GDLIGHT:
		iDevcieType = DT_SELF;
		pList = &m_GdStatusList;
		break;

	case MSFL_QJLIGHT:
		iDevcieType = DT_SELF;
		pList = &m_QjStatusList;
		break;

	case MSFL_DLCHEAN:
	case MSFL_DAOCHAN:
		iDevcieType = DT_SELF;
		pList = &m_ANList;
		break;

	case MSFL_WCQDNAME:
		iDevcieType = DT_NAME;
		pList = &m_WcQDList;
		break;

	case MSFL_DCQDNAME:
		iDevcieType = DT_NAME;
		pList = &m_DCANList;
		break;
	}
	if (NULL == pList) {
		m_pTempDevice = NULL;
		return FALSE;
	}

	//
	POSITION pos = pList->GetHeadPosition();
	while(pos)
	{
		CBaseElement* pDevice = (CBaseElement*)pList->GetNext(pos);
		if (pDevice->PtInDevice(pDC,pt,iDevcieType)) {
			m_pTempDevice = pDevice;
			return TRUE;
		}
	}
	//
	m_pTempDevice = NULL;
	return FALSE;
}

int CZCTWnd::GetJLProAccordBtn(const WORD *pBtnList, const int &iBtnNum)
{
	int iPro = m_InterlockJuge.m_EntRailWay.GetProAccordByBtn(pBtnList,iBtnNum);
	if (iPro != -1) {
		return iPro;
	}
	else{
		if (m_InterlockJuge.m_PasRailWay.IsExistER(pBtnList,iBtnNum)) {
			return 3;
		}
		else{
			return -1;
		}
	}
}
