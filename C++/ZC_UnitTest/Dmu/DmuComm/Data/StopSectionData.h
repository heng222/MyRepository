/*************************************************
  �ļ���   ��StopSectionData.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� StopSectionData���ݹ���
			DmuCommonData�����StopSectionData���ܿɷֽ����£�
			1��	��StopSectionDataStru�ṹ��ָ�����ռ�
			2��	��ȡStopSectionData����
			3��	��ȡStopSectionData��Ϣ
			4��	��ȡָ��IDStopSectionDataStru�Ľṹ���±�
			5��	��ȡָ��IDStopSectionDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDStopSectionDataStru��������վ����
			7��	��ȡָ��dstCode��������վ����
			8��	��ȡָ��IDStopSectionDataStru��Ŀ�ĵر��
			9��	��ȡָ��IDStopSectionDataStru��ͣ������seg���
			10��	��ȡָ��IDStopSectionDataStru��ͣ����������
			11��	��ȡָ��IDStopSectionDataStru��վ̨��Сͣվʱ��
			12��	��ȡָ��IDStopSectionDataStru��վ̨���ͣվʱ��
			13��	��ȡָ��IDStopSectionDataStru��վ̨Ĭ��ͣվʱ��
			14��	��ȡָ��IDStopSectionDataStru��վ̨���ŷ�ʽ
			15��	��ȡָ��IDStopSectionDataStru��վ̨����ʱ����
			16��	��ȡָ��IDStopSectionDataStru��վ̨���ŷ�ʽ
			17��	��ȡָ��IDStopSectionDataStru��վ̨����ʱ����
			18��	��ȡָ��IDStopSectionDataStru��վ̨Ĭ��ͣ��ʱ��
			19��	��ѯĳ�����Ƿ�����ת����
			20��	��ȡָ��λ�õ�ͣ����������
			21��	��ȡָ��λ�õ�ͣ������ID
			22��	��ȡָ��λ�õ�ͣ��������Ϣ
  ��ע    ���ޡ�
 
*************************************************/
#ifndef STOPSECTION_DATA_H_
#define STOPSECTION_DATA_H_

#include "../../../Common/CommonTypes.h"

#define STOPSECTION_STATION_NAME_LEN                  20                                                       /*�����ֽ���*/
#define STOPSECTION_DEST_CODE_LEN                         4                                                       /*Ŀ�ĵر�ų���*/
#define STOPSECTION_LINE_BYTE_NUM                      46                                                    /*һ�������ֽ���*/
#define STOPSECTION_MAX_PSD_NUM                        0x02                                                    /*ͬʱ��Ҫ���Ƶ�PSD�������,����һ��վ̨������PSD,���Զ���Ϊ2*/



