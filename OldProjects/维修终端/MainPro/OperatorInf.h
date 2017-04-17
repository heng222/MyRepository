// OperatorInf.h: interface for the COperatorInf class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPERATORINF_H__ABCC27C3_3BE5_4C08_ACDB_E4110C90D38F__INCLUDED_)
#define AFX_OPERATORINF_H__ABCC27C3_3BE5_4C08_ACDB_E4110C90D38F__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//################################################################################
#include "Maintain.h"	// Added by ClassView


//����Ա��Ϣ��:��Ҫ��Ų���Ա�����������룬Ȩ��(������Ϣ������Ϊ��)��Ϣ�������
//���ļ���ȡ��Ϣ�����Ϣ�����ļ�
struct OperatorNode
{
	CString		strName;		//����Ա����
	CString		strPassword;	//����Ա����

	/* iKind����
		1: ����Ա��
		2: һ���û�	
	*/
	int			iKind;			//����ԱȨ��
};

class COperatorInf : public CObject  
{
public:
	
	COperatorInf(CString strFileName = "");
	virtual ~COperatorInf();

public:
	//�����û�����
	void ModifyUserPassword(CString strName,CString strPassword);

	//ɾ���û�
	void DelUser(CString strName);
	
	//�����û�strName,�û���Ϣ����sOperator�з���
	void FindUser(CString strName,OperatorNode& sOperator);
	
	//��������洢���±�ΪiIndex���û�������
	CString GetName(int iIndex);
	
	//�õ��û�����
	int GetLength();

	//�Ƿ�����û�strName,���ڷ��������룬�����ڷ��ؿ��ַ���
	CString IsExistUser(CString strName);
	
	//����ȫ·��
	void SetPathName(CString strPathName);

	//����һԪ��
	void Add(const OperatorNode& item);
	//��Administrator����
	void AddAdministrator();
	
	//�������
	void ClearList();
	
	//����Ϣд���ļ�
	BOOL WriteFile(CString strFileName = "");
	
	//���ļ���ȡ��Ϣ
	BOOL ReadFile(CString strFileName = "");

private:
	OperatorNode*	m_pVector[OPERATORMAXNUM];		//ͷָ������
	int				m_iOperatorNum;					//����Աʵ�ʸ���
	CString			m_strPathName;					//�ļ���ȫ·��
};

#endif // !defined(AFX_OPERATORINF_H__ABCC27C3_3BE5_4C08_ACDB_E4110C90D38F__INCLUDED_)
