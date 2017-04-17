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


//操作员信息类:主要存放操作员的姓名，密码，权限(三种信息都不能为空)信息，并完成
//从文件读取信息或把信息存入文件
struct OperatorNode
{
	CString		strName;		//操作员名字
	CString		strPassword;	//操作员密码

	/* iKind定义
		1: 管理员。
		2: 一般用户	
	*/
	int			iKind;			//操作员权限
};

class COperatorInf : public CObject  
{
public:
	
	COperatorInf(CString strFileName = "");
	virtual ~COperatorInf();

public:
	//更改用户密码
	void ModifyUserPassword(CString strName,CString strPassword);

	//删除用户
	void DelUser(CString strName);
	
	//查找用户strName,用户信息存入sOperator中返回
	void FindUser(CString strName,OperatorNode& sOperator);
	
	//返回数组存储中下标为iIndex的用户的名字
	CString GetName(int iIndex);
	
	//得到用户总数
	int GetLength();

	//是否存在用户strName,存在返回其密码，不存在返回空字符串
	CString IsExistUser(CString strName);
	
	//设置全路径
	void SetPathName(CString strPathName);

	//新增一元素
	void Add(const OperatorNode& item);
	//将Administrator加入
	void AddAdministrator();
	
	//清空链表
	void ClearList();
	
	//将信息写入文件
	BOOL WriteFile(CString strFileName = "");
	
	//从文件读取信息
	BOOL ReadFile(CString strFileName = "");

private:
	OperatorNode*	m_pVector[OPERATORMAXNUM];		//头指针数组
	int				m_iOperatorNum;					//操作员实际个数
	CString			m_strPathName;					//文件的全路径
};

#endif // !defined(AFX_OPERATORINF_H__ABCC27C3_3BE5_4C08_ACDB_E4110C90D38F__INCLUDED_)
