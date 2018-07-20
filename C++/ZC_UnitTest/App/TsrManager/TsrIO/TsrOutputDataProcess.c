/*******************************************
�ļ���	��TsrOutputDataProcess.c
����	������
����ʱ�䣺2016-10
����	������������
��ע	����
*******************************************/

#include "TsrOutputDataProcess.h"
#include "../TsrTransmitFlagAdmin/TsrTransmitStateDataManage.h"
#include "../TsrParserPacker/TsrParsePackAtsData.h"
#include "../TsrParserPacker/ParsePackInterfaceDefine.h"
#include "../TsrSystem/TsrSysStatusData.h"
#include "../TsrSystem/TsrSysConfigData.h"
/*#include "../TsrMaintenance/MaintainManager.h" */
#include "../../../Common/MemSet.h"
#include "../../SysDataManager/SysStatusData.h"

static UINT8_S g_AutoReplyToAtsFlag = DEFAULT_ZERO;/*������ATS�㱨��־:0�����ڲ��㱨��1�����ڻ㱨*/

/*******************************************
������	��GetAutoReplyToAtsFlag
������������ȡ������ATS�㱨��־
����	����
���	����
����ֵ	��0�����ڲ��㱨��1�����ڻ㱨
*******************************************/
UINT8_S GetAutoReplyToAtsFlag(void)
{
	return g_AutoReplyToAtsFlag;
}

/*******************************************
������	��SetAutoReplyToAtsFlag
��������������������ATS�㱨��־
����	��UINT8_S replayTime,0�����ڲ��㱨��1�����ڻ㱨
���	����
����ֵ	����
*******************************************/
void SetAutoReplyToAtsFlag(UINT8_S replayTime)
{
	g_AutoReplyToAtsFlag = replayTime;
}

/*******************************************
������	��ProcessReplyToAtsData
��������������ظ���Ats����
����	����
���	����
����ֵ	��0��ʧ�ܣ�1���ɹ�
*******************************************/
UINT8_S ProcessReplyToAtsData()
{
	UINT32_S zcCycle = DEFAULT_ZERO;
	UINT16_S replyToAtsCycle = DEFAULT_ZERO;
	Tsr_DataStru_Set_Stru* pTmpTsrSetData = NULL;

	zcCycle = GetZcCycle();
	pTmpTsrSetData = GetTsrDataAdmin();

	if (ZC_WORK_POP == GetZcWorkState())/*�ϵ�*/
	{
		SetReplyToAtsAutoCmdValue(ZC_TO_ATS_TSR_RESET_REPORT);
		WriteReplyToAtsData(pTmpTsrSetData);/*����ʱ���ٹ�����Ϣ��д����ATS������ʱ���ٽṹ����*/
		SetAutoReplyToAtsFlag(AUTO_REPLYTO_ATS);/*��ʼ�ϵ�״̬��Ҫ�����ظ�ATS��Ϣ,����������㱨TSR*/
	}
	else if (ZC_WORK_NORMAL == GetZcWorkState())
	{
		replyToAtsCycle = GetPeriodsDuringAutoReplyTsrToAts(); 

		if ((DEFAULT_ZERO != replyToAtsCycle)
			        &&(DEFAULT_ZERO == (zcCycle % replyToAtsCycle))
					         &&(DEFAULT_ZERO != zcCycle))/*�ظ����ڵ�*/
		{
			SetReplyToAtsAutoCmdValue(ZC_TO_ATS_TSR_NORMAL_REPORT);
			WriteReplyToAtsData(pTmpTsrSetData);/*������ʱ������Ϣ*/
			SetAutoReplyToAtsFlag(AUTO_REPLYTO_ATS);/*�ظ����ڵ���Ҫ�����ظ�ATS��Ϣ�����������㱨TSR*/
			SetReplyToAtsAutoCmdValue(ZC_TO_ATS_TSR_NORMAL_REPORT);
		}
		else
		{
			/*������*/
		}

	}
	else
	{
		/*������*/
	}

	return TSR_SUCCESS;
}



