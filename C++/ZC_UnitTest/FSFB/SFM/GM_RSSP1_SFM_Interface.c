#include "GM_RSSP1_SFM_Interface.h"


/*接收过程 先CFM，再SFM*/

void GM_RSSP1_SFM_Interface_Proc_Recv(void)
{
	GM_RSSP1_SFM_object_struct *pSFM = NULL;
	pSFM = GM_RSSP1_Get_SFM_Object();

	if ((NULL == pSFM))
	{
		return;
	}

	if (GM_RSSP1_Lib_State_Operational != pSFM->lib_state)
	{
		return;
	}

	GM_RSSP1_SFM_Process_CFM_Ind(pSFM);/*该函数直接将从CFM队列处理接收消息，拆分中间队列*/


	/* jianghongjun 20100618 调整GM_RSSP1_SFM_Dispatch_Dat_Indi与GM_RSSP1_SFM_Proc_Connection_Monit_And_Tolerate调用顺序，应该先宽恕，后分发各通道数据。 */
	GM_RSSP1_SFM_Proc_Connection_Monit_And_Tolerate(pSFM);
	GM_RSSP1_SFM_Dispatch_Dat_Indi(pSFM);

	GM_RSSP1_SFM_Update_Time(pSFM);
}

/*发送过程 先SFM，再CFM*/

void GM_RSSP1_SFM_Interface_Proc_Send(void)
{
	GM_RSSP1_SFM_object_struct *pSFM = NULL;

	pSFM = GM_RSSP1_Get_SFM_Object();

	if (NULL == pSFM)
	{
		return;
	}

	if (GM_RSSP1_Lib_State_Operational != pSFM->lib_state)
	{
		return;
	}

	GM_RSSP1_SFM_Reset_Connection_RSD_Sent_Flag(pSFM);

	GM_RSSP1_SFM_Process_User_Req(pSFM);

	return;
}
