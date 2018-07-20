/*************************************************
  �ļ���   ��PhysicalSectionData.c
  ����     ������      
  ����ʱ�� ��2016-8-12
  �������� �� PhysicalSectionData���ݹ���
			DmuCommonData�����PhysicalSectionData���ܿɷֽ����£�
			1��	��LogicSectionDataStru�ṹ��ָ�����ռ�
			2��	��ȡLogicSectionData����
			3��	��ȡLogicSectionData��Ϣ
			4��	��ȡָ��IDLogicSectionDataStru�Ľṹ���±�
			5��	��ȡָ��IDLogicSectionDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDLogicSectionDataStru������
			7��	��ȡָ��IDLogicSectionDataStru���������Seg���
			8��	��ȡָ��IDLogicSectionDataStru���������Segƫ����
			9��	��ȡָ��IDLogicSectionDataStru���յ�����Seg���
			10��	��ȡָ��IDLogicSectionDataStru���յ�����Segƫ����
			11��	��ȡ��·�߼��������ID
			12��	���������SEGID��ȡ�߼����ε���Ϣ
			13��	��ȡ�߼���������ZC
			14��	��ȡ�߼���������CI
			15��	��ȡ�߼���������AC
			16��	��ѯ��SEGǰ�����߼�����
			17��	��ѯ��SEG�󷽵��߼�����
			18��	��ȡ�߼�����ID��������߼�����ID
  ��ע    ���ޡ�
 
*************************************************/

#include "PhysicalSectionData.h"
#include "../../../Common/Malloc.h"

static BnfPhysicalSectionStruct* PhysicalSectionDataStru = NULL;   /*����PhysicalSectionData���ݽṹ��*/
static UINT16_S LineNumPhysicalSection = 0u;/*������*/


/*
* ���������� ��PhysicalSectionDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocPhysicalSectionDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == PhysicalSectionDataStru))
    {
        PhysicalSectionDataStru = (BnfPhysicalSectionStruct*)MemoryMalloc((UINT32_S)sizeof(BnfPhysicalSectionStruct) * lineNum);
        LineNumPhysicalSection = lineNum;
    }
}

/*
* ���������� ��ȡPhysicalSectionData����
* ����˵����
* ����ֵ  �� 
            BnfPhysicalSectionStruct*
*/
BnfPhysicalSectionStruct *GetPhysicalSectionData(void)
{
    return PhysicalSectionDataStru;
}


/*
* ���������� ��ȡPhysicalSectionData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfPhysicalSectionStruct*
*/
BnfPhysicalSectionStruct *GetPhysicalSectionDataInfo(UINT16_S* lineNum)
{
    BnfPhysicalSectionStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumPhysicalSection;
        retVal = PhysicalSectionDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDPhysicalSectionDataStru�Ľṹ���±�
* ����˵���� const UINT16_S physicalStcId;���
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetPhysicalSectionDataStruIndex(const UINT16_S physicalStcId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumPhysicalSection; i++)
    {
        if (physicalStcId == PhysicalSectionDataStru[i].physicalStcId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDPhysicalSectionDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S physicalStcId;���
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfPhysicalSectionStruct* GetIndexIdPhysicalSectionDataStru(const UINT16_S physicalStcId)
{
    BnfPhysicalSectionStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetPhysicalSectionDataStruIndex(physicalStcId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumPhysicalSection)
    {
        retVal = &PhysicalSectionDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDPhysicalSectionDataStru������
* ����˵���� const UINT16_S physicalStcId;���
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ����
*/ 
UINT8_S* GetPhysicalSectionDataStruname(const UINT16_S physicalStcId)
{
    UINT8_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetPhysicalSectionDataStruIndex(physicalStcId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumPhysicalSection)
    {
        retVal = PhysicalSectionDataStru[bufIndex].name;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDPhysicalSectionDataStru�İ�������������Ŀ
* ����˵���� const UINT16_S physicalStcId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��������������Ŀ
*/ 
UINT16_S GetPhysicalSectionDataStruincludeAxleScNum(const UINT16_S physicalStcId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetPhysicalSectionDataStruIndex(physicalStcId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumPhysicalSection)
    {
        retVal = PhysicalSectionDataStru[bufIndex].includeAxleScNum;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDPhysicalSectionDataStru�ļ�����
* ����˵���� const UINT16_S physicalStcId;���
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ������
*/ 
UINT16_S* GetPhysicalSectionDataStruaxleIdBuff(const UINT16_S physicalStcId)
{
    UINT16_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetPhysicalSectionDataStruIndex(physicalStcId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumPhysicalSection)
    {
        retVal = PhysicalSectionDataStru[bufIndex].axleIdBuff;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

