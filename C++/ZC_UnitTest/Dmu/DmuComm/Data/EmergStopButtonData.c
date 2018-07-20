/*************************************************
  �ļ���   ��EmergStopButtonData.c
  ����     ������      
  ����ʱ�� ��2016-8-12
  �������� �� EmergStopButtonData���ݹ���
			DmuCommonData�����EmergStopButtonData���ܿɷֽ����£�
			1��	��EmergStopButtonDataStru�ṹ��ָ�����ռ�
			2��	��ȡEmergStopButtonData����
			3��	��ȡEmergStopButtonData��Ϣ
			4��	��ȡָ��IDEmergStopButtonDataStru�Ľṹ���±�
			5��	��ȡָ��IDEmergStopButtonDataStru�Ľṹ��ָ��
			6��	 ��ȡָ��IDEmergStopButtonDataStru������
			7��	��ȡָ��IDEmergStopButtonDataStru������վ̨���
			8��	��ȡ��·����ͣ����ť���ID
			9��	��ȡ��·����ͣ����ť����վ̨ID
			10��	���������SEGID��ȡESB��Ϣ
			11��	����վ̨ID��ȡ��Ӧ�Ľ���ͣ����ťID
			12��	��ȡ��·����ͣ����ť����ZC
			13��	��ȡ��·����ͣ����ť����ci
  ��ע    ���ޡ�
 
*************************************************/

#include "EmergStopButtonData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/MemSet.h"

static BnfEmergStopButtonStruct* EmergStopButtonDataStru = NULL;   /*����EmergStopButtonData���ݽṹ��*/
static UINT16_S LineNumEmergStopButton = 0u;/*������*/


/*
* ���������� ��EmergStopButtonDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocEmergStopButtonDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == EmergStopButtonDataStru))
    {
        EmergStopButtonDataStru = (BnfEmergStopButtonStruct*)MemoryMalloc((UINT32_S)sizeof(BnfEmergStopButtonStruct) * lineNum);
        if (EmergStopButtonDataStru != NULL)
        {
            LineNumEmergStopButton = lineNum;
            /*��ֵΪ��Чֵ*/
            MemorySet(EmergStopButtonDataStru,lineNum*sizeof(BnfEmergStopButtonStruct),UINT8_NULL,lineNum*sizeof(BnfEmergStopButtonStruct));
        }
    }
}

/*
* ���������� ��ȡEmergStopButtonData����
* ����˵����
* ����ֵ  �� 
            BnfEmergStopButtonStruct*
*/
BnfEmergStopButtonStruct *GetEmergStopButtonData(void)
{
    return EmergStopButtonDataStru;
}


/*
* ���������� ��ȡEmergStopButtonData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfEmergStopButtonStruct*
*/
BnfEmergStopButtonStruct *GetEmergStopButtonDataInfo(UINT16_S* lineNum)
{
    BnfEmergStopButtonStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumEmergStopButton;
        retVal =  EmergStopButtonDataStru;

    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDEmergStopButtonDataStru�Ľṹ���±�
* ����˵���� const UINT16_S emergStopButtonId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetEmergStopButtonDataStruIndex(const UINT16_S emergStopButtonId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumEmergStopButton; i++)
    {
        if (emergStopButtonId == EmergStopButtonDataStru[i].emergStopButtonId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDEmergStopButtonDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S emergStopButtonId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfEmergStopButtonStruct* GetIndexIdEmergStopButtonDataStru(const UINT16_S emergStopButtonId)
{
    BnfEmergStopButtonStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetEmergStopButtonDataStruIndex(emergStopButtonId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumEmergStopButton)
    {
        retVal = &EmergStopButtonDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDEmergStopButtonDataStru������
* ����˵���� const UINT16_S emergStopButtonId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ����
*/ 
UINT8_S* GetEmergStopButtonDataStruname(const UINT16_S emergStopButtonId)
{
    UINT8_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetEmergStopButtonDataStruIndex(emergStopButtonId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumEmergStopButton)
    {
        retVal = EmergStopButtonDataStru[bufIndex].name;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDEmergStopButtonDataStru������վ̨���
* ����˵���� const UINT16_S emergStopButtonId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����վ̨���
*/ 
UINT16_S GetEmergStopButtonDataStrustationId(const UINT16_S emergStopButtonId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetEmergStopButtonDataStruIndex(emergStopButtonId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumEmergStopButton)
    {
        retVal = EmergStopButtonDataStru[bufIndex].stationId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* ���������� ��ȡ��·����ͣ����ť���ID
* ����˵���� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:����ͣ����ť���ID
*/
UINT16_S GetLineEsbMaxId(void)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S emergStopButtonId = 0u;/*����ͣ����ťID*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumEmergStopButton; i++)
    {
        if (emergStopButtonId < EmergStopButtonDataStru[i].emergStopButtonId)
        {
            emergStopButtonId = EmergStopButtonDataStru[i].emergStopButtonId;
        }
    }

    if(emergStopButtonId != 0u)
    {
        retVal = emergStopButtonId;
    }

    return retVal;
}

/*
* ���������� ��ȡ��·����ͣ����ť����վ̨ID
* ����˵���� const UINT16_S esbId,����ͣ����ťID
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:����վ̨ID
*/
UINT16_S GetLineEsbBelongStationId(const UINT16_S esbId)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumEmergStopButton; i++)
    {
        if (esbId == EmergStopButtonDataStru[i].emergStopButtonId)
        {
            retVal = EmergStopButtonDataStru[i].stationId;
            break;
        }
    }

    return retVal;
}

/*
** ���������� ���������SEGID��ȡESB��Ϣ
* ����˵���� ����:const UINT16_S stationIdBuff,վ̨ID
*             const UINT8_S stationIdNum    վ̨ID����
*             UINT16_S* index    ����ƫ��                  
*             �������:UINT16_S esbIdBuff[],ESBID����      
* ����ֵ  :  >=0: ESB��Ϣ
*/ 
UINT16_S GetStationIdBelongofEsbInfo(const UINT16_S* stationIdBuff,const UINT8_S stationIdNum,UINT16_S index,UINT16_S esbIdBuff[])
{
    UINT16_S retVal = 0u;
    UINT16_S esbIdNum = 0u;/*����ͣ����ť����*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S j = 0u;/*ѭ��ʹ��*/
    
    if ((stationIdBuff != NULL)&&(stationIdNum > 0u)&&(esbIdBuff != NULL))
    {
        for ( i = 0u; i < LineNumEmergStopButton; i++)
        {
            for (j = 0u; j < stationIdNum; j++)
            {
                if (stationIdBuff[j] == EmergStopButtonDataStru[i].stationId)
                {
                    esbIdBuff[index] = EmergStopButtonDataStru[i].emergStopButtonId;
                    index=index+1;

                    esbIdBuff[index] = LINEOBS_ESB;
                    index=index+1;
                    esbIdNum++;
                    break;
                }
            }

        }
    }

    retVal = esbIdNum;
    return retVal;
}

/*
** ���������� ����վ̨ID��ȡ��Ӧ�Ľ���ͣ����ťID
* ����˵���� const UINT16_S pPlatformId;վ̨ID
*             const UINT8_S platformNum  վ̨ID����
*             UINT16_S*  pPsdId          ������IDָ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����ͣ����ť����
*/ 
UINT8_S GetEsbIdAccordPlatformIdBuff(const UINT16_S* pPlatformId,const UINT8_S platformNum,UINT16_S* pEsbId)
{
    UINT8_S retVal = 0u;

    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S  j = 0u;/*ѭ��ʹ��*/

    UINT8_S index = 0u;/*�����±�*/

    if (((platformNum <= TWO_POINT_STATION_NUM_MAX)&&(platformNum > 0u))
        &&(pPlatformId != NULL)&&(pEsbId != NULL))
    {
        for ( i = 0u;( i < LineNumEmergStopButton)&&(index < TWO_POINT_ESB_NUM_MAX); i++)
        {
            for ( j = 0u; j < platformNum; j++)
            {
                if (pPlatformId[j] == EmergStopButtonDataStru[i].stationId)
                {
                    pEsbId[index] = EmergStopButtonDataStru[i].emergStopButtonId;
                    index=index+1;
                    break;
                }
            }
        }

        if (i == LineNumEmergStopButton)
        {
            retVal = index;
        }
    }

    return retVal;
}

/*
* ���������� ��ȡ��·����ͣ����ť����ZC
* ����˵���� const UINT16_S esbId,����ͣ����ťID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����ZCId
*/
UINT16_S GetLineEsbBelongZcId(const UINT16_S esbId)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumEmergStopButton; i++)
    {
        if (esbId == EmergStopButtonDataStru[i].emergStopButtonId)
        {
            retVal = EmergStopButtonDataStru[i].manageZCId;
            break;
        }
    }

    return retVal;
}

/*
* ���������� ��ȡ��·����ͣ����ť����ci
* ����˵���� const UINT16_S esbId,����ͣ����ťID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����ciId
*/
UINT16_S GetLineEsbBelongCiId(const UINT16_S esbId)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumEmergStopButton; i++)
    {
        if (esbId == EmergStopButtonDataStru[i].emergStopButtonId)
        {
            retVal = EmergStopButtonDataStru[i].manageCIId;
            break;
        }
    }

    return retVal;
}
