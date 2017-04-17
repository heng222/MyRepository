// ReadRecord.cpp: implementation of the CReadRecord class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "maintain.h"
#include "ReadRecord.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CReadRecord,CObject,1)

CReadRecord::CReadRecord(CString strPathName/* = ""*/)
{
	if ( !strPathName.IsEmpty() )
	{
		m_strPathName = strPathName;
	}
	//
	m_byRecordNum = 0;
	m_bModified = FALSE;
	//
	for ( int i = 0; i<RECORDMAXNUM; i++ )
	{
		m_pRecordMap[i] = NULL;
	}
}

CReadRecord::~CReadRecord()
{
	ClearPArray();
}

//================================================
BOOL CReadRecord::WriteRecords(LPCSTR lpFileName /*= '\0'*/)
{
	if ( lpFileName != '\0' )
	{
		m_strPathName = lpFileName;
	}
	//-------------------------------------------------------
	CFile fp;
	//CString strLine;
	if(	!fp.Open(m_strPathName,CFile::modeReadWrite | CFile::modeCreate) )
	{
		return FALSE;
	}
	CArchive ar(&fp,CArchive::store);
	//д���¼����
	ar<<m_byRecordNum<<m_bModified;
	//
	for ( int i = 0; i<m_byRecordNum; i++ )
	{
		m_pRecordMap[i]->Serialize(ar);
	}
	//�ر��ļ�
	ar.Close();
	fp.Close();
	//-----------------------------------------
	return TRUE;
}
BOOL CReadRecord::ReadRecords(LPCSTR lpcstrFileName/*= '\0'*/)
{
	if ( lpcstrFileName != '\0' )
	{
		m_strPathName = lpcstrFileName;
	}
	//--------------------------------------------
	DeleteAllRecord();
	//
	CFile fp;
	//���ڼ��ָ�����ļ��Ƿ����
	if(!fp.Open(lpcstrFileName,CFile::modeRead))
	{
		return FALSE;
	}
	//����鵵����
	CArchive ar(&fp,CArchive::load);
	//ȡ����¼����
	ar>>m_byRecordNum>>m_bModified;
	//
	for (BYTE i=0; i<m_byRecordNum; i++ )
	{
		m_pRecordMap[i] = new CMapStringToString;
		m_pRecordMap[i]->Serialize(ar);
	}
	//�ر��ļ�
	ar.Close();
	fp.Close();
	//---------------------------------------
	return TRUE;
}
//===========================================================================================

//===============================================================
CString CReadRecord::GetValue(BYTE byIndex, const CString strKey) const
{
	ASSERT(byIndex>=1 && byIndex<=m_byRecordNum);
	CString strValue;
	m_pRecordMap[byIndex-1]->Lookup(strKey,strValue);
	return strValue;
}
void CReadRecord::SetValue(BYTE byIndex, const CString strKey, const CString strItem)
{
	ASSERT( byIndex<=(m_byRecordNum+1) && byIndex>0 );
	//-------------------------------------
	if( byIndex == (m_byRecordNum+1) )
	{
		m_pRecordMap[byIndex-1] = new CMapStringToString;
		//����¼��������һ
		m_byRecordNum++;
		ASSERT(m_byRecordNum<=RECORDMAXNUM);
	}
	m_pRecordMap[byIndex-1]->SetAt(strKey,strItem);
	
	//------------------------------------------------
	m_bModified = TRUE;
}
void CReadRecord::SetValue(BYTE byIndex, const CString strKey, const int iItem)
{
	CString sTemp;
	sTemp.Format("%d",iItem);
	SetValue(byIndex,strKey,sTemp);
}

//==============================================
BYTE CReadRecord::GetRecordNum()
{
	return m_byRecordNum;
}
BOOL CReadRecord::GetModified()
{
	return m_bModified;
}
void CReadRecord::SetModified(BOOL bFlag)
{
	m_bModified = bFlag;
}
//==============================================

//==========================================
void CReadRecord::DeleteRecord(BYTE byIndex)
{
	ASSERT( byIndex <= m_byRecordNum );
	//������¼ɾ��
	delete m_pRecordMap[byIndex-1];
	//�����һ����¼���ڵĵ�ַ������ǰָ��
	m_pRecordMap[byIndex-1] = m_pRecordMap[m_byRecordNum-1];
	// ������ָ���ÿ�
	m_pRecordMap[m_byRecordNum-1] = NULL;
	//�����Ѹ���
	m_bModified = TRUE;
	//��¼����һ
	m_byRecordNum --;
}
//===========================================

void CReadRecord::DeleteAllRecord()
{
	for (int i = 0; i<m_byRecordNum; i++ )
	{
		delete m_pRecordMap[i];
		m_pRecordMap[i] = NULL;
	}
	//
	m_bModified = TRUE;
	m_byRecordNum = 0;
}


int CReadRecord::GetOrderByDT(CString strKey, CString strItem)
{
	for (BYTE i = 0; i<m_byRecordNum; i++)
	{
		CString strValue;
		m_pRecordMap[i]->Lookup(strKey,strValue);
		if ( strValue.Compare(strItem) == 0 )
		{
			return i+1;
		}
	}
	return 0;
}

CString CReadRecord::GetPathName()
{
	return m_strPathName;
}

void CReadRecord::ClearPArray()
{
	m_bModified = false;
	//
	for (int i = 0; i<m_byRecordNum; i++ )
	{
		delete m_pRecordMap[i];
		m_pRecordMap[i] = NULL;
	}
	//
	m_byRecordNum = 0;
	//
}
