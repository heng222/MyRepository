// ReadMendTemplate.h: interface for the CReadMendTemplate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_READMENDTEMPLATE_H__3B9CAA11_23AF_4C94_8D9C_8163DBF0CF6B__INCLUDED_)
#define AFX_READMENDTEMPLATE_H__3B9CAA11_23AF_4C94_8D9C_8163DBF0CF6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*##############################################
				��ʩ��ģ����
	##############################################*/
struct MendNode
{
	BYTE		byOrder;			//ʩ����������(== ֡��ʽ�е����)
	CString		strName;			//ʩ�����������
	CString		strCloseContent;	//��صľ����������
	CString		strOpenContent;		//��صľ��忪ͨ����

	MendNode*	Next;			//ָ����һ�����
};
//--------------------------------------
class CReadMendTemplate : public CObject  
{
public:
	//����ʩ����Ż����ֵõ�ָ���ķ�����ͨ����
	CString GetContent(const CString& strName,BOOL bIsClose);
	CString GetContent(int iOrder,BOOL bIsClose);

	//����ʩ�����ֵõ������
	int GetOrder(const CString& strName);
	//����ʩ���������ŵõ�������
	CString GetName(const int& iOrder);

	void Add(MendNode& item);
	
	BOOL ReadFile(LPCSTR lpFileName);
	//---------------------------------
public:
	CReadMendTemplate(CString strPathName = "" );
	virtual ~CReadMendTemplate();

private:
	CString		m_strPathName;
	MendNode*	m_pHead;
};

#endif // !defined(AFX_READMENDTEMPLATE_H__3B9CAA11_23AF_4C94_8D9C_8163DBF0CF6B__INCLUDED_)
