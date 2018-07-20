/*******************************************
�ļ���	��TsrInterface.h
���ߣ�����
����ʱ�䣺2016-10
������TSR�ӿ�
��ע����
*******************************************/

#ifndef TSR_INTERFACE_H_
#define TSR_INTERFACE_H_

#include "../../Common/CommonTypes.h"
#include "TsrSystem/TsrSystemDefine.h"
#include "TsrParserPacker/TsrParsePackInterface.h"
#include "TsrIO/TsrInputDataProcess.h"
#include "TsrIO/TsrOutputDataProcess.h"
#include "TsrInitialization/InitialProcess.h"
#include "TsrSystem/TsrSysStatusData.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*******************************************
������	��TsrInit
����������Tsr��ʼ������
����	����
���	����
����ֵ	��0:��ʼ��ʧ�ܣ�1����ʼ���ɹ���
*******************************************/
extern UINT8_S TsrInit(void);

/*******************************************
������	: TsrIFGetZcWorkState
������������ȡ����״̬
����	����
���	����
����ֵ	��ZC����״̬
*******************************************/
extern UINT8_S TsrIFGetZcWorkState(void);

/*******************************************
������	: TsrIFSetZcWorkState
�������������ù���״̬
����	����
���	����
����ֵ	����
*******************************************/
extern void TsrIFSetZcWorkState(UINT8_S workState);

/*******************************************
������	��ParseTsrCommandsFromAts
��������������ATS����������
����	����
���	����
����ֵ	��retVal�ɹ����������ݰ�������
*******************************************/
extern UINT8_S ParseTsrCommandsFromAts(void);

/*******************************************
������	��ProcessTsrCommandsFromAts
�������������� ATS��������
����	����
���	����
����ֵ	��0:����ʧ��,1:����ɹ�
*******************************************/
extern UINT8_S ProcessTsrCommandsFromAts(void);

/*******************************************
������	��ProcessTsrCommandsToAts
�������������� �ظ���Ats����
����	����
���	����
����ֵ	��0��ʧ�ܣ�1���ɹ�
*******************************************/
extern UINT8_S ProcessTsrCommandsToAts(void);

/*******************************************
������	��PackTsrCommandsToAts
�������������ATS�������
����	����
���	����
����ֵ	����
*******************************************/

extern void PackTsrCommandsToAts(void);

#ifdef __cplusplus
}
#endif

#endif