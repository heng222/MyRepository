/*************************************************
  �ļ���   ��TrainControlLevelData.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� TrainControlLevelData���ݹ���
			DmuCommonData�����TrainControlLevelData���ܿɷֽ����£�
			1��	��TrainControlLevelDataStru�ṹ��ָ�����ռ�
			2��	��ȡTrainControlLevelData����
			3��	��ȡTrainControlLevelData��Ϣ
			4��	��ȡָ��IDTrainControlLevelDataStru�Ľṹ���±�
			5��	��ȡָ��IDTrainControlLevelDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDTrainControlLevelDataStru���������seg���
			7��	��ȡָ��IDTrainControlLevelDataStru���������Segƫ����
			8��	��ȡָ��IDTrainControlLevelDataStru���յ�����seg���
			9��	��ȡָ��IDTrainControlLevelDataStru���յ�����Segƫ����
			10��	��ȡָ��IDTrainControlLevelDataStru�ķ�CBTC�����г����з���

  ��ע    ���ޡ� 
*************************************************/
#ifndef TRAINCONTROLLEVEL_DATA_H_
#define TRAINCONTROLLEVEL_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  TRAINCONTROLLEVEL_LINE_BYTE_NUM                 16                              /*һ�������ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*��CBTC��������ݽṹ��*/
typedef struct BnfTrainControlLevelStruct
{
    UINT16_S  indexId;                               /*�������*/
    UINT16_S  startSegId;                               /*�������seg���*/
    UINT32_S  startOffset;                        /*�������Segƫ����*/
    UINT16_S  endSegId;                               /*�յ�����seg���*/
    UINT32_S  endOffset;                               /*�յ�����Segƫ����*/
    UINT16_S  dir;                                   /*��CBTC�����г����з���*/
}BnfTrainControlLevelStruct;

/*
* ���������� ��TrainControlLevelDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocTrainControlLevelDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡTrainControlLevelData����
* ����˵����
* ����ֵ  �� 
            BnfTrainControlLevelStruct*
*/
BnfTrainControlLevelStruct *GetTrainControlLevelData(void);

/*
* ���������� ��ȡTrainControlLevelData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfTrainControlLevelStruct*
*/
BnfTrainControlLevelStruct *GetTrainControlLevelDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDTrainControlLevelDataStru�Ľṹ���±�
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetTrainControlLevelDataStruIndex(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDTrainControlLevelDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfTrainControlLevelStruct* GetIndexIdTrainControlLevelDataStru(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDTrainControlLevelDataStru���������seg���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������seg���
*/ 
UINT16_S GetTrainControlLevelDataStrustartSegId(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDTrainControlLevelDataStru���������Segƫ����
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������Segƫ����
*/ 
UINT32_S GetTrContrLevDataStartOff(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDTrainControlLevelDataStru���յ�����seg���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�����seg���
*/ 
UINT16_S GetTrainControlLevelDataStruendSegId(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDTrainControlLevelDataStru���յ�����Segƫ����
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�����Segƫ����
*/ 
UINT32_S GetTrContrLevDataOff(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDTrainControlLevelDataStru�ķ�CBTC�����г����з���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��CBTC�����г����з���
*/ 
UINT16_S GetTrainControlLevelDataStrudir(const UINT16_S indexId);


#ifdef __cplusplus
}
#endif

#endif
