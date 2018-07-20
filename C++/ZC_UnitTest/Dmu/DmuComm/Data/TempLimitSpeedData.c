/*************************************************
  �ļ���   ��TempLimitSpeedData.c
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� TempLimitSpeedData���ݹ���
			DmuCommonData�����TempLimitSpeedData���ܿɷֽ����£�
			1��	��TempLimitSpeedDataStru�ṹ��ָ�����ռ�
			2��	��ȡTempLimitSpeedData����
			3��	��ȡTempLimitSpeedData��Ϣ
			4��	��ȡָ��IDTempLimitSpeedDataStru��һ�����õ���ʱ����������
			5��	��ȡָ��IDTempLimitSpeedDataStru��һ����ʱ���ٱ����а���������߼���������
  ��ע    ���ޡ� 
*************************************************/

#include "TempLimitSpeedData.h"
#include "../../../Common/Malloc.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"

static BnfTempLimitSpeedStruct* TempLimitSpeedDataStru = NULL;   /*����TempLimitSpeedData���ݽṹ��*/
static UINT16_S LineNumTempLimitSpeed = 0u;/*������*/


/*
* ���������� ��TempLimitSpeedDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocTempLimitSpeedDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == TempLimitSpeedDataStru))
    {
        TempLimitSpeedDataStru = (BnfTempLimitSpeedStruct*)MemoryMalloc((UINT32_S)sizeof(BnfTempLimitSpeedStruct) * lineNum);
        LineNumTempLimitSpeed = lineNum;
    }
}

/*
* ���������� ��ȡTempLimitSpeedData����
* ����˵����
* ����ֵ  �� 
            BnfTempLimitSpeedStruct*
*/
BnfTempLimitSpeedStruct *GetTempLimitSpeedData(void)
{
    return TempLimitSpeedDataStru;
}


/*
* ���������� ��ȡTempLimitSpeedData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfTempLimitSpeedStruct*
*/
BnfTempLimitSpeedStruct *GetTempLimitSpeedDataInfo(UINT16_S* lineNum)
{
    BnfTempLimitSpeedStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumTempLimitSpeed;
        retVal = TempLimitSpeedDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDTempLimitSpeedDataStru��һ�����õ���ʱ����������
* ����˵��:  ��
* ����ֵ  :  UINT16_NULL: ��ȡ����ʧ��
*            <UINT16_NULL: һ�����õ���ʱ����������
*/ 
UINT16_S GetTempLimitSpeedDataStruoneSetMaxNum(void)
{
    UINT16_S retVal = UINT16_NULL;/*��������ֵ*/
    if (NULL != TempLimitSpeedDataStru)
    {
        retVal = TempLimitSpeedDataStru[0].oneSetMaxNum;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDTempLimitSpeedDataStru��һ����ʱ���ٱ����а���������߼���������
* ����˵��:  ��
* ����ֵ  :  UINT16_NULL: ��ȡ����ʧ��
*            <UINT16_NULL: һ����ʱ���ٱ����а���������߼���������
*/ 
UINT16_S GetTempLimitSpeedDataStruincludeLgcSectionNum(void)
{
    UINT16_S retVal = UINT16_NULL;/*��������ֵ*/
    if (NULL != TempLimitSpeedDataStru)
    {
        retVal = TempLimitSpeedDataStru[0].includeLgcSectionNum;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

