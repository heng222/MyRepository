/********************************************************
*                                                                                                            
* �� �� ���� GM_LOG_INTERCOMM.c   
* ��    �ߣ�    ������
* ����ʱ�䣺 2018-05-15
* ���������� CSPƽ̨��־����
* ��    ע�� �� 
*
********************************************************/  

#include "GM_LOG_INTERCOMM.h"

INTERCOM_UDP_mng_struct LOG_INTERCOMM_mng_struct;

/*********************************�ڲ��������� BEGIN****************************************/

GM_BOOL GM_LOG_INTERCOMM_INIT();

/*******************************************END*********************************************/

/*******************************************************************************************
*�������ܣ���ʼ����־�ӿ� ����socket������socket������Iϵ IIϵ���ò�ͬ�ı���IP��PORT��Զ�˵�IP
		   �Ͷ˿�ͳһ��

*����˵������

*����ֵ��1 ����ʼ���ɹ�
		 0 ����ʼ��ʧ��
*******************************************************************************************/
GM_BOOL GM_LOG_INTERCOMM_INIT()
{
	GM_INT32 rt = GM_RSSP1_ERROR;
	
	UINT32 m_MachineID;
	/*sock ����Ϊ-1 ��֤û���ظ�����*/
	LOG_INTERCOMM_mng_struct.sock = GM_RSSP1_INVALID_SOCKET;
	LOG_INTERCOMM_mng_struct.max_socket_value = 30003U;
	/*Iϵ ʹ��192.168.2.1��30001  IIϵʹ��192.168.2.11��30002*/
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

	/*ά����ֻ��һ�� Iϵ IIϵ һ��*/
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
/*2 ���� ��ȡ������ݣ���ȡsocket��״̬writeable����socket�����÷��͡� */
/*******************************************************************************************
*�������ܣ��ṩ����������Է�����־���ݣ�����ͳ���15*1400.

*����˵������

*����ֵ�� 1�����ͳɹ�
          0������ʧ��
*******************************************************************************************/

GM_BOOL GM_LOG_INTERCOMM_SEND(UINT8*  m_Msg_Ptr, UINT32 m_Msg_Length)
{	
	
	GM_BOOL SendRt;
	
	
	/*û�����ݲ��÷���*/
	if (m_Msg_Length == 0)
		{
		return GM_TRUE;
		}
	
	
		
	SendRt=	sendto(LOG_INTERCOMM_mng_struct.sock, (char*)m_Msg_Ptr, m_Msg_Length, 0,
						(struct sockaddr *)&(LOG_INTERCOMM_mng_struct.addr_cfg.remote_addr),
						sizeof(LOG_INTERCOMM_mng_struct.addr_cfg.remote_addr));
		

						
		
   
	return SendRt;
}
