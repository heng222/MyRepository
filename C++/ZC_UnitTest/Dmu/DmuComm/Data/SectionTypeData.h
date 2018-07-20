/*************************************************
  �ļ���   ��SectionTypeData.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� SectionTypeData���ݹ���
			DmuCommonData�����SectionTypeData���ܿɷֽ����£�
			1��	��SectionTypeDataStru�ṹ��ָ�����ռ�
			2��	��ȡSectionTypeData����
			3��	��ȡSectionTypeData��Ϣ
			4��	��ȡָ��IDSectionTypeDataStru�Ľṹ���±�
			5��	��ȡָ��IDSectionTypeDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDSectionTypeDataStru����������
			7��	��ȡָ��IDSectionTypeDataStru������ID
			8��	��ȡָ��IDSectionTypeDataStru����������
			9��	��ȡָ���豸���ͺ�ID����������

  ��ע    ���ޡ�
 
*************************************************/

#ifndef SECTIONTYPE_DATA_H_
#define SECTIONTYPE_DATA_H_

#include "../../../Common/CommonTypes.h"

#define SECTIONTYPE_LINE_BYTE_NUM                 7         /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*�������Ա����ݽṹ��*/
typedef struct BnfSectionTypeStruct
{
    UINT16_S  indexId;                               /*�������*/
    UINT16_S  sectionType;                           /*��������*/
    UINT16_S  sectionId;                               /*����ID*/
    UINT8_S      sectionProperty;                    /*��������*/
}BnfSectionTypeStruct;

/*
* ���������� ��SectionTypeDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocSectionTypeDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡSectionTypeData����
* ����˵����
* ����ֵ  �� 
            BnfSectionTypeStruct*
*/
BnfSectionTypeStruct *GetSectionTypeData(void);

/*
* ���������� ��ȡSectionTypeData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfSectionTypeStruct*
*/
BnfSectionTypeStruct *GetSectionTypeDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDSectionTypeDataStru�Ľṹ���±�
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetSectionTypeDataStruIndex(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDSectionTypeDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfSectionTypeStruct* GetIndexIdSectionTypeDataStru(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDSectionTypeDataStru����������
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��������
*/ 
UINT16_S GetSectionTypeDataStrusectionType(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDSectionTypeDataStru������ID
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����ID
*/ 
UINT16_S GetSectionTypeDataStrusectionId(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDSectionTypeDataStru����������
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��������
*/ 
UINT8_S GetSectionTypeDataStrusectionProperty(const UINT16_S indexId);

/*
** ���������� ��ȡָ���豸���ͺ�ID����������
* ����˵���� const UINT16_S devType   �豸����,const UINT16_S devId   �豸ID
* ����ֵ  :  0: ��ȡ����ʧ��
*             >0: ��������
*/ 
UINT8_S GetSecPropertyAccordName(const UINT16_S devType,const UINT16_S devId);

#ifdef __cplusplus
}
#endif

#endif
