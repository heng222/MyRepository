/********************************************************
*                                                                                                            
* 文 件 名： MemCmp.c
* 版权说明：  
* 创建时间： 2013-10-25
* 作    者： 郭文章
* 功能描述： 进行初始化赋值函数 
* 修改记录：   
*
********************************************************/
#include "MemCmp.h"
#include "string.h"

/*
*  功能描述：  比较内存数据
*  参数说明：  
*  返回值      ：    1,比较相同；0,比较不相同
*/
UINT8_S MemoryCmp(const void* pBuf1, UINT32_S buf1Len, const void* pBuf2,UINT32_S buf2Len)
{
    UINT8_S retVal = 0u; /* 返回结果 */
    INT32_S funcVal = 0;

    if((NULL != pBuf1) && (NULL != pBuf2))
    {
        if(buf1Len != buf2Len)
        {
            retVal = 0u;
        }
        else
        {
            funcVal = memcmp(pBuf1,pBuf2,buf1Len);
            if( 0 == funcVal)
            {
                retVal = 1u;
            }
            else
            {
                retVal = 0u;
            }
        }
    }

    return retVal;
}
