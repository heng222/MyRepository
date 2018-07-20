/*************************************************
  �ļ���   ��DefaultRouteData.c
  ����     ������      
  ����ʱ�� ��2016-8-12
  �������� �� DefaultRouteData���ݹ���
			DmuCommonData�����DefaultRouteData���ܿɷֽ����£�
			1��	��DefaultRouteDataStru�ṹ��ָ�����ռ�
			2��	��ȡDefaultRouteData����
			3��	 ��ȡDefaultRouteData��Ϣ
			4��	��ȡָ��IDDefaultRouteDataStru�Ľṹ���±�
			5��	��ȡָ��IDDefaultRouteDataStru�Ľṹ��ָ��
			6��	 ��ȡָ��IDDefaultRouteDataStru��seg���
			7��	��ȡָ��IDDefaultRouteDataStru�����з���
			8��	��ȡָ��IDDefaultRouteDataStru��ǰ��վ̨ID
			9��	��ȡָ��IDDefaultRouteDataStru��Ŀ��վ̨ID
			10��	��ȡ���з������һ����Ȼվ̨ID��ѯ��һ����Ȼվ̨ID


  ��ע    ���ޡ�
 
*************************************************/

#include "DefaultRouteData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"

static BnfDefaultRouteStruct* DefaultRouteDataStru = NULL;   /*����DefaultRouteData���ݽṹ��*/
static UINT16_S LineNumDefaultRoute = 0u;/*������*/


/*
* ���������� ��DefaultRouteDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocDefaultRouteDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == DefaultRouteDataStru))
    {
        DefaultRouteDataStru = (BnfDefaultRouteStruct*)MemoryMalloc((UINT32_S)sizeof(BnfDefaultRouteStruct) * lineNum);
        LineNumDefaultRoute = lineNum;
    }
}

/*
* ���������� ��ȡDefaultRouteData����
* ����˵����
* ����ֵ  �� 
            BnfDefaultRouteStruct*
*/
BnfDefaultRouteStruct *GetDefaultRouteData(void)
{
    return DefaultRouteDataStru;
}


/*
* ���������� ��ȡDefaultRouteData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfDefaultRouteStruct*
*/
BnfDefaultRouteStruct *GetDefaultRouteDataInfo(UINT16_S* lineNum)
{

    BnfDefaultRouteStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumDefaultRoute;
        retVal =  DefaultRouteDataStru;

    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDDefaultRouteDataStru�Ľṹ���±�
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetDefaultRouteDataStruIndex(const UINT16_S indexId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumDefaultRoute; i++)
    {
        if (indexId == DefaultRouteDataStru[i].indexId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDDefaultRouteDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfDefaultRouteStruct* GetIndexIdDefaultRouteDataStru(const UINT16_S indexId)
{
    BnfDefaultRouteStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetDefaultRouteDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumDefaultRoute)
    {
        retVal = &DefaultRouteDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDDefaultRouteDataStru��seg���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: seg���
*/ 
UINT16_S GetDefaultRouteDataStrusegId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetDefaultRouteDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumDefaultRoute)
    {
        retVal = DefaultRouteDataStru[bufIndex].segId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDDefaultRouteDataStru�����з���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ���з���
*/ 
UINT16_S GetDefaultRouteDataStrudir(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetDefaultRouteDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumDefaultRoute)
    {
        retVal = DefaultRouteDataStru[bufIndex].dir;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDDefaultRouteDataStru��ǰ��վ̨ID
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ǰ��վ̨ID
*/ 
UINT16_S GetDefaultRouteDataStruarriveStaId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetDefaultRouteDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumDefaultRoute)
    {
        retVal = DefaultRouteDataStru[bufIndex].arriveStaId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDDefaultRouteDataStru��Ŀ��վ̨ID
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: Ŀ��վ̨ID
*/ 
UINT16_S GetDefaultRouteDataStruaimStaId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetDefaultRouteDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumDefaultRoute)
    {
        retVal = DefaultRouteDataStru[bufIndex].aimStaId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* ��������:��ȡ���з������һ����Ȼվ̨ID��ѯ��һ����Ȼվ̨ID
* ����˵��:����:UINT16_S     segId          SEGID 
*                UINT16_S      dir             ���з���
*                UINT16_S*   nextStationId  >0 ��һ����Ȼվ̨ID
* ����ֵ   UINT8_S  1 �ɹ�  0ʧ��
*/
UINT8_S GetNextAccordCurStationId(const UINT16_S segId,const UINT16_S dir,UINT16_S* nextStationId)
{
    UINT8_S retVal = 0u;/*��һ��Ȼվ̨ID*/
            
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT16_S tmpNextId = 0u;
    
    if (nextStationId != NULL)
    {
        for ( i = 0u; i < LineNumDefaultRoute; i++)
        {
            if ((segId == DefaultRouteDataStru[i].segId)&&(dir == DefaultRouteDataStru[i].dir))
            {
                tmpNextId = DefaultRouteDataStru[i].arriveStaId;
                retVal = 1u;
                break;
            }
        }
        *nextStationId = tmpNextId;
    }
    
    
    return retVal;
}
