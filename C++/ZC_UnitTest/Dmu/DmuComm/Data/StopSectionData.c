/*************************************************
  �ļ���   ��StopSectionData.c
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

#include "StopSectionData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/Convert.h"
static BnfStopSectionStruct* StopSectionDataStru = NULL;   /*����StopSectionData���ݽṹ��*/
static UINT16_S LineNumStopSection = 0u;/*������*/


/*
* ���������� ��StopSectionDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocStopSectionDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == StopSectionDataStru))
    {
        StopSectionDataStru = (BnfStopSectionStruct*)MemoryMalloc((UINT32_S)sizeof(BnfStopSectionStruct) * lineNum);
        LineNumStopSection = lineNum;
    }
}

/*
* ���������� ��ȡStopSectionData����
* ����˵����
* ����ֵ  �� 
BnfStopSectionStruct*
*/
BnfStopSectionStruct *GetStopSectionData(void)
{
    return StopSectionDataStru;
}


/*
* ���������� ��ȡStopSectionData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
BnfStopSectionStruct*
*/
BnfStopSectionStruct *GetStopSectionDataInfo(UINT16_S* lineNum)
{

    BnfStopSectionStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumStopSection;
        retVal = StopSectionDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDStopSectionDataStru�Ľṹ���±�
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetStopSectionDataStruIndex(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumStopSection; i++)
    {
        if (stopSectionId == StopSectionDataStru[i].stopSectionId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStopSectionDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfStopSectionStruct* GetIndexIdStopSectionDataStru(const UINT16_S stopSectionId)
{
    BnfStopSectionStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = &StopSectionDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStopSectionDataStru��������վ����
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ������վ����
*/ 
UINT8_S* GetStopSectionDataStrustationName(const UINT16_S stopSectionId)
{
    UINT8_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].stationName;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��dstCode��������վ����
* ����˵���� const UINT16_S dstCode;
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ������վ����
*/ 
UINT8_S* GetStopSecNameByDstCode(const UINT16_S dstCode)
{
    UINT8_S* retVal = NULL;/*��������ֵ*/
    UINT16_S i = 0u;
    UINT16_S destId = 0u;

    for(i = 0u;i < LineNumStopSection;i++)
    {
        destId = ShortFromChar(StopSectionDataStru[i].bDesId);
        if(dstCode == destId)
        {
            retVal = StopSectionDataStru[i].stationName;
            break;
        }
    }
    return retVal;
}


/*
** ���������� ��ȡָ��IDStopSectionDataStru��Ŀ�ĵر��
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: Ŀ�ĵر��
*/ 
UINT8_S* GetStopSectionDataStrubDesId(const UINT16_S stopSectionId)
{
    UINT8_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].bDesId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStopSectionDataStru��ͣ������seg���
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ͣ������seg���
*/ 
UINT16_S GetStopSectionDataStrusegId(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].segId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStopSectionDataStru��ͣ����������
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ͣ����������
*/ 
UINT16_S GetStopSectionDataStrusttribute(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].sttribute;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStopSectionDataStru��վ̨��Сͣվʱ��
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨��Сͣվʱ��
*/ 
UINT16_S GetStopSectionDataStruminParkTime(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].minParkTime;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStopSectionDataStru��վ̨���ͣվʱ��
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨���ͣվʱ��
*/ 
UINT16_S GetStopSectionDataStrumaxParkTime(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].maxParkTime;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStopSectionDataStru��վ̨Ĭ��ͣվʱ��
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨Ĭ��ͣվʱ��
*/ 
UINT16_S GetStopSectionDataStruparkTime(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].parkTime;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStopSectionDataStru��վ̨���ŷ�ʽ
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨���ŷ�ʽ
*/ 
UINT16_S GetStopSectionDataStrudoorOpenMode(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].doorOpenMode;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStopSectionDataStru��վ̨����ʱ����
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨����ʱ����
*/ 
UINT16_S GetStopSectionDataStrudoorOpenTime(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].doorOpenTime;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStopSectionDataStru��վ̨���ŷ�ʽ
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨���ŷ�ʽ
*/ 
UINT16_S GetStopSectionDataStrudoorCloseMode(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].doorCloseMode;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStopSectionDataStru��վ̨����ʱ����
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨����ʱ����
*/ 
UINT16_S GetStopSectDataDoorCTim(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].doorCloseTime;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStopSectionDataStru��վ̨Ĭ��ͣ��ʱ��
* ����˵���� const UINT16_S stopSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨Ĭ��ͣ��ʱ��
*/ 
UINT16_S GetStopSectionDataStruparkSteadyTime(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].parkSteadyTime;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* ���������� ��ѯĳ�����Ƿ�����ת����
* ����˵���� 
* ����ֵ  �� 0: ��ѯʧ��
*            1: ����
*             2: ������
*/
UINT8_S CheckPointBelongToZHG(UINT16_S wTrainHeadSeg)
{
    UINT8_S retVal = 0u;

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumStopSection; i++)
    {
        if (wTrainHeadSeg == StopSectionDataStru[i].segId)
        {
            if (RUN_TRANSFORM_AREA == (StopSectionDataStru[i].sttribute &RUN_TRANSFORM_AREA))
            {
                retVal = 1u;        
            }
            else
            {
                retVal = 2u;
            }

            break;
        }
        else
        {
            retVal = 2u;
        }

    }

    return retVal;
}

/*
** ���������� ��ȡָ��λ�õ�ͣ����������
* ����˵���� const UINT16_S segId;SEGID
* ����ֵ  :   0: ��SEGIDû��ͣ������
*             >0: ͣ����������
*/ 
UINT16_S GetCurSegOfStopSecType(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumStopSection; i++)
    {
        if (segId == StopSectionDataStru[i].segId)
        {
            retVal = StopSectionDataStru[i].sttribute;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��λ�õ�ͣ������ID
* ����˵���� const UINT16_S segId;SEGID
* ����ֵ  :   0: ��SEGIDû��ͣ������
*             >0: ͣ������ID
*/ 
UINT16_S GetCurSegOfStopSecId(const UINT16_S segId)
{
    UINT16_S retVal = 0x0u;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumStopSection; i++)
    {
        if (segId == StopSectionDataStru[i].segId)
        {
            retVal = StopSectionDataStru[i].stopSectionId;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��λ�õ�ͣ��������Ϣ
* ����˵���� const UINT16_S segId;SEGID
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfStopSectionStruct* GetCurSegOfStopSecInfo(const UINT16_S segId)
{
    BnfStopSectionStruct* retVal = NULL;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumStopSection; i++)
    {
        if (segId == StopSectionDataStru[i].segId)
        {
            retVal = &StopSectionDataStru[i];
            break;
        }
    }
    return retVal;
}

