// BaseElement.h: interface for the CBaseElement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEELEMENT_H__B85C7E94_BF8D_4A69_B70E_B095E535E54C__INCLUDED_)
#define AFX_BASEELEMENT_H__B85C7E94_BF8D_4A69_B70E_B095E535E54C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CLR_INVALIDATE	LIGHTGRAY	//无效时的显示颜色
#include "Color.h"
#include <math.h>
#include <afxtempl.h>

enum DeviceState/*设备状态*/
{
	DS_COMM		/*普通*/,	
	DS_DOWN		/*按下*/, 
	DS_FLASH	/*闪烁*/,
	DS_HIDE		/*不显示*/,
	DS_INVALID	/*无效*/
};

enum NameState/*名称状态*/
{
	NS_COMM		/*普通*/,
	NS_HIDE		/*不显示*/,
	NS_QGJ		/*区故解*/,
	NS_SGNAME	/*单站名称*/,
	NS_MPNAME	/*多站名称*/,
	NS_INVALID
};

/*
	站场图设备基类
*/
class CBaseElement : public CObject  
{
public:
	CBaseElement();
	virtual ~CBaseElement();

public:
	
	CPoint		m_pt;
	//int			m_iType;
	//int			m_iCommandID;
	//CString		m_strName;

protected:
	//BOOL	m_bInvalidate;

public:
	virtual int GetType();
	/*
	 *	返回CommandID值
	 */
	virtual int GetCommandID();
	/*
	 *	显示与设备相关的名称
	 */
	virtual void ShowName(CDC* pDC,int iState);
	
	/*
	 	在指定的DC中自画
		pDC:	设备场景
		mDvcSta: 自身状态
	 */
	virtual void DrawSlf(CDC* pDC,int mDvcSta);

};

#endif // !defined(AFX_BASEELEMENT_H__B85C7E94_BF8D_4A69_B70E_B095E535E54C__INCLUDED_)
