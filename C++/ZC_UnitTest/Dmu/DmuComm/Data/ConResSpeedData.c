/*************************************************
  �ļ���   ��ConResSpeedData.c
  ����     ������      
  ����ʱ�� ��2016-8-11
  �������� �� ConResSpeedData���ݹ���
			DmuCommonData�����ConResSpeedData���ܿɷֽ����£�
			1��	��BnfConResSpeedStruct�ṹ��ָ�����ռ�
			2��	��ȡConResSpeed����
			3��	��ȡConResSpeed��Ϣ
			4��	��ȡͳһ���ٱ��е�����ֵ

  ��ע    ���ޡ�
 
*************************************************/

#include "ConResSpeedData.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/Copy.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"

static BnfConResSpeedStruct* ConResSpeedDataStru = NULL;   /*����ConResSpeed���ݽṹ��*/
static UINT16_S LineNumConResSpeed = 0u;/*������*/


/*
* ���������� ��BnfConResSpeedStruct�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocConResSpeedDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == ConResSpeedDataStru))
    {
        ConResSpeedDataStru = (BnfConResSpeedStruct*)MemoryMalloc((UINT32_S)sizeof(BnfConResSpeedStruct) * lineNum);
        LineNumConResSpeed = lineNum;
    }
}

/*
* ���������� ��ȡConResSpeed����
* ����˵����
* ����ֵ  �� 
            BnfConResSpeedStruct*
*/
BnfConResSpeedStruct *GetConResSpeedData(void)
{
    return ConResSpeedDataStru;
}


/*
* ���������� ��ȡConResSpeed��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfConResSpeedStruct*
*/
BnfConResSpeedStruct *GetConResSpeedDataInfo(UINT16_S* lineNum)
{

    BnfConResSpeedStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumConResSpeed;
        retVal =  ConResSpeedDataStru;

    }
    return retVal;
}

/*
* ���������� ��ȡͳһ���ٱ��е�����ֵ
* ����˵������
* ����ֵ  ��0xFFFF ��Ч
            ����:��Ч
*/
UINT16_S GetConResSpeedValue(void)
{
    UINT16_S retVal = UINT16_NULL;
    if (NULL != ConResSpeedDataStru)
    {
        retVal = ConResSpeedDataStru[0].resSpeed;
    }

    return retVal;
}
