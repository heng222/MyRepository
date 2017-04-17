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
	CString			m_strMsgKind;		//消息种类
	int				m_iOrder;			//序号
	COleDateTime	m_tTime;			//相应的时间（同消息种类有关）
										//施工登销记时间或施工封锁开通命令的发令时间
	
	COleDateTime	m_tSpeTime;			//调度命令中相应的登销记时间

	NewMsgNode*	m_pNext;
};
//尚未查看的新消息
class CNewMessage : public CObject  
{
/*public:
	enum MsgKind
	{
			ConstReg = 1,		//施工登记
			ConstClose,			//施工消记
			CmdOpen,			//开通命令
			CmdClose			//封锁命令
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
	WORD			m_wMsgNum;			//新消息的个数
	CString			m_strPathName;		//

private:
	BOOL WriteToFile();

	BOOL ReadFile();
};

#endif // !defined(AFX_NEWMESSAGE_H__1F4C8C95_04A4_4C67_9107_B873E03D0426__INCLUDED_)
