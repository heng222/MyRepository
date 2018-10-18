
/************************************************************************
*
* �ļ���   ��  TMCommCRC32.h
* ��Ȩ˵�� ��  ������ģ�Ƽ��������ι�˾ 
* �汾��   ��  1.0
* ����ʱ�� ��  2015.05.21
* �������� ��  ����32λCRC����  
* ʹ��ע�� �� 
* �޸ļ�¼ ��  
*
************************************************************************/

#ifndef TM_COMM_CRC32_H_
#define TM_COMM_CRC32_H_

#include "CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif



/*
*  ���������� CRC32����������������£�ע�⣺����CRC�Ǵ��������ݵ�һ���ֽڵ����BIT��ʼ��
*  ����˵����
*             pData,    ����ָ��
*             DataLen,  ���ݳ��ȣ��ֽڣ�
*  ����ֵ��   ����ֵΪCRCֵ
*/
UINT32_S Crc32(const UINT8_S *pData,UINT32_S DataLen);


#ifdef __cplusplus
}
#endif

#endif
