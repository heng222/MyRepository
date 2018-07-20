/*******************************************
�ļ���	��TsrTransmitStateDataManage.h
����	������
����ʱ�䣺2016-10
����	��ͨ��״̬���ݹ���ͷ�ļ�
��ע	����
*******************************************/
#ifndef TSR_TRANSMIT_STATE_DATA_MANAGE_H_
#define TSR_TRANSMIT_STATE_DATA_MANAGE_H_

#include "../../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*******************************************
������	��GetResReplyToAtsFlag
������������ȡ ��ATS����Ӧ����Ϣ��־
����	����
���	����
����ֵ	��0: ��ȡ����ʧ��
		  0xaau:�յ�ATS�����־ 0x55u:δ�յ�ATS�����־
*******************************************/
extern UINT8_S GetResReplyToAtsFlag();

/*******************************************
������	��SetResReplyToAtsFlag
�������������� ��ATS����Ӧ����Ϣ��־
����	��UINT8_S resReplyToAtsFlag, Ӧ����Ϣ��־
���	����
����ֵ	����
*******************************************/
extern void SetResReplyToAtsFlag(UINT8_S resReplyToAtsFlag);

#ifdef __cplusplus
}
#endif 

#endif