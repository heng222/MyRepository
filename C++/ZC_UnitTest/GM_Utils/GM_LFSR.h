/**
* @file GM_LFSR.h
* @brief 采用小端编码
* @author 
* @date 
* @version
* <pre><b>copyright: 

*/

#ifndef _GM_LFSR_H
#define _GM_LFSR_H

#include "GM_Utils_Base.h"
#include "GM_LFSR_Table.h"

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */

    typedef struct
    {
        GM_UINT32 reg;
        const GM_UINT32 *leftTable;
        const GM_UINT32 *rightTable;
    }GM_PACKED GM_LFSR;

    /**
    * @brief GM_LFSR_Read
    *
    * 获取运算结果.
    * @param[in] This LFSR运算中间数据结构
    * @param[out] pData 寄存器中的值
    * @return GM_BOOL
    */
    GM_BOOL GM_LFSR_Read(GM_LFSR* This, GM_UINT32* pData);

    /**
    * @brief GM_LFSR_Init
    *
    * 初始化LFSR运算中间数据结构.
    * @param[in] This LFSR运算中间数据结构
    * @param[in] pLeftTable 左移运算表
    * @param[in] pRightTable 右移运算表
    * @return GM_BOOL
    */
    GM_BOOL GM_LFSR_Init(GM_LFSR* This, const GM_UINT32* pLeftTable, const GM_UINT32* pRightTable);

    /**
    * @brief GM_LFSR_Load
    *
    * 加载进行LFSR运算的数据.
    * @param[in] This LFSR运算中间数据结构
    * @param[in] data 运算数据
    * @return GM_BOOL
    */
    GM_BOOL GM_LFSR_Load(GM_LFSR* This, GM_UINT32 data);

    /**
    * @brief GM_LFSR_Add
    *
    * 进行Add运算.
    * @param[in] This LFSR运算中间数据结构
    * @param[in] data 运算数据
    * @return GM_BOOL
    */
    GM_BOOL GM_LFSR_Add(GM_LFSR* This, GM_UINT32 data);

    /**
    * @brief GM_LFSR_Sub
    *
    * 进行Sub运算.
    * @param[in] This LFSR运算中间数据结构
    * @param[in] data 运算数据
    * @return GM_BOOL
    */
    GM_BOOL GM_LFSR_Sub(GM_LFSR* This, GM_UINT32 data);

    /**
    * @brief GM_LFSR_Post
    *
    * 进行Post运算.
    * @param[in] This LFSR运算中间数据结构
    * @param[in] data 运算数据
    * @return GM_BOOL
    */
    GM_BOOL GM_LFSR_Post(GM_LFSR* This, GM_UINT32 data);

    /**
    * @brief GM_LFSR_Xor
    *
    * 进行Xor运算.
    * @param[in] This LFSR运算中间数据结构
    * @param[in] data 运算数据
    * @return GM_BOOL
    */
    GM_BOOL GM_LFSR_Xor(GM_LFSR* This, GM_UINT32 data);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_LFSR_H */



