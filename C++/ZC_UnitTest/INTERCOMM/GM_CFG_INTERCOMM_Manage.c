/**
* @file GM_CFG_INTERCOMM_Manage.c
* @brief 内外网通信控制器使用的数据结构体定义及声明
* @author 
* @date 2017-10-17 14:56:35
* @version
* <pre><b>copyright: </b></pre>
* <pre><b>email: </b></pre>
* <pre><b>company: </b></pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>Write modifications here.</pre>
*/
#include "GM_CFG_INTERCOMM_TCP_Object.h"
#include "GM_CFG_INTERCOMM_Manage.h"
#include "GM_CFG_INTERCOMM.h"
#include "..\cspadpt\Vcp_Service_Interface.h"


TCP_Object_struct    g_CfgComm_Obj;

/**
* @brief 获取TCP通信信息
*
* Detailed description.
* @return GM_BOOL
*
*/

TCP_Object_struct*GM_CFG_INTERCOM_Get_TCPObject(void)
{
    
    return &g_CfgComm_Obj;
    
}

/**
* @brief TCP通信库初始化 
*
* Detailed description.
* @return GM_BOOL
*
*/

TCP_Initialize_Library_Result_Enum GM_CFG_INTERCOM_TCP_Initialize_Library(TCP_Object_struct *pTCP)
{
	GM_UINT32 i                                  = 0U;
	TCP_Connection_struct *pTCP_Con              = NULL;
	int rt                                       = 0;
	UINT32 l_MachineId = 0U;

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	if ((NULL == pTCP) )
	{
		return TCP_Initialize_Library_ERROR;
	}
	
    GM_memset((void *)pTCP, 0x00U, (size_t)(sizeof(TCP_Object_struct)));

	/** @brief 开始CFM初始化 */
	pTCP->libraryState = Library_State_Unknown;
	
	F_VCP_GetSystemId(&l_MachineId);
	
	if(l_MachineId <= 0U)
	{
		
		return TCP_Initialize_Library_ERROR;		
	}


	
	/** @brief 初始化CFG_INTERCOMM内容 */
#ifdef LINK_Part	
	pTCP->is_server =  GM_FALSE;   /*ETH BRD Is Client*/
#else
	pTCP->is_server =  GM_TRUE;   /*CPU BRD Is Server*/
#endif		

	pTCP->sock_check_counter = 0U;
	pTCP->connection_nums =  1U;   /*Connection Number*/	
	
    if(l_MachineId == 1U)
	{
	   GM_memcpy(pTCP->server_IP_port[0].ip_str,"192.168.2.1", strlen("192.168.2.1"));		
	}	
    else
	{
	   GM_memcpy(pTCP->server_IP_port[0].ip_str,"192.168.2.11", strlen("192.168.2.11"));		
	}		

	pTCP->server_IP_port[0].IP = inet_addr(pTCP->server_IP_port[0].ip_str);
	pTCP->server_IP_port[0].port = 7010U;	

	
    if(pTCP->is_server == GM_TRUE)	
	{
		GM_memcpy(pTCP->local_IP_port[0].ip_str,pTCP->server_IP_port[0].ip_str, strlen(pTCP->server_IP_port[0].ip_str));
		pTCP->local_IP_port[0].IP = inet_addr(pTCP->local_IP_port[0].ip_str);
		pTCP->local_IP_port[0].port = 7010U;				
		
	}
	else
	{
		
		if(l_MachineId == 1U)
		{
	        GM_memcpy(pTCP->local_IP_port[0].ip_str,"192.168.2.8", strlen("192.168.2.8"));			
		}
		else
		{
	        GM_memcpy(pTCP->local_IP_port[0].ip_str,"192.168.2.18", strlen("192.168.2.18"));				
		}		

		pTCP->local_IP_port[0].IP = inet_addr(pTCP->local_IP_port[0].ip_str);
		pTCP->local_IP_port[0].port = 7010U;			
	}
	
	
	/** @brief 初始化各冗余连接 */

	for (i = 0U; i < pTCP->connection_nums; ++i)
	{
		
        pTCP->server_socket[i] = RSSP2_INVALID_SOCKET;	
		
		pTCP_Con = (TCP_Connection_struct *)(&pTCP->connection[i]);
		pTCP_Con->index = i;
		
        if(pTCP->is_server == GM_TRUE)		
		  pTCP_Con->Role = Role_Server;
	    else
		  pTCP_Con->Role = Role_Client;			
	  
		pTCP_Con->TCP_State = Layer_State_Free;		
		pTCP_Con->socket = RSSP2_INVALID_SOCKET;
		

	  pTCP_Con->rcv_buf.p_rcv_buf = GM_malloc(1024U*100U);
	  pTCP_Con->rcv_buf.buf_size = 1024U*100U;	
	  pTCP_Con->rcv_buf.buf_head_pos = 0U;	
	  pTCP_Con->rcv_buf.valid_dat_len = 0U;			  
	  GM_memset(pTCP_Con->rcv_buf.p_rcv_buf, 0x00U, pTCP_Con->rcv_buf.buf_size);		

	  pTCP_Con->send_buf.p_rcv_buf = GM_malloc(1024U*100U);
	  pTCP_Con->send_buf.buf_size = 1024U*100U;	
	  pTCP_Con->send_buf.buf_head_pos = 0U;	
	  pTCP_Con->send_buf.valid_dat_len = 0U;			  
	  GM_memset(pTCP_Con->send_buf.p_rcv_buf, 0x00U, pTCP_Con->send_buf.buf_size);	
		  

	}  

 	 pTCP->libraryState = Library_State_Operational;

	/** @brief 初始化成功 */
	return TCP_Initialize_Library_OK;
}



/**
* @brief 内网通信创建套接字 
*
* Detailed description.
* @return GM_BOOL
*
*/

int GM_CFG_INTERCOMM_Create_Socket(int type, RSSP2_SOCKET *max_socket_value)
{	
	int new_socket = RSSP2_INVALID_SOCKET;
	if (NULL == max_socket_value)
	{
		return RSSP2_INVALID_SOCKET;
	}

	new_socket = socket(AF_INET, type, 0);

	if (new_socket < 0)
	{
		return RSSP2_INVALID_SOCKET;
	}

	if (*max_socket_value < (RSSP2_SOCKET)new_socket)
	{
		*max_socket_value = (RSSP2_SOCKET)new_socket;
	}
	else
	{
		;/*不是最大值不处理*/
	}

	return new_socket;
}
/**
* @brief 内网通信关闭套接字 
*
* Detailed description.
* @return GM_BOOL
*
*/

int GM_CFG_INTERCOMM_Close_Socket(RSSP2_SOCKET *sock)
{
	int rt = -1;

	if ((NULL == sock)||(RSSP2_INVALID_SOCKET == *sock))
	{
		return -1;
	}

	shutdown(*sock, 2);
	rt = close(*sock);
	*sock = RSSP2_INVALID_SOCKET;

	return rt;
}

/**
* @brief 内网通信设置套接字选项 
*
* Detailed description.
* @return GM_BOOL
*
*/

GM_INT32 GM_CFG_INTERCOMM_Set_Socket_Option(RSSP2_SOCKET sock)
{
	GM_UINT32 arg                   = 1U;

	if (RSSP2_INVALID_SOCKET == sock)
	{
		return GM_ERROR;
	}

	/* 公共属性设置 TODO:vxworks下需要设置最大文件描述符数目,默认为50.可通过iosFdShow查看. */
	/* 设置非阻塞 */

	if (GM_ERROR == ioctl(sock, FIONBIO, (int)&arg))
	{
		printf("Set_Socket_Option Error.....\n");
		return GM_ERROR;
	}


	return GM_OK;

}

/**
* @brief 内网通信连接维护 
*
* Detailed description.
* @return GM_BOOL
*
*/

GM_BOOL GM_CFG_INTERCOMM_TCP_Socket_Maintain(TCP_Object_struct *pTCP)
{
	
	if(pTCP == NULL)
		return GM_FALSE;

    if(pTCP->is_server == GM_TRUE)
	{
	   GM_CFG_INTERCOMM_TCP_Accept_Socket(pTCP);
	   GM_CFG_INTERCOMM_Maintain_Server_Sockets(pTCP);		
		
	}
	else
	{
		
	   GM_CFG_INTERCOMM_Maintain_Client_Sockets(pTCP);		
		
	}

	return GM_TRUE;
}

/**
* @brief 内网通信服务端套接字维护 
*
* Detailed description.
* @return GM_BOOL
*
*/

void GM_CFG_INTERCOMM_Maintain_Server_Sockets(TCP_Object_struct *pTCP)
{
    GM_UINT8 socket_index = 0U; /* socket子通道下标 */
    int error_no          = 0;
    int rv                = 0;
    GM_BOOL mutex_rt      = GM_FALSE;

	struct sockaddr_in server_addr;

	/** @brief 检测server socket的状态, 保证开机启动时, 网卡异常（如网卡禁用, 网线拔出）后恢复后可以服务器正常工作
	** 或者server端接受的socket异常后, 同时关闭了本地server socket, 以保证client能够正常重新连接, 而不是虚连接 */

    if ((NULL == pTCP)||(GM_TRUE != pTCP->is_server))
    {
        return;
    }


	for (socket_index = 0U; socket_index < pTCP->connection_nums; ++socket_index)
	{
		if (RSSP2_INVALID_SOCKET != pTCP->server_socket[socket_index])
		{
			continue;/* use of continue can not be avoided.*/
		}
		else
		{
			/*不处理*/
		}

		pTCP->server_socket[socket_index] = GM_CFG_INTERCOMM_Create_Socket(SOCK_STREAM, & (pTCP->max_socket_value));
		if (RSSP2_INVALID_SOCKET == pTCP->server_socket[socket_index])
		{
			printf("create server socket error=%d\n",errno);
			continue;/* use of continue can not be avoided.*/
		}
		else
		{
			printf("create server socket ok\n");			
			;/*不处理*/
		}

		if (GM_ERROR == GM_CFG_INTERCOMM_Set_Socket_Option(pTCP->server_socket[socket_index]))
		{
			rv = GM_CFG_INTERCOMM_Close_Socket(&(pTCP->server_socket[socket_index]));
			printf("set server socket opt error\n");			
			continue;/* use of continue can not be avoided.*/
		}
		else
		{
			printf("set server socket opt ok\n");					
			;/*不处理*/
		}

		/* 成功创建,bind, listen */
		server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = /*htonl(INADDR_ANY)*/ pTCP->server_IP_port[socket_index].IP;
        server_addr.sin_port = htons((int)(pTCP->server_IP_port[socket_index].port));

		if (RSSP2_SOCKET_ERROR == bind(pTCP->server_socket[socket_index], (struct sockaddr *)(&server_addr), sizeof(server_addr)))
		{
			rv = GM_CFG_INTERCOMM_Close_Socket(&(pTCP->server_socket[socket_index]));
			printf("bind server socket error = %d\n",errno);				
			continue;
		}
		else
		{
		}

		if (RSSP2_SOCKET_ERROR == listen(pTCP->server_socket[socket_index], pTCP->connection_nums * 4U))
		{
			rv = GM_CFG_INTERCOMM_Close_Socket(&(pTCP->server_socket[socket_index]));
			printf("listen server socket error = %d\n",errno);				
			continue;
		}
		else
		{
			printf("server socket channel:%d re-listen OK.\n", socket_index);
		}
	}


	return;
}

/**
* @brief 内网通信客户端套接字维护 
*
* Detailed description.
* @return GM_BOOL
*
*/

void GM_CFG_INTERCOMM_Maintain_Client_Sockets(TCP_Object_struct *pTCP)
{
    GM_UINT8 socket_index = 0U; /* socket子通道下标 */
    int error_no          = 0;
    int rv                = 0;
    GM_BOOL mutex_rt      = GM_FALSE;
    TCP_Connection_struct *pTCP_Con = NULL;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;	
	

	/** @brief 检测server socket的状态, 保证开机启动时, 网卡异常（如网卡禁用, 网线拔出）后恢复后可以服务器正常工作
	** 或者server端接受的socket异常后, 同时关闭了本地server socket, 以保证client能够正常重新连接, 而不是虚连接 */

    if ((NULL == pTCP)||(GM_FALSE != pTCP->is_server) )
    {
        return;
    }


	for (socket_index = 0U; socket_index < pTCP->connection_nums; ++socket_index)
	{
		
		pTCP_Con = (TCP_Connection_struct *)(&pTCP->connection[socket_index]);		
		if (RSSP2_INVALID_SOCKET != pTCP_Con->socket)
		{
			continue;/* use of continue can not be avoided.*/
		}
		else
		{
			;/*不处理*/
		}

		pTCP_Con->socket = GM_CFG_INTERCOMM_Create_Socket(SOCK_STREAM, & (pTCP->max_socket_value));
		if (RSSP2_INVALID_SOCKET == pTCP_Con->socket)
		{
			continue;/* use of continue can not be avoided.*/
		}
		else
		{
			;/*不处理*/
		}

		if (GM_ERROR == GM_CFG_INTERCOMM_Set_Socket_Option(pTCP_Con->socket))
		{
			rv = GM_CFG_INTERCOMM_Close_Socket(&(pTCP_Con->socket));
			continue;/* use of continue can not be avoided.*/
		}
		else
		{
			;/*不处理*/
		}

		/* 成功创建,bind, listen */
		server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = /*htonl(INADDR_ANY)*/ pTCP->server_IP_port[socket_index].IP;
        server_addr.sin_port = htons((int)(pTCP->server_IP_port[socket_index].port));
        
        
        client_addr.sin_family = AF_INET;
        client_addr.sin_addr.s_addr = pTCP->local_IP_port[socket_index].IP;
        client_addr.sin_port = htons((int)(pTCP->local_IP_port[socket_index].port));        

		if (RSSP2_SOCKET_ERROR == bind(pTCP_Con->socket, (struct sockaddr *)(&client_addr), sizeof(client_addr)))
		{
			rv = GM_CFG_INTERCOMM_Close_Socket(&(pTCP_Con->socket));
			continue;
		}
		else
		{
		}
		
		
		if (RSSP2_SOCKET_OK != connect(pTCP_Con->socket, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr_in)))
	    {
            GM_CFG_INTERCOMM_Close_Socket(&(pTCP_Con->socket));					
            continue;
	    }
	    else
	    {
            printf("client channel:%d re-connect at port:%d success.\n", socket_index, pTCP->server_IP_port[socket_index].port);										
		}	

        pTCP_Con->TCP_State = Layer_State_Connected;			
		
	}


	return;
}



/**
* @brief 内网通信套接字accept操作 
*
* Detailed description.
* @return GM_BOOL
*
*/


void GM_CFG_INTERCOMM_TCP_Accept_Socket(TCP_Object_struct *pTCP)
{

    GM_UINT8 server_socket_index    = 0U;  /* server socket子通道下标 */
    RSSP2_SOCKET accept_socket      = RSSP2_INVALID_SOCKET;
    Transport_Config_struct acpt_addr;
	struct sockaddr_in client_addr;
	int client_addr_len             = sizeof(client_addr);
	TCP_Connection_struct *pTCP_Con = NULL;
	int rv                          = 0;

    if ((NULL == pTCP)||(GM_FALSE == pTCP->is_server) )
    {
        return;
    }

	for (server_socket_index = 0U; server_socket_index < pTCP->connection_nums; ++server_socket_index)
	{
        pTCP_Con = (TCP_Connection_struct *)(&pTCP->connection[server_socket_index]);	
		if (RSSP2_INVALID_SOCKET == pTCP->server_socket[server_socket_index])
		{
			continue;
		}
		
		if(RSSP2_INVALID_SOCKET != pTCP_Con->socket)
		{
			continue;
		}

		accept_socket = accept(pTCP->server_socket[server_socket_index], (struct sockaddr *)(&client_addr), &client_addr_len);
		if (0 > accept_socket)
		{
/*			printf("accept error, socket=%d, errno=%d", pTCP->server_socket[server_socket_index], errno);*/
			continue;
		}
		else
		{

			printf("SERVER chn:%d acpt new sock:%d.\n",server_socket_index, accept_socket);
		}

		/** @brief accept socket, set sock option成功, 遍历冗余连接, 匹配accept的socket */
		if (accept_socket > pTCP->max_socket_value)
		{
			pTCP->max_socket_value = accept_socket;
		}
		
		
		/* 在已配置的通道中成功匹配接受的socket */
		if (GM_ERROR != GM_CFG_INTERCOMM_Set_Socket_Option(accept_socket))
		{
           printf("Server Set Accept Socket Opt OK\n");
		}
		else
		{
			rv = GM_CFG_INTERCOMM_Close_Socket(&(accept_socket));

			/* 设置失败,svr socket 继续接受其他连接请求 */
			continue;
		}	
		

        pTCP_Con->TCP_State = Layer_State_Connected;		
        pTCP_Con->socket = accept_socket;	
        accept_socket = RSSP2_INVALID_SOCKET;	


	}/* 遍历各个server socket */

	return;
}

/**
* @brief 内网通信IO通道管理操作 
*
* Detailed description.
* @return GM_BOOL
*
*/

GM_BOOL GM_CFG_INTERCOMM_Is_Sock_Readable(RSSP2_SOCKET sock)
{

	int ret = -1;
	
    UINT32 l_len = 0U;    
    ret = ioctl(sock,FIONREAD,(int)(&l_len));    
    
    
    if (0U >= l_len)
    {
        return GM_FALSE;
    }
    else
    {
		
		return GM_TRUE;
		
    }	
	
}

/**
* @brief 内网通信套接字数据接收 
*
* Detailed description.
* @return GM_BOOL
*
*/

GM_INT32 GM_CFG_INTERCOMM_TCP_Conn_Recv_Sock_Dat(TCP_Object_struct *pTCP)
{
    TCP_Connection_struct *pTCP_Con        = NULL;
    int rcv_len                            = 0; /* 一次读到的字节数 */
    int rcv_buf_free_bytes                 = 0; /* 通道TCP接收缓冲区中可用于存储新数据的剩余空间 */
    int error_no                           = 0;
    GM_BOOL mutex_rt                       = GM_FALSE;
    TCP_Rcv_PKT_Buf_struct *p_rcv_pkt_buf  = NULL;
    UINT32 l_Index = 0U;
    UINT8 l_Buf[1024U*10U] = { 0U };

	if (NULL == pTCP)
	{
		return GM_ERROR;
	}

	if (pTCP->libraryState != Library_State_Operational)
	{
		return GM_ERROR;
	}

	for (l_Index = 0U; l_Index < pTCP->connection_nums; ++l_Index)
	{	

       GM_memset((void *)l_Buf, 0x00U, (size_t)(sizeof(l_Buf)));
       
       pTCP_Con = (TCP_Connection_struct *)(&pTCP->connection[l_Index]);


	   p_rcv_pkt_buf = &(pTCP_Con->rcv_buf);/*接收缓冲区*/
	   
	   if(p_rcv_pkt_buf->p_rcv_buf == NULL)
	   {
		   continue;
	   }

	   if (Layer_State_Connected != pTCP_Con->TCP_State)
	  {
		/* 接收数据:只负责状态为connected的冗余连接 */
		 continue;
	  }
	
	  if(GM_CFG_INTERCOMM_Is_Sock_Readable(pTCP_Con->socket) != GM_TRUE)
	  {
		 continue;		
	  }


	  rcv_buf_free_bytes = p_rcv_pkt_buf->buf_size - (p_rcv_pkt_buf->buf_head_pos + p_rcv_pkt_buf->valid_dat_len);
	  if ((rcv_buf_free_bytes <= 0))
	  {
		/* 1.接收缓冲区空间不足,不再从tcp协议栈读出数据,防止丢包
		* 2.长度非法,超出临时接收缓冲的容量
		*/
		 continue;
	  }


	  rcv_len = recv(pTCP_Con->socket, (char *)l_Buf, rcv_buf_free_bytes , 0);

	  printf("***********************rcv_len = %d\n",rcv_len);

	  if (0 >= rcv_len)
	  {
        GM_CFG_INTERCOMM_Close_Socket(pTCP_Con->socket);
		pTCP_Con->TCP_State = Layer_State_Free;
		
		printf("@@@@ sock %d rcv err.ret %d.errno:%d.\n",pTCP_Con->socket,rcv_len,errno);		
		return GM_ERROR;		
	  }
	  else
	  {     

		/** @brief 保存到接收数据缓冲中, 等待ALEPKT处理. */
		/** @brief 更新buf的headpos和validlen.@note 覆盖原则:当buf中无法存储所有新接收的数据时, 只接收buf剩余空间的部分, 其余的丢弃 */
		rcv_buf_free_bytes = p_rcv_pkt_buf->buf_size - (p_rcv_pkt_buf->buf_head_pos + p_rcv_pkt_buf->valid_dat_len);



        if (rcv_len <= rcv_buf_free_bytes)
        {
            /** @brief 剩余空间足够, 直接保存 */
            GM_memcpy((void *)(p_rcv_pkt_buf->p_rcv_buf + p_rcv_pkt_buf->buf_head_pos + p_rcv_pkt_buf->valid_dat_len), (const void *)l_Buf, (size_t)rcv_len);
            /** @brief 更新valid_dat_len */
            p_rcv_pkt_buf->valid_dat_len += rcv_len;
        }
        else
        {
            /** @brief 剩余空间不足, 截取保存(修改接收保存机制后,此处作为冗余) */
            GM_memcpy((void *)(p_rcv_pkt_buf->p_rcv_buf), (const void *)l_Buf, (size_t)rcv_buf_free_bytes);
            /** @brief 更新valid_dat_len */
            p_rcv_pkt_buf->valid_dat_len += rcv_buf_free_bytes;
        }

	  }
	}
	return GM_OK;
}

/**
* @brief 内网通信套接字数据发送 
*
* Detailed description.
* @return GM_BOOL
*
*/

GM_INT32 GM_CFG_INTERCOMM_TCP_Conn_Send_Sock_Dat(TCP_Object_struct *pTCP)
{
	TCP_Connection_struct *pTCP_Con        = NULL;
	GM_BOOL rt                             = GM_FALSE;
	int rv                                 = -1;
	UINT32 l_Index = 0U;
	UINT32 l_ToSendLen = 0U;	
	INT32 l_SentLen = 0;
	UINT32 l_MaxSendLen = 5120U;		
	TCP_Rcv_PKT_Buf_struct *p_send_pkt_buf  = NULL;	
	
	if (NULL == pTCP)
	{
		return GM_ERROR;
	}

	for (l_Index = 0U; l_Index < pTCP->connection_nums; ++l_Index)
	{	


	    pTCP_Con = (TCP_Connection_struct *)(&pTCP->connection[l_Index]);

	    p_send_pkt_buf = &(pTCP_Con->send_buf);/*接收缓冲区*/	

        if(p_send_pkt_buf->valid_dat_len <= 0U)
		{
			continue;
		}			

		/*负责状态为connected发送数据*/
		if (Layer_State_Connected != pTCP_Con->TCP_State)
		{
			continue;
		}
		

		
		l_ToSendLen =  p_send_pkt_buf->valid_dat_len;
		
		printf("Server is to send len=%d\n", l_ToSendLen);
		
		if(l_ToSendLen > l_MaxSendLen)
		{
			l_ToSendLen = l_MaxSendLen;			
		}
	    l_SentLen = send(pTCP_Con->socket, p_send_pkt_buf->p_rcv_buf, l_ToSendLen, MSG_FSC_IF);
		
		if(l_SentLen <= 0)
		{
			printf("GM_CFG_INTERCOMM_TCP_Conn_Send_Sock_Dat error=%d", errno);
			continue;			
		}
		else
		{
			/*判断是否全部发送，未发送的数据左移到包头下周期发送*/
			if(p_send_pkt_buf->valid_dat_len == l_SentLen)
			{
				/* all dat snd ok */
				p_send_pkt_buf->valid_dat_len = 0U;
			}
			else
			{
				/* mov left dat to head */
				GM_memcpy(p_send_pkt_buf->p_rcv_buf,
						  p_send_pkt_buf->p_rcv_buf + l_SentLen,
						  p_send_pkt_buf->valid_dat_len - l_SentLen);
				p_send_pkt_buf->valid_dat_len -= l_SentLen;
			}

            printf("Sent Len = %d", l_SentLen);			
									
		}

		
	}

	return GM_OK;
}




