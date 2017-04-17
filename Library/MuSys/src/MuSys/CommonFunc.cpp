
#include "stdafx.h"
#include "CommonFunc.h"
#include "XTrace.h"
//////////////////////////////////////////////////////////////////////////

int g_iTest = 100;

//////////////////////////////////////////////////////////////////////////
using namespace std;
#if 0 // 从别处粘来的，有时间修改一下
/*******************************************************************************
/*  MY_ATOI
/*******************************************************************************
/* NOTE that some exchanges return integere values such as
/*      1,022
/**/

static int my_atoi( const char *ip, int len )
{
    bool		neg = false;
    int			ans = 0;
    const char  *cp = ip;

    while ( len > 0 )
    {
        char    ch = *cp;

        if (ch == '-' )
            neg = true;
        else
            if (ch == '+' )
                neg = false;
            else
                if (ch >= '0' && ch <= '9')
                {
                    ans = (ans*10) + ch - '0';
                }

                cp++;
                len--;
    }


    if (neg)
        return -ans;
    else
        return ans;

} /* MY_ATOI */


static double my_atof(  const char *ip, const int len )
{
    char    str[ 32 ];
    double	ans;

    memcpy(str,ip,len);
    str[len] = '\0';
    ans = atof(str);
    return ans;
} 

static __int64 my_atoi64( const char *ip, const int len )
{
    char    str[ 32 ];
    __int64 ans;

    memcpy(str,ip,len);
    str[len] = '\0';
    ans = _atoi64(str);
    return ans;
} 

static double my_atof(const char*ip, int len, int ndp)
{
    char	str[32];
    double	ans;

    if (ndp<len)
        memcpy(str,ip,len-ndp);
    str[len-ndp] = '.';

    if (ndp>0)
        memcpy(&str[len-ndp+1],&ip[len-ndp],ndp);
    str[len+1] = '\0';

    ans = atof(str);
    return ans;
}

static long long my_byte_reverse(long long llVal)
{
    char *p=reinterpret_cast<char*> (&llVal);
    std::reverse(p, p+sizeof(llVal));
    return llVal;

}
#endif

//////////////////////////////////////////////////////////////////////////
CString GetExePath()
{

    CString strExePath;

    TCHAR   filename[MAX_PATH] = {0};
    ::GetModuleFileName(NULL,filename,MAX_PATH);  
    CString strExeFileName   = filename;   
    strExePath = strExeFileName.Left(strExeFileName.ReverseFind('\\'))+_T("\\"); 

    return strExePath;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
BOOL IsBinString(CString str)
{
	for (int i=0; i<str.GetLength(); i++)
		if (str[i]!='0' && str[i]!='1') return FALSE;
	return TRUE;
}

BOOL ConvertIntToBinStr(int iDecValue, char *pBinStr, UINT nLen)
{
	char szBinString[64];

	if( pBinStr == NULL ) return FALSE;

	_itoa_s(iDecValue, szBinString, 2);
	if(strlen(szBinString) > nLen)
	{
		memset(pBinStr, '*', nLen);
		pBinStr[nLen-1] = 0;
		return FALSE;
	}

	memset(pBinStr, '0', nLen);
	pBinStr += nLen-strlen(szBinString);
	strcpy_s(pBinStr, sizeof(szBinString),szBinString);
	return TRUE;
}

void CovertByteBufToBinString(const BYTE* pByteBuf,int iByteBufLen,
													CString& strBin)
{
	char cTemp[10];
	WORD j = 0;
	for(int i=0; (i<iByteBufLen); i++, j+=8){
		
		// 先将十进制转换为二进制
		_itoa_s(pByteBuf[i],cTemp,2);

		// 补足8位
		CString strTemp(cTemp);
		strTemp.MakeReverse();
		int iLen = strTemp.GetLength();
		for(int n=0; n<8-iLen; n++){
			strTemp += _T("0");
		}
		strTemp.MakeReverse();

		//
		strBin += strTemp;
	}
}
int ConvertBinStringToInt(CString strBinStr)
{
	int iBit = 1;
	int iData = 0;

	for(int i=strBinStr.GetLength()-1; i>=0; i--, iBit<<=1)
		switch(strBinStr[i])
		{
		case '1': iData |= iBit;
		case '0': break;
		default: return -1;
		}

	return iData;
}


//从一个字符串中得到元素的个数，元素以cCompart符号分隔
int GetItemSum(CString strSource, char cCompart)
{
    if ( strSource.IsEmpty() )
    {
        return 0;
    }
    //---------------------------
    int iItemSum = 0;
    LPCTSTR cp,cq;
    cq = cp = (LPCTSTR)strSource;
    //得到cCompart的总个数
    while ( *cp != '\0' )
    {
        if ( *cp == cCompart )
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
    cp = (LPCTSTR)strSource;
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

//从一个字符串中得到第iIndex个字符串,字符串间以strDelimiter分隔
TString GetSFStr(const TString& strSource, const int &iIndex, const TString& strDelimiter)
{
    int iCount = -1;

    size_t iLenDelimiter = strDelimiter.length();

    TString strElement;
    size_t iOldFindStartPos = 0;
    size_t iNewFindStartPos;

    do
    {
        iNewFindStartPos = strSource.find(strDelimiter,iOldFindStartPos);
        if (iNewFindStartPos!=TString::npos)
        {
            strElement = strSource.substr(iOldFindStartPos,iNewFindStartPos-iOldFindStartPos);
            iCount ++;
            if (iCount==iIndex)
            {
                return strElement;
            }
        }
        else
        {
            break;
        }

        iOldFindStartPos = iNewFindStartPos+iLenDelimiter;

    }while (iNewFindStartPos!=TString::npos);

    // 
    if (iOldFindStartPos<=strSource.length()-1)
    {
        strElement = strSource.substr(iOldFindStartPos,strSource.length()-iOldFindStartPos);
        iCount ++;
        if (iCount==iIndex)
        {
            return strElement;
        }
    }
	
    return _T("");
}

//////////////////////////////////////////////////////////////////////////
__int64 PickupDigit(const CString& chSource, const int &iIndex)
{
    TCHAR chNum[20];

    LPCTSTR cp = chSource;
    while( !::isdigit(*(cp+0)) && *cp!='\0' )
    {
        cp++;
    }//cp此时指向chSource字符串中第一个数字字符处

    LPCTSTR cq = cp;
    WORD iOrder = 0;

    while (*cp != '\0' )
    {
        //当前字符为数字且前一个字符不是数字时，数字个数加一
        if( ::isdigit( *(cp+0) ) && !::isdigit( *(cq+0) ) )
        {
            iOrder++;
        }
        //找到第iIndex个整数，取出整数,返回.
        if( iOrder == iIndex)
        {
            BYTE i = 0;

            while( ::isdigit(*(cp+0)) )
            {
                chNum[i] = *cp;
                i++;
                cp++;
            }
            chNum[i] = '\0';
            return _tcstol(chNum,NULL,10);
            break;
        }
        //
        cq = cp;
        cp++;
    }
    //--------------
    return 0;
}
//从一个字符串中得到第iIndex个整数
__int64  GetNFStr(const CString& strSource, const int &iIndex,const CString& strDelimiter)
{
    TString source,delimiter;
    source = (LPCTSTR)strSource;
    delimiter = (LPCTSTR)strDelimiter;
    return  _tcstoul(GetSFStr(source,iIndex,delimiter).c_str(),NULL,10);
}
// 
double GetFloatFromStr(const CString& strSource,
                       const int &iIndex, const CString& strDelimiter)
{
    TString source,delimiter;
    source = (LPCTSTR)strSource;
    delimiter = (LPCTSTR)strDelimiter;
    return _tcstod(GetSFStr(source,iIndex,delimiter).c_str(),NULL);
}
unsigned long StrHextoDeci( LPCTSTR chNum )
{
    return _tcstoul(chNum,NULL,16);
}

//////////////////////////////////////////////////////////////////////////
// 
void GetFormattedStrList(const CStringList& strList,
                            const CString& strDelimiter,
                            CString& strResult)
{
    CString strElement;

    POSITION pos = strList.GetHeadPosition();
    if (pos)
    {
        strResult += strDelimiter;
    }

    while (pos)
    {
        strElement = strList.GetNext(pos);
        strResult = strResult + strElement + strDelimiter;
    }
}

//////////////////////////////////////////////////////////////////////////
// 
void ParseFormattedString( const CString& strFmtLine,
                           const CString& strDelimiter,
                           CStringList& strList)
{
    int iLenDelimiter = strDelimiter.GetLength();

    CString strElement;
    int iOldFindStartPos = 0;
    int iNewFindStartPos;

    do
    {
        iNewFindStartPos = strFmtLine.Find(strDelimiter,iOldFindStartPos);
        if (iNewFindStartPos>0)
        {
            strElement = strFmtLine.Mid(iOldFindStartPos,iNewFindStartPos-iOldFindStartPos);
            strList.AddTail(strElement);
        }
        else if (iNewFindStartPos<0)
        {
            break;
        }

        iOldFindStartPos = iNewFindStartPos+iLenDelimiter;

    }while (iNewFindStartPos!=-1);

    // 
    if (iOldFindStartPos<=strFmtLine.GetLength()-1)
    {
        strElement = strFmtLine.Mid(iOldFindStartPos,strFmtLine.GetLength()-iOldFindStartPos);
        strList.AddTail(strElement);
    }
}


/*########################################################################
------------------------------------------------
数值类型转换
------------------------------------------------
########################################################################*/
COleDateTime vartodate(const _variant_t& var)
{
    COleDateTime value;
    switch (var.vt) 
    {
    case VT_DATE:
        {
            value = var.date;
        }
        break;
    case VT_EMPTY:
    case VT_NULL:
        value.SetStatus(COleDateTime::null);
        break;
    default:
        value.SetStatus(COleDateTime::null);
        XTRACE(_T("Warning: 未处理的 _variant_t 类型值; 文件: %s; 行: %d\n"), _T(__FILE__), __LINE__);
    }
    return value;
}

COleCurrency vartocy(const _variant_t& var)
{
    COleCurrency value;
    switch (var.vt) 
    {
    case VT_CY:
        value = (CURRENCY)var.cyVal;
        break;
    case VT_EMPTY:
    case VT_NULL:
        value.m_status = COleCurrency::null;
        break;
    default:
        value.m_status = COleCurrency::null;
        XTRACE(_T("Warning: 未处理的 _variant_t 类型值; 文件: %s; 行: %d\n"), _T(__FILE__), __LINE__);
    }
    return value;
}

bool vartobool(const _variant_t& var)
{
    bool value = false;
    switch (var.vt)
    {
    case VT_BOOL:
        value = var.boolVal ? true : false;
    case VT_EMPTY:
    case VT_NULL:
        break;
    default:
        XTRACE(_T("Warning: 未处理的 _variant_t 类型值; 文件: %s; 行: %d\n"), _T(__FILE__), __LINE__);
    }
    return value;
}

BYTE vartoby(const _variant_t& var)
{
    BYTE value = 0;
    switch (var.vt)
    {
    case VT_DECIMAL:
    case VT_I1:
    case VT_UI1:
        value = var.bVal;
        break;
    case VT_NULL:
    case VT_EMPTY:
        value = 0;
        break;
    default:
        XTRACE(_T("Warning: 未处理的 _variant_t 类型值; 文件: %s; 行: %d\n"), _T(__FILE__), __LINE__);
    }	
    return value;
}

short vartoi(const _variant_t& var)
{
    short value = 0;
    switch (var.vt)
    {
    case VT_BOOL:
        value = var.boolVal;
        break;
    case VT_UI1:
    case VT_I1:
        value = var.bVal;
        break;
    case VT_I2:
    case VT_UI2:
        value = var.iVal;
        break;
    case VT_NULL:
    case VT_EMPTY:
        value = 0;
        break;
    default:
        XTRACE(_T("Warning: 未处理的 _variant_t 类型值; 文件: %s; 行: %d\n"), _T(__FILE__), __LINE__);
    }	
    return value;
}

long vartol(const _variant_t& var)
{
    long value = 0;
    switch (var.vt)
    {
    case VT_BOOL:
        value = var.boolVal;
        break;
    case VT_UI1:
    case VT_I1:
        value = var.bVal;
        break;
    case VT_UI2:
    case VT_I2:
        value = var.iVal;
        break;
    case VT_I4:
    case VT_UI4:
        value = var.lVal;
        break;
    case VT_INT:
        value = var.intVal;
        break;
    case VT_R4:
        value = (long)(var.fltVal + 0.5);
        break;
    case VT_R8:
        value = (long)(var.dblVal + 0.5);
        break;
    case VT_DECIMAL:
        value = (long)var;
        break;
    case VT_CY:
        value = (long)var;
        break;
    case VT_BSTR://字符串
    case VT_LPSTR://字符串
    case VT_LPWSTR://字符串
        value = _tcstol((LPCTSTR)(_bstr_t)var,NULL,10);
        break;
    case VT_NULL:
    case VT_EMPTY:
        value = 0;
        break;
    default:
        XTRACE(_T("Warning: 未处理的 _variant_t 类型值; 文件: %s; 行: %d\n"), _T(__FILE__), __LINE__);
    }
    return value;
}
__int64 vartoi64(const _variant_t& var)
{
    __int64 value = 0;
    switch (var.vt)
    {
    case VT_BOOL:
        value = var.boolVal;
        break;
    case VT_UI1:
    case VT_I1:
        value = var.bVal;
        break;
    case VT_UI2:
    case VT_I2:
        value = var.iVal;
        break;
    case VT_I4:
    case VT_UI4:
        value = var.lVal;
        break;
    case VT_INT:
        value = var.intVal;
        break;
    case VT_R4:
        value = (__int64)(var.fltVal + 0.5);
        break;
    case VT_R8:
        value = (__int64)(var.dblVal + 0.5);
        break;
    case VT_DECIMAL:
        value = (__int64)var.llVal;
        break;
    case VT_CY:
        value = (__int64)(var.cyVal.int64);
        break;
    case VT_BSTR://字符串
    case VT_LPSTR://字符串
    case VT_LPWSTR://字符串
        value = _tcstoul((LPCTSTR)(_bstr_t)var,NULL,10);
        break;
    case VT_NULL:
    case VT_EMPTY:
        value = 0;
        break;
    default:
        XTRACE(_T("Warning: 未处理的 _variant_t 类型值; 文件: %s; 行: %d\n"), _T(__FILE__), __LINE__);
    }
    return value;
}
double vartof(const _variant_t& var)
{
    double value = 0;
    switch (var.vt)
    {
    case VT_R4:
        value = var.fltVal;
        break;
    case VT_R8:
        value = var.dblVal;
        break;
    case VT_DECIMAL:
        value = (double)var;
        break;
    case VT_CY:
        value = (double)var;
        break;
    case VT_BOOL:
        value = var.boolVal;
        break;
    case VT_UI1:
    case VT_I1:
        value = var.bVal;
        break;
    case VT_UI2:
    case VT_I2:
        value = var.iVal;
        break;
    case VT_UI4:
    case VT_I4:
        value = var.lVal;
        break;
    case VT_INT:
        value = var.intVal;
        break;
    case VT_BSTR://字符串
    case VT_LPSTR://字符串
    case VT_LPWSTR://字符串
        value = _tcstod((LPCTSTR)(_bstr_t)var,NULL);
        break;
    case VT_NULL:
    case VT_EMPTY:
        value = 0;
        break;
    default:
        value = 0;
        XTRACE(_T("Warning: 未处理的 _variant_t 类型值; 文件: %s; 行: %d\n"), _T(__FILE__), __LINE__);
    }
    return value;
}

CString vartostr(const _variant_t &var)
{
    CString strValue;

    switch (var.vt)
    {
    case VT_BSTR://字符串
    case VT_LPSTR://字符串
    case VT_LPWSTR://字符串
        strValue = (LPCTSTR)(_bstr_t)var;
        break;
    case VT_I1:
    case VT_UI1:
        strValue.Format(_T("%d"), var.bVal);
        break;
    case VT_I2://短整型
        strValue.Format(_T("%d"), var.iVal);
        break;
    case VT_UI2://无符号短整型
        strValue.Format(_T("%d"), var.uiVal);
        break;
    case VT_INT://整型
        strValue.Format(_T("%d"), var.intVal);
        break;
    case VT_I4: //整型
        strValue.Format(_T("%d"), var.lVal);
        break;
    case VT_I8: //长整型
        strValue.Format(_T("%d"), var.lVal);
        break;
    case VT_UINT://无符号整型
        strValue.Format(_T("%d"), var.uintVal);
        break;
    case VT_UI4: //无符号整型
        strValue.Format(_T("%d"), var.ulVal);
        break;
    case VT_UI8: //无符号长整型
        strValue.Format(_T("%d"), var.ulVal);
        break;
    case VT_VOID:
        strValue.Format(_T("%8x"), var.byref);
        break;
    case VT_R4://浮点型
        strValue.Format(_T("%.4f"), var.fltVal);
        break;
    case VT_R8://双精度型
        strValue.Format(_T("%.8f"), var.dblVal);
        break;
    case VT_DECIMAL: //小数
        strValue.Format(_T("%.8f"), (double)var);
        break;
    case VT_CY:
        {
            COleCurrency cy = var.cyVal;
            strValue = cy.Format();
        }
        break;
    case VT_BLOB:
    case VT_BLOB_OBJECT:
    case 0x2011:
        strValue = _T("[BLOB]");
        break;
    case VT_BOOL://布尔型
        strValue = var.boolVal ? _T("TRUE") : _T("FALSE");
        break;
    case VT_DATE: //日期型
        {
            DATE dt = var.date;
            COleDateTime da = COleDateTime(dt); 
            strValue = da.Format(_T("%Y-%m-%d %H:%M:%S"));
        }
        break;
    case VT_NULL://NULL值
        strValue = "";
        break;
    case VT_EMPTY://空
        strValue = "";
        break;
    case VT_UNKNOWN://未知类型
    default:
        strValue = _T("UN_KNOWN");
        break;
    }
    return strValue;
}
