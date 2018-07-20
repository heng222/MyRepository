/**
* @file GM_CRC32.h
* @brief
* @author  CRC封装,不太完整,之后再进行封装
* @date 
* @version
* <pre><b>copyright: 

*/
#ifndef _GM_CRC32_H
#define _GM_CRC32_H

#include "GM_CRC_Table32.h"

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */

#define GM_CRC32_SIZE_BYTE (4U) /**< CRC32的字节数 */
#define GM_CRC32_SIZE_BIT (32U) /**< CRC32的位数   */

    /**
    * @brief GM_CRC_Calculate_CRC32
    *
    * Detailed description.
    * @param[in] pBuffer 被校验的数据
    * @param[in] bufferLen 被校验的数据长度(字节)
    * @param[in] pCRC 返回CRC校验码
    * @param[in] pCRCTable CRC表
    * @return GM_BOOL
    */
    GM_BOOL GM_CRC_Calculate_CRC32(const GM_UINT8* pBuffer, GM_UINT32 bufferLen, GM_UINT32* pCRC, const GM_UINT32* pCRCTable);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_CRC_H */

