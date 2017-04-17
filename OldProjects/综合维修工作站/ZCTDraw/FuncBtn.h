//CFuncBtn.h
#ifndef _FUNCTIONBTN_H
#define _FUNCTIONBTN_H


#include "BaseElement.h"

#define   FUNBTNRADIUS	7	//功能按钮半径

// 桌面功能按钮的绘制
class CFuncBtn : public CBaseElement
{
	DECLARE_DYNCREATE(CFuncBtn)

public:
	enum FuncBtnCommandID{
		ZDW=1/*总定位*/,		ZFW=2/*总反位*/,			DS=3/*单锁*/,	
		DJ=4/*单解*/,			DF=5/*单封*/,				JF=6/*解封*/,
		PDJS=8/*坡道解锁*/,		QGJ=9/*区故解*/,			ZQX=10/*总取消*/,	
		ZRJ=11/*总人解*/,		QCAN=12/*清除按钮*/,		XYZS=13/*下引总锁*/,
		SYZS=14/*上引总锁*/,	XTDHF=16/*X停电恢复按钮*/,	STDHF=17/*S停电恢复按钮*/,
		CKXH=18/*重开信号按钮*/,JLSP=19/*进路试排按钮*/,	PLJL=20/*排列进路按钮*/,
		GDFS=99/*股道封锁*/,	QJFS=100/*区间封锁*/
	};//功能按钮ID声明

	CFuncBtn();
	~CFuncBtn();

// Attibutes
public:
	int			m_iType;
	int			m_iCommandID;
	int			m_iOffset;
	//int			m_iClr0,m_iClr1;

	int			m_Index;
	CString		m_strName;
	
	int		m_iStatus;	//按钮状态

// Overrides
public:
	void DrawSlf(CDC *pDC,int mDvcSta);
	int GetCommandID() {return m_iCommandID;}
	int GetType() { return m_iType;}
	BOOL PtInDevice(CDC* pDC,CPoint pt,int iDeviceType);
// Operation
public:
};
typedef CTypedPtrList<CObList,CFuncBtn*> CFuncBtnList;

#endif