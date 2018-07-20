/*******************************************
�ļ���	��TsrOutputDataProcess.h
����	������
����ʱ�䣺2016-10
����	������������
��ע	����
*******************************************/

#ifndef TSR_OUTPUT_DATA_PROCESS_H_
#define TSR_OUTPUT_DATA_PROCESS_H_

#include "../../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************
������	��ProcessReplyToAtsData
�������������� �ظ���Ats����
����	����
���	����
����ֵ	��0��ʧ�ܣ�1���ɹ�
*******************************************/
extern UINT8_S ProcessReplyToAtsData(void);

/*******************************************
������	��GetAutoReplyToAtsFlag
������������ȡ������ATS�㱨��־
����	����
���	����
����ֵ	��0�����ڲ��㱨��1�����ڻ㱨
*******************************************/
extern UINT8_S GetAutoReplyToAtsFlag(void);

/*******************************************
������	��SetAutoReplyToAtsFlag
��������������������ATS�㱨��־
����	��UINT8_S replayTime,0�����ڲ��㱨��1�����ڻ㱨
���	����
����ֵ	����
*******************************************/
extern void SetAutoReplyToAtsFlag(UINT8_S replayTime);

#ifdef __cplusplus
}
#endif

#endif
