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
    * �����׼CRC32
    * @param[in] Data ��У�������
    * @param[in] DataLen ��У������ݳ���(�ֽ�)
	* @param[in] Poly CRC16���õĶ���ʽ
    * @param[in] pCRCTable CRC��
    * @param[in] pCRC ����CRCУ����   
    * @return GM_BOOL GM_CRC_Calculate_CRC32_Standard
	*/

    GM_BOOL GM_CRC_Calculate_CRC32_Standard(GM_UINT8* Data, GM_UINT32 DataLen, GM_UINT32 Poly, const GM_UINT32* pCRC32Table, GM_UINT32* pCRC);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif 

