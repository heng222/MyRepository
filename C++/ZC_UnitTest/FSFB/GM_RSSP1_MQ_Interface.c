#include "GM_RSSP1_MQ_Interface.h"

extern GM_UINT32 g_valid_chn;
RSSP1_MQ_LINK_struct g_Link_MQ[GM_RSSP1_MAX_SAFETY_CONNECTION_NUM] = {0};

RSSP1_MQ_Inter_struct g_CFM_MQ = {0};

RSSP1_MQ_Inter_struct g_SFM_MQ = {0};

GM_BOOL GM_RSSP1_SND_com_Interface(GM_UINT8* p_dat, GM_UINT16* len, GM_UINT8 index, GM_UINT8 chn_index)
{
	GM_RSSP1_com_pri_struct  temp_send_pkt= {0};
	GM_BOOL write_q_rt = Q_WRITE_FAIL;

	if ((p_dat == NULL)||(len == NULL)||(index>=GM_RSSP1_MAX_SAFETY_CONNECTION_NUM)||(chn_index>=GM_RSSP1_MAX_LINK_CHANNEL))
	{
		return GM_FALSE;
	}
	write_q_rt = FSFB_Msg_Queue_Get(&(g_Link_MQ[index].RCV_SND_MQ[chn_index].SND_MQ),&temp_send_pkt);
	if (GM_TRUE == write_q_rt)
	{
		GM_memcpy(p_dat, temp_send_pkt.byte, temp_send_pkt.bytes_count);
		*len = temp_send_pkt.bytes_count;
		return GM_TRUE;
	}
	else
	{
		return GM_FALSE;
	}
}

GM_BOOL GM_RSSP1_RCV_com_Interface(GM_UINT8* p_dat, GM_INT16 recv_len, GM_UINT8 index, GM_UINT8 chn_index)
{
	GM_RSSP1_Write_Q_Return_Enum write_q_rt = Q_WRITE_FAIL;
	GM_RSSP1_com_pri_struct pri;

	if ((recv_len > GM_RSSP1_MAX_USER_DAT_LEN)||(p_dat ==NULL)||(index>=GM_RSSP1_MAX_SAFETY_CONNECTION_NUM)||(chn_index>=GM_RSSP1_MAX_LINK_CHANNEL))
	{
		return GM_FALSE;
	}

	pri.bytes_count = recv_len;
	GM_memcpy(pri.byte , p_dat , recv_len);

	write_q_rt = FSFB_Msg_Queue_Write(&(g_Link_MQ[index].RCV_SND_MQ[chn_index].RCV_MQ), &pri);
	if (Q_WRITE_FAIL == write_q_rt)
	{
		return GM_FALSE;
	}
	else
	{
		return GM_TRUE;
	}
}


GM_BOOL GM_RSSP1_MessageQueue_Inter_Set(GM_RSSP1_MQ_Type_Enum type, GM_UINT8* pMsg)
{
	GM_RSSP1_Write_Q_Return_Enum write_q_rt = Q_WRITE_FAIL;

	if (pMsg == NULL)
	{
		return GM_FALSE;
	}
	switch(type)
	{
		case RSSP1_S2C_SND:
			write_q_rt = FSFB_Msg_Queue_Write(&(g_CFM_MQ.SND_MQ) , pMsg);
			if (Q_WRITE_FAIL == write_q_rt)
			{
				return GM_FALSE;
			}
			break;

		case RSSP1_C2S_RCV:
			write_q_rt = FSFB_Msg_Queue_Write(&(g_CFM_MQ.RCV_MQ) , pMsg);
			if (Q_WRITE_FAIL == write_q_rt)
			{
				return GM_FALSE;
			}
			break;
		default:
			return GM_FALSE;
	}
	return GM_TRUE;
}


GM_BOOL GM_RSSP1_MessageQueue_Inter_Get(GM_RSSP1_MQ_Type_Enum type, GM_UINT8* pMsg, GM_UINT32* len)
{
	GM_BOOL write_q_rt = GM_FALSE;
	GM_RSSP1_CFM_U2L_pri_struct S2C_Msg = {0};
	GM_RSSP1_CFM_L2U_pri_struct C2S_Msg = {0};
	GM_UINT32 count = 0;
	GM_UINT32 lenth = 0;

	if ((pMsg == NULL)||(len == NULL))
	{
		return GM_FALSE;
	}

	lenth = sizeof(GM_RSSP1_CFM_L2U_type_enum)+sizeof(GM_UINT8);

	switch(type)
	{
		case RSSP1_S2C_SND:
			write_q_rt = FSFB_Msg_Queue_Get(&(g_CFM_MQ.SND_MQ) , &S2C_Msg);
			if (GM_FALSE == write_q_rt)
			{
				return GM_FALSE;
			}
			lenth = sizeof(GM_RSSP1_CFM_U2L_pri_struct)-GM_RSSP1_MAX_SAFETY_DAT_LEN+S2C_Msg.as.data_req.bytes_count;
			GM_memcpy(pMsg, &S2C_Msg, lenth);
			*len = lenth;
			write_q_rt = GM_TRUE;
			break;

		case RSSP1_C2S_RCV:
			write_q_rt = FSFB_Msg_Queue_Get(&(g_CFM_MQ.RCV_MQ) , &C2S_Msg);
			if (GM_FALSE == write_q_rt)
			{
				return GM_FALSE;
			}
			switch(C2S_Msg.type)
			{
				case GM_RSSP1_CFM_Data_Ind:
					lenth += sizeof(GM_RSSP1_CFM_L2U_Dat_pri_struct)-GM_RSSP1_MAX_SAFETY_DAT_LEN+C2S_Msg.as.data_indi.bytes_count;
					GM_memcpy(pMsg, &C2S_Msg, lenth);
					*len = lenth;
					write_q_rt = GM_TRUE;
					break;

				case GM_RSSP1_CFM_Indi_com_State:
					lenth += sizeof(GM_RSSP1_CFM_L2U_State_Noti_struct)/GM_RSSP1_MAX_SAFETY_CONNECTION_NUM*g_valid_chn;
					GM_memcpy(pMsg, &C2S_Msg, lenth);
					*len = lenth;
					write_q_rt = GM_TRUE;
					break;

				case GM_RSSP1_CFM_Indi_Error_Noti:
					lenth += sizeof(GM_RSSP1_CFM_L2U_Error_Noti_struct);
					*len = lenth;
					GM_memcpy(pMsg, &C2S_Msg, lenth);
					write_q_rt = GM_TRUE;
					break;

				default:
					write_q_rt = GM_FALSE;
					break;
			}
			break;
		default:
			write_q_rt = GM_FALSE;
			break;
	}
	return write_q_rt;
}