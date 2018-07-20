/********************************************************
*                                                                                                            
* 文 件 名： Malloc.h
* 版权说明：  
* 创建时间： 2013-10-25
* 作    者： 
* 功能描述： 内存分配函数头文件
* 修改记录：   
*
********************************************************/
#ifndef MALLOC_H_
#define MALLOC_H_

#include "CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


/*
*  功能描述：  内存分配
*  参数说明：  
*  返回值：    
*/
void* MemoryMalloc(UINT32_S size);



#ifdef __cplusplus
}
#endif

#endif
