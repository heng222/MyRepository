/********************************************************
*                                                                                                            
* �� �� ���� MemSet.h
* ��Ȩ˵����  
* ����ʱ�䣺 2013-10-25
* ��    �ߣ� 
* ���������� ���г�ʼ����ֵ����ͷ�ļ�
* �޸ļ�¼��   
*
********************************************************/
#ifndef MEMSET_H_
#define MEMSET_H_

#include "CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

/*
*  ����������  �ڴ����ݳ�ʼ��
*  ����˵����  
*  ����ֵ��    
*/
UINT8_S MemorySet(void* pDest, UINT32_S destBuffSize, UINT8_S c, UINT32_S count);

#ifdef __cplusplus
}
#endif

#endif
