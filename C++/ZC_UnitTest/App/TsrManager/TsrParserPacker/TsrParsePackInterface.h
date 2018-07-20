/*******************************************
�ļ���	��TsrParsePackInterface.h
����	������
����ʱ�䣺2016-10
����	���������
��ע	����
*******************************************/
#ifndef TSR_PARSEPACK_INTERFACE_H
#define TSR_PARSEPACK_INTERFACE_H

#include "../../../Common/CommonTypes.h"
#include "../TsrSystem/TsrSystemDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ATS_FRAME_OFFSET 0
#define ZC_FRAME_OFFSET 0
#define NTP_FRAME_OFFSET 0
/*******************************************
������	��Tsr_ParseIncomingDatas
���������������ⲿͨ���豸����������
����	����
���	����
����ֵ	��retVal�ɹ����������ݰ�������
*******************************************/
extern UINT8_S Tsr_ParseIncomingDatas(void);

/*******************************************
������	��Tsr_PackOutletDatas
�������������ATS�������
����	����
���	����
����ֵ	����
*******************************************/

extern void Tsr_PackOutletDatas(void);

#ifdef __cplusplus
}
#endif


#endif

