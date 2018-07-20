/********************************************************
*                                                                                                            
* 文 件 名： MemSet.c
* 版权说明：  
* 创建时间： 2013-10-25
* 作    者： 郭文章
* 功能描述： 进行初始化赋值函数 
* 修改记录：   
*
********************************************************/
#include "MemSet.h"
#include "string.h"

/*
*  功能描述：  内存数据初始化
*  参数说明：  
*  返回值：    
*/
UINT8_S MemorySet(void* pDest, UINT32_S destBuffSize, UINT8_S c, UINT32_S count)
{
    UINT8_S Result = 0; /* 返回结果 */

    if((count > destBuffSize) || (NULL == pDest))
    { 
        /* 赋值长度异常或为空指针，不赋值*/
        Result = 0;
    }
    else 
    {
        /*内存赋值*/
        memset(pDest,c,count);
        Result = 1;
    }

    return Result;
}

