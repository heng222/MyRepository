/*************************************************
  �ļ���   ��PointData.c
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� PointData���ݹ���
			DmuCommonData�����PointData���ܿɷֽ����£�
			1��	��PointDataStru�ṹ��ָ�����ռ�
			2��	��ȡPointData����
			3��	��ȡPointData��Ϣ
			4��	��ȡָ��IDPointDataStru�Ľṹ���±�
			5��	��ȡָ��IDPointDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDPointDataStru������
			7��	��ȡָ��IDPointDataStru�����������
			8��	��ȡָ��IDPointDataStru�Ĺ����(cm)
			9��	��ȡָ��IDPointDataStru�ĵ�����
			10��	��ȡָ��IDPointDataStru������������ڵ�ID
			11��	��ȡָ��IDPointDataStru�����������ڵ�ID
			12��	��ȡָ��IDPointDataStru���յ��������ڵ�ID
			13��	��ȡָ��IDPointDataStru���յ�������ڵ�ID
			14��	��ȡָ��IDPointDataStru������ZC������
			15��	��ȡָ��IDPointDataStru������ATS������
			16��	��ȡָ��IDPointDataStru����������CI������
  ��ע    ���ޡ�
 
*************************************************/

#include "PointData.h"
#include "../../../Common/Malloc.h"

static BnfPointStruct* PointDataStru = NULL;   /*����PointData���ݽṹ��*/
static UINT16_S LineNumPoint = 0u;/*������*/


/*
* ���������� ��PointDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocPointDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == PointDataStru))
    {
        PointDataStru = (BnfPointStruct*)MemoryMalloc((UINT32_S)sizeof(BnfPointStruct) * lineNum);
        LineNumPoint = lineNum;
    }
}

/*
* ���������� ��ȡPointData����
* ����˵����
* ����ֵ  �� 
            BnfPointStruct*
*/
BnfPointStruct *GetPointData(void)
{
    return PointDataStru;
}


/*
* ���������� ��ȡPointData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfPointStruct*
*/
BnfPointStruct *GetPointDataInfo(UINT16_S* lineNum)
{

    BnfPointStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumPoint;
        retVal = PointDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDPointDataStru�Ľṹ���±�
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetPointDataStruIndex(const UINT16_S indexId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumPoint; i++)
    {
        if (indexId == PointDataStru[i].indexId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDPointDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfPointStruct* GetIndexIdPointDataStru(const UINT16_S indexId)
{
    BnfPointStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetPointDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumPoint)
    {
        retVal = &PointDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDPointDataStru������
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ����
*/ 
UINT8_S* GetPointDataStruname(const UINT16_S indexId)
{
    UINT8_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetPointDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].name;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDPointDataStru�����������
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���������
*/ 
UINT8_S* GetPointDataStrustartPathwayName(const UINT16_S indexId)
{
    UINT8_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetPointDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].startPathwayName;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDPointDataStru�Ĺ����(cm)
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �����(cm)
*/ 
UINT32_S GetPointDataStrulocation(const UINT16_S indexId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetPointDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].location;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDPointDataStru�ĵ�����
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ������
*/ 
UINT16_S GetPointDataStrupointType(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetPointDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].pointType;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDPointDataStru������������ڵ�ID
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����������ڵ�ID
*/ 
UINT16_S GetPointDataStrustartJointMainLkId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetPointDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].startJointMainLkId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDPointDataStru�����������ڵ�ID
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ���������ڵ�ID
*/ 
UINT16_S GetPointDataStrustartJointSideLkId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetPointDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].startJointSideLkId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDPointDataStru���յ��������ڵ�ID
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ��������ڵ�ID
*/ 
UINT16_S GetPointDataStrutmnlJointMainLkId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetPointDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].tmnlJointMainLkId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDPointDataStru���յ�������ڵ�ID
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�������ڵ�ID
*/ 
UINT16_S GetPointDataStrutmnlJointSideLkId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetPointDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].tmnlJointSideLkId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDPointDataStru������ZC������
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����ZC������
*/ 
UINT16_S GetPointDataStrumanageZCId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetPointDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].manageZCId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDPointDataStru������ATS������
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����ATS������
*/ 
UINT16_S GetPointDataStrumanageATSId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetPointDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].manageATSId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDPointDataStru����������CI������
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��������CI������
*/ 
UINT16_S GetPointDataStrumanageCIId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetPointDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].manageCIId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

