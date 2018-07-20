/**
* @file GM_VSN.h
* @brief VSN�㷨ʵ��,AlgorithmA��AlgorithmB�����㷨���ڴ��ļ���ʵ��
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

#define GM_VSN_MAX (4U) /**< GM_VSNģ������֧��4��VSN */

#define GM_VSN1_CHECK_WORD (0xAAAAAAAA) /**< ����ģ��VSN1��У���� */
#define GM_VSN2_CHECK_WORD (0x77777777) /**< ����ģ��VSN2��У���� */

#define GM_VSN_M01 (0x12340234U) /**< VSN1������  */
#define GM_VSN_M02 (0x43211328U) /**< VSN2������ */

#define GM_VSN_SEED1 (0x0B7A7124U) /**< VSN1�ĳ�ʼֵ*/
#define GM_VSN_SEED2 (0x1C4269F4U) /**< VSN2�ĳ�ʼֵ*/

    /**
    * @brief GM_VSN_Init
    *
    * ��ʼ��VSN.  ע�⣺���������VSNֻ�ܳ�ʼ��һ�Σ��ڶ��ε��ó�ʼ����������ʹVSN��ֵ������Ϊ��ʼ̬��
    */
    GM_BOOL GM_VSN_Init(void);

    /**
    * @brief GM_VSN_Update
    *
    * ÿ�����ڸ���һ��VSN.
    */
    void GM_VSN_Update(void);

    /**
    * @brief GM_VSN_Get
    *
    * ��õ�ǰ���ڵ�VSN.
    * @param[out] pVSN0
    * @param[out] pVSN1
    * @param[out] pVSN2
    */
    void GM_VSN_Get(GM_UINT32* pVSN0, GM_UINT32* pVSN1, GM_UINT32* pVSN2);

    /**
    * @brief GM_VSN_Get_Old
    *
    * ����ϸ����ڵ�VSN.
    * @param[in] pVSN0
    * @param[in] pVSN1
    * @param[in] pVSN2
    */
    GM_BOOL GM_VSN_Get_Old(GM_UINT32* pVSN0, GM_UINT32* pVSN1, GM_UINT32* pVSN2);

    /**
    * @brief GM_VSN_Set
    *
    * ���õ�ǰ���ڵ�VSN.
    * @param[in] VSN0
    * @param[in] VSN1
    * @param[in] VSN2
    */
    void GM_VSN_Set(GM_UINT32 VSN0, GM_UINT32 VSN1, GM_UINT32 VSN2);

    /**
    * @brief GM_VSN_Set_Old
    *
    * �����ϸ����ڵ�VSN.
    * @param[in] VSN1
    * @param[in] VSN2
    */
    void GM_VSN_Set_Old(GM_UINT32 VSN1, GM_UINT32 VSN2);

    /**
    * @brief GM_VSN_Cal_Check_Word_VSN1
    *
    * Detailed description.
    * @param[in] VSN1 ��ģ���VSN1
    * @param[in] otherVSN1 ��һ��ģ���VSN1
    * @param[out] pCHKW �����У����
    * @return GM_BOOL
    */
    GM_BOOL GM_VSN_Cal_Check_Word_VSN1(GM_UINT32 VSN1, GM_UINT32 otherVSN1, GM_UINT32* pCHKW);

    /**
    * @brief GM_VSN_Cal_Check_Word_VSN2
    *
    * Detailed description.
    * @param[in] VSN1 ��ģ���VSN1
    * @param[in] otherVSN1 ��һ��ģ���VSN1
    * @param[out] pCHKW �����У����
    * @return GM_BOOL
    */
    GM_BOOL GM_VSN_Cal_Check_Word_VSN2(GM_UINT32 VSN2, GM_UINT32 otherVSN2, GM_UINT32* pCHKW);


    /**
    *
    * Detailed description.
    * @param[in] VSNID ����VSN �� VSNID�š� ��0��255]�� �Ҷ�ÿ��������VSN��VSNID�ֶ�Ψһ
    * @return GM_BOOL �Ƿ������ɹ���1��VSNID���Ƿ���Ч 2����������4�ף�
    */
	GM_BOOL GM_VSN_Add(GM_UINT8 VSNID);

	/**
    * 
    * Detailed description.
    * @param[in] VSNID ����VSN �� VSNID�š� [0��255]�� �Ҷ�ÿ��������VSN��VSNID�ֶ�Ψһ
	* ��VSNID=0ʱ�����»���GM_VSN �� ��VSNID���ڣ�0��255]ʱ������VSNID�Ŷ�Ӧ��GM_VSN
    * @return GM_BOOL �Ƿ���³ɹ���1��VSNID���Ƿ���Ч��
    */
	GM_BOOL GM_VSN_Update_S(GM_UINT8 VSNID);

	/**
    * 
    * Detailed description.
	* ��õ�ǰ���ڵ�VSN.
    * @param[in] VSNID ����VSN �� VSNID�š� [0��255]�� �Ҷ�ÿ��������VSN��VSNID�ֶ�Ψһ
	* ��VSNID=0ʱ����û���GM_VSN �� ��VSNID���ڣ�0��255]ʱ�����VSNID�Ŷ�Ӧ��GM_VSN
	* @param[out] pVSN0
	* @param[out] pVSN1
	* @param[out] pVSN2
    * @return GM_BOOL �Ƿ��ȡ�ɹ���1��VSNID���Ƿ���Ч��
    */
	GM_BOOL GM_VSN_Get_S(GM_UINT8 VSNID, GM_UINT32* pVSN0, GM_UINT32* pVSN1, GM_UINT32* pVSN2);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_VSN_H */

