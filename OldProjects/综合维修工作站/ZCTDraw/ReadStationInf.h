// ReadStationInf.h: interface for the CReadStationInf class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_READSTATIONINF_H__F0523364_9A30_469C_A795_8FFBE5EF36F9__INCLUDED_)
#define AFX_READSTATIONINF_H__F0523364_9A30_469C_A795_8FFBE5EF36F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommFunction.h"

/*#####################################################################
			������г�վ��վ�롢�����Լ�����·������Ϣ
######################################################################*/

struct AFX_EXT_CLASS StationNode
{
	friend class CReadStationInf;
public:
	int			iIndex;				//���

	/*  ---- ��վ������Ϣ ---------*/
	int			iStationID;			//��վ��վ��
	CString		strName;			//��վ������
	CString		strDirectory;		//��վվ��ͼ��Ϣ���ڵ����·��

	/* ------����������վ��վ��----*/
	int			iUpStationID[2];		//��������վվ��
	int			iDownStationID[2];		//��������վվ��

private:
	StationNode* Next;				//��һ����ָ��
};
//----------------------------------
class AFX_EXT_CLASS CReadStationInf : public CObject  
{
protected:
		CReadStationInf();
		virtual ~CReadStationInf();
		
public:
	static void ReleaseInstance();
	static CReadStationInf* GetInstance() ;
	static void SetActiveStation(int iActStaID) { _iActiveStationID = iActStaID;}
	static int  GetActiveStation() { return _iActiveStationID;}

	//�õ���iIndex��Ԫ�ص�ָ��
	StationNode* GetAt(int iIndex) const;

	//ͨ��վ��õ���վ�Ľṹ��Ϣ
	StationNode* GetItem(int iStationID) const;
	
	//��������ĳ���
	int GetLength() const;
	

	//��վ���б�ת��Ϊ�����б���ǽ������б�ת��Ϊվ���б�
	//SComPart ָ��strName��strNum��Դ���ķָ���
	//DComPart ָ��strNum��strName��Ŀ���ַ����ķָ���
	CString CovNameToNum(CString strName, char SComPart = ',', char DComPart = '/' ) const;
	CString CovNumToName(CString strNum,  char SComPart = '/', char DComPart = ',' ) const;

	//��յ�����
	void	ClearList();


	//���ݳ�վ�����ֵõ���վ��վ��
	WORD	GetStationID(LPCSTR strName) const;
	/*
	 *	������ŵõ���վ��վ��
	 */
	WORD	GetStationID(int iOrder) const;

	//���ݳ�վ��վ��������ŵõ���վ������
	/*
		Par: bFlagΪTRUEʱ������վ��õ�վ����ΪFALSEʱ������ŵõ�վ��
	*/
	CString GetName(const WORD& wStationNo,BOOL byStationID = TRUE) const;


	/*���ݳ�վ��վ������Ƶõ���վ��Ϣ���ڵ��ļ���λ��
		bAbsolute :
			TRUE: ���ؾ���·��
			FALSE:�������·��
	*/
	CString GetDirectory(const WORD& wStationNo,BOOL bAbsolute = TRUE) const;
	CString GetDirectory(const CString& strStationName,BOOL bAbsolute = TRUE) const;



private:
	//���ļ��ж�ȡ��վ����Ϣ
	BOOL	ReadFile(LPCSTR lpFileName = '\0');

	/*
	 *	
	 */
	void	Add(const StationNode& item);

private:
	//CString	m_strPath;		//վ����Ϣ�ļ�����·��

	StationNode*	m_pHead;
	WORD			m_wStationNum;	//�����г�վ����Ŀ

private:
	static CReadStationInf*	_pInstance;
	static int		_iActiveStationID;//��ǰ������ʾ״̬��վ��ͼID

};

#endif // !defined(AFX_READSTATIONINF_H__F0523364_9A30_469C_A795_8FFBE5EF36F9__INCLUDED_)
