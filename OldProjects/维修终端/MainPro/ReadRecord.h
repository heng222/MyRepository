// ReadRecord.h: interface for the CReadRecord class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_READRECORD_H__AF1168FF_CE7B_49D8_9A5D_63236AC8FF36__INCLUDED_)
#define AFX_READRECORD_H__AF1168FF_CE7B_49D8_9A5D_63236AC8FF36__INCLUDED_

#include "Maintain.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/* ###################################################################################
����������ȡʩ����¼
####################################################################################��*/

class CReadRecord : public CObject  
{
protected:
	DECLARE_SERIAL(CReadRecord)
public:
	void ClearPArray();
	//���ؼ�¼��ŵľ���·��
	CString GetPathName();

	//����strKey��strItem�õ�Order(Base 1)
	int GetOrderByDT(CString strKey, CString strItem);

	//ɾ�����еļ�¼
	void DeleteAllRecord();
	//ɾ��ָ���ļ�¼
	void DeleteRecord(BYTE byIndex);
	
	//�õ������ø��ı�־
	void SetModified(BOOL bFlag=TRUE);
	BOOL GetModified();

	//�õ�һ���ļ��еļ�¼��
	BYTE GetRecordNum();

	//�õ���byIndex,strKeyָ����ӳ������Ԫ��ֵ(BASE 1)
	CString GetValue(BYTE byIndex, const CString strKey) const;
	//����byIndexӳ�����ֵ
	void SetValue(BYTE byIndex, const CString strKey, const int iItem);
	void SetValue(BYTE byIndex,const CString strKey,const CString strItem);

	//��ָ����·����дʩ����¼
	BOOL ReadRecords(LPCSTR lpcstrFileName = '\0');
	BOOL WriteRecords(LPCSTR lpFileName = '\0');

	CReadRecord(CString strPathName = "");
	virtual ~CReadRecord();

private:
	BOOL		m_bModified;		//��¼���Ӵ򿪺���û�н��и���
	BYTE		m_byRecordNum;		//һ���е�ʵ�ʼ�¼��
	CString		m_strPathName;		//��ű���¼���ڵ�·��
	
	CMapStringToString*		m_pRecordMap[RECORDMAXNUM];		//��¼ӳ��ָ������

};

#endif // !defined(AFX_READRECORD_H__AF1168FF_CE7B_49D8_9A5D_63236AC8FF36__INCLUDED_)
