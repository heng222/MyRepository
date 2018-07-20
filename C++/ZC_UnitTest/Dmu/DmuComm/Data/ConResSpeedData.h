/*************************************************
  �ļ���   ��ConResSpeedData.h
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
#ifndef CONRESSPEED_DATA_H_
#define CONRESSPEED_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  CONRESSPEED_LINE_BYTE_NUM             3                                            /*һ�������ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*ͳһ���ٱ����ݽṹ��*/
typedef struct BnfConResSpeedStruct
{
    UINT8_S  index;                                        /*�������*/
    UINT16_S resSpeed;                                    /*����ֵ��cm/s��*/
}BnfConResSpeedStruct;

/*
* ���������� ��BnfConResSpeedStruct�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocConResSpeedDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡConResSpeed����
* ����˵����
* ����ֵ  �� 
            BnfConResSpeedStruct*
*/
BnfConResSpeedStruct *GetConResSpeedData(void);

/*
* ���������� ��ȡConResSpeed��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfConResSpeedStruct*
*/
BnfConResSpeedStruct *GetConResSpeedDataInfo(UINT16_S* lineNum);

/*
* ���������� ��ȡͳһ���ٱ��е�����ֵ
* ����˵������
* ����ֵ  ��0xFFFF ��Ч
            ����:��Ч
*/
UINT16_S GetConResSpeedValue(void);

#ifdef __cplusplus
}
#endif

#endif
