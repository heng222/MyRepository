// AlarmInfo.cpp: implementation of the CAlarmInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AlarmInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
	strPathName:	�����ļ���ŵ��ļ���·���������Զ���ָ�����ļ������ٽ���һwarning�ļ���

	Remark:			ָ�����ļ���һ��Ҫ��Ч�����򽫳���
*/
CAlarmInfo::CAlarmInfo(CString strPathName /*=""*/)
{
	//��ǰ��������0
	m_wCurNumber = 0;
	
	//��ʼ��ָ������
	InitArray();
	
	//��ָ���ļ�·��������ʹ��Ĭ�ϵ�·��?
	if ( !strPathName.IsEmpty() )
	{
		m_strDirPath = strPathName + "\\warning";	
	}
	else
	{
		//ȷ������Ĭ�ϴ��·��
		char CArray[100];
		GetCurrentDirectory(100,CArray);
		m_strDirPath.Format("%s%s",CArray,"\\warning");
	}

	//��鵱ǰĿ¼warning�ļ������Ƿ����ָ���ļ�
	CFileFind fer;
	if( fer.FindFile(m_strDirPath,0) == 0 )
	{
		//�������Զ����Զ�����
		CreateDirectory( m_strDirPath,NULL );
		//��������Ϊ0
		m_dTotalNumber = 0;
	}
	//
	fer.Close();
}

CAlarmInfo::~CAlarmInfo()
{
	
}

BOOL CAlarmInfo::OpenFile(UINT nOpenFlags/*=modeWrite*/,CString strFileName/*=""*/)
{
	m_nOpenFlags = nOpenFlags;
	//��ʼ���ļ�ȫ·��
	if ( strFileName.IsEmpty() )
	{
		m_strPathName.Format("%s%s",m_strDirPath,CTime::GetCurrentTime().Format("\\%Y-%m-%d.alm"));
	}
	else
	{
		m_strPathName = m_strDirPath + "\\" + strFileName;
	}
		
	//��ʼ����������
	//�鿴ָ�����ļ��Ƿ�����Լ��Ծ��������������и�ֵ
	//CFile fp;
	if ( m_cFile.Open(m_strPathName,CFile::modeRead  | CFile::shareDenyNone) )
	{
		//ȡ�����еľ�������
		m_cFile.Read(&m_dTotalNumber,sizeof(m_dTotalNumber));
	}
	else
	{
		//��ȡ�ļ���־����ָ�����ļ������ڡ�
		if ( m_nOpenFlags == modeRead )
		{
			return false;
		}
		else
		{//д�ļ����ļ������ڣ��Զ�����
			m_cFile.Open( m_strPathName,CFile::modeCreate );	
		}
		m_dTotalNumber = 0;
	}	
	m_cFile.Close();

	//���û�ָ���ķ�ʽ���ļ�
	BOOL bIsOpen = m_cFile.Open(m_strPathName,m_nOpenFlags | CFile::shareDenyNone) ;
	ASSERT( bIsOpen );
	
	return true;
}

void CAlarmInfo::ReadFile()
{
	ASSERT ( (m_nOpenFlags & modeRead) == modeRead );

	//����ڴ�
	ClearArray();
	
	//�õ�ǰ��Ϊ0
	m_wCurNumber = 0;
	
	//����鵵����
	m_cFile.SeekToBegin();
	CArchive ar(&m_cFile,CArchive::load);
	
	//���ļ���ȡ������Ŀ
	ar>>m_dTotalNumber;
	ar.Close();

}
BOOL CAlarmInfo::ReadNext()
{
	ASSERT ( (m_nOpenFlags & modeRead) == modeRead );
	//����ڴ�
	ClearArray();

	m_wCurNumber = 0;
	if ( m_dTotalNumber <= 0 )
	{
		return false;//��ʱ���أ�˵���ļ��Ѷ�ȡ����һ�����������
	}
	while( m_dTotalNumber > 0 )
	{
		//�����Ƿ�������
		if ( m_wCurNumber == ALARMMAXNUMBER )
		{
			return true;//��ʱ���أ�˵����������
		}
		m_pVector[m_wCurNumber] = new AINode;
		//����鵵����
		CArchive ar(&m_cFile,CArchive::load);
		ar>>m_pVector[m_wCurNumber]->m_wOrder
			>>m_pVector[m_wCurNumber]->m_sStation
			>>m_pVector[m_wCurNumber]->m_time
			>>m_pVector[m_wCurNumber]->m_sContent
			>>m_pVector[m_wCurNumber]->m_byLevel
			>>m_pVector[m_wCurNumber]->m_sSource;
		//
		m_wCurNumber ++;
		m_dTotalNumber --;
	}
	//��ʱ���أ�˵���ļ��е��������ݶ�ȡ��ϵ���������������
	return true;
}
void CAlarmInfo::WriteCacheToFile()
{
	ASSERT ( (m_nOpenFlags & modeWrite) == modeWrite);

	//���ļ�ָ���ƶ����ļ�ͷ(��ʱ�ļ�ָ��ָ���ļ�ͷ)
	m_cFile.SeekToBegin();

	//д���¼����
	m_cFile.Write(&m_dTotalNumber,sizeof(m_dTotalNumber));

	//����鵵����(��ʱ�ļ�ָ��ָ���ļ�β)
	m_cFile.SeekToEnd();
	CArchive ar(&m_cFile,CArchive::store);

	for ( int i = 0; i<m_wCurNumber; i++ )
	{
		ar<<m_pVector[i]->m_wOrder<<m_pVector[i]->m_sStation<<m_pVector[i]->m_time<<m_pVector[i]->m_sContent
			<<m_pVector[i]->m_byLevel<<m_pVector[i]->m_sSource;
	}
	ar.Close();
}

