/*************************************************
  �ļ���   ��ConGradeData.c
  ����     ������      
  ����ʱ�� ��2016-8-11
  �������� �� ConGradeData���ݹ���
			DmuCommonData�����ConGradeData���ܿɷֽ����£�
			1��	��BnfConGradeStruct�ṹ��ָ�����ռ�
			2��	��ȡConGrade����
			3��	��ȡConGrade��Ϣ
			4��	��ȡͳһ���ٱ��е��¶�ֵ
  ��ע    ���ޡ�
 
*************************************************/

#include "ConGradeData.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/Copy.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"

static BnfConGradeDataStruct* ConGradeDataStru = NULL;   /*����ConGradeData���ݽṹ��*/
static UINT16_S LineNumConGrade = 0u;/*������*/


/*
* ���������� ��BnfConGradeStruct�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocConGradeDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == ConGradeDataStru))
    {
        ConGradeDataStru = (BnfConGradeDataStruct*)MemoryMalloc((UINT32_S)sizeof(BnfConGradeDataStruct) * lineNum);
        LineNumConGrade = lineNum;
    }
}

/*
* ���������� ��ȡConGrade����
* ����˵����
* ����ֵ  �� 
            BnfConGradeStruct*
*/
BnfConGradeDataStruct *GetConGradeData(void)
{
    return ConGradeDataStru;
}


/*
* ���������� ��ȡConGrade��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfConGradeStruct*
*/
BnfConGradeDataStruct *GetConGradeDataInfo(UINT16_S* lineNum)
{

    BnfConGradeDataStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumConGrade;
        retVal =  ConGradeDataStru;

    }
    return retVal;
}

/*
* ���������� ��ȡͳһ���ٱ��е��¶�ֵ
* ����˵������
* ����ֵ  ��0xFFFF ��Ч
            ����:��Ч
*/
UINT16_S GetConGradeValue(void)
{
    UINT16_S retVal = UINT16_NULL;
    if (NULL != ConGradeDataStru)
    {
        retVal = ConGradeDataStru[0].grade;
    }

    return retVal;
}
