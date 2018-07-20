/*************************************************
  �ļ���   ��SystemConfigData.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� SystemConfigData���ݹ���
			DmuCommonData�����SystemConfigData���ܿɷֽ����£�
			1��	��SystemConfigDataStru�ṹ��ָ�����ռ�
			2��	��ȡSystemConfigData����
			3��	��ȡSystemConfigData��Ϣ
			4��	��ȡָ��IDSystemConfigDataStru��ϵͳ��������ٶ�(km/h)
			5��	��ȡ��ʱ�����������(km/h)
			6��	��ȡNTPУʱʱ����.��������ʱ���뱾��ʱ���ʱ�����λ
			7��	��ȡ��ȫ��������.���ǵ�����������£����Ǳ�����о������·����¶ȵȣ��ƶ���Ȩ���ǵİ�ȫ��������
			8��	��ȡϵͳ������󱣻����γ��ȣ�cm��
			9��	��ȡseg�߼�����������
			10��	��ȡRM����ֵ
  ��ע    ���ޡ� 
*************************************************/
#ifndef SYSTEMCONFIG_DATA_H_
#define SYSTEMCONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"

#define SYSTEMCONFIG_LINE_BYTE_NUM                        (10-2)                           /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*ϵͳ�������ݱ����ݽṹ��*/
typedef struct BnfSystemConfigStruct
{
    UINT8_S   maxLineLimitSpeed;            /*ϵͳ��������ٶ�(km/h)*/        
    UINT8_S    maxTsrSpeed;                /*��ʱ�����������(km/h)*/        
    UINT8_S    mimeZoneDifference;            /*NTPУʱʱ����.��������ʱ���뱾��ʱ���ʱ�����λ��ʱ����Ӧ��ʹ��ʱӦ����3600ת��Ϊ�롣*/        
    UINT16_S    safeBackDistance;            /*��ȫ��������.���ǵ�����������£����Ǳ�����о������·����¶ȵȣ��ƶ���Ȩ���ǵİ�ȫ��������*/        
    UINT16_S  maxOverlapLength;            /*ϵͳ������󱣻����γ��ȣ�cm��*/
    UINT8_S    segLogicDirUpAndDown;        /*seg�߼�����������*/    
    UINT16_S    rmLimitSpeed;                /*RM����ֵ*/        
}BnfSystemConfigStruct;

/*
* ���������� ��SystemConfigDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocSystemConfigDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡSystemConfigData����
* ����˵����
* ����ֵ  �� 
            BnfSystemConfigStruct*
*/
BnfSystemConfigStruct *GetSystemConfigData(void);

/*
* ���������� ��ȡSystemConfigData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfSystemConfigStruct*
*/
BnfSystemConfigStruct *GetSystemConfigDataInfo(UINT16_S* lineNum);

/*
** ���������� ��ȡָ��IDSystemConfigDataStru��ϵͳ��������ٶ�(km/h)
* ����˵��:  ��
* ����ֵ  :  UINT8_NULL: ��ȡ����ʧ��
*            <UINT8_NULL: ϵͳ��������ٶ�(km/h)
*/ 
UINT8_S GetSystemConfigDataStrumaxLineLimitSpeed(void);

/*
** ���������� ��ȡ��ʱ�����������(km/h)
* ����˵��:  ��
* ����ֵ  :  UINT8_NULL: ��ȡ����ʧ��
*            <UINT8_NULL: ��ʱ�����������(km/h)
*/ 
UINT8_S GetSystemMaxTsrSpeed(void);

/*
** ���������� ��ȡNTPУʱʱ����.��������ʱ���뱾��ʱ���ʱ�����λ��ʱ����Ӧ��ʹ��ʱӦ����3600ת��Ϊ�롣
* ����˵��:  ��
* ����ֵ  :  UINT8_NULL: ��ȡ����ʧ��
*            <UINT8_NULL: NTPУʱʱ����.��������ʱ���뱾��ʱ���ʱ�����λ��ʱ����Ӧ��ʹ��ʱӦ����3600ת��Ϊ�롣
*/ 
UINT8_S GetSystemNtpMimeZoneDifference(void);

/*
** ���������� ��ȡ��ȫ��������.���ǵ�����������£����Ǳ�����о������·����¶ȵȣ��ƶ���Ȩ���ǵİ�ȫ��������
* ����˵��:  ��
* ����ֵ  :  UINT16_NULL: ��ȡ����ʧ��
*            <UINT16_NULL: ��ȫ��������.���ǵ�����������£����Ǳ�����о������·����¶ȵȣ��ƶ���Ȩ���ǵİ�ȫ��������
*/ 
UINT16_S GetSystemSafeBackDistance(void);

/*
** ���������� ��ȡϵͳ������󱣻����γ��ȣ�cm��
* ����˵��:  ��
* ����ֵ  :  UINT16_NULL: ��ȡ����ʧ��
*            <UINT16_NULL: ϵͳ������󱣻����γ��ȣ�cm��
*/ 
UINT16_S GetSystemMaxOverlapLength(void);

/*
** ���������� ��ȡseg�߼�����������
* ����˵��:  ��
* ����ֵ  :  UINT8_NULL: ��ȡ����ʧ��
*            <UINT8_NULL: seg�߼�����������
*/ 
UINT8_S GetSystemSegLogicDirUpAndDown(void);

/*
** ���������� ��ȡRM����ֵ
* ����˵��:  ��
* ����ֵ  :  UINT16_NULL: ��ȡ����ʧ��
*            <UINT16_NULL: RM����ֵ
*/ 
UINT16_S GetSystemRmLimitSpeed(void);


#ifdef __cplusplus
}
#endif

#endif
