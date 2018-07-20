/**
* @file GM_RSSP1_INTERCOMM.c
* @brief 内外网通信控制器接口实现文件
* @author 
* @date 2017-10-17 15:36:43
* @version
* <pre><b>copyright: </b></pre>
* <pre><b>email: </b></pre>
* <pre><b>company: </b></pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>Write modifications here.</pre>
*/
#include "GM_RSSP1_INTERCOMM.h"
#include "GM_RSSP1_INTERCOMM_Init.h"
#include "GM_RSSP1_INTERCOMM_Socket.h"
#include "..\FSFB\GM_RSSP1_MQ_Interface.h"
#include "..\cspadpt\Vcp_Service_Interface.h"

extern RSSP1_MQ_LINK_struct g_Link_MQ[GM_RSSP1_MAX_SAFETY_CONNECTION_NUM];

/***********************************************************************************************
*
*
* 板通信控制器部分
*
*
***********************************************************************************************/
#ifdef LINK_Part
/**
* @brief IO通信控制器数据的收发
*
* Detailed description.
* @return GM_BOOL
*/
/*static GM_BOOL GM_RSSP1_INTERCOMM_PROCESS_IOB(INTERCOM_Cfg_struct* pintercomm, FSFB_LNK_connection_struct *pLNK_con, FSFB_LNK_object_struct *pLNK);*/
/**
* @brief IO通信控制器数据的socket的维护
*
* Detailed description.
* @return GM_BOOL
*/
static GM_BOOL GM_RSSP1_INTERCOMM_IOB_Matain(INTERCOM_Cfg_struct* pintercomm);
/**
* @brief IO通信控制器数据 将外网数据从外网队列转移至内网队列
*
* Detailed description.
* @param[in] pintercomm:内网通信数据结构体指针
* @param[in] pLNK_con:指定外网链路的结构体指针
* @param[in] pLNK:所有外网链路的结构体指针
* @return GM_BOOL
*/
static GM_BOOL GM_RSSP1_INTERCOMM_IOB_E2I_Before(INTERCOM_Cfg_struct* pintercomm, FSFB_LNK_connection_struct *pLNK_con, FSFB_LNK_object_struct *pLNK);
/**
* @brief IO通信控制器数据 将内网队列数据发送至CPU板内网
*
* Detailed description.
* @param[in] pintercomm:内网通信数据结构体指针
* @param[in] pLNK_con:指定外网链路的结构体指针
* @return GM_BOOL
*/
static GM_BOOL GM_RSSP1_INTERCOMM_IOB_E2I(INTERCOM_Cfg_struct* pintercomm, FSFB_LNK_connection_struct *pLNK_con);
/**
* @brief IO通信控制器数据 将内网队列数据发送CPU板内网后的处理函数 预留
*
* Detailed description.
* @param[in] pintercomm:内网通信数据结构体指针
* @param[in] pLNK_con:指定外网链路的结构体指针
* @return GM_BOOL
*/
static GM_BOOL GM_RSSP1_INTERCOMM_IOB_E2I_After(INTERCOM_Cfg_struct* pintercomm, FSFB_LNK_connection_struct *pLNK_con);
/**
* @brief IO通信控制器数据 接收CPU板内网的数据并存入内网的数据队列
*
* Detailed description.
* @param[in] pintercomm:内网通信数据结构体指针
* @return GM_BOOL
*/
static GM_BOOL GM_RSSP1_INTERCOMM_IOB_I2E_Before(INTERCOM_Cfg_struct* pintercomm);
/**
* @brief IO通信控制器数据 将接收到的CPU板内网数据发送至外网
*
* Detailed description.
* @param[in] pintercomm:内网通信数据结构体指针
* @param[in] pLNK:所有外网链路的结构体指针
* @return GM_BOOL
*/
static GM_BOOL GM_RSSP1_INTERCOMM_IOB_I2E(INTERCOM_Cfg_struct* pintercomm, FSFB_LNK_object_struct *pLNK);
/**
* @brief IO通信控制器数据 将接收到的CPU板内网数据发送至外网后的处理工作 预留
*
* Detailed description.
* @param[in] pintercomm:内网通信数据结构体指针
* @return GM_BOOL
*/
static GM_BOOL GM_RSSP1_INTERCOMM_IOB_I2E_After(INTERCOM_Cfg_struct* pintercomm);

/**
* @brief CPU通信控制器数据的接收
*
* Detailed description.
* @return GM_BOOL
*/
GM_BOOL GM_RSSP1_INTERCOMM_IOB_From_CPUB(FSFB_LNK_connection_struct *pLNK_con, FSFB_LNK_object_struct *pLNK)
{
	GM_BOOL bRet = GM_FALSE;
	INTERCOM_Cfg_struct* pInterComm = NULL;

    if ((pLNK == NULL) || (pLNK_con == NULL))
    {
        return GM_FALSE;
    }

	bRet = GM_RSSP1_INTERCOMM_Init_Finished();
	if (!bRet)
	{
		return GM_FALSE;
	}

	pInterComm = GM_RSSP1_INTERCOMM_Get_Stru();
	if (NULL == pInterComm)
	{
		return GM_FALSE;
	}

	if (pInterComm->type != GM_RSSP1_INTERCOMM_Type_IOB)
	{
		return GM_FALSE;
	}

	(void)GM_RSSP1_INTERCOMM_IOB_Matain(pInterComm);
	(void)GM_RSSP1_INTERCOMM_IOB_I2E_Before(pInterComm);
	(void)GM_RSSP1_INTERCOMM_IOB_I2E(pInterComm, pLNK);
	(void)GM_RSSP1_INTERCOMM_IOB_I2E_After(pInterComm);

	return GM_TRUE;
}
GM_BOOL GM_RSSP1_INTERCOMM_IOB_To_CPUB(FSFB_LNK_connection_struct *pLNK_con, FSFB_LNK_object_struct *pLNK)
{
	GM_BOOL bRet = GM_FALSE;
	INTERCOM_Cfg_struct* pInterComm = NULL;

    if ((pLNK == NULL) || (pLNK_con == NULL))
    {
        return GM_FALSE;
    }

	bRet = GM_RSSP1_INTERCOMM_Init_Finished();
	if (!bRet)
	{
		return GM_FALSE;
	}

	pInterComm = GM_RSSP1_INTERCOMM_Get_Stru();
	if (NULL == pInterComm)
	{
		return GM_FALSE;
	}

	if (pInterComm->type != GM_RSSP1_INTERCOMM_Type_IOB)
	{
		return GM_FALSE;
	}
	
	(void)GM_RSSP1_INTERCOMM_IOB_Matain(pInterComm);
	(void)GM_RSSP1_INTERCOMM_IOB_E2I_Before(pInterComm, pLNK_con, pLNK);
	(void)GM_RSSP1_INTERCOMM_IOB_E2I(pInterComm, pLNK_con);
	(void)GM_RSSP1_INTERCOMM_IOB_E2I_After(pInterComm, pLNK_con);

	return GM_TRUE;
}

/**
* @brief 
*
* Detailed description.
* @return GM_BOOL
*
*/
static GM_BOOL GM_RSSP1_INTERCOMM_IOB_Matain(INTERCOM_Cfg_struct* pintercomm)
{
	GM_INT32 rt = GM_RSSP1_ERROR;
	int i = 0;

	if (NULL == pintercomm)
	{
		return GM_FALSE;
	}
	if (pintercomm->type != GM_RSSP1_INTERCOMM_Type_IOB)
	{
		return GM_FALSE;
	}

	for (i = 0; i< GM_RSSP1_CFM_MAX_CHANNEL_NUM; i++)
	{	
		if (0 > pintercomm->chnl_IOB[i].sock)
		{
			rt = INTERCOMM_Socket_Init(
						&(pintercomm->chnl_IOB[i].sock) ,
						SOCK_DGRAM ,
						&(pintercomm->chnl_IOB[i].addr_cfg.local_addr) ,
						(1500U*20U),
						(1500U*20U),
						&(pintercomm->chnl_IOB[i].max_socket_value)
					);

			if (GM_RSSP1_ERROR == rt)
			{
				continue;	
			}
		}
	}

	return GM_TRUE;
}

/**
* @brief 
*
* Detailed description.
* @return GM_BOOL
*
*/
static GM_BOOL GM_RSSP1_INTERCOMM_IOB_E2I_Before(INTERCOM_Cfg_struct* pintercomm, FSFB_LNK_connection_struct *pLNK_con, FSFB_LNK_object_struct *pLNK)
{
	GM_UINT8 conn_index = 0;
	int i = 0;
	GM_BOOL bRet = GM_FALSE;
	GM_UINT8 szInterBuf[512] = {0U};
	GM_UINT16 nInterBufLen = 0U;	
	

	if (NULL == pintercomm || pLNK_con == NULL || pLNK == NULL)
	{
		return GM_FALSE;
	}
	if (pintercomm->type != GM_RSSP1_INTERCOMM_Type_IOB)
	{
		return GM_FALSE;
	}

	conn_index = pLNK_con->index;
	if (conn_index >= pLNK->connection_nums)
	{
		return GM_FALSE;
	}	
	
	for (i = 0; i < GM_RSSP1_MAX_LINK_CHANNEL; i++)
	{
		/*
		* 每次调用之前清空队列 clear send msg queue
		*/
		

/*		GM_MQ_Fixed_Flush(&(pintercomm->chnl_IOB[i].stInDataQ));*/
		while(!FSFB_Is_Msg_Queue_Empty(&(g_Link_MQ[conn_index].RCV_SND_MQ[i].RCV_MQ)))
		{
			GM_RSSP1_com_pri_struct stQElem;

			GM_memset(szInterBuf, 0x00, sizeof(szInterBuf));
			GM_memset(&stQElem, 0x00, sizeof(stQElem));

			
			
			bRet = FSFB_Msg_Queue_Get(&(g_Link_MQ[conn_index].RCV_SND_MQ[i].RCV_MQ), (void*)&stQElem);
			if (bRet)
			{
				
									printf("read g_link_MQ ok\n");

				/***
				* 内网数据传输时需要增加1个字节的内网数据头(采用本链鲁在所有链路中的索引)
				***/

/*				printf("IOB[%s:%d] read external g_Link_MQ[%d][%d].RCV_MQ\n", 
					pintercomm->chnl_IOB[i].addr_cfg.local_ip, 
					pintercomm->chnl_IOB[i].addr_cfg.local_port,
					conn_index,
					i);
*/
                printf("intercomm get from g_Link, %d\n", i);
				nInterBufLen = stQElem.bytes_count + GM_RSSP1_INTERCOMM_HEAD_LEN;
				szInterBuf[GM_RSSP1_INTERCOMM_HEAD_INDEX] = conn_index;
				GM_memcpy(&szInterBuf[GM_RSSP1_INTERCOMM_HEAD_INDEX + GM_RSSP1_INTERCOMM_HEAD_LEN], stQElem.byte, stQElem.bytes_count);
				(void)GM_MQ_Fixed_Write(&(pintercomm->chnl_IOB[i].stInDataQ), szInterBuf, nInterBufLen);
			}
			else
			{
				(void)FSFB_Msg_Queue_Clear(&(g_Link_MQ[conn_index].RCV_SND_MQ[i].RCV_MQ));
				break;
			}
		}
	}

	return GM_TRUE;
}

/**
* @brief 
*
* Detailed description.
* @return GM_BOOL
*
*/
static GM_BOOL GM_RSSP1_INTERCOMM_IOB_E2I(INTERCOM_Cfg_struct* pintercomm, FSFB_LNK_connection_struct *pLNK_con)
{
	int index = 0;
	GM_UINT8 szOutBuf[512] = {0U};
	GM_UINT16 nBufLen = sizeof(szOutBuf);
	GM_BOOL bRet = GM_FALSE;
	int send_rt = 0;
	GM_UINT8 tryCount = 0U;
	const GM_UINT8 TRY_MAX_COUNT = 2U;	
	
			
	if (NULL == pintercomm || pLNK_con == NULL)
	{
		return GM_FALSE;
	}
	if (pintercomm->type != GM_RSSP1_INTERCOMM_Type_IOB)
	{
		return GM_FALSE;
	}

	for (index = 0; index < GM_RSSP1_MAX_LINK_CHANNEL; index++)
	{
		if (pintercomm->chnl_IOB[index].sock < 0)
		{
			continue;
		}

		
		while(GM_MQ_Fixed_Get_Msg_Num(&(pintercomm->chnl_IOB[index].stInDataQ)) > 0)
		{
				
			
	       send_rt = 0;
	       tryCount = 0;
           nBufLen = sizeof(szOutBuf);
		   GM_memset(szOutBuf, 0x00, sizeof(szOutBuf));
			
		    printf("mark33 %d\n", index);	
			while(GM_FALSE == INTERCOMM_Socket_Is_Writable(pintercomm->chnl_IOB[index].sock, pintercomm->chnl_IOB[index].max_socket_value , 0))
			{
				/***
				* 增加1次发送是否可写的尝试机会
				***/
				tryCount++;
				if (tryCount >= TRY_MAX_COUNT)
				{
					break;
				}

			}
			if (tryCount >= TRY_MAX_COUNT)
			{
				break;
			}

            bRet = GM_MQ_Fixed_Read(&(pintercomm->chnl_IOB[index].stInDataQ), szOutBuf, &nBufLen);
            if (bRet && (nBufLen > 0U) && (pintercomm->chnl_IOB[index].sock > 0))
			{/* 发送数据包延时，防止粘包 */

				send_rt = sendto(pintercomm->chnl_IOB[index].sock, (char*)szOutBuf, nBufLen, 0, 
								(struct sockaddr *)&(pintercomm->chnl_IOB[index].addr_cfg.remote_addr) ,
								sizeof(pintercomm->chnl_IOB[index].addr_cfg.remote_addr) );        
				if (send_rt != nBufLen)
				{/* close socket */
					INTERCOMM_Socket_Close(&(pintercomm->chnl_IOB[index].sock));
					break;
				}
				#ifdef WIN32
				printf("IOB[%s:%d] send CPUB[%s:%d] len:%d\n", 
					pintercomm->chnl_IOB[index].addr_cfg.local_ip, 
					pintercomm->chnl_IOB[index].addr_cfg.local_port,
					pintercomm->chnl_IOB[index].addr_cfg.remote_ip,
					pintercomm->chnl_IOB[index].addr_cfg.remote_port,
					send_rt);
				#endif
			}
			else
			{
				break;
			}
		}
	}

	return GM_TRUE;
}

/**
* @brief 
*
* Detailed description.
* @return GM_BOOL
*
*/
static GM_BOOL GM_RSSP1_INTERCOMM_IOB_E2I_After(INTERCOM_Cfg_struct* pintercomm, FSFB_LNK_connection_struct *pLNK_con)
{
	/***
	* 预留该函数
	***/
	int i = 0;

    if ((NULL == pintercomm) || (pLNK_con == NULL))
    {
        return GM_FALSE;
    }
    if (pintercomm->type != GM_RSSP1_INTERCOMM_Type_IOB)
    {
        return GM_FALSE;
    }

	return GM_TRUE;
}

/**
* @brief 
*
* Detailed description.
* @return GM_BOOL
*
*/
static GM_BOOL GM_RSSP1_INTERCOMM_IOB_I2E_Before(INTERCOM_Cfg_struct* pintercomm)
{
	int index = 0;

	if (NULL == pintercomm)
	{
		return GM_FALSE;
	}
	if (pintercomm->type != GM_RSSP1_INTERCOMM_Type_IOB)
	{
		return GM_FALSE;
	}

	for (index = 0; index < GM_RSSP1_MAX_LINK_CHANNEL; index++)
	{	
		GM_INT32 recv_len = 0;
		char szRecvBuf[GM_RSSP1_MAX_SAFETY_DAT_LEN * 2]  = {0};  /* 预留空间，防止越界 */
		int remote_addr_len = 0;

		if (pintercomm->chnl_IOB[index].sock < 0)
		{
			continue;
		}
		if (GM_FALSE == INTERCOMM_Socket_Is_Readable(pintercomm->chnl_IOB[index].sock, pintercomm->chnl_IOB[index].max_socket_value , 0))
		{
			continue;
		}
		GM_MQ_Fixed_Flush(&(pintercomm->chnl_IOB[index].stOutDataQ));

		remote_addr_len = sizeof(struct sockaddr);
		recv_len = recvfrom(pintercomm->chnl_IOB[index].sock, szRecvBuf , sizeof(szRecvBuf) , 0 , (struct sockaddr *)(&pintercomm->chnl_IOB[index].addr_cfg.remote_addr) , &remote_addr_len);
		if (0 > recv_len)
		{
			/* recv error close socket */
			INTERCOMM_Socket_Close(&(pintercomm->chnl_IOB[index].sock));
			continue;
		}
		else if (0 == recv_len)
		{
			/* 不作任何处理 The  return  value  will be 0 when the peer has performed an orderly shutdown*/
			;
		}
		else if (0 < recv_len)
		{
			if (recv_len > GM_RSSP1_MAX_SAFETY_DAT_LEN + 1)
			{
				/* 不作任何处理,超出 安全数据长度 + 1
				"+1"报文的第1个字节为报文对应的外网在所有连接中的索引
				*/
			}
			else
			{
				#ifdef WIN32
				printf("IOB[%s:%d] recv CPUB[%s:%d] len:%d\n", 
					pintercomm->chnl_IOB[index].addr_cfg.local_ip, 
					pintercomm->chnl_IOB[index].addr_cfg.local_port,
					pintercomm->chnl_IOB[index].addr_cfg.remote_ip,
					pintercomm->chnl_IOB[index].addr_cfg.remote_port,
					recv_len);
				#endif
				GM_MQ_Fixed_Write(&(pintercomm->chnl_IOB[index].stOutDataQ), (GM_UINT8*)szRecvBuf, (GM_UINT16)recv_len);
			}
		}
		else
		{
			/* 不会出现该情况，增加可读性 */
			;
		}
	}
	
	return GM_TRUE;
}

/**
* @brief 
*
* Detailed description.
* @return GM_BOOL
*
*/
static GM_BOOL GM_RSSP1_INTERCOMM_IOB_I2E(INTERCOM_Cfg_struct* pintercomm, FSFB_LNK_object_struct *pLNK)
{
    GM_UINT32 index = 0U;

    if ((NULL == pintercomm) || (pLNK == NULL))
    {
        return GM_FALSE;
    }
    if (pintercomm->type != GM_RSSP1_INTERCOMM_Type_IOB)
    {
        return GM_FALSE;
    }

    for (index = 0U; index < GM_RSSP1_MAX_LINK_CHANNEL; index++)
    {
        while(GM_MQ_Fixed_Get_Msg_Num(&(pintercomm->chnl_IOB[index].stOutDataQ)) > 0)
        {
            GM_UINT8 szQElem[1500U] = {0U};
            GM_UINT16 nQElemLen = sizeof(szQElem);
            GM_BOOL bRet = GM_FALSE;
            GM_UINT16 con_index = 0U;
            FSFB_LNK_connection_struct* pLNK_con = NULL;
            GM_RSSP1_com_pri_struct stSndQElem;
            GM_RSSP1_Write_Q_Return_Enum write_q_rt = Q_WRITE_FAIL;

			bRet = GM_MQ_Fixed_Read(&(pintercomm->chnl_IOB[index].stOutDataQ), szQElem, &nQElemLen);
			if (!bRet)
			{
				break;
			}
			
			/***
			* 解析内网数据时，首先取出内网数据头
			***/
			con_index = szQElem[GM_RSSP1_INTERCOMM_HEAD_INDEX];
			if (con_index >= pLNK->connection_nums)
			{
				break;
			}

			/*pLNK_con = &(pLNK->connection[con_index]);*/
			
			/***
			* 将内网发送至外网的数据放入外网数据队列
			***/
            GM_memset(&stSndQElem, 0x00U, sizeof(GM_RSSP1_com_pri_struct));
            stSndQElem.bytes_count = nQElemLen - GM_RSSP1_INTERCOMM_HEAD_LEN;
			GM_memcpy(stSndQElem.byte, &szQElem[GM_RSSP1_INTERCOMM_HEAD_INDEX + GM_RSSP1_INTERCOMM_HEAD_LEN], stSndQElem.bytes_count);
			write_q_rt = FSFB_Msg_Queue_Write(&(g_Link_MQ[con_index].RCV_SND_MQ[index].SND_MQ), &stSndQElem);
			if (Q_WRITE_FAIL == write_q_rt)
			{
				FSFB_Msg_Queue_Clear(&(g_Link_MQ[con_index].RCV_SND_MQ[index].SND_MQ));
				break;
			}
			#ifdef WIN32
			printf("IOB[%s:%d] write external g_Link_MQ[%d][%d].SND_MQ\n", 
				pintercomm->chnl_IOB[index].addr_cfg.local_ip, 
				pintercomm->chnl_IOB[index].addr_cfg.local_port,
				con_index,
				index);
			#endif
		}
		if (GM_MQ_Fixed_Get_Msg_Num(&(pintercomm->chnl_IOB[index].stOutDataQ)) > 0)
		{
			/***
			* 数据处理过程出错，直接清空队列
			***/
			GM_MQ_Fixed_Flush(&(pintercomm->chnl_IOB[index].stOutDataQ));
		}
	}

	return GM_TRUE;
}

/**
* @brief 
*
* Detailed description.
* @return GM_BOOL
*
*/
static GM_BOOL GM_RSSP1_INTERCOMM_IOB_I2E_After(INTERCOM_Cfg_struct* pintercomm)
{
	if (pintercomm == NULL)
	{
		return GM_FALSE;
	}
	if (pintercomm->type != GM_RSSP1_INTERCOMM_Type_IOB)
	{
		return GM_FALSE;
	}

	return GM_TRUE;
}
#endif

/***********************************************************************************************
************************************************************************************************
*
* CPU板通信控制器部分
*
***********************************************************************************************
***********************************************************************************************/
#ifdef  CFM_Part
static GM_BOOL GM_RSSP1_INTERCOMM_CPUB_Matain(INTERCOM_Cfg_struct* pintercomm);
/**
* @brief CPU通信控制器 接收IO板内网的数据前的准备工作
*
* Detailed description.
* @param[in] pintercomm:内网通信数据结构体指针
* @return GM_BOOL
*/
static GM_BOOL GM_RSSP1_INTERCOMM_CPUB_Recv_Before(INTERCOM_Cfg_struct* pintercomm);
/**
* @brief CPU通信控制器 接收IO板内网的数据
*
* Detailed description.
* @param[in] pintercomm:内网通信数据结构体指针
* @return GM_BOOL
*/
static GM_BOOL GM_RSSP1_INTERCOMM_CPUB_Recv(INTERCOM_Cfg_struct* pintercomm);
/**
* @brief CPU通信控制器 接收IO板内网的数据后，交给CFM层处理(CFM会交给SFM层处理->SFM会给应用处理 不归本函数处理)
*
* Detailed description.
* @param[in] pintercomm:内网通信数据结构体指针
* @return GM_BOOL
*/
static GM_BOOL GM_RSSP1_INTERCOMM_CPUB_Recv_After(INTERCOM_Cfg_struct* pintercomm);

/**
* @brief CPU通信控制器数据的发送
*
* Detailed description.
* @return GM_BOOL
*/
/*static GM_BOOL GM_RSSP1_INTERCOMM_CPUB_TO_IO(INTERCOM_Cfg_struct* pintercomm);*/

/**
* @brief CPU通信控制器 数据发送前的准备
*
* Detailed description.
* @return GM_BOOL
*/
static GM_BOOL GM_RSSP1_INTERCOMM_CPUB_Send_Before(INTERCOM_Cfg_struct* pintercomm, GM_RSSP1_CFM_object_struct* pCFM);

/**
* @brief CPU通信控制器 数据发送
*
* Detailed description.
* @return GM_BOOL
*/
static GM_BOOL GM_RSSP1_INTERCOMM_CPUB_Send(INTERCOM_Cfg_struct* pintercomm, GM_RSSP1_CFM_object_struct* pCFM);

/**
* @brief CPU通信控制器 数据发送后的收尾工作
*
* Detailed description.
* @return GM_BOOL
*/
static GM_BOOL GM_RSSP1_INTERCOMM_CPUB_Send_After(INTERCOM_Cfg_struct* pintercomm, GM_RSSP1_CFM_object_struct* pCFM);
/**
* @brief 内网通信CPU板从IO板接收数据 
*
* Detailed description.
* @return GM_BOOL
*
*/
GM_BOOL GM_RSSP1_INTERCOMM_CPUB_From_IOB()
{
	GM_BOOL bRet = GM_FALSE;
	INTERCOM_Cfg_struct* pInterComm = NULL;

	bRet = GM_RSSP1_INTERCOMM_Init_Finished();
	if (!bRet)
	{
		return GM_FALSE;
	}

	pInterComm = GM_RSSP1_INTERCOMM_Get_Stru();
	if (NULL == pInterComm)
	{
		return GM_FALSE;
	}

	if (pInterComm->type != GM_RSSP1_INTERCOMM_Type_CPUB)
	{
		return GM_FALSE;
	}

	(void)GM_RSSP1_INTERCOMM_CPUB_Matain(pInterComm);
	(void)GM_RSSP1_INTERCOMM_CPUB_Recv_Before(pInterComm);
	(void)GM_RSSP1_INTERCOMM_CPUB_Recv(pInterComm);
	(void)GM_RSSP1_INTERCOMM_CPUB_Recv_After(pInterComm);

	return GM_TRUE;
}

/**
* @brief 内网通信CPU板给IO板发送数据 
*
* Detailed description.
* @return GM_BOOL
*
*/
GM_BOOL GM_RSSP1_INTERCOMM_CPUB_To_IOB( GM_RSSP1_CFM_object_struct* pCFM)
{
	GM_BOOL bRet = GM_FALSE;
	INTERCOM_Cfg_struct* pInterComm = NULL;

	if (pCFM == NULL)
	{
		return GM_FALSE;
	}

	bRet = GM_RSSP1_INTERCOMM_Init_Finished();
	if (!bRet)
	{
		return GM_FALSE;
	}

	pInterComm = GM_RSSP1_INTERCOMM_Get_Stru();
	if (NULL == pInterComm)
	{
		return GM_FALSE;
	}

	if (pInterComm->type != GM_RSSP1_INTERCOMM_Type_CPUB)
	{
		return GM_FALSE;
	}

	(void)GM_RSSP1_INTERCOMM_CPUB_Matain(pInterComm);
	(void)GM_RSSP1_INTERCOMM_CPUB_Send_Before(pInterComm, pCFM);
	(void)GM_RSSP1_INTERCOMM_CPUB_Send(pInterComm, pCFM);
	(void)GM_RSSP1_INTERCOMM_CPUB_Send_After(pInterComm, pCFM);

	return GM_TRUE;
}

/**
* @brief 内网通信CPU通信维护 
*
* Detailed description.
* @return GM_BOOL
*
*/
static GM_BOOL GM_RSSP1_INTERCOMM_CPUB_Matain(INTERCOM_Cfg_struct* pintercomm)
{
	GM_INT32 rt = GM_RSSP1_ERROR;
	int i = 0;

	if (NULL == pintercomm)
	{
		return GM_FALSE;
	}
	if (pintercomm->type != GM_RSSP1_INTERCOMM_Type_CPUB)
	{
		return GM_FALSE;
	}

    for (i = 0; i< GM_RSSP1_CFM_MAX_CHANNEL_NUM; i++)
    {    
        if (((GM_INT16)0) > (pintercomm->chnl_CPUB[i].sock))
		{
			rt = INTERCOMM_Socket_Init(
				&(pintercomm->chnl_CPUB[i].sock) ,
				SOCK_DGRAM ,
				&(pintercomm->chnl_CPUB[i].addr_cfg.local_addr) ,
				(1500U*20U),
				(1500U*20U),
				&(pintercomm->chnl_CPUB[i].max_socket_value)
				);

			if (GM_RSSP1_ERROR == rt)
			{
				continue;	
			}
		}
	}

	return GM_TRUE;
}

/**
* @brief CPU通信控制器 接收IO板内网的数据前的准备工作
*
* Detailed description.
* @param[in] pintercomm:内网通信数据结构体指针
* @return GM_BOOL
*/
static GM_BOOL GM_RSSP1_INTERCOMM_CPUB_Recv_Before(INTERCOM_Cfg_struct* pintercomm)
{
    GM_UINT32 chnl_index = 0U;

	if (pintercomm == NULL)
	{
		return GM_FALSE;
	}
	if (pintercomm->type != GM_RSSP1_INTERCOMM_Type_CPUB)
	{
		return GM_FALSE;
	}

    for (chnl_index = 0U; chnl_index < ((GM_UINT32)GM_RSSP1_CFM_MAX_CHANNEL_NUM); chnl_index++)
    {
        GM_MQ_Fixed_Flush((GM_MQ_Fixed_Struct *)&(pintercomm->chnl_CPUB[chnl_index].stInDataQ));    
    }

	return GM_TRUE;
}

/**
* @brief CPU通信控制器 接收IO板内网的数据
*
* Detailed description.
* @param[in] pintercomm:内网通信数据结构体指针
* @return GM_BOOL
*/
static GM_BOOL GM_RSSP1_INTERCOMM_CPUB_Recv(INTERCOM_Cfg_struct* pintercomm)
{
    GM_UINT32 chnl_index = 0U;

	if (pintercomm == NULL)
	{
		return GM_FALSE;
	}
	if (pintercomm->type != GM_RSSP1_INTERCOMM_Type_CPUB)
	{
		return GM_FALSE;
	}

    for (chnl_index = 0U; chnl_index < ((GM_UINT32)GM_RSSP1_CFM_MAX_CHANNEL_NUM); chnl_index++)
    {
        GM_INT32 recv_len = 0;
        char szRecvBuf[GM_RSSP1_MAX_SAFETY_DAT_LEN * 2U]  = {0};  /* 预留空间，防止越界 */
        int remote_addr_len = 0;

		if (pintercomm->chnl_CPUB[chnl_index].sock < 0)
		{
			continue;
		}
		while(INTERCOMM_Socket_Is_Readable(pintercomm->chnl_CPUB[chnl_index].sock, pintercomm->chnl_CPUB[chnl_index].max_socket_value , 0) == GM_TRUE)
		{
			
		remote_addr_len = sizeof(struct sockaddr);
        recv_len = recvfrom(pintercomm->chnl_CPUB[chnl_index].sock, szRecvBuf , sizeof(szRecvBuf) , 0 , (struct sockaddr *)(&pintercomm->chnl_CPUB[chnl_index].addr_cfg.remote_addr) , &remote_addr_len);
        if (((GM_INT32)0) > recv_len)
        {
            /* recv error close socket */
            INTERCOMM_Socket_Close(&(pintercomm->chnl_CPUB[chnl_index].sock));
				break;
        }
        else if (((GM_INT32)0) == recv_len)
        {
            /* 不作任何处理 The  return  value  will be 0 when the peer has performed an orderly shutdown*/
				break;
        }
        else if (((GM_INT32)0) < recv_len)
		{
			if (recv_len > GM_RSSP1_MAX_SAFETY_DAT_LEN)
			{
				/* 不作任何处理,超出 安全数据长度 + 1
				"+1"报文的第1个字节为报文对应的外网在所有连接中的索引
				*/
			}
			else
			{
				if(chnl_index == 0)
/*			    printf("RL%d\n",recv_len);*/
/*				printf("recv rssp1 udp data len=%d from ethio, chn = %d\n", recv_len, chnl_index);*/
                GM_MQ_Fixed_Write((GM_MQ_Fixed_Struct *)&(pintercomm->chnl_CPUB[chnl_index].stInDataQ), (GM_UINT8*)szRecvBuf, (GM_UINT16)recv_len);
            }
        }
		else
		{
			/* 不会出现该情况，增加可读性 */
				break;
			}			
		}
	}

	return GM_TRUE;
}

/**
* @brief CPU通信控制器 接收IO板内网的数据后，交给CFM层处理(CFM会交给SFM层处理->SFM会给应用处理 不归本函数处理)
*
* Detailed description.
* @param[in] pintercomm:内网通信数据结构体指针
* @return GM_BOOL
*/
static GM_BOOL GM_RSSP1_INTERCOMM_CPUB_Recv_After(INTERCOM_Cfg_struct* pintercomm)
{
	GM_UINT32 chnl_index = 0U;
	
	GM_UINT8 szQElem[1024] = {0U};
	GM_UINT16 nQElemLen = sizeof(szQElem);
	GM_BOOL bRet = GM_FALSE;
	GM_UINT16 con_index = 0U;
	GM_RSSP1_com_pri_struct stRecvQElem;
	GM_RSSP1_Write_Q_Return_Enum q_write_rt = Q_WRITE_FAIL;	

	if (pintercomm == NULL)
	{
		return GM_FALSE;
	}
	if (pintercomm->type != GM_RSSP1_INTERCOMM_Type_CPUB)
	{
		return GM_FALSE;
	}

    for (chnl_index = 0U; chnl_index < (GM_UINT32)GM_RSSP1_CFM_MAX_CHANNEL_NUM; chnl_index++)
    {
        while(GM_MQ_Fixed_Get_Msg_Num((GM_MQ_Fixed_Struct *)&(pintercomm->chnl_CPUB[chnl_index].stInDataQ)) > 0)
        {

	        nQElemLen = sizeof(szQElem);
			GM_memset(szQElem, 0x00U, sizeof(szQElem));

			
			bRet = GM_MQ_Fixed_Read(&(pintercomm->chnl_CPUB[chnl_index].stInDataQ), szQElem, &nQElemLen);
					
			if (!bRet)
			{
				break;
			}
			
             con_index = szQElem[0U];
            if (con_index >= (GM_UINT16)GM_RSSP1_MAX_SAFETY_CONNECTION_NUM)
            {
                break;
            }

            GM_memset((void *)&stRecvQElem, 0x00U, ((size_t)(sizeof(GM_RSSP1_com_pri_struct))));

            stRecvQElem.bytes_count = nQElemLen - GM_RSSP1_INTERCOMM_HEAD_LEN;
            GM_memcpy(((void *)stRecvQElem.byte), ((const void *)(&szQElem[GM_RSSP1_INTERCOMM_HEAD_INDEX + GM_RSSP1_INTERCOMM_HEAD_LEN])), ((size_t)stRecvQElem.bytes_count));
			
			q_write_rt = FSFB_Msg_Queue_Write(&(g_Link_MQ[con_index].RCV_SND_MQ[chnl_index].RCV_MQ), &stRecvQElem);
			if (Q_WRITE_FAIL == q_write_rt)
			{			
				FSFB_Msg_Queue_Clear(&(g_Link_MQ[con_index].RCV_SND_MQ[chnl_index].RCV_MQ));
				break;
			}
			
/*			printf("write g_Link_MQ OK!\n");*/
		}

        if (GM_MQ_Fixed_Get_Msg_Num((GM_MQ_Fixed_Struct *)&(pintercomm->chnl_CPUB[chnl_index].stInDataQ)) > 0)
        {
            GM_MQ_Fixed_Flush(&(pintercomm->chnl_CPUB[chnl_index].stInDataQ));
        }
    }

	return GM_TRUE;
}

