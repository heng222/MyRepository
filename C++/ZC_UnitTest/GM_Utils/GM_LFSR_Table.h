/**
* @file GM_LFSR_Table.h
* @brief Linear Feedback Shift-Register���Է�����λ�Ĵ�����
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
    * @brief FSFB2ͨ��1 PD�����õ�������LFSR��0x10FC22F87
    *
    * ���ɺ���: GM_LFSR_Build_Table(0x0FC22F87, GM_LFSR_LEFT_CHN1_TABLE, GM_TRUE);
    */
    extern const GM_UINT32 GM_LFSR_LEFT_CHN1_TABLE[];

    /**
    * @brief FSFB2ͨ��1 PD�����õ�������LFSR��0x10FC22F87
    *
    * ���ɺ���: GM_LFSR_Build_Table(0x0FC22F87, GM_LFSR_RIGHT_CHN1_TABLE, GM_FALSE);
    */
    extern const GM_UINT32 GM_LFSR_RIGHT_CHN1_TABLE[];

    /**
    * @brief FSFB2ͨ��2 PD�����õ�������LFSR��0x1C3E887E1
    *
    * ���ɺ���: GM_LFSR_Build_Table(0x1C3E887E1, GM_LFSR_LEFT_CHN2_TABLE, GM_TRUE);
    */
    extern const GM_UINT32 GM_LFSR_LEFT_CHN2_TABLE[];

    /**
    * @brief FSFB2ͨ��2 PD�����õ�������LFSR��0x1C3E887E1
    *
    * ���ɺ���: GM_LFSR_Build_Table(0x1C3E887E1, GM_LFSR_RIGHT_CHN2_TABLE, GM_FALSE);
    */
    extern const GM_UINT32 GM_LFSR_RIGHT_CHN2_TABLE[];

    /**
    * @brief GM_LFSR_Build_Table
    *
    * Detailed description.
    * @param[in] polynomial LFSR�õĶ���ʽ
    * @param[in] pTable ���ɵı�
    * @param[in] isLeft �����Ʊ������Ʊ�
    * @return GM_BOOL
    */
    GM_BOOL GM_LFSR_Build_Table(GM_UINT32 polynomial, GM_UINT32* pTable, GM_BOOL isLeft);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_LFSR_TABLE_H */



