/**
* @file GM_LFSR_Table.h
* @brief Linear Feedback Shift-Register线性反馈移位寄存器表
* @author Hao Liming
* @date 2010-7-29 18:45:15
* @version
* <pre><b>copyright: CASCO</b></pre>
* <pre><b>email: </b>haoliming@casco.com.cn</pre>
* <pre><b>company: </b>http://www.casco.com.cn</pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>Write modifications here.</pre>
*/
#ifndef _GM_LFSR_TABLE_H
#define _GM_LFSR_TABLE_H

#include "GM_Utils_Base.h"

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */

    /**
    * @brief FSFB2通道1 PD运算用到的左移LFSR表0x10FC22F87
    *
    * 生成函数: GM_LFSR_Build_Table(0x0FC22F87, GM_LFSR_LEFT_CHN1_TABLE, GM_TRUE);
    */
    extern const GM_UINT32 GM_LFSR_LEFT_CHN1_TABLE[];

    /**
    * @brief FSFB2通道1 PD运算用到的右移LFSR表0x10FC22F87
    *
    * 生成函数: GM_LFSR_Build_Table(0x0FC22F87, GM_LFSR_RIGHT_CHN1_TABLE, GM_FALSE);
    */
    extern const GM_UINT32 GM_LFSR_RIGHT_CHN1_TABLE[];

    /**
    * @brief FSFB2通道2 PD运算用到的左移LFSR表0x1C3E887E1
    *
    * 生成函数: GM_LFSR_Build_Table(0x1C3E887E1, GM_LFSR_LEFT_CHN2_TABLE, GM_TRUE);
    */
    extern const GM_UINT32 GM_LFSR_LEFT_CHN2_TABLE[];

    /**
    * @brief FSFB2通道2 PD运算用到的右移LFSR表0x1C3E887E1
    *
    * 生成函数: GM_LFSR_Build_Table(0x1C3E887E1, GM_LFSR_RIGHT_CHN2_TABLE, GM_FALSE);
    */
    extern const GM_UINT32 GM_LFSR_RIGHT_CHN2_TABLE[];

    /**
    * @brief GM_LFSR_Build_Table
    *
    * Detailed description.
    * @param[in] polynomial LFSR用的多项式
    * @param[in] pTable 生成的表
    * @param[in] isLeft 是左移表还是右移表
    * @return GM_BOOL
    */
    GM_BOOL GM_LFSR_Build_Table(GM_UINT32 polynomial, GM_UINT32* pTable, GM_BOOL isLeft);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_LFSR_TABLE_H */



