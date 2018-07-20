/*************************************************
  �ļ���   ��CommFailTimeData.h
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
#ifndef COMMFAILTIME_DATA_H_
#define COMMFAILTIME_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  COMMFAILTIME_LINE_BYTE_NUM                    60                            /*һ�������ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*ͨ�Ź������ñ����ݽṹ��*/
typedef struct BnfCommFailTimeStruct
{
    UINT32_S  atpToZcCommFailTime;                       /*ATP��ZCͨ�Ź���ʱ��(ms)*/
    UINT32_S  zcToAtpCommFailTime;                       /*ZC��ATPͨ�Ź���ʱ��*/
    UINT32_S  atpToCiCommFailTime;                       /*ATP��CIͨ�Ź���ʱ��(ms)*/
    UINT32_S  ciToAtpCommFailTime;                       /*CI��ATPͨ�Ź���ʱ��(ms)*/
    UINT32_S  atpToAtsCommFailTime;                       /*ATP��ATSͨ�Ź���ʱ��(ms)*/
    UINT32_S  atsToAtpCommFailTime;                       /*ATS��ATPͨ�Ź���ʱ��(ms)*/
    UINT32_S  zcToDmsCommFailTime;                       /*ZC��DMSͨ�Ź���ʱ��(ms)*/
    UINT32_S  dmsToZcCommFailTime;                       /*DMS��ZCͨ�Ź���ʱ��(ms)*/
    UINT32_S  zcToCiCommFailTime;                           /*ZC��CIͨ�Ź���ʱ��(ms)*/
    UINT32_S  ciToZcCommFailTime;                           /*CI��ZCͨ�Ź���ʱ��(ms)*/
    UINT32_S  dmsToAtsCommFailTime;                       /*DMS��ATSͨ�Ź���ʱ��(ms)*/
    UINT32_S  atsToDmsCommFailTime;                       /*ATS��DMSͨ�Ź���ʱ��(ms)*/
    UINT32_S  zcToAtsCommFailTime;                       /*ZC��ATSͨ�Ź���ʱ��(ms)*/
    UINT32_S  zcToZcCommFailTime;                           /*ZC��ZCͨ�Ź���ʱ��(ms)*/
    UINT32_S  ciToCiCommFailTime;                           /*CI��CIͨ�Ź���ʱ��(ms)*/
}BnfCommFailTimeStruct;

/*
* ���������� ��CommFailTimeDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocCommFailTimeDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡCommFailTimeData����
* ����˵����
* ����ֵ  �� 
            BnfCommFailTimeStruct*
*/
BnfCommFailTimeStruct *GetCommFailTimeData(void);

/*
* ���������� ��ȡCommFailTimeData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfCommFailTimeStruct*
*/
BnfCommFailTimeStruct *GetCommFailTimeDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��ATP��ZCͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ATP��ZCͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruAtpToZcCommFailTime(void);

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��ZC��ATPͨ�Ź���ʱ��
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ZC��ATPͨ�Ź���ʱ��
*/ 
UINT32_S GetCommFailTimeDataStruZcToAtpCommFailTime(void);

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��ATP��CIͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ATP��CIͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruAtpToCiCommFailTime(void);

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��CI��ATPͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: CI��ATPͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruCiToAtpCommFailTime(void);

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��ATP��ATSͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ATP��ATSͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruAtpToAtsCommFailTime(void);

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��ATS��ATPͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ATS��ATPͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruAtsToAtpCommFailTime(void);

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��ZC��DMSͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ZC��DMSͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruZcToDmsCommFailTime(void);

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��DMS��ZCͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: DMS��ZCͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruDmsToZcCommFailTime(void);

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��ZC��CIͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ZC��CIͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruZcToCiCommFailTime(void);

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��CI��ZCͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: CI��ZCͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruCiToZcCommFailTime(void);

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��DMS��ATSͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: DMS��ATSͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruDmsToAtsCommFailTime(void);

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��ATS��DMSͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ATS��DMSͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruAtsToDmsCommFailTime(void);

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��ZC��ATSͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ZC��ATSͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruZcToAtsCommFailTime(void);


/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��ZC��ZCͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ZC��ZCͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruZcToZcCommFailTime(void);

/*
** ���������� ��ȡָ��IDCommFailTimeDataStru��CI��CIͨ�Ź���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: CI��CIͨ�Ź���ʱ��(ms)
*/ 
UINT32_S GetCommFailTimeDataStruCiToCiCommFailTime(void);


#ifdef __cplusplus
}
#endif

#endif
