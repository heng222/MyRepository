#include "GM_RSSP1_SFM_Interface.h"


/*���չ��� ��CFM����SFM*/

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

	GM_RSSP1_SFM_Process_CFM_Ind(pSFM);/*�ú���ֱ�ӽ���CFM���д��������Ϣ������м����*/


	/* jianghongjun 20100618 ����GM_RSSP1_SFM_Dispatch_Dat_Indi��GM_RSSP1_SFM_Proc_Connection_Monit_And_Tolerate����˳��Ӧ���ȿ�ˡ����ַ���ͨ�����ݡ� */
	GM_RSSP1_SFM_Proc_Connection_Monit_And_Tolerate(pSFM);
	GM_RSSP1_SFM_Dispatch_Dat_Indi(pSFM);

	GM_RSSP1_SFM_Update_Time(pSFM);
}

/*���͹��� ��SFM����CFM*/

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
