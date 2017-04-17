//WcQD.h

// Draw WuChaQuanDuan

#ifndef _CWcQD
#define _CWcQD

#include "BaseElement.h"

class CWcQD : public CBaseElement
{
    DECLARE_SERIAL(CWcQD)
public:
	CWcQD();
    virtual ~CWcQD();

// Attributes
public:
//	int			m_iType;
	CString		m_strName;

	CPoint m_pt1;
	CPoint m_pt2;
    int m_iIndex;
	int m_iCommandID;
	//bool m_bHidAble;
	bool m_bCanQGJ;
	bool m_bCanPlQGJ;
	
	int m_iStatus;

// Operations
public:

// Overrides
public:
	void DrawSlf (CDC *pDC,int iDevSta);
	void ShowName(CDC *pDC,int iNameSta);
	int GetCommandID(){return m_iCommandID;};
};
typedef CTypedPtrList<CObList,CWcQD*> CWcQDList;

#endif



