/*************************************************
  �ļ���   ��BlocApptchSectionData.h
  ����     ������      
  ����ʱ�� ��2016-8-11
  �������� �� BaliseData���ݹ���
			DmuCommonData�����BlocApptchSectionData���ܿɷֽ����£�
			1��	��BlocApptchSectionDataStru�ṹ��ָ�����ռ�
			2��	��ȡBlocApptchSectionData����
			3��	��ȡBlocApptchSectionData��Ϣ
			4��	��ȡָ��IDBlocApptchSectionDataStru�Ľṹ���±�
			5��	��ȡָ��IDBlocApptchSectionDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDBlocApptchSectionDataStru�İ����ļ���������Ŀ
			7��	��ȡָ��IDBlocApptchSectionDataStru�İ����ļ������α��
  ��ע    ���ޡ�
 
*************************************************/
#ifndef BLOCAPPTCHSECTION_DATA_H_
#define BLOCAPPTCHSECTION_DATA_H_

#include "../../../Common/CommonTypes.h"

#define BLOCAPPTCHSECTION_AXLESGM_MAX_NUM               10                                                   /*�����������ε������Ŀ*/
#define BLOCAPPTCHSECTION_LINE_BYTE_NUM                 24                                                    /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*��ʽ�������α����ݽṹ��*/
typedef struct BnfBlocApptchSectionStruct
{
    UINT16_S  blocApptchSectionId;                                            /*�������*/
    UINT16_S  includeAxleSgmtNum;                                                /*�����ļ���������Ŀ*/
    UINT16_S  includeAxleSgmtId[BLOCAPPTCHSECTION_AXLESGM_MAX_NUM];                /*�����ļ������α��*/
}BnfBlocApptchSectionStruct;

/*
* ���������� ��BlocApptchSectionDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocBlocApptchSectionDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡBlocApptchSectionData����
* ����˵����
* ����ֵ  �� 
            BnfBlocApptchSectionStruct*
*/
BnfBlocApptchSectionStruct *GetBlocApptchSectionData(void);

/*
* ���������� ��ȡBlocApptchSectionData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfBlocApptchSectionStruct*
*/
BnfBlocApptchSectionStruct *GetBlocApptchSectionDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDBlocApptchSectionDataStru�Ľṹ���±�
* ����˵���� const UINT16_S blocApptchSectionId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetBlocApptchSectionDataStruIndex(const UINT16_S blocApptchSectionId);

/*
** ���������� ��ȡָ��IDBlocApptchSectionDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S blocApptchSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfBlocApptchSectionStruct* GetIndexIdBlocApptchSectionDataStru(const UINT16_S blocApptchSectionId);

/*
** ���������� ��ȡָ��IDBlocApptchSectionDataStru�İ����ļ���������Ŀ
* ����˵���� const UINT16_S blocApptchSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �����ļ���������Ŀ
*/ 
UINT16_S GetBlocApptchSectionDataStruincludeAxleSgmtNum(const UINT16_S blocApptchSectionId);

/*
** ���������� ��ȡָ��IDBlocApptchSectionDataStru�İ����ļ������α��
* ����˵���� const UINT16_S blocApptchSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: �����ļ������α��
*/ 
UINT16_S* GetBlAppSectDataInAxSgmtId(const UINT16_S blocApptchSectionId);


#ifdef __cplusplus
}
#endif

#endif
