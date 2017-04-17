// BaseElement.h: interface for the CBaseElement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEELEMENT_H__B85C7E94_BF8D_4A69_B70E_B095E535E54C__INCLUDED_)
#define AFX_BASEELEMENT_H__B85C7E94_BF8D_4A69_B70E_B095E535E54C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CLR_INVALIDATE	LIGHTGRAY	//��Чʱ����ʾ��ɫ
#include "Color.h"
#include <math.h>
#include <afxtempl.h>

enum DeviceState/*�豸״̬*/
{
	DS_COMM		/*��ͨ*/,	
	DS_DOWN		/*����*/, 
	DS_FLASH	/*��˸*/,
	DS_HIDE		/*����ʾ*/,
	DS_INVALID	/*��Ч*/
};

enum NameState/*����״̬*/
{
	NS_COMM		/*��ͨ*/,
	NS_HIDE		/*����ʾ*/,
	NS_QGJ		/*���ʽ�*/,
	NS_SGNAME	/*��վ����*/,
	NS_MPNAME	/*��վ����*/,
	NS_INVALID
};

/*
	վ��ͼ�豸����
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
	 *	����CommandIDֵ
	 */
	virtual int GetCommandID();
	/*
	 *	��ʾ���豸��ص�����
	 */
	virtual void ShowName(CDC* pDC,int iState);
	
	/*
	 	��ָ����DC���Ի�
		pDC:	�豸����
		mDvcSta: ����״̬
	 */
	virtual void DrawSlf(CDC* pDC,int mDvcSta);

};

#endif // !defined(AFX_BASEELEMENT_H__B85C7E94_BF8D_4A69_B70E_B095E535E54C__INCLUDED_)
