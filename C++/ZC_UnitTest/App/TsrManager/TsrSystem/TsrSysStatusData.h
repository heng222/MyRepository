/*******************************************
�ļ���	��TsrSysStatusData.h
����	������
����ʱ�䣺2016-10
����	��ϵͳ״̬���ݹ���
��ע	����
*******************************************/

#ifndef TSR_SYS_STATUS_DATA_H_
#define TSR_SYS_STATUS_DATA_H_
#include "../../../Common/CommonTypes.h"
#include "TsrSystemDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************
������	: GetZcWorkState
������������ȡ����״̬
����	����
���	����
����ֵ	��ZC����״̬
*******************************************/
extern UINT8_S GetZcWorkState(void);

/*******************************************
������	: SetZcWorkState
�������������ù���״̬
����	����
���	����
����ֵ	����
*******************************************/
extern void SetZcWorkState(UINT8_S workState);

#ifdef __cplusplus
}
#endif
#endif