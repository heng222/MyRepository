//CFuncBtn.h
#ifndef _FUNCTIONBTN_H
#define _FUNCTIONBTN_H


#include "BaseElement.h"

#define   FUNBTNRADIUS	7	//���ܰ�ť�뾶

// ���湦�ܰ�ť�Ļ���
class CFuncBtn : public CBaseElement
{
	DECLARE_DYNCREATE(CFuncBtn)

public:
	enum FuncBtnCommandID{
		ZDW=1/*�ܶ�λ*/,		ZFW=2/*�ܷ�λ*/,			DS=3/*����*/,	
		DJ=4/*����*/,			DF=5/*����*/,				JF=6/*���*/,
		PDJS=8/*�µ�����*/,		QGJ=9/*���ʽ�*/,			ZQX=10/*��ȡ��*/,	
		ZRJ=11/*���˽�*/,		QCAN=12/*�����ť*/,		XYZS=13/*��������*/,
		SYZS=14/*��������*/,	XTDHF=16/*Xͣ��ָ���ť*/,	STDHF=17/*Sͣ��ָ���ť*/,
		CKXH=18/*�ؿ��źŰ�ť*/,JLSP=19/*��·���Ű�ť*/,	PLJL=20/*���н�·��ť*/,
		GDFS=99/*�ɵ�����*/,	QJFS=100/*�������*/
	};//���ܰ�ťID����

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
	
	int		m_iStatus;	//��ť״̬

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