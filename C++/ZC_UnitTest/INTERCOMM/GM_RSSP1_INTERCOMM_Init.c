/**
* @file GM_RSSP1_INTERCOMM_Init.c
* @brief 联锁安全平台内外网通信控制器初始化实现文件
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

#include "GM_RSSP1_INTERCOMM_Init.h"
#include "GM_RSSP1_INTERCOMM_Def.h"

static GM_BOOL g_bINTERCOMMInit = GM_FALSE;

/**
* @brief 内网通信初始化 
*
* Detailed description.
* @return GM_BOOL
*
*/

GM_BOOL GM_RSSP1_INTERCOMM_Init(INTERCOM_Cfg_struct* pINTERCOMM, int type)
{
	int i = 0U;
	UINT32 mSysID=0U;
	INTERCOMM_transport_config_struct	szAddrCfg[GM_RSSP1_MAX_LINK_CHANNEL];
	F_VCP_GetSystemId(&mSysID);
    if ((NULL == pINTERCOMM) || (!GM_RSSP1_INTERCOMM_Type_Vaild(type)))
    {
        return GM_FALSE;
    }
    if (GM_TRUE == g_bINTERCOMMInit)
    {
        return GM_TRUE;
    }

    GM_memset((void *)szAddrCfg, 0x00U, (size_t)(sizeof(szAddrCfg)));
    /***
    * IO与CPU通信控制器通信通道地址参数，以IO作为本端，以CPU作为远端
    ***/
	/*??CSP???????VCP ?? ???*/
    if(mSysID == 1U)
	{
	  GM_memcpy(szAddrCfg[0].local_ip, "192.168.2.8", strlen("192.168.2.8"));		
	}		
    else
	{
	  GM_memcpy(szAddrCfg[0].local_ip, "192.168.2.18", strlen("192.168.2.18"));				
	}

    szAddrCfg[0U].local_port = 10001U;
    szAddrCfg[0U].local_addr.sin_family = AF_INET;
    szAddrCfg[0U].local_addr.sin_addr.s_addr = inet_addr(szAddrCfg[0U].local_ip);
    szAddrCfg[0U].local_addr.sin_port = htons((int)(szAddrCfg[0U].local_port));


    if(mSysID == 1U)
	{
	   GM_memcpy(szAddrCfg[0].remote_ip, "192.168.2.1", strlen("192.168.2.1"));	
	}		
    else
	{
	   GM_memcpy(szAddrCfg[0].remote_ip, "192.168.2.11", strlen("192.168.2.11"));		
	}	
	
    szAddrCfg[0U].remote_port = 20001U;
    szAddrCfg[0U].remote_addr.sin_family = AF_INET;
    szAddrCfg[0U].remote_addr.sin_addr.s_addr = inet_addr(szAddrCfg[0U].remote_ip);
    szAddrCfg[0U].remote_addr.sin_port = htons((int)(szAddrCfg[0U].remote_port));


    if(mSysID == 1U)
	{
	   GM_memcpy(szAddrCfg[1].local_ip, "192.168.2.8", strlen("192.168.2.8"));
	}		
    else
	{
	   GM_memcpy(szAddrCfg[1].local_ip, "192.168.2.18", strlen("192.168.2.18"));	
	}	
	
    szAddrCfg[1U].local_port = 10002U;
    szAddrCfg[1U].local_addr.sin_family = AF_INET;
    szAddrCfg[1U].local_addr.sin_addr.s_addr = inet_addr(szAddrCfg[1U].local_ip);
    szAddrCfg[1U].local_addr.sin_port = htons((int)(szAddrCfg[1U].local_port));


    if(mSysID == 1U)
	{
	   GM_memcpy(szAddrCfg[1].remote_ip, "192.168.2.1", strlen("192.168.2.1"));	   
	}		
    else
	{
	   GM_memcpy(szAddrCfg[1].remote_ip, "192.168.2.11", strlen("192.168.2.11"));	   	   
	}	
    szAddrCfg[1U].remote_port = 20002U;
    szAddrCfg[1U].remote_addr.sin_family = AF_INET;
    szAddrCfg[1U].remote_addr.sin_addr.s_addr = inet_addr(szAddrCfg[1U].remote_ip);
    szAddrCfg[1U].remote_addr.sin_port = htons((int)(szAddrCfg[1U].remote_port));

    GM_memset((void *)pINTERCOMM, 0x00U, (size_t)(sizeof(INTERCOM_Cfg_struct)));

	pINTERCOMM->type = (INTERCOMM_Type_Enum)type;
	for (i = 0; i < GM_RSSP1_MAX_LINK_CHANNEL; i++)
	{
		GM_BOOL bRet = GM_FALSE;

		/***
		* IO板通信控制器数据初始化
		***/
		bRet = GM_MQ_Fixed_Init(&(pINTERCOMM->chnl_IOB[i].stInDataQ));
		if (bRet != GM_TRUE)
		{
			return GM_FALSE;
		}	
		bRet = GM_MQ_Fixed_Init(&(pINTERCOMM->chnl_IOB[i].stOutDataQ));
		if (bRet != GM_TRUE)
		{
			return GM_FALSE;
		}
		pINTERCOMM->chnl_IOB[i].sock = GM_RSSP1_INVALID_SOCKET;
		pINTERCOMM->chnl_IOB[i].max_socket_value = 0;
		pINTERCOMM->chnl_IOB[i].addr_cfg = szAddrCfg[i];

		/***
		* CPU板通信控制器数据初始化
		***/
		bRet = GM_MQ_Fixed_Init(&(pINTERCOMM->chnl_CPUB[i].stInDataQ));
		if (bRet != GM_TRUE)
		{
			return GM_FALSE;
		}

		bRet = GM_MQ_Fixed_Init(&(pINTERCOMM->chnl_CPUB[i].stOutDataQ));
		if (bRet != GM_TRUE)
		{
			return GM_FALSE;
		}
		pINTERCOMM->chnl_CPUB[i].sock = GM_RSSP1_INVALID_SOCKET;
		pINTERCOMM->chnl_CPUB[i].max_socket_value = 0;

        GM_memcpy(((void *)(pINTERCOMM->chnl_CPUB[i].addr_cfg.local_ip)), ((const void *)(szAddrCfg[i].remote_ip)), (size_t)sizeof(szAddrCfg[i].remote_ip));
        pINTERCOMM->chnl_CPUB[i].addr_cfg.local_port = szAddrCfg[i].remote_port;
        pINTERCOMM->chnl_CPUB[i].addr_cfg.local_addr = szAddrCfg[i].remote_addr;
        GM_memcpy(((void *)(pINTERCOMM->chnl_CPUB[i].addr_cfg.remote_ip)), ((const void *)(szAddrCfg[i].local_ip)), (size_t)sizeof(szAddrCfg[i].local_ip));
        pINTERCOMM->chnl_CPUB[i].addr_cfg.remote_port = szAddrCfg[i].local_port;
        pINTERCOMM->chnl_CPUB[i].addr_cfg.remote_addr = szAddrCfg[i].local_addr;
    }

	g_bINTERCOMMInit = GM_TRUE;

	return GM_TRUE;
}

/**
* @brief 内网通信类型判断 
*
* Detailed description.
* @return GM_BOOL
*
*/

GM_BOOL GM_RSSP1_INTERCOMM_Type_Vaild(int type)
{
	if (GM_RSSP1_INTERCOMM_Type_IOB == type || GM_RSSP1_INTERCOMM_Type_CPUB == type)
	{
		return GM_TRUE;
	}

	return GM_FALSE;
}

/**
* @brief 内网通信初始化结束 
*
* Detailed description.
* @return GM_BOOL
*
*/

GM_BOOL GM_RSSP1_INTERCOMM_Init_Finished()
{
	return g_bINTERCOMMInit;
}

/**
* @brief 获取内网通信结构体 
*
* Detailed description.
* @return GM_BOOL
*
*/

INTERCOM_Cfg_struct* GM_RSSP1_INTERCOMM_Get_Stru()
{
	return &g_stINTERCOMM;
}
