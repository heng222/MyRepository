/********************************************************
*                                                                                                            
* 文 件 名： Malloc.c
* 版权说明：  
* 创建时间： 2013-10-25
* 作    者： 郭文章
* 功能描述： 内存分配函数 
* 修改记录：   
*
********************************************************/
#include "Malloc.h"
#include "stdlib.h"

/*
*  功能描述：  内存分配
*  参数说明：  
*  返回值：    
*/
void* MemoryMalloc(UINT32_S size)
{
    void* retFun = NULL;
    if (size > 0)
    {
        retFun = malloc(size);
    }
    else
    {
        retFun = NULL;
    }

    return retFun;
}

