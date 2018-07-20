

#ifndef _GM_CRC16_STARDAND_H
#define _GM_CRC16_STARDAND_H

#include "GM_CRC_Reflect.h"
#include "GM_CRC_Table16.h"

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */


    /**
    * @brief
    *
    * �����׼����CRC16 
    * @param[in] Data ��У�������
    * @param[in] DataLen ��У������ݳ���(�ֽ�)
	* @param[in] Poly CRC16���õĶ���ʽ
	* @param[in] isHighFirst  ��������
    * @param[in] pCRCTable CRC��
    * @param[in] pCRC ����CRCУ����   
    * @return GM_BOOL GM_CRC_Calculate_CRC16_Standard_H
	*/
    GM_BOOL GM_CRC_Calculate_CRC16_Standard_Seed(GM_UINT8* Data, GM_UINT16 DataLen, GM_UINT16 Seed, GM_UINT16 Poly, GM_BOOL isHighFirst, const GM_UINT16* pCRC16Table, GM_UINT16* pCRC);	

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif 
