// RailwayBureau.cpp: implementation of the CRailwayBureau class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "RailwayBureau.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRailwayBureau::CRailwayBureau()
{
	InitMatrix();
	m_byBureauNum = 0;
}

CRailwayBureau::~CRailwayBureau()
{
	ClearMatrix();
}

void CRailwayBureau::InitMatrix()
{
	for ( int i = 0; i<BUREAUMAXNUM; i++ )
	{
		m_pVector[i] = NULL;
	}
}

void CRailwayBureau::ClearMatrix()
{
	for ( int i = 0; i<m_byBureauNum; i++ )
	{
		BureauNode *cp = m_pVector[i];
		BureauNode *cq;

		while (cp != NULL)
		{
			
			cq = cp->pNext;
			delete cp;
			cp = cq;
			
		}

		m_pVector[i] = NULL;

	}
}

BOOL CRailwayBureau::ReadFile(const CString strFileName)
{
	CFile fp;
	//用于检测指定的文件是否存在
	if(!fp.Open(strFileName,CFile::modeRead))
		//指定的文件不存在，则以当前的日期为文件名创建文件
	{
		return FALSE;
	}
	else//文件存在
	{
		fp.Close();
	}

	//取出路局数目
	m_byBureauNum = GetPrivateProfileInt("路局数目","总数",0,strFileName);
	if ( m_byBureauNum > BUREAUMAXNUM || m_byBureauNum == 0)
	{
		MessageBox(NULL,"路局数目大于程序中所允许的最大个数!","Information",MB_ICONEXCLAMATION);
		return FALSE;
	}

	CString strKey;
	char sValue[255];
	
	for ( int i = 0; i<m_byBureauNum; i++ )
	{
		//取出当前路局
		strKey.Format("路局%d",i+1);
		GetPrivateProfileString(strKey,"分局","",sValue,255,strFileName);
		BureauNode* newNode = new BureauNode;
		newNode->byID = i+1;
		newNode->strName = GetSFStr(sValue,0,',');
		newNode->pNext = NULL;
		AddItem(i,newNode);
		
		//依次取出当前路局下的各分局
		WORD wNumber = GetItemSum(sValue,',');
		for ( int j = 0; j<wNumber; j++ )
		{
			newNode = new BureauNode;
			newNode->byID = j+1;
			newNode->strName = GetSFStr(sValue,j,',');

			newNode->pNext = NULL;
			AddItem(i,newNode);
		}
	}
	//
	return TRUE;
}

/*
	得到路局数目
*/
WORD CRailwayBureau::GetBureauNumber()
{
	return m_byBureauNum;
}

/*
	得到代码为iID的路局的名称
*/
CString CRailwayBureau::GetRoadBureauName(const int &iID)
{
	if (iID<0 || iID>m_byBureauNum)
	{
		return "未知路局";
	}
	else
	{
		return m_pVector[iID-1]-> strName;
	}	
}

/*
	返回路局代码为iRoadID,分局代码为iSubID的分局的名称
*/
CString CRailwayBureau::GetSubBureauName(const int &iRoadID, const int &iSubID)
{
	if (iRoadID<0 || iRoadID>m_byBureauNum)
	{
		return "未知分局";
	}
	if ( iSubID<1 && iSubID>GetSubBureauNumber(iRoadID) )
	{
		return "未知分局";
	}

	BureauNode* _q = m_pVector[iRoadID-1]->pNext;
	while ( _q != NULL)
	{
		if ( _q->byID == iSubID )
		{
			return _q-> strName;
		}
		_q = _q-> pNext;
	}

	return "未知分局";
}

/*
	返回代码为iRoadID的路局的分局数目
*/
//iRoadID 为路局的ID
WORD CRailwayBureau::GetSubBureauNumber(const int &iRoadID)
{
	if ( iRoadID<0 || iRoadID>m_byBureauNum )
	{
		return 0;
	}

	BureauNode* p = m_pVector[iRoadID - 1];

	WORD wLength = 0;
	while ( p != NULL)
	{
		wLength++;
		p = p->pNext;
	}
	return wLength-1;
}

//=============================================================================================
//Private Methods, offer for public methdos.

void CRailwayBureau::AddItem(int iRowNo,BureauNode *item)
{
	BureauNode* cp = m_pVector[iRowNo];

	if ( cp == NULL )
	{
		m_pVector[iRowNo] = item;
	}
	else
	{
		while ( cp->pNext != NULL )	{cp = cp->pNext;}
		cp->pNext = item;
	}
}
