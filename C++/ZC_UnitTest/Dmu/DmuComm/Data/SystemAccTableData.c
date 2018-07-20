/*************************************************
  �ļ���   ��SystemAccTableData.c
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� SystemAccTableData���ݹ���
			DmuCommonData�����SystemAccTableData���ܿɷֽ����£�
			1��	��SystemAccTableDataStru�ṹ��ָ�����ռ�
			2��	��ȡSystemAccTableData����
			3��	��ȡSystemAccTableData��Ϣ
			4��	��ȡָ��IDSystemAccTableDataStru�Ľṹ���±�
			5��	��ȡָ��IDSystemAccTableDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDSystemAccTableDataStru�ķֶ��ٶ����ޡ����ݳ����ṩ��ǣ���������߷ֶεó�����λkm/h
			7��	��ȡָ��IDSystemAccTableDataStru�ķֶ��ٶ����ޡ����ݳ����ṩ��ǣ���������߷ֶεó�����λkm/h
			8��	��ȡָ��IDSystemAccTableDataStru�ķֶμ��ٶ�ֵ�����ݳ����ṩ��ǣ���������߷ֶεó�����λcm/s2
			9��	��ȡǣ�����ٶ�

  ��ע    ���ޡ�
 
*************************************************/

#include "SystemAccTableData.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/UnitConver.h"

static BnfSystemAccTableStruct* SystemAccTableDataStru = NULL;   /*����SystemAccTableData���ݽṹ��*/
static UINT16_S LineNumSystemAccTable = 0u;/*������*/


/*
* ���������� ��SystemAccTableDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocSystemAccTableDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == SystemAccTableDataStru))
    {
        SystemAccTableDataStru = (BnfSystemAccTableStruct*)MemoryMalloc((UINT32_S)sizeof(BnfSystemAccTableStruct) * lineNum);
        LineNumSystemAccTable = lineNum;
    }
}

/*
* ���������� ��ȡSystemAccTableData����
* ����˵����
* ����ֵ  �� 
            BnfSystemAccTableStruct*
*/
BnfSystemAccTableStruct *GetSystemAccTableData(void)
{
    return SystemAccTableDataStru;
}


/*
* ���������� ��ȡSystemAccTableData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfSystemAccTableStruct*
*/
BnfSystemAccTableStruct *GetSystemAccTableDataInfo(UINT16_S* lineNum)
{

    BnfSystemAccTableStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumSystemAccTable;
        retVal = SystemAccTableDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDSystemAccTableDataStru�Ľṹ���±�
* ����˵���� const UINT8_S trainType;�г�����
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetSystemAccTableDataStruIndex(const UINT8_S trainType)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumSystemAccTable; i++)
    {
        if (trainType == SystemAccTableDataStru[i].trainType)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSystemAccTableDataStru�Ľṹ��ָ��
* ����˵���� const UINT8_S trainType;�г�����
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfSystemAccTableStruct* GetIndexIdSystemAccTableDataStru(const UINT8_S trainType)
{
    BnfSystemAccTableStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSystemAccTableDataStruIndex(trainType);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSystemAccTable)
    {
        retVal = &SystemAccTableDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSystemAccTableDataStru�ķֶ��ٶ����ޡ����ݳ����ṩ��ǣ���������߷ֶεó�����λkm/h
* ����˵���� const UINT8_S trainType;�г�����
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �ֶ��ٶ����ޡ����ݳ����ṩ��ǣ���������߷ֶεó�����λkm/h
*/ 
UINT8_S GetSystemAccTableDataStrulowerLimitSpeed(const UINT8_S trainType)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSystemAccTableDataStruIndex(trainType);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSystemAccTable)
    {
        retVal = SystemAccTableDataStru[bufIndex].lowerLimitSpeed;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSystemAccTableDataStru�ķֶ��ٶ����ޡ����ݳ����ṩ��ǣ���������߷ֶεó�����λkm/h
* ����˵���� const UINT8_S trainType;�г�����
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �ֶ��ٶ����ޡ����ݳ����ṩ��ǣ���������߷ֶεó�����λkm/h
*/ 
UINT8_S GetSystemAccTableDataStruupperLimitSpeed(const UINT8_S trainType)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSystemAccTableDataStruIndex(trainType);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSystemAccTable)
    {
        retVal = SystemAccTableDataStru[bufIndex].upperLimitSpeed;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSystemAccTableDataStru�ķֶμ��ٶ�ֵ�����ݳ����ṩ��ǣ���������߷ֶεó�����λcm/s2
* ����˵���� const UINT8_S trainType;�г�����
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �ֶμ��ٶ�ֵ�����ݳ����ṩ��ǣ���������߷ֶεó�����λcm/s2
*/ 
UINT8_S GetSystemAccTableDataStruaccValue(const UINT8_S trainType)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSystemAccTableDataStruIndex(trainType);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSystemAccTable)
    {
        retVal = SystemAccTableDataStru[bufIndex].accValue;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}


/*
** ���������� ��ȡǣ�����ٶ�
* ����˵���� const UINT8_S trainType;�г�����
*             const UINT16_S trainSpeed �г���ǰ�ٶ�
* ����ֵ  :  ���ٶ�
*/ 
UINT8_S GetTracAcc(const UINT16_S trainSpeed,const UINT8_S trainType)
{
    UINT8_S acc = 0u;
    UINT16_S i = 0u;
    UINT8_S flag = 0u;/*���*/

    if (SystemAccTableDataStru != NULL)
    {
        
        for ( i = 0u; i < LineNumSystemAccTable; i++)
        {
            if (trainType == SystemAccTableDataStru[i].trainType)
            {
                if (0u == flag)
                {
                    acc = SystemAccTableDataStru[i].accValue;
                    flag = 1u;
                }
                else
                {
                    if ((trainSpeed >=KmsConvertCMPS(SystemAccTableDataStru[i].lowerLimitSpeed))
                    &&(trainSpeed < KmsConvertCMPS(SystemAccTableDataStru[i].upperLimitSpeed))
                    )
                    {
                        acc = SystemAccTableDataStru[i].accValue;
                    }
                }
            }
        }
    }

    return acc;
}

