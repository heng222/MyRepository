/*************************************************
  �ļ���   ��StaRunLevelData.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� StaRunLevelData���ݹ���
			DmuCommonData�����StaRunLevelData���ܿɷֽ����£�
			1��	��StaRunLevelDataStru�ṹ��ָ�����ռ�
			2��	��ȡStaRunLevelData����
			3��	��ȡStaRunLevelData��Ϣ
			4��	��ȡָ��IDStaRunLevelDataStru�Ľṹ���±�
			5��	��ȡָ��IDStaRunLevelDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDStaRunLevelDataStru�����Ŀ�ĵر��
			7��	��ȡָ��IDStaRunLevelDataStru���յ�Ŀ�ĵر��
			8��	��ȡָ��IDStaRunLevelDataStru�����м���ּ���Ŀ
			9��	��ȡָ��IDStaRunLevelDataStru��
			10��	��ȡָ��������յ�����м����Ӧ�ٶ�

  ��ע    ���ޡ�
 
*************************************************/
#ifndef STARUNLEVEL_DATA_H_
#define STARUNLEVEL_DATA_H_

#include "../../../Common/CommonTypes.h"

#define STARUNLEVEL_LEVEL_NUM                      5                                   /*���м������*/              
#define STARUNLEVEL_LINE_BYTE_NUM                 38                                /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*ÿ�����м�����Ϣ*/
typedef struct _SngRunLevelStruct
{
    UINT16_S levelId;               /*������*/
    UINT16_S levelTime;             /*�����Ӧʱ��*/
    UINT16_S levelSpeed;            /*�����Ӧ�ٶ�*/
}SngRunLevelStruct;

/*վ����Ӫ��������ݽṹ��*/
typedef struct BnfStaRunLevelStruct
{
    UINT16_S  indexId;                           /*�������*/
    UINT16_S  startDestId;                       /*���Ŀ�ĵر��*/
    UINT16_S  endDestId;                           /*�յ�Ŀ�ĵر��*/
    UINT16_S  runLevelNum;                       /*���м���ּ���Ŀ*/
    SngRunLevelStruct runLevelStru[STARUNLEVEL_LEVEL_NUM];
}BnfStaRunLevelStruct;

/*
* ���������� ��StaRunLevelDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocStaRunLevelDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡStaRunLevelData����
* ����˵����
* ����ֵ  �� 
            BnfStaRunLevelStruct*
*/
BnfStaRunLevelStruct *GetStaRunLevelData(void);

/*
* ���������� ��ȡStaRunLevelData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfStaRunLevelStruct*
*/
BnfStaRunLevelStruct *GetStaRunLevelDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDStaRunLevelDataStru�Ľṹ���±�
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetStaRunLevelDataStruIndex(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDStaRunLevelDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfStaRunLevelStruct* GetIndexIdStaRunLevelDataStru(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDStaRunLevelDataStru�����Ŀ�ĵر��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ���Ŀ�ĵر��
*/ 
UINT16_S GetStaRunLevelDataStrustartDestId(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDStaRunLevelDataStru���յ�Ŀ�ĵر��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�Ŀ�ĵر��
*/ 
UINT16_S GetStaRunLevelDataStruendDestId(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDStaRunLevelDataStru�����м���ּ���Ŀ
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ���м���ּ���Ŀ
*/ 
UINT16_S GetStaRunLevelDataStrurunLevelNum(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDStaRunLevelDataStru��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: 
*/ 
SngRunLevelStruct* GetStaRunLevelDataStrurunLevelStru(const UINT16_S indexId);

/*
** ���������� ��ȡָ��������յ�����м����Ӧ�ٶ�
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0 ��ѯʧ��
*            > 0 : ��ѯ���ٶ� 
*/ 
UINT16_S GetSpdForLevelByStartToEnd(UINT16_S startId,UINT16_S endId,UINT16_S level);

#ifdef __cplusplus
}
#endif

#endif
