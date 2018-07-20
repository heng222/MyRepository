/*************************************************
  �ļ���   ��StaRunLevelData.c
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� StaRunLevelData���ݹ���
			DmuCommonData�����StaRunLevelData���ܿɷֽ����£�
			1��	��StaRunLevelDataStru�ṹ��ָ�����ռ�
			2��	��ȡStaRunLevelData����
			3��	��ȡStaRunLevelData��Ϣ
			4��	��ȡָ��IDStaRunLevelDataStru�Ľṹ���±�
			5��	��ȡָ��IDStaRunLevelDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDStaRunLevelDataStru�����Ŀ�ĵر��
			7��	��ȡָ��IDStaRunLevelDataStru���յ�Ŀ�ĵر��
			8��	��ȡָ��IDStaRunLevelDataStru�����м���ּ���Ŀ
			9��	��ȡָ��IDStaRunLevelDataStru��
			10��	��ȡָ��������յ�����м����Ӧ�ٶ�

  ��ע    ���ޡ�
 
*************************************************/

#include "StaRunLevelData.h"
#include "../../../Common/Malloc.h"

static BnfStaRunLevelStruct* StaRunLevelDataStru = NULL;   /*����StaRunLevelData���ݽṹ��*/
static UINT16_S LineNumStaRunLevel = 0u;/*������*/


/*
* ���������� ��StaRunLevelDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocStaRunLevelDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == StaRunLevelDataStru))
    {
        StaRunLevelDataStru = (BnfStaRunLevelStruct*)MemoryMalloc((UINT32_S)sizeof(BnfStaRunLevelStruct) * lineNum);
        LineNumStaRunLevel = lineNum;
    }
}

/*
* ���������� ��ȡStaRunLevelData����
* ����˵����
* ����ֵ  �� 
            BnfStaRunLevelStruct*
*/
BnfStaRunLevelStruct *GetStaRunLevelData(void)
{
    return StaRunLevelDataStru;
}


/*
* ���������� ��ȡStaRunLevelData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfStaRunLevelStruct*
*/
BnfStaRunLevelStruct *GetStaRunLevelDataInfo(UINT16_S* lineNum)
{
    BnfStaRunLevelStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumStaRunLevel;
        retVal = StaRunLevelDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDStaRunLevelDataStru�Ľṹ���±�
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetStaRunLevelDataStruIndex(const UINT16_S indexId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumStaRunLevel; i++)
    {
        if (indexId == StaRunLevelDataStru[i].indexId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStaRunLevelDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfStaRunLevelStruct* GetIndexIdStaRunLevelDataStru(const UINT16_S indexId)
{
    BnfStaRunLevelStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStaRunLevelDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStaRunLevel)
    {
        retVal = &StaRunLevelDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStaRunLevelDataStru�����Ŀ�ĵر��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ���Ŀ�ĵر��
*/ 
UINT16_S GetStaRunLevelDataStrustartDestId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStaRunLevelDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStaRunLevel)
    {
        retVal = StaRunLevelDataStru[bufIndex].startDestId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStaRunLevelDataStru���յ�Ŀ�ĵر��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�Ŀ�ĵر��
*/ 
UINT16_S GetStaRunLevelDataStruendDestId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStaRunLevelDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStaRunLevel)
    {
        retVal = StaRunLevelDataStru[bufIndex].endDestId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStaRunLevelDataStru�����м���ּ���Ŀ
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ���м���ּ���Ŀ
*/ 
UINT16_S GetStaRunLevelDataStrurunLevelNum(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStaRunLevelDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStaRunLevel)
    {
        retVal = StaRunLevelDataStru[bufIndex].runLevelNum;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStaRunLevelDataStru��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: 
*/ 
SngRunLevelStruct* GetStaRunLevelDataStrurunLevelStru(const UINT16_S indexId)
{
    SngRunLevelStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStaRunLevelDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStaRunLevel)
    {
        retVal = StaRunLevelDataStru[bufIndex].runLevelStru;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��������յ�����м����Ӧ�ٶ�
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0 ��ѯʧ��
*            > 0 : ��ѯ���ٶ� 
*/ 
UINT16_S GetSpdForLevelByStartToEnd(UINT16_S startId,UINT16_S endId,UINT16_S level)
{
    UINT16_S tmpSpd = 0u;
    UINT32_S    tmpI = 0u;
    if ((startId == 0u)||(endId == 0u)||(level == 0u))
    {
        tmpI = 0xffffu;
    }
    for (tmpI = 0u; tmpI < LineNumStaRunLevel; tmpI++)
    {
        if ((StaRunLevelDataStru[tmpI].startDestId == startId)
            &&(StaRunLevelDataStru[tmpI].endDestId == endId))
        {
            if ((level <= StaRunLevelDataStru[tmpI].runLevelNum)&&(level > 0u))
            {
                tmpSpd = StaRunLevelDataStru[tmpI].runLevelStru[level-1u].levelSpeed;
                break;
            }
        }
    }
    return tmpSpd;
}
