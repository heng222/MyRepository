/*************************************************
  �ļ���   ��TrainStationData.c
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

#include "TrainStationData.h"
#include "../../../Common/Malloc.h"

static BnfTrainStationStruct* TrainStationDataStru = NULL;   /*����TrainStationData���ݽṹ��*/
static UINT16_S LineNumTrainStation = 0u;/*������*/


/*
* ���������� ��TrainStationDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocTrainStationDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == TrainStationDataStru))
    {
        TrainStationDataStru = (BnfTrainStationStruct*)MemoryMalloc((UINT32_S)sizeof(BnfTrainStationStruct) * lineNum);
        LineNumTrainStation = lineNum;
    }
}

/*
* ���������� ��ȡTrainStationData����
* ����˵����
* ����ֵ  �� 
            BnfTrainStationStruct*
*/
BnfTrainStationStruct *GetTrainStationData(void)
{
    return TrainStationDataStru;
}


/*
* ���������� ��ȡTrainStationData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfTrainStationStruct*
*/
BnfTrainStationStruct *GetTrainStationDataInfo(UINT16_S* lineNum)
{

    BnfTrainStationStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumTrainStation;
        retVal = TrainStationDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDTrainStationDataStru�Ľṹ���±�
* ����˵���� const UINT16_S stationId;��վID
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetTrainStationDataStruIndex(const UINT16_S stationId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumTrainStation; i++)
    {
        if (stationId == TrainStationDataStru[i].stationId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDTrainStationDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S stationId;��վID
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfTrainStationStruct* GetIndexIdTrainStationDataStru(const UINT16_S stationId)
{
    BnfTrainStationStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetTrainStationDataStruIndex(stationId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumTrainStation)
    {
        retVal = &TrainStationDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDTrainStationDataStru�ĳ�վ����
* ����˵���� const UINT16_S stationId;��վID
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ��վ����
*/ 
UINT8_S* GetTrainStationDataStruname(const UINT16_S stationId)
{
    UINT8_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetTrainStationDataStruIndex(stationId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumTrainStation)
    {
        retVal = TrainStationDataStru[bufIndex].name;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDTrainStationDataStru�ĳ�վ����վ̨��Ŀ
* ����˵���� const UINT16_S stationId;��վID
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��վ����վ̨��Ŀ
*/ 
UINT16_S GetTrainStationDataStruincludeStationNum(const UINT16_S stationId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetTrainStationDataStruIndex(stationId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumTrainStation)
    {
        retVal = TrainStationDataStru[bufIndex].includeStationNum;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDTrainStationDataStru��վ̨���
* ����˵���� const UINT16_S stationId;��վID
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: վ̨���
*/ 
UINT16_S* GetTrainStationDataStrustationIdBuff(const UINT16_S stationId)
{
    UINT16_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetTrainStationDataStruIndex(stationId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumTrainStation)
    {
        retVal = TrainStationDataStru[bufIndex].stationIdBuff;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

