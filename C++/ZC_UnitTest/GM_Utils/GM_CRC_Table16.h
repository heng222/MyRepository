/**
* @file GM_CRC_Table16.h
* @brief ����CRC����õı�
* @author 
* @date 
* @version
* <pre><b>copyright: 

*/
#ifndef _GM_CRC_TABLE16_H
#define _GM_CRC_TABLE16_H

#include "GM_Utils_Base.h"
#include "GM_CRC_Reflect.h"

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */

    /** @brief ����ʽ0x11021������CRC�� */
    extern const GM_UINT16 GM_CRC16_Table_0x11021_MSB[];

    /** @brief ����ʽ0x11021������CRC��(0x18408) */
    extern const GM_UINT16 GM_CRC16_Table_0x11021_LSB[];

    /** @brief ����ʽ0x10811������CRC�� */
    extern const GM_UINT16 GM_CRC16_Table_0x10811_MSB[];

    /** @brief ����ʽ0x10811������CRC��, FSFB2�л��õ���CRC�� */
    extern const GM_UINT16 GM_CRC16_Table_0x10811_LSB[];

    /**
    * @brief GM_CRC_Build_CRC16_Table
    *
    * ���ݶ���ʽ��˳�����CRC��
    * @param[in] polynomial ����ʽ 0x1021
    * @param[out] pCRCTable CRC��
    * @param[in] isHighFirst 1Ϊ���� ����0x8408, ͨ��Ϊ����0 ����0x1021.
    * @return GM_BOOL
    */
    GM_BOOL GM_CRC_Build_CRC16_Table(GM_UINT32 polynomial, GM_UINT16* pCRCTable, GM_BOOL isHighFirst);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_CRC_TABLE_H */

