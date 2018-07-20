/*************************************************
  �ļ���   ��BlocTrgZoneData.c
  ����     ������      
  ����ʱ�� ��2016-8-11
  �������� �� BlocTrgZoneData���ݹ���
			DmuCommonData�����BlocTrgZoneData���ܿɷֽ����£�
			1��	��BlocTrgZoneDataStru�ṹ��ָ�����ռ�
			2��	��ȡBlocTrgZoneData����
			3��	��ȡBlocTrgZoneData��Ϣ
			4��	��ȡָ��IDBlocTrgZoneDataStru�Ľṹ���±�
			5��	��ȡָ��IDBlocTrgZoneDataStru�Ľṹ��ָ��
			6��	 ��ȡָ��IDBlocTrgZoneDataStru�İ����ļ���������Ŀ
			7��	��ȡָ��IDBlocTrgZoneDataStru�İ����ļ������α��

  ��ע    ���ޡ�
 
*************************************************/

#include "BlocTrgZoneData.h"
#include "../../../Common/Malloc.h"

static BnfBlocTrgZoneStruct* BlocTrgZoneDataStru = NULL;   /*����BlocTrgZoneData���ݽṹ��*/
static UINT16_S LineNumBlocTrgZone = 0u;/*������*/


/*
* ���������� ��BlocTrgZoneDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocBlocTrgZoneDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == BlocTrgZoneDataStru))
    {
        BlocTrgZoneDataStru = (BnfBlocTrgZoneStruct*)MemoryMalloc((UINT32_S)sizeof(BnfBlocTrgZoneStruct) * lineNum);
        LineNumBlocTrgZone = lineNum;
    }
}

/*
* ���������� ��ȡBlocTrgZoneData����
* ����˵����
* ����ֵ  �� 
BnfBlocTrgZoneStruct*
*/
BnfBlocTrgZoneStruct *GetBlocTrgZoneData(void)
{
    return BlocTrgZoneDataStru;
}


/*
* ���������� ��ȡBlocTrgZoneData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
BnfBlocTrgZoneStruct*
*/
BnfBlocTrgZoneStruct *GetBlocTrgZoneDataInfo(UINT16_S* lineNum)
{

    BnfBlocTrgZoneStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumBlocTrgZone;
        retVal =  BlocTrgZoneDataStru;

    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDBlocTrgZoneDataStru�Ľṹ���±�
* ����˵���� const UINT16_S blocApptchSectionId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetBlocTrgZoneDataStruIndex(const UINT16_S blocApptchSectionId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumBlocTrgZone; i++)
    {
        if (blocApptchSectionId == BlocTrgZoneDataStru[i].blocApptchSectionId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDBlocTrgZoneDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S blocApptchSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfBlocTrgZoneStruct* GetIndexIdBlocTrgZoneDataStru(const UINT16_S blocApptchSectionId)
{
    BnfBlocTrgZoneStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetBlocTrgZoneDataStruIndex(blocApptchSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumBlocTrgZone)
    {
        retVal = &BlocTrgZoneDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDBlocTrgZoneDataStru�İ����ļ���������Ŀ
* ����˵���� const UINT16_S blocApptchSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �����ļ���������Ŀ
*/ 
UINT16_S GetBlocTrgZoneDataStruincludeAxleSgmtNum(const UINT16_S blocApptchSectionId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetBlocTrgZoneDataStruIndex(blocApptchSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumBlocTrgZone)
    {
        retVal = BlocTrgZoneDataStru[bufIndex].includeAxleSgmtNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDBlocTrgZoneDataStru�İ����ļ������α��
* ����˵���� const UINT16_S blocApptchSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: �����ļ������α��
*/ 
UINT16_S* GetBlTrgZoDataInAxleSegmId(const UINT16_S blocApptchSectionId)
{
    UINT16_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetBlocTrgZoneDataStruIndex(blocApptchSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumBlocTrgZone)
    {
        retVal = BlocTrgZoneDataStru[bufIndex].includeAxleSgmtId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

