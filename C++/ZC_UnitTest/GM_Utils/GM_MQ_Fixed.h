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
        GM_UINT16 front;              /**< 头指针               */
        GM_UINT16 rear;               /**< 尾指针               */
        GM_UINT16 msgNum;      /**< 消息队列中消息个数   */
        GM_MUTEX mutex;        /**< 保护消息队列的互斥器 */
        GM_MQ_Fixed_Msg_Struct MQMsgArray[GM_MQ_FIXED_MSG_NUM]; /**< 指向第一条消息    */
    }GM_PACKED GM_MQ_Fixed_Struct;

    /**
    * @brief GM_MQ_Get_Msg_Num
    *
    * Detailed description.
    * @param[in] pMQ 要获得消息个数的消息队列
    * @return GM_INT32 若失败则返回-1,否则返回消息个数
    */
    GM_INT32 GM_MQ_Fixed_Get_Msg_Num(const GM_MQ_Fixed_Struct* pMQ);

    /**
    * @brief GM_MQ_Write
    *
    * Detailed description.
    * @param[in] pMQ 要写的消息队列
    * @param[in] pMsg 要写的消息
    * @param[in] size 要写的消息大小
    * @return GM_MQ_Write_Result_Enum 
    */
    GM_BOOL GM_MQ_Fixed_Write(GM_MQ_Fixed_Struct* pMQ, const GM_UINT8* pMsg, GM_UINT16 size);

    /**
    * @brief GM_MQ_Read
    * 读取消息，并将消息的缓存置0
    * Detailed description.
    * @param[in] pMQ 要读的消息队列
    * @param[in] pOutBuf 要输出消息的缓冲区
    * @param[in/out] pSize 作为输入参数时为输出的缓冲区消息大小，作为输出参数为读到的消息大小
    * @return GM_BOOL
    */
    GM_BOOL GM_MQ_Fixed_Read(GM_MQ_Fixed_Struct* pMQ, GM_UINT8* pOutBuf, GM_UINT16* pSize);

    /**
    * @brief GM_MQ_Flush
    *
    * Detailed description.
    * @param[in] pMQ 要清零的消息队列内存
    * @return GM_BOOL
    */
	GM_BOOL GM_MQ_Fixed_Flush(GM_MQ_Fixed_Struct* pMQ);
 
	
	/**
    * @brief GM_MQ_Fixed_Init
    *
    * Detailed description.
    * @param[in] pMQ 要初始化的消息队列内存
    * @return GM_BOOL
    */
    GM_BOOL GM_MQ_Fixed_Init(GM_MQ_Fixed_Struct* pMQ);
    
#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_MQ_H */

