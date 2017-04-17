// RailwayBureau.h: interface for the CRailwayBureau class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RAILWAYBUREAU_H__B5D28CBF_AB96_4B6D_AF57_A8472BE24F89__INCLUDED_)
#define AFX_RAILWAYBUREAU_H__B5D28CBF_AB96_4B6D_AF57_A8472BE24F89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Maintain.h"

#define		BUREAUMAXNUM	14
//路局，分局名字及其代码

struct BureauNode
{
	BYTE			byID;		//路局或分局代码
	CString			strName;	//名称

	BureauNode*		pNext;

};
class CRailwayBureau : public CObject  
{
public:
	BOOL ReadFile(const CString strFileName);
	void ClearMatrix();
public:
	WORD	GetSubBureauNumber(const int& iRoadID);
	CString GetSubBureauName(const int& iRoadID,const int& iSubID);
	CString GetRoadBureauName(const int& iID);
	WORD	GetBureauNumber();

	CRailwayBureau();
	virtual ~CRailwayBureau();

private:
	BureauNode*		m_pVector[BUREAUMAXNUM];
	BYTE			m_byBureauNum;	//保存路局个数

private:
	void AddItem(int iRowNo,BureauNode* item);
	
	void InitMatrix();
	
};

#endif // !defined(AFX_RAILWAYBUREAU_H__B5D28CBF_AB96_4B6D_AF57_A8472BE24F89__INCLUDED_)
