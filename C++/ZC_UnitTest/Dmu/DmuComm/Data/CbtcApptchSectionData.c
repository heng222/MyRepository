/*************************************************
  �ļ���   ��CbtcApptchSectionData.c
  ����     ������      
  ����ʱ�� ��2016-8-11
  �������� �� CbtcApptchSectionData���ݹ���
			DmuCommonData�����CbtcApptchSectionData���ܿɷֽ����£�
			1��	��CbtcApptchSectionDataStru�ṹ��ָ�����ռ�
			2��	��ȡCbtcApptchSectionData����
			3��	��ȡCbtcApptchSectionData��Ϣ
			4��	��ȡָ��IDCbtcApptchSectionDataStru�Ľṹ���±�
			5��	��ȡָ��IDCbtcApptchSectionDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDCbtcApptchSectionDataStru�İ������߼����ε���Ŀ
			7��	��ȡָ��IDCbtcApptchSectionDataStru�İ������߼����εı��


  ��ע    ���ޡ�
 
*************************************************/

#include "CbtcApptchSectionData.h"
#include "../../../Common/Malloc.h"

static BnfCbtcApptchSectionStruct* CbtcApptchSectionDataStru = NULL;   /*����CbtcApptchSectionData���ݽṹ��*/
static UINT16_S LineNumCbtcApptchSection = 0u;/*������*/


/*
* ���������� ��CbtcApptchSectionDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocCbtcApptchSectionDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == CbtcApptchSectionDataStru))
    {
        CbtcApptchSectionDataStru = (BnfCbtcApptchSectionStruct*)MemoryMalloc((UINT32_S)sizeof(BnfCbtcApptchSectionStruct) * lineNum);
        LineNumCbtcApptchSection = lineNum;
    }
}

/*
* ���������� ��ȡCbtcApptchSectionData����
* ����˵����
* ����ֵ  �� 
BnfCbtcApptchSectionStruct*
*/
BnfCbtcApptchSectionStruct *GetCbtcApptchSectionData(void)
{
    return CbtcApptchSectionDataStru;
}


/*
* ���������� ��ȡCbtcApptchSectionData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
BnfCbtcApptchSectionStruct*
*/
BnfCbtcApptchSectionStruct *GetCbtcApptchSectionDataInfo(UINT16_S* lineNum)
{
    BnfCbtcApptchSectionStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumCbtcApptchSection;
        retVal =  CbtcApptchSectionDataStru;

    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDCbtcApptchSectionDataStru�Ľṹ���±�
* ����˵���� const UINT16_S cbtcApptchSectionId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetCbtcApptchSectionDataStruIndex(const UINT16_S cbtcApptchSectionId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumCbtcApptchSection; i++)
    {
        if (cbtcApptchSectionId == CbtcApptchSectionDataStru[i].cbtcApptchSectionId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDCbtcApptchSectionDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S cbtcApptchSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfCbtcApptchSectionStruct* GetIndexIdCbtcApptchSectionDataStru(const UINT16_S cbtcApptchSectionId)
{
    BnfCbtcApptchSectionStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetCbtcApptchSectionDataStruIndex(cbtcApptchSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumCbtcApptchSection)
    {
        retVal = &CbtcApptchSectionDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDCbtcApptchSectionDataStru�İ������߼����ε���Ŀ
* ����˵���� const UINT16_S cbtcApptchSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������߼����ε���Ŀ
*/ 
UINT16_S GetCbtcApptchSectionDataStruincludeLgcZoneNum(const UINT16_S cbtcApptchSectionId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetCbtcApptchSectionDataStruIndex(cbtcApptchSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumCbtcApptchSection)
    {
        retVal = CbtcApptchSectionDataStru[bufIndex].includeLgcZoneNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDCbtcApptchSectionDataStru�İ������߼����εı��
* ����˵���� const UINT16_S cbtcApptchSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: �������߼����εı��
*/ 
UINT16_S* GetCbtcAppSectDataInLgcZoId(const UINT16_S cbtcApptchSectionId)
{
    UINT16_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetCbtcApptchSectionDataStruIndex(cbtcApptchSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumCbtcApptchSection)
    {
        retVal = CbtcApptchSectionDataStru[bufIndex].includeLgcZoneId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

