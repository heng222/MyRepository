/*************************************************
  �ļ���   ��ShieldDoorData.c
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� ShieldDoorData���ݹ���
			DmuCommonData�����ShieldDoorData���ܿɷֽ����£�
			1��	��ShieldDoorDataStru�ṹ��ָ�����ռ�
			2��	��ȡShieldDoorData����
			3��	��ȡShieldDoorData��Ϣ
			4��	��ȡָ��IDShieldDoorDataStru�Ľṹ���±�
			5��	��ȡָ��IDShieldDoorDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDShieldDoorDataStru������
			7��	��ȡָ��IDShieldDoorDataStru������վ̨���
			8��	��ȡ��·���������ID
			9��	��ѯվ̨���ȡ��վ̨��Ӧ��PSD��Ϣ
			10��	��ȡ��SEG��Ӧ��������ID
			11��	��ȡ��·����������ZC
			12��	��ȡ��·����������CI

  ��ע    ���ޡ�
 
*************************************************/

#include "ShieldDoorData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/MemSet.h"
#include "../../../Common/Convert.h"

static BnfShieldDoorStruct* ShieldDoorDataStru = NULL;   /*����ShieldDoorData���ݽṹ��*/
static UINT16_S LineNumShieldDoor = 0u;/*������*/


/*
* ���������� ��ShieldDoorDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocShieldDoorDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == ShieldDoorDataStru))
    {
        ShieldDoorDataStru = (BnfShieldDoorStruct*)MemoryMalloc((UINT32_S)sizeof(BnfShieldDoorStruct) * lineNum);
        if (ShieldDoorDataStru != NULL)
        {
            LineNumShieldDoor = lineNum;
            /*��ֵΪ��Чֵ*/
            MemorySet(ShieldDoorDataStru,lineNum*sizeof(BnfShieldDoorStruct),UINT8_NULL,lineNum*sizeof(BnfShieldDoorStruct));
        }
    }
}

/*
* ���������� ��ȡShieldDoorData����
* ����˵����
* ����ֵ  �� 
            BnfShieldDoorStruct*
*/
BnfShieldDoorStruct *GetShieldDoorData(void)
{
    return ShieldDoorDataStru;
}


/*
* ���������� ��ȡShieldDoorData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfShieldDoorStruct*
*/
BnfShieldDoorStruct *GetShieldDoorDataInfo(UINT16_S* lineNum)
{

    BnfShieldDoorStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumShieldDoor;
        retVal = ShieldDoorDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDShieldDoorDataStru�Ľṹ���±�
* ����˵���� const UINT16_S shieldDoorId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetShieldDoorDataStruIndex(const UINT16_S shieldDoorId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumShieldDoor; i++)
    {
        if (shieldDoorId == ShieldDoorDataStru[i].shieldDoorId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDShieldDoorDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S shieldDoorId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfShieldDoorStruct* GetIndexIdShieldDoorDataStru(const UINT16_S shieldDoorId)
{
    BnfShieldDoorStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetShieldDoorDataStruIndex(shieldDoorId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumShieldDoor)
    {
        retVal = &ShieldDoorDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDShieldDoorDataStru������
* ����˵���� const UINT16_S shieldDoorId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ����
*/ 
UINT8_S* GetShieldDoorDataStruname(const UINT16_S shieldDoorId)
{
    UINT8_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetShieldDoorDataStruIndex(shieldDoorId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumShieldDoor)
    {
        retVal = ShieldDoorDataStru[bufIndex].name;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDShieldDoorDataStru������վ̨���
* ����˵���� const UINT16_S shieldDoorId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����վ̨���
*/ 
UINT16_S GetShieldDoorDataStrustationId(const UINT16_S shieldDoorId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetShieldDoorDataStruIndex(shieldDoorId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumShieldDoor)
    {
        retVal = ShieldDoorDataStru[bufIndex].stationId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* ���������� ��ȡ��·���������ID
* ����˵���� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:���������ID
*/
UINT16_S GetLinePsdMaxId(void)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S shieldDoorId = 0u;/*������ID*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumShieldDoor; i++)
    {
        if (shieldDoorId < ShieldDoorDataStru[i].shieldDoorId)
        {
            shieldDoorId = ShieldDoorDataStru[i].shieldDoorId;
        }
    }

    if(shieldDoorId != 0u)
    {
        retVal = shieldDoorId;
    }

    return retVal;
}


/*
* ���������� ��ѯվ̨���ȡ��վ̨��Ӧ��PSD��Ϣ
* ����˵���� ����:const UINT16_S stationId,վ̨ID
*             const UINT8_S stationIdNum   վ̨����
*             UINT16_S index    ����ƫ��                  
*             �������:UINT16_S psdIdBuff[],������ID����          
* ����ֵ  �� >=0:�����Ÿ���
*/
UINT16_S GetStationIdBelongofPsdInfo(const UINT16_S* stationIdBuff,const UINT8_S stationIdNum,UINT16_S index,UINT16_S psdIdBuff[])
{
    UINT16_S psdIdNum = 0u;/*�����Ÿ���*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S j = 0u;/*ѭ��ʹ��*/

    if ((stationIdBuff != NULL)&&(stationIdNum > 0u)&&(psdIdBuff != NULL))
    {
        for ( i = 0u; i < LineNumShieldDoor; i++)
        {
            for ( j = 0u; j < stationIdNum; j++)
            {
                if (stationIdBuff[j] == ShieldDoorDataStru[i].stationId)
                {
                    psdIdBuff[index] = ShieldDoorDataStru[i].shieldDoorId;
                    index=index+1;
                    psdIdBuff[index] = LINEOBS_PLATFORM;
                    index=index+1;
                    psdIdNum++;
                    break;
                }
            }
        }
    }
    return psdIdNum;
}

/*
** ���������� ��ȡ��SEG��Ӧ��������ID
* ����˵���� const UINT16_S pPlatformId;վ̨ID
*             const UINT8_S platformNum  վ̨ID����
*             UINT16_S*  pPsdId          ������IDָ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �����Ÿ���
*/ 
UINT8_S GetPsdIdAccordPlatformIdBuff(const UINT16_S* pPlatformId,const UINT8_S platformNum,UINT16_S* pPsdId)
{
    UINT8_S retVal = 0u;

    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S  j = 0u;/*ѭ��ʹ��*/

    UINT8_S index = 0u;/*�����±�*/

    if (((platformNum <= TWO_POINT_STATION_NUM_MAX)&&(platformNum > 0u))
        &&(pPlatformId != NULL)&&(pPsdId != NULL))
    {
        for ( i = 0u;( i < LineNumShieldDoor)&&(index < TWO_POINT_STATION_NUM_MAX); i++)
        {
            for ( j = 0u; j < platformNum; j++)
            {
                if (pPlatformId[j] == ShieldDoorDataStru[i].stationId)
                {
                    pPsdId[index] = ShieldDoorDataStru[i].shieldDoorId;
                    index=index+1;
                    break;
                }
            }
        }

        if ((index <= TWO_POINT_PSD_NUM_MAX)&&(i == LineNumShieldDoor))
        {
            retVal = index;
        }
    }

    return retVal;
}

/*
* ���������� ��ȡ��·����������ZC
* ����˵���� const UINT16_S psdId,������ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����ZCId
*/
UINT16_S GetLinePsdBelongZcId(const UINT16_S psdId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetShieldDoorDataStruIndex(psdId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumShieldDoor)
    {
        retVal = ShieldDoorDataStru[bufIndex].manageZCId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* ���������� ��ȡ��·����������CI
* ����˵���� const UINT16_S psdId,������ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����CIId
*/
UINT16_S GetLinePsdBelongCiId(const UINT16_S psdId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetShieldDoorDataStruIndex(psdId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumShieldDoor)
    {
        retVal = ShieldDoorDataStru[bufIndex].manageCIId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}
