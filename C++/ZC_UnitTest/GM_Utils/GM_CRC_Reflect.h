/**
 * Copyright(C) 
 * 
 * @file:GM_CRC_Reflect.h
 * @brief:
 * @auther:
 * @create date:
 */

#ifndef _GM_CRC_REFLECT
#define _GM_CRC_REFLECT

#include "GM_Utils_Base.h"

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */

    /**
    * @brief
    *
    * 反转二进制序列
    * @param[in] reflect 待反转的二进制序列
    * @param[in] ch 需要反转的二进制比特数
    * @return GM_UINT32 反转后的二进制序列
    */
    GM_UINT32 GM_CRC_Reflect(GM_UINT32 reflect, GM_UINT32 ch);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_CRC_H */

