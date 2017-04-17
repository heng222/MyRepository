// JYJ.H

//Draw JueYuanjie 
#ifndef _JYJ_H
#define _JYJ_H
//////////////////////////////////////////////////////////////////////////

#include "BaseElement.h"
class CJYJ : public CBaseElement
{
	DECLARE_SERIAL(CJYJ)

public:
	CJYJ();

// Attributes
public:
	int m_iType;
	CPoint m_pt1,m_pt2;


// Overrides
public:
	void DrawSlf(CDC *pDC,int mDvcSta);
	int GetType() { return m_iType;	}


// Operations
public:
	~CJYJ();
};
typedef CTypedPtrList<CObList,CJYJ*> CJYJList;

//////////////////////////////////////////////////////////////////////////
#endif