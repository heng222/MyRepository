/********************************************************
*                                                                                                            
* 文 件 名： MemSet.h
* 版权说明：  
* 创建时间： 2013-10-25
* 作    者： 
* 功能描述： 进行初始化赋值函数头文件
* 修改记录：   
*
********************************************************/
#ifndef MEMSET_H_
#define MEMSET_H_

#include "CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

/*
*  功能描述：  内存数据初始化
*  参数说明：  
*  返回值：    
*/
UINT8_S MemorySet(void* pDest, UINT32_S destBuffSize, UINT8_S c, UINT32_S count);

#ifdef __cplusplus
}
#endif

#endif
