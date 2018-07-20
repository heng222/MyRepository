/*******************************************
�ļ���	��TsrTransmitStateDataManage.c
����	������
����ʱ�䣺2016-10
����	��ͨ��״̬���ݹ����ļ�
��ע	����
*******************************************/

#include "TsrTransmitStateDataManage.h"
#include "../TsrSystem/TsrSystemDefine.h"
#include "../TsrSystem/TsrSysConfigData.h"
/*#include "../TsrMaintenance/MaintainManager.h"*/
/*#include "../TsrMaintenance/EventCode.h"			*/
#include "../../../Common/MemSet.h"

static UINT8_S  g_ResReplyToAtsFlag = ANTI_RES_REPLYTO_ATS;/*��ATS����Ӧ����Ϣ��־����*/

/*******************************************
������	��GetResReplyToAtsFlag
������������ȡ ��ATS����Ӧ����Ϣ��־
����	����
���	����
����ֵ	��0: ��ȡ����ʧ��
		  0xaau:�յ�ATS�����־ 0x55u:δ�յ�ATS�����־
*******************************************/
UINT8_S GetResReplyToAtsFlag()
{
	return g_ResReplyToAtsFlag;
}


/*******************************************
������	��SetResReplyToAtsFlag
�������������� ��ATS����Ӧ����Ϣ��־
����	��UINT8_S resReplyToAtsFlag, Ӧ����Ϣ��־
���	����
����ֵ	����
*******************************************/
void SetResReplyToAtsFlag(UINT8_S resReplyToAtsFlag)
{
	g_ResReplyToAtsFlag = resReplyToAtsFlag;
}