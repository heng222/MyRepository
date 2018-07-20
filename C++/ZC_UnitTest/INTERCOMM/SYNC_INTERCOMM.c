/**
* @file SYNC_INTERCOMM.c
* @brief 系间同步接口实现文件
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
#include "SYNC_INTERCOMM.h"
#include "SYNC_INTERCOMM_Init.h"
#include "GM_RSSP1_INTERCOMM_Socket.h"
#include "..\cspadpt\Vcp_Service_Interface.h"



/***********************************************************************************************/



static GM_BOOL SYNC_INTERCOMM_Matain(SYNC_INTERCOM_Cfg_struct* pintercomm);



static GM_BOOL SYNC_INTERCOMM_Recv(SYNC_INTERCOM_Cfg_struct* pintercomm);



static GM_BOOL SYNC_INTERCOMM_Send(SYNC_INTERCOM_Cfg_struct* pintercomm);



/**
* @brief 系间同步 数据组包
*
* Detailed description.
* @param[in] pintercomm:系间同步数据结构体指针
* @return GM_BOOL
*/
static GM_BOOL SYNC_INTERCOMM_Packet(SYNC_INTERCOM_Cfg_struct* pintercomm);

/**
* @brief 系间同步 通道维护接口
*
* Detailed description.
* @param[in] void
* @return GM_BOOL
*/
GM_BOOL SYNC_INTERCOMM_Matain_Proc(void)
{
	GM_BOOL bRet = GM_FALSE;
	SYNC_INTERCOM_Cfg_struct* pInterComm = NULL;


	bRet = SYNC_INTERCOMM_Init_Finished();
	if (!bRet)
	{
		return GM_FALSE;
	}

	pInterComm = SYNC_INTERCOMM_Get_Sync_Intercomm_Cfg();
	if (NULL == pInterComm)
	{
		return GM_FALSE;
	}


	(void)SYNC_INTERCOMM_Matain(pInterComm);
	return GM_TRUE;
}
/**
* @brief 系间同步 数据接收接口
*
* Detailed description.
* @param[in] void
* @return GM_BOOL
*/
GM_BOOL SYNC_INTERCOMM_Recv_Proc(void)
{
	GM_BOOL bRet = GM_FALSE;
	SYNC_INTERCOM_Cfg_struct* pInterComm = NULL;
	bRet = SYNC_INTERCOMM_Init_Finished();
	if (!bRet)
	{
		return GM_FALSE;
	}
	pInterComm = SYNC_INTERCOMM_Get_Sync_Intercomm_Cfg();
	if (NULL == pInterComm)
	{
		return GM_FALSE;
	}
	(void)SYNC_INTERCOMM_Recv(pInterComm);
/*    SYNC_INTERCOMM_Csp_Safety_Layer_Statistics();*/
	return GM_TRUE;
}
/**
* @brief 系间同步 数据发送接口
*
* Detailed description.
* @param[in] void
* @return GM_BOOL
*/
GM_BOOL SYNC_INTERCOMM_Send_Proc(void)
{
	GM_BOOL bRet = GM_FALSE;
	SYNC_INTERCOM_Cfg_struct* pInterComm = NULL;
	bRet = SYNC_INTERCOMM_Init_Finished();
	if (!bRet)
	{
		return GM_FALSE;
	}
	pInterComm = SYNC_INTERCOMM_Get_Sync_Intercomm_Cfg();
	if (NULL == pInterComm)
	{
		return GM_FALSE;
	}
	SYNC_INTERCOMM_Packet(pInterComm);
	(void)SYNC_INTERCOMM_Send(pInterComm);
/*	SYNC_INTERCOMM_Csp_Safety_Layer_Statistics();*/

	return GM_TRUE;
}

/**
* @brief 系间同步 通信链路维护
*
* Detailed description.
* @param[in] pintercomm:系间同步数据结构体指针
* @return GM_BOOL
*/
static GM_BOOL SYNC_INTERCOMM_Matain(SYNC_INTERCOM_Cfg_struct* pintercomm)
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

	for (i = 0; i< SYNC_INTERCOMM_MAX_LINK_CHANNEL; i++)
	{	
		if (0 > pintercomm->chnl_Sync[i].sock)
		{
			rt = INTERCOMM_Socket_Init(
				(int)&(pintercomm->chnl_Sync[i].sock) ,
				(int)SOCK_DGRAM ,
				&(pintercomm->chnl_Sync[i].addr_cfg.local_addr) ,
				(unsigned short)(1500U*30U),
				(unsigned short)(1500U*30U),
				&(pintercomm->chnl_Sync[i].max_socket_value)
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
* @brief 系间同步 接收数据
*
* Detailed description.
* @param[in] pintercomm:系间同步数据结构体指针
* @return GM_BOOL
*/
static GM_BOOL SYNC_INTERCOMM_Recv(SYNC_INTERCOM_Cfg_struct* pintercomm)
{
	GM_UINT32 chnl_index = 0U;
	GM_INT32 recv_len = 0U;
	GM_UINT8 szRecvBuf[1400]  = {0U};  /* 预留空间，防止越界 */
	int remote_addr_len = 0;	
	void* l_dest = NULL;
	UINT32* l_MainCyle = NULL;
	INT32 l_DiffCyle = 0;
	UINT32 l_Offset = 0U;
	UINT8* l_InputPtr = NULL;
	UINT32 MasterID= 0;
	UINT32 mSysID  = 0;
	F_VCP_GetSystemId(&mSysID);
	F_VCP_GetMasterId(&MasterID);
	if (pintercomm == NULL)
	{
		return GM_FALSE;
	}


	for (chnl_index = 0U; chnl_index < SYNC_INTERCOMM_MAX_LINK_CHANNEL; chnl_index++)
	{
		pintercomm->chnl_Sync[chnl_index].InDataLen = 0U; 
        pintercomm->chnl_Sync[chnl_index].timeout_cycle++;
		if (pintercomm->chnl_Sync[chnl_index].timeout_cycle > SYNC_INTERCOMM_MAX_LINK_TIMEOUT_CYCLE)
		{
			CSPADPT_Set_OppoMachine_State(0U);          
		}

		if (pintercomm->chnl_Sync[chnl_index].sock < 0)
		{
			continue;
		}
		
		pintercomm->chnl_Sync[chnl_index].InDataLen = 0U;
			
		while(GM_TRUE == INTERCOMM_Socket_Is_Readable(pintercomm->chnl_Sync[chnl_index].sock, pintercomm->chnl_Sync[chnl_index].max_socket_value , 0U))
		{
			remote_addr_len = sizeof(struct sockaddr);
			GM_memset((void*)szRecvBuf, 0x00U, (size_t)(sizeof(szRecvBuf)));
			

			recv_len = recvfrom(pintercomm->chnl_Sync[chnl_index].sock, 
			                    (char*)szRecvBuf ,
								(int)sizeof(szRecvBuf) ,
								0U ,
								(struct sockaddr *)(&pintercomm->chnl_Sync[chnl_index].addr_cfg.remote_addr) , 
								&remote_addr_len);
			if (0 > recv_len)
			{
				/* recv error close socket */
				INTERCOMM_Socket_Close(&(pintercomm->chnl_Sync[chnl_index].sock));
				continue;
			}
			else if (0 == recv_len)
			{
				/* 不作任何处理 The  return  value  will be 0 when the peer has performed an orderly shutdown*/
				continue;
			}
			else if (0 < recv_len)
			{
				
                l_dest = (void*)(pintercomm->chnl_Sync[chnl_index].pInData + pintercomm->chnl_Sync[chnl_index].InDataLen);
				GM_memcpy(l_dest,
				          (void*)szRecvBuf,
						  (size_t)recv_len);
				pintercomm->chnl_Sync[chnl_index].InDataLen += recv_len;		 

                if(pintercomm->chnl_Sync[chnl_index].InDataLen >= (1024U*200U - 2800U))
				{
					printf("RSYN-ERR1\n");
					continue;
				}				
				
			}
			else
			{
				/* 不会出现该情况，增加可读性 */
				continue;
			}			
				
							
		}
		if(pintercomm->chnl_Sync[chnl_index].InDataLen > 0U)
		{
			if(pintercomm->chnl_Sync[chnl_index].InDataLen == ((*(UINT32*)pintercomm->chnl_Sync[chnl_index].pInData) + 4U))
			{
				pintercomm->chnl_Sync[chnl_index].timeout_cycle = 0U;
				printf("SYN-RLEN=%d ", pintercomm->chnl_Sync[chnl_index].InDataLen);					
				if(*(UINT32*)(pintercomm->chnl_Sync[chnl_index].pInData + 4) == 0x55AAAA55U)
				{
					CSPADPT_Set_OppoMachine_State(*(UINT8*)(pintercomm->chnl_Sync[chnl_index].pInData + 8));
				    printf("0x%x", *(UINT8*)(pintercomm->chnl_Sync[chnl_index].pInData + 8));	
								
					if((MasterID!=mSysID) && (CSPADPT_Get_OppoMachine_State() == 0xAAU))
					{
	                    l_MainCyle = CSPADPT_Get_Main_Cycle_Ptr();	
						l_DiffCyle = (*(UINT32*)(pintercomm->chnl_Sync[chnl_index].pInData + 9)) - (*l_MainCyle);
						if(abs(l_DiffCyle) > 1)
						{
                           *l_MainCyle = *(UINT32*)(pintercomm->chnl_Sync[chnl_index].pInData + 9);	
                           printf("------%d", *l_MainCyle);							   
						}
					}
				}
				else
				if(*(UINT32*)(pintercomm->chnl_Sync[chnl_index].pInData + 4) == 0xAA5555AAU)
				{
				/* 融合后改成ZC 索明宇
				SetCiAppData(pintercomm->chnl_Sync[chnl_index].pInData);
				*/
				}
				printf("\n");					
			}				
			else
			if(pintercomm->chnl_Sync[chnl_index].InDataLen > ((*(UINT32*)pintercomm->chnl_Sync[chnl_index].pInData) + 4U))
			{

				l_Offset = 0U;			
				l_InputPtr = pintercomm->chnl_Sync[chnl_index].pInData;
				while((pintercomm->chnl_Sync[chnl_index].InDataLen > 0U )
				&& pintercomm->chnl_Sync[chnl_index].InDataLen >= ((*(UINT32*)l_InputPtr) + 4U))
				{
					if(*(UINT32*)(l_InputPtr + 4) == 0x55AAAA55U)
					{
						CSPADPT_Set_OppoMachine_State(*(UINT8*)(l_InputPtr + 8));
/*						printf("0x%x", *(UINT8*)(pintercomm->chnl_Sync[chnl_index].pInData + 8));	*/					
						if((MasterID!=mSysID) && (CSPADPT_Get_OppoMachine_State() == 0xAAU))
						{
							l_MainCyle = CSPADPT_Get_Main_Cycle_Ptr();	
							l_DiffCyle = (*(UINT32*)(l_InputPtr + 9)) - (*l_MainCyle);
							if(abs(l_DiffCyle) > 1)
							{
							   *l_MainCyle = *(UINT32*)(l_InputPtr + 9);	
/*							   printf("------%d", *l_MainCyle);		*/					   
							}
						}
						
					   l_Offset = ((*(UINT32*)l_InputPtr) + 4U);
					   pintercomm->chnl_Sync[chnl_index].InDataLen -= l_Offset;	
					   l_InputPtr = l_InputPtr + l_Offset;
						
					}
					else
					if(*(UINT32*)(l_InputPtr + 4) == 0xAA5555AAU)
					{
					/*融合后改成ZC 索明宇
					   SetCiAppData(l_InputPtr);
					*/
					   l_Offset = ((*(UINT32*)l_InputPtr) + 4U);
						pintercomm->chnl_Sync[chnl_index].InDataLen -= l_Offset;	
					   l_InputPtr = l_InputPtr + l_Offset;
				       printf("SYN-RLEN2=%d\n", l_Offset);					   
                      
					}	
                    else
					{
				        printf("RSYN-Err2\n");
						break;
					}						
					
				}					
					

			}
			else
			{
				
				printf("Error\n");
			}			
			
			
		}

	}

	return GM_TRUE;
}

/**
* @brief 系间同步 数据组包
*
* Detailed description.
* @param[in] pintercomm:系间同步数据结构体指针
* @return GM_BOOL
*/
static GM_BOOL SYNC_INTERCOMM_Packet(SYNC_INTERCOM_Cfg_struct* pintercomm)
{
	GM_UINT16 chnl_index = 0U;
	UINT32* l_CyclePtr = NULL;	
	
	if (NULL == pintercomm )
	{
		return GM_FALSE;
	}	
	
	l_CyclePtr = CSPADPT_Get_Main_Cycle_Ptr();	
	
	for (chnl_index = 0U; chnl_index < SYNC_INTERCOMM_MAX_LINK_CHANNEL; chnl_index++)
	{
		UINT32 MasterID= 0;
		UINT32 mSysID  = 0;
		F_VCP_GetSystemId(&mSysID);
		F_VCP_GetMasterId(&MasterID);									
		/*备系不发送*/
		if(MasterID!=mSysID)
		{
			CSPADPT_Get_Running_State(pintercomm->chnl_Sync[chnl_index].pOutData, (UINT32 *)(&(pintercomm->chnl_Sync[chnl_index].OutDataLen)));
	
		}	
        else
		{
			if(((*l_CyclePtr)%6 == 0U) && (CSPADPT_Get_OppoMachine_State() > 0U))
			{	/*融合后改成ZC 索明宇
				GetCiAppData(pintercomm->chnl_Sync[chnl_index].pOutData);	
				*/				
			}		
			else
			{
				CSPADPT_Get_Running_State(pintercomm->chnl_Sync[chnl_index].pOutData, (UINT32 *)(&(pintercomm->chnl_Sync[chnl_index].OutDataLen)));
			}				
			
		}		
	}		


}



/**
* @brief 系间同步 数据发送
*
* Detailed description.
* @param[in] pintercomm:系间同步数据结构体指针
* @return GM_BOOL
*/
static GM_BOOL SYNC_INTERCOMM_Send(SYNC_INTERCOM_Cfg_struct* pintercomm)
{
	GM_UINT16 chnl_index = 0U;
	GM_UINT8 con_index = 0U;
	
	GM_BOOL bRet = GM_FALSE;
	int send_rt = 0;
	GM_UINT16 nMaxSendLen = 1400U;
	GM_UINT8 nSentCount = 0U;
	GM_UINT8* pSendBuf = NULL;
	struct sockaddr* pSockAddr = NULL;
	GM_UINT32 addrSize = 0U;
	GM_UINT32 SentLen = 0U;
	void* l_dest = NULL;
	void* l_src = NULL;
	size_t l_size = 0U;

	if (NULL == pintercomm )
	{
		return GM_FALSE;
	}

	for (chnl_index = 0U; chnl_index < SYNC_INTERCOMM_MAX_LINK_CHANNEL; chnl_index++)
	{
		if (pintercomm->chnl_Sync[chnl_index].sock < 0)
		{
			continue;
		}

		
		pintercomm->chnl_Sync[chnl_index].OutDataLen = *(UINT32*)(pintercomm->chnl_Sync[chnl_index].pOutData);
		pintercomm->chnl_Sync[chnl_index].OutDataLen += 4U;
/*		printf("SYN-LEN=%d\n",pintercomm->chnl_Sync[chnl_index].OutDataLen);*/
		nSentCount = 50U;
		while((pintercomm->chnl_Sync[chnl_index].OutDataLen > 0U) && (nSentCount > 0U))
		{
			nSentCount -= 1U;	
			nMaxSendLen = 1400U;
			if(pintercomm->chnl_Sync[chnl_index].OutDataLen < nMaxSendLen)
			{
				nMaxSendLen = pintercomm->chnl_Sync[chnl_index].OutDataLen;
			}
			pSendBuf = pintercomm->chnl_Sync[chnl_index].pOutData;
			pSockAddr = (struct sockaddr *)&(pintercomm->chnl_Sync[chnl_index].addr_cfg.remote_addr);
			addrSize = sizeof(pintercomm->chnl_Sync[chnl_index].addr_cfg.remote_addr);
			send_rt = sendto(pintercomm->chnl_Sync[chnl_index].sock, 
			                (char*)pSendBuf, 
							(int)nMaxSendLen,
							(int)MSG_FSC_DA,
							pSockAddr,
							(int)addrSize);

			
			if (send_rt != nMaxSendLen)
			{/* close socket */
				INTERCOMM_Socket_Close(&(pintercomm->chnl_Sync[chnl_index].sock));
				break;
			}		
			else
			if(send_rt > 0)
			{
				
				/*判断是否全部发送，未发送的数据左移到包头下周期发送*/
				if(pintercomm->chnl_Sync[chnl_index].OutDataLen == send_rt)
				{
					/* all dat snd ok */
					pintercomm->chnl_Sync[chnl_index].OutDataLen = 0U;
				}
				else
				{
					/* mov left dat to head */
					l_dest = (void*)(pintercomm->chnl_Sync[chnl_index].pOutData);
					l_src = (void*)(pintercomm->chnl_Sync[chnl_index].pOutData + send_rt);
					l_size = (size_t)(pintercomm->chnl_Sync[chnl_index].OutDataLen - send_rt);
					GM_memcpy(l_dest,l_src,l_size);
							  
					pintercomm->chnl_Sync[chnl_index].OutDataLen -= send_rt;
				}			
				
				SentLen +=  send_rt;
			}

	

		}
        pintercomm->chnl_Sync[chnl_index].OutDataLen = 0U;		
/*        printf("SYN-SLEN=%d\n",SentLen);	*/					
	
	}

	return GM_TRUE;
}
/**
* @brief 系间同步内部通信 获取输出信息缓存指针
*
* Detailed description.
* @param[in]  void
* @param[out] void
* @return GM_UINT8*
*/
GM_UINT8* SYNC_INTERCOMM_Get_Sync_Output_Ptr(void)
{
	GM_BOOL bRet = GM_FALSE;
	SYNC_INTERCOM_Cfg_struct* pInterComm = NULL;
	GM_UINT8* pOutput = NULL;


	bRet = SYNC_INTERCOMM_Init_Finished();
	if (!bRet)
	{
		return pOutput;
	}

	pInterComm = SYNC_INTERCOMM_Get_Sync_Intercomm_Cfg();
	if (NULL == pInterComm)
	{
		return pOutput;
	}
	
	return pInterComm->chnl_Sync[0].pOutData;

}

/**
* @brief 系间同步内部通信 获取输入信息缓存指针
*
* Detailed description.
* @param[in]  void
* @param[out] void
* @return GM_UINT8*
*/
GM_UINT8* SYNC_INTERCOMM_Get_Sync_Input_Ptr(void)
{
	GM_BOOL bRet = GM_FALSE;
	SYNC_INTERCOM_Cfg_struct* pInterComm = NULL;
	GM_UINT8* pInput = NULL;


	bRet = SYNC_INTERCOMM_Init_Finished();
	if (!bRet)
	{
		return pInput;
	}

	pInterComm = SYNC_INTERCOMM_Get_Sync_Intercomm_Cfg();
	if (NULL == pInterComm)
	{
		return pInput;
	}
	
	return pInterComm->chnl_Sync[0].pInData;

}


/**
* @brief 系间同步内部通信 设置输出信息的长度
*
* Detailed description.
* @param[in]  GM_UINT32 Len
* @param[out] void
* @return void
*/
void SYNC_INTERCOMM_Set_Sync_Output_Length(GM_UINT32 Len)
{
	GM_BOOL bRet = GM_FALSE;
	SYNC_INTERCOM_Cfg_struct* pInterComm = NULL;


	bRet = SYNC_INTERCOMM_Init_Finished();
	if (!bRet)
	{
		return;
	}

	pInterComm = SYNC_INTERCOMM_Get_Sync_Intercomm_Cfg();
	if (NULL == pInterComm)
	{
		return;
	}	
	
	pInterComm->chnl_Sync[0].OutDataLen = Len;
	
}



/**
* @brief 系间同步内部通信 获取收到信息的长度
*
* Detailed description.
* @param[in]  void
* @param[out] void
* @return GM_UINT32
*/
GM_UINT32 SYNC_INTERCOMM_Get_Sync_Input_Length(void)
{
	GM_BOOL bRet = GM_FALSE;
	SYNC_INTERCOM_Cfg_struct* pInterComm = NULL;
	GM_UINT32 nLen = 0U;


	bRet = SYNC_INTERCOMM_Init_Finished();
	if (!bRet)
	{
		return nLen;
	}

	pInterComm = SYNC_INTERCOMM_Get_Sync_Intercomm_Cfg();
	if (NULL == pInterComm)
	{
		return nLen;
	}	
	
	nLen = pInterComm->chnl_Sync[0].InDataLen;
	
	return nLen;
	
}
