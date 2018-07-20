/*************************************************
  �ļ���   ��BlocApptchSectionData.c
  ����     ������      
  ����ʱ�� ��2016-8-11
  �������� �� BaliseData���ݹ���
			DmuCommonData�����BlocApptchSectionData���ܿɷֽ����£�
			1��	��BlocApptchSectionDataStru�ṹ��ָ�����ռ�
			2��	��ȡBlocApptchSectionData����
			3��	��ȡBlocApptchSectionData��Ϣ
			4��	��ȡָ��IDBlocApptchSectionDataStru�Ľṹ���±�
			5��	��ȡָ��IDBlocApptchSectionDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDBlocApptchSectionDataStru�İ����ļ���������Ŀ
			7��	��ȡָ��IDBlocApptchSectionDataStru�İ����ļ������α��
  ��ע    ���ޡ�
 
*************************************************/

#include "BlocApptchSectionData.h"
#include "../../../Common/Malloc.h"

static BnfBlocApptchSectionStruct* BlocApptchSectionDataStru = NULL;   /*����BlocApptchSectionData���ݽṹ��*/
static UINT16_S LineNumBlocApptchSection = 0u;/*������*/


/*
* ���������� ��BlocApptchSectionDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocBlocApptchSectionDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == BlocApptchSectionDataStru))
    {
        BlocApptchSectionDataStru = (BnfBlocApptchSectionStruct*)MemoryMalloc((UINT32_S)sizeof(BnfBlocApptchSectionStruct) * lineNum);
        LineNumBlocApptchSection = lineNum;
    }
}

/*
* ���������� ��ȡBlocApptchSectionData����
* ����˵����
* ����ֵ  �� 
BnfBlocApptchSectionStruct*
*/
BnfBlocApptchSectionStruct *GetBlocApptchSectionData(void)
{
    return BlocApptchSectionDataStru;
}


/*
* ���������� ��ȡBlocApptchSectionData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
BnfBlocApptchSectionStruct*
*/
BnfBlocApptchSectionStruct *GetBlocApptchSectionDataInfo(UINT16_S* lineNum)
{
    BnfBlocApptchSectionStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumBlocApptchSection;
        retVal =  BlocApptchSectionDataStru;

    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDBlocApptchSectionDataStru�Ľṹ���±�
* ����˵���� const UINT16_S blocApptchSectionId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetBlocApptchSectionDataStruIndex(const UINT16_S blocApptchSectionId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumBlocApptchSection; i++)
    {
        if (blocApptchSectionId == BlocApptchSectionDataStru[i].blocApptchSectionId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDBlocApptchSectionDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S blocApptchSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfBlocApptchSectionStruct* GetIndexIdBlocApptchSectionDataStru(const UINT16_S blocApptchSectionId)
{
    BnfBlocApptchSectionStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetBlocApptchSectionDataStruIndex(blocApptchSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumBlocApptchSection)
    {
        retVal = &BlocApptchSectionDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDBlocApptchSectionDataStru�İ����ļ���������Ŀ
* ����˵���� const UINT16_S blocApptchSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �����ļ���������Ŀ
*/ 
UINT16_S GetBlocApptchSectionDataStruincludeAxleSgmtNum(const UINT16_S blocApptchSectionId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetBlocApptchSectionDataStruIndex(blocApptchSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumBlocApptchSection)
    {
        retVal = BlocApptchSectionDataStru[bufIndex].includeAxleSgmtNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDBlocApptchSectionDataStru�İ����ļ������α��
* ����˵���� const UINT16_S blocApptchSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: �����ļ������α��
*/ 
UINT16_S* GetBlAppSectDataInAxSgmtId(const UINT16_S blocApptchSectionId)
{
    UINT16_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetBlocApptchSectionDataStruIndex(blocApptchSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumBlocApptchSection)
    {
        retVal = BlocApptchSectionDataStru[bufIndex].includeAxleSgmtId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

