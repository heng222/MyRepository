/**
* @file GM_CRC32.h
* @brief
* @author  CRC��װ,��̫����,֮���ٽ��з�װ
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

#define GM_CRC32_SIZE_BYTE (4U) /**< CRC32���ֽ��� */
#define GM_CRC32_SIZE_BIT (32U) /**< CRC32��λ��   */

    /**
    * @brief GM_CRC_Calculate_CRC32
    *
    * Detailed description.
    * @param[in] pBuffer ��У�������
    * @param[in] bufferLen ��У������ݳ���(�ֽ�)
    * @param[in] pCRC ����CRCУ����
    * @param[in] pCRCTable CRC��
    * @return GM_BOOL
    */
    GM_BOOL GM_CRC_Calculate_CRC32(const GM_UINT8* pBuffer, GM_UINT32 bufferLen, GM_UINT32* pCRC, const GM_UINT32* pCRCTable);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_CRC_H */

