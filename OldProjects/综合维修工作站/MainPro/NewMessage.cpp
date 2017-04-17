// NewMessage.cpp: implementation of the CNewMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "maintain.h"
#include "NewMessage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CMaintainApp theApp;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNewMessage::CNewMessage()
{
	m_pHead = 0;
	m_wMsgNum = 0;
	m_strPathName = theApp.m_strExePath + NEWMESSAGEPATHNAME;
	ReadFile();
}

CNewMessage::~CNewMessage()
{
	WriteToFile();
	ClearList();
}

void CNewMessage::ClearList()
{
	NewMsgNode *cp,*np;
	cp = m_pHead;
	while(cp!=NULL)
	{
		np=cp->m_pNext;
		delete cp;
		cp=np;
	}
	//
	m_pHead = NULL;
	m_wMsgNum = 0;
	m_strPathName = "";
}

void CNewMessage::Add(const NewMsgNode &item)
{
	NewMsgNode *newPtr = new NewMsgNode;
	newPtr->m_strMsgKind = item.m_strMsgKind;
	newPtr->m_iOrder = item.m_iOrder;
	newPtr->m_tTime = item.m_tTime;
	newPtr->m_tSpeTime = item.m_tSpeTime;

	newPtr->m_pNext = NULL;

	//若头指针为空，则将头指针指向当前结点
	if( m_pHead==NULL )
	{
		m_pHead = newPtr;
	}
	else//头指针不为空，则找到单链表的末尾，并将当前结点加入到末尾.
	{
		NewMsgNode *p = m_pHead;
		while(p->m_pNext!=NULL)
		{
			p = p->m_pNext;
		}
		p->m_pNext = newPtr;
	}
	//
	m_wMsgNum++;	//消息数加一

	
}

BOOL CNewMessage::ReadFile()
{
	CFile fp;
	CString strLine;
	if(	!fp.Open(m_strPathName,CFile::modeRead | CFile::shareDenyNone) )
	{
		return FALSE;
	}
	CArchive ar(&fp,CArchive::load);
	//记录总数
	WORD dwTotalNum;
	ar>>dwTotalNum;
	//
	NewMsgNode pNode;
	for ( WORD i = 0; i<dwTotalNum; i++ )
	{
		ar >> pNode.m_strMsgKind >> pNode.m_iOrder >> pNode.m_tTime >> pNode.m_tSpeTime;
		Add(pNode);
	}
	
	//关闭文件
	ar.Close();
	fp.Close();
	//-----------------------------------------
	return TRUE;

}

BOOL CNewMessage::WriteToFile()
{
	//-------------------------------------------------------
	CFile fp;

	if(	!fp.Open(m_strPathName,CFile::modeCreate | CFile::shareDenyNone | CFile::modeWrite) )
	{
		return FALSE;
	}
	CArchive ar(&fp,CArchive::store);
	//写入记录总数
	ar<<m_wMsgNum;
	//
	NewMsgNode* pNode;
	for ( DWORD i = 0; i<m_wMsgNum; i++ )
	{
		pNode = GetAt(i);
		ar << pNode->m_strMsgKind << pNode->m_iOrder << pNode->m_tTime << pNode->m_tSpeTime;
	}
	//关闭文件
	ar.Close();
	fp.Close();
	//-----------------------------------------
	return TRUE;
}

NewMsgNode* CNewMessage::GetAt(const int &iIndex)
{
	NewMsgNode* cp = m_pHead;
	for (WORD i=0; i<m_wMsgNum; i++ )
	{
		if ( i == iIndex )
		{
			return cp;
		}
		cp = cp->m_pNext;
	}
	return NULL;
}

int CNewMessage::GetLength()
{
	return m_wMsgNum;
}

void CNewMessage::DeleteItem(const int &iIndex)
{
	NewMsgNode*		p = m_pHead;	//指向后继结点
	NewMsgNode*		fp = m_pHead;	//前驱结点的指针
	int i = 0;

	while ( p != NULL )
	{
		if ( i == iIndex )//找到了要删除的结点
		{

			if ( p == m_pHead )//根据要删除的结点是否为表头结点进行不同的处理
			{
				m_pHead = p->m_pNext;
				//fp = m_pHead;
			}
			else
			{
				fp->m_pNext = p->m_pNext;
			}
			delete p;
			//记录数减一
			m_wMsgNum -- ;
			return;
		}

		//-------------------
		fp = p;
		p = p->m_pNext;
		//
		i++;
	}
}
