/**
* @file GM_Memncomp.h
* @brief
* @author Hao Liming
* @date 2010-9-30 13:33:06
* @version
* <pre><b>copyright: CASCO</b></pre>
* <pre><b>email: </b>haoliming@casco.com.cn</pre>
* <pre><b>company: </b>http://www.casco.com.cn</pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>Write modifications here.</pre>
*/
#ifndef _GM_MEMNCOMP_H
#define _GM_MEMNCOMP_H

#include "GM_Utils_Base.h"

#ifdef WIN32
#include <malloc.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */

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
    GM_INT16 GM_memncomp(const GM_UINT8* pBufA, const GM_UINT8* pBufB, size_t size);

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
	GM_INT32 GM_memcmp(const void* pBufA, const void* pBufB, size_t size);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_MEMNCOMP_H */

