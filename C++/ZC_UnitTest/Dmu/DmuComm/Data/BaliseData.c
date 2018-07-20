/*************************************************
  �ļ���   ��BaliseData.c
  ����     ������      
  ����ʱ�� ��2016-8-11
  �������� �� BaliseData���ݹ���
			DmuCommonData�����BaliseData���ܿɷֽ����£�
			1��	��BaliseDataStru�ṹ��ָ�����ռ�
			2��	��ȡBaliseData����
			3��	��ȡBaliseData��Ϣ
			4��	��ȡָ��IDBaliseDataStru�Ľṹ���±�
			5��	��ȡָ��IDBaliseDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDBaliseDataStru������
			7��	��ȡָ��IDBaliseDataStru������seg���
			8��	��ȡָ��IDBaliseDataStru������Segƫ������cm��


  ��ע    ���ޡ�
 
*************************************************/

#include "BaliseData.h"
#include "../../../Common/Malloc.h"

static BnfBaliseStruct* BaliseDataStru = NULL;   /*����BaliseData���ݽṹ��*/
static UINT16_S LineNumBalise = 0u;/*������*/


/*
* ���������� ��BaliseDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocBaliseDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == BaliseDataStru))
    {
        BaliseDataStru = (BnfBaliseStruct*)MemoryMalloc((UINT32_S)sizeof(BnfBaliseStruct) * lineNum);
        LineNumBalise = lineNum;
    }
}

/*
* ���������� ��ȡBaliseData����
* ����˵����
* ����ֵ  �� 
BnfBaliseStruct*
*/
BnfBaliseStruct *GetBaliseData(void)
{
    return BaliseDataStru;
}


/*
* ���������� ��ȡBaliseData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
BnfBaliseStruct*
*/
BnfBaliseStruct *GetBaliseDataInfo(UINT16_S* lineNum)
{

    BnfBaliseStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumBalise;
        retVal =  BaliseDataStru;

    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDBaliseDataStru�Ľṹ���±�
* ����˵���� const UINT32_S baliseId;Ӧ����ID
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetBaliseDataStruIndex(const UINT32_S baliseId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumBalise; i++)
    {
        if (baliseId == BaliseDataStru[i].baliseId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDBaliseDataStru�Ľṹ��ָ��
* ����˵���� const UINT32_S baliseId;Ӧ����ID
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfBaliseStruct* GetIndexIdBaliseDataStru(const UINT32_S baliseId)
{
    BnfBaliseStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetBaliseDataStruIndex(baliseId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumBalise)
    {
        retVal = &BaliseDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDBaliseDataStru������
* ����˵���� const UINT32_S baliseId;Ӧ����ID
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ����
*/ 
UINT8_S* GetBaliseDataStruname(const UINT32_S baliseId)
{
    UINT8_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetBaliseDataStruIndex(baliseId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumBalise)
    {
        retVal = BaliseDataStru[bufIndex].name;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDBaliseDataStru������seg���
* ����˵���� const UINT32_S baliseId;Ӧ����ID
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����seg���
*/ 
UINT16_S GetBaliseDataStrusegId(const UINT32_S baliseId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetBaliseDataStruIndex(baliseId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumBalise)
    {
        retVal = BaliseDataStru[bufIndex].segId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDBaliseDataStru������Segƫ������cm��
* ����˵���� const UINT32_S baliseId;Ӧ����ID
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����Segƫ������cm��
*/ 
UINT32_S GetBaliseDataStrusegOffset(const UINT32_S baliseId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetBaliseDataStruIndex(baliseId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumBalise)
    {
        retVal = BaliseDataStru[bufIndex].segOffset;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}



