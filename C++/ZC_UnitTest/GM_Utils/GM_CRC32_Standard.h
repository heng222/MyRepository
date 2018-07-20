/**
 * Copyright(C) 2012
 * 
 * @file:GM_CRC32_Standard.h
 * @brief:
 * @auther:
 * @create date:

 */


#ifndef _GM_CRC32_STARDAND_H
#define _GM_CRC32_STARDAND_H


#include "GM_CRC_Table32.h"

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */

    /**
    * @brief
    *
    * 计算标准CRC32
    * @param[in] Data 被校验的数据
    * @param[in] DataLen 被校验的数据长度(字节)
	* @param[in] Poly CRC16采用的多项式
    * @param[in] pCRCTable CRC表
    * @param[in] pCRC 返回CRC校验码   
    * @return GM_BOOL GM_CRC_Calculate_CRC32_Standard
	*/

    GM_BOOL GM_CRC_Calculate_CRC32_Standard(GM_UINT8* Data, GM_UINT32 DataLen, GM_UINT32 Poly, const GM_UINT32* pCRC32Table, GM_UINT32* pCRC);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif 

