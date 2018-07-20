/**
* @file GM_Memncomp.c
* @brief
* @author 
* @date 
* @version


*/
#include "GM_Memncomp.h"

/**
* @brief GM_memncomp
*
* 对两个缓冲区的数据进行比较. 按字节 逐位比较
* @param[in] pBufA
* @param[in] pBufB
* @param[in] size
* @return GM_INT16 
* 返回 0表示 pBufA = pBufB
* 返回 -1表示 pBufA < pBufB
* 返回 1表示 pBufA > pBufB
* 返回-256 表示传入的pBufA或pBufB == NULL或size==0
*/
GM_INT16 GM_memncomp(const GM_UINT8* pBufA, const GM_UINT8* pBufB, size_t size)
{
    size_t i = 0U;

	if ((NULL == pBufA) || (NULL == pBufB) || (size == (size_t)0))
    {
        return -256;
    }

    for (i = (size_t)0u; i < size; ++i)
    {
        if (*(pBufA + i) > *(pBufB + i))
        {
            return 1;
        }
		
		if(*(pBufA + i) < *(pBufB + i))
		{
			return -1;
		}
    }

	return 0;
}

	/**
* @brief GM_memcmp
*
* 对两个缓冲区的数据进行比较.调用系统的 memcmp函数
* @param[in] pBufA
* @param[in] pBufB
* @param[in] size
* @return GM_INT32 
* 返回值与memcmp函数的返回值意义基本一样，区别在于：返回-256 表示传入的pBufA或pBufB == NULL或size==0
*/
GM_INT32 GM_memcmp(const void* pBufA, const void* pBufB, size_t size)
{
	if ((pBufA == NULL)||(pBufB == NULL) || (size == (size_t)0))
	{
		return (GM_INT32)-256;
	}

	return (GM_INT32)memcmp(pBufA, pBufB, size);

}
