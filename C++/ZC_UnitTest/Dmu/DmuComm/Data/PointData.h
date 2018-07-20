/*************************************************
  �ļ���   ��PointData.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� PointData���ݹ���
			DmuCommonData�����PointData���ܿɷֽ����£�
			1��	��PointDataStru�ṹ��ָ�����ռ�
			2��	��ȡPointData����
			3��	��ȡPointData��Ϣ
			4��	��ȡָ��IDPointDataStru�Ľṹ���±�
			5��	��ȡָ��IDPointDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDPointDataStru������
			7��	��ȡָ��IDPointDataStru�����������
			8��	��ȡָ��IDPointDataStru�Ĺ����(cm)
			9��	��ȡָ��IDPointDataStru�ĵ�����
			10��	��ȡָ��IDPointDataStru������������ڵ�ID
			11��	��ȡָ��IDPointDataStru�����������ڵ�ID
			12��	��ȡָ��IDPointDataStru���յ��������ڵ�ID
			13��	��ȡָ��IDPointDataStru���յ�������ڵ�ID
			14��	��ȡָ��IDPointDataStru������ZC������
			15��	��ȡָ��IDPointDataStru������ATS������
			16��	��ȡָ��IDPointDataStru����������CI������
  ��ע    ���ޡ�
 
*************************************************/
#ifndef POINT_DATA_H_
#define POINT_DATA_H_

#include "../../../Common/CommonTypes.h"

#define POINT_MAX_NAME_LEN                  16                              /*���Ƴ���*/
#define POINT_LINE_BYTE_NUM                 44                         /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*������ݽṹ��*/
typedef struct BnfPointStruct
{
    UINT16_S  indexId;                                        /*�������*/
    UINT8_S  name[POINT_MAX_NAME_LEN];                        /*����*/
    UINT8_S  startPathwayName[POINT_MAX_NAME_LEN];            /*���������*/
    UINT32_S  location;                                          /*�����(cm)*/  
    UINT16_S  pointType;                                        /*������*/
    UINT16_S  startJointMainLkId;                                /*����������ڵ�ID*/
    UINT16_S  startJointSideLkId;                                /*���������ڵ�ID*/
    UINT16_S  tmnlJointMainLkId;                                /*�յ��������ڵ�ID*/
    UINT16_S  tmnlJointSideLkId;                                /*�յ�������ڵ�ID*/
    UINT16_S  manageZCId;                                        /*����ZC������*/
    UINT16_S  manageATSId;                                    /*����ATS������*/
    UINT16_S  manageCIId;                                /*��������CI������*/ 
}BnfPointStruct;

/*
* ���������� ��PointDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocPointDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡPointData����
* ����˵����
* ����ֵ  �� 
            BnfPointStruct*
*/
BnfPointStruct *GetPointData(void);

/*
* ���������� ��ȡPointData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfPointStruct*
*/
BnfPointStruct *GetPointDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDPointDataStru�Ľṹ���±�
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetPointDataStruIndex(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDPointDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfPointStruct* GetIndexIdPointDataStru(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDPointDataStru������
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ����
*/ 
UINT8_S* GetPointDataStruname(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDPointDataStru�����������
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���������
*/ 
UINT8_S* GetPointDataStrustartPathwayName(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDPointDataStru�Ĺ����(cm)
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �����(cm)
*/ 
UINT32_S GetPointDataStrulocation(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDPointDataStru�ĵ�����
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ������
*/ 
UINT16_S GetPointDataStrupointType(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDPointDataStru������������ڵ�ID
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����������ڵ�ID
*/ 
UINT16_S GetPointDataStrustartJointMainLkId(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDPointDataStru�����������ڵ�ID
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ���������ڵ�ID
*/ 
UINT16_S GetPointDataStrustartJointSideLkId(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDPointDataStru���յ��������ڵ�ID
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ��������ڵ�ID
*/ 
UINT16_S GetPointDataStrutmnlJointMainLkId(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDPointDataStru���յ�������ڵ�ID
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�������ڵ�ID
*/ 
UINT16_S GetPointDataStrutmnlJointSideLkId(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDPointDataStru������ZC������
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����ZC������
*/ 
UINT16_S GetPointDataStrumanageZCId(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDPointDataStru������ATS������
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����ATS������
*/ 
UINT16_S GetPointDataStrumanageATSId(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDPointDataStru����������CI������
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��������CI������
*/ 
UINT16_S GetPointDataStrumanageCIId(const UINT16_S indexId);


#ifdef __cplusplus
}
#endif

#endif
