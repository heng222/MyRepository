/**
* @file GM_VSN.h
* @brief VSN算法实现,AlgorithmA和AlgorithmB两种算法均在此文件中实现
* @author Hao Liming
* @date 2010-4-4 11:11:55
* @version
* <pre><b>copyright: CASCO</b></pre>
* <pre><b>email: </b>haoliming@casco.com.cn</pre>
* <pre><b>company: </b>http://www.casco.com.cn</pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>Write modifications here.</pre>
*/
#ifndef _GM_VSN_H
#define _GM_VSN_H

#include "GM_Utils_Base.h"
#include "GM_LFSR.h"
#include "GM_Memcpy.h"

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */

#define GM_VSN_MAX (4U) /**< GM_VSN模块最多可支持4套VSN */

#define GM_VSN1_CHECK_WORD (0xAAAAAAAA) /**< 两个模块VSN1的校核字 */
#define GM_VSN2_CHECK_WORD (0x77777777) /**< 两个模块VSN2的校核字 */

#define GM_VSN_M01 (0x12340234U) /**< VSN1的掩码  */
#define GM_VSN_M02 (0x43211328U) /**< VSN2的掩码 */

#define GM_VSN_SEED1 (0x0B7A7124U) /**< VSN1的初始值*/
#define GM_VSN_SEED2 (0x1C4269F4U) /**< VSN2的初始值*/

    /**
    * @brief GM_VSN_Init
    *
    * 初始化VSN.  注意：正常情况下VSN只能初始化一次，第二次调用初始化函数，会使VSN的值被重置为初始态。
    */
    GM_BOOL GM_VSN_Init(void);

    /**
    * @brief GM_VSN_Update
    *
    * 每个周期更新一次VSN.
    */
    void GM_VSN_Update(void);

    /**
    * @brief GM_VSN_Get
    *
    * 获得当前周期的VSN.
    * @param[out] pVSN0
    * @param[out] pVSN1
    * @param[out] pVSN2
    */
    void GM_VSN_Get(GM_UINT32* pVSN0, GM_UINT32* pVSN1, GM_UINT32* pVSN2);

    /**
    * @brief GM_VSN_Get_Old
    *
    * 获得上个周期的VSN.
    * @param[in] pVSN0
    * @param[in] pVSN1
    * @param[in] pVSN2
    */
    GM_BOOL GM_VSN_Get_Old(GM_UINT32* pVSN0, GM_UINT32* pVSN1, GM_UINT32* pVSN2);

    /**
    * @brief GM_VSN_Set
    *
    * 设置当前周期的VSN.
    * @param[in] VSN0
    * @param[in] VSN1
    * @param[in] VSN2
    */
    void GM_VSN_Set(GM_UINT32 VSN0, GM_UINT32 VSN1, GM_UINT32 VSN2);

    /**
    * @brief GM_VSN_Set_Old
    *
    * 设置上个周期的VSN.
    * @param[in] VSN1
    * @param[in] VSN2
    */
    void GM_VSN_Set_Old(GM_UINT32 VSN1, GM_UINT32 VSN2);

    /**
    * @brief GM_VSN_Cal_Check_Word_VSN1
    *
    * Detailed description.
    * @param[in] VSN1 本模块的VSN1
    * @param[in] otherVSN1 另一个模块的VSN1
    * @param[out] pCHKW 输出的校核字
    * @return GM_BOOL
    */
    GM_BOOL GM_VSN_Cal_Check_Word_VSN1(GM_UINT32 VSN1, GM_UINT32 otherVSN1, GM_UINT32* pCHKW);

    /**
    * @brief GM_VSN_Cal_Check_Word_VSN2
    *
    * Detailed description.
    * @param[in] VSN1 本模块的VSN1
    * @param[in] otherVSN1 另一个模块的VSN1
    * @param[out] pCHKW 输出的校核字
    * @return GM_BOOL
    */
    GM_BOOL GM_VSN_Cal_Check_Word_VSN2(GM_UINT32 VSN2, GM_UINT32 otherVSN2, GM_UINT32* pCHKW);


    /**
    *
    * Detailed description.
    * @param[in] VSNID 新增VSN 的 VSNID号。 （0，255]， 且对每个新增的VSN，VSNID字段唯一
    * @return GM_BOOL 是否新增成功（1、VSNID号是否有效 2、最多可增加4套）
    */
	GM_BOOL GM_VSN_Add(GM_UINT8 VSNID);

	/**
    * 
    * Detailed description.
    * @param[in] VSNID 新增VSN 的 VSNID号。 [0，255]， 且对每个新增的VSN，VSNID字段唯一
	* 当VSNID=0时，更新基本GM_VSN ， 当VSNID属于（0，255]时，更新VSNID号对应的GM_VSN
    * @return GM_BOOL 是否更新成功（1、VSNID号是否有效）
    */
	GM_BOOL GM_VSN_Update_S(GM_UINT8 VSNID);

	/**
    * 
    * Detailed description.
	* 获得当前周期的VSN.
    * @param[in] VSNID 新增VSN 的 VSNID号。 [0，255]， 且对每个新增的VSN，VSNID字段唯一
	* 当VSNID=0时，获得基本GM_VSN ， 当VSNID属于（0，255]时，获得VSNID号对应的GM_VSN
	* @param[out] pVSN0
	* @param[out] pVSN1
	* @param[out] pVSN2
    * @return GM_BOOL 是否获取成功（1、VSNID号是否有效）
    */
	GM_BOOL GM_VSN_Get_S(GM_UINT8 VSNID, GM_UINT32* pVSN0, GM_UINT32* pVSN1, GM_UINT32* pVSN2);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_VSN_H */

