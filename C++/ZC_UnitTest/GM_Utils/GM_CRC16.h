/**
* @file GM_CRC16.h
* @brief
* @author 
* @date 
* @version
* <pre><b>copyright: 

*/
#ifndef _GM_CRC16_H
#define _GM_CRC16_H

#include "GM_CRC_Table16.h"

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */

#define GM_CRC16_SIZE_BYTE (2U) /**< CRC16的字节数 */
#define GM_CRC16_SIZE_BIT (16) /**< CRC16的位数   */

    /**
    * @brief
    *
    * 根据种子和顺序决定CRC校验码
    * @param[in] pBuffer 被校验的数据
    * @param[in] bufferLen 被校验的数据长度(字节)
    * @param[in] pCRC 返回CRC校验码
    * @param[in] pCRCTable CRC表
    * @return GM_BOOL GM_CRC_Calculate_CRC16
    */
    GM_BOOL GM_CRC_Calculate_CRC16(const GM_UINT8 *pBuffer, GM_UINT32 bufferLen, GM_UINT16* pCRC, const GM_UINT16* pCRCTable);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_CRC_H */

