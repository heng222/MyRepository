/*************************************************
  �ļ���   ��TempLimitSpeedData.h
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
#ifndef TEMPLIMITSPEED_DATA_H_
#define TEMPLIMITSPEED_DATA_H_

#include "../../../Common/CommonTypes.h"

#define TEMPLIMITSPEED_LINE_BYTE_NUM                    4                            /*һ�������ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*��ʱ�������ñ����ݽṹ��*/
typedef struct BnfTempLimitSpeedStruct
{
    UINT16_S  oneSetMaxNum;                       /*һ�����õ���ʱ����������*/
    UINT16_S  includeLgcSectionNum;               /*һ����ʱ���ٱ����а���������߼���������*/
}BnfTempLimitSpeedStruct;

/*
* ���������� ��TempLimitSpeedDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocTempLimitSpeedDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡTempLimitSpeedData����
* ����˵����
* ����ֵ  �� 
            BnfTempLimitSpeedStruct*
*/
BnfTempLimitSpeedStruct *GetTempLimitSpeedData(void);

/*
* ���������� ��ȡTempLimitSpeedData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfTempLimitSpeedStruct*
*/
BnfTempLimitSpeedStruct *GetTempLimitSpeedDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDTempLimitSpeedDataStru��һ�����õ���ʱ����������
* ����˵��:  ��
* ����ֵ  :  UINT16_NULL: ��ȡ����ʧ��
*            <UINT16_NULL: һ�����õ���ʱ����������
*/ 
UINT16_S GetTempLimitSpeedDataStruoneSetMaxNum(void);

/*
** ���������� ��ȡָ��IDTempLimitSpeedDataStru��һ����ʱ���ٱ����а���������߼���������
* ����˵��:  ��
* ����ֵ  :  UINT16_NULL: ��ȡ����ʧ��
*            <UINT16_NULL: һ����ʱ���ٱ����а���������߼���������
*/ 
UINT16_S GetTempLimitSpeedDataStruincludeLgcSectionNum(void);


#ifdef __cplusplus
}
#endif

#endif
