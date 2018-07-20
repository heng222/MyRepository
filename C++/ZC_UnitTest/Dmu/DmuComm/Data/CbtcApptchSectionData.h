/*************************************************
  �ļ���   ��CbtcApptchSectionData.h
  ����     ������      
  ����ʱ�� ��2016-8-11
  �������� �� CbtcApptchSectionData���ݹ���
			DmuCommonData�����CbtcApptchSectionData���ܿɷֽ����£�
			1��	��CbtcApptchSectionDataStru�ṹ��ָ�����ռ�
			2��	��ȡCbtcApptchSectionData����
			3��	��ȡCbtcApptchSectionData��Ϣ
			4��	��ȡָ��IDCbtcApptchSectionDataStru�Ľṹ���±�
			5��	��ȡָ��IDCbtcApptchSectionDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDCbtcApptchSectionDataStru�İ������߼����ε���Ŀ
			7��	��ȡָ��IDCbtcApptchSectionDataStru�İ������߼����εı��


  ��ע    ���ޡ�
 
*************************************************/
#ifndef CBTCAPPTCHSECTION_DATA_H_
#define CBTCAPPTCHSECTION_DATA_H_

#include "../../../Common/CommonTypes.h"

#define CBTCAPPTCHSECTION_LGCZONE_MAX_NUM               10                                               /*�����߼����ε������Ŀ*/
#define CBTCAPPTCHSECTION_LINE_BYTE_NUM                 24                                                /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*Cbtc�������α����ݽṹ��*/
typedef struct BnfCbtcApptchSectionStruct
{
    UINT16_S  cbtcApptchSectionId;                                            /*�������*/
    UINT16_S  includeLgcZoneNum;                                                /*�������߼����ε���Ŀ*/
    UINT16_S  includeLgcZoneId[CBTCAPPTCHSECTION_LGCZONE_MAX_NUM];            /*�������߼����εı��*/
}BnfCbtcApptchSectionStruct;

/*
* ���������� ��CbtcApptchSectionDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocCbtcApptchSectionDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡCbtcApptchSectionData����
* ����˵����
* ����ֵ  �� 
            BnfCbtcApptchSectionStruct*
*/
BnfCbtcApptchSectionStruct *GetCbtcApptchSectionData(void);

/*
* ���������� ��ȡCbtcApptchSectionData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfCbtcApptchSectionStruct*
*/
BnfCbtcApptchSectionStruct *GetCbtcApptchSectionDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDCbtcApptchSectionDataStru�Ľṹ���±�
* ����˵���� const UINT16_S cbtcApptchSectionId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetCbtcApptchSectionDataStruIndex(const UINT16_S cbtcApptchSectionId);

/*
** ���������� ��ȡָ��IDCbtcApptchSectionDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S cbtcApptchSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfCbtcApptchSectionStruct* GetIndexIdCbtcApptchSectionDataStru(const UINT16_S cbtcApptchSectionId);

/*
** ���������� ��ȡָ��IDCbtcApptchSectionDataStru�İ������߼����ε���Ŀ
* ����˵���� const UINT16_S cbtcApptchSectionId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������߼����ε���Ŀ
*/ 
UINT16_S GetCbtcApptchSectionDataStruincludeLgcZoneNum(const UINT16_S cbtcApptchSectionId);

/*
** ���������� ��ȡָ��IDCbtcApptchSectionDataStru�İ������߼����εı��
* ����˵���� const UINT16_S cbtcApptchSectionId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: �������߼����εı��
*/ 
UINT16_S* GetCbtcAppSectDataInLgcZoId(const UINT16_S cbtcApptchSectionId);


#ifdef __cplusplus
}
#endif

#endif
