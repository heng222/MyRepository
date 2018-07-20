
#include "GM_RSSP1_SFM_Init.h"
#include "../../GM_Utils/GM_Code_Convert.h"
#ifdef SFM_Part
extern RSSP1_MQ_Inter_struct g_SFM_MQ;

#ifndef CFM_Part
extern RSSP1_MQ_Inter_struct g_CFM_MQ;
#endif

extern GM_UINT32 g_valid_chn;
GM_BOOL GM_RSSP1_Init_Comm_Cfg_SFM_Addr(GM_UINT8 *pFileContent , GM_RSSP1_comm_cfg_struct *pCfg)
{
	GM_INT32 file_len = -1;
	GM_BOOL rt = GM_FALSE;
	GM_UINT8 **rp_file = &pFileContent;
	GM_UINT8 type = 0;

	if ((NULL == pFileContent) || (NULL == pCfg))
	{
		return GM_FALSE;
	}

	type = *(GM_UINT8*)pFileContent;
	pFileContent += sizeof(GM_UINT8);
	if (type == 0xFF)
	{
		pFileContent += sizeof(GM_UINT32);
	}

	/* 顺序不可变动。初始化各连接时需要从SFM cfg中获取本地连接通道共享的一些配置 */
	if (GM_FALSE == GM_RSSP1_Init_Comm_Global_SFM_Addr(pCfg, pFileContent, rp_file))
	{
		return GM_FALSE;
	}

	if (GM_FALSE == GM_RSSP1_Init_Comm_Connection_SFM_Addr(pCfg, pFileContent, rp_file))
	{
		return GM_FALSE;
	}
	return GM_TRUE;
}

GM_BOOL GM_RSSP1_Init_Comm_Global_SFM_Addr(GM_RSSP1_comm_cfg_struct *pCfg , GM_UINT8 *pFileContent, GM_UINT8 **r_ptr)
{
	GM_BOOL rt = GM_FALSE;
	GM_UINT32 valueInt = 0;
	GM_BOOL isbig = GM_Code_Is_Big_Endian();
	GM_UINT8 i =0;
	GM_UINT16 con_num = 0;
	GM_INT8 conn_index = 0;

	if ((NULL == pCfg) || (NULL == pFileContent))
	{
		return GM_FALSE;
	}

	/* RSSP1_GLOBAL 全局配置 */
	valueInt = *(GM_UINT16*)pFileContent;
	pFileContent += sizeof(GM_UINT16);
	pCfg->SFM_cfg.connection_nums = (GM_UINT16)valueInt;
	g_valid_chn = valueInt;

	valueInt = *(GM_UINT16*)pFileContent;
	pFileContent += sizeof(GM_UINT16);
	pCfg->SFM_cfg.source_addr = (GM_UINT16)valueInt;

	valueInt = *(GM_UINT32*)pFileContent;
	pFileContent += sizeof(GM_UINT32);
	pCfg->SFM_cfg.local_cfg[0].local_sid = valueInt;

	valueInt = *(GM_UINT32*)pFileContent;
	pFileContent += sizeof(GM_UINT32);
	pCfg->SFM_cfg.local_cfg[0].local_sinit = valueInt;

	valueInt = *(GM_UINT32*)pFileContent;
	pFileContent += sizeof(GM_UINT32);
	pCfg->SFM_cfg.local_cfg[0].local_dataVer = valueInt;

	valueInt = *(GM_UINT32*)pFileContent;
	pFileContent += sizeof(GM_UINT32);
	pCfg->SFM_cfg.local_cfg[0].local_sys_chk = valueInt;
	
	valueInt = *(GM_UINT32*)pFileContent;
	pFileContent += sizeof(GM_UINT32);
	pCfg->SFM_cfg.local_cfg[1].local_sid = valueInt;

	valueInt = *(GM_UINT32*)pFileContent;
	pFileContent += sizeof(GM_UINT32);
	pCfg->SFM_cfg.local_cfg[1].local_sinit = valueInt;

	valueInt = *(GM_UINT32*)pFileContent;
	pFileContent += sizeof(GM_UINT32);
	pCfg->SFM_cfg.local_cfg[1].local_dataVer = valueInt;

	valueInt = *(GM_UINT32*)pFileContent;
	pFileContent += sizeof(GM_UINT32);
	pCfg->SFM_cfg.local_cfg[1].local_sys_chk = valueInt;

	valueInt = *(GM_UINT32*)pFileContent;
	pFileContent += sizeof(GM_UINT32);
	if (isbig == GM_FALSE)
	{
		valueInt = GM_Code_Big_Little_Endian32(valueInt);
	}
	pCfg->SFM_cfg.U2L_pri_Q_size    = valueInt;
	pCfg->SFM_cfg.U2L_pri_Q_offset  = (GM_UINT32)GM_malloc(valueInt*sizeof(GM_RSSP1_SFM_U2L_pri_struct));
	if (0 == pCfg->SFM_cfg.U2L_pri_Q_offset)
	{
		return GM_FALSE;
	}
	GM_memset((void*)pCfg->SFM_cfg.U2L_pri_Q_offset, 0, valueInt*sizeof(GM_RSSP1_SFM_U2L_pri_struct));

	valueInt = *(GM_UINT32*)pFileContent;
	pFileContent += sizeof(GM_UINT32);
	if (isbig == GM_FALSE)
	{
		valueInt = GM_Code_Big_Little_Endian32(valueInt);
	}
	pCfg->SFM_cfg.L2U_pri_Q_size    = valueInt;
	pCfg->SFM_cfg.L2U_pri_Q_offset  = (GM_UINT32)GM_malloc(valueInt*sizeof(GM_RSSP1_SFM_L2U_pri_struct));

	if (0 == pCfg->SFM_cfg.L2U_pri_Q_offset)
	{
		return GM_FALSE;
	}
	GM_memset((void*)pCfg->SFM_cfg.L2U_pri_Q_offset, 0, valueInt*sizeof(GM_RSSP1_SFM_L2U_pri_struct));
	
#ifndef CFM_Part
	valueInt = *(GM_UINT32*)pFileContent;
	pFileContent += sizeof(GM_UINT32);
	if (isbig == GM_FALSE)
	{
		valueInt = GM_Code_Big_Little_Endian32(valueInt);
	}
	pCfg->SFM_cfg.U2L_pri_Q_size_CFM    = valueInt;
	pCfg->SFM_cfg.U2L_pri_Q_offset_CFM  = (GM_UINT32)GM_malloc(valueInt * sizeof(GM_RSSP1_CFM_U2L_pri_struct));
	if (NULL == pCfg->SFM_cfg.U2L_pri_Q_offset_CFM)
	{
		return GM_FALSE;
	}
	GM_memset((void*)pCfg->SFM_cfg.U2L_pri_Q_offset_CFM, 0, valueInt*sizeof(GM_RSSP1_CFM_U2L_pri_struct));

	valueInt = *(GM_UINT32*)pFileContent;
	pFileContent += sizeof(GM_UINT32);
	if (isbig == GM_FALSE)
	{
		valueInt = GM_Code_Big_Little_Endian32(valueInt);
	}
	pCfg->SFM_cfg.L2U_pri_Q_size_CFM    = valueInt;
	pCfg->SFM_cfg.L2U_pri_Q_offset_CFM  = (GM_UINT32)GM_malloc(valueInt * sizeof(GM_RSSP1_CFM_L2U_pri_struct));

	if (NULL == pCfg->SFM_cfg.L2U_pri_Q_offset_CFM)
	{
		return GM_FALSE;
	}
	GM_memset((void*)pCfg->SFM_cfg.L2U_pri_Q_offset_CFM, 0, valueInt * sizeof(GM_RSSP1_CFM_L2U_pri_struct));
#endif
	if (isbig == GM_FALSE)
	{
		pCfg->SFM_cfg.connection_nums = GM_Code_Big_Little_Endian16(pCfg->SFM_cfg.connection_nums);
		if (pCfg->SFM_cfg.connection_nums > GM_RSSP1_MAX_SAFETY_CONNECTION_NUM)
		{
			return GM_FALSE;
		}
		pCfg->SFM_cfg.source_addr = GM_Code_Big_Little_Endian16(pCfg->SFM_cfg.source_addr);
		for (i=0;i<2;i++)
		{
			pCfg->SFM_cfg.local_cfg[i].local_sid = GM_Code_Big_Little_Endian32(pCfg->SFM_cfg.local_cfg[i].local_sid);
			pCfg->SFM_cfg.local_cfg[i].local_sinit = GM_Code_Big_Little_Endian32(pCfg->SFM_cfg.local_cfg[i].local_sinit);
			pCfg->SFM_cfg.local_cfg[i].local_dataVer = GM_Code_Big_Little_Endian32(pCfg->SFM_cfg.local_cfg[i].local_dataVer);
			pCfg->SFM_cfg.local_cfg[i].local_sys_chk = GM_Code_Big_Little_Endian32(pCfg->SFM_cfg.local_cfg[i].local_sys_chk);
		}
	}
	*r_ptr = pFileContent;
	return GM_TRUE;
}

GM_BOOL GM_RSSP1_Init_Comm_Connection_SFM_Addr(GM_RSSP1_comm_cfg_struct *pCfg , GM_UINT8 *pFileContent, GM_UINT8 **r_ptr)
{
	GM_BOOL rt                             = GM_FALSE;
	GM_UINT32 valueInt                        = 0;
	GM_INT32 conn_index                      = 0;
	GM_INT32 chn_index                   = 0;
	GM_INT32 fsfb_chn_index                  = 0;
	GM_BOOL isbig = GM_Code_Is_Big_Endian();
	GM_UINT8 i =0;
	GM_RSSP1_SFM_connection_cfg_struct *pSFM_conn_cfg           = NULL;

	if ((NULL == pCfg) || (NULL == pFileContent))
	{
		return GM_FALSE;
	}

	/* 各个连接通道配置 */
	for (conn_index = 0; conn_index < pCfg->SFM_cfg.connection_nums; ++conn_index)
	{
		pSFM_conn_cfg = &(pCfg->SFM_cfg.connection_cfg[conn_index]);

		valueInt = *(GM_UINT16*)pFileContent;
		pFileContent += sizeof(GM_UINT16);
		pSFM_conn_cfg->dest_addr = (GM_UINT16)valueInt;

		/* init FSFB param */
		valueInt = *(GM_UINT16*)pFileContent;
		pFileContent += sizeof(GM_UINT16);
		pSFM_conn_cfg->deltaTime = (GM_UINT16)valueInt;

		valueInt = *(GM_UINT16*)pFileContent;
		pFileContent += sizeof(GM_UINT16);
		pSFM_conn_cfg->lifeTime = (GM_UINT16)valueInt;

		valueInt = *(GM_UINT16*)pFileContent;
		pFileContent += sizeof(GM_UINT16);
		pSFM_conn_cfg->torlerate_cycle_cfg = (GM_UINT16)valueInt;

		valueInt = *(GM_UINT8*)pFileContent;
		pFileContent += sizeof(GM_UINT8);
		pSFM_conn_cfg->num_data_ver = (GM_UINT8)valueInt;

		valueInt = *(GM_UINT32*)pFileContent;
		pFileContent += sizeof(GM_UINT32);
		pSFM_conn_cfg->fsfb_chn_cfg[0].remote_sid = valueInt;

		valueInt = *(GM_UINT32*)pFileContent;
		pFileContent += sizeof(GM_UINT32);
		pSFM_conn_cfg->fsfb_chn_cfg[0].remote_sinit = valueInt;

		valueInt = *(GM_UINT32*)pFileContent;
		pFileContent += sizeof(GM_UINT32);
		pSFM_conn_cfg->fsfb_chn_cfg[0].remote_dataVer = valueInt;

		valueInt = *(GM_UINT32*)pFileContent;
		pFileContent += sizeof(GM_UINT32);
		pSFM_conn_cfg->fsfb_chn_cfg[1].remote_sid = valueInt;

		valueInt = *(GM_UINT32*)pFileContent;
		pFileContent += sizeof(GM_UINT32);
		pSFM_conn_cfg->fsfb_chn_cfg[1].remote_sinit = valueInt;

		valueInt = *(GM_UINT32*)pFileContent;
		pFileContent += sizeof(GM_UINT32);
		pSFM_conn_cfg->fsfb_chn_cfg[1].remote_dataVer = valueInt;

		/* 对等设备各个UDP通道均使用独立的FSFB。此时UDP通道数必须为1 */
		valueInt = *(GM_BOOL*)pFileContent;
		pFileContent += sizeof(GM_BOOL);
		if (isbig == GM_FALSE)
		{
			valueInt = GM_Code_Big_Little_Endian32(valueInt);
		}
		pSFM_conn_cfg->b_enable_FSFB_on_chn = (GM_BOOL)valueInt;

		if (GM_TRUE == pSFM_conn_cfg->b_enable_FSFB_on_chn)
		{
			/* init UDP chn apply FSFB ID */
			valueInt = *(GM_UINT32*)pFileContent;
			pFileContent += sizeof(GM_UINT32);
			pSFM_conn_cfg->Chn_apply_FSFB_ID = (GM_UINT32)valueInt;

			/* init msg queue in the SFM connection */
			valueInt = *(GM_UINT32*)pFileContent;
			pFileContent += sizeof(GM_UINT32);
			if (isbig == GM_FALSE)
			{
				valueInt = GM_Code_Big_Little_Endian32(valueInt);
			}
			pSFM_conn_cfg->L2U_dat_Q_size = valueInt;
			pSFM_conn_cfg->L2U_dat_Q_offset = (GM_UINT32)GM_malloc( valueInt*sizeof(GM_RSSP1_SFM_L2U_pri_struct));

			if (0 == pSFM_conn_cfg->L2U_dat_Q_offset)
			{
				return GM_FALSE;
			}
			GM_memset((void*)pSFM_conn_cfg->L2U_dat_Q_offset, 0, valueInt*sizeof(GM_RSSP1_SFM_L2U_pri_struct));
		}

		if (isbig == GM_FALSE)
		{
			for (conn_index = 0; conn_index < pCfg->SFM_cfg.connection_nums; ++conn_index)
			{
				pSFM_conn_cfg = &(pCfg->SFM_cfg.connection_cfg[conn_index]);

				pSFM_conn_cfg->dest_addr = GM_Code_Big_Little_Endian16(pSFM_conn_cfg->dest_addr);
				pSFM_conn_cfg->deltaTime = GM_Code_Big_Little_Endian16(pSFM_conn_cfg->deltaTime);
				pSFM_conn_cfg->lifeTime = GM_Code_Big_Little_Endian16(pSFM_conn_cfg->lifeTime);
				pSFM_conn_cfg->torlerate_cycle_cfg = GM_Code_Big_Little_Endian16(pSFM_conn_cfg->torlerate_cycle_cfg);
				for (i=0; i<2; ++i)
				{
					pSFM_conn_cfg->fsfb_chn_cfg[i].remote_sid = GM_Code_Big_Little_Endian32(pSFM_conn_cfg->fsfb_chn_cfg[i].remote_sid);
					pSFM_conn_cfg->fsfb_chn_cfg[i].remote_sinit = GM_Code_Big_Little_Endian32(pSFM_conn_cfg->fsfb_chn_cfg[i].remote_sinit);
					pSFM_conn_cfg->fsfb_chn_cfg[i].remote_dataVer = GM_Code_Big_Little_Endian32(pSFM_conn_cfg->fsfb_chn_cfg[i].remote_dataVer);
				}
				if (GM_TRUE == pSFM_conn_cfg->b_enable_FSFB_on_chn)
				{
					pSFM_conn_cfg->Chn_apply_FSFB_ID = GM_Code_Big_Little_Endian32(pSFM_conn_cfg->Chn_apply_FSFB_ID);
				}
			}
		}

		/* init local params form SFM cfg */
		for (fsfb_chn_index = 0 ; fsfb_chn_index < GM_RSSP1_CHECK_CHN_NUM ; ++fsfb_chn_index)
		{
			pSFM_conn_cfg->fsfb_chn_cfg[fsfb_chn_index].local_sid       = pCfg->SFM_cfg.local_cfg[fsfb_chn_index].local_sid;
			pSFM_conn_cfg->fsfb_chn_cfg[fsfb_chn_index].local_sinit     = pCfg->SFM_cfg.local_cfg[fsfb_chn_index].local_sinit;
			pSFM_conn_cfg->fsfb_chn_cfg[fsfb_chn_index].local_dataVer   = pCfg->SFM_cfg.local_cfg[fsfb_chn_index].local_dataVer;
			pSFM_conn_cfg->fsfb_chn_cfg[fsfb_chn_index].local_sys_chk   = pCfg->SFM_cfg.local_cfg[fsfb_chn_index].local_sys_chk;
		}

		/* init LSFR,CRC table */
		pSFM_conn_cfg->fsfb_chn_cfg[0].pLFSR_left_table     = (GM_UINT32 *)GM_LFSR_LEFT_CHN1_TABLE;
		pSFM_conn_cfg->fsfb_chn_cfg[0].pLFSR_right_table    = (GM_UINT32 *)GM_LFSR_RIGHT_CHN1_TABLE;
		pSFM_conn_cfg->fsfb_chn_cfg[0].pCRC32_table         = (GM_UINT32 *)GM_CRC32_Channel1_Table;
		pSFM_conn_cfg->fsfb_chn_cfg[0].pCRC16_table         = (GM_UINT16 *)GM_CRC16_Table_0x10811_LSB;
		pSFM_conn_cfg->fsfb_chn_cfg[1].pLFSR_left_table     = (GM_UINT32 *)GM_LFSR_LEFT_CHN2_TABLE;
		pSFM_conn_cfg->fsfb_chn_cfg[1].pLFSR_right_table    = (GM_UINT32 *)GM_LFSR_RIGHT_CHN2_TABLE;
		pSFM_conn_cfg->fsfb_chn_cfg[1].pCRC32_table         = (GM_UINT32 *)GM_CRC32_Channel2_Table;
		pSFM_conn_cfg->fsfb_chn_cfg[1].pCRC16_table         = (GM_UINT16 *)GM_CRC16_Table_0x10811_LSB;
	}

	return GM_TRUE;
}

GM_BOOL GM_RSSP1_SFM_Init_Addr(GM_UINT8 *addr)
{
	GM_RSSP1_comm_cfg_struct fsfb_cfg;
	GM_RSSP1_SFM_object_struct *pFSFB_SFM        = NULL;

	pFSFB_SFM = GM_RSSP1_Get_SFM_Object();

	if ((NULL == addr) || (NULL == pFSFB_SFM))
	{
		return GM_FALSE;
	}

	if (GM_TRUE == GM_RSSP1_Init_Comm_Cfg_SFM_Addr(addr, &fsfb_cfg))
	{
		if (GM_TRUE == GM_RSSP1_SFM_Init_Lib(&fsfb_cfg , pFSFB_SFM))
		{
			return GM_TRUE;
		}
	}

	return GM_FALSE;
}

#endif
