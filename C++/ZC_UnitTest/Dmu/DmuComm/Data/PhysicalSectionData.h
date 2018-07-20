/*************************************************
  �ļ���   ��PhysicalSectionData.h
  ����     ������      
  ����ʱ�� ��2016-8-12
  �������� �� PhysicalSectionData���ݹ���
			DmuCommonData�����PhysicalSectionData���ܿɷֽ����£�
			1��	��LogicSectionDataStru�ṹ��ָ�����ռ�
			2��	��ȡLogicSectionData����
			3��	��ȡLogicSectionData��Ϣ
			4��	��ȡָ��IDLogicSectionDataStru�Ľṹ���±�
			5��	��ȡָ��IDLogicSectionDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDLogicSectionDataStru������
			7��	��ȡָ��IDLogicSectionDataStru���������Seg���
			8��	��ȡָ��IDLogicSectionDataStru���������Segƫ����
			9��	��ȡָ��IDLogicSectionDataStru���յ�����Seg���
			10��	��ȡָ��IDLogicSectionDataStru���յ�����Segƫ����
			11��	��ȡ��·�߼��������ID
			12��	���������SEGID��ȡ�߼����ε���Ϣ
			13��	��ȡ�߼���������ZC
			14��	��ȡ�߼���������CI
			15��	��ȡ�߼���������AC
			16��	��ѯ��SEGǰ�����߼�����
			17��	��ѯ��SEG�󷽵��߼�����
			18��	��ȡ�߼�����ID��������߼�����ID
  ��ע    ���ޡ�
 
*************************************************/
#ifndef PHYSICAL_SECTION_DATA_H_
#define PHYSICAL_SECTION_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  PHYSICALSECTION_NAME_BYTE_NUM       16                                                                      /*���Ƶ��ֽ���*/
#define  PHYSICALSECTION_AXLEID_MAX_NUM       5                                                                    /*���������*/
#define  PHYSICALSECTION_LINE_BYTE_NUM         30                                                                    /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*�������α�*/
typedef struct BnfPhysicalSectionStruct
{
    UINT16_S  physicalStcId;                                                /*���*/
    UINT8_S   name[PHYSICALSECTION_NAME_BYTE_NUM];                        /*����*/
    UINT16_S  includeAxleScNum;                                            /*��������������Ŀ*/
    UINT16_S  axleIdBuff[PHYSICALSECTION_AXLEID_MAX_NUM];                 /*������*/
}BnfPhysicalSectionStruct;

/*
* ���������� ��PhysicalSectionDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocPhysicalSectionDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡPhysicalSectionData����
* ����˵����
* ����ֵ  �� 
            BnfPhysicalSectionStruct*
*/
BnfPhysicalSectionStruct *GetPhysicalSectionData(void);

/*
* ���������� ��ȡPhysicalSectionData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfPhysicalSectionStruct*
*/
BnfPhysicalSectionStruct *GetPhysicalSectionDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDPhysicalSectionDataStru�Ľṹ���±�
* ����˵���� const UINT16_S physicalStcId;���
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetPhysicalSectionDataStruIndex(const UINT16_S physicalStcId);

/*
** ���������� ��ȡָ��IDPhysicalSectionDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S physicalStcId;���
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfPhysicalSectionStruct* GetIndexIdPhysicalSectionDataStru(const UINT16_S physicalStcId);

/*
** ���������� ��ȡָ��IDPhysicalSectionDataStru������
* ����˵���� const UINT16_S physicalStcId;���
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ����
*/ 
UINT8_S* GetPhysicalSectionDataStruname(const UINT16_S physicalStcId);

/*
** ���������� ��ȡָ��IDPhysicalSectionDataStru�İ�������������Ŀ
* ����˵���� const UINT16_S physicalStcId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��������������Ŀ
*/ 
UINT16_S GetPhysicalSectionDataStruincludeAxleScNum(const UINT16_S physicalStcId);

/*
** ���������� ��ȡָ��IDPhysicalSectionDataStru�ļ�����
* ����˵���� const UINT16_S physicalStcId;���
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ������
*/ 
UINT16_S* GetPhysicalSectionDataStruaxleIdBuff(const UINT16_S physicalStcId);


#ifdef __cplusplus
}
#endif

#endif
