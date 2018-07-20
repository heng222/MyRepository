/*************************************************
  �ļ���   ��AxleData.h
  ����     ������      
  ����ʱ�� ��2016-8-10
  �������� �� AxleData���ݹ���
			DmuCommonData�����AxleData���ܿɷֽ����£�
				1��	��AxleDataStru�ṹ��ָ�����ռ�
				2��	��ȡAxleData����
				3��	��ȡAxleData��Ϣ
				4��	��ȡָ��IDAxleDataStru�Ľṹ���±�
				5��	��ȡָ��IDAxleDataStru�Ľṹ��ָ��
				6��	��ȡָ��IDAxleDataStru�ļ���������
				7��	��ȡָ��IDAxleDataStru�ļ���������Segƫ����(cm)
  ��ע    ���ޡ�
 
*************************************************/
#ifndef AXLE_DATA_H_
#define AXLE_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  AXLE_NAME_BYTE_NUM       8                            /*���Ƶ��ֽ���*/
#define  AXLE_LINE_BYTE_NUM      14                            /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif


/*��������*/
typedef struct BnfAxleStruct
{
    UINT16_S  axleId;                        /*���*/
    UINT8_S  axleName[AXLE_NAME_BYTE_NUM];                    /*����������*/    
    UINT32_S axleSegOfst;                    /*����������Segƫ����(cm)*/
}BnfAxleStruct;

/*
* �������ƣ� MallocAxleDataStru
* ���������� ��AxleDataStru�ṹ��ָ�����ռ�
* ��������� UINT16_S lineNum �����������
* ��������� ��
* ����ֵ  �� void
*/
void MallocAxleDataStru(UINT16_S lineNum);

/*
* �������ƣ� GetAxleData
* ���������� ��ȡAxleData����
* ��������� ��
* ��������� ��
* ����ֵ  �� 
            BnfAxleStruct*
*/
BnfAxleStruct *GetAxleData(void);

/*
* �������ƣ� GetAxleDataInfo
* ���������� ��ȡAxleData��Ϣ
* ��������� ��
* ��������� UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfAxleStruct*
*/
BnfAxleStruct *GetAxleDataInfo(UINT16_S* lineNum);

/*
* �������ƣ� GetAxleDataStruIndex
* ���������� ��ȡָ��IDAxleDataStru�Ľṹ���±�
* ��������� const UINT16_S axleId;���
* ��������� ��
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetAxleDataStruIndex(const UINT16_S axleId);

/*
* �������ƣ� GetIndexIdAxleDataStru
* ���������� ��ȡָ��IDAxleDataStru�Ľṹ��ָ��
* ��������� const UINT16_S axleId;���
* ��������� ��
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfAxleStruct* GetIndexIdAxleDataStru(const UINT16_S axleId);

/*
* �������ƣ� GetAxleDataStruaxleName
* ���������� ��ȡָ��IDAxleDataStru�ļ���������
* ��������� const UINT16_S axleId;���
* ��������� ��
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ����������
*/ 
UINT8_S* GetAxleDataStruaxleName(const UINT16_S axleId);

/*
* �������ƣ� GetAxleDataStruaxleSegOfst
* ���������� ��ȡָ��IDAxleDataStru�ļ���������Segƫ����(cm)
* ��������� const UINT16_S axleId;���
* ��������� ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����������Segƫ����(cm)
*/ 
UINT32_S GetAxleDataStruaxleSegOfst(const UINT16_S axleId);


#ifdef __cplusplus
}
#endif

#endif
