// DaoC.h

#ifndef _DaoC_H
#define _DaoC_h

#include "BaseElement.h"


#define CX_RADIUS      14 /* radius of the heart of DaoCha */
#define DC_POINT       12
#define DefaultSlope   1

typedef struct {         /* Qu Duan Map */
	short QD_INDEX;
	short iPrDC;
} DCQDMAP;

typedef struct {         /* Dao Cha Jiao Cha Huan Wei */
	short dc1;
	BOOL  DWZG1;
	short dc2;
	BOOL  DWZG2;
} JCHW;

//道岔状态定义
enum _DaoChaStatus		
{
	DCST_SK = 0x00,	//四开
	DCST_FW = 0x01,	//反位
	DCST_DW = 0x02,	//定位
	DCST_JC = 0x03,	//挤岔
	DCST_DF = 0x08,	//单封
	DCST_DS = 0x24	//单锁
};

//道岔状态判断宏定义
#define DAOCHA_ISSK(iStatus)	((iStatus)==DCST_SK)	// 是否四开 
#define DAOCHA_ISFW(iStatus)	((iStatus)&DCST_FW)		// 是否反位
#define DAOCHA_ISDW(iStatus)	((iStatus)&DCST_DW)		// 是否定位 
#define DAOCHA_ISJC(iStatus)	((iStatus)==DCST_JC)	// 是否挤岔 
#define DAOCHA_ISLOCK(iStatus)	((iStatus)&DCST_DS)		// 是否单锁 
#define DAOCHA_ISOFF(iStatus)	((iStatus)&DCST_DF)		// 是否单封
	

class CDaoC: public CBaseElement
{
	DECLARE_SERIAL(CDaoC)
//Construtor
public:
	CDaoC();
	~CDaoC();

	//道岔类型
	enum _DaoChaType		
	{
		DT_GENERAL = 0,		//普通道岔
		DT_TUOGUIQI= 1		//脱轨器
	};



// Attributes
public:
	//static data, from file "yard.dat"
	CPoint m_deltaA;
	CPoint m_deltaB;
	CPoint m_deltaC;

	int	m_iIndex;

	int m_iALink;
	int m_iBLink;
	int m_iCLink;

	int	m_iType;
	CString	m_strName;

	//
	float CosAlpha;
    float SinAlpha; 
	float fSlope;



	int m_iRWCBand;
	
	//int m_iPrevRWCBand;
	//int m_iDir,m_iPrevDir;
	
	int m_iStatus;	//道岔状态
	
	BOOL bZoom;

	
// Operations
public:

	/* 是否四开 */
	BOOL IsSK() { return DAOCHA_ISSK(m_iStatus); }
	
	/* 是否反位 */
	BOOL IsFW() { return DAOCHA_ISFW(m_iStatus);}
	
	/* 是否定位 */
	BOOL IsDW() { return DAOCHA_ISDW(m_iStatus); }

	/* 是否挤岔 */
	BOOL IsJC() { return DAOCHA_ISJC(m_iStatus); }

	/* 是否单锁 */
	BOOL IsLocked() { return DAOCHA_ISLOCK(m_iStatus); }

	/* 是否单封 */
	BOOL IsOffed() { return DAOCHA_ISOFF(m_iStatus); }

// Overrides
public:
	void DrawSlf(CDC* pDC, int mDvcSta);
	int GetType() { return m_iType; }

public:
	void DrawDcc(CDC *pDC,/*int x,int y,*/int deltaX,int deltaY,int iClr,int iClr0,
		BOOL bIsCJ,BOOL bCXOnly);

private:
	/*
	 *	画普通道岔( _/_ )
	 */
	void DrawGeneralDC(CDC *pDC,BOOL bInfInvalid);
	
	/*
	 *	画脱轨器( ▲ )
	 */
	void DrawTGQ(CDC *pDC,BOOL bInfInvalid);
};

typedef CTypedPtrList<CObList,CDaoC*> CDaoCList;
#endif







