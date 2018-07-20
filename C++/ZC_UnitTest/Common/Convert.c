/********************************************************
*                                                                                                            
* �� �� ���� Convert.c
* ��Ȩ˵����  
* ����ʱ�䣺 2013-10-25
* ��    �ߣ� 
* ���������� ͨ������ת������ 
* �޸ļ�¼��   
*
********************************************************/
#include "Convert.h"

/*
*  ����������  ���ڽ�2�ֽ����ݱ�ΪUINT16�� BIG endian
*  ����˵����  pInput, Ϊ����
*  ����ֵ��    �任���UINT16ֵ
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
*  ����������  ���ڽ�4�ֽ����ݱ�ΪUINT32�� BIG endian
*  ����˵����  pInput, Ϊ����
*  ����ֵ��    �任���UINT32ֵ
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
*  ����������  ��2���ֽڳ������ͱ�Ϊ�ֽڱ�ʾ  BIG endian
*  ����˵����  Input, Ϊ����
*              pOutput,Ϊ���
*  ����ֵ��  
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
*  ����������  ��3���ֽڳ������ͱ�Ϊ�ֽڱ�ʾ  BIG endian
*  ����˵����  Input, Ϊ����
*              pOutput,Ϊ���
*  ����ֵ��  
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
*  ����������  ��4���ֽڳ������ͱ�Ϊ�ֽڱ�ʾ  BIG endian
*  ����˵����  Input, Ϊ����
*              pOutput,Ϊ���
*  ����ֵ��  
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
*  ����������  ���ڽ�UINT8��ΪUINT16�� LITTLE endian
*  ����˵����  pInput, Ϊ����
*  ����ֵ��    �任���UINT16ֵ
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
*  ����������  ���ڽ�UINT8��ΪUINT32�� LITTLE endian
*  ����˵����  pInput, Ϊ����
*  ����ֵ��    �任���UINT32ֵ
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
*  ���������� ��2���ֽڵ����ͱ�Ϊ�ֽڱ�ʾ  LITTLE endian
*  ����˵���� Input, Ϊ����
*             pOutput,Ϊ���
*  ����ֵ�� 
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
*  ���������� ��4���ֽڵ����ͱ�Ϊ�ֽڱ�ʾ  LITTLE endian
*  ����˵���� Input, Ϊ����
*             pOutput,Ϊ���
*  ����ֵ�� 
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
