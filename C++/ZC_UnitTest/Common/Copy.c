/********************************************************
*                                                                                                            
* 文 件 名： Copy.c
* 版权说明：  
* 创建时间： 
* 作    者： 郭文章
* 功能描述： 复制函数 
* 修改记录：   
*
********************************************************/
#include "Copy.h"
#include "string.h"


/* 函数功能 : 内存拷贝函数。
*  参数说明 : void *pDest, 目的地址
*             UINT32_S destBuffSize, 缓冲区长度，最大可用拷贝的数据长度
*             const void *pSrc, 源地址
*             UINT32_S count, 拷贝长度
*  返回值:    1, 未拷贝，拷贝长度大于报警长度
*             0, 拷贝成功
*/
UINT8_S MemoryCpy(void *pDest, UINT32_S destBuffSize, const void *pSrc, UINT32_S count)
{
    UINT8_S Result = 0u; /* 返回结果 */

    if((count > destBuffSize) || (NULL == pDest) || (NULL == pSrc))
    { 
        /* 拷贝长度异常或为空指针，不拷贝*/
        Result = 1u;
    }
    else 
    {
        /*内存复制*/
        memcpy(pDest,pSrc,count);
        Result = 0u;

    }

    return Result;
}


