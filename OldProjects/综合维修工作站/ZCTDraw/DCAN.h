// DCAN.h
#ifndef _DAOCHAAN_H
#define _DAOCHAAN_H

// Draw DaoChaAnNiu

#define DCHeight 6
#define DCWidth  12

#include "BaseElement.h"

class CDCAN : public CBaseElement
{
	DECLARE_SERIAL(CDCAN)

public:
	CDCAN();

// Attributes
public:
	//CPoint		m_pt;
	int			m_iType;
	int			m_iCommandID;
	CString		m_strName;

	int		m_QD_Index,m_DC_Index;
	char	m_DCText[7];
	char	m_QDName[17];

// Overrides
public:
	void ShowName(CDC* pDC,int iState);
	int GetCommandID()	{return m_iCommandID;}
	
	BOOL PtInDevice(CDC* pDC,CPoint pt,int iDeviceType);

// Implementation
public:
	~CDCAN();
};
typedef CTypedPtrList<CObList,CDCAN*> CDCANList;

#endif