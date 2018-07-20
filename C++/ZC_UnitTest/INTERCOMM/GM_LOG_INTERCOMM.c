/********************************************************
*                                                                                                            
* 文 件 名： GM_LOG_INTERCOMM.c   
* 作    者：    索明宇
* 创建时间： 2018-05-15
* 功能描述： CSP平台日志函数
* 备    注： 无 
*
********************************************************/  

#include "GM_LOG_INTERCOMM.h"

INTERCOM_UDP_mng_struct LOG_INTERCOMM_mng_struct;

/*********************************内部函数声明 BEGIN****************************************/

GM_BOOL GM_LOG_INTERCOMM_INIT();

/*******************************************END*********************************************/

/*******************************************************************************************
*函数功能：初始化日志接口 创建socket，设置socket，根据I系 II系设置不同的本地IP和PORT，远端的IP
		   和端口统一。

*参数说明：无

*返回值：1 ：初始化成功
		 0 ：初始化失败
*******************************************************************************************/
GM_BOOL GM_LOG_INTERCOMM_INIT()
{
	GM_INT32 rt = GM_RSSP1_ERROR;
	
	UINT32 m_MachineID;
	/*sock 设置为-1 保证没有重复创建*/
	LOG_INTERCOMM_mng_struct.sock = GM_RSSP1_INVALID_SOCKET;
	LOG_INTERCOMM_mng_struct.max_socket_value = 30003U;
	/*I系 使用192.168.2.1：30001  II系使用192.168.2.11：30002*/
	F_VCP_GetSystemId(&m_MachineID);
	if (m_MachineID == 1U)
	{
		GM_memcpy(LOG_INTERCOMM_mng_struct.addr_cfg.local_ip, "192.168.2.1", strlen("192.168.2.1"));
		LOG_INTERCOMM_mng_struct.addr_cfg.local_port = 30001U;
	}
	else
	{
		GM_memcpy(LOG_INTERCOMM_mng_struct.addr_cfg.local_ip, "192.168.2.11", strlen("192.168.2.11"));
		LOG_INTERCOMM_mng_struct.addr_cfg.local_port = 30002U;
	}	
	LOG_INTERCOMM_mng_struct.addr_cfg.local_addr.sin_family = AF_INET;
	LOG_INTERCOMM_mng_struct.addr_cfg.local_addr.sin_addr.s_addr = inet_addr(LOG_INTERCOMM_mng_struct.addr_cfg.local_ip);
	LOG_INTERCOMM_mng_struct.addr_cfg.local_addr.sin_port = htons((int)(LOG_INTERCOMM_mng_struct.addr_cfg.local_port));

	/*维护机只有一个 I系 II系 一致*/
	GM_memcpy(LOG_INTERCOMM_mng_struct.addr_cfg.remote_ip, "192.168.2.240", strlen("192.168.2.240"));
	LOG_INTERCOMM_mng_struct.addr_cfg.remote_port = 30001U;
	LOG_INTERCOMM_mng_struct.addr_cfg.remote_addr.sin_family = AF_INET;
	LOG_INTERCOMM_mng_struct.addr_cfg.remote_addr.sin_addr.s_addr = inet_addr(LOG_INTERCOMM_mng_struct.addr_cfg.remote_ip);
	LOG_INTERCOMM_mng_struct.addr_cfg.remote_addr.sin_port = htons((int)(LOG_INTERCOMM_mng_struct.addr_cfg.remote_port));

	rt=INTERCOMM_Socket_Init(&LOG_INTERCOMM_mng_struct.sock, SOCK_DGRAM, 
		                     &LOG_INTERCOMM_mng_struct.addr_cfg.local_addr, 
		                    (1500U * 20U),
			                (1500U * 20U),
		                    &LOG_INTERCOMM_mng_struct.max_socket_value);

	
	return rt;
}
/*2 发送 获取组包数据，获取socket的状态writeable根据socket的设置发送。 */
/*******************************************************************************************
*函数功能：提供适配层周期性发送日志数据，最大发送长度15*1400.

*参数说明：无

*返回值： 1：发送成功
          0：发送失败
*******************************************************************************************/

GM_BOOL GM_LOG_INTERCOMM_SEND(UINT8*  m_Msg_Ptr, UINT32 m_Msg_Length)
{	
	
	GM_BOOL SendRt;
	
	
	/*没有数据不用发送*/
	if (m_Msg_Length == 0)
		{
		return GM_TRUE;
		}
	
	
		
	SendRt=	sendto(LOG_INTERCOMM_mng_struct.sock, (char*)m_Msg_Ptr, m_Msg_Length, 0,
						(struct sockaddr *)&(LOG_INTERCOMM_mng_struct.addr_cfg.remote_addr),
						sizeof(LOG_INTERCOMM_mng_struct.addr_cfg.remote_addr));
		

						
		
   
	return SendRt;
}
