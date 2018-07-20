#include "GM_RSSP1_CFM_Interface.h"
#include "../GM_RSSP1_MQ_Interface.h"
#include "../../INTERCOMM/GM_RSSP1_INTERCOMM.h"

extern RSSP1_MQ_LINK_struct g_Link_MQ[GM_RSSP1_MAX_SAFETY_CONNECTION_NUM];

/*���չ��� ��CFM����SFM*/
void GM_RSSP1_CFM_Interface_Proc_Recv(void)
{
	GM_RSSP1_CFM_object_struct *pCFM = NULL;
	pCFM = GM_RSSP1_Get_CFM_Object();

	if (NULL == pCFM)
	{
		return;
	}

	if (GM_RSSP1_Lib_State_Operational != pCFM->lib_state)
	{
		return;
	}
	
	
	GM_RSSP1_INTERCOMM_CPUB_From_IOB();

	GM_RSSP1_CFM_Proc_Recvd_Dat(pCFM);/*���ܣ���ͨ�Ų����ݷ�������㣬��Ҫ���*/
	GM_RSSP1_CFM_Report_com_State_To_SFM(pCFM);/*���ܣ���ͨ�Ų�״̬ͨ��������ϴ�����Ҫ���*/
}


/*���͹��� ��SFM����CFM*/
void GM_RSSP1_CFM_Interface_Proc_Send(void)
{
	GM_RSSP1_CFM_object_struct *pCFM = NULL;

	pCFM = GM_RSSP1_Get_CFM_Object();

	if (NULL == pCFM)
	{
		return;
	}

	if (GM_RSSP1_Lib_State_Operational != pCFM->lib_state)
	{
		return;
	}

	GM_RSSP1_CFM_Proc_SFM_Req(pCFM);
	
	GM_RSSP1_INTERCOMM_CPUB_To_IOB(pCFM);

}


void GM_RSSP1_CFM_Interface_Proc_Recv_For_Raw(void)
{
	GM_RSSP1_CFM_object_struct *pCFM = NULL;
	pCFM = GM_RSSP1_Get_CFM_Object();

	if (NULL == pCFM)
	{
		return;
	}

	if (GM_RSSP1_Lib_State_Operational != pCFM->lib_state)
	{
		return;
	}
	
	
	GM_RSSP1_INTERCOMM_CPUB_From_IOB();

}


void GM_RSSP1_CFM_Interface_Proc_Send_For_Raw(void)
{
	GM_RSSP1_CFM_object_struct *pCFM = NULL;

	pCFM = GM_RSSP1_Get_CFM_Object();

	if (NULL == pCFM)
	{
		return;
	}

	if (GM_RSSP1_Lib_State_Operational != pCFM->lib_state)
	{
		return;
	}
	
	GM_RSSP1_INTERCOMM_CPUB_To_IOB(pCFM);

}


GM_BOOL GM_RSSP1_Get_ConIndex(GM_UINT32 r_port, GM_UINT32 r_ip, GM_UINT8* con_index, GM_UINT8* red_index)
{
	GM_RSSP1_CFM_object_struct *pCFM = NULL;
	GM_RSSP1_CFM_connection_struct *pCFM_con = NULL;
	GM_UINT8 chn_index = 0;
	GM_UINT8 conn_index = 0;

	if ((con_index == NULL)||(red_index == NULL))
	{
		return GM_FALSE;
	}
	pCFM = GM_RSSP1_Get_CFM_Object();

	for (conn_index=0; conn_index<pCFM->connection_nums; ++conn_index)
	{
		pCFM_con = &(pCFM->connection[conn_index]);
		for (chn_index=0;chn_index<pCFM_con->chn_num;++chn_index)
		{
			if ((r_port == pCFM_con->com_chn[chn_index].rem_port)&&(r_ip == pCFM_con->com_chn[chn_index].rem_ip))
			{
				*con_index = conn_index;
				*red_index = chn_index;
				return GM_TRUE; 
			}
		}
	}
	return GM_FALSE;
}

GM_BOOL GM_RSSP1_Get_Address(GM_UINT32* r_port, GM_UINT32* r_ip, GM_UINT8 con_index, GM_UINT8 red_index)
{
	GM_RSSP1_CFM_object_struct *pCFM = NULL;
	GM_RSSP1_CFM_connection_struct *pCFM_con = NULL;

	if ((r_port == NULL)||(r_ip == NULL))
	{
	}

	pCFM = GM_RSSP1_Get_CFM_Object();
	if (con_index>=pCFM->connection_nums)
	{
		return GM_FALSE;
	}

	pCFM_con = &(pCFM->connection[con_index]);

	if (red_index>=pCFM_con->chn_num)
	{
		return GM_FALSE;
	}
	
	*r_port = pCFM_con->com_chn[red_index].rem_port;
	*r_ip = pCFM_con->com_chn[red_index].rem_ip;

	return GM_TRUE;
}

GM_BOOL GM_RSSP1_Write_SFM_Interface_ergodic(GM_UINT8* p_dat, GM_UINT16* len, GM_UINT32* r_port, GM_UINT32* r_ip, GM_UINT8* index)
{
	GM_RSSP1_com_pri_struct  temp_send_pkt= {0};
	GM_BOOL write_q_rt = GM_FALSE;
	GM_BOOL rt = GM_FALSE;
	GM_RSSP1_CFM_object_struct *pCFM = NULL;
	GM_RSSP1_CFM_connection_struct *pCFM_con = NULL;

	static GM_UINT8 i = 0;
	static GM_UINT8 j = 0;

	pCFM = GM_RSSP1_Get_CFM_Object();
	if (pCFM == NULL)
	{
		return GM_FALSE;
	}

	while (i<pCFM->connection_nums)
	{
		pCFM_con = &(pCFM->connection[i]);
		while(j<pCFM_con->chn_num)
		{
			j++;
			write_q_rt = FSFB_Msg_Queue_Get(&(g_Link_MQ[i].RCV_SND_MQ[j-1].SND_MQ),&temp_send_pkt);
			if (GM_TRUE == write_q_rt)
			{
				rt = GM_RSSP1_Get_Address(r_port, r_ip, i, j-1);
				if (rt == GM_TRUE)
				{
					GM_memcpy(p_dat, temp_send_pkt.byte, temp_send_pkt.bytes_count);
					*len = temp_send_pkt.bytes_count;
					*index = j-1;
					return GM_TRUE;
				}
			}
		}
		j = 0;
		i++;
	}
	
	i = 0;
	j = 0;
	
	return GM_FALSE;
}