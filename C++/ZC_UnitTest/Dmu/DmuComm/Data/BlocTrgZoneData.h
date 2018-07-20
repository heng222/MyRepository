/*************************************************
  �ļ���   ��BlocTrgZoneData.h
  ����     ������      
  ����ʱ�� ��2016-8-11
  �������� �� BlocTrgZoneData���ݹ���
			DmuCommonData�����BlocTrgZoneData���ܿɷֽ����£�
			1��	��BlocTrgZoneDataStru�ṹ��ָ�����ռ�
			2��	��ȡBlocTrgZoneData����
			3��	��ȡBlocTrgZoneData��Ϣ
			4��	��ȡָ��IDBlocTrgZoneDataStru�Ľṹ���±�
			5��	��ȡָ��IDBlocTrgZoneDataStru�Ľṹ��ָ��
			6��	 ��ȡָ��IDBlocTrgZoneDataStru�İ����ļ���������Ŀ
			7��	��ȡָ��IDBlocTrgZoneDataStru�İ����ļ������α��

  ��ע    ���ޡ�
 
*************************************************/
#ifndef BLOCTRGZONE_DATA_H_
#define BLOCTRGZONE_DATA_H_

#include "../../../Common/CommonTypes.h"

#define BLOCTRGZONE_AXLESGM_MAX_NUM               16                                                           /*�����������ε������Ŀ*/
#define BLOCTRGZONE_LINE_BYTE_NUM                 36                                                        /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*��ʽ�������α�����ݽṹ��*/
typedef struct BnfBlocTrgZoneStruct
{
    UINT16_S  blocApptchSectionId;                                        /*�������*/
    UINT16_S  includeAxleSgmtNum;                                            /*�����ļ���������Ŀ*/
    UINT16_S  includeAxleSgmtId[BLOCTRGZONE_AXLESGM_MAX_NUM];                /*�����ļ������α��*/
}BnfBlocTrgZoneStruct;

/*
* ���������� ��BlocTrgZoneDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocBlocTrgZoneDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡBlocTrgZoneData����
* ����˵����
* ����ֵ  �� 
            BnfBlocTrgZoneStruct*
*/
BnfBlocTrgZoneStruct *GetBlocTrgZoneData(void);

/*
* ���������� ��ȡBlocTrgZoneData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfBlocTrgZoneStruct*
*/
BnfBlocTrgZoneStruct *GetBlocTrgZoneDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDBlocTrgZoneDataStru�Ľṹ���±�
* ����˵���� const UINT16_S blocApptchSectionId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetBlocTrgZoneDataStruIndex(const UINT16_S blocApptchSectionId);

/*
** ���������� ��ȡָ��IDBlocTrgZoneDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S blocApptchSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfBlocTrgZoneStruct* GetIndexIdBlocTrgZoneDataStru(const UINT16_S blocApptchSectionId);

/*
** ���������� ��ȡָ��IDBlocTrgZoneDataStru�İ����ļ���������Ŀ
* ����˵���� const UINT16_S blocApptchSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �����ļ���������Ŀ
*/ 
UINT16_S GetBlocTrgZoneDataStruincludeAxleSgmtNum(const UINT16_S blocApptchSectionId);

/*
** ���������� ��ȡָ��IDBlocTrgZoneDataStru�İ����ļ������α��
* ����˵���� const UINT16_S blocApptchSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: �����ļ������α��
*/ 
UINT16_S* GetBlTrgZoDataInAxleSegmId(const UINT16_S blocApptchSectionId);


#ifdef __cplusplus
}
#endif

#endif
