/*************************************************
  �ļ���   ��SectionTypeData.c
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� SectionTypeData���ݹ���
			DmuCommonData�����SectionTypeData���ܿɷֽ����£�
			1��	��SectionTypeDataStru�ṹ��ָ�����ռ�
			2��	��ȡSectionTypeData����
			3��	��ȡSectionTypeData��Ϣ
			4��	��ȡָ��IDSectionTypeDataStru�Ľṹ���±�
			5��	��ȡָ��IDSectionTypeDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDSectionTypeDataStru����������
			7��	��ȡָ��IDSectionTypeDataStru������ID
			8��	��ȡָ��IDSectionTypeDataStru����������
			9��	��ȡָ���豸���ͺ�ID����������

  ��ע    ���ޡ�
 
*************************************************/

#include "SectionTypeData.h"
#include "../../../Common/Malloc.h"

static BnfSectionTypeStruct* SectionTypeDataStru = NULL;   /*����SectionTypeData���ݽṹ��*/
static UINT16_S LineNumSectionType = 0u;/*������*/


/*
* ���������� ��SectionTypeDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocSectionTypeDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == SectionTypeDataStru))
    {
        SectionTypeDataStru = (BnfSectionTypeStruct*)MemoryMalloc((UINT32_S)sizeof(BnfSectionTypeStruct) * lineNum);
        LineNumSectionType = lineNum;
    }
}

/*
* ���������� ��ȡSectionTypeData����
* ����˵����
* ����ֵ  �� 
            BnfSectionTypeStruct*
*/
BnfSectionTypeStruct *GetSectionTypeData(void)
{
    return SectionTypeDataStru;
}


/*
* ���������� ��ȡSectionTypeData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfSectionTypeStruct*
*/
BnfSectionTypeStruct *GetSectionTypeDataInfo(UINT16_S* lineNum)
{

    BnfSectionTypeStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumSectionType;
        retVal = SectionTypeDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDSectionTypeDataStru�Ľṹ���±�
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetSectionTypeDataStruIndex(const UINT16_S indexId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumSectionType; i++)
    {
        if (indexId == SectionTypeDataStru[i].indexId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSectionTypeDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfSectionTypeStruct* GetIndexIdSectionTypeDataStru(const UINT16_S indexId)
{
    BnfSectionTypeStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSectionTypeDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSectionType)
    {
        retVal = &SectionTypeDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSectionTypeDataStru����������
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��������
*/ 
UINT16_S GetSectionTypeDataStrusectionType(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSectionTypeDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSectionType)
    {
        retVal = SectionTypeDataStru[bufIndex].sectionType;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSectionTypeDataStru������ID
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����ID
*/ 
UINT16_S GetSectionTypeDataStrusectionId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSectionTypeDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSectionType)
    {
        retVal = SectionTypeDataStru[bufIndex].sectionId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSectionTypeDataStru����������
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��������
*/ 
UINT8_S GetSectionTypeDataStrusectionProperty(const UINT16_S indexId)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSectionTypeDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSectionType)
    {
        retVal = SectionTypeDataStru[bufIndex].sectionProperty;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}


/*
** ���������� ��ȡָ���豸���ͺ�ID����������
* ����˵���� const UINT16_S devType   �豸����,const UINT16_S devId   �豸ID
* ����ֵ  :  0: ��ȡ����ʧ��
*             >0: ��������
*/ 
UINT8_S GetSecPropertyAccordName(const UINT16_S devType,const UINT16_S devId)
{
    UINT8_S retVal = 0u;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; (i < LineNumSectionType)&&(devId > 0); i++)
    {
        if ((devType == SectionTypeDataStru[i].sectionType)&&(devId == SectionTypeDataStru[i].sectionId))
        {
            retVal = SectionTypeDataStru[i].sectionProperty;
            break;
        }
    }
    return retVal;
}

