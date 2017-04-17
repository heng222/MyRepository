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
此类用来读取施工记录
####################################################################################　*/

class CReadRecord : public CObject  
{
protected:
	DECLARE_SERIAL(CReadRecord)
public:
	void ClearPArray();
	//返回记录存放的绝对路径
	CString GetPathName();

	//根据strKey的strItem得到Order(Base 1)
	int GetOrderByDT(CString strKey, CString strItem);

	//删除所有的记录
	void DeleteAllRecord();
	//删除指定的记录
	void DeleteRecord(BYTE byIndex);
	
	//得到或设置更改标志
	void SetModified(BOOL bFlag=TRUE);
	BOOL GetModified();

	//得到一个文件中的记录数
	BYTE GetRecordNum();

	//得到由byIndex,strKey指定的映射对象的元素值(BASE 1)
	CString GetValue(BYTE byIndex, const CString strKey) const;
	//给第byIndex映射对象赋值
	void SetValue(BYTE byIndex, const CString strKey, const int iItem);
	void SetValue(BYTE byIndex,const CString strKey,const CString strItem);

	//从指定的路径读写施工记录
	BOOL ReadRecords(LPCSTR lpcstrFileName = '\0');
	BOOL WriteRecords(LPCSTR lpFileName = '\0');

	CReadRecord(CString strPathName = "");
	virtual ~CReadRecord();

private:
	BOOL		m_bModified;		//记录集从打开后有没有进行更改
	BYTE		m_byRecordNum;		//一天中的实际记录数
	CString		m_strPathName;		//存放本记录所在的路径
	
	CMapStringToString*		m_pRecordMap[RECORDMAXNUM];		//记录映射指针数组

};

#endif // !defined(AFX_READRECORD_H__AF1168FF_CE7B_49D8_9A5D_63236AC8FF36__INCLUDED_)