void CAlarmInfo::CloseFile()
{
	if ( m_nOpenFlags == modeWrite )
	{
		if ( m_wCurNumber != 0 )
		{
			WriteCacheToFile();
		}
	}
	//�ر��ļ�
	m_cFile.Close();

	//�������
	ClearArray();

	//��ǰ��������0
	m_wCurNumber = 0;
}
void CAlarmInfo::InitArray()
{
	for ( int i = 0; i<ALARMMAXNUMBER; i++ )
	{
		m_pVector[i] = NULL;
	}
}

void CAlarmInfo::ClearArray()
{
	for ( int i = 0; i<m_wCurNumber; i++ )
	{
		delete m_pVector[i];
		m_pVector[i] = NULL;
	}
}

void CAlarmInfo::Add(const AINode &item)
{
	ASSERT ( m_nOpenFlags == modeWrite );
	//�õ��Ե�ǰʱ��Ϊ�ļ������ļ���ȫ·��
	CString sSpeTime = item.m_time.Format("\\%Y-%m-%d.alm");
	CString sSpePath;
	sSpePath.Format("%s%s",m_strDirPath,sSpeTime);

	//ԭʼ��Ϣ��ʱ���뵱ǰҪ�������Ϣ��ʱ�䲻һ�£�
	//���Զ������е�ԭʼ��Ϣ�洢���ٽ���ǰ��Ϣ����.
	if ( m_strPathName != sSpePath )
	{
		WriteCacheToFile();
		ClearArray();	//���ԭ����Ϣ
		m_strPathName = sSpePath;
		m_wCurNumber = 0;
		//����ǰ�����ļ��Ѿ����ڣ���ȡ������
		//CFile fp;
		m_cFile.Close();
		if ( m_cFile.Open(m_strPathName,CFile::modeRead  | CFile::shareDenyNone) )
		{
			//ȡ�����еľ�������
			m_cFile.Read(&m_dTotalNumber,sizeof(m_dTotalNumber));
		}
		else
		{
			m_cFile.Open( m_strPathName,CFile::modeCreate );
			m_dTotalNumber = 0;
		}
		m_cFile.Close();
		//
		m_cFile.Open(m_strPathName,CFile::modeWrite  | CFile::shareDenyNone);
	}
	

	//��ǰ������Ŀ��������������Ŀ(Ҳ��������ʱ)
	if ( m_wCurNumber == ALARMMAXNUMBER )
	{
		WriteCacheToFile();
		ClearArray();
		m_wCurNumber = 0;
	}
	//
	AINode *pNode = new AINode;
	pNode->m_wOrder		= item.m_wOrder;
	pNode->m_sStation   = item.m_sStation;
	pNode->m_time		= item.m_time;
	pNode->m_sContent	= item.m_sContent;
	pNode->m_byLevel	= item.m_byLevel;
	pNode->m_sSource	= item.m_sSource;
	
	//---------------------------------
	m_pVector[m_wCurNumber++] = pNode;
	m_dTotalNumber++;
}

CURNUMTYPE CAlarmInfo::GetCurLength()
{
	return m_wCurNumber;
}

AINode* CAlarmInfo::GetAt(CURNUMTYPE iIndex)
{
	ASSERT ( iIndex < m_wCurNumber );
	return m_pVector[iIndex];
}


void CAlarmInfo::SetPathName(CString strPathName)
{
	m_strDirPath = strPathName;
}

TOTALNUMTYPE CAlarmInfo::GetTotalNumber()
{
	return m_dTotalNumber;
}

BOOL CAlarmInfo::FindItem(TOTALNUMTYPE iOrder,AINode& item)
{
	//-------------------------
	ReadFile();
	while ( ReadNext() )
	{
		int iLength = GetCurLength();
		//	
		for ( int i = 0; i<iLength; i++ )
		{
			if ( m_pVector[i]->m_wOrder == iOrder )
			{
				item.m_wOrder	= m_pVector[i]->m_wOrder;
				item.m_sStation = m_pVector[i]->m_sStation;
				item.m_time		= m_pVector[i]->m_time;
				item.m_sContent = m_pVector[i]->m_sContent;
				item.m_byLevel	= m_pVector[i]->m_byLevel;
				item.m_sSource	= m_pVector[i]->m_sSource;
				//
				return true;
			}
		}
	}
	ClearArray();
	//
	item.m_wOrder = 0;
	return false;
}

BOOL CAlarmInfo::DelItem(TOTALNUMTYPE iOrder)
{
	//����鵵����
	m_cFile.SeekToBegin();
	CArchive ar1(&m_cFile,CArchive::load,20480);//2K Cache
	//���ļ���ȡ������Ŀ
	ar1>>m_dTotalNumber;
	
	//����һ����
	TOTALNUMTYPE i=0,j=0,k=0;
	BOOL	bFlag = FALSE;
	AINode *pVector = new AINode[m_dTotalNumber];
	for ( i = 0; i<m_dTotalNumber; i++ )
	{
		ar1>>pVector[i].m_wOrder>>pVector[i].m_sStation>>pVector[i].m_time>>pVector[i].m_sContent>>pVector[i].m_byLevel
			>>pVector[i].m_sSource;
		if ( pVector[i].m_wOrder == iOrder )
		{
			bFlag = TRUE;
			k = i;
		}
	}
	ar1.Close();
	//
	if ( !bFlag )
	{
		delete[] pVector;
		return false;
	}
	else
	{
		//�޸���Ϣ
		for ( i = k,j = k+1; i<m_dTotalNumber-1; i++,j++ )
		{
			pVector[i].m_wOrder		= pVector[j].m_wOrder;
			pVector[i].m_sStation   = pVector[j].m_sStation;
			pVector[i].m_time		= pVector[j].m_time;
			pVector[i].m_sContent	= pVector[j].m_sContent;
			pVector[i].m_byLevel	= pVector[j].m_byLevel;
			pVector[i].m_sSource	= pVector[j].m_sSource;
		}
		//�ܼ�¼����һ
		m_dTotalNumber --;
		//ɾ�����ļ�
		m_cFile.Close();
		CFile::Remove(m_strPathName);
		
		//�������ļ�
		m_cFile.Open(m_strPathName,CFile::modeWrite | CFile::modeCreate);
		//����鵵����
		m_cFile.SeekToBegin();
		CArchive ar2(&m_cFile,CArchive::store,20480);//2K Cache
		//����Ŀ
		ar2<<m_dTotalNumber;
		//д���޸ĺ����Ϣ��
		for ( i = 0; i<m_dTotalNumber; i++ )
		{
			ar2<<pVector[i].m_wOrder<<pVector[i].m_sStation<<pVector[i].m_time<<pVector[i].m_sContent<<pVector[i].m_byLevel
				<<pVector[i].m_sSource;
		}
		ar2.Close();
		//
		delete[] pVector;
		return true;
	}
/*
	TOTALNUMTYPE dwTotalNumber = m_dTotalNumber;
	if ( iOrder > dwTotalNumber || iOrder < 0 )
	{
		return false;
	}
	//�Ƚ����һ����Ϣ�������ݴ�
	AINode item;
	FindItem( dwTotalNumber, item );
	//
	ReadFile();
	while ( ReadNext() )
	{
		int iLength = GetCurLength();
		//	
		for ( int i = 0; i<iLength; i++ )
		{
			if ( m_pVector[i]->m_wOrder == (iOrder - 1) )
				//��ʱ�ļ�ָ��ָ��Ҫɾ����Ϣ����ʼλ�� 
			{
				//����鵵����(��ʱ�ļ�ָ��ָ���iOrderԪ�ص���ʼλ��)
				CArchive ar(&m_cFile,CArchive::store);
				//�����һ��Ԫ�ص���Ϣ���ǵ�ָ������Ϣ������Ų���
				ar<<iOrder<<item.m_time
					<<item.m_sContent<<item.m_byLevel
					<<item.m_sSource;
				ar.Close();
				//�����һ��Ԫ�ص���Ϣɾ��

				//����Ϣ��������
				m_cFile.SeekToBegin();
				dwTotalNumber --;
				m_cFile.Write( &dwTotalNumber,sizeof(dwTotalNumber) );
				//

				return true;
			}
		}
	}
	return false;
*/
}
