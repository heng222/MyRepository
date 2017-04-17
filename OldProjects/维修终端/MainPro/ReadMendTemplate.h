// ReadMendTemplate.h: interface for the CReadMendTemplate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_READMENDTEMPLATE_H__3B9CAA11_23AF_4C94_8D9C_8163DBF0CF6B__INCLUDED_)
#define AFX_READMENDTEMPLATE_H__3B9CAA11_23AF_4C94_8D9C_8163DBF0CF6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*##############################################
				读施工模板类
	##############################################*/
struct MendNode
{
	BYTE		byOrder;			//施工种类的序号(== 帧格式中的序号)
	CString		strName;			//施工种类的名字
	CString		strCloseContent;	//相关的具体封锁内容
	CString		strOpenContent;		//相关的具体开通内容

	MendNode*	Next;			//指向下一个结点
};
//--------------------------------------
class CReadMendTemplate : public CObject  
{
public:
	//根据施工序号或名字得到指定的封锁或开通内容
	CString GetContent(const CString& strName,BOOL bIsClose);
	CString GetContent(int iOrder,BOOL bIsClose);

	//根据施工名字得到其序号
	int GetOrder(const CString& strName);
	//根据施工种类的序号得到其名字
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
