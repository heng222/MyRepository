// XinHJ.h

//Draw XinHaoJi

#ifndef _XINHAOJI_H
#define _XINHAOJI_H

#include "BaseElement.h"

#define iRJ 7        //
#define JHeight 7
#define RDeng 7

class CXinHJ : public CBaseElement
{
	DECLARE_SERIAL(CXinHJ)

public:
	enum XHJType//信号机类型
	{
		XT_INVALID = 0,	//无效
		XT_DIAOCHE = 2,	//调车信号机
		XT_LIECHE = 1	//列车信号机
	};

	enum XHJDirection//信号机方向
	{
		XD_LEFT = 1,	//左
		XD_RIGHT= 0		//右
	};

	CXinHJ();
	~CXinHJ();
	
// Attributes
public:
	int			m_iType;
	CString		m_strName;

	int m_iDir;
	
	int m_iForBidClr;
	int m_iLXIndex;	//信号机设备号
	int	m_iDXIndex;
	int m_iTx;
	int m_iTy;
	   
	//BOOL m_bHidAble;
	BOOL m_bHigh;
	
	int m_iStatus;
	BOOL bZoom;

// Operations
public:
	/*
	 *	 信号机是否处于闪烁状态
	 */
	BOOL GetFlashState();

// Overrides
public:
	void DrawSlf(CDC *pDC,int iDevState);
	void ShowName(CDC *pDC,int iNameState);
	int GetType() { return m_iType;	}


private:
	void MapLgtColor(BOOL bFlash,COLORREF& iClr1,COLORREF& iClr2);
};


typedef CTypedPtrList<CObList,CXinHJ*> CXinHJList;
#endif
