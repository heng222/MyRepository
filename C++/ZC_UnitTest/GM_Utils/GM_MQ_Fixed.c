/**
 * Copyright(C)
 * 
 * @file:GM_MQ_Fixed.c
 * @brief:
 * @auther:
 * @create date:

 */

#include "GM_MQ_Fixed.h"

/**
* @brief GM_MQ_Read
* 读取消息，并将消息的缓存置0
* Detailed description.
* @param[in] pMQ 要读的消息队列
* @param[in] pOutBuf 要输出消息的缓冲区
* @param[in/out] pSize 作为输入参数时为输出的缓冲区消息大小，作为输出参数为读到的消息大小
* @return GM_BOOL
*/
GM_BOOL GM_MQ_Fixed_Read(GM_MQ_Fixed_Struct* pMQ, GM_UINT8* pOutBuf, GM_UINT16* pSize)
{
    GM_BOOL rt = GM_FALSE;
    GM_UINT16 temp = 0U;

    if ((NULL == pMQ) || (NULL == pOutBuf) || (NULL == pSize)
        || (GM_TRUE != pMQ->initialized))
    {
		
		printf("GM_MQ_Fixed_Read()::Error 11111\n");
		
        return GM_FALSE;
    }
	/*关于msgNum， front的读取和判断 调整到lock mutex之后。 CR1409*/
	rt = GM_Mutex_Lock(pMQ->mutex);

	if (GM_FALSE == rt)
	{
			printf("GM_MQ_Fixed_Read()::Error 2222\n");	
		return GM_FALSE;
	}	
	
	if ((GM_UINT16)0u == pMQ->msgNum)
	{
		GM_Mutex_Unlock(pMQ->mutex);
		return GM_FALSE;
	}

    temp = (pMQ->front + 1U) % (GM_MQ_FIXED_MSG_NUM);

    if (pMQ->MQMsgArray[temp].msgSize > (*pSize))
    {
		GM_Mutex_Unlock(pMQ->mutex);
	    printf("GM_MQ_Fixed_Read()::Error 4444, %d  %d\n", pMQ->MQMsgArray[temp].msgSize, *pSize);
		return GM_FALSE;    
	}
    else
    {

        pMQ->front = temp;
        --(pMQ->msgNum);

        GM_memcpy((void*)pOutBuf, ((const void*)(pMQ->MQMsgArray[pMQ->front].MsgBuff)), ((size_t)(pMQ->MQMsgArray[pMQ->front].msgSize)));
        *pSize = pMQ->MQMsgArray[pMQ->front].msgSize;

		/*增加清空已读消息内容的接口*/
		GM_memset(((void*)(pMQ->MQMsgArray[pMQ->front].MsgBuff)),(GM_UINT8)0U, ((size_t)(GM_MQ_FIXED_MSG_SIZE)));
		pMQ->MQMsgArray[pMQ->front].msgSize = 0U;

		rt = GM_Mutex_Unlock(pMQ->mutex);
		
    }

    return rt;
}

/**
* @brief GM_MQ_Write
*
* Detailed description.
* @param[in] pMQ 要写的消息队列
* @param[in] pMsg 要写的消息
* @param[in] size 要写的消息大小
* @return GM_MQ_Write_Result_Enum 
*/
GM_BOOL GM_MQ_Fixed_Write(GM_MQ_Fixed_Struct* pMQ, const GM_UINT8* pMsg, GM_UINT16 size)
{
    GM_BOOL rt = GM_FALSE;
    GM_UINT16 temp = 0U;

    if ((NULL == pMQ) || (NULL == pMsg) || (size > GM_MQ_FIXED_MSG_SIZE) || (size == 0U)
        || (GM_TRUE != pMQ->initialized))
    {
        return GM_FALSE;
    }

	/*关于msgNum， front的读取和判断 调整到lock mutex之后。 CR1409*/
	rt = GM_Mutex_Lock(pMQ->mutex);

	if (GM_FALSE == rt)
	{
		return GM_FALSE;
	}

	temp = (GM_MQ_FIXED_MSG_NUM) - (GM_UINT16)1u;/*计算temp*/

	if (temp ==  pMQ->msgNum)/*如果当前消息数=max-1 表示满了*/
	{
		GM_Mutex_Unlock(pMQ->mutex);
		return GM_FALSE;
	}
	else
	{
	    pMQ->rear = (pMQ->rear + 1U) % (GM_MQ_FIXED_MSG_NUM);/*rear前进一步*/
		GM_memcpy(((void*)(pMQ->MQMsgArray[pMQ->rear].MsgBuff)), (const void*) pMsg, (size_t)size);/*复制消息进入rear位*/
		pMQ->MQMsgArray[pMQ->rear].msgSize = size;
		++(pMQ->msgNum);/*当前消息数++*/

		rt = GM_Mutex_Unlock(pMQ->mutex);
	}

    return rt;
}

