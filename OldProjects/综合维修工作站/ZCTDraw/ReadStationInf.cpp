// ReadStationInf.cpp: implementation of the CReadStationInf class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReadStationInf.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
#define FILENAMESTATIONINF "\\ini\\StationInf.ini"	//车站配置文件
//////////////////////////////////////////////////////////////////////

CReadStationInf* CReadStationInf::_pInstance = CReadStationInf::GetInstance();

int		CReadStationInf::_iActiveStationID = -1;//当前处于显示状态的站场图ID

CReadStationInf::CReadStationInf()
{
	m_pHead = NULL;
	m_wStationNum = 0;
}

CReadStationInf::~CReadStationInf()
{
	ClearList();
}


CReadStationInf* CReadStationInf::GetInstance() 
{
	if ( _pInstance == NULL )
	{
		//确定系统当前路径
		char cTemp[MAX_PATH];
		CString strExePath;
		GetCurrentDirectory(MAX_PATH,cTemp);
		strExePath.Format("%s%s",cTemp,FILENAMESTATIONINF);
		_pInstance = new CReadStationInf;
		_pInstance->ReadFile(strExePath);

		//
		_iActiveStationID = GetPrivateProfileInt("SYSTEM","CurStationID",-1,strExePath);
	}
	
	return _pInstance;
}


void CReadStationInf::ReleaseInstance()
{
	if ( _pInstance )
	{
		delete _pInstance;
		_pInstance = NULL;
	}
	

	//确定系统当前路径
	char cTemp[MAX_PATH];
	CString strExePath;
	GetCurrentDirectory(MAX_PATH,cTemp);
	strExePath.Format("%s%s",cTemp,FILENAMESTATIONINF);
	CString strStaID;
	strStaID.Format("%d",_iActiveStationID);
	WritePrivateProfileString("SYSTEM","CurStationID",strStaID,strExePath);
}
BOOL CReadStationInf::ReadFile(LPCSTR lpFileName/*=""*/)
{
	CFile fp;
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

	ClearList();

	//施工种类的个数
	CString strAppName;
	m_wStationNum = GetPrivateProfileInt("SYSTEM","StationCount",-1,lpFileName);
	

	//定义一个新结点
	StationNode newItem;
	char strLine[400];
	for (int i = 0; i<m_wStationNum; i++)
	{
		//Index
		newItem.iIndex = i;
		strAppName.Format("STATION%d",i+1);

		//Station ID
		newItem.iStationID = GetPrivateProfileInt(strAppName,"StationID",0,lpFileName);
		
		//Station Name
		GetPrivateProfileString(strAppName,"StationName","",strLine,400,lpFileName);
		newItem.strName.Format("%s",strLine);

		//station Directory
		GetPrivateProfileString(strAppName,"StationDataDir",_T(""),strLine,400,lpFileName);
		newItem.strDirectory = strLine;

		//UpStation1 ID
		newItem.iUpStationID[0] = GetPrivateProfileInt(strAppName,"UpStation1ID",0,lpFileName);

		//UpStation2 ID
		newItem.iUpStationID[1] = GetPrivateProfileInt(strAppName,"UpStation2ID",0,lpFileName);

		//DownStation1 ID
		newItem.iDownStationID[0] = GetPrivateProfileInt(strAppName,"DownStation1ID",0,lpFileName);
		
		//DownStation2 ID
		newItem.iDownStationID[1] = GetPrivateProfileInt(strAppName,"DownStation2ID",0,lpFileName);

		//==============
		Add(newItem);
	}
	//--------------------------------------------
	return TRUE;
	
}


CString CReadStationInf::GetName(const WORD &wStationNo,BOOL byStationID/*=TRUE*/) const
{
	StationNode *p = m_pHead;
	while( p!=NULL )
	{
		if ( byStationID ){			
			if(p->iStationID == wStationNo){
				return p->strName;
			}
		}
		else{
			if ( p->iIndex == wStationNo ){
				return p->strName;
			}
		}
		p = p->Next;
	}
	return "";
}

WORD CReadStationInf::GetStationID(LPCSTR strName) const
{
	StationNode *p = m_pHead;
	while( p!=NULL )
	{
		if(p->strName.CompareNoCase(strName) == 0){
			return p->iStationID;
		}
		p = p->Next;
	}
	return -1;
}
WORD CReadStationInf::GetStationID(int iOrder) const
{
	StationNode *p = m_pHead;
	while( p!=NULL )
	{
		if(p->iIndex == iOrder)	{
			return p->iStationID;
		}
		p = p->Next;
	}
	return -1;
}
CString CReadStationInf::GetDirectory(const WORD& wStationNo,BOOL bAbsolute) const
{
	StationNode *p = m_pHead;
	while( p!=NULL )
	{
		if(p->iStationID == wStationNo )
		{
			if (bAbsolute) {
				char cTemp[MAX_PATH];
				GetCurrentDirectory(MAX_PATH,cTemp);//确定系统当前路径
				return  (CString(cTemp) + "\\" + p->strDirectory + "\\");
			}
			else{
				return p->strDirectory;
			}
		}
		p = p->Next;
	}
	return "";
}
CString CReadStationInf::GetDirectory(const CString& strStationName,BOOL bAbsolute) const
{
	WORD wStaID = GetStationID(strStationName);
	return GetDirectory(wStaID,bAbsolute);
}
int CReadStationInf::GetLength() const
{
	return m_wStationNum;
}

StationNode* CReadStationInf::GetAt(int iIndex) const
{
	StationNode* cp = m_pHead;
	for (int i=0; i<m_wStationNum; i++ )
	{
		if (i==iIndex){
			return cp;
		}
		cp = cp->Next;
	}
	return NULL;
}

StationNode* CReadStationInf::GetItem(int iStationID) const
{
	StationNode* cp = m_pHead;
	for (int i=0; i<m_wStationNum; i++ )
	{
		if (cp->iStationID == iStationID){
			return cp;
		}
		cp = cp->Next;
	}
	return NULL;
}

void CReadStationInf::ClearList()
{
	StationNode *cp,*np;
	cp=m_pHead;
	while(cp!=NULL)	{
		np=cp->Next;
		delete cp;
		cp=np;
	}
	//
	m_pHead = NULL;
	m_wStationNum = 0;
	//
}

CString CReadStationInf::CovNumToName(CString strNum, 
					char SComPart/* = '/'*/, char DComPart/* = ','*/) const
{
	ASSERT( m_wStationNum >= 0);
	CString strName;
	//
	int iItemCount = GetItemSum(strNum,SComPart);
	for ( int i = 0; i<iItemCount; i++ )
	{
		WORD wTemp = GetNFStr(strNum,i);
		//
		CString strTemp;
		if ( i == (iItemCount-1) )	{
			strTemp = GetName(wTemp);		
		}
		else{
			strTemp.Format("%s%c",GetName(wTemp),DComPart);
		}
		//
		strName = strName + strTemp;
	}
	//
	return strName;
}

CString CReadStationInf::CovNameToNum(CString strName,
			 char SComPart/* = ','*/, char DComPart/* = '/'*/) const
{
	ASSERT( m_wStationNum >= 0);
	CString strNum;
	//
	int iItemCount = GetItemSum(strName,SComPart);
	for ( int i = 0; i<iItemCount; i++ )
	{
		CString strTemp = GetSFStr(strName,i,SComPart);
		//
		WORD wTemp = GetStationID(strTemp);
		//
		
		if ( i == (iItemCount-1) )
		{
			strTemp.Format("%d",wTemp);
		}
		else
		{
			strTemp.Format("%d%c",wTemp,DComPart);	
		}
		//
		strNum = strNum + strTemp;
	}
	//
	return strNum;
}
//=============================================================================================
//Private Methods, offer for public methods.
void CReadStationInf::Add(const StationNode &item)
{
	StationNode *newPtr = new StationNode;
	
	newPtr->iIndex = item.iIndex;
	newPtr->iStationID = item.iStationID;
	newPtr->strName = item.strName;
	newPtr->strDirectory = item.strDirectory;
	newPtr->iUpStationID[0] = item.iUpStationID[0];
	newPtr->iUpStationID[1] = item.iUpStationID[1];
	newPtr->iDownStationID[0] = item.iDownStationID[0];
	newPtr->iDownStationID[1] = item.iDownStationID[1];

	newPtr->Next = NULL;

	//若头指针为空，则将头指针指向当前结点
	if( m_pHead==NULL )
	{
		m_pHead = newPtr;
	}
	else//头指针不为空，则找到单链表的末尾，并将当前结点加入到末尾.
	{
		StationNode *p = m_pHead;
		while(p->Next!=NULL)
		{
			p = p->Next;
		}
		p->Next = newPtr;
	}
}

