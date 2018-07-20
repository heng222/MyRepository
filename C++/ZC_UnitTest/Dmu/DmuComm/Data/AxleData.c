/*************************************************
  �ļ���   ��AxleData.h
  ����     ������      
  ����ʱ�� ��2016-8-10
  �������� �� ����AxleData���ݹ���
			DmuCommonData�����AxleData���ܿɷֽ����£�
				1��	��AxleDataStru�ṹ��ָ�����ռ�
				2��	��ȡAxleData����
				3��	��ȡAxleData��Ϣ
				4��	��ȡָ��IDAxleDataStru�Ľṹ���±�
				5��	��ȡָ��IDAxleDataStru�Ľṹ��ָ��
				6��	��ȡָ��IDAxleDataStru�ļ���������
				7��	��ȡָ��IDAxleDataStru�ļ���������Segƫ����(cm)
  ��ע    ���ޡ�
 
*************************************************/

#include "AxleData.h"
#include "../../../Common/Malloc.h"

static BnfAxleStruct* AxleDataStru = NULL;   /*����AxleData���ݽṹ��*/
static UINT16_S LineNumAxle = 0u;/*������*/


/*
* �������ƣ� MallocAxleDataStru
* ���������� ��AxleDataStru�ṹ��ָ�����ռ�
* ��������� UINT16_S lineNum �����������
* ��������� ��
* ����ֵ  �� void
*/
void MallocAxleDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == AxleDataStru))
    {
        AxleDataStru = (BnfAxleStruct*)MemoryMalloc((UINT32_S)sizeof(BnfAxleStruct) * lineNum);
        LineNumAxle = lineNum;
    }
}

/*
* �������ƣ� GetAxleData
* ���������� ��ȡAxleData����
* ��������� ��
* ��������� ��
* ����ֵ  �� 
            BnfAxleStruct*
*/
BnfAxleStruct *GetAxleData(void)
{
    return AxleDataStru;
}


/*
* �������ƣ� GetAxleDataInfo
* ���������� ��ȡAxleData��Ϣ
* ��������� ��
* ��������� UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfAxleStruct*
*/
BnfAxleStruct *GetAxleDataInfo(UINT16_S* lineNum)
{

    BnfAxleStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumAxle;
        retVal =  AxleDataStru;

    }
    return retVal;
}
/*
* �������ƣ� GetAxleDataStruIndex
* ���������� ��ȡָ��IDAxleDataStru�Ľṹ���±�
* ��������� const UINT16_S axleId;���
* ��������� ��
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetAxleDataStruIndex(const UINT16_S axleId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumAxle; i++)
    {
        if (axleId == AxleDataStru[i].axleId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
* �������ƣ� GetIndexIdAxleDataStru
* ���������� ��ȡָ��IDAxleDataStru�Ľṹ��ָ��
* ��������� const UINT16_S axleId;���
* ��������� ��
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfAxleStruct* GetIndexIdAxleDataStru(const UINT16_S axleId)
{
    BnfAxleStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetAxleDataStruIndex(axleId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumAxle)
    {
        retVal = &AxleDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* �������ƣ� GetAxleDataStruaxleName
* ���������� ��ȡָ��IDAxleDataStru�ļ���������
* ��������� const UINT16_S axleId;���
* ��������� ��
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ����������
*/ 
UINT8_S* GetAxleDataStruaxleName(const UINT16_S axleId)
{
    UINT8_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetAxleDataStruIndex(axleId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumAxle)
    {
        retVal = AxleDataStru[bufIndex].axleName;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* �������ƣ� GetAxleDataStruaxleSegOfst
* ���������� ��ȡָ��IDAxleDataStru�ļ���������Segƫ����(cm)
* ��������� const UINT16_S axleId;���
* ��������� ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����������Segƫ����(cm)
*/ 
UINT32_S GetAxleDataStruaxleSegOfst(const UINT16_S axleId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetAxleDataStruIndex(axleId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumAxle)
    {
        retVal = AxleDataStru[bufIndex].axleSegOfst;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

