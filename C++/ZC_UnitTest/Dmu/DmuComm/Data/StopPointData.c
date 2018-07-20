/*************************************************
  �ļ���   ��StopPointData.c
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� StopPointData���ݹ���
			DmuCommonData�����StopPointData���ܿɷֽ����£�
			1��	��StopPointDataStru�ṹ��ָ�����ռ�
			2��	��ȡStopPointData����
			3��	��ȡStopPointData��Ϣ
			4��	��ȡָ��IDStopPointDataStru�Ľṹ���±�
			5��	��ȡָ��IDStopPointDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDStopPointDataStru��ͣ��������
			7��	��ȡָ��IDStopPointDataStru��ͣ�������÷���(16����)
			8��	��ȡָ��IDStopPointDataStru��ͣ��������seg���
			9��	��ȡָ��IDStopPointDataStru��ͣ����Segƫ����
			10��	��ȡָ��IDStopPointDataStru��ͣ�����ӦATO���ô���Χ
			11��	��ȡָ��IDStopPointDataStru��ͣ�����ӦATP���ô���Χ
			12��	��ȡָ��ƫ���Ƿ���ATP���ô���Χ
			13��	��ȡָ��ƫ���Ƿ���ATO���ô���Χ
   ��ע    ���ޡ�
 
*************************************************/

#include "StopPointData.h"
#include "../../../Common/Malloc.h"

static BnfStopPointStruct* StopPointDataStru = NULL;   /*����StopPointData���ݽṹ��*/
static UINT16_S LineNumStopPoint = 0u;/*������*/


/*
* ���������� ��StopPointDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocStopPointDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == StopPointDataStru))
    {
        StopPointDataStru = (BnfStopPointStruct*)MemoryMalloc((UINT32_S)sizeof(BnfStopPointStruct) * lineNum);
        LineNumStopPoint = lineNum;
    }
}

/*
* ���������� ��ȡStopPointData����
* ����˵����
* ����ֵ  �� 
            BnfStopPointStruct*
*/
BnfStopPointStruct *GetStopPointData(void)
{
    return StopPointDataStru;
}


/*
* ���������� ��ȡStopPointData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfStopPointStruct*
*/
BnfStopPointStruct *GetStopPointDataInfo(UINT16_S* lineNum)
{

    BnfStopPointStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumStopPoint;
        retVal = StopPointDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDStopPointDataStru�Ľṹ���±�
* ����˵���� const UINT16_S stopPointId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetStopPointDataStruIndex(const UINT16_S stopPointId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumStopPoint; i++)
    {
        if (stopPointId == StopPointDataStru[i].stopPointId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStopPointDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S stopPointId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfStopPointStruct* GetIndexIdStopPointDataStru(const UINT16_S stopPointId)
{
    BnfStopPointStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStopPointDataStruIndex(stopPointId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStopPoint)
    {
        retVal = &StopPointDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStopPointDataStru��ͣ��������
* ����˵���� const UINT16_S stopPointId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ͣ��������
*/ 
UINT16_S GetStopPointDataStruattribute(const UINT16_S stopPointId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStopPointDataStruIndex(stopPointId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStopPoint)
    {
        retVal = StopPointDataStru[bufIndex].attribute;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStopPointDataStru��ͣ�������÷���(16����)
* ����˵���� const UINT16_S stopPointId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ͣ�������÷���(16����)
*/ 
UINT16_S GetStopPointDataStrudir(const UINT16_S stopPointId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStopPointDataStruIndex(stopPointId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStopPoint)
    {
        retVal = StopPointDataStru[bufIndex].dir;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStopPointDataStru��ͣ��������seg���
* ����˵���� const UINT16_S stopPointId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ͣ��������seg���
*/ 
UINT16_S GetStopPointDataStrusegId(const UINT16_S stopPointId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStopPointDataStruIndex(stopPointId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStopPoint)
    {
        retVal = StopPointDataStru[bufIndex].segId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStopPointDataStru��ͣ����Segƫ����
* ����˵���� const UINT16_S stopPointId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ͣ����Segƫ����
*/ 
UINT32_S GetStopPointDataStrusegOfst(const UINT16_S stopPointId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStopPointDataStruIndex(stopPointId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStopPoint)
    {
        retVal = StopPointDataStru[bufIndex].segOfst;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStopPointDataStru��ͣ�����ӦATO���ô���Χ
* ����˵���� const UINT16_S stopPointId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ͣ�����ӦATO���ô���Χ
*/ 
UINT32_S GetStopPointDataStruaTOParkArea(const UINT16_S stopPointId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStopPointDataStruIndex(stopPointId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStopPoint)
    {
        retVal = StopPointDataStru[bufIndex].aTOParkArea;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStopPointDataStru��ͣ�����ӦATP���ô���Χ
* ����˵���� const UINT16_S stopPointId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ͣ�����ӦATP���ô���Χ
*/ 
UINT32_S GetStopPointDataStruaTPParkArea(const UINT16_S stopPointId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStopPointDataStruIndex(stopPointId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStopPoint)
    {
        retVal = StopPointDataStru[bufIndex].aTPParkArea;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��ƫ���Ƿ���ATP���ô���Χ
* ����˵���� const UINT16_S stopPointId;�������
                         UINT32_S Off
* ����ֵ  :  0������ATPͣ������
*                    1����ATPͣ������
*/ 
UINT8_S GetThisInAtpStopPointWindow(const UINT16_S stopPointId,UINT32_S Off)
{
    UINT8_S isIn = 0u;
    UINT32_S pointOff = GetStopPointDataStrusegOfst(stopPointId);
    UINT32_S windowLen = GetStopPointDataStruaTPParkArea(stopPointId);
    UINT32_S leftOff = pointOff -windowLen;
    UINT32_S rightOff = pointOff +windowLen;
    if ((Off>leftOff)&&(Off<rightOff))
    {
        isIn = 1u;
    }
    return isIn;
}

/*
** ���������� ��ȡָ��ƫ���Ƿ���ATO���ô���Χ
* ����˵���� const UINT16_S stopPointId;�������
                         UINT32_S Off
* ����ֵ  :  0������ATPͣ������
*                    1����ATPͣ������
*/ 
UINT8_S GetThisInAtoStopPointWindow(const UINT16_S stopPointId,UINT32_S Off)
{
    UINT8_S isIn = 0u;
    UINT32_S pointOff = GetStopPointDataStrusegOfst(stopPointId);
    UINT32_S windowLen = GetStopPointDataStruaTOParkArea(stopPointId);
    UINT32_S leftOff = pointOff -windowLen;
    UINT32_S rightOff = pointOff +windowLen;
    if ((Off>leftOff)&&(Off<rightOff))
    {
        isIn = 1u;
    }
    return isIn;
}
