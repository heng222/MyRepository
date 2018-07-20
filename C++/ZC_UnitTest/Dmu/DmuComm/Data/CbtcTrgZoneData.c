/*************************************************
  �ļ���   ��CbtcTrgZoneData.c
  ����     ������      
  ����ʱ�� ��2016-8-11
  �������� �� CbtcTrgZoneData���ݹ���
			DmuCommonData�����CbtcTrgZoneData���ܿɷֽ����£�
			1��	��CbtcTrgZoneDataStru�ṹ��ָ�����ռ�
			2��	��ȡCbtcTrgZoneData����
			3��	��ȡCbtcTrgZoneData��Ϣ
			4��	��ȡָ��IDCbtcTrgZoneDataStru�Ľṹ���±�
			5��	��ȡָ��IDCbtcTrgZoneDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDCbtcTrgZoneDataStru�İ������߼����ε���Ŀ
			7��	��ȡָ��IDCbtcTrgZoneDataStru�İ������߼����εı��
  ��ע    ���ޡ�
 
*************************************************/

#include "CbtcTrgZoneData.h"
#include "../../../Common/Malloc.h"

static BnfCbtcTrgZoneStruct* CbtcTrgZoneDataStru = NULL;   /*����CbtcTrgZoneData���ݽṹ��*/
static UINT16_S LineNumCbtcTrgZone = 0u;/*������*/


/*
* ���������� ��CbtcTrgZoneDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocCbtcTrgZoneDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == CbtcTrgZoneDataStru))
    {
        CbtcTrgZoneDataStru = (BnfCbtcTrgZoneStruct*)MemoryMalloc((UINT32_S)sizeof(BnfCbtcTrgZoneStruct) * lineNum);
        LineNumCbtcTrgZone = lineNum;
    }
}

/*
* ���������� ��ȡCbtcTrgZoneData����
* ����˵����
* ����ֵ  �� 
            BnfCbtcTrgZoneStruct*
*/
BnfCbtcTrgZoneStruct *GetCbtcTrgZoneData(void)
{
    return CbtcTrgZoneDataStru;
}


/*
* ���������� ��ȡCbtcTrgZoneData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfCbtcTrgZoneStruct*
*/
BnfCbtcTrgZoneStruct *GetCbtcTrgZoneDataInfo(UINT16_S* lineNum)
{

    BnfCbtcTrgZoneStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumCbtcTrgZone;
        retVal =  CbtcTrgZoneDataStru;

    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDCbtcTrgZoneDataStru�Ľṹ���±�
* ����˵���� const UINT16_S cbtcApptchSectionId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetCbtcTrgZoneDataStruIndex(const UINT16_S cbtcApptchSectionId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumCbtcTrgZone; i++)
    {
        if (cbtcApptchSectionId == CbtcTrgZoneDataStru[i].cbtcApptchSectionId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDCbtcTrgZoneDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S cbtcApptchSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfCbtcTrgZoneStruct* GetIndexIdCbtcTrgZoneDataStru(const UINT16_S cbtcApptchSectionId)
{
    BnfCbtcTrgZoneStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetCbtcTrgZoneDataStruIndex(cbtcApptchSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumCbtcTrgZone)
    {
        retVal = &CbtcTrgZoneDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDCbtcTrgZoneDataStru�İ������߼����ε���Ŀ
* ����˵���� const UINT16_S cbtcApptchSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������߼����ε���Ŀ
*/ 
UINT16_S GetCbtcTrgZoneDataStruincludeLgcZoneNum(const UINT16_S cbtcApptchSectionId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetCbtcTrgZoneDataStruIndex(cbtcApptchSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumCbtcTrgZone)
    {
        retVal = CbtcTrgZoneDataStru[bufIndex].includeLgcZoneNum;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDCbtcTrgZoneDataStru�İ������߼����εı��
* ����˵���� const UINT16_S cbtcApptchSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: �������߼����εı��
*/ 
UINT16_S* GetCbtcTrgZoDataInLgcZoId(const UINT16_S cbtcApptchSectionId)
{
    UINT16_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetCbtcTrgZoneDataStruIndex(cbtcApptchSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumCbtcTrgZone)
    {
        retVal = CbtcTrgZoneDataStru[bufIndex].includeLgcZoneId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

