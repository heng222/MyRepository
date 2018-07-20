/*************************************************
  �ļ���   ��ProtectZoneData.c
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� ProtectZoneData���ݹ���
			DmuCommonData�����ProtectZoneData���ܿɷֽ����£�
			1��	��ProtectZoneDataStru�ṹ��ָ�����ռ�
			2��	��ȡProtectZoneData����
			3��	��ȡProtectZoneData��Ϣ
			4��	��ȡָ��IDProtectZoneDataStru�Ľṹ���±�
			5��	��ȡָ��IDProtectZoneDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDProtectZoneDataStru�İ����ļ���������Ŀ
			7��	��ȡָ��IDProtectZoneDataStru�İ����ļ������α��
			8��	��ȡ��·�����������ID
			9��	��ȡ�������ΰ����ļ���������Ϣ
			10��	��ȡ��·������������ZC
			11��	��ȡ��·�����������ID
  ��ע    ���ޡ�
 
*************************************************/

#include "ProtectZoneData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/MemSet.h"
#include "../../../Common/Copy.h"

static BnfProtectZoneStruct* ProtectZoneDataStru = NULL;   /*����ProtectZoneData���ݽṹ��*/
static UINT16_S LineNumProtectZone = 0u;/*������*/


/*
* ���������� ��ProtectZoneDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocProtectZoneDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == ProtectZoneDataStru))
    {
        ProtectZoneDataStru = (BnfProtectZoneStruct*)MemoryMalloc((UINT32_S)sizeof(BnfProtectZoneStruct) * lineNum);
        if (ProtectZoneDataStru != NULL)
        {
            LineNumProtectZone = lineNum;
            /*��ֵΪ��Чֵ*/
            MemorySet(ProtectZoneDataStru,lineNum*sizeof(BnfProtectZoneStruct),UINT8_NULL,lineNum*sizeof(BnfProtectZoneStruct));
        }
    }
}

/*
* ���������� ��ȡProtectZoneData����
* ����˵����
* ����ֵ  �� 
            BnfProtectZoneStruct*
*/
BnfProtectZoneStruct *GetProtectZoneData(void)
{
    return ProtectZoneDataStru;
}


/*
* ���������� ��ȡProtectZoneData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfProtectZoneStruct*
*/
BnfProtectZoneStruct *GetProtectZoneDataInfo(UINT16_S* lineNum)
{

    BnfProtectZoneStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumProtectZone;
        retVal = ProtectZoneDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDProtectZoneDataStru�Ľṹ���±�
* ����˵���� const UINT16_S protectZoneId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetProtectZoneDataStruIndex(const UINT16_S protectZoneId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumProtectZone; i++)
    {
        if (protectZoneId == ProtectZoneDataStru[i].protectZoneId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDProtectZoneDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S protectZoneId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfProtectZoneStruct* GetIndexIdProtectZoneDataStru(const UINT16_S protectZoneId)
{
    BnfProtectZoneStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetProtectZoneDataStruIndex(protectZoneId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumProtectZone)
    {
        retVal = &ProtectZoneDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDProtectZoneDataStru�İ����ļ���������Ŀ
* ����˵���� const UINT16_S protectZoneId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �����ļ���������Ŀ
*/ 
UINT16_S GetProtectZoneDataStruincludeAxleSgmtNum(const UINT16_S protectZoneId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetProtectZoneDataStruIndex(protectZoneId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumProtectZone)
    {
        retVal = ProtectZoneDataStru[bufIndex].includeAxleSgmtNum;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDProtectZoneDataStru�İ����ļ������α��
* ����˵���� const UINT16_S protectZoneId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: �����ļ������α��
*/ 
UINT16_S* GetProtZoDataInAxleSgmtId(const UINT16_S protectZoneId)
{
    UINT16_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetProtectZoneDataStruIndex(protectZoneId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumProtectZone)
    {
        retVal = ProtectZoneDataStru[bufIndex].includeAxleSgmtId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* ���������� ��ȡ��·�����������ID
* ����˵���� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0: ��·�����������ID
*/
UINT16_S GetLineOverlapMaxId(void)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S protectZoneId = 0u;/*��·��������ID*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumProtectZone; i++)
    {
        if (protectZoneId < ProtectZoneDataStru[i].protectZoneId)
        {
            protectZoneId = ProtectZoneDataStru[i].protectZoneId;
        }
    }

    if(protectZoneId != 0u)
    {
        retVal = protectZoneId;
    }

    return retVal;
}


/*
* ���������� ��ȡ�������ΰ����ļ���������Ϣ
* ����˵���� const UINT16_S protectZoneId,��������ID
*            UINT16_S* pAcIdBuf����������ID����
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:������������
*/
UINT16_S GetLineOverlapOfAcInfo(const UINT16_S protectZoneId,UINT16_S* pAcIdBuf)
{
    UINT16_S retVal = UINT16_NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetProtectZoneDataStruIndex(protectZoneId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumProtectZone)
    {
        MemoryCpy(pAcIdBuf,sizeof(UINT16_S)*PROTECTZONE_AXLESGM_MAX_NUM,ProtectZoneDataStru[bufIndex].includeAxleSgmtId,sizeof(UINT16_S)*PROTECTZONE_AXLESGM_MAX_NUM);
        retVal = ProtectZoneDataStru[bufIndex].includeAxleSgmtNum;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* ���������� ��ȡ��·������������ZC
* ����˵���� const UINT16_S overlapId,��������ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����ZCId
*/
UINT16_S GetLineOverlapBelongZcId(const UINT16_S overlapId)
{
    UINT16_S retVal = UINT16_NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetProtectZoneDataStruIndex(overlapId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumProtectZone)
    {
        retVal = ProtectZoneDataStru[bufIndex].manageZCId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* ���������� ��ȡ��·�����������ID
����CI
* ����˵���� const UINT16_S overlapId,��������ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����ciId
*/
UINT16_S GetLineOverlapBelongCiId(const UINT16_S overlapId)
{
    UINT16_S retVal = UINT16_NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetProtectZoneDataStruIndex(overlapId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumProtectZone)
    {
        retVal = ProtectZoneDataStru[bufIndex].manageCIId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

