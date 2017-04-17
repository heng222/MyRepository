// AnN.h

// Draw AnNiu
#if !defined _ANN_h_
#define _ANN_h_


#include "BaseElement.h"


#define AN_HEIGHT   10
#define AN_WIDTH    10

class AFX_EXT_CLASS CAnN : public CBaseElement
{
	DECLARE_SERIAL(CAnN)
		
public:
	CAnN();
	~CAnN();

	enum ButtonType
	{	BTN_TYPE_LA = 0x01	/*列车按钮类型*/,
		BTN_TYPE_DA = 0x02	/*调车按钮类型*/,
		BTN_TYPE_CA = 0x03	/*道岔按钮类型*/,
		BTN_TYPE_YA = 0x21	/*引导按钮*/
	};

// Attibutes
public:
	
	int			m_iType;
	int			m_iCommandID;
	CString		m_strName;

	int m_iRelate1,m_iRelate2,m_deltaX,m_deltaY;
	BOOL m_bShow,m_bHidAble;

	/*
	 *	m_iType为BTN_TYPE_CA时，相应的道岔状态。
	 */
	BYTE	m_byDCStatus;
	

// Operations
public:
	void DrawSlf(CDC* pDC,int mDvcSta);
	void ShowName(CDC *pDC,int iState);
	int GetCommandID() { return m_iCommandID;}
	int GetType() { return m_iType;	}
};

typedef CTypedPtrList<CObList,CAnN*> CAnNList;

#endif//