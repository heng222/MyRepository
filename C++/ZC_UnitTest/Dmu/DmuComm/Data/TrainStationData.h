/*************************************************
  �ļ���   ��TrainStationData.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� TrainStationData���ݹ���
			DmuCommonData�����TrainStationData���ܿɷֽ����£�
			1��	��TrainStationDataStru�ṹ��ָ�����ռ�
			2��	��ȡTrainStationData����
			3��	��ȡTrainStationData��Ϣ
			4��	��ȡָ��IDTrainStationDataStru�Ľṹ���±�
			5��	��ȡָ��IDTrainStationDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDTrainStationDataStru�ĳ�վ����
			7��	��ȡָ��IDTrainStationDataStru�ĳ�վ����վ̨��Ŀ
			8��	��ȡָ��IDTrainStationDataStru��վ̨���
  ��ע    ���ޡ� 
*************************************************/
#ifndef TRAINSTATION_DATA_H_
#define TRAINSTATION_DATA_H_

#include "../../../Common/CommonTypes.h"

#define TRAINSTATION_NAME_BYTE_LEN                 16                                                            /*���Ƴ���*/
#define TRAINSTATION_ID_MAX_NUM                     6                                                            /*���վ̨���*/
#define TRAINSTATION_LINE_BYTE_NUM                 32                                                       /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*��վ�����ݽṹ��*/
typedef struct BnfTrainStationStruct
{
    UINT16_S  stationId;                                /*��վID*/
    UINT8_S   name[TRAINSTATION_NAME_BYTE_LEN];        /*��վ����*/
    UINT16_S  includeStationNum;                        /*��վ����վ̨��Ŀ*/
    UINT16_S  stationIdBuff[TRAINSTATION_ID_MAX_NUM];      /*վ̨���*/
}BnfTrainStationStruct;

/*
* ���������� ��TrainStationDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocTrainStationDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡTrainStationData����
* ����˵����
* ����ֵ  �� 
            BnfTrainStationStruct*
*/
BnfTrainStationStruct *GetTrainStationData(void);

/*
* ���������� ��ȡTrainStationData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfTrainStationStruct*
*/
BnfTrainStationStruct *GetTrainStationDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDTrainStationDataStru�Ľṹ���±�
* ����˵���� const UINT16_S stationId;��վID
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetTrainStationDataStruIndex(const UINT16_S stationId);

/*
** ���������� ��ȡָ��IDTrainStationDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S stationId;��վID
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfTrainStationStruct* GetIndexIdTrainStationDataStru(const UINT16_S stationId);

/*
** ���������� ��ȡָ��IDTrainStationDataStru�ĳ�վ����
* ����˵���� const UINT16_S stationId;��վID
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ��վ����
*/ 
UINT8_S* GetTrainStationDataStruname(const UINT16_S stationId);

/*
** ���������� ��ȡָ��IDTrainStationDataStru�ĳ�վ����վ̨��Ŀ
* ����˵���� const UINT16_S stationId;��վID
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��վ����վ̨��Ŀ
*/ 
UINT16_S GetTrainStationDataStruincludeStationNum(const UINT16_S stationId);

/*
** ���������� ��ȡָ��IDTrainStationDataStru��վ̨���
* ����˵���� const UINT16_S stationId;��վID
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: վ̨���
*/ 
UINT16_S* GetTrainStationDataStrustationIdBuff(const UINT16_S stationId);


#ifdef __cplusplus
}
#endif

#endif
