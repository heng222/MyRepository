/*************************************************
  �ļ���   ��PlatFormData.c
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� PlatFormData���ݹ���
			DmuCommonData�����PlatFormData���ܿɷֽ����£�
			1��	��PlatFormDataStru�ṹ��ָ�����ռ�
			2��	��ȡPlatFormData����
			3��	��ȡPlatFormData��Ϣ
			4��	��ȡָ��IDPlatFormDataStru�Ľṹ���±�
			5��	��ȡָ��IDPlatFormDataStru�Ľṹ��ָ��
			6��	 ��ȡָ��IDPlatFormDataStru��վ̨���Ĺ����
			7��	��ȡָ��IDPlatFormDataStru��վ̨����seg���
			8��	��ȡָ��IDPlatFormDataStru���߼�������վ̨�����ͣ������ķ���
			9��	��ȡ��SEG��Ӧ��վ̨ID
			10��	���Ҵ˼��������Ƿ�����վ̨����
			11��	��ȡ��SEG��Ӧ��վ̨ID
			12��	��ȡ��SEG��Ӧ��վ̨ID
  ��ע    ���ޡ� 
*************************************************/

#include "PlatFormData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"

static BnfPlatFormStruct* PlatFormDataStru = NULL;   /*����PlatFormData���ݽṹ��*/
static UINT16_S LineNumPlatForm = 0u;/*������*/


/*
* ���������� ��PlatFormDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocPlatFormDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == PlatFormDataStru))
    {
        PlatFormDataStru = (BnfPlatFormStruct*)MemoryMalloc((UINT32_S)sizeof(BnfPlatFormStruct) * lineNum);
        LineNumPlatForm = lineNum;
    }
}

/*
* ���������� ��ȡPlatFormData����
* ����˵����
* ����ֵ  �� 
            BnfPlatFormStruct*
*/
BnfPlatFormStruct *GetPlatFormData(void)
{
    return PlatFormDataStru;
}


/*
* ���������� ��ȡPlatFormData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfPlatFormStruct*
*/
BnfPlatFormStruct *GetPlatFormDataInfo(UINT16_S* lineNum)
{

    BnfPlatFormStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumPlatForm;
        retVal = PlatFormDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDPlatFormDataStru�Ľṹ���±�
* ����˵���� const UINT16_S platFormId;վ̨ID
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetPlatFormDataStruIndex(const UINT16_S platFormId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumPlatForm; i++)
    {
        if (platFormId == PlatFormDataStru[i].platFormId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDPlatFormDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S platFormId;վ̨ID
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfPlatFormStruct* GetIndexIdPlatFormDataStru(const UINT16_S platFormId)
{
    BnfPlatFormStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetPlatFormDataStruIndex(platFormId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumPlatForm)
    {
        retVal = &PlatFormDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDPlatFormDataStru��վ̨���Ĺ����
* ����˵���� const UINT16_S platFormId;վ̨ID
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: վ̨���Ĺ����
*/ 
UINT8_S* GetPlatFormDataStruplatFormKillPost(const UINT16_S platFormId)
{
    UINT8_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetPlatFormDataStruIndex(platFormId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumPlatForm)
    {
        retVal = PlatFormDataStru[bufIndex].platFormKillPost;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDPlatFormDataStru��վ̨����seg���
* ����˵���� const UINT16_S platFormId;վ̨ID
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨����seg���
*/ 
UINT16_S GetPlatFormDataStrusegId(const UINT16_S platFormId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetPlatFormDataStruIndex(platFormId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumPlatForm)
    {
        retVal = PlatFormDataStru[bufIndex].segId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDPlatFormDataStru���߼�������վ̨�����ͣ������ķ���
* ����˵���� const UINT16_S platFormId;վ̨ID
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �߼�������վ̨�����ͣ������ķ���
*/ 
UINT8_S GetPlatFormDataStrudir(const UINT16_S platFormId)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetPlatFormDataStruIndex(platFormId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumPlatForm)
    {
        retVal = PlatFormDataStru[bufIndex].dir;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡ��SEG��Ӧ��վ̨ID
* ����˵���� const UINT16_S segId;SEGID
*             UINT16_S* platFormIdBuff  վ̨ID
* ����ֵ  :  Oxff: ��ȡ����ʧ��
*            >=0: վ̨ID����
*/ 
UINT8_S GetSegIdBelongOfStationId(const UINT16_S* segIdBuff,UINT8_S segIdNum,UINT16_S* platFormIdBuff)
{
    UINT8_S retVal = 0u;

    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S j = 0u;/*ѭ��ʹ��*/
    UINT8_S platFormIdNum = 0u;/*վ̨����*/

    if ((NULL == segIdBuff) ||(NULL == platFormIdBuff))
    {
        retVal = UINT8_NULL;
    }
    else
    {
        for ( i = 0u;(i < LineNumPlatForm)&&(UINT8_NULL != retVal); i++)
        {
            for (j = 0u; j < segIdNum; j++)
            {
                if (segIdBuff[j] == PlatFormDataStru[i].segId)
                {
                    if (platFormIdNum == ROUTE_INCLUDE_PLATFORM_MAX_NUM)
                    {
                        retVal = UINT8_NULL;
                        break;
                    }
                    else
                    {
                        platFormIdBuff[platFormIdNum] = PlatFormDataStru[i].platFormId;
                        platFormIdNum=platFormIdNum+1;
                        break;
                    }

                }
            }

        }

        if (UINT8_NULL != retVal)
        {
            retVal = platFormIdNum;
        }

    }
    return retVal;
}

/*
* ���������� ���Ҵ˼��������Ƿ�����վ̨����
* ����˵���� const UINT16_S* pSegId;SEGIDָ��
* ����ֵ  :  1 ����
*             2 ������
*/ 
UINT8_S SearchStationBelongAxleSec(const UINT16_S* pSegId,UINT16_S includeSegNum)
{
    UINT8_S retVal = 2u;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT16_S  j = 0u;/*ѭ��ʹ��*/

    if(NULL != pSegId)
    {
        for ( i = 0u; i < LineNumPlatForm; i++)
        {
            for (j = 0u;j < includeSegNum; j++)
            {
                if (pSegId[j] == PlatFormDataStru[i].segId)
                {
                    retVal = 1u;
                    break;
                }
            }
        }
    }

    return retVal;
}

/*
** ���������� ��ȡ��SEG��Ӧ��վ̨ID
* ����˵���� const UINT16_S segId;SEGID
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨����
*/ 
UINT8_S GetPlatformIdAccordSegBuff(const UINT16_S* pSegId,const UINT8_S segNum,UINT16_S* pPlatformId)
{
    UINT8_S retVal = 0u;

    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S  j = 0u;/*ѭ��ʹ��*/

    UINT8_S index = 0u;/*�����±�*/

    if (((segNum <= BOTHSEG_INCLUDE_MAX_SEG)&&(segNum > 0))
        &&(pSegId != NULL)&&(pPlatformId != NULL))
    {
        for ( i = 0u;( i < LineNumPlatForm)&&(index < TWO_POINT_STATION_NUM_MAX); i++)
        {
            for ( j = 0u; j < segNum; j++)
            {
                if (pSegId[j] == PlatFormDataStru[i].segId)
                {
                    pPlatformId[index] = PlatFormDataStru[i].platFormId;
                    index=index+1;
                    break;
                }
            }
        }

        if ((index <= TWO_POINT_STATION_NUM_MAX)&&(i == LineNumPlatForm))
        {
            retVal = index;
        }
    }

    return retVal;
}

/*
** ���������� ��ȡ��SEG��Ӧ��վ̨ID
* ����˵���� const UINT16_S segId;SEGID
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨ID
*/ 
UINT16_S GetPlatformIdAccordSegId(const UINT16_S segId)
{
    UINT16_S retVal = 0u;

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u;i < LineNumPlatForm; i++)
    {
        if (segId == PlatFormDataStru[i].segId)
        {
            retVal = PlatFormDataStru[i].platFormId;
            break;
        }
    }

    return retVal;
}
