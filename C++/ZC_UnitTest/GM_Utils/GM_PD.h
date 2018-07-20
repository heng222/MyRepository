/**
* @file GM_PD.h
* @brief 通过查表法实现PD运算，主要用于生成校核字.
* 可以把这里的PD运算看作是计算CRC,即对一组数据执行PD运算之后生成一个32位的值.
* @author 
* @date 
* @version

*/
#ifndef _GM_PD_H
#define _GM_PD_H

#include "GM_PD_Table.h"

#ifdef __cplusplus
extern "C"
{
#endif

 
    /**
    * @brief GM_PD_Operation
    *
    * 标准PD运算.
    * 注意: 如果是中断调用该函数,那么需要创建一个该函数的副本,因为有寄存器变量
    * @param[in] isAlgorithmA 是通道1还是通道2
    * @param[in] VSN1 VSN1
    * @param[in] VSN2 VSN2
    * @param[in] pPDPara 要进行PD运算的数组
    * @param[in] paraNum 数组大小
    * @param[out] pResult PD运算结果
    * @return GM_BOOL PD运算是否成功
    */
    GM_BOOL GM_PD_Operation(GM_BOOL isAlgorithmA, GM_UINT32 VSN1, GM_UINT32 VSN2, GM_UINT32 *pPDPara, GM_UINT32 paraNum, GM_UINT32* pResult);

	/**
    * @brief GM_PD_Operation2
    *
    * 追加型PD运算.
    * 注意: 如果是中断调用该函数,那么需要创建一个该函数的副本,因为有寄存器变量
    * @param[in] isAlgorithmA 是通道1还是通道2
    * @param[in] VSN1 VSN1
    * @param[in] VSN2 VSN2
    * @param[in] pPDPara 要进行PD运算的数组
    * @param[in] paraNum 数组大小
    * @param[out] pResult PD运算结果
    * @return GM_BOOL PD运算是否成功
    */
    GM_BOOL GM_PD_Operation2(GM_BOOL isAlgorithmA, GM_UINT32 VSN1, GM_UINT32 VSN2, GM_UINT32 *pPDPara, GM_UINT32 paraNum, GM_UINT32* pResult);

    /**
    * @brief GM_PD_Inverse
    *
    * 多参数的PD逆运算.
    * 注意: 如果是中断调用该函数,那么需要创建一个该函数的副本,因为有寄存器变量
    * @param[in] 是通道1还是通道2
    * @param[in] VSN1 VSN1
    * @param[in] VSN2 VSN2
    * @param[in] pPDPara
    * @param[in] paraNum
    * @param[out] pResult
    * @return GM_BOOL
    */
    GM_BOOL GM_PD_Inverse(GM_BOOL isAlgorithmA, GM_UINT32 VSN1, GM_UINT32 VSN2, GM_UINT32 *pPDPara, GM_UINT32 paraNum, GM_UINT32* pResult);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_PD_H */

