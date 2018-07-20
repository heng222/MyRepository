/*************************************************
  �ļ���   ��SegData.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� SegData���ݹ���
			DmuCommonData�����SegData���ܿɷֽ����£�
			1��	��SegDataStru�ṹ��ָ�����ռ�
			2��	��ȡSEG�������
			3��	��ȡSegData����
			4��	��ȡSegData��Ϣ
			5��	��ȡָ��IDSegDataStru�Ľṹ���±�
			6��	��ȡָ��IDSegDataStru�Ľṹ��ָ��
			7��	 ��ȡָ��IDSegDataStru�ĳ��ȣ�cm)
			8��	��ȡָ��IDSegDataStru�����˵�����
			9��	��ȡָ��IDSegDataStru�����˵���
			10��	��ȡָ��IDSegDataStru���յ�˵�����
			11��	��ȡָ��IDSegDataStru���յ�˵���
			12��	��ȡָ��IDSegDataStru�������������SegID
			13��	��ȡָ��IDSegDataStru�����������ڵ�SegID
			14��	��ȡָ��IDSegDataStru���յ��������ڵ�SegID
			15��	��ȡָ��IDSegDataStru���յ�������ڵ�SegID
			16��	��ȡָ��IDSegDataStru������ZC����ID
			17��	��ȡָ��IDSegDataStru������ATS����ID
			18��	��ȡָ��IDSegDataStru������CI����ID
			19��	��ȡָ��IDSegDataStru���յ�˵��ź��յ�˵�����
			20��	��ȡָ��IDSegDataStru�����˵��ź����˵�����
			21��	��ȡָ����ָ��λ�õ�SEG��Ϣ
			22��	��ȡָ��CIID��ȡZCID
  ��ע    ���ޡ�
 
*************************************************/
#ifndef SEG_DATA_H_
#define SEG_DATA_H_

#include "../../../Common/CommonTypes.h"

#define SEG_LINE_BYTE_NUM                 30                           /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*Seg�����ݽṹ��*/
typedef struct BnfSegStruct
{
    UINT16_S  segId;                        /*�������*/
    UINT32_S     length;                        /*���ȣ�cm)*/
    UINT16_S  startPointType;                /*���˵�����*/
    UINT16_S  startPointId;                /*���˵���*/
    UINT16_S  endPointType;                /*�յ�˵�����*/
    UINT16_S  endPointId;                    /*�յ�˵���*/
    UINT16_S  segStartJointMainSegId;        /*�����������SegID*/
    UINT16_S  segStartJointSideSegId;        /*���������ڵ�SegID*/
    UINT16_S  segTmnlJointMainSegId;        /*�յ��������ڵ�SegID*/
    UINT16_S  segTmnlJointSideSegId;        /*�յ�������ڵ�SegID*/
    UINT16_S  segManageZCId;                /*����ZC����ID*/
    UINT16_S  segManageATSId;                /*����ATS����ID*/
    UINT16_S  segManageCIId;                /*����CI����ID*/ 
    UINT8_S    segResSpeed;                /*SEG������Ϣ����*/
    UINT8_S    grade;                        /*SEG�¶���Ϣ����*/
}BnfSegStruct;

/*
* ���������� ��SegDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocSegDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡSegData����
* ����˵����
* ����ֵ  �� 
            BnfSegStruct*
*/
BnfSegStruct *GetSegData(void);

/*��ȡSEG�������*/
UINT16_S GetSegIdNum(void);
/*
* ���������� ��ȡSegData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfSegStruct*
*/
BnfSegStruct *GetSegDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDSegDataStru�Ľṹ���±�
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetSegDataStruIndex(const UINT16_S segId);

/*
** ���������� ��ȡָ��IDSegDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfSegStruct* GetIndexIdSegDataStru(const UINT16_S segId);

/*
** ���������� ��ȡָ��IDSegDataStru�ĳ��ȣ�cm)
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ���ȣ�cm)
*/ 
UINT32_S GetSegDataStrulength(const UINT16_S segId);

/*
** ���������� ��ȡָ��IDSegDataStru�����˵�����
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ���˵�����
*/ 
UINT16_S GetSegDataStrustartPointType(const UINT16_S segId);

/*
** ���������� ��ȡָ��IDSegDataStru�����˵���
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ���˵���
*/ 
UINT16_S GetSegDataStrustartPointId(const UINT16_S segId);

/*
** ���������� ��ȡָ��IDSegDataStru���յ�˵�����
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�˵�����
*/ 
UINT16_S GetSegDataStruendPointType(const UINT16_S segId);

/*
** ���������� ��ȡָ��IDSegDataStru���յ�˵���
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�˵���
*/ 
UINT16_S GetSegDataStruendPointId(const UINT16_S segId);

/*
** ���������� ��ȡָ��IDSegDataStru�������������SegID
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �����������SegID
*/ 
UINT16_S GetSegDataStrusegStartJointMainSegId(const UINT16_S segId);

/*
** ���������� ��ȡָ��IDSegDataStru�����������ڵ�SegID
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ���������ڵ�SegID
*/ 
UINT16_S GetSegDataStrusegStartJointSideSegId(const UINT16_S segId);

/*
** ���������� ��ȡָ��IDSegDataStru���յ��������ڵ�SegID
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ��������ڵ�SegID
*/ 
UINT16_S GetSegDataStrusegTmnlJointMainSegId(const UINT16_S segId);

/*
** ���������� ��ȡָ��IDSegDataStru���յ�������ڵ�SegID
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�������ڵ�SegID
*/ 
UINT16_S GetSegDataStrusegTmnlJointSideSegId(const UINT16_S segId);

/*
** ���������� ��ȡָ��IDSegDataStru������ZC����ID
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����ZC����ID
*/ 
UINT16_S GetSegDataStrusegManageZCId(const UINT16_S segId);

/*
** ���������� ��ȡָ��IDSegDataStru������ATS����ID
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����ATS����ID
*/ 
UINT16_S GetSegDataStrusegManageATSId(const UINT16_S segId);

/*
** ���������� ��ȡָ��IDSegDataStru������CI����ID
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����CI����ID
*/ 
UINT16_S GetSegDataStrusegManageCIId(const UINT16_S segId);

/*
** ���������� ��ȡָ��IDSegDataStru���յ�˵��ź��յ�˵�����
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�˵���
*/ 
UINT16_S GetSegDataStruendPointInfo(const UINT16_S segId,UINT16_S* pointType);

/*
** ���������� ��ȡָ��IDSegDataStru�����˵��ź����˵�����
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�˵���
*/ 
UINT16_S GetSegDataStrustartPointInfo(const UINT16_S segId,UINT16_S* pointType);

/*
** ���������� ��ȡָ����ָ��λ�õ�SEG��Ϣ
* ����˵���� const UINT16_S pointId;����
*             const UINT8_S startOrEnd  �˵�Ϊ�����յ�  1 ��� 2 �յ�
*             BnfSegStruct* pSegStru SEG�ṹ����Ϣָ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�˵���
*/ 
UINT8_S GetSegInfoBuffAccordPointId(UINT16_S pointId,const UINT8_S startOrEnd,BnfSegStruct* pSegStru);

/*
** ���������� ��ȡָ��CIID��ȡZCID
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ZCID
*/ 
UINT16_S ArrordCiIdGetZcId(const UINT16_S ciId);

#ifdef __cplusplus
}
#endif

#endif
