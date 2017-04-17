// ReadMendTemplate.cpp: implementation of the CReadMendTemplate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "maintain.h"
#include "ReadMendTemplate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReadMendTemplate::CReadMendTemplate(CString strPathName/*=""*/)
{
	m_pHead = NULL;
	if ( !strPathName.IsEmpty() )
	{
		m_strPathName = strPathName;
		ReadFile(strPathName);
	}
}

CReadMendTemplate::~CReadMendTemplate()
{
	MendNode *cp,*np;
	cp=m_pHead;
	while(cp!=NULL)
	{
		np=cp->Next;
		delete cp;
		cp=np;
	}
	//
	m_pHead = NULL;
}

BOOL CReadMendTemplate::ReadFile(LPCSTR lpFileName)
{
	CStdioFile fp;
	//用于检测指定的文件是否存在
	if(!fp.Open(lpFileName,CFile::modeRead))
		//指定的文件不存在，则以当前的日期为文件名创建文件
	{
		return FALSE;
	}
	else//文件存在
	{
		fp.Close();
	}
	//--------------------------------------------
	m_strPathName = lpFileName;
	//施工种类的个数
	CString strApp;
	int iMendSum = GetPrivateProfileInt("MendKindSum","Sum",-1,lpFileName);
	//定义一个新结点
	MendNode newItem;
	char strLine[400];
	for (int i = 0; i<iMendSum; i++)
	{
		newItem.byOrder = i+1;

		strApp.Format("Order%d",i+1);
		//Name
		GetPrivateProfileString(strApp,"Name","Error",strLine,400,lpFileName);
		newItem.strName.Format("%s",strLine);
		//ContentClose
		GetPrivateProfileString(strApp,"ContentClose","Error",strLine,400,lpFileName);
		newItem.strCloseContent.Format("%s",strLine);
		//ContentOpen
		GetPrivateProfileString(strApp,"ContentOpen","Error",strLine,400,lpFileName);
		newItem.strOpenContent.Format("%s",strLine);
		//==============
		Add(newItem);
	}
	//--------------------------------------------
	return TRUE;
}

void CReadMendTemplate::Add(MendNode &item)
{
	MendNode *newPtr = new MendNode;
	newPtr->byOrder = item.byOrder;
	newPtr->strName = item.strName;
	newPtr->strCloseContent = item.strCloseContent;
	newPtr->strOpenContent = item.strOpenContent;

	newPtr->Next = NULL;

	//若头指针为空，则将头指针指向当前结点
	if( m_pHead==NULL )
	{
		m_pHead = newPtr;
	}
	else//头指针不为空，则找到单链表的末尾，并将当前结点加入到末尾.
	{
		MendNode *p = m_pHead;
		while(p->Next!=NULL)
		{
			p = p->Next;
		}
		p->Next = newPtr;
	}
}

CString CReadMendTemplate::GetName(const int &iOrder)
{
	MendNode *p = m_pHead;
	while( p!=NULL )
	{
		if(p->byOrder == iOrder)
		{
			return p->strName;
		}
		p = p->Next;
	}
	return "";
}

int CReadMendTemplate::GetOrder(const CString &strName)
{
	MendNode *p = m_pHead;
	while( p!=NULL )
	{
		if(p->strName.CompareNoCase(strName) == 0)
		{
			return p->byOrder;
		}
		p = p->Next;
	}
	return -1;
}

CString CReadMendTemplate::GetContent(int iOrder, BOOL bIsClose)
{
	MendNode *p = m_pHead;
	while( p!=NULL )
	{
		if(p->byOrder == iOrder )
		{
			if(bIsClose)
			{
				return p->strCloseContent;
			}
			else
			{
				return p->strOpenContent;
			}
		}
		p = p->Next;
	}
	return "";
}

CString CReadMendTemplate::GetContent(const CString &strName, BOOL bIsClose)
{
	MendNode *p = m_pHead;
	while( p!=NULL )
	{
		if(p->strName.CompareNoCase(strName) == 0 )
		{
			if(bIsClose)
			{
				return p->strCloseContent;
			}
			else
			{
				return p->strOpenContent;
			}
		}
		p = p->Next;
	}
	return "";
}
