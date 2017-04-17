// JT.h

// Draw JinTouXian

#define JT_HALF_H       5  /* half height of the JinTou iamge */
#define JT_W            6  /* width of the JinTou iamge */

#include "BaseElement.h"

class CJT : public CBaseElement
{
	DECLARE_SERIAL(CJT)

public:
	CJT();

// Attributes
public:
	int m_iType;
	int m_iDir;

// Overrides
public:
	void DrawSlf(CDC *pDC,int mDvcSta);
	int GetType(){ return m_iType;}

//Implements
public:
	~CJT();
};
typedef CTypedPtrList<CObList,CJT*> CJTList;

