#include "GM_RSSP1_APP_Interface.h"
#include "GM_RSSP1_Syn.h"
#include "..\INTERCOMM\GM_RSSP1_INTERCOMM_Def.h"
#include "..\INTERCOMM\GM_RSSP1_INTERCOMM_Init.h"


GM_RSSP_GET_ABAS_FUN GM_RSSP_Resource_Get_ABAS = NULL;

GM_BOOL RSSP1_Initialized = GM_FALSE;

GM_UINT32 g_valid_chn = 0;

extern RSSP1_MQ_Inter_struct g_SFM_MQ;

extern RSSP1_MQ_Inter_struct g_CFM_MQ;

extern RSSP1_MQ_LINK_struct g_Link_MQ[GM_RSSP1_MAX_SAFETY_CONNECTION_NUM];

/*****************FSFB_Interface_Init**************************************
用途:CBI与TCC接口，初始化
参数:无
返回值: 无
************************************************************************/

#if 0
GM_BOOL GM_RSSP1_APP_Interface_Init_Addr(GM_RSSP_GET_ABAS_FUN fun, GM_UINT8* SFM_Addr, GM_UINT8* CFM_Addr, GM_UINT8* Addr)
{
#ifdef SFM_Part
	if (GM_FALSE == GM_RSSP1_SFM_Init_Addr(SFM_Addr))
	{
		GM_Log_Msg(0,"FSFB SFM init FAIL!\n", 0, 0, 0, 0, 0, 0);
		return GM_FALSE;
	}
	else
	{
		GM_Log_Msg(0,"FSFB SFM init OK.\n", 0, 0, 0, 0, 0, 0);
	}
#endif

#ifdef CFM_Part
	if (GM_FALSE == GM_RSSP1_CFM_Init_Addr(CFM_Addr))
	{
		GM_Log_Msg(0,"FSFB CFM init FAIL!\n", 0, 0, 0, 0, 0, 0);
		return GM_FALSE;
	}
	else
	{
		GM_Log_Msg(0,"FSFB CFM init OK.\n", 0, 0, 0, 0, 0, 0);
	}
#endif

#ifdef LINK_Part
	if (GM_FALSE == FSFB_LNK_Init(Addr))
	{
		GM_Log_Msg(0,"FSFB LNK init FAIL!\n", 0, 0, 0, 0, 0, 0);
		return GM_FALSE;
	}
	else
	{
		GM_Log_Msg(0,"FSFB LNK init OK.\n", 0, 0, 0, 0, 0, 0);
	}
#endif

	GM_RSSP_Resource_Get_ABAS = (GM_RSSP_GET_ABAS_FUN)fun;

	RSSP1_Initialized = GM_TRUE;

	return GM_TRUE;
}
#endif

#if 0
GM_BOOL GM_RSSP1_APP_Interface_Init(GM_RSSP_GET_ABAS_FUN fun, char* path)
{
#ifdef SFM_Part
	if (GM_FALSE == GM_RSSP1_SFM_Init(path))
	{
		GM_Log_Msg(0,"FSFB SFM init FAIL!\n", 0, 0, 0, 0, 0, 0);
		return GM_FALSE;
	}
	else
	{
		GM_Log_Msg(0,"FSFB SFM init OK.\n", 0, 0, 0, 0, 0, 0);
	}
#endif

#ifdef CFM_Part

	if (GM_FALSE == GM_RSSP1_CFM_Init(path))
	{
		GM_Log_Msg(0,"FSFB CFM init FAIL!\n", 0, 0, 0, 0, 0, 0);
		return GM_FALSE;
	}
	else
	{
		GM_Log_Msg(0,"FSFB CFM init OK.\n", 0, 0, 0, 0, 0, 0);
	}
#endif

#ifdef LINK_Part
	if (GM_FALSE == FSFB_LNK_Init(path))
	{
		GM_Log_Msg(0,"FSFB LNK init FAIL!\n", 0, 0, 0, 0, 0, 0);
		return GM_FALSE;
	}
	else
	{
		GM_Log_Msg(0,"FSFB LNK init OK.\n", 0, 0, 0, 0, 0, 0);
	}
#endif

	GM_RSSP_Resource_Get_ABAS = (GM_RSSP_GET_ABAS_FUN)fun;

	RSSP1_Initialized = GM_TRUE;

	return GM_TRUE;
}
#endif

GM_BOOL GM_RSSP1_APP_Interface_Init_CSP(GM_RSSP_GET_ABAS_FUN fun, char* pcfg, GM_UINT32 len)
{



#ifdef SFM_Part
	if (GM_FALSE == GM_RSSP1_SFM_Init_CSP(pcfg, len))
	{
		printf("FSFB SFM init FAIL!\n");
		return GM_FALSE;
	}
	else
	{
		printf("FSFB SFM init OK.\n");
	}
#endif

#ifdef CFM_Part
	if (GM_FALSE == GM_RSSP1_CFM_Init_CSP(pcfg, len))
	{
		printf("FSFB CFM init FAIL!\n");
		return GM_FALSE;
	}
	else
	{
		printf("FSFB CFM init OK.\n");
	}
	
	if (GM_FALSE == GM_RSSP1_INTERCOMM_Init(GM_INTERCOMM_Get_Rssp1_Intercomm_Cfg(), GM_RSSP1_INTERCOMM_Type_CPUB))
	{
	    printf("GM_RSSP1_INTERCOMM_Init: fail.!\n");			
	}	
	else
	{
		printf("GM_RSSP1_INTERCOMM_Init OK.\n");		
	}
		
	
	
#endif

#ifdef LINK_Part
	if (GM_FALSE == FSFB_LNK_Init_CSP(pcfg, len))
	{
		GM_Log_Msg(0,"FSFB LNK init FAIL!\n", 0, 0, 0, 0, 0, 0);
		return GM_FALSE;
	}
	else
	{
		GM_Log_Msg(0,"FSFB LNK init OK.\n", 0, 0, 0, 0, 0, 0);
	}
#endif

	GM_RSSP_Resource_Get_ABAS = (GM_RSSP_GET_ABAS_FUN)fun;

	RSSP1_Initialized = GM_TRUE;

	return GM_TRUE;
}


GM_BOOL GM_RSSP1_APP_Interface_Get_Syn_AB_AS_Info(Local_Sys_AB_enum *p_sys_a_b , GM_BOOL *p_bactive)
{
    GM_UINT16 t_usIPS_ROLE = 0;
	t_usIPS_ROLE = GM_RSSP_Resource_Get_ABAS();

    if ((ABAS_Type_A_AS == t_usIPS_ROLE) || (ABAS_Type_A_AA == t_usIPS_ROLE) ||
            (ABAS_Type_B_AS == t_usIPS_ROLE) || (ABAS_Type_B_AA == t_usIPS_ROLE))
    {

        if ((ABAS_Type_A_AS == t_usIPS_ROLE) || (ABAS_Type_A_AA == t_usIPS_ROLE))
        {
            *p_sys_a_b = GM_RSSP1_Local_Sys_A;
        }
        else
        {
            *p_sys_a_b = GM_RSSP1_Local_Sys_B;
        }

        *p_bactive = GM_TRUE;
    }
    else if ((ABAS_Type_A_SA == t_usIPS_ROLE) || (ABAS_Type_A_SS == t_usIPS_ROLE) ||
             (ABAS_Type_B_SA == t_usIPS_ROLE) || (ABAS_Type_B_SS == t_usIPS_ROLE))
    {
        if ((ABAS_Type_A_SA == t_usIPS_ROLE) || (ABAS_Type_A_SS == t_usIPS_ROLE))
        {
            *p_sys_a_b = GM_RSSP1_Local_Sys_A;
        }
        else
        {
            *p_sys_a_b = GM_RSSP1_Local_Sys_B;
        }

        *p_bactive = GM_FALSE;
    }
    else
    {
        return GM_FALSE;
    }

    return GM_TRUE;
}

GM_BOOL GM_RSSP1_APP_Interface_Is_Local_ACTIVE(void)
{
    Local_Sys_AB_enum sys_a_b;
    GM_BOOL b_active = GM_FALSE;

    if (GM_TRUE == GM_RSSP1_APP_Interface_Get_Syn_AB_AS_Info(&sys_a_b , &b_active))
    {
        return b_active;
    }
    else
    {
        /* 异常，视为备机 */
        return GM_FALSE;
    }

}


GM_BOOL GM_RSSP1_Send_App_Dat(GM_UINT8 *pDat , GM_UINT32 dat_len)
{
    GM_RSSP1_SACEPID_struct dest_sacepid;
    Local_Sys_AB_enum sys_a_b = GM_RSSP1_Local_Sys_A;
    GM_BOOL b_active = GM_TRUE;
    GM_BOOL rt = GM_FALSE;
	GM_UINT16 crc16        = 0;
	GM_UINT16 crc16_in     = 0;

    if ((NULL == pDat) || (dat_len>(GM_RSSP1_MAX_USER_DAT_LEN-22)))
    {
        return GM_FALSE;
    }

	dest_sacepid.source_addr    = (*(pDat) << 8) + (*(pDat + 1));
	dest_sacepid.dest_addr      = (*(pDat + 2) << 8) + (*(pDat + 3));
	
	if (GM_TRUE == GM_RSSP1_APP_Interface_Get_Syn_AB_AS_Info(&sys_a_b , &b_active))
	{
		rt = GM_RSSP1_User_Send_Dat(&(dest_sacepid) , (pDat+4), (dat_len-4), sys_a_b, b_active, GM_RSSP1_Get_SFM_Object());
		return rt;
	}
	else
	{
		return GM_FALSE;
	}
}

GM_BOOL GM_RSSP1_APP_Clear_Msg_Queue(void)
{
	GM_RSSP1_SFM_object_struct *pSFM_FSFB = NULL;
	register GM_RSSP1_SFM_connection_struct *pSFM_FSFB_con = NULL;
	GM_UINT16 lv_count0;
	GM_INT32 rt;

	/*clear FSFB SFM queue*/
	pSFM_FSFB = GM_RSSP1_Get_SFM_Object();

	rt = FSFB_Msg_Queue_Clear(&(g_SFM_MQ.SND_MQ));
	if(GM_FALSE == rt)
	{
		return GM_FALSE;
	}

	rt = FSFB_Msg_Queue_Clear(&(g_SFM_MQ.RCV_MQ));   
	if(GM_FALSE == rt)
	{
		return GM_FALSE;
	}

	/*every connection Q*/
	for(lv_count0 = 0; lv_count0 < pSFM_FSFB->connection_nums; lv_count0++)
	{
		if(GM_TRUE  == pSFM_FSFB->connection[lv_count0].b_enable_FSFB_on_chn)
		{
			pSFM_FSFB_con = &(pSFM_FSFB->connection[lv_count0]);
			rt =  FSFB_Msg_Queue_Clear(&(pSFM_FSFB_con->L2U_dat_Q));
			if(GM_FALSE == rt)
			{
				return GM_FALSE;
			}
		}
	}
	return GM_TRUE;
}


GM_INT8 GM_RSSP1_APP_Interface_Rcv_App_Dat(GM_UINT8* buf, GM_UINT32* Src, GM_UINT32* len)
{
    GM_RSSP1_SFM_object_struct *pFSFB_SFM        = NULL;
    GM_INT32 i = 0;
    GM_RSSP1_SFM_L2U_pri_struct fsfb_pri;
    GM_UINT8 dat[GM_MAX_QUEUE_ELE_LEN - 50 + 200];   /* 预留，防止VLE端对SDM打包P1状态时，增加包头长度后超过GM_MAX_QUEUE_ELE_LEN */
    GM_UINT8 tmp_state_dat[GM_MAX_QUEUE_ELE_LEN + 200];
    GM_UINT8 warning_dat[GM_MAX_QUEUE_ELE_LEN];
    GM_INT32 warning_dat_len = 0;
    GM_RSSP1_SACEPID_struct peer_syn_sacepid;
    GM_INT32 dat_len = 0;
	GM_INT32 state_len = 0;
    GM_INT32 p1_pkt_sum= 0;

	if ((buf == NULL)||(Src == NULL)||(len == NULL))
	{
		return -1;
	}

    pFSFB_SFM = GM_RSSP1_Get_SFM_Object();

    GM_memset(dat , 0 , sizeof(dat));
    GM_memset(warning_dat, 0 , sizeof(warning_dat));
    warning_dat[0]  = INTERFACE_TYPE_RSSP1;
    warning_dat[1]  = INTERFACE_DAT_TYPE_RSSP1_WARNING;
    warning_dat_len = 0;
    peer_syn_sacepid.source_addr    = pFSFB_SFM->source_addr;
    peer_syn_sacepid.dest_addr      = GM_RSSP1_SYN_DEST_ADDR;

    if (GM_TRUE == FSFB_Msg_Queue_Get(&(g_SFM_MQ.RCV_MQ) , &fsfb_pri))
    {
    		printf("fsfb_pri.type = %x\n",fsfb_pri.type);
        switch (fsfb_pri.type)
        {

        case GM_RSSP1_SFM_Data_Ind:

            if (fsfb_pri.as.data_indi.bytes_count + 6 + 8 + 2 > sizeof(dat))
            {
                return -1;
            }

            if (GM_FALSE == GM_RSSP1_SFM_Is_SaCEPID_Equal(&peer_syn_sacepid , &(fsfb_pri.SaCEPID)))
            {
			
                if (GM_FALSE == GM_RSSP1_APP_Interface_Is_Local_ACTIVE())
                {
                    /* 本机为主机才将数据上传 LKD200000216  */
                    return -1;
                }
                ++p1_pkt_sum;

                /* dat from remote devices.report to VLE */
                dat[0]   = INTERFACE_TYPE_RSSP1;
                dat[1]   = INTERFACE_DAT_TYPE_RSSP1_DAT;
                dat[2]   = ((fsfb_pri.SaCEPID.source_addr & 0xff00) >> 8);
                dat[3]   = (fsfb_pri.SaCEPID.source_addr & 0x00ff) ;
                dat[4]   = ((fsfb_pri.SaCEPID.dest_addr & 0xff00) >> 8);
                dat[5]   = (fsfb_pri.SaCEPID.dest_addr & 0x00ff) ;
                GM_memcpy(dat + 6 , fsfb_pri.as.data_indi.byte , fsfb_pri.as.data_indi.bytes_count);

                *len = 6 + fsfb_pri.as.data_indi.bytes_count;
				
				*Src = fsfb_pri.SaCEPID.dest_addr;

				GM_memcpy(buf, dat, 6 + fsfb_pri.as.data_indi.bytes_count);					
            }
            else
            {
                /* syn dat from peer */
                GM_RSSP1_Syn_Proc_Rcvd_Syn_Dat(fsfb_pri.as.data_indi.byte , fsfb_pri.as.data_indi.bytes_count , pFSFB_SFM);
            }

            return 1;

        case GM_RSSP1_SFM_Connection_State_Indi:

            state_len = 0;
            for (i = 0 ; i < fsfb_pri.as.connection_state.connection_num ; ++i)
            {
                tmp_state_dat[state_len++] = (i & 0xff00) >> 8;
                tmp_state_dat[state_len++] = (i & 0xff);
                tmp_state_dat[state_len++] = (fsfb_pri.as.connection_state.connection_states[i].sacepid.dest_addr & 0xff00) >> 8;
                tmp_state_dat[state_len++] = (fsfb_pri.as.connection_state.connection_states[i].sacepid.dest_addr & 0xff);

                tmp_state_dat[state_len++] = (fsfb_pri.as.connection_state.connection_states[i].state & 0xff000000) >> 24;
                tmp_state_dat[state_len++] = (fsfb_pri.as.connection_state.connection_states[i].state & 0x00ff0000) >> 16;
                tmp_state_dat[state_len++] = (fsfb_pri.as.connection_state.connection_states[i].state & 0x0000ff00) >> 8;
                tmp_state_dat[state_len++] = (fsfb_pri.as.connection_state.connection_states[i].state & 0x000000ff);

                if((state_len + 3 + 2 <= sizeof(dat)) && (i == fsfb_pri.as.connection_state.connection_num - 1))
                {
                    dat_len = 0;
                    dat[dat_len++] = INTERFACE_TYPE_RSSP1;
                    dat[dat_len++] = INTERFACE_DAT_TYPE_RSSP1_COM_STATE;
                    dat[dat_len++] = state_len/8;
                    GM_memcpy(dat + dat_len , tmp_state_dat , state_len);
                    dat_len += state_len;

					*Src = 0x11;
					*len = dat_len;
					GM_memcpy(buf, dat, dat_len);		

                    state_len = 0;
                    GM_memset(tmp_state_dat , 0 , sizeof(tmp_state_dat));
                }
            }

            return 1;

        case GM_RSSP1_SFM_Warning_Indi:
            /* 处理报警信息。收集本周期内产生的所有报警信息，集中发送给vle */
            if(warning_dat_len + 2 + 2 <= sizeof(warning_dat))
            {
                warning_dat[1 + warning_dat_len] = fsfb_pri.as.warning.index;
                warning_dat[1 + warning_dat_len + 1] = fsfb_pri.as.warning.type;
                warning_dat_len += 2;
            }
            return 1;

        default:
            GM_Log_Msg(0,"####FSFB USER recvd unknow SFM indi:0x%x.Qcnt:%d.ID:(0x%X,0x%X),idx:%d.\n", fsfb_pri.type, FSFB_Get_Queue_Count(&g_SFM_MQ.RCV_MQ), fsfb_pri.SaCEPID.source_addr, fsfb_pri.SaCEPID.dest_addr, 0, 0);
            return -1;
        }
    }

    return 0;
}
GM_BOOL GM_RSSP1_APP_Interface_Send_App_Dat(GM_UINT8* pData, GM_INT16 len, GM_UINT16 dest_addr)
{
	GM_BOOL rt =GM_FALSE;
	GM_RSSP1_SFM_object_struct *pFSFB_SFM = NULL;
	GM_UINT8 dat[GM_MAX_QUEUE_ELE_LEN-50];   /* 预留，防止VLE端对SDM打包P1状态时，增加包头长度后超过GM_MAX_QUEUE_ELE_LEN */
	GM_UINT16 i = 0;
	GM_UINT16 source_addr = 0;
	GM_INT16 dat_len = 0;

	if (len<0)
	{
		return GM_FALSE;
	}

	pFSFB_SFM = GM_RSSP1_Get_SFM_Object();

	GM_memset(dat, 0, (GM_MAX_QUEUE_ELE_LEN-50));
	
	source_addr = pFSFB_SFM->source_addr;
	
	dat[0]   = ((source_addr & 0xff00) >> 8);
	dat[1]   = (source_addr & 0x00ff) ;
	dat[2]   = ((dest_addr & 0xff00) >> 8);
	dat[3]   = (dest_addr & 0x00ff) ;
	GM_memcpy(dat + 4 , pData , len);
	dat_len = 4 + len;

	rt = GM_RSSP1_Send_App_Dat(dat , dat_len);

	return rt;
}

#ifdef PF2oo3
GM_BOOL GM_RSSP1_2oo3_Conn_Recv_Dat(RSSP_Message_t* msg, GM_UINT8 index, GM_UINT8 chn_index)
{
	GM_RSSP1_com_pri_struct pri;
	GM_RSSP1_Write_Q_Return_Enum write_q_rt = Q_WRITE_FAIL;

	pri.bytes_count = msg->MsgSize;
	GM_memcpy(pri.byte , msg->Message, msg->MsgSize);

	write_q_rt = FSFB_Msg_Queue_Write(&(g_Link_MQ[index].RCV_SND_MQ[chn_index].RCV_MQ/*pLNK->connection[i].com_chn[j].recv_udp_dat_Q*/) , &pri);
	if (write_q_rt == Q_WRITE_FAIL)
	{
		return GM_FALSE;
	} 
	return GM_TRUE;
}

GM_BOOL GM_RSSP1_2oo3_Conn_Send_Dat(RSSP_Message_t* msg, GM_UINT8 index, GM_UINT8 chn_index)
{
	GM_RSSP1_com_pri_struct    pri;
	if (GM_FALSE == FSFB_Is_Msg_Queue_Empty(&(g_Link_MQ[index].RCV_SND_MQ[chn_index].SND_MQ)/*&(pLNK_con->com_chn[udp_chn_index].send_udp_dat_Q)*/))
	{

		if (GM_FALSE == FSFB_Msg_Queue_Get(&(g_Link_MQ[index].RCV_SND_MQ[chn_index].SND_MQ)/*&(pLNK_con->com_chn[udp_chn_index].send_udp_dat_Q)*/, &pri))
		{
			return GM_FALSE;
		}

		GM_memcpy(msg->Message,  pri.byte, pri.bytes_count);
		msg->MsgSize = pri.bytes_count;
		return GM_TRUE;
	}
	return GM_FALSE;
}

#endif
