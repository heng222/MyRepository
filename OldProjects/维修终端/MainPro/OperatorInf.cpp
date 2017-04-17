// OperatorInf.cpp: implementation of the COperatorInf class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "maintain.h"
#include "OperatorInf.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COperatorInf::COperatorInf(CString strFileName/*=""*/)
{
	//m_iOperatorNum
	m_iOperatorNum = 0;

	//m_strPathName
	if ( !strFileName.IsEmpty() )
	{
		m_strPathName = strFileName;
	}
	
	//m_pVector[OPERATIORMAXNUM]
	for ( int i=0; i<OPERATORMAXNUM; i++)
	{
		m_pVector[i] = NULL;
	}
}

COperatorInf::~COperatorInf()
{
	ClearList();
}

BOOL COperatorInf::ReadFile(CString strFileName/*=""*/)
{
	if ( !strFileName.IsEmpty() )
	{
		m_strPathName = strFileName;
	}
	//--------------------------------------------
	CFile fp;
	//���ڼ��ָ�����ļ��Ƿ����
	if(!fp.Open(m_strPathName,CFile::modeRead))
	{
		return FALSE;
	}

	//���������Ϣ
	ClearList();

	//����鵵����
	CArchive ar(&fp,CArchive::load);
	//ȡ������
	ar>>m_iOperatorNum;
	//
	for (int i=0; i<m_iOperatorNum; i++ )
	{
		m_pVector[i] = new OperatorNode;
		ar>>m_pVector[i]->strName>>m_pVector[i]->strPassword>>m_pVector[i]->iKind;
	}
	//�ر��ļ�
	ar.Close();
	fp.Close();
	//---------------------------------------
	return TRUE;
}

BOOL COperatorInf::WriteFile(CString strFileName/*=""*/)
{
	if ( !strFileName.IsEmpty() )
	{
		m_strPathName = strFileName;
	}
	//-------------------------------------------------------
	CFile fp;
	CString strLine;
	if(	!fp.Open(m_strPathName,CFile::modeReadWrite | CFile::modeCreate) )
	{
		return FALSE;
	}
	CArchive ar(&fp,CArchive::store);
	//д���¼����
	ar<<m_iOperatorNum;
	//
	for ( int i = 0; i<m_iOperatorNum; i++ )
	{
		ar<<m_pVector[i]->strName<<m_pVector[i]->strPassword<<m_pVector[i]->iKind;
	}
	//�ر��ļ�
	ar.Close();
	fp.Close();
	//-----------------------------------------
	return TRUE;
}

//==========================================================================
void COperatorInf::AddAdministrator()
{
	OperatorNode sOptNode;
	sOptNode.strName = "Administrator";
	sOptNode.strPassword = "123";
	sOptNode.iKind = 1;
	//
	Add(sOptNode);
}
void COperatorInf::Add(const OperatorNode& item)
{
	//ȷ��Ŀǰ����Ա��Ϣ��С����������ֵ
	ASSERT( m_iOperatorNum <= OPERATORMAXNUM );
	ASSERT( item.strName.IsEmpty() != TRUE );
	ASSERT( item.strPassword.IsEmpty() != TRUE );
	ASSERT( item.iKind != 0 );
	//�¿���һ�ڴ�ռ䲢���丳ֵ
	m_pVector[m_iOperatorNum - 1] = new OperatorNode;

	m_pVector[m_iOperatorNum - 1]->strName = item.strName;
	m_pVector[m_iOperatorNum - 1]->strPassword = item.strPassword;
	m_pVector[m_iOperatorNum - 1]->iKind = item.iKind;

	//�û�������һ
	m_iOperatorNum++;

	//д���ļ�
	WriteFile();
}

void COperatorInf::DelUser(CString strName)
{
	int iSpeNum = -1;
	//�ҵ�strName���ڵ��±�
	for ( int i = 0; i<m_iOperatorNum; i++ )
	{
		if ( m_pVector[i]->strName == strName )
		{
			iSpeNum = i;
			break;
		}
	}

	ASSERT( iSpeNum != -1 );

	//ɾ���û�
	delete m_pVector[iSpeNum];
	//�����һ��ָ�븳ֵ����ǰָ��
	m_pVector[iSpeNum] = m_pVector[m_iOperatorNum];
	//�����һ��ָ�븳ֵΪNULL
	m_pVector[m_iOperatorNum] = NULL;
	//�û�����һ
	m_iOperatorNum --;

	//
	
	//д���ļ�
	WriteFile();
}

void COperatorInf::ModifyUserPassword(CString strName, CString strPassword)
{
	for ( int i = 0; i<m_iOperatorNum; i++ )
	{
		if ( m_pVector[i]->strName == strName )
		{
			m_pVector[i]->strPassword = strPassword;
			break;
		}
	}
	
	//д���ļ�
	WriteFile();
}

//===============================================================================
void COperatorInf::ClearList()
{
	//
	for ( int i = 0; i<m_iOperatorNum; i++ )
	{
		delete m_pVector[i];
		m_pVector[i] = NULL;
	}
	//
	m_iOperatorNum = 0;
}
void COperatorInf::SetPathName(CString strPathName)
{
	m_strPathName = strPathName;
}

CString COperatorInf::IsExistUser(CString strName)
{
	for ( int i = 0; i<m_iOperatorNum; i++ )
	{
		if ( m_pVector[i]->strName == strName )
		{

			return m_pVector[i]->strPassword;
		}
	}
	return "";
}

int COperatorInf::GetLength()
{
	return m_iOperatorNum;
}

CString COperatorInf::GetName(int iIndex)
{
	ASSERT(iIndex < m_iOperatorNum);
	//
	return m_pVector[iIndex]->strName;
}

void COperatorInf::FindUser(CString strName, OperatorNode& sOperator)
{
	for ( int i = 0; i<m_iOperatorNum; i++ )
	{
		if ( m_pVector[i]->strName == strName )
		{
			sOperator.strName = m_pVector[i]->strName;
			sOperator.strPassword = m_pVector[i]->strPassword;
			sOperator.iKind = m_pVector[i]->iKind;
			break;
		}
	}
	//return false;
	sOperator.strName = "";
	sOperator.strPassword = "";
	sOperator.iKind = 0;
}
