/*
* ============================================================================
*  Name     : Internal module communication
*  Part of  : Auxiliary module
*  Created  : 19.11.2006 by HW
*  Description: Free
*     
*  Version  : 1.2
*  Copyright: Copyright (c) 2007-2010. DCL-CHARY Network Corporation Ltd.
* ============================================================================
*/

#if !defined _COMMONFUNC_H__2004_07_05_ZHANGHENG
#define _COMMONFUNC_H__2004_07_05_ZHANGHENG


#include "afx.h"
#include "CommonDefine.h"

//////////////////////////////////////////////////////////////////////////

#ifdef _BASIC_CLASS_PROJECT_
#define BSCEG_EXT_API __declspec(dllexport)
#else
#define BSCEG_EXT_API __declspec(dllimport)
#endif


//////////////////////////////////////////////////////////////////////////

#ifndef _BASIC_CLASS_PROJECT_
    #ifdef _DEBUG
        #ifdef _UNICODE
        #pragma comment( lib, "BscEgUD" )
        #else
        #pragma comment( lib, "BscEgD" )
        #endif
    #else
        #ifdef _UNICODE
        #pragma comment( lib, "BscEgU" )
        #else
        #pragma comment( lib, "BscEg" )
        #endif
    #endif
#endif


//////////////////////////////////////////////////////////////////////////

#ifndef IN
    #define IN
#endif

#ifndef OUT
    #define OUT
#endif

#ifndef IN_OUT
    #define IN_OUT
#endif

//////////////////////////////////////////////////////////////////////////


extern "C" BSCEG_EXT_API int g_iTest;

// �õ���ǰ��������·�� 
// #pragma message("�ѱ�CSysUtils::GetProcessHostPath���") 
extern "C++" BSCEG_EXT_API CString GetExePath();


/************************************************************************/
/*
    �������ж�һ���ַ����Ƿ��Ƕ������ַ���
*/
/************************************************************************/
extern "C++" BSCEG_EXT_API BOOL IsBinString(CString str);


/************************************************************************/
/* 
Description: ������ת��Ϊ�������ַ���
Example:
    ConvertToBinString(7,pBinStr,3) means pBinStr=="111"
    ConvertToBinString(7,pBinStr,4) means pBinStr=="00111"
    ConvertToBinString(7,pBinStr,8) means pBinStr=="00000111"
*/
extern "C++" BSCEG_EXT_API BOOL ConvertIntToBinStr(int iDecValue, 
                                                            char *pBinStr, UINT nLen);


/************************************************************************/
/*                                                                      
Description: ���������ַ���ת��Ϊ����ֵ

[IN strBinStr] : Դ�������ַ���

Example:
ASSERT(ConvertBinStringToInt("0111") == 7)
*/
extern "C++" BSCEG_EXT_API int ConvertBinStringToInt(CString strBinStr);


/************************************************************************/
/*
Description: ���ֽ�����ת���ɶ������ַ���
    [in]pByteBuf:		Դ�ֽ�����
    [in]iByteBufLen:	���鳤��
    [out]strBin:		ת���������

    EXAPLE: 
    BYTE buffer[20] = {0x11,0x12,0x13,0x14,0x15};
    CString strTemp;

    CovertByteBufToBinString(buffer,2,strTemp);
    ASSERT(strTemp=="0001000100010010");
*/
extern "C++" BSCEG_EXT_API void CovertByteBufToBinString(const BYTE* pByteBuf,
                                                         int iByteBufLen,
                                                         CString& strBin);



/************************************************************************/
/*                                                                      
Description: ��һ���ַ�������ȡ����

[IN strSource] : Դ�ַ���
[IN iIndex] : ��N����ֵ
[cCompart]: �ָ���

Example:
ASSERT(PickupDigit("A12BC45D",0) == 12)
ASSERT(PickupDigit("A12BC45D",1) == 45)
*/
/************************************************************************/
extern "C++" BSCEG_EXT_API __int64 PickupDigit(const CString& strSource,
                                                        const int &iIndex);



/************************************************************************/
/*                                                                      
    Description: ��һ���ַ����еõ����ض��ָ����ָ��ĵ�iIndex������

    [IN strSource] : Դ�ַ���
    [IN iIndex] : ��N����ֵ
    [cCompart]: �ָ���
    
    Example:
    ASSERT(GetNFStr("1,2,ABC",0,",") == 2)
*/
/************************************************************************/
extern "C++" BSCEG_EXT_API __int64 GetNFStr(const CString& strSource,
                                            const int &iIndex, 
                                            const CString& strDelimiter);

extern "C++" BSCEG_EXT_API double GetFloatFromStr(const CString& strSource,
                                                  const int &iIndex, 
                                                  const CString& strDelimiter);

/************************************************************************/
/*
    Description: ��һ���ַ����еõ���iIndex���ַ���,�ַ�������cCompart�ָ�
    [strSource]:
    [iIndex]:
    [cCompart]:

    Example:
    ASSERT(GetSFStr("a,AbC,d",1,",") == "AbC")
*/
/************************************************************************/
extern "C++" BSCEG_EXT_API TString GetSFStr(const TString& strSource,
                                            const int &iIndex, 
                                            const TString& strDelimiter);


/************************************************************************/
// ��һ���ַ����еõ�Ԫ�صĸ�����Ԫ����cDelimiter���ŷָ�
/************************************************************************/
extern "C++" BSCEG_EXT_API int GetItemSum(CString strSource, char cDelimiter);


/************************************************************************/
// ����ʮ�����Ʊ�ʾ���ַ���ת��������
// ���磺 strHextoDeci("0011") = 0x11; 
//		 strHextoDeci("001A") = 0x1A = 26(Dec)
/************************************************************************/
extern "C++" BSCEG_EXT_API unsigned long StrHextoDeci( LPCTSTR chNum );


/**
    Description: �õ����ض����ŷָ����ַ����б�
    Example: 
    INPUT: strList = {"1","2"}; strDelimiter = "|"
    OUTPUT:strResult �� ��|1|2|��
*/
extern "C++" BSCEG_EXT_API void GetFormattedStrList( const CStringList& strList,
                                                     const CString& strDelimiter,
                                                     CString& strResult);

/**
    Description: �������ض����ŷָ����ַ���
    Example:
    INPUT: strFmtLine = "1|2|3"
    OUPUT: strList = {"1","2","3"}
*/
extern "C++" BSCEG_EXT_API void ParseFormattedString( const CString& strFmtLine,
                                                      const CString& strDelimiter,
                                                      CStringList& strList);



// ��ֵ����ת�� -----------------------------------
extern "C++" BSCEG_EXT_API COleDateTime vartodate(const _variant_t& var);
extern "C++" BSCEG_EXT_API COleCurrency vartocy(const _variant_t& var);
extern "C++" BSCEG_EXT_API bool vartobool(const _variant_t& var);
extern "C++" BSCEG_EXT_API BYTE vartoby(const _variant_t& var);
extern "C++" BSCEG_EXT_API short vartoi(const _variant_t& var);
extern "C++" BSCEG_EXT_API long vartol(const _variant_t& var);
extern "C++" BSCEG_EXT_API __int64 vartoi64(const _variant_t& var);
extern "C++" BSCEG_EXT_API double vartof(const _variant_t& var);
extern "C++" BSCEG_EXT_API CString vartostr(const _variant_t& var);


//////////////////////////////////////////////////////////////////////////














//////////////////////////////////////////////////////////////////////////
#endif	//_COMMONFUNC_H__