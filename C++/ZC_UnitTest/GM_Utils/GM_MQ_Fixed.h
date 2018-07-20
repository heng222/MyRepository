/**
 * Copyright(C)
 * 
 * @file:GM_MQ_Fixed.h
 * @brief:
 * @auther:
 * @create date:

 */

#ifndef _GM_MQ_FIXED_H
#define _GM_MQ_FIXED_H

#include "GM_Mutex.h"
#include "GM_Memset.h"
#include "GM_Memcpy.h"
#include "../GM_Define.h"

#ifndef GM_MQ_FIXED_MSG_NUM
#define GM_MQ_FIXED_MSG_NUM		20U
#else
#if GM_MQ_FIXED_MSG_NUM >= GM_UINT16_MAX
#error GM_MQ_FIXED_MSG_NUM should not >=GM_UINT16_MAX
#endif	
#endif
#ifndef GM_MQ_FIXED_MSG_SIZE
#define GM_MQ_FIXED_MSG_SIZE	20U
#else
#if GM_MQ_FIXED_MSG_SIZE >= GM_UINT16_MAX
#error GM_MQ_FIXED_MSG_SIZE should not >=GM_UINT16_MAX
#endif	
#endif

#if (GM_MQ_FIXED_MSG_SIZE + 2) * (GM_MQ_FIXED_MSG_NUM) >= 0x7fffffff
#error (GM_MQ_FIXED_MSG_SIZE + 2) * (GM_MQ_FIXED_MSG_NUM) >= 0x7fffffff
#endif

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */

    typedef struct
    {
        GM_UINT16 msgSize;
        GM_UINT8  MsgBuff[GM_MQ_FIXED_MSG_SIZE];
    }GM_PACKED GM_MQ_Fixed_Msg_Struct;

    typedef struct
    {
		GM_BOOL	initialized;
        GM_UINT16 front;              /**< ͷָ��               */
        GM_UINT16 rear;               /**< βָ��               */
        GM_UINT16 msgNum;      /**< ��Ϣ��������Ϣ����   */
        GM_MUTEX mutex;        /**< ������Ϣ���еĻ����� */
        GM_MQ_Fixed_Msg_Struct MQMsgArray[GM_MQ_FIXED_MSG_NUM]; /**< ָ���һ����Ϣ    */
    }GM_PACKED GM_MQ_Fixed_Struct;

    /**
    * @brief GM_MQ_Get_Msg_Num
    *
    * Detailed description.
    * @param[in] pMQ Ҫ�����Ϣ��������Ϣ����
    * @return GM_INT32 ��ʧ���򷵻�-1,���򷵻���Ϣ����
    */
    GM_INT32 GM_MQ_Fixed_Get_Msg_Num(const GM_MQ_Fixed_Struct* pMQ);

    /**
    * @brief GM_MQ_Write
    *
    * Detailed description.
    * @param[in] pMQ Ҫд����Ϣ����
    * @param[in] pMsg Ҫд����Ϣ
    * @param[in] size Ҫд����Ϣ��С
    * @return GM_MQ_Write_Result_Enum 
    */
    GM_BOOL GM_MQ_Fixed_Write(GM_MQ_Fixed_Struct* pMQ, const GM_UINT8* pMsg, GM_UINT16 size);

    /**
    * @brief GM_MQ_Read
    * ��ȡ��Ϣ��������Ϣ�Ļ�����0
    * Detailed description.
    * @param[in] pMQ Ҫ������Ϣ����
    * @param[in] pOutBuf Ҫ�����Ϣ�Ļ�����
    * @param[in/out] pSize ��Ϊ�������ʱΪ����Ļ�������Ϣ��С����Ϊ�������Ϊ��������Ϣ��С
    * @return GM_BOOL
    */
    GM_BOOL GM_MQ_Fixed_Read(GM_MQ_Fixed_Struct* pMQ, GM_UINT8* pOutBuf, GM_UINT16* pSize);

    /**
    * @brief GM_MQ_Flush
    *
    * Detailed description.
    * @param[in] pMQ Ҫ�������Ϣ�����ڴ�
    * @return GM_BOOL
    */
	GM_BOOL GM_MQ_Fixed_Flush(GM_MQ_Fixed_Struct* pMQ);
 
	
	/**
    * @brief GM_MQ_Fixed_Init
    *
    * Detailed description.
    * @param[in] pMQ Ҫ��ʼ������Ϣ�����ڴ�
    * @return GM_BOOL
    */
    GM_BOOL GM_MQ_Fixed_Init(GM_MQ_Fixed_Struct* pMQ);
    
#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_MQ_H */

