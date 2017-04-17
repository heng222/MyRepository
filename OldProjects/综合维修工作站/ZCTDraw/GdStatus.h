//CGdStatus.h
#if !defined(AFX_CGdStatus_H__FA2B0348_C9DA_470D_BF28_DFF783ECAC51__INCLUDED_)
#define AFX_CGdStatus_H__FA2B0348_C9DA_470D_BF28_DFF783ECAC51__INCLUDED_

#include "BaseElement.h"
#define  GDLIGHTRADIUS	7	//股道封锁灯的半径
// 股道封锁灯的绘制
class CGdStatus : public CBaseElement
{
	DECLARE_SERIAL(CGdStatus)
public:
	CGdStatus();
	~CGdStatus();

// Attibutes
public:
	int			m_iCommandID;	//ID
	CString		m_strName;		//名称
	
// Overrides
public:
	void DrawSlf(CDC *pDC,int mDvcSta);
	int GetCommandID() { return m_iCommandID;}
	BOOL PtInDevice(CDC* pDC,CPoint pt,int iDeviceType);

// Operation	
public:
	void SetLockSta(BOOL bLock) { m_bLock = bLock;}
	BOOL GetLockSta() {return m_bLock;}

private:
	BOOL	m_bLock;			//是否处于封锁状态
};
typedef CTypedPtrList<CObList,CGdStatus*> CGdStatusList;

#endif