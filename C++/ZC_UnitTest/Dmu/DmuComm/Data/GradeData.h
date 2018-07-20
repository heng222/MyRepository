/*************************************************
  �ļ���   ��GradeData.h
  ����     ������      
  ����ʱ�� ��2016-8-12
  �������� �� GradeData���ݹ���
			DmuCommonData�����GradeData���ܿɷֽ����£�
			1��	��GradeDataStru�ṹ��ָ�����ռ�
			2��	��ȡGradeData����
			3��	��ȡGradeData������
			4��	��ȡGradeData��Ϣ
			5��	��ȡָ��IDGradeDataStru�Ľṹ���±�
			6��	��ȡָ��IDGradeDataStru�Ľṹ��ָ��
			7��	��ȡָ��IDGradeDataStru���¶��������Seg���
			8��	��ȡָ��IDGradeDataStru���¶��������Segƫ����
			9��	��ȡָ��IDGradeDataStru���¶��յ�����Seg���
			10��	��ȡָ��IDGradeDataStru���¶��յ�����Segƫ����
			11��	��ȡָ��IDGradeDataStru����������¶ȱ��
			12��	��ȡָ��IDGradeDataStru���������¶ȱ��
			13��	��ȡָ��IDGradeDataStru���յ������¶ȱ��
			14��	��ȡָ��IDGradeDataStru���յ�����¶ȱ��
			15��	��ȡָ��IDGradeDataStru���¶�ֵ
			16��	��ȡָ��IDGradeDataStru���¶��������·�߼��������б����
			17��	��ȡָ��IDGradeDataStru�������߰뾶
  ��ע    ���ޡ�
 
*************************************************/
#ifndef GRADE_DATA_H_
#define GRADE_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  GRADE_LINE_BYTE_NUM            34                        /*һ�������ֽ���*/
#define     GRADE_INCLUDE_LINK_NUM            10                        /*�¶��м�SEG���ֵ*/

#ifdef __cplusplus
extern "C" {
#endif

/*�¶ȱ�*/
typedef struct BnfGradeStruct
{
    UINT16_S  gradeId;                                /*���*/
    UINT16_S  orgnSegId;                                /*�¶��������Seg���*/
    UINT32_S  orgnSegOfst;                            /*�¶��������Segƫ����*/
    UINT16_S  tmnlSegId;                                /*�¶��յ�����Seg���*/
    UINT32_S  tmnlSegOfst;                            /*�¶��յ�����Segƫ����*/    
    UINT16_S    orgnRelatePointId;                        /*������������*/
    UINT16_S  orgnJointMainGradeId;                    /*��������¶ȱ��*/
    UINT16_S  orgnJointSideGradeId;                    /*�������¶ȱ��*/
    UINT16_S    tmnlRelatePointId;                        /*�յ����������*/
    UINT16_S  tmnlJointMainGradeId;                    /*�յ������¶ȱ��*/    
    UINT16_S  tmnlJointSideGradeId;                    /*�յ�����¶ȱ��*/
    UINT16_S  gradValue;                                /*�¶�ֵ*/
    UINT16_S  inclineDir;                                /*�¶��������·�߼��������б����*/
    UINT32_S  radius;                                    /*�����߰뾶*/

    /*��̬����*/
    UINT32_S  orgnSegIdLength;                        /*�¶��������Seg����*/
    UINT32_S  tmnlSegIdLength;                        /*�¶��յ�����Seg����*/
    UINT8_S    includeSegNum;                            /*������SEGID����*/
    UINT16_S    segIdBuff[GRADE_INCLUDE_LINK_NUM];        /*������SEGID*/
    UINT32_S    segIdLength[GRADE_INCLUDE_LINK_NUM];    /*����SEG�ĳ���*/
    UINT32_S gradeLength;                                /*�¶ȳ���*/    
}BnfGradeStruct;

/*
* ���������� ��GradeDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocGradeDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡGradeData����
* ����˵����
* ����ֵ  �� 
            BnfGradeStruct*
*/
BnfGradeStruct *GetGradeData(void);

/*
* ������������ȡGradeData������
* ����˵������
* ����ֵ  ��UINT16
*/
UINT16_S GetGradeDataLineNum(void);

/*
* ���������� ��ȡGradeData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfGradeStruct*
*/
BnfGradeStruct *GetGradeDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDGradeDataStru�Ľṹ���±�
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetGradeDataStruIndex(const UINT16_S gradeId);

/*
** ���������� ��ȡָ��IDGradeDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfGradeStruct* GetIndexIdGradeDataStru(const UINT16_S gradeId);

/*
** ���������� ��ȡָ��IDGradeDataStru���¶��������Seg���
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �¶��������Seg���
*/ 
UINT16_S GetGradeDataStruorgnSegId(const UINT16_S gradeId);

/*
** ���������� ��ȡָ��IDGradeDataStru���¶��������Segƫ����
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �¶��������Segƫ����
*/ 
UINT32_S GetGradeDataStruorgnSegOfst(const UINT16_S gradeId);

/*
** ���������� ��ȡָ��IDGradeDataStru���¶��յ�����Seg���
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �¶��յ�����Seg���
*/ 
UINT16_S GetGradeDataStrutmnlSegId(const UINT16_S gradeId);

/*
** ���������� ��ȡָ��IDGradeDataStru���¶��յ�����Segƫ����
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �¶��յ�����Segƫ����
*/ 
UINT32_S GetGradeDataStrutmnlSegOfst(const UINT16_S gradeId);

/*
** ���������� ��ȡָ��IDGradeDataStru����������¶ȱ��
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��������¶ȱ��
*/ 
UINT16_S GetGradeDataStruorgnJointMainGradeId(const UINT16_S gradeId);

/*
** ���������� ��ȡָ��IDGradeDataStru���������¶ȱ��
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������¶ȱ��
*/ 
UINT16_S GetGradeDataStruorgnJointSideGradeId(const UINT16_S gradeId);

/*
** ���������� ��ȡָ��IDGradeDataStru���յ������¶ȱ��
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ������¶ȱ��
*/ 
UINT16_S GetGradeDataStrutmnlJointMainGradeId(const UINT16_S gradeId);

/*
** ���������� ��ȡָ��IDGradeDataStru���յ�����¶ȱ��
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�����¶ȱ��
*/ 
UINT16_S GetGradeDataStrutmnlJointSideGradeId(const UINT16_S gradeId);

/*
** ���������� ��ȡָ��IDGradeDataStru���¶�ֵ
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �¶�ֵ
*/ 
UINT16_S GetGradeDataStrugradValue(const UINT16_S gradeId);

/*
** ���������� ��ȡָ��IDGradeDataStru���¶��������·�߼��������б����
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �¶��������·�߼��������б����
*/ 
UINT16_S GetGradeDataStruinclineDir(const UINT16_S gradeId);

/*
** ���������� ��ȡָ��IDGradeDataStru�������߰뾶
* ����˵���� const UINT16_S gradeId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �����߰뾶
*/ 
UINT32_S GetGradeDataStruradius(const UINT16_S gradeId);


#ifdef __cplusplus
}
#endif

#endif
