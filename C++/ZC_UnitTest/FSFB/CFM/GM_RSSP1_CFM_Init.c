
#include "GM_RSSP1_CFM_Init.h"

#ifdef CFM_Part

extern GM_UINT32 g_valid_chn;

extern RSSP1_MQ_Inter_struct g_CFM_MQ;
extern RSSP1_MQ_LINK_struct g_Link_MQ[GM_RSSP1_MAX_SAFETY_CONNECTION_NUM];


#if 0
GM_BOOL GM_RSSP1_Init_Comm_Cfg_CFM(char *init_file_path , GM_RSSP1_comm_cfg_struct *pCfg)
{
    GM_INT32 file_len = -1;
    GM_INT8 *pIniFileContent = NULL; /**< 存储Ini文件内容, 动态分配, 使用完之后释放 */
    GM_BOOL rt = GM_FALSE;

    if ((NULL == init_file_path) || (NULL == pCfg))
    {
        return GM_FALSE;
    }

    /* 为读文件分配内存 */
    file_len = GM_Get_File_Size(init_file_path);

    if (-1 == file_len)
    {
        return GM_FALSE;
    }

    pIniFileContent = (char *)GM_malloc(file_len + 1);

    if (NULL == pIniFileContent)
    {
        return GM_FALSE;
    }

    GM_memset(pIniFileContent, 0, file_len + 1);

    /** @brief 初始化ini文件, 即读取其中的内容 */

    rt = GM_Ini_File_Load(init_file_path, pIniFileContent, file_len + 1);

    if (GM_FALSE == rt)
    {
        GM_free(pIniFileContent);
        pIniFileContent = NULL;

        return GM_FALSE;
    }

    /* 顺序不可变动。初始化各连接时需要从SFM cfg中获取本地连接通道共享的一些配置 */
    if (GM_FALSE == GM_RSSP1_Init_Comm_Global_CFM(pCfg, pIniFileContent))
    {
        return GM_FALSE;
    }

    if (GM_FALSE == GM_RSSP1_Init_Comm_Connection_CFM(pCfg, pIniFileContent))
    {
        return GM_FALSE;
    }

    GM_free(pIniFileContent);

    pIniFileContent = NULL;

    return GM_TRUE;
}
#endif

GM_BOOL GM_RSSP1_Init_Comm_Cfg_CFM_CSP(char *init_file , GM_RSSP1_comm_cfg_struct *pCfg)
{
    GM_INT32 file_len = -1;
    GM_INT8 *pIniFileContent = NULL; /**< 存储Ini文件内容, 动态分配, 使用完之后释放 */
    GM_BOOL rt = GM_FALSE;

    if ((NULL == init_file) || (NULL == pCfg))
    {
        return GM_FALSE;
    }


	pIniFileContent = (GM_INT8*)init_file;


    /* 顺序不可变动。初始化各连接时需要从SFM cfg中获取本地连接通道共享的一些配置 */
    if (GM_FALSE == GM_RSSP1_Init_Comm_Global_CFM(pCfg, pIniFileContent))
    {
		printf("Global_CFM Err\n");
        return GM_FALSE;
    }

    if (GM_FALSE == GM_RSSP1_Init_Comm_Connection_CFM(pCfg, pIniFileContent))
    {
		printf("Global_CFM Err2\n");		
        return GM_FALSE;
    }

    return GM_TRUE;
}


GM_BOOL GM_RSSP1_Init_Comm_Global_CFM(GM_RSSP1_comm_cfg_struct *pCfg , GM_INT8 *pIniFileContent)
{
    GM_BOOL rt = GM_FALSE;
    GM_INT32 valueInt = -1;
    GM_INT8 valueString[256] = {0};

    if ((NULL == pCfg) || (NULL == pIniFileContent))
    {
        return GM_FALSE;
    }

    /* RSSP1_GLOBAL 全局配置 */
    rt = GM_Ini_File_Read_Int("RSSP1_GLOBAL", "connection_num", &valueInt, pIniFileContent);

    if ((GM_FALSE == rt) || (valueInt < 0) || (valueInt > GM_RSSP1_MAX_SAFETY_CONNECTION_NUM))
    {
        return GM_FALSE;
    }
    else
    {
        pCfg->CFM_cfg.connection_nums = (GM_UINT16)valueInt;
		g_valid_chn = valueInt;
    }

	printf("connection_num = %d\n",valueInt);

	rt = GM_Ini_File_Read_String("RSSP1_GLOBAL", "source_addr", valueString , sizeof(valueString), pIniFileContent);

	if (GM_FALSE == rt)
	{
		
	printf("111\n");		
		return GM_FALSE;
	}
	else
	{
		pCfg->CFM_cfg.source_addr = (GM_UINT16)(strtoul(valueString , NULL , 16));
	}
	

    rt = GM_Ini_File_Read_Int("RSSP1_GLOBAL", "CFM_U2L_Q_Size_per_connection", &valueInt, pIniFileContent);
	
	valueInt = 50;

    if ((GM_FALSE == rt) || (valueInt < 0))
    {
	printf("222\n");			
        return GM_FALSE;
    }
    else
    {
        pCfg->CFM_cfg.U2L_pri_Q_size    = (GM_UINT32)valueInt;
        pCfg->CFM_cfg.U2L_pri_Q_offset  = (GM_UINT32)GM_malloc(valueInt * sizeof(GM_RSSP1_CFM_U2L_pri_struct));

        if (NULL == pCfg->CFM_cfg.U2L_pri_Q_offset)
        {
	        printf("333  %d, %d, %d\n", valueInt, sizeof(GM_RSSP1_CFM_U2L_pri_struct), valueInt * sizeof(GM_RSSP1_CFM_U2L_pri_struct));				
            return GM_FALSE;
        }
        GM_memset((void*)pCfg->CFM_cfg.U2L_pri_Q_offset, 0, valueInt*sizeof(GM_RSSP1_CFM_U2L_pri_struct));
    }

    rt = GM_Ini_File_Read_Int("RSSP1_GLOBAL", "CFM_L2U_Q_Size_per_connection", &valueInt, pIniFileContent);

	valueInt = 50;
	
    if ((GM_FALSE == rt) || (valueInt < 0))
    {
		
	printf("444\n");			
        return GM_FALSE;
    }
    else
    {
        pCfg->CFM_cfg.L2U_pri_Q_size    = (GM_UINT32)valueInt;
        pCfg->CFM_cfg.L2U_pri_Q_offset  = (GM_UINT32)GM_malloc(valueInt * sizeof(GM_RSSP1_CFM_L2U_pri_struct));

        if (NULL == pCfg->CFM_cfg.L2U_pri_Q_offset)
        {
	printf("555 %d\n", valueInt * sizeof(GM_RSSP1_CFM_L2U_pri_struct));				
            return GM_FALSE;
        }
        GM_memset((void*)pCfg->CFM_cfg.L2U_pri_Q_offset, 0, valueInt * sizeof(GM_RSSP1_CFM_L2U_pri_struct));
    }

    return GM_TRUE;
}

GM_BOOL GM_RSSP1_Init_Comm_Connection_CFM(GM_RSSP1_comm_cfg_struct *pCfg , GM_INT8 *pIniFileContent)
{
    GM_BOOL rt = GM_FALSE;
    GM_INT32 valueInt = -1;
    GM_INT8 valueString[256] = {0};
    GM_BOOL valueBool = GM_FALSE;
    GM_INT8 section_key[256] = {0};   /* 连接通道键名 */
    GM_INT8 sub_section_key[256] = {0};   /* UDP通道键名 */
    GM_INT32 key_len = 0;
    GM_INT32 sub_key_len = 0;
    GM_INT32 conn_index = 0;
    GM_INT32 chn_index = 0;
    GM_INT32 fsfb_chn_index = 0;
    GM_RSSP1_CFM_connection_cfg_struct *pCFM_conn_cfg = NULL;

    if ((NULL == pCfg) || (NULL == pIniFileContent))
    {
        return GM_FALSE;
    }

    /* 各个连接通道配置 */
    key_len = sizeof("CON_") - 1;

    GM_memcpy(section_key, "CON_", key_len + 1);

    for (conn_index = 0; conn_index < pCfg->CFM_cfg.connection_nums; ++conn_index)
    {
        pCFM_conn_cfg = &(pCfg->CFM_cfg.connection_cfg[conn_index]);

        GM_memset(section_key + key_len, 0, sizeof(section_key) - key_len);
        sprintf(section_key + key_len, "%d", conn_index);

        rt = GM_Ini_File_Read_String(section_key, "dest_addr", valueString , sizeof(valueString), pIniFileContent);

        if (GM_FALSE == rt)
        {
            return GM_FALSE;
        }
        else
        {
            pCFM_conn_cfg->dest_addr = (GM_UINT16)(strtoul(valueString , NULL , 16));
        }

        rt = GM_Ini_File_Read_BOOL(section_key , "enable_CRSCD_pack" , &valueBool, pIniFileContent);

        if (GM_FALSE == rt)
        {
            return GM_FALSE;
        }
        else
        {
            pCFM_conn_cfg->b_enable_CRSCD_pack = valueBool;
        }

		/* 对等设备各个UDP通道均使用独立的FSFB。此时UDP通道数必须为1 */
		rt = GM_Ini_File_Read_BOOL(section_key , "enable_UDP_chn_FSFB" , &valueBool, pIniFileContent);

		if (GM_FALSE == rt)
		{
			return GM_FALSE;
		}
		else
		{
			pCFM_conn_cfg->b_enable_FSFB_on_chn = valueBool;
		}
        /* init com type */
        rt = GM_Ini_File_Read_Int(section_key, "com_type", &valueInt, pIniFileContent);

        if ((GM_FALSE == rt) || (valueInt < 0))
        {
            return GM_FALSE;
        }
        else
        {
            if(0 == valueInt)
            {
                pCFM_conn_cfg->com_type = GM_RSSP1_CFM_COMM_TYPE_UDP;
            }
            else if(1 == valueInt)
            {
                pCFM_conn_cfg->com_type = GM_RSSP1_CFM_COMM_TYPE_SCOM;
            }
            else
            {
                pCFM_conn_cfg->com_type = GM_RSSP1_CFM_COMM_TYPE_UNKNOW;
            }
        }

        if(GM_RSSP1_CFM_COMM_TYPE_UDP == pCFM_conn_cfg->com_type)
        {
            /* init UDP channel param */
            rt = GM_Ini_File_Read_Int(section_key, "UDP_channel_num", &valueInt, pIniFileContent);

            if ((GM_FALSE == rt) || (valueInt < 0) || (valueInt > GM_RSSP1_CFM_MAX_CHANNEL_NUM))
            {
                return GM_FALSE;
            }
            else
            {
				pCFM_conn_cfg->chn_num = (GM_UINT16)valueInt;
			}
        }

        /* 检查UDP通道数是否与走独立的FSFB检验方案冲突。使用此方案时，UDP通道数必须为1 */
        if ((GM_TRUE == pCFM_conn_cfg->b_enable_FSFB_on_chn) && (1 != pCFM_conn_cfg->chn_num))
        {
            GM_Log_Msg(0,"FSFB init fail! UDP channel = %d,must = 1.check 'enable_UDP_chn_FSFB' option.\n", pCFM_conn_cfg->chn_num, 0, 0, 0, 0, 0);
            return GM_FALSE;
        }

		/* init UDP msg queues */
		for (chn_index = 0 ; chn_index < pCFM_conn_cfg->chn_num ; ++chn_index)
		{

			sub_key_len = sizeof("local_ip_") - 1;
			GM_memcpy(sub_section_key, "local_ip_", sub_key_len + 1);
			GM_memset(sub_section_key + sub_key_len, 0, 2);
			sprintf(sub_section_key + sub_key_len, "%d", chn_index);
			rt = GM_Ini_File_Read_String(section_key, sub_section_key, valueString, sizeof(valueString), pIniFileContent);

			if (GM_FALSE == rt)
			{
				return GM_FALSE;
			}
			else
			{
				pCFM_conn_cfg->UDP_chn_cfg[chn_index].loc_ip = inet_addr(valueString);
			}

			sub_key_len = sizeof("local_port_") - 1;

			GM_memcpy(sub_section_key, "local_port_", sub_key_len + 1);
			GM_memset(sub_section_key + sub_key_len, 0, 2);
			sprintf(sub_section_key + sub_key_len, "%d", chn_index);
			rt = GM_Ini_File_Read_Int(section_key, sub_section_key, &valueInt, pIniFileContent);

			if ((GM_FALSE == rt) || (valueInt < 0))
			{
				return GM_FALSE;
			}
			else
			{
				pCFM_conn_cfg->UDP_chn_cfg[chn_index].loc_port= (GM_UINT32)valueInt;
			}

			sub_key_len = sizeof("remote_ip_") - 1;
			GM_memcpy(sub_section_key, "remote_ip_", sub_key_len + 1);
			GM_memset(sub_section_key + sub_key_len, 0, 2);
			sprintf(sub_section_key + sub_key_len, "%d", chn_index);
			rt = GM_Ini_File_Read_String(section_key, sub_section_key, valueString, sizeof(valueString), pIniFileContent);

			if (GM_FALSE == rt)
			{
				return GM_FALSE;
			}
			else
			{
				pCFM_conn_cfg->UDP_chn_cfg[chn_index].rem_ip = inet_addr(valueString);
			}

			sub_key_len = sizeof("remote_port_") - 1;

			GM_memcpy(sub_section_key, "remote_port_", sub_key_len + 1);
			GM_memset(sub_section_key + sub_key_len, 0, 2);
			sprintf(sub_section_key + sub_key_len, "%d", chn_index);
			rt = GM_Ini_File_Read_Int(section_key, sub_section_key, &valueInt, pIniFileContent);

			if ((GM_FALSE == rt) || (valueInt < 0))
			{
				return GM_FALSE;
			}
			else
			{
				pCFM_conn_cfg->UDP_chn_cfg[chn_index].rem_port= (GM_UINT32)valueInt;
			}
		}

		rt = GM_Ini_File_Read_Int(section_key, "UDP_recv_MQ_size", &valueInt, pIniFileContent);

		if ((GM_FALSE == rt) || (valueInt < 0))
		{
			return GM_FALSE;
		}
		else
		{
			for (chn_index = 0 ; chn_index < pCFM_conn_cfg->chn_num ; ++chn_index)
			{
				pCFM_conn_cfg->UDP_chn_cfg[chn_index].recv_Q_size = (GM_UINT32)valueInt;
				pCFM_conn_cfg->UDP_chn_cfg[chn_index].recv_Q_offset = (GM_UINT32)GM_malloc(valueInt * sizeof(GM_RSSP1_com_pri_struct));

				if (NULL == pCFM_conn_cfg->UDP_chn_cfg[chn_index].recv_Q_offset)
				{
					return GM_FALSE;
				}
				GM_memset((void*)pCFM_conn_cfg->UDP_chn_cfg[chn_index].recv_Q_offset, 0, valueInt * sizeof(GM_RSSP1_com_pri_struct));
			}
		}


		rt = GM_Ini_File_Read_Int(section_key, "UDP_send_MQ_size", &valueInt, pIniFileContent);

		if ((GM_FALSE == rt) || (valueInt < 0))
		{
			return GM_FALSE;
		}
		else
		{
			for (chn_index = 0 ; chn_index < pCFM_conn_cfg->chn_num ; ++chn_index)
			{
				pCFM_conn_cfg->UDP_chn_cfg[chn_index].send_Q_size   = (GM_UINT32)valueInt;
				pCFM_conn_cfg->UDP_chn_cfg[chn_index].send_Q_offset = (GM_UINT32)GM_malloc(valueInt * sizeof(GM_RSSP1_com_pri_struct));

				if (NULL == pCFM_conn_cfg->UDP_chn_cfg[chn_index].send_Q_offset)
				{
					return GM_FALSE;
				}
				GM_memset((void*)pCFM_conn_cfg->UDP_chn_cfg[chn_index].send_Q_offset, 0, valueInt * sizeof(GM_RSSP1_com_pri_struct));
			}
		}
	}
    return GM_TRUE;
}

#if 0
GM_BOOL GM_RSSP1_CFM_Init(char *file_path)
{
	GM_RSSP1_CFM_object_struct *pCFM = NULL;
	GM_RSSP1_comm_cfg_struct fsfb_cfg;

	pCFM = GM_RSSP1_Get_CFM_Object();

	if (NULL == file_path)
	{
		return GM_FALSE;
	}

	if (GM_TRUE == GM_RSSP1_Init_Comm_Cfg_CFM(file_path, &fsfb_cfg))
	{
		if (GM_TRUE == GM_RSSP1_CFM_Init_Lib(&fsfb_cfg , pCFM))
		{
			return GM_TRUE;
		}
	}
	return GM_FALSE;
}

#endif

GM_BOOL GM_RSSP1_CFM_Init_CSP(char *pcfg, GM_UINT32 len)
{
	GM_RSSP1_CFM_object_struct *pCFM = NULL;
	GM_RSSP1_comm_cfg_struct fsfb_cfg;

	pCFM = GM_RSSP1_Get_CFM_Object();

	if (NULL == pcfg || len == 0)
	{
		return GM_FALSE;
	}

	if (GM_TRUE == GM_RSSP1_Init_Comm_Cfg_CFM_CSP(pcfg, &fsfb_cfg))
	{
		if (GM_TRUE == GM_RSSP1_CFM_Init_Lib(&fsfb_cfg , pCFM))
		{
			return GM_TRUE;
		}
	}
	return GM_FALSE;
}


GM_BOOL GM_RSSP1_CFM_Init_Lib(GM_RSSP1_comm_cfg_struct *pcfg, GM_RSSP1_CFM_object_struct *pCFM)
{
	GM_RSSP1_CFM_connection_struct *pCFM_con        = NULL;
	GM_RSSP1_CFM_connection_cfg_struct *pConn_cfg   = NULL;
	GM_INT32 conn_index                              = 0;
	GM_INT32 chn_index                           = 0;

	if ((NULL == pcfg) || (NULL == pCFM))
	{
		return GM_FALSE;
	}

	pCFM->lib_state             = GM_RSSP1_Lib_State_Unknown;

	pCFM->connection_nums       = pcfg->CFM_cfg.connection_nums;

	/* init connections */

	for (conn_index = 0 ; conn_index < pCFM->connection_nums ; ++conn_index)
	{
		pConn_cfg               = &(pcfg->CFM_cfg.connection_cfg[conn_index]);
		pCFM_con               = &(pCFM->connection[conn_index]);

		pCFM_con->index        = (GM_UINT8)conn_index;
		pCFM_con->state        = GM_RSSP1_Layer_State_Free;
		pCFM_con->b_enable_CRSCD_pack  = pConn_cfg->b_enable_CRSCD_pack;
		pCFM_con->SaCEPID.source_addr  = pcfg->CFM_cfg.source_addr;
		pCFM_con->SaCEPID.dest_addr    = pConn_cfg->dest_addr;
		pCFM_con->com_type              = pConn_cfg->com_type;
		pCFM_con->chn_num          = pConn_cfg->chn_num;
		pCFM_con->chn_num          = pConn_cfg->chn_num;

		for (chn_index=0; chn_index<pCFM_con->chn_num; ++chn_index)
		{
			pCFM_con->com_chn[chn_index].loc_ip = pConn_cfg->UDP_chn_cfg[chn_index].loc_ip;
			pCFM_con->com_chn[chn_index].rem_ip = pConn_cfg->UDP_chn_cfg[chn_index].rem_ip;
			pCFM_con->com_chn[chn_index].loc_port = pConn_cfg->UDP_chn_cfg[chn_index].loc_port;
			pCFM_con->com_chn[chn_index].rem_port = pConn_cfg->UDP_chn_cfg[chn_index].rem_port;
			pCFM_con->com_chn[chn_index].b_connected = GM_FALSE;

			if (GM_FALSE == FSFB_Msg_Queue_Init(
				&(g_Link_MQ[conn_index].RCV_SND_MQ[chn_index].RCV_MQ),
				pConn_cfg->UDP_chn_cfg[chn_index].recv_Q_size ,
				pConn_cfg->UDP_chn_cfg[chn_index].recv_Q_offset ,
				FSFB_Q_TYPE_RCVD_PKT)
				)
			{
				
				return GM_FALSE;
			}
			else
			{
/*				printf("g_Link_MQ[%d] Init OK size=%d, offset =%d \n", conn_index, pConn_cfg->UDP_chn_cfg[chn_index].recv_Q_size, pConn_cfg->UDP_chn_cfg[chn_index].recv_Q_offset);*/
			}

			if (GM_FALSE == FSFB_Msg_Queue_Init(
				&(g_Link_MQ[conn_index].RCV_SND_MQ[chn_index].SND_MQ),
				pConn_cfg->UDP_chn_cfg[chn_index].send_Q_size ,
				pConn_cfg->UDP_chn_cfg[chn_index].send_Q_offset ,
				FSFB_Q_TYPE_SENT_PKT)
				)
			{
				return GM_FALSE;
			}
		}

	}

	/* init CFM msg queue */

	if (GM_FALSE == FSFB_Msg_Queue_Init(&(g_CFM_MQ.SND_MQ)/*&(pCFM->U2L_pri_Q)*/ , pcfg->CFM_cfg.U2L_pri_Q_size , pcfg->CFM_cfg.U2L_pri_Q_offset , FSFB_Q_TYPE_CFM_U2L_PRI))
	{
		return GM_FALSE;
	}

	if (GM_FALSE == FSFB_Msg_Queue_Init(&(g_CFM_MQ.RCV_MQ)/*&(pCFM->L2U_pri_Q)*/ , pcfg->CFM_cfg.L2U_pri_Q_size , pcfg->CFM_cfg.L2U_pri_Q_offset , FSFB_Q_TYPE_CFM_L2U_PRI))
	{
		return GM_FALSE;
	}

	pCFM->lib_state = GM_RSSP1_Lib_State_Operational;

	return GM_TRUE;
}
#endif
