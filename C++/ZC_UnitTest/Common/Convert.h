/********************************************************
*                                                                                                            
* �� �� ���� Convert.h
* ��Ȩ˵����  
* ����ʱ�䣺 2013-10-25
* ��    �ߣ� 
* ���������� ͨ������ת������ͷ�ļ�
* �޸ļ�¼��   
*
********************************************************/
#ifndef CONVERT_H_
#define CONVERT_H_

#include "CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif


/*
*  ����������  ���ڽ�2�ֽ����ݱ�ΪUINT16�� BIG endian
*  ����˵����  pInput, Ϊ����
*  ����ֵ��    �任���UINT16ֵ
*/
UINT16_S ShortFromChar(const UINT8_S *pInput);

/*
*  ����������  ���ڽ�4�ֽ����ݱ�ΪUINT32�� BIG endian
*  ����˵����  pInput, Ϊ����
*  ����ֵ��    �任���UINT32ֵ
*/
UINT32_S LongFromChar(const UINT8_S *pInput);


/*
*  ����������  ��2���ֽڳ������ͱ�Ϊ�ֽڱ�ʾ  BIG endian
*  ����˵����  Input, Ϊ����
*              pOutput,Ϊ���
*  ����ֵ��  
*/
void ShortToChar ( UINT16_S Input, UINT8_S *pOutput);

/*
*  ����������  ��3���ֽڳ������ͱ�Ϊ�ֽڱ�ʾ  BIG endian
*  ����˵����  Input, Ϊ����
*              pOutput,Ϊ���
*  ����ֵ��  
*/
void ThreeToChar ( UINT32_S Input, UINT8_S *pOutput);

/*
*  ����������  ��4���ֽڳ������ͱ�Ϊ�ֽڱ�ʾ  BIG endian
*  ����˵����  Input, Ϊ����
*              pOutput,Ϊ���
*  ����ֵ��  
*/
void LongToChar(UINT32_S Input, UINT8_S *pOutput);



/*
*  ����������  ���ڽ�UINT8��ΪUINT16�� LITTLE endian
*  ����˵����  pInput, Ϊ����
*  ����ֵ��    �任���UINT16ֵ
*/
UINT16_S ShortFromCharLE(const UINT8_S *pInput);


/*
*  ����������  ���ڽ�UINT8��ΪUINT32�� LITTLE endian
*  ����˵����  pInput, Ϊ����
*  ����ֵ��    �任���UINT32ֵ
*/
UINT32_S LongFromCharLE(const UINT8_S *pInput);

/*
*  ���������� ��2���ֽڵ����ͱ�Ϊ�ֽڱ�ʾ  LITTLE endian
*  ����˵���� Input, Ϊ����
*             pOutput,Ϊ���
*  ����ֵ�� 
*/
void ShortToCharLE ( UINT16_S Input, UINT8_S *pOutput);

/*
*  ���������� ��4���ֽڵ����ͱ�Ϊ�ֽڱ�ʾ  LITTLE endian
*  ����˵���� Input, Ϊ����
*             pOutput,Ϊ���
*  ����ֵ�� 
*/
void LongToCharLE(UINT32_S Input, UINT8_S *pOutput);


#ifdef __cplusplus
}
#endif

#endif