#ifdef __cplusplus
extern "C" {
#endif

/*ͣ�������*/
typedef struct BnfStopSectionStruct
{
    UINT16_S  stopSectionId;                                                /*�������*/                    
    UINT8_S   stationName[STOPSECTION_STATION_NAME_LEN];                    /*������վ����*/
    UINT8_S   bDesId[STOPSECTION_DEST_CODE_LEN];                            /*Ŀ�ĵر��*/
    UINT16_S  segId;                                                        /*ͣ������seg���*/
    UINT16_S  sttribute;                                                    /*ͣ����������*/
    UINT16_S  minParkTime;                                                   /*վ̨��Сͣվʱ��*/
    UINT16_S  maxParkTime;                                                   /*վ̨���ͣվʱ��*/
    UINT16_S  parkTime;                                                    /*վ̨Ĭ��ͣվʱ��*/
    UINT16_S  doorOpenMode;                                                /*վ̨���ŷ�ʽ*/
    UINT16_S  doorOpenTime;                                                /*վ̨����ʱ����*/
    UINT16_S  doorCloseMode;                                                /*վ̨���ŷ�ʽ*/
    UINT16_S  doorCloseTime;                                                /*վ̨����ʱ����*/
    UINT16_S  parkSteadyTime;                                                /*վ̨Ĭ��ͣ��ʱ��*/

    
    /*��̬�����ֶ�*/
    UINT8_S  psdNum;                                                        /*վ̨������������*/
    UINT16_S  psdId[STOPSECTION_MAX_PSD_NUM];                                /*��ȫ�����ű��*/
    UINT16_S  manageZCId;                                                    /*����ZC����ID*/
    UINT16_S  manageCIId;                                                    /*����CI����ID*/ 
}BnfStopSectionStruct;

/*
* ���������� ��StopSectionDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocStopSectionDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡStopSectionData����
* ����˵����
* ����ֵ  �� 
            BnfStopSectionStruct*
*/
BnfStopSectionStruct *GetStopSectionData(void);

/*
* ���������� ��ȡStopSectionData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfStopSectionStruct*
*/
BnfStopSectionStruct *GetStopSectionDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDStopSectionDataStru�Ľṹ���±�
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetStopSectionDataStruIndex(const UINT16_S stopSectionId);

/*
** ���������� ��ȡָ��IDStopSectionDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfStopSectionStruct* GetIndexIdStopSectionDataStru(const UINT16_S stopSectionId);

/*
** ���������� ��ȡָ��IDStopSectionDataStru��������վ����
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ������վ����
*/ 
UINT8_S* GetStopSectionDataStrustationName(const UINT16_S stopSectionId);

/*
** ���������� ��ȡָ��dstCode��������վ����
* ����˵���� const UINT16_S dstCode;
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ������վ����
*/ 
UINT8_S* GetStopSecNameByDstCode(const UINT16_S dstCode);


/*
** ���������� ��ȡָ��IDStopSectionDataStru��Ŀ�ĵر��
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: Ŀ�ĵر��
*/ 
UINT8_S* GetStopSectionDataStrubDesId(const UINT16_S stopSectionId);

/*
** ���������� ��ȡָ��IDStopSectionDataStru��ͣ������seg���
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ͣ������seg���
*/ 
UINT16_S GetStopSectionDataStrusegId(const UINT16_S stopSectionId);

/*
** ���������� ��ȡָ��IDStopSectionDataStru��ͣ����������
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ͣ����������
*/ 
UINT16_S GetStopSectionDataStrusttribute(const UINT16_S stopSectionId);

/*
** ���������� ��ȡָ��IDStopSectionDataStru��վ̨��Сͣվʱ��
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨��Сͣվʱ��
*/ 
UINT16_S GetStopSectionDataStruminParkTime(const UINT16_S stopSectionId);

/*
** ���������� ��ȡָ��IDStopSectionDataStru��վ̨���ͣվʱ��
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨���ͣվʱ��
*/ 
UINT16_S GetStopSectionDataStrumaxParkTime(const UINT16_S stopSectionId);

/*
** ���������� ��ȡָ��IDStopSectionDataStru��վ̨Ĭ��ͣվʱ��
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨Ĭ��ͣվʱ��
*/ 
UINT16_S GetStopSectionDataStruparkTime(const UINT16_S stopSectionId);

/*
** ���������� ��ȡָ��IDStopSectionDataStru��վ̨���ŷ�ʽ
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨���ŷ�ʽ
*/ 
UINT16_S GetStopSectionDataStrudoorOpenMode(const UINT16_S stopSectionId);

/*
** ���������� ��ȡָ��IDStopSectionDataStru��վ̨����ʱ����
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨����ʱ����
*/ 
UINT16_S GetStopSectionDataStrudoorOpenTime(const UINT16_S stopSectionId);

/*
** ���������� ��ȡָ��IDStopSectionDataStru��վ̨���ŷ�ʽ
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨���ŷ�ʽ
*/ 
UINT16_S GetStopSectionDataStrudoorCloseMode(const UINT16_S stopSectionId);

/*
** ���������� ��ȡָ��IDStopSectionDataStru��վ̨����ʱ����
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨����ʱ����
*/ 
UINT16_S GetStopSectDataDoorCTim(const UINT16_S stopSectionId);

/*
** ���������� ��ȡָ��IDStopSectionDataStru��վ̨Ĭ��ͣ��ʱ��
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨Ĭ��ͣ��ʱ��
*/ 
UINT16_S GetStopSectionDataStruparkSteadyTime(const UINT16_S stopSectionId);

/*
* ���������� ��ѯĳ�����Ƿ�����ת����
* ����˵���� 
* ����ֵ  �� 0: ������
*             1: ����
*/
UINT8_S CheckPointBelongToZHG(UINT16_S wTrainHeadSeg);

/*
** ���������� ��ȡָ��λ�õ�ͣ����������
* ����˵���� const UINT16_S segId;SEGID
*             const UINT32_S offset;ƫ����
*             const UINT8_S dir;���з���
* ����ֵ  :   0: ��SEGIDû��ͣ������
*             >0: ͣ����������
*/ 
UINT16_S GetCurSegOfStopSecType(const UINT16_S segId);

/*
** ���������� ��ȡָ��λ�õ�ͣ������ID
* ����˵���� const UINT16_S segId;SEGID
* ����ֵ  :   0: ��SEGIDû��ͣ������
*             >0: ͣ������ID
*/ 
UINT16_S GetCurSegOfStopSecId(const UINT16_S segId);

/*
** ���������� ��ȡָ��λ�õ�ͣ��������Ϣ
* ����˵���� const UINT16_S segId;SEGID
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfStopSectionStruct* GetCurSegOfStopSecInfo(const UINT16_S segId);

#ifdef __cplusplus
}
#endif

#endif
