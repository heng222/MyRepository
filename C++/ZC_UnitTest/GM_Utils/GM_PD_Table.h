/**
* @file GM_PD_Table.h
* @brief ������ȼ���õ�PD��
* @author 
* @date 
* @version

*/
#ifndef _GM_PD_TABLE_H
#define _GM_PD_TABLE_H

#include "GM_Utils_Base.h"

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */

#define GM_PD_TABLE_SIZE (512U)

#define GM_PD_CRC_CHANEL_1 (0xFFBFFFF9)
#define GM_PD_CRC_CHANEL_2 (0x3FFFFBFFU)

    /** @brief ͨ��1�õı� ���ö���ʽGM_PD_CRC_CHANEL_1*/
    extern const GM_UINT32 GM_PD_Channel1_Table[GM_PD_TABLE_SIZE];

    /** @brief ͨ��2�õı� ���ö���ʽGM_PD_CRC_CHANEL_2*/
    extern const GM_UINT32 GM_PD_Channel2_Table[GM_PD_TABLE_SIZE];

    /**
    * @brief GM_PD_Build_Table
    *
    * ����PD�����.
    * @param[in] XORPara ����PD���õ��Ķ���ʽ
    * @param[out] pPD_Table �����PD��
    * @return GM_BOOL
    */
    GM_BOOL GM_PD_Build_Table(GM_UINT32 XORPara, GM_UINT32* pPDTable);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_PD_TABLE_H */

