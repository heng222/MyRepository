/**
* @file GM_CRC_Table32.h
* @brief 常用CRC查表用的表
* @author Hao Liming
* @date 2010-3-3 14:06:41
* @version
* <pre><b>copyright: CASCO</b></pre>
* <pre><b>email: </b>haoliming@casco.com.cn</pre>
* <pre><b>company: </b>http://www.casco.com.cn</pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>Write modifications here.</pre>
*/
#ifndef _GM_CRC_TABLE32_H
#define _GM_CRC_TABLE32_H

#include "GM_Utils_Base.h"
#include "GM_CRC_Reflect.h"

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */

	/** @brief FSFB2通道1用到的CRC表0x1100D4E63 */
    extern const GM_UINT32 GM_CRC32_Channel1_Table[];

    /** @brief FSFB2通道2用到的CRC表0x18CE56011 */
    extern const GM_UINT32 GM_CRC32_Channel2_Table[];
	
	/** @brief 多项式0x04C11DB7的CRC32颠倒表 */
	extern const GM_UINT32 GM_CRC32_Table_0x04C11DB7_L[];
    /**
    * @brief GM_CRC_Build_CRC32_Table
    *
    * 生成查表法计算32位CRC的表.
    * @param[in] polynomial 多项式
    * @param[out] pCRCTable 生成的表
    * @return GM_BOOL
    */
    GM_BOOL GM_CRC_Build_CRC32_Table(GM_UINT32 polynomial, GM_UINT32* pCRCTable);
#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_CRC_TABLE_H */