/**
* @brief CPU通信控制器 数据发送前的准备
*
* Detailed description.
* @return GM_BOOL
*/
static GM_BOOL GM_RSSP1_INTERCOMM_CPUB_Send_Before(INTERCOM_Cfg_struct* pintercomm, GM_RSSP1_CFM_object_struct* pCFM)
{
    GM_UINT16 chnl_index = 0U;
    GM_UINT8 con_index = 0U;
	GM_RSSP1_com_pri_struct stQElem;
	GM_BOOL bRet = GM_FALSE;
    GM_UINT8 szInterBuf[1500U] = {0U};
    GM_UINT16 nInterBufLen = 0U;
	/*GM_RSSP1_CFM_connection_struct* pCFM_con = NULL;*/

	if (NULL == pintercomm || NULL == pCFM)
	{
		return GM_FALSE;
	}
	if (pintercomm->type != GM_RSSP1_INTERCOMM_Type_CPUB)
	{
		return GM_FALSE;
	}
	
	for (chnl_index = 0; chnl_index < GM_RSSP1_CFM_MAX_CHANNEL_NUM; chnl_index++)
	{
		GM_MQ_Fixed_Flush(&(pintercomm->chnl_CPUB[chnl_index].stOutDataQ));

		for (con_index = 0; con_index < pCFM->connection_nums; con_index++)
		{
			while(!FSFB_Is_Msg_Queue_Empty(&(g_Link_MQ[con_index].RCV_SND_MQ[chnl_index].SND_MQ)))
			{


                GM_memset((void *)&stQElem, 0x00U, ((size_t)(sizeof(stQElem))));

				bRet = FSFB_Msg_Queue_Get(&(g_Link_MQ[con_index].RCV_SND_MQ[chnl_index].SND_MQ), (void*)&stQElem);
				if (bRet)
				{
					/***
					* 内网数据传输时需要增加1个字节的内网数据头(采用本链路在所有链路中的索引)
					***/
					nInterBufLen = stQElem.bytes_count + GM_RSSP1_INTERCOMM_HEAD_LEN;
					szInterBuf[GM_RSSP1_INTERCOMM_HEAD_INDEX] = con_index;
                    GM_memcpy(((void *)(&szInterBuf[GM_RSSP1_INTERCOMM_HEAD_INDEX + GM_RSSP1_INTERCOMM_HEAD_LEN])), (const void*)stQElem.byte, (size_t)stQElem.bytes_count);
                    (void)GM_MQ_Fixed_Write(&(pintercomm->chnl_CPUB[chnl_index].stOutDataQ), szInterBuf, nInterBufLen);
					
				}
				else
				{
					(void)FSFB_Msg_Queue_Clear(&(g_Link_MQ[con_index].RCV_SND_MQ[chnl_index].SND_MQ));
					break;
				}
			}
		}
	}

	return GM_TRUE;
}

/**
* @brief CPU通信控制器 数据发送
*
* Detailed description.
* @return GM_BOOL
*/
static GM_BOOL GM_RSSP1_INTERCOMM_CPUB_Send(INTERCOM_Cfg_struct* pintercomm,  GM_RSSP1_CFM_object_struct* pCFM)
{
    GM_UINT16 chnl_index = 0U;
    GM_UINT8 con_index = 0U;
	
	GM_UINT8 szOutBuf[800] = {0U};
	GM_UINT16 nBufLen = sizeof(szOutBuf);
	GM_BOOL bRet = GM_FALSE;
	int send_rt = 0;
    GM_UINT8 tryCount = 0U;
    const GM_UINT8 TRY_MAX_COUNT = 2U;

    if ((NULL == pintercomm) || (NULL == pCFM))
    {
        return GM_FALSE;
    }
    if (pintercomm->type != GM_RSSP1_INTERCOMM_Type_CPUB)
    {
        return GM_FALSE;
    }

    for (chnl_index = 0U; chnl_index < (GM_UINT16)GM_RSSP1_CFM_MAX_CHANNEL_NUM; chnl_index++)
    {
        if (pintercomm->chnl_CPUB[chnl_index].sock < ((GM_INT16)0))
        {
            continue;
        }

        while(GM_MQ_Fixed_Get_Msg_Num((GM_MQ_Fixed_Struct *)&(pintercomm->chnl_CPUB[chnl_index].stOutDataQ)) > ((GM_INT32)0))
        {


			GM_memset(szOutBuf, 0x00U, sizeof(szOutBuf));
			nBufLen = sizeof(szOutBuf);


            bRet = GM_MQ_Fixed_Read(&(pintercomm->chnl_CPUB[chnl_index].stOutDataQ), szOutBuf, &nBufLen);
            if (bRet && (nBufLen > 0U) && (pintercomm->chnl_CPUB[chnl_index].sock > 0))
			{/* 发送数据包延时，防止粘包 */
		
                send_rt = sendto(pintercomm->chnl_CPUB[chnl_index].sock, (char*)szOutBuf, (int)nBufLen, MSG_FSC_DA, 
                                (struct sockaddr *)&(pintercomm->chnl_CPUB[chnl_index].addr_cfg.remote_addr) ,
                                ((int)sizeof(pintercomm->chnl_CPUB[chnl_index].addr_cfg.remote_addr)) );        

/*			    if(chnl_index == 0)
				   printf("SL%d\n", send_rt);	
*/			   
				if (send_rt != nBufLen)
				{/* close socket */
					INTERCOMM_Socket_Close(&(pintercomm->chnl_CPUB[chnl_index].sock));
					break;
				}
			}
			else
			{
				break;
			}
		}
	}

	return GM_TRUE;
}

/**
* @brief CPU通信控制器 数据发送后的收尾工作
*
* Detailed description.
* @return GM_BOOL
*/
static GM_BOOL GM_RSSP1_INTERCOMM_CPUB_Send_After(INTERCOM_Cfg_struct* pintercomm,  GM_RSSP1_CFM_object_struct* pCFM)
{
    if ((pintercomm == NULL) || (pCFM == NULL))
    {
        return GM_FALSE;
    }

	return GM_TRUE;
}
#endif