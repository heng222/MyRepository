/**
* @file GM_PD_Table.h
* @brief 存放事先计算好的PD表
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

    /** @brief 通道1用的表 采用多项式GM_PD_CRC_CHANEL_1*/
    extern const GM_UINT32 GM_PD_Channel1_Table[GM_PD_TABLE_SIZE];

    /** @brief 通道2用的表 采用多项式GM_PD_CRC_CHANEL_2*/
    extern const GM_UINT32 GM_PD_Channel2_Table[GM_PD_TABLE_SIZE];

    /**
    * @brief GM_PD_Build_Table
    *
    * 构建PD运算表.
    * @param[in] XORPara 构建PD所用到的多项式
    * @param[out] pPD_Table 输出的PD表
    * @return GM_BOOL
    */
    GM_BOOL GM_PD_Build_Table(GM_UINT32 XORPara, GM_UINT32* pPDTable);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_PD_TABLE_H */

