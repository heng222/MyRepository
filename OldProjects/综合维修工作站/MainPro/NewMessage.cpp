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

	//��ͷָ��Ϊ�գ���ͷָ��ָ��ǰ���
	if( m_pHead==NULL )
	{
		m_pHead = newPtr;
	}
	else//ͷָ�벻Ϊ�գ����ҵ��������ĩβ��������ǰ�����뵽ĩβ.
	{
		NewMsgNode *p = m_pHead;
		while(p->m_pNext!=NULL)
		{
			p = p->m_pNext;
		}
		p->m_pNext = newPtr;
	}
	//
	m_wMsgNum++;	//��Ϣ����һ

	
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
	//��¼����
	WORD dwTotalNum;
	ar>>dwTotalNum;
	//
	NewMsgNode pNode;
	for ( WORD i = 0; i<dwTotalNum; i++ )
	{
		ar >> pNode.m_strMsgKind >> pNode.m_iOrder >> pNode.m_tTime >> pNode.m_tSpeTime;
		Add(pNode);
	}
	
	//�ر��ļ�
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
	//д���¼����
	ar<<m_wMsgNum;
	//
	NewMsgNode* pNode;
	for ( DWORD i = 0; i<m_wMsgNum; i++ )
	{
		pNode = GetAt(i);
		ar << pNode->m_strMsgKind << pNode->m_iOrder << pNode->m_tTime << pNode->m_tSpeTime;
	}
	//�ر��ļ�
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
	NewMsgNode*		p = m_pHead;	//ָ���̽��
	NewMsgNode*		fp = m_pHead;	//ǰ������ָ��
	int i = 0;

	while ( p != NULL )
	{
		if ( i == iIndex )//�ҵ���Ҫɾ���Ľ��
		{

			if ( p == m_pHead )//����Ҫɾ���Ľ���Ƿ�Ϊ��ͷ�����в�ͬ�Ĵ���
			{
				m_pHead = p->m_pNext;
				//fp = m_pHead;
			}
			else
			{
				fp->m_pNext = p->m_pNext;
			}
			delete p;
			//��¼����һ
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
