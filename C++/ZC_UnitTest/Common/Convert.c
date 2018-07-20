/********************************************************
*                                                                                                            
* 文 件 名： Convert.c
* 版权说明：  
* 创建时间： 2013-10-25
* 作    者： 
* 功能描述： 通用类型转换函数 
* 修改记录：   
*
********************************************************/
#include "Convert.h"

/*
*  功能描述：  用于将2字节数据变为UINT16， BIG endian
*  参数说明：  pInput, 为输入
*  返回值：    变换后的UINT16值
*/
UINT16_S ShortFromChar(const UINT8_S *pInput)
{
    UINT16_S Tempshort = 0u;
    if(NULL != pInput)
    {
        Tempshort = ( *(pInput) );
        Tempshort =(UINT32_S)(((UINT32_S)Tempshort << 8 ) + ( *(pInput + 1) ));  
    }
    return Tempshort;
}

/*
*  功能描述：  用于将4字节数据变为UINT32， BIG endian
*  参数说明：  pInput, 为输入
*  返回值：    变换后的UINT32值
*/
UINT32_S LongFromChar(const UINT8_S *pInput)
{
    UINT32_S Templong = 0u;
    if(NULL != pInput)
    {
        Templong = ( *(pInput) );
        Templong = ( Templong<<8 ) + ( *(pInput+1) );
        Templong = ( Templong<<8 ) + ( *(pInput+2) );
        Templong = ( Templong<<8 ) + ( *(pInput+3) );
    }
    return Templong;
}

/*
*  功能描述：  将2个字节长的整型变为字节表示  BIG endian
*  参数说明：  Input, 为输入
*              pOutput,为输出
*  返回值：  
*/
void ShortToChar ( UINT16_S Input, UINT8_S *pOutput)
{
    if(NULL != pOutput)
    {
        *pOutput =  (Input>>8) & 0xffu;
        *(pOutput + 1) = Input & 0xffu;
    }
}

/*
*  功能描述：  将3个字节长的整型变为字节表示  BIG endian
*  参数说明：  Input, 为输入
*              pOutput,为输出
*  返回值：  
*/
void ThreeToChar ( UINT32_S Input, UINT8_S *pOutput)
{
    if(NULL != pOutput)
    {
        if(Input <= 0xFFFFFFu)
        {
            *pOutput =  (UINT8_S)((Input>>16) & 0xffu);
            *(pOutput + 1) =  (UINT8_S)((Input>>8) & 0xffu);
            *(pOutput + 2) = (UINT8_S)(Input & 0xffu);
        }
    }
}

/*
*  功能描述：  将4个字节长的整型变为字节表示  BIG endian
*  参数说明：  Input, 为输入
*              pOutput,为输出
*  返回值：  
*/
void LongToChar(UINT32_S Input, UINT8_S *pOutput)
{
    if(NULL != pOutput)
    {
        *pOutput =  (UINT8_S)((Input>>24) & 0xffu);
        *(pOutput + 1) =  (UINT8_S)((Input>>16) & 0xffu);
        *(pOutput + 2) =  (UINT8_S)((Input>>8) & 0xffu);
        *(pOutput + 3) = (UINT8_S)(Input & 0xffu);
    }
}




/*
*  功能描述：  用于将UINT8变为UINT16， LITTLE endian
*  参数说明：  pInput, 为输入
*  返回值：    变换后的UINT16值
*/
UINT16_S ShortFromCharLE(const UINT8_S *pInput)
{
    UINT16_S Tempshort = 0u;
    if(NULL != pInput)
    {
        Tempshort = ( *(pInput+1) );
        Tempshort = (UINT16_S)(((UINT32_S)Tempshort<<8 ) + ( *(pInput) ));  
    }
    return Tempshort;
}

/*
*  功能描述：  用于将UINT8变为UINT32， LITTLE endian
*  参数说明：  pInput, 为输入
*  返回值：    变换后的UINT32值
*/
UINT32_S LongFromCharLE(const UINT8_S *pInput)
{
    UINT32_S Templong = 0u;
    if(NULL != pInput)
    {
        Templong = ( *(pInput+3) );
        Templong = ( Templong<<8 ) + ( *(pInput+2) );
        Templong = ( Templong<<8 ) + ( *(pInput+1) );
        Templong = ( Templong<<8 ) + ( *(pInput) );
    }
    return Templong;
}

/*
*  功能描述： 将2个字节的整型变为字节表示  LITTLE endian
*  参数说明： Input, 为输入
*             pOutput,为输出
*  返回值： 
*/
void ShortToCharLE ( UINT16_S Input, UINT8_S *pOutput)
{
    if(NULL != pOutput)
    {
        *(pOutput + 1) =  (Input>>8) & 0xffu;
        *pOutput = Input & 0xffu;
    }
}

/*
*  功能描述： 将4个字节的整型变为字节表示  LITTLE endian
*  参数说明： Input, 为输入
*             pOutput,为输出
*  返回值： 
*/
void LongToCharLE(UINT32_S Input, UINT8_S *pOutput)
{
    if(NULL != pOutput)
    {
        *(pOutput + 3) =  (UINT8_S)((Input>>24) & 0xffu);
        *(pOutput + 2) =  ( UINT8_S)((Input>>16) & 0xffu);
        *(pOutput + 1) =  ( UINT8_S)((Input>>8) & 0xffu);
        *pOutput = ( UINT8_S)(Input & 0xffu);
    }
}
