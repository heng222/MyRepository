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

#define GM_CRC16_SIZE_BYTE (2U) /**< CRC16���ֽ��� */
#define GM_CRC16_SIZE_BIT (16) /**< CRC16��λ��   */

    /**
    * @brief
    *
    * �������Ӻ�˳�����CRCУ����
    * @param[in] pBuffer ��У�������
    * @param[in] bufferLen ��У������ݳ���(�ֽ�)
    * @param[in] pCRC ����CRCУ����
    * @param[in] pCRCTable CRC��
    * @return GM_BOOL GM_CRC_Calculate_CRC16
    */
    GM_BOOL GM_CRC_Calculate_CRC16(const GM_UINT8 *pBuffer, GM_UINT32 bufferLen, GM_UINT16* pCRC, const GM_UINT16* pCRCTable);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_CRC_H */

