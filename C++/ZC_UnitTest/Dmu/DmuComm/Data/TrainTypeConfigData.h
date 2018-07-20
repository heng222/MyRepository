/*************************************************
  �ļ���   ��TrainTypeConfigData.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� TrainTypeConfigData���ݹ���
			DmuCommonData�����TrainTypeConfigData���ܿɷֽ����£�
			1��	��TrainTypeConfigDataStru�ṹ��ָ�����ռ�
			2��	��ȡTrainTypeConfigData����
			3��	��ȡTrainTypeConfigData��Ϣ
			4��	��ȡָ��IDTrainTypeConfigDataStru�Ľṹ���±�
			5��	��ȡָ��IDTrainTypeConfigDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDTrainTypeConfigDataStru���г�����

  ��ע    ���ޡ� 
*************************************************/
#ifndef TRAINTYPECONFIG_DATA_H_
#define TRAINTYPECONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"

#define TRAINTYPECONFIG_LINE_BYTE_NUM                    3u                  /*һ�������ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*�г��������ñ����ݽṹ��*/
typedef struct BnfTrainTypeConfigStruct
{
    UINT16_S  trainDevName;            /*�г�����(TYPE+ID)*/        
    UINT8_S   trainType;                /*�г�����*/            
}BnfTrainTypeConfigStruct;

/*
* ���������� ��TrainTypeConfigDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocTrainTypeConfigDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡTrainTypeConfigData����
* ����˵����
* ����ֵ  �� 
            BnfTrainTypeConfigStruct*
*/
BnfTrainTypeConfigStruct *GetTrainTypeConfigData(void);

/*
* ���������� ��ȡTrainTypeConfigData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
*            BnfTrainTypeConfigStruct*
*/
BnfTrainTypeConfigStruct *GetTrainTypeConfigDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDTrainTypeConfigDataStru�Ľṹ���±�
* ����˵���� const UINT16_S trainDevName;�г�����(TYPE+ID)
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetTrainTypeConfigDataStruIndex(const UINT16_S trainDevName);

/*
** ���������� ��ȡָ��IDTrainTypeConfigDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S trainDevName;�г�����(TYPE+ID)
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfTrainTypeConfigStruct* GetIndexIdTrainTypeConfigDataStru(const UINT16_S trainDevName);

/*
** ���������� ��ȡָ��IDTrainTypeConfigDataStru���г�����
* ����˵���� const UINT16_S trainDevName;�г�����(TYPE+ID)
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �г�����
*/ 
UINT8_S GetTrainTypeConfigDataStrutrainType(const UINT16_S trainDevName);


#ifdef __cplusplus
}
#endif

#endif
