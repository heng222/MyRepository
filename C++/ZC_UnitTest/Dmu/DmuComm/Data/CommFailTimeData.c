/*************************************************
  �ļ���   ��CommFailTimeData.C
  ����     ������      
  ����ʱ�� ��2016-8-11
  �������� �� CommFailTimeData���ݹ���
			DmuCommonData�����CommFailTimeData���ܿɷֽ����£�
			1��	��CommFailTimeDataStru�ṹ��ָ�����ռ�
			2��	��ȡCommFailTimeData����
			3��	��ȡCommFailTimeData��Ϣ
			4��	��ȡָ��IDCommFailTimeDataStru��ATP��ZCͨ�Ź���ʱ��(ms)
			5��	��ȡָ��IDCommFailTimeDataStru��ZC��ATPͨ�Ź���ʱ��
			6��	��ȡָ��IDCommFailTimeDataStru��ATP��CIͨ�Ź���ʱ��(ms)
			7��	��ȡָ��IDCommFailTimeDataStru��CI��ATPͨ�Ź���ʱ��(ms)
			8��	��ȡָ��IDCommFailTimeDataStru��ATP��ATSͨ�Ź���ʱ��(ms)
			9��	��ȡָ��IDCommFailTimeDataStru��ATS��ATPͨ�Ź���ʱ��(ms)
			10��	��ȡָ��IDCommFailTimeDataStru��DMS��ZCͨ�Ź���ʱ��(ms)
			11��	��ȡָ��IDCommFailTimeDataStru��ZC��CIͨ�Ź���ʱ��(ms)
			12��	��ȡָ��IDCommFailTimeDataStru��CI��ZCͨ�Ź���ʱ��(ms)
			13��	��ȡָ��IDCommFailTimeDataStru��DMS��ATSͨ�Ź���ʱ��(ms)
			14��	��ȡָ��IDCommFailTimeDataStru��ATS��DMSͨ�Ź���ʱ��(ms)
			15��	��ȡָ��IDCommFailTimeDataStru��ZC��ATSͨ�Ź���ʱ��(ms)
			16��	��ȡָ��IDCommFailTimeDataStru��ZC��ZCͨ�Ź���ʱ��(ms)
			17��	��ȡָ��IDCommFailTimeDataStru��CI��CIͨ�Ź���ʱ��(ms)

  ��ע    ���ޡ�
 
*************************************************/

#include "CommFailTimeData.h"
#include "../../../Common/Malloc.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"

static BnfCommFailTimeStruct* CommFailTimeDataStru = NULL;   /*����CommFailTimeData���ݽṹ��*/
static UINT16_S LineNumCommFailTime = 0u;/*������*/


/*
* ���������� ��CommFailTimeDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocCommFailTimeDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == CommFailTimeDataStru))
    {
        CommFailTimeDataStru = (BnfCommFailTimeStruct*)MemoryMalloc((UINT32_S)sizeof(BnfCommFailTimeStruct) * lineNum);
        LineNumCommFailTime = lineNum;
    }
}

/*
* ���������� ��ȡCommFailTimeData����
* ����˵����
* ����ֵ  �� 
            BnfCommFailTimeStruct*
*/
BnfCommFailTimeStruct *GetCommFailTimeData(void)
{
    return CommFailTimeDataStru;
}


/*
* ���������� ��ȡCommFailTimeData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfCommFailTimeStruct*
*/
BnfCommFailTimeStruct *GetCommFailTimeDataInfo(UINT16_S* lineNum)
{

    BnfCommFailTimeStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumCommFailTime;
        retVal =  CommFailTimeDataStru;

    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��ATP��ZCͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ATP��ZCͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruAtpToZcCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*��������ֵ*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].atpToZcCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��ZC��ATPͨ�Ź���ʱ��
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ZC��ATPͨ�Ź���ʱ��
*/ 
UINT32_S GetCommFailTimeDataStruZcToAtpCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*��������ֵ*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].zcToAtpCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��ATP��CIͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ATP��CIͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruAtpToCiCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*��������ֵ*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].atpToCiCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��CI��ATPͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: CI��ATPͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruCiToAtpCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*��������ֵ*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].ciToAtpCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��ATP��ATSͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ATP��ATSͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruAtpToAtsCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*��������ֵ*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].atpToAtsCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��ATS��ATPͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ATS��ATPͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruAtsToAtpCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*��������ֵ*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].atsToAtpCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��ZC��DMSͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ZC��DMSͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruZcToDmsCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*��������ֵ*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].zcToDmsCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��DMS��ZCͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: DMS��ZCͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruDmsToZcCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*��������ֵ*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].dmsToZcCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��ZC��CIͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ZC��CIͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruZcToCiCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*��������ֵ*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].zcToCiCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��CI��ZCͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: CI��ZCͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruCiToZcCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*��������ֵ*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].ciToZcCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��DMS��ATSͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: DMS��ATSͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruDmsToAtsCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*��������ֵ*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].dmsToAtsCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��ATS��DMSͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ATS��DMSͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruAtsToDmsCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*��������ֵ*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].atsToDmsCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��ZC��ATSͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ZC��ATSͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruZcToAtsCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*��������ֵ*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].zcToAtsCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��ZC��ZCͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ZC��ZCͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruZcToZcCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*��������ֵ*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].zcToZcCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��CI��CIͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: CI��CIͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruCiToCiCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*��������ֵ*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].ciToCiCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

