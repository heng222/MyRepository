/*************************************************
  �ļ���   ��ConGradeData.h
  ����     ������      
  ����ʱ�� ��2016-8-11
  �������� �� ConGradeData���ݹ���
			DmuCommonData�����ConGradeData���ܿɷֽ����£�
			1��	��BnfConGradeStruct�ṹ��ָ�����ռ�
			2��	��ȡConGrade����
			3��	��ȡConGrade��Ϣ
			4��	��ȡͳһ���ٱ��е��¶�ֵ
  ��ע    ���ޡ�
 
*************************************************/
#ifndef CONGRADE_DATA_H_
#define CONGRADE_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  CONGRADE_LINE_BYTE_NUM             3                                            /*һ�������ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*ͳһ���ٱ����ݽṹ��*/
typedef struct BnfConGradeDataStruct
{
    UINT8_S  index;                                        /*�������*/
    UINT16_S grade;                                        /*�¶�ֵ*/
}BnfConGradeDataStruct;

/*
* ���������� ��BnfConGradeStruct�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocConGradeDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡConGrade����
* ����˵����
* ����ֵ  �� 
            BnfConGradeStruct*
*/
BnfConGradeDataStruct *GetConGradeData(void);

/*
* ���������� ��ȡConGrade��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfConGradeStruct*
*/
BnfConGradeDataStruct *GetConGradeDataInfo(UINT16_S* lineNum);

/*
* ���������� ��ȡͳһ���ٱ��е��¶�ֵ
* ����˵������
* ����ֵ  ��0xFFFF ��Ч
            ����:��Ч
*/
UINT16_S GetConGradeValue(void);

#ifdef __cplusplus
}
#endif

#endif
