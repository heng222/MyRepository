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
* ��ȡ��Ϣ��������Ϣ�Ļ�����0
* Detailed description.
* @param[in] pMQ Ҫ������Ϣ����
* @param[in] pOutBuf Ҫ�����Ϣ�Ļ�����
* @param[in/out] pSize ��Ϊ�������ʱΪ����Ļ�������Ϣ��С����Ϊ�������Ϊ��������Ϣ��С
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
	/*����msgNum�� front�Ķ�ȡ���ж� ������lock mutex֮�� CR1409*/
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

		/*��������Ѷ���Ϣ���ݵĽӿ�*/
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
* @param[in] pMQ Ҫд����Ϣ����
* @param[in] pMsg Ҫд����Ϣ
* @param[in] size Ҫд����Ϣ��С
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

	/*����msgNum�� front�Ķ�ȡ���ж� ������lock mutex֮�� CR1409*/
	rt = GM_Mutex_Lock(pMQ->mutex);

	if (GM_FALSE == rt)
	{
		return GM_FALSE;
	}

	temp = (GM_MQ_FIXED_MSG_NUM) - (GM_UINT16)1u;/*����temp*/

	if (temp ==  pMQ->msgNum)/*�����ǰ��Ϣ��=max-1 ��ʾ����*/
	{
		GM_Mutex_Unlock(pMQ->mutex);
		return GM_FALSE;
	}
	else
	{
	    pMQ->rear = (pMQ->rear + 1U) % (GM_MQ_FIXED_MSG_NUM);/*rearǰ��һ��*/
		GM_memcpy(((void*)(pMQ->MQMsgArray[pMQ->rear].MsgBuff)), (const void*) pMsg, (size_t)size);/*������Ϣ����rearλ*/
		pMQ->MQMsgArray[pMQ->rear].msgSize = size;
		++(pMQ->msgNum);/*��ǰ��Ϣ��++*/

		rt = GM_Mutex_Unlock(pMQ->mutex);
	}

    return rt;
}

/**
 * @brief GM_MQ_Get_Msg_Num
 *
 * Detailed description.
 * @param[in] pMQ Ҫ�����Ϣ��������Ϣ����
 * @return GM_INT32 ��ʧ���򷵻�-1,���򷵻���Ϣ����
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
		/*��ȡmsgNum�� ����lock mutex������ CR1409*/
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
* @param[in] pMQ Ҫ�������Ϣ�����ڴ�
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
* @param[in] pMQ Ҫ��ʼ������Ϣ�����ڴ�
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