/**
 * @brief GM_MQ_Get_Msg_Num
 *
 * Detailed description.
 * @param[in] pMQ 要获得消息个数的消息队列
 * @return GM_INT32 若失败则返回-1,否则返回消息个数
 */
GM_INT32 GM_MQ_Fixed_Get_Msg_Num(const GM_MQ_Fixed_Struct* pMQ)
{
	GM_BOOL rt = GM_FALSE;
	GM_UINT16 temp = -1;

	if ((NULL == pMQ) || (GM_TRUE != pMQ->initialized))
    {
        return -1;
    }
    else
    {
		/*获取msgNum， 增加lock mutex保护。 CR1409*/
		rt = GM_Mutex_Lock(pMQ->mutex);

		if (rt == GM_FALSE)
		{
			return -1;
		}
		
		temp = (GM_INT32)(pMQ->msgNum);

		rt = GM_Mutex_Unlock(pMQ->mutex);

		if ( rt == GM_FALSE)
		{
			return -1;
		}

		return temp;
    }
}

/**
* @brief GM_MQ_Flush
*
* Detailed description.
* @param[in] pMQ 要清零的消息队列内存
* @return GM_BOOL
*/
GM_BOOL GM_MQ_Fixed_Flush(GM_MQ_Fixed_Struct* pMQ)
{
	GM_BOOL rt = GM_FALSE;
	GM_UINT16 msgIndex = 0U;

	if ((NULL == pMQ) || (GM_TRUE != pMQ->initialized))
	{
		return GM_FALSE;
	}

	rt = GM_Mutex_Lock(pMQ->mutex);

	if (GM_FALSE == rt)
	{
		return GM_FALSE;
	}

	for(; msgIndex< (GM_MQ_FIXED_MSG_NUM); ++msgIndex)
	{
		pMQ->MQMsgArray[msgIndex].msgSize = 0u;
		GM_memset(((void*)(pMQ->MQMsgArray[msgIndex].MsgBuff)), (GM_UINT8)0u, ((size_t)(GM_MQ_FIXED_MSG_SIZE)));
	}

	pMQ->front  = (GM_UINT16)0u;
	pMQ->rear   = (GM_UINT16)0u;
	pMQ->msgNum = (GM_UINT16)0u;

	rt = GM_Mutex_Unlock(pMQ->mutex);

	return rt;
}

/**
* @brief GM_MQ_Fixed_Init
*
* Detailed description.
* @param[in] pMQ 要初始化的消息队列内存
* @return GM_BOOL
*/
GM_BOOL GM_MQ_Fixed_Init(GM_MQ_Fixed_Struct* pMQ)
{
	GM_BOOL rt  = GM_FALSE;
	GM_UINT16 i = 0U;

	if(NULL == pMQ)
	{
		return GM_FALSE;
	}

	if (GM_TRUE == pMQ->initialized)
    {
        return GM_TRUE;
    }
	pMQ->front  = (GM_UINT16)0u;
	pMQ->rear   = (GM_UINT16)0u;
	pMQ->msgNum = (GM_UINT16)0u;

	rt = GM_Mutex_Init(&(pMQ->mutex));
    if(GM_FALSE == rt)
    {
    	return GM_FALSE;
    }

    for(i = 0U; i < GM_MQ_FIXED_MSG_NUM; ++i)
    {
    	GM_memset(((void*)(pMQ->MQMsgArray[i].MsgBuff)), (GM_UINT8)0u, ((size_t)(GM_MQ_FIXED_MSG_SIZE)));

    }

    pMQ->initialized = GM_TRUE;
    return GM_TRUE;
}
