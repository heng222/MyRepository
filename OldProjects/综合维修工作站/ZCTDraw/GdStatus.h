//CGdStatus.h
#if !defined(AFX_CGdStatus_H__FA2B0348_C9DA_470D_BF28_DFF783ECAC51__INCLUDED_)
#define AFX_CGdStatus_H__FA2B0348_C9DA_470D_BF28_DFF783ECAC51__INCLUDED_

#include "BaseElement.h"
#define  GDLIGHTRADIUS	7	//�ɵ������Ƶİ뾶
// �ɵ������ƵĻ���
class CGdStatus : public CBaseElement
{
	DECLARE_SERIAL(CGdStatus)
public:
	CGdStatus();
	~CGdStatus();

// Attibutes
public:
	int			m_iCommandID;	//ID
	CString		m_strName;		//����
	
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
	BOOL	m_bLock;			//�Ƿ��ڷ���״̬
};
typedef CTypedPtrList<CObList,CGdStatus*> CGdStatusList;

#endif