
#include "GM_RSSP1_Syn.h"
#include "GM_RSSP1_APP_Interface.h"

static GM_UINT32 syn_last_rcvd_pkt_SN  = 0;
static GM_BOOL b_last_AS_state    = GM_FALSE;

GM_BOOL GM_RSSP1_Syn_Send_Fsfb_State_To_Peer(GM_RSSP1_SFM_object_struct *pSFM , Local_Sys_AB_enum sys_a_b , GM_BOOL b_is_active)
{
    GM_RSSP1_SFM_connection_struct *pSFM_con = NULL;
    GM_INT32 con_index = 0;
    GM_RSSP1_Syn_Info_struct syn_info;
    GM_UINT8 syn_dat[GM_RSSP1_MAX_SAFETY_DAT_LEN] = {0};
    GM_INT32 state_dat_len = 0;
    GM_UINT16 crc16 = 0;
	GM_RSSP1_SACEPID_struct peer_syn_sacepid = {0};
    GM_BOOL rt = GM_FALSE;

    if (NULL == pSFM)
    {
        return GM_FALSE;
    }

    if (GM_RSSP1_Lib_State_Operational != pSFM->lib_state)
    {
        return GM_FALSE;
    }

    if (1 >= pSFM->connection_nums)
    {
        /* 只有一个连接，不可能存在同步通道 */
        return GM_FALSE;
    }

    peer_syn_sacepid.source_addr    = pSFM->source_addr;
    peer_syn_sacepid.dest_addr      = GM_RSSP1_SYN_DEST_ADDR;

    syn_dat[0] = INTERFACE_TYPE_SYN;
    syn_dat[1] = INTERFACE_DAT_TYPE_SYN_RSSP1_STATUS_DAT;
        
    for (con_index = 0 ; con_index < pSFM->connection_nums ; ++con_index)
    {
        pSFM_con = &(pSFM->connection[con_index]);

        if (GM_FALSE == GM_RSSP1_SFM_Is_SaCEPID_Equal(&peer_syn_sacepid , &(pSFM_con->SaCEPID)))
        {
            syn_info.sacepid = pSFM_con->SaCEPID;
            syn_info.time_TC    = pSFM_con->time.TC;
            syn_info.time_TS[0] = pSFM_con->time.TS[0];
            syn_info.time_TS[1] = pSFM_con->time.TS[1];
            syn_info.time_oldTS[0] = pSFM_con->time.oldTS[0];
            syn_info.time_oldTS[1] = pSFM_con->time.oldTS[1];
            syn_info.env[0] = pSFM_con->env[0];
            syn_info.env[1] = pSFM_con->env[1];

            GM_memcpy(syn_dat + 2 + state_dat_len , &syn_info , sizeof(syn_info));
            state_dat_len += sizeof(syn_info);
        }
    }

    /* add crc16 at tail, send to peer  */
    GM_CRC_Calculate_CRC16(syn_dat, state_dat_len + 2, &crc16, GM_CRC16_Table_0x11021_MSB);

    syn_dat[2 + state_dat_len] = (crc16 & 0xff00) >> 8;
    syn_dat[3 + state_dat_len] = (crc16 & 0xff);

    /* send syn dat to peer via FSFB syn channel.CRC checksum not used here */
    rt = GM_RSSP1_User_Send_Dat(&peer_syn_sacepid , syn_dat , 4 + state_dat_len , sys_a_b , b_is_active, pSFM);
    return rt;
}

void GM_RSSP1_Syn_Proc_Rcvd_Syn_Dat(GM_UINT8 *pDat , GM_INT32 dat_len , GM_RSSP1_SFM_object_struct *pSFM)
{
    GM_RSSP1_Syn_Info_struct syn_info;      /* 同步过来的连接状态数据 */
    GM_UINT8 interface_type;
    GM_UINT8 syn_dat_type;
    GM_INT32 syn_con_index = 0;
    GM_INT32 syn_con_nums = 0;   /* 同步过来的连接数 */
    GM_RSSP1_SFM_connection_struct *pSFM_con = NULL;
    GM_UINT16 crc16 = 0;
    GM_UINT16 rcvd_crc16 = 0;
    GM_UINT32 rcvd_main_cycle   = 0;
    GM_UINT32 cycle = 0;

    interface_type = *(pDat);
    if((INTERFACE_TYPE_SYN != interface_type)||(dat_len<0))
    {
        GM_Log_Msg(0,"RSSP1 syn rcv interface type err:0x%X.\n",interface_type,0,0,0,0,0);
        return;
    }
    
    /* check crc16 first */
    GM_CRC_Calculate_CRC16(pDat, dat_len - 2, &crc16, GM_CRC16_Table_0x11021_MSB);
    rcvd_crc16 = ((*(pDat + dat_len - 2)) << 8) + *(pDat + dat_len - 1);

    if (rcvd_crc16 != crc16)
    {
        GM_Log_Msg(0,"FSFB rcvd Syn dat from peer,%d bytes , CRC16 err! rcv:0x%X,cal:0x%X.\n", dat_len, rcvd_crc16, crc16, 0, 0, 0);
        return;
    }

    syn_dat_type    = *(pDat + 1);

	switch (syn_dat_type)
    {
		case INTERFACE_DAT_TYPE_SYN_RSSP1_STATUS_DAT:

			for (syn_con_index = 0 ; syn_con_index < syn_con_nums ; ++syn_con_index)
			{
				GM_memcpy(&syn_info , pDat + 2 + syn_con_index * sizeof(syn_info) , sizeof(syn_info));
				pSFM_con = GM_RSSP1_SFM_Get_Connection_BY_SaCEPID(&(syn_info.sacepid) , pSFM);

				if (NULL != pSFM_con)
				{
					/* if local is standby,set local fsfb connection state. */
					pSFM_con->time.TC       = syn_info.time_TC;
					pSFM_con->time.TS[0]    = syn_info.time_TS[0];
					pSFM_con->time.TS[1]    = syn_info.time_TS[1];
					pSFM_con->time.oldTS[0] = syn_info.time_oldTS[0];
					pSFM_con->time.oldTS[1] = syn_info.time_oldTS[1];
					pSFM_con->env[0]        = syn_info.env[0];
					pSFM_con->env[1]        = syn_info.env[1];
				}
			}
			break;

		default:
			GM_Log_Msg(0,"FSFB SFM rcv unknow syn dat type:0x%X.\n", syn_dat_type , 0, 0, 0, 0, 0);
			break;
    }

    return;
}
