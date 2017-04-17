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
	strPathName:	报警文件存放的文件夹路径，程序自动在指定的文件夹下再建立一warning文件夹

	Remark:			指定的文件夹一定要有效，否则将出错
*/
CAlarmInfo::CAlarmInfo(CString strPathName /*=""*/)
{
	//当前警报数置0
	m_wCurNumber = 0;
	
	//初始化指针数组
	InitArray();
	
	//是指定文件路径，还是使用默认的路径?
	if ( !strPathName.IsEmpty() )
	{
		m_strDirPath = strPathName + "\\warning";	
	}
	else
	{
		//确定警报默认存放路径
		char CArray[100];
		GetCurrentDirectory(100,CArray);
		m_strDirPath.Format("%s%s",CArray,"\\warning");
	}

	//检查当前目录warning文件夹下是否存在指定文件
	CFileFind fer;
	if( fer.FindFile(m_strDirPath,0) == 0 )
	{
		//不存在自动则自动建立
		CreateDirectory( m_strDirPath,NULL );
		//警报总数为0
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
	//初始化文件全路径
	if ( strFileName.IsEmpty() )
	{
		m_strPathName.Format("%s%s",m_strDirPath,CTime::GetCurrentTime().Format("\\%Y-%m-%d.alm"));
	}
	else
	{
		m_strPathName = m_strDirPath + "\\" + strFileName;
	}
		
	//初始化警报总数
	//查看指定的文件是否存在以及对警报总数变量进行赋值
	//CFile fp;
	if ( m_cFile.Open(m_strPathName,CFile::modeRead  | CFile::shareDenyNone) )
	{
		//取出已有的警报总数
		m_cFile.Read(&m_dTotalNumber,sizeof(m_dTotalNumber));
	}
	else
	{
		//读取文件标志，但指定的文件不存在。
		if ( m_nOpenFlags == modeRead )
		{
			return false;
		}
		else
		{//写文件，文件不存在，自动创建
			m_cFile.Open( m_strPathName,CFile::modeCreate );	
		}
		m_dTotalNumber = 0;
	}	
	m_cFile.Close();

	//以用户指定的方式打开文件
	BOOL bIsOpen = m_cFile.Open(m_strPathName,m_nOpenFlags | CFile::shareDenyNone) ;
	ASSERT( bIsOpen );
	
	return true;
}

void CAlarmInfo::ReadFile()
{
	ASSERT ( (m_nOpenFlags & modeRead) == modeRead );

	//清空内存
	ClearArray();
	
	//置当前数为0
	m_wCurNumber = 0;
	
	//定义归档对象
	m_cFile.SeekToBegin();
	CArchive ar(&m_cFile,CArchive::load);
	
	//从文件中取出总数目
	ar>>m_dTotalNumber;
	ar.Close();

}
BOOL CAlarmInfo::ReadNext()
{
	ASSERT ( (m_nOpenFlags & modeRead) == modeRead );
	//清空内存
	ClearArray();

	m_wCurNumber = 0;
	if ( m_dTotalNumber <= 0 )
	{
		return false;//此时返回，说明文件已读取完毕且缓冲中无数据
	}
	while( m_dTotalNumber > 0 )
	{
		//缓冲是否已满？
		if ( m_wCurNumber == ALARMMAXNUMBER )
		{
			return true;//此时返回，说明缓冲已满
		}
		m_pVector[m_wCurNumber] = new AINode;
		//定义归档对象
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
	//此时返回，说明文件中的所有内容读取完毕但缓冲中尚有数据
	return true;
}
void CAlarmInfo::WriteCacheToFile()
{
	ASSERT ( (m_nOpenFlags & modeWrite) == modeWrite);

	//将文件指针移动到文件头(此时文件指针指向文件头)
	m_cFile.SeekToBegin();

	//写入记录总数
	m_cFile.Write(&m_dTotalNumber,sizeof(m_dTotalNumber));

	//定义归档对象(此时文件指针指向文件尾)
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
	//关闭文件
	m_cFile.Close();

	//清空数组
	ClearArray();

	//当前警报数置0
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
	//得到以当前时间为文件名的文件的全路径
	CString sSpeTime = item.m_time.Format("\\%Y-%m-%d.alm");
	CString sSpePath;
	sSpePath.Format("%s%s",m_strDirPath,sSpeTime);

	//原始信息的时间与当前要加入的信息的时间不一致，
	//则自动将所有的原始信息存储后，再将当前信息加入.
	if ( m_strPathName != sSpePath )
	{
		WriteCacheToFile();
		ClearArray();	//清空原有信息
		m_strPathName = sSpePath;
		m_wCurNumber = 0;
		//若当前日期文件已经存在，则取出总数
		//CFile fp;
		m_cFile.Close();
		if ( m_cFile.Open(m_strPathName,CFile::modeRead  | CFile::shareDenyNone) )
		{
			//取出已有的警报总数
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
	

	//当前警报数目等于允许的最大数目(也即缓冲满时)
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
	//定义归档对象
	m_cFile.SeekToBegin();
	CArchive ar1(&m_cFile,CArchive::load,20480);//2K Cache
	//从文件中取出总数目
	ar1>>m_dTotalNumber;
	
	//另开辟一缓存
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
		//修改信息
		for ( i = k,j = k+1; i<m_dTotalNumber-1; i++,j++ )
		{
			pVector[i].m_wOrder		= pVector[j].m_wOrder;
			pVector[i].m_sStation   = pVector[j].m_sStation;
			pVector[i].m_time		= pVector[j].m_time;
			pVector[i].m_sContent	= pVector[j].m_sContent;
			pVector[i].m_byLevel	= pVector[j].m_byLevel;
			pVector[i].m_sSource	= pVector[j].m_sSource;
		}
		//总记录数减一
		m_dTotalNumber --;
		//删除旧文件
		m_cFile.Close();
		CFile::Remove(m_strPathName);
		
		//建立新文件
		m_cFile.Open(m_strPathName,CFile::modeWrite | CFile::modeCreate);
		//定义归档对象
		m_cFile.SeekToBegin();
		CArchive ar2(&m_cFile,CArchive::store,20480);//2K Cache
		//总数目
		ar2<<m_dTotalNumber;
		//写入修改后的信息。
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
	//先将最后一个信息的内容暂存
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
				//此时文件指针指向要删除信息的起始位置 
			{
				//定义归档对象(此时文件指针指向第iOrder元素的起始位置)
				CArchive ar(&m_cFile,CArchive::store);
				//将最后一个元素的信息覆盖掉指定的信息，但序号不变
				ar<<iOrder<<item.m_time
					<<item.m_sContent<<item.m_byLevel
					<<item.m_sSource;
				ar.Close();
				//将最后一个元素的信息删掉

				//将信息总数保存
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
