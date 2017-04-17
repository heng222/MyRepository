#if !defined _PINGMUHANZI_H
#define _PINGMUHANZI_H


// Draw HanZi
#include "BaseElement.h"

class CHanZ : public CBaseElement
{
	DECLARE_SERIAL(CHanZ)
	
public:
	CHanZ();

// Attributes
public:

	BOOL m_bHidAble;
	CString m_strText;

// Operations
public:
	void DrawHZ(CDC *pDC,BOOL bInfInvalid,BOOL bShrink,BOOL bShow);

	void DrawSlf(CDC*pDC,int mDvcSta);
//Implenent
public:
	~CHanZ();
};
typedef CTypedPtrList<CObList,CHanZ*> CHanZList;
#endif