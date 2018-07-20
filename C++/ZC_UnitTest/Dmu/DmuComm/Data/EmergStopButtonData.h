/*************************************************
  �ļ���   ��EmergStopButtonData.h
  ����     ������      
  ����ʱ�� ��2016-8-12
  �������� �� EmergStopButtonData���ݹ���
			DmuCommonData�����EmergStopButtonData���ܿɷֽ����£�
			1��	��EmergStopButtonDataStru�ṹ��ָ�����ռ�
			2��	��ȡEmergStopButtonData����
			3��	��ȡEmergStopButtonData��Ϣ
			4��	��ȡָ��IDEmergStopButtonDataStru�Ľṹ���±�
			5��	��ȡָ��IDEmergStopButtonDataStru�Ľṹ��ָ��
			6��	 ��ȡָ��IDEmergStopButtonDataStru������
			7��	��ȡָ��IDEmergStopButtonDataStru������վ̨���
			8��	��ȡ��·����ͣ����ť���ID
			9��	��ȡ��·����ͣ����ť����վ̨ID
			10��	���������SEGID��ȡESB��Ϣ
			11��	����վ̨ID��ȡ��Ӧ�Ľ���ͣ����ťID
			12��	��ȡ��·����ͣ����ť����ZC
			13��	��ȡ��·����ͣ����ť����ci
  ��ע    ���ޡ�
 
*************************************************/
#ifndef EMERGSTOPBUTTON_DATA_H_
#define EMERGSTOPBUTTON_DATA_H_

#include "../../../Common/CommonTypes.h"

#define EMERGSTOPBUTTON_NAME_BYTE_LEN                 12                                /*���Ƴ���*/
#define EMERGSTOPBUTTON_LINE_BYTE_NUM                 16                                /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*EmergStopButton�����ݽṹ��*/
typedef struct BnfEmergStopButtonStruct
{
    UINT16_S  emergStopButtonId;                                    /*�������*/
    UINT8_S   name[EMERGSTOPBUTTON_NAME_BYTE_LEN];                /*����*/
    UINT16_S  stationId;                                            /*����վ̨���*/

    /*��̬�����ֶ�*/
    UINT16_S  manageZCId;                                            /*����ZC����ID*/
    UINT16_S  manageCIId;                                            /*����CI����ID*/ 
    UINT16_S  segId;                                                /*��ȡSEG������SEGID*/
}BnfEmergStopButtonStruct;

/*
* ���������� ��EmergStopButtonDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocEmergStopButtonDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡEmergStopButtonData����
* ����˵����
* ����ֵ  �� 
            BnfEmergStopButtonStruct*
*/
BnfEmergStopButtonStruct *GetEmergStopButtonData(void);

/*
* ���������� ��ȡEmergStopButtonData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfEmergStopButtonStruct*
*/
BnfEmergStopButtonStruct *GetEmergStopButtonDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDEmergStopButtonDataStru�Ľṹ���±�
* ����˵���� const UINT16_S emergStopButtonId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetEmergStopButtonDataStruIndex(const UINT16_S emergStopButtonId);

/*
** ���������� ��ȡָ��IDEmergStopButtonDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S emergStopButtonId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfEmergStopButtonStruct* GetIndexIdEmergStopButtonDataStru(const UINT16_S emergStopButtonId);

/*
** ���������� ��ȡָ��IDEmergStopButtonDataStru������
* ����˵���� const UINT16_S emergStopButtonId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ����
*/ 
UINT8_S* GetEmergStopButtonDataStruname(const UINT16_S emergStopButtonId);

/*
** ���������� ��ȡָ��IDEmergStopButtonDataStru������վ̨���
* ����˵���� const UINT16_S emergStopButtonId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����վ̨���
*/ 
UINT16_S GetEmergStopButtonDataStrustationId(const UINT16_S emergStopButtonId);
/*
* ���������� ��ȡ��·����ͣ����ť���ID
* ����˵���� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:����ͣ����ť���ID
*/
UINT16_S GetLineEsbMaxId(void);

/*
* ���������� ��ȡ��·����ͣ����ť����վ̨ID
* ����˵���� const UINT16_S esbId,����ͣ����ťID
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:����վ̨ID
*/
UINT16_S GetLineEsbBelongStationId(const UINT16_S esbId);

/*
** ���������� ���������SEGID��ȡESB��Ϣ
* ����˵���� ����:const UINT16_S stationIdBuff,վ̨ID
*             const UINT8_S stationIdNum    վ̨ID����
*             UINT16_S index*    ����ƫ��                  
*             �������:UINT16_S esbIdBuff[],ESBID����      
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ESB��Ϣ
*/ 
UINT16_S GetStationIdBelongofEsbInfo(const UINT16_S* stationIdBuff,const UINT8_S stationIdNum,UINT16_S index,UINT16_S esbIdBuff[]);

/*
** ���������� ����վ̨ID��ȡ��Ӧ�Ľ���ͣ����ťID
* ����˵���� const UINT16_S pPlatformId;վ̨ID
*             const UINT8_S platformNum  վ̨ID����
*             UINT16_S*  pPsdId          ������IDָ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����ͣ����ť����
*/ 
UINT8_S GetEsbIdAccordPlatformIdBuff(const UINT16_S* pPlatformId,const UINT8_S platformNum,UINT16_S* pEsbId);

/*
* ���������� ��ȡ��·����ͣ����ť����ZC
* ����˵���� const UINT16_S esbId,����ͣ����ťID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����ZCId
*/
UINT16_S GetLineEsbBelongZcId(const UINT16_S esbId);

/*
* ���������� ��ȡ��·����ͣ����ť����ci
* ����˵���� const UINT16_S esbId,����ͣ����ťID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����ciId
*/
UINT16_S GetLineEsbBelongCiId(const UINT16_S esbId);

#ifdef __cplusplus
}
#endif

#endif
