// PasRailway.cpp: implementation of the CPasRailway class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PasRailway.h"
#include "CommFunction.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPasRailway::CPasRailway()
{
	Head = NULL;
	PWNumber = 0;
}

CPasRailway::~CPasRailway()
{
	ClearList();
}

BOOL CPasRailway::ReadFile(LPCSTR lpcsFileName)
{
	CFile fp;
	if(!fp.Open(lpcsFileName,CFile::modeRead | CFile::shareDenyNone))
	{
		return false;
	}
	//
	PWNumber = GetPrivateProfileInt("SumTable","TSum",0,lpcsFileName);

	//
//	ClearList();
	char strLine[255];
	PRNode newPRNode;
	CString strAppName = "TRoad";
	for ( int i = 0; i<PWNumber; i++ )
	{
		strAppName.Format("TRoad%d",i+1);
		//Button
		GetPrivateProfileString(strAppName,"Button","",strLine,255,lpcsFileName);
		newPRNode.abyButton[0] = (BYTE)GetNFStr(strLine,0);
		newPRNode.abyButton[1] = (BYTE)GetNFStr(strLine,1);
		//SubRoad1
		GetPrivateProfileString(strAppName,"SubRoad1","",strLine,255,lpcsFileName);
		newPRNode.abySubRoad1[0] = (BYTE)GetNFStr(strLine,0);
		newPRNode.abySubRoad1[1] = (BYTE)GetNFStr(strLine,1);
		//SubRoad2
		GetPrivateProfileString(strAppName,"SubRoad2","",strLine,255,lpcsFileName);
		newPRNode.abySubRoad2[0] = (BYTE)GetNFStr(strLine,0);
		newPRNode.abySubRoad2[1] = (BYTE)GetNFStr(strLine,1);

		//Add new node to list
		AddNode(&newPRNode);
	}
	//
	return TRUE;
}

void CPasRailway::AddNode(PRNode *item)
{
	PRNode *newPtr = new PRNode;
	//初始化新开辟的结点
	InitNode(newPtr);
	//赋值
	for (int i = 0; i<2; i++ )
	{
		newPtr->abyButton[i] = item->abyButton[i];
		newPtr->abySubRoad1[i] = item->abySubRoad1[i];
		newPtr->abySubRoad2[i] = item->abySubRoad2[i];
	}
	newPtr->Next = NULL;
	//若头指针为空，则将头指针指向当前结点
	if( Head==NULL )
	{
		Head = newPtr;
	}
	else//头指针不为空，则找到单链表的末尾，并将当前结点加入到末尾.
	{
		PRNode *p = Head;
		while(p->Next!=NULL)
		{
			p = p->Next;
		}
		p->Next = newPtr;
	}
}

void CPasRailway::ClearList()
{
	PRNode *cp,*np;
	//
	cp=Head;
	while(cp!=NULL)
	{
		np=cp->Next;
		//再释放结构本身占用的内存
		delete cp;
		cp=np;
	}
	//
	Head = NULL;
	PWNumber = 0;
}
void CPasRailway::InitNode(PRNode *item)
{
	item->abyButton[0] = item->abyButton[1] = 0;
	item->abySubRoad1[0] = item->abySubRoad1[1] = 0;
	item->abySubRoad2[0] = item->abySubRoad2[1] = 0;

	item->Next = NULL;
}

PRNode* CPasRailway::GetAt(const int &iIndex)
{
	PRNode *cp = Head;
	for(WORD i = 0; i<iIndex; i++)
	{
		if(cp == NULL)
		{
			return NULL;
		}
		cp = cp->Next;
	}
	return cp;
}

int CPasRailway::GetLength()
{
	return PWNumber;
}
BOOL CPasRailway::IsExistER(const WORD* pwBtn,int iBtnNum/*=2*/,PRNode *pItem /*= NULL*/)
{
	PRNode *cp;
	cp=Head;
	while(cp!=NULL)
	{
		if (cp->abyButton[0] == pwBtn[0] &&
				cp->abyButton[1] == pwBtn[1]) {
			if (pItem) {
				memcpy(pItem,cp,sizeof(PRNode));
				//*pItem = *cp;
			}
			return TRUE;
		}
		cp=cp->Next;
	}
	return FALSE;
}