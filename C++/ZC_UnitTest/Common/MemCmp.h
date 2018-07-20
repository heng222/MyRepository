/********************************************************
*                                                                                                            
* �� �� ���� MemCmp.h
* ��Ȩ˵����  
* ����ʱ�䣺 2015-09-20
* ��    �ߣ� 
* �����������Ƚ��ڴ�����
* �޸ļ�¼��   
*
********************************************************/
#ifndef MEMCMP_H_
#define MEMCMP_H_

#include "CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

/*
*  ����������  �Ƚ��ڴ�����
*  ����˵����  
*  ����ֵ      ��    1,�Ƚ���ͬ��0,�Ƚϲ���ͬ
*/
UINT8_S MemoryCmp(const void* pBuf1, UINT32_S buf1Len, const void* pBuf2,UINT32_S buf2Len);

#ifdef __cplusplus
}
#endif

#endif

