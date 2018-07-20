/**
* @file GM_CFG_INTERCOMM_Manage.c
* @brief ������ͨ�ſ�����ʹ�õ����ݽṹ�嶨�弰����
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
* @brief ��ȡTCPͨ����Ϣ
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
* @brief TCPͨ�ſ��ʼ�� 
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

	/** @brief ��ʼCFM��ʼ�� */
	pTCP->libraryState = Library_State_Unknown;
	
	F_VCP_GetSystemId(&l_MachineId);
	
	if(l_MachineId <= 0U)
	{
		
		return TCP_Initialize_Library_ERROR;		
	}


	
	/** @brief ��ʼ��CFG_INTERCOMM���� */
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
	
	
	/** @brief ��ʼ������������ */

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

	/** @brief ��ʼ���ɹ� */
	return TCP_Initialize_Library_OK;
}



/**
* @brief ����ͨ�Ŵ����׽��� 
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
		;/*�������ֵ������*/
	}

	return new_socket;
}
/**
* @brief ����ͨ�Źر��׽��� 
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
* @brief ����ͨ�������׽���ѡ�� 
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

	/* ������������ TODO:vxworks����Ҫ��������ļ���������Ŀ,Ĭ��Ϊ50.��ͨ��iosFdShow�鿴. */
	/* ���÷����� */

	if (GM_ERROR == ioctl(sock, FIONBIO, (int)&arg))
	{
		printf("Set_Socket_Option Error.....\n");
		return GM_ERROR;
	}


	return GM_OK;

}

/**
* @brief ����ͨ������ά�� 
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
* @brief ����ͨ�ŷ�����׽���ά�� 
*
* Detailed description.
* @return GM_BOOL
*
*/

void GM_CFG_INTERCOMM_Maintain_Server_Sockets(TCP_Object_struct *pTCP)
{
    GM_UINT8 socket_index = 0U; /* socket��ͨ���±� */
    int error_no          = 0;
    int rv                = 0;
    GM_BOOL mutex_rt      = GM_FALSE;

	struct sockaddr_in server_addr;

	/** @brief ���server socket��״̬, ��֤��������ʱ, �����쳣������������, ���߰γ�����ָ�����Է�������������
	** ����server�˽��ܵ�socket�쳣��, ͬʱ�ر��˱���server socket, �Ա�֤client�ܹ�������������, ������������ */

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
			/*������*/
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
			;/*������*/
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
			;/*������*/
		}

		/* �ɹ�����,bind, listen */
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
* @brief ����ͨ�ſͻ����׽���ά�� 
*
* Detailed description.
* @return GM_BOOL
*
*/

void GM_CFG_INTERCOMM_Maintain_Client_Sockets(TCP_Object_struct *pTCP)
{
    GM_UINT8 socket_index = 0U; /* socket��ͨ���±� */
    int error_no          = 0;
    int rv                = 0;
    GM_BOOL mutex_rt      = GM_FALSE;
    TCP_Connection_struct *pTCP_Con = NULL;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;	
	

	/** @brief ���server socket��״̬, ��֤��������ʱ, �����쳣������������, ���߰γ�����ָ�����Է�������������
	** ����server�˽��ܵ�socket�쳣��, ͬʱ�ر��˱���server socket, �Ա�֤client�ܹ�������������, ������������ */

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
			;/*������*/
		}

		pTCP_Con->socket = GM_CFG_INTERCOMM_Create_Socket(SOCK_STREAM, & (pTCP->max_socket_value));
		if (RSSP2_INVALID_SOCKET == pTCP_Con->socket)
		{
			continue;/* use of continue can not be avoided.*/
		}
		else
		{
			;/*������*/
		}

		if (GM_ERROR == GM_CFG_INTERCOMM_Set_Socket_Option(pTCP_Con->socket))
		{
			rv = GM_CFG_INTERCOMM_Close_Socket(&(pTCP_Con->socket));
			continue;/* use of continue can not be avoided.*/
		}
		else
		{
			;/*������*/
		}

		/* �ɹ�����,bind, listen */
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
* @brief ����ͨ���׽���accept���� 
*
* Detailed description.
* @return GM_BOOL
*
*/


void GM_CFG_INTERCOMM_TCP_Accept_Socket(TCP_Object_struct *pTCP)
{

    GM_UINT8 server_socket_index    = 0U;  /* server socket��ͨ���±� */
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

		/** @brief accept socket, set sock option�ɹ�, ������������, ƥ��accept��socket */
		if (accept_socket > pTCP->max_socket_value)
		{
			pTCP->max_socket_value = accept_socket;
		}
		
		
		/* �������õ�ͨ���гɹ�ƥ����ܵ�socket */
		if (GM_ERROR != GM_CFG_INTERCOMM_Set_Socket_Option(accept_socket))
		{
           printf("Server Set Accept Socket Opt OK\n");
		}
		else
		{
			rv = GM_CFG_INTERCOMM_Close_Socket(&(accept_socket));

			/* ����ʧ��,svr socket �������������������� */
			continue;
		}	
		

        pTCP_Con->TCP_State = Layer_State_Connected;		
        pTCP_Con->socket = accept_socket;	
        accept_socket = RSSP2_INVALID_SOCKET;	


	}/* ��������server socket */

	return;
}

/**
* @brief ����ͨ��IOͨ��������� 
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
* @brief ����ͨ���׽������ݽ��� 
*
* Detailed description.
* @return GM_BOOL
*
*/

GM_INT32 GM_CFG_INTERCOMM_TCP_Conn_Recv_Sock_Dat(TCP_Object_struct *pTCP)
{
    TCP_Connection_struct *pTCP_Con        = NULL;
    int rcv_len                            = 0; /* һ�ζ������ֽ��� */
    int rcv_buf_free_bytes                 = 0; /* ͨ��TCP���ջ������п����ڴ洢�����ݵ�ʣ��ռ� */
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


	   p_rcv_pkt_buf = &(pTCP_Con->rcv_buf);/*���ջ�����*/
	   
	   if(p_rcv_pkt_buf->p_rcv_buf == NULL)
	   {
		   continue;
	   }

	   if (Layer_State_Connected != pTCP_Con->TCP_State)
	  {
		/* ��������:ֻ����״̬Ϊconnected���������� */
		 continue;
	  }
	
	  if(GM_CFG_INTERCOMM_Is_Sock_Readable(pTCP_Con->socket) != GM_TRUE)
	  {
		 continue;		
	  }


	  rcv_buf_free_bytes = p_rcv_pkt_buf->buf_size - (p_rcv_pkt_buf->buf_head_pos + p_rcv_pkt_buf->valid_dat_len);
	  if ((rcv_buf_free_bytes <= 0))
	  {
		/* 1.���ջ������ռ䲻��,���ٴ�tcpЭ��ջ��������,��ֹ����
		* 2.���ȷǷ�,������ʱ���ջ��������
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

		/** @brief ���浽�������ݻ�����, �ȴ�ALEPKT����. */
		/** @brief ����buf��headpos��validlen.@note ����ԭ��:��buf���޷��洢�����½��յ�����ʱ, ֻ����bufʣ��ռ�Ĳ���, ����Ķ��� */
		rcv_buf_free_bytes = p_rcv_pkt_buf->buf_size - (p_rcv_pkt_buf->buf_head_pos + p_rcv_pkt_buf->valid_dat_len);



        if (rcv_len <= rcv_buf_free_bytes)
        {
            /** @brief ʣ��ռ��㹻, ֱ�ӱ��� */
            GM_memcpy((void *)(p_rcv_pkt_buf->p_rcv_buf + p_rcv_pkt_buf->buf_head_pos + p_rcv_pkt_buf->valid_dat_len), (const void *)l_Buf, (size_t)rcv_len);
            /** @brief ����valid_dat_len */
            p_rcv_pkt_buf->valid_dat_len += rcv_len;
        }
        else
        {
            /** @brief ʣ��ռ䲻��, ��ȡ����(�޸Ľ��ձ�����ƺ�,�˴���Ϊ����) */
            GM_memcpy((void *)(p_rcv_pkt_buf->p_rcv_buf), (const void *)l_Buf, (size_t)rcv_buf_free_bytes);
            /** @brief ����valid_dat_len */
            p_rcv_pkt_buf->valid_dat_len += rcv_buf_free_bytes;
        }

	  }
	}
	return GM_OK;
}

/**
* @brief ����ͨ���׽������ݷ��� 
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

	    p_send_pkt_buf = &(pTCP_Con->send_buf);/*���ջ�����*/	

        if(p_send_pkt_buf->valid_dat_len <= 0U)
		{
			continue;
		}			

		/*����״̬Ϊconnected��������*/
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
			/*�ж��Ƿ�ȫ�����ͣ�δ���͵��������Ƶ���ͷ�����ڷ���*/
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




