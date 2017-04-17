//CQjStatus.h
#if !defined(AFX_CQjStatus_H__FA2B0348_C9DA_470D_BF28_DFF783ECAC51__INCLUDED_)
#define AFX_CQjStatus_H__FA2B0348_C9DA_470D_BF28_DFF783ECAC51__INCLUDED_


#define  QJLIGHTRADIUS	7	//��������ư뾶
// ��������ƵĻ���
#include "BaseElement.h"
class CQjStatus : public CBaseElement
{
	DECLARE_SERIAL(CQjStatus)
public:
	CQjStatus();
	~CQjStatus();

	
// Attibutes
public:
	int			m_iCommandID;	//����ID
	int			m_iStationNo1;	//վ��1
	int			m_iXHNo1;		//������

	int			m_iCommandID2;
	int			m_iStationNo2;
	int			m_iXHNo2;
	
	CString		m_strName;



// Overrides
public:
	void DrawSlf(CDC *pDC,int iDevSta);
	int GetCommandID() { return m_iCommandID;}

//// Operation
public:
	BOOL GetLockSta() { return m_bLock;}
	void SetLockSta( BOOL bLock) { m_bLock = bLock;}

private:

	BOOL		m_bLock;		//�Ƿ��ڷ���״̬
	
};
typedef CTypedPtrList<CObList,CQjStatus*> CQjStatusList;

#endif