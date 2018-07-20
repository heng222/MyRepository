/**
* @file SYNC_INTERCOMM_Init.c
* @brief 双系同步初始化头文件初始化实现文件
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


#include "SYNC_INTERCOMM_Init.h"
#include "SYNC_INTERCOMM_Def.h"
#include "..\cspadpt\Vcp_Service_Interface.h"
#include <fscSl.h>

static GM_BOOL g_bSYNCINTERCOMMInit = GM_FALSE;
static GM_INT32 g_slFd = 0U;

/**
* @brief 系间同步 初始化接口
*
* Detailed description.
* @param[in] void
* @return GM_BOOL
*/
GM_BOOL SYNC_INTERCOMM_Init(void)
{
	int i = 0;
	INTERCOMM_transport_config_struct	szAddrCfg;
	SYNC_INTERCOM_Cfg_struct* pCfg = NULL;
	char* ip1 = "192.168.2.1";
	char* ip2 = "192.168.2.11";
	UINT32 mSysID = 0;

	pCfg = SYNC_INTERCOMM_Get_Sync_Intercomm_Cfg();	
	

	if (NULL == pCfg)
	{
		return GM_FALSE;
	}
	if (GM_TRUE == g_bSYNCINTERCOMMInit)
	{
		return GM_TRUE;
	}

	GM_memset((void*)&szAddrCfg, 0x00, (size_t)(sizeof(szAddrCfg)));
	/***
	* IO与CPU通信控制器通信通道地址参数，以IO作为本端，以CPU作为远端
	***/
	F_VCP_GetSystemId(&mSysID);
	
    if(mSysID == 1U)
	{
	  GM_memcpy((void*)(szAddrCfg.local_ip), (void*)ip1, (size_t)(strlen("192.168.2.1")));
	  GM_memcpy((void*)(szAddrCfg.remote_ip), (void*)ip2, (size_t)(strlen("192.168.2.11")));
	}		
    else
	{
	  GM_memcpy((void*)(szAddrCfg.local_ip), (void*)ip2, (size_t)(strlen("192.168.2.11")));
	  GM_memcpy((void*)(szAddrCfg.remote_ip), (void*)ip1, (size_t)(strlen("192.168.2.1")));
	}

	szAddrCfg.local_port = 10010;
	szAddrCfg.local_addr.sin_family = AF_INET;
	szAddrCfg.local_addr.sin_addr.s_addr = inet_addr((char*)szAddrCfg.local_ip);
	szAddrCfg.local_addr.sin_port = htons(szAddrCfg.local_port);
	
	szAddrCfg.remote_port = 10010;
	szAddrCfg.remote_addr.sin_family = AF_INET;
	szAddrCfg.remote_addr.sin_addr.s_addr = inet_addr((char*)szAddrCfg.remote_ip);
	szAddrCfg.remote_addr.sin_port = htons(szAddrCfg.remote_port);


	GM_memset((void*)pCfg, 0x00, (size_t)(sizeof(SYNC_INTERCOM_Cfg_struct)));

	pCfg->type = (INTERCOMM_Type_Enum)GM_RSSP1_INTERCOMM_Type_CPUB;
	
	pCfg->chnl_Sync[0].sock = GM_RSSP1_INVALID_SOCKET;
	pCfg->chnl_Sync[0].max_socket_value = 0U;
	pCfg->chnl_Sync[0].timeout_cycle = 0U;		
	pCfg->chnl_Sync[0].addr_cfg = szAddrCfg;		
	pCfg->chnl_Sync[0].InDataLen = 0U;		
	pCfg->chnl_Sync[0].pInData = (UINT8*)(GM_malloc(1024U*200U));
	pCfg->chnl_Sync[0].OutDataLen = 0U;		
	pCfg->chnl_Sync[0].pOutData = (UINT8*)(GM_malloc(1024U*200U));

/*    SYNC_INTERCOMM_Csp_Safety_Layer_Reg();	*/
	g_bSYNCINTERCOMMInit = GM_TRUE;

	return GM_TRUE;
}

/**
* @brief 系间同步 CSP Safety Layer注册
*
* Detailed description.
* @param[in] void
* @return void
*/
void SYNC_INTERCOMM_Csp_Safety_Layer_Reg(void)
{
	GM_INT32 slFd;
	FSCSL_REG slReg;
	struct in_addr *laddr = (struct in_addr *)(&(slReg.ipAddr));
	int arg = 0;
	int fun = 0;
	char* dev = (char*)FSCSL_DEVNAME;
	printf("SYNC_INTERCOMM_Csp_Safety_Layer_Reg starting\n");
	slFd = open(dev,0,0);
	g_slFd = slFd;
	UINT32 mSysID=0U;
	
	F_VCP_GetSystemId(&mSysID);
	
    if(mSysID == 1U)
	{	
	 inet_aton("192.168.2.11",laddr);
	}
	else
	{
	 inet_aton("192.168.2.1",laddr);
	}
	slReg.transType = FSCSL_TT_CYCLIC;
	slReg.maxDeltaTMsec = 2000U + 250U;  /*ms*/
	arg = (int)(&slReg);
	fun = (int)FSCSL_IOC_REGISTER;
	ioctl((int)slFd,fun,arg);
	printf("SYNC_INTERCOMM_Csp_Safety_Layer_Reg end\n");	
}
/**
* @brief 系间同步 CSP Safety Layer收发信息统计
*
* Detailed description.
* @param[in] void
* @return void
*/
void SYNC_INTERCOMM_Csp_Safety_Layer_Statistics(void)
{

	FSCSL_STATS slStats;
	int arg = 0;
	int fun = 0;
	
	if(g_slFd == 0)
		return;
   	
	fun = (int)FSCSL_IOC_GET_STATISTICS;
	arg = (int)(&slStats);
	ioctl((int)g_slFd,fun,arg);
	
	printf("SafetyLayer,%d,%d\n", slStats.numNonIPv4pktsIn, slStats.numNonIPv4pktsOut);
	

		
}

/**
* @brief 系间同步 判断初始化是否完成
*
* Detailed description.
* @param[in] void
* @return GM_BOOL
*/
GM_BOOL SYNC_INTERCOMM_Init_Finished()
{
	return g_bSYNCINTERCOMMInit;
}
