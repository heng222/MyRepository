
//--------------------------------------------------------------------------------
#include "stdAfx.h"
#include "CommFunction.h"
//--------------------------------------------------------------------------------
//从一个字符串中得到第iIndex个字符串,字符串间以cCompart分隔
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
//从一个字符串中得到元素的个数，元素以cCompart符号分隔
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
	//得到cCompart的总个数
	while ( *cp != '\0' )
	{
		if ( *cp == cCompart && *cq != cCompart )
		{
			iItemSum++;
		}
		cq = cp;
		cp++;
	}
	//若字符串中没有分隔符，则返回1
	if ( iItemSum == 0 )
	{
		return 1;
	}
	//若第一个符号和最后一个符号都是分隔符，则元素个数减一
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

//从一个字符串中得到第iIndex个整数
WORD GetNFStr(const char *chSource, const int &iIndex)
{
	char chNum[10];

	const char *cp = chSource;
	while( !isdigit(*(cp+0)) && *cp!='\0' )
	{
		cp++;
	}//cp此时指向chSource字符串中第一个数字字符处

	const char *cq = cp;
	WORD iOrder = 0;

	while (*cp != '\0' )
	{
		//当前字符为数字且前一个字符不是数字时，数字个数加一
		if( isdigit( *(cp+0) ) && !isdigit( *(cq+0) ) )
		{
			iOrder++;
		}
		//找到第iIndex个整数，取出整数,返回.
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