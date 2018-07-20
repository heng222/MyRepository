/*************************************************
  �ļ���   ��GradeData.c
  ����     ������      
  ����ʱ�� ��2016-8-12
  �������� �� GradeData���ݹ���
			DmuCommonData�����GradeData���ܿɷֽ����£�
			1��	��GradeDataStru�ṹ��ָ�����ռ�
			2��	��ȡGradeData����
			3��	��ȡGradeData������
			4��	��ȡGradeData��Ϣ
			5��	��ȡָ��IDGradeDataStru�Ľṹ���±�
			6��	��ȡָ��IDGradeDataStru�Ľṹ��ָ��
			7��	��ȡָ��IDGradeDataStru���¶��������Seg���
			8��	��ȡָ��IDGradeDataStru���¶��������Segƫ����
			9��	��ȡָ��IDGradeDataStru���¶��յ�����Seg���
			10��	��ȡָ��IDGradeDataStru���¶��յ�����Segƫ����
			11��	��ȡָ��IDGradeDataStru����������¶ȱ��
			12��	��ȡָ��IDGradeDataStru���������¶ȱ��
			13��	��ȡָ��IDGradeDataStru���յ������¶ȱ��
			14��	��ȡָ��IDGradeDataStru���յ�����¶ȱ��
			15��	��ȡָ��IDGradeDataStru���¶�ֵ
			16��	��ȡָ��IDGradeDataStru���¶��������·�߼��������б����
			17��	��ȡָ��IDGradeDataStru�������߰뾶
  ��ע    ���ޡ�
 
*************************************************/

#include "GradeData.h"
#include "../../../Common/Malloc.h"

static BnfGradeStruct* GradeDataStru = NULL;   /*����GradeData���ݽṹ��*/
static UINT16_S LineNumGrade = 0u;/*������*/


/*
* ���������� ��GradeDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocGradeDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == GradeDataStru))
    {
        GradeDataStru = (BnfGradeStruct*)MemoryMalloc((UINT32_S)sizeof(BnfGradeStruct) * lineNum);
        LineNumGrade = lineNum;
    }
}

/*
* ���������� ��ȡGradeData����
* ����˵����
* ����ֵ  �� 
BnfGradeStruct*
*/
BnfGradeStruct *GetGradeData(void)
{
    return GradeDataStru;
}

/*
* ������������ȡGradeData������
* ����˵������
* ����ֵ  ��UINT16
*/
UINT16_S GetGradeDataLineNum(void)
{
    return LineNumGrade;
}


/*
* ���������� ��ȡGradeData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
BnfGradeStruct*
*/
BnfGradeStruct *GetGradeDataInfo(UINT16_S* lineNum)
{

    BnfGradeStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumGrade;
        retVal = GradeDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDGradeDataStru�Ľṹ���±�
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetGradeDataStruIndex(const UINT16_S gradeId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumGrade; i++)
    {
        if (gradeId == GradeDataStru[i].gradeId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDGradeDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfGradeStruct* GetIndexIdGradeDataStru(const UINT16_S gradeId)
{
    BnfGradeStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumGrade)
    {
        retVal = &GradeDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDGradeDataStru���¶��������Seg���
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �¶��������Seg���
*/ 
UINT16_S GetGradeDataStruorgnSegId(const UINT16_S gradeId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].orgnSegId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDGradeDataStru���¶��������Segƫ����
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �¶��������Segƫ����
*/ 
UINT32_S GetGradeDataStruorgnSegOfst(const UINT16_S gradeId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].orgnSegOfst;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDGradeDataStru���¶��յ�����Seg���
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �¶��յ�����Seg���
*/ 
UINT16_S GetGradeDataStrutmnlSegId(const UINT16_S gradeId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].tmnlSegId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDGradeDataStru���¶��յ�����Segƫ����
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �¶��յ�����Segƫ����
*/ 
UINT32_S GetGradeDataStrutmnlSegOfst(const UINT16_S gradeId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].tmnlSegOfst;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDGradeDataStru����������¶ȱ��
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��������¶ȱ��
*/ 
UINT16_S GetGradeDataStruorgnJointMainGradeId(const UINT16_S gradeId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].orgnJointMainGradeId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDGradeDataStru���������¶ȱ��
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������¶ȱ��
*/ 
UINT16_S GetGradeDataStruorgnJointSideGradeId(const UINT16_S gradeId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].orgnJointSideGradeId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDGradeDataStru���յ������¶ȱ��
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ������¶ȱ��
*/ 
UINT16_S GetGradeDataStrutmnlJointMainGradeId(const UINT16_S gradeId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].tmnlJointMainGradeId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDGradeDataStru���յ�����¶ȱ��
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�����¶ȱ��
*/ 
UINT16_S GetGradeDataStrutmnlJointSideGradeId(const UINT16_S gradeId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].tmnlJointSideGradeId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDGradeDataStru���¶�ֵ
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �¶�ֵ
*/ 
UINT16_S GetGradeDataStrugradValue(const UINT16_S gradeId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].gradValue;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDGradeDataStru���¶��������·�߼��������б����
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �¶��������·�߼��������б����
*/ 
UINT16_S GetGradeDataStruinclineDir(const UINT16_S gradeId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].inclineDir;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDGradeDataStru�������߰뾶
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �����߰뾶
*/ 
UINT32_S GetGradeDataStruradius(const UINT16_S gradeId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].radius;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

