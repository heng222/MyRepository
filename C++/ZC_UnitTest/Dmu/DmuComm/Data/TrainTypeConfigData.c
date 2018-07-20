/*************************************************
  �ļ���   ��TrainTypeConfigData.c
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� TrainTypeConfigData���ݹ���
			DmuCommonData�����TrainTypeConfigData���ܿɷֽ����£�
			1��	��TrainTypeConfigDataStru�ṹ��ָ�����ռ�
			2��	��ȡTrainTypeConfigData����
			3��	��ȡTrainTypeConfigData��Ϣ
			4��	��ȡָ��IDTrainTypeConfigDataStru�Ľṹ���±�
			5��	��ȡָ��IDTrainTypeConfigDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDTrainTypeConfigDataStru���г�����

  ��ע    ���ޡ� 
*************************************************/

#include "TrainTypeConfigData.h"
#include "../../../Common/Malloc.h"

static BnfTrainTypeConfigStruct* TrainTypeConfigDataStru = NULL;   /*����TrainTypeConfigData���ݽṹ��*/
static UINT16_S LineNumTrainTypeConfig = 0u;/*������*/


/*
* ���������� ��TrainTypeConfigDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocTrainTypeConfigDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == TrainTypeConfigDataStru))
    {
        TrainTypeConfigDataStru = (BnfTrainTypeConfigStruct*)MemoryMalloc((UINT32_S)sizeof(BnfTrainTypeConfigStruct) * lineNum);
        LineNumTrainTypeConfig = lineNum;
    }
}

/*
* ���������� ��ȡTrainTypeConfigData����
* ����˵����
* ����ֵ  �� 
            BnfTrainTypeConfigStruct*
*/
BnfTrainTypeConfigStruct *GetTrainTypeConfigData(void)
{
    return TrainTypeConfigDataStru;
}


/*
* ���������� ��ȡTrainTypeConfigData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfTrainTypeConfigStruct*
*/
BnfTrainTypeConfigStruct *GetTrainTypeConfigDataInfo(UINT16_S* lineNum)
{

    BnfTrainTypeConfigStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumTrainTypeConfig;
        retVal = TrainTypeConfigDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDTrainTypeConfigDataStru�Ľṹ���±�
* ����˵���� const UINT16_S trainDevName;�г�����(TYPE+ID)
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetTrainTypeConfigDataStruIndex(const UINT16_S trainDevName)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumTrainTypeConfig; i++)
    {
        if (trainDevName == TrainTypeConfigDataStru[i].trainDevName)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDTrainTypeConfigDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S trainDevName;�г�����(TYPE+ID)
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfTrainTypeConfigStruct* GetIndexIdTrainTypeConfigDataStru(const UINT16_S trainDevName)
{
    BnfTrainTypeConfigStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetTrainTypeConfigDataStruIndex(trainDevName);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumTrainTypeConfig)
    {
        retVal = &TrainTypeConfigDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDTrainTypeConfigDataStru���г�����
* ����˵���� const UINT16_S trainDevName;�г�����(TYPE+ID)
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �г�����
*/ 
UINT8_S GetTrainTypeConfigDataStrutrainType(const UINT16_S trainDevName)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetTrainTypeConfigDataStruIndex(trainDevName);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumTrainTypeConfig)
    {
        retVal = TrainTypeConfigDataStru[bufIndex].trainType;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

