/*************************************************
  �ļ���   ��SystemAccTableData.h
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
#ifndef SYSTEMACCTABLE_DATA_H_
#define SYSTEMACCTABLE_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  SYSTEMACCTABLE_LINE_BYTE_NUM                 4                            /*һ�������ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*�г����ǣ�����ٶȷֶ�ȡֵ�����ݽṹ��*/
typedef struct BnfSystemAccTableStruct
{
    UINT8_S  trainType;            /*�г�����*/    
    UINT8_S  lowerLimitSpeed;        /*�ֶ��ٶ����ޡ����ݳ����ṩ��ǣ���������߷ֶεó�����λkm/h*/
    UINT8_S  upperLimitSpeed;        /*�ֶ��ٶ����ޡ����ݳ����ṩ��ǣ���������߷ֶεó�����λkm/h*/
    UINT8_S  accValue;            /*�ֶμ��ٶ�ֵ�����ݳ����ṩ��ǣ���������߷ֶεó�����λcm/s2*/    
}BnfSystemAccTableStruct;

/*
* ���������� ��SystemAccTableDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocSystemAccTableDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡSystemAccTableData����
* ����˵����
* ����ֵ  �� 
            BnfSystemAccTableStruct*
*/
BnfSystemAccTableStruct *GetSystemAccTableData(void);

/*
* ���������� ��ȡSystemAccTableData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfSystemAccTableStruct*
*/
BnfSystemAccTableStruct *GetSystemAccTableDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDSystemAccTableDataStru�Ľṹ���±�
* ����˵���� const UINT8_S trainType;�г�����
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetSystemAccTableDataStruIndex(const UINT8_S trainType);

/*
** ���������� ��ȡָ��IDSystemAccTableDataStru�Ľṹ��ָ��
* ����˵���� const UINT8_S trainType;�г�����
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfSystemAccTableStruct* GetIndexIdSystemAccTableDataStru(const UINT8_S trainType);

/*
** ���������� ��ȡָ��IDSystemAccTableDataStru�ķֶ��ٶ����ޡ����ݳ����ṩ��ǣ���������߷ֶεó�����λkm/h
* ����˵���� const UINT8_S trainType;�г�����
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �ֶ��ٶ����ޡ����ݳ����ṩ��ǣ���������߷ֶεó�����λkm/h
*/ 
UINT8_S GetSystemAccTableDataStrulowerLimitSpeed(const UINT8_S trainType);

/*
** ���������� ��ȡָ��IDSystemAccTableDataStru�ķֶ��ٶ����ޡ����ݳ����ṩ��ǣ���������߷ֶεó�����λkm/h
* ����˵���� const UINT8_S trainType;�г�����
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �ֶ��ٶ����ޡ����ݳ����ṩ��ǣ���������߷ֶεó�����λkm/h
*/ 
UINT8_S GetSystemAccTableDataStruupperLimitSpeed(const UINT8_S trainType);

/*
** ���������� ��ȡָ��IDSystemAccTableDataStru�ķֶμ��ٶ�ֵ�����ݳ����ṩ��ǣ���������߷ֶεó�����λcm/s2
* ����˵���� const UINT8_S trainType;�г�����
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �ֶμ��ٶ�ֵ�����ݳ����ṩ��ǣ���������߷ֶεó�����λcm/s2
*/ 
UINT8_S GetSystemAccTableDataStruaccValue(const UINT8_S trainType);

/*
** ���������� ��ȡǣ�����ٶ�
* ����˵���� const UINT8_S trainType;�г�����
*             const UINT16_S trainSpeed �г���ǰ�ٶ�
* ����ֵ  :  ���ٶ�
*/ 
UINT8_S GetTracAcc(const UINT16_S trainSpeed,const UINT8_S trainType);


#ifdef __cplusplus
}
#endif

#endif
