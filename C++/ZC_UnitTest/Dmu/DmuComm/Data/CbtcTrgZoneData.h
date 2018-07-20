/*************************************************
  �ļ���   ��CbtcTrgZoneData.h
  ����     ������      
  ����ʱ�� ��2016-8-11
  �������� �� CbtcTrgZoneData���ݹ���
			DmuCommonData�����CbtcTrgZoneData���ܿɷֽ����£�
			1��	��CbtcTrgZoneDataStru�ṹ��ָ�����ռ�
			2��	��ȡCbtcTrgZoneData����
			3��	��ȡCbtcTrgZoneData��Ϣ
			4��	��ȡָ��IDCbtcTrgZoneDataStru�Ľṹ���±�
			5��	��ȡָ��IDCbtcTrgZoneDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDCbtcTrgZoneDataStru�İ������߼����ε���Ŀ
			7��	��ȡָ��IDCbtcTrgZoneDataStru�İ������߼����εı��
  ��ע    ���ޡ�
 
*************************************************/
#ifndef CBTCTRGZONE_DATA_H_
#define CBTCTRGZONE_DATA_H_

#include "../../../Common/CommonTypes.h"

#define CBTCTRGZONE_LGCZONE_MAX_NUM               16                                                   /*�����߼����ε������Ŀ*/
#define CBTCTRGZONE_LINE_BYTE_NUM                 36                                                /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*Cbtc�������α����ݽṹ��*/
typedef struct BnfCbtcTrgZoneStruct
{
    UINT16_S  cbtcApptchSectionId;                                /*�������*/
    UINT16_S  includeLgcZoneNum;                                    /*�������߼����ε���Ŀ*/
    UINT16_S  includeLgcZoneId[CBTCTRGZONE_LGCZONE_MAX_NUM];        /*�������߼����εı��*/
}BnfCbtcTrgZoneStruct;

/*
* ���������� ��CbtcTrgZoneDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocCbtcTrgZoneDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡCbtcTrgZoneData����
* ����˵����
* ����ֵ  �� 
            BnfCbtcTrgZoneStruct*
*/
BnfCbtcTrgZoneStruct *GetCbtcTrgZoneData(void);

/*
* ���������� ��ȡCbtcTrgZoneData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfCbtcTrgZoneStruct*
*/
BnfCbtcTrgZoneStruct *GetCbtcTrgZoneDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDCbtcTrgZoneDataStru�Ľṹ���±�
* ����˵���� const UINT16_S cbtcApptchSectionId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetCbtcTrgZoneDataStruIndex(const UINT16_S cbtcApptchSectionId);

/*
** ���������� ��ȡָ��IDCbtcTrgZoneDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S cbtcApptchSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfCbtcTrgZoneStruct* GetIndexIdCbtcTrgZoneDataStru(const UINT16_S cbtcApptchSectionId);

/*
** ���������� ��ȡָ��IDCbtcTrgZoneDataStru�İ������߼����ε���Ŀ
* ����˵���� const UINT16_S cbtcApptchSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������߼����ε���Ŀ
*/ 
UINT16_S GetCbtcTrgZoneDataStruincludeLgcZoneNum(const UINT16_S cbtcApptchSectionId);

/*
** ���������� ��ȡָ��IDCbtcTrgZoneDataStru�İ������߼����εı��
* ����˵���� const UINT16_S cbtcApptchSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: �������߼����εı��
*/ 
UINT16_S* GetCbtcTrgZoDataInLgcZoId(const UINT16_S cbtcApptchSectionId);


#ifdef __cplusplus
}
#endif

#endif
