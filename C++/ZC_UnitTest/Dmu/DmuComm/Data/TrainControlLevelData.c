/*************************************************
  �ļ���   ��TrainControlLevelData.c
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

#include "TrainControlLevelData.h"
#include "../../../Common/Malloc.h"

static BnfTrainControlLevelStruct* TrainControlLevelDataStru = NULL;   /*����TrainControlLevelData���ݽṹ��*/
static UINT16_S LineNumTrainControlLevel = 0u;/*������*/


/*
* ���������� ��TrainControlLevelDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocTrainControlLevelDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == TrainControlLevelDataStru))
    {
        TrainControlLevelDataStru = (BnfTrainControlLevelStruct*)MemoryMalloc((UINT32_S)sizeof(BnfTrainControlLevelStruct) * lineNum);
        LineNumTrainControlLevel = lineNum;
    }
}

/*
* ���������� ��ȡTrainControlLevelData����
* ����˵����
* ����ֵ  �� 
            BnfTrainControlLevelStruct*
*/
BnfTrainControlLevelStruct *GetTrainControlLevelData(void)
{
    return TrainControlLevelDataStru;
}


/*
* ���������� ��ȡTrainControlLevelData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfTrainControlLevelStruct*
*/
BnfTrainControlLevelStruct *GetTrainControlLevelDataInfo(UINT16_S* lineNum)
{

    BnfTrainControlLevelStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumTrainControlLevel;
        retVal = TrainControlLevelDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDTrainControlLevelDataStru�Ľṹ���±�
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetTrainControlLevelDataStruIndex(const UINT16_S indexId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumTrainControlLevel; i++)
    {
        if (indexId == TrainControlLevelDataStru[i].indexId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDTrainControlLevelDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfTrainControlLevelStruct* GetIndexIdTrainControlLevelDataStru(const UINT16_S indexId)
{
    BnfTrainControlLevelStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetTrainControlLevelDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumTrainControlLevel)
    {
        retVal = &TrainControlLevelDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDTrainControlLevelDataStru���������seg���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������seg���
*/ 
UINT16_S GetTrainControlLevelDataStrustartSegId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetTrainControlLevelDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumTrainControlLevel)
    {
        retVal = TrainControlLevelDataStru[bufIndex].startSegId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDTrainControlLevelDataStru���������Segƫ����
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������Segƫ����
*/ 
UINT32_S GetTrContrLevDataStartOff(const UINT16_S indexId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetTrainControlLevelDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumTrainControlLevel)
    {
        retVal = TrainControlLevelDataStru[bufIndex].startOffset;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDTrainControlLevelDataStru���յ�����seg���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�����seg���
*/ 
UINT16_S GetTrainControlLevelDataStruendSegId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetTrainControlLevelDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumTrainControlLevel)
    {
        retVal = TrainControlLevelDataStru[bufIndex].endSegId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDTrainControlLevelDataStru���յ�����Segƫ����
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�����Segƫ����
*/ 
UINT32_S GetTrContrLevDataOff(const UINT16_S indexId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetTrainControlLevelDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumTrainControlLevel)
    {
        retVal = TrainControlLevelDataStru[bufIndex].endOffset;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDTrainControlLevelDataStru�ķ�CBTC�����г����з���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��CBTC�����г����з���
*/ 
UINT16_S GetTrainControlLevelDataStrudir(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetTrainControlLevelDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumTrainControlLevel)
    {
        retVal = TrainControlLevelDataStru[bufIndex].dir;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

