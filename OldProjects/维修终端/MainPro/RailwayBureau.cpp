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
	//���ڼ��ָ�����ļ��Ƿ����
	if(!fp.Open(strFileName,CFile::modeRead))
		//ָ�����ļ������ڣ����Ե�ǰ������Ϊ�ļ��������ļ�
	{
		return FALSE;
	}
	else//�ļ�����
	{
		fp.Close();
	}

	//ȡ��·����Ŀ
	m_byBureauNum = GetPrivateProfileInt("·����Ŀ","����",0,strFileName);
	if ( m_byBureauNum > BUREAUMAXNUM || m_byBureauNum == 0)
	{
		MessageBox(NULL,"·����Ŀ���ڳ������������������!","Information",MB_ICONEXCLAMATION);
		return FALSE;
	}

	CString strKey;
	char sValue[255];
	
	for ( int i = 0; i<m_byBureauNum; i++ )
	{
		//ȡ����ǰ·��
		strKey.Format("·��%d",i+1);
		GetPrivateProfileString(strKey,"�־�","",sValue,255,strFileName);
		BureauNode* newNode = new BureauNode;
		newNode->byID = i+1;
		newNode->strName = GetSFStr(sValue,0,',');
		newNode->pNext = NULL;
		AddItem(i,newNode);
		
		//����ȡ����ǰ·���µĸ��־�
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
	�õ�·����Ŀ
*/
WORD CRailwayBureau::GetBureauNumber()
{
	return m_byBureauNum;
}

/*
	�õ�����ΪiID��·�ֵ�����
*/
CString CRailwayBureau::GetRoadBureauName(const int &iID)
{
	if (iID<0 || iID>m_byBureauNum)
	{
		return "δ֪·��";
	}
	else
	{
		return m_pVector[iID-1]-> strName;
	}	
}

/*
	����·�ִ���ΪiRoadID,�־ִ���ΪiSubID�ķ־ֵ�����
*/
CString CRailwayBureau::GetSubBureauName(const int &iRoadID, const int &iSubID)
{
	if (iRoadID<0 || iRoadID>m_byBureauNum)
	{
		return "δ֪�־�";
	}
	if ( iSubID<1 && iSubID>GetSubBureauNumber(iRoadID) )
	{
		return "δ֪�־�";
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

	return "δ֪�־�";
}

/*
	���ش���ΪiRoadID��·�ֵķ־���Ŀ
*/
//iRoadID Ϊ·�ֵ�ID
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
