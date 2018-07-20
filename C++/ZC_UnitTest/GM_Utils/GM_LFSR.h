/**
* @file GM_LFSR.h
* @brief ����С�˱���
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
    * ��ȡ������.
    * @param[in] This LFSR�����м����ݽṹ
    * @param[out] pData �Ĵ����е�ֵ
    * @return GM_BOOL
    */
    GM_BOOL GM_LFSR_Read(GM_LFSR* This, GM_UINT32* pData);

    /**
    * @brief GM_LFSR_Init
    *
    * ��ʼ��LFSR�����м����ݽṹ.
    * @param[in] This LFSR�����м����ݽṹ
    * @param[in] pLeftTable ���������
    * @param[in] pRightTable ���������
    * @return GM_BOOL
    */
    GM_BOOL GM_LFSR_Init(GM_LFSR* This, const GM_UINT32* pLeftTable, const GM_UINT32* pRightTable);

    /**
    * @brief GM_LFSR_Load
    *
    * ���ؽ���LFSR���������.
    * @param[in] This LFSR�����м����ݽṹ
    * @param[in] data ��������
    * @return GM_BOOL
    */
    GM_BOOL GM_LFSR_Load(GM_LFSR* This, GM_UINT32 data);

    /**
    * @brief GM_LFSR_Add
    *
    * ����Add����.
    * @param[in] This LFSR�����м����ݽṹ
    * @param[in] data ��������
    * @return GM_BOOL
    */
    GM_BOOL GM_LFSR_Add(GM_LFSR* This, GM_UINT32 data);

    /**
    * @brief GM_LFSR_Sub
    *
    * ����Sub����.
    * @param[in] This LFSR�����м����ݽṹ
    * @param[in] data ��������
    * @return GM_BOOL
    */
    GM_BOOL GM_LFSR_Sub(GM_LFSR* This, GM_UINT32 data);

    /**
    * @brief GM_LFSR_Post
    *
    * ����Post����.
    * @param[in] This LFSR�����м����ݽṹ
    * @param[in] data ��������
    * @return GM_BOOL
    */
    GM_BOOL GM_LFSR_Post(GM_LFSR* This, GM_UINT32 data);

    /**
    * @brief GM_LFSR_Xor
    *
    * ����Xor����.
    * @param[in] This LFSR�����м����ݽṹ
    * @param[in] data ��������
    * @return GM_BOOL
    */
    GM_BOOL GM_LFSR_Xor(GM_LFSR* This, GM_UINT32 data);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_LFSR_H */



