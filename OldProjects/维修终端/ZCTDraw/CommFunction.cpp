
//--------------------------------------------------------------------------------
#include "stdAfx.h"
#include "CommFunction.h"
//--------------------------------------------------------------------------------
//��һ���ַ����еõ���iIndex���ַ���,�ַ�������cCompart�ָ�
CString GetSFStr(CString strSource, const int &iIndex, char cCompart)
{
	strSource.TrimLeft(" ");
	strSource.TrimRight(" ");
	//---
	CString strName;
	const char *cp,*cq;
	cq = cp = (const char*)strSource;
	int iCount = -1;
	//---
	while ( *cp != '\0' )
	{
		if ( *cp == cCompart )
		{
			iCount++;
			if ( iCount == iIndex )
			{
				break;
			}
			cp++;
			strName.Empty();
		}
		strName += *cp;
		//
		cp++;
	}
	return strName;
}
//��һ���ַ����еõ�Ԫ�صĸ�����Ԫ����cCompart���ŷָ�
int GetItemSum(CString strSource, char cCompart)
{
	strSource.TrimLeft(" ");
	strSource.TrimRight(" ");
	if ( strSource.IsEmpty() )
	{
		return 0;
	}
	//---------------------------
	int iItemSum = 0;
	const char *cp,*cq;
	cq = cp = (const char*)strSource;
	//�õ�cCompart���ܸ���
	while ( *cp != '\0' )
	{
		if ( *cp == cCompart && *cq != cCompart )
		{
			iItemSum++;
		}
		cq = cp;
		cp++;
	}
	//���ַ�����û�зָ������򷵻�1
	if ( iItemSum == 0 )
	{
		return 1;
	}
	//����һ�����ź����һ�����Ŷ��Ƿָ�������Ԫ�ظ�����һ
	cp = (const char*)strSource;
	if ( *cp == cCompart && *cq == cCompart )
	{
		iItemSum--;
	}
	if ( *cp != cCompart && *cq != cCompart )
	{
		iItemSum++;
	}
	//----------------------------------
	return iItemSum;
}

//��һ���ַ����еõ���iIndex������
WORD GetNFStr(const char *chSource, const int &iIndex)
{
	char chNum[10];

	const char *cp = chSource;
	while( !isdigit(*(cp+0)) && *cp!='\0' )
	{
		cp++;
	}//cp��ʱָ��chSource�ַ����е�һ�������ַ���

	const char *cq = cp;
	WORD iOrder = 0;

	while (*cp != '\0' )
	{
		//��ǰ�ַ�Ϊ������ǰһ���ַ���������ʱ�����ָ�����һ
		if( isdigit( *(cp+0) ) && !isdigit( *(cq+0) ) )
		{
			iOrder++;
		}
		//�ҵ���iIndex��������ȡ������,����.
		if( iOrder == iIndex)
		{
			BYTE i = 0;
			
			while( isdigit(*(cp+0)) )
			{
				chNum[i] = *cp;
				i++;
				cp++;
			}
			chNum[i] = '\0';
			return atoi(chNum);
			break;
		}
		//
		cq = cp;
		cp++;
	}
	//--------------
	return 0;
}