/********************************************************
*                                                                                                            
* 文 件 名： MemCmp.h
* 版权说明：  
* 创建时间： 2015-09-20
* 作    者： 
* 功能描述：比较内存数据
* 修改记录：   
*
********************************************************/
#ifndef MEMCMP_H_
#define MEMCMP_H_

#include "CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

/*
*  功能描述：  比较内存数据
*  参数说明：  
*  返回值      ：    1,比较相同；0,比较不相同
*/
UINT8_S MemoryCmp(const void* pBuf1, UINT32_S buf1Len, const void* pBuf2,UINT32_S buf2Len);

#ifdef __cplusplus
}
#endif

#endif

