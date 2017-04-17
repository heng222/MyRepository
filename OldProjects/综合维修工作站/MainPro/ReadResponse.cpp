// ReadResponse.cpp: implementation of the CReadResponse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "maintain.h"
#include "ReadResponse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CMaintainApp theApp;
CReadResponse::CReadResponse()
{
	m_pHead = NULL;
	m_dwResNum = 0;
	m_strPathName = theApp.m_strExePath+RESPONSEINFPATHNAME+CTime::GetCurrentTime().Format("%Y-%m-%d");
}

CReadResponse::~CReadResponse()
{
	ClearList();
}

BOOL CReadResponse::ReadFile(CString strPathName)
{
	if (!strPathName.IsEmpty())
	{
		m_strPathName = strPathName;
	}
	
	//-------------------------------------------------------
	CFile fp;
	CString strLine;
	if(	!fp.Open(m_strPathName,CFile::modeRead | CFile::shareDenyNone) )
	{
		return FALSE;
	}
	CArchive ar(&fp,CArchive::load);
	//记录总数
	DWORD dwTotalNum;
	ar>>dwTotalNum;
	//
	ResponseNode pNode;
	for ( DWORD i = 0; i<dwTotalNum; i++ )
	{
		ar >> pNode.dwOrder >> pNode.strStationName >> pNode.tTime >> pNode.strReceiver;
		Add(pNode);
	}
	//m_dwResNum = dwTotalNum;
	//关闭文件
	ar.Close();
	fp.Close();
	//-----------------------------------------
	return TRUE;
}

void CReadResponse::Add(const ResponseNode &item)
{
	ResponseNode *newPtr = new ResponseNode;
	newPtr->dwOrder = item.dwOrder;
	newPtr->strStationName = item.strStationName;
	newPtr->tTime = item.tTime;
	newPtr->strReceiver = item.strReceiver;

	newPtr->Next = NULL;

	//若头指针为空，则将头指针指向当前结点
	if( m_pHead==NULL )
	{
		m_pHead = newPtr;
	}
	else//头指针不为空，则找到单链表的末尾，并将当前结点加入到末尾.
	{
		ResponseNode *p = m_pHead;
		while(p->Next!=NULL)
		{
			p = p->Next;
		}
		p->Next = newPtr;
	}
	//
	m_dwResNum ++;
}

BOOL CReadResponse::WriteFile(CString strPathName)
{
	if (!strPathName.IsEmpty())
	{
		m_strPathName = strPathName;
	}
	//-------------------------------------------------------
	CFile fp;
	CString strLine;
	if(	!fp.Open(m_strPathName,CFile::modeCreate | CFile::shareDenyNone | CFile::modeWrite) )
	{
		return FALSE;
	}
	CArchive ar(&fp,CArchive::store);
	//写入记录总数
	ar<<m_dwResNum;
	//
	ResponseNode* pNode;
	for ( DWORD i = 0; i<m_dwResNum; i++ )
	{
		pNode = GetAt(i);
		ar << pNode->dwOrder << pNode->strStationName << pNode->tTime << pNode->strReceiver;
	}
	//关闭文件
	ar.Close();
	fp.Close();
	//-----------------------------------------
	return TRUE;
}

void CReadResponse::ClearList()
{
	ResponseNode *cp,*np;
	cp=m_pHead;
	while(cp!=NULL)
	{
		np=cp->Next;
		delete cp;
		cp=np;
	}
}

ResponseNode* CReadResponse::GetAt(const DWORD &iIndex)
{
	ResponseNode* cp = m_pHead;
	for (DWORD i=0; i<m_dwResNum; i++ )
	{
		if (i==iIndex)
		{
			return cp;
		}
		cp = cp->Next;
	}
	return NULL;
}

DWORD CReadResponse::GetLength()
{
	return m_dwResNum;
}

void CReadResponse::Add(DWORD dwOrder, CString strStationName, COleDateTime resTime,CString sRever)
{
	ResponseNode item;
	item.dwOrder = dwOrder;
	item.strStationName = strStationName;
	item.tTime = resTime;
	item.strReceiver = sRever;
	//
	Add(item);
}
