// NQD.h

//Draw WuDianLu_QuDuan 

#include "BaseElement.h"

class CNQD : public CBaseElement
{
	DECLARE_SERIAL(CNQD)

public:
	CNQD();

// Attributes
public:
	CPoint m_pt1;
	CPoint m_pt2;

// Overrides
public:
	void DrawSlf(CDC *pDC,int mDvcSta);


// Operations
public:
	~CNQD();
};
typedef CTypedPtrList<CObList,CNQD*> CNQDList;