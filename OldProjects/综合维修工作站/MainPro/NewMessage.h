// NewMessage.h: interface for the CNewMessage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEWMESSAGE_H__1F4C8C95_04A4_4C67_9107_B873E03D0426__INCLUDED_)
#define AFX_NEWMESSAGE_H__1F4C8C95_04A4_4C67_9107_B873E03D0426__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


struct NewMsgNode
{
	CString			m_strMsgKind;		//��Ϣ����
	int				m_iOrder;			//���
	COleDateTime	m_tTime;			//��Ӧ��ʱ�䣨ͬ��Ϣ�����йأ�
										//ʩ��������ʱ���ʩ��������ͨ����ķ���ʱ��
	
	COleDateTime	m_tSpeTime;			//������������Ӧ�ĵ�����ʱ��

	NewMsgNode*	m_pNext;
};
//��δ�鿴������Ϣ
class CNewMessage : public CObject  
{
/*public:
	enum MsgKind
	{
			ConstReg = 1,		//ʩ���Ǽ�
			ConstClose,			//ʩ������
			CmdOpen,			//��ͨ����
			CmdClose			//��������
	};
*/
public:
	CNewMessage();
	virtual ~CNewMessage();

public:

	void DeleteItem(const int & iIndex);
	
	int GetLength();

	NewMsgNode* GetAt(const int& iIndex);

	

	void Add(const NewMsgNode& item);

	void ClearList();
	

private:
	NewMsgNode*		m_pHead;
	WORD			m_wMsgNum;			//����Ϣ�ĸ���
	CString			m_strPathName;		//

private:
	BOOL WriteToFile();

	BOOL ReadFile();
};

#endif // !defined(AFX_NEWMESSAGE_H__1F4C8C95_04A4_4C67_9107_B873E03D0426__INCLUDED_)
