/********************************************************
*                                                                                                            
* �� �� ���� Copy.h
* ��Ȩ˵����  
* ����ʱ�䣺 2013-10-25
* ��    �ߣ� 
* ���������� ���ƺ���ͷ�ļ�
* �޸ļ�¼��   
*
********************************************************/
#ifndef COPY_H_
#define COPY_H_

#include "CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


/* �������� : �ڴ濽��������
*  ����˵�� : void *pDest, Ŀ�ĵ�ַ
*             UINT32_S destBuffSize, ���������ȣ������ÿ��������ݳ���
*             const void *pSrc, Դ��ַ
*             UINT32_S count, ��������
*  ����ֵ:    1, δ�������������ȴ��ڱ�������
*             0, �����ɹ�
*/
UINT8_S MemoryCpy(void *pDest, UINT32_S destBuffSize, const void *pSrc, UINT32_S count);









#ifdef __cplusplus
}
#endif

#endif
