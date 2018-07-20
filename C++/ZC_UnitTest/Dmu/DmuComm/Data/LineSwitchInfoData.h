/*************************************************
  �ļ���   ��LineSwitchInfoData.h
  ����     ������      
  ����ʱ�� ��2016-8-12
  �������� �� LineSwitchInfoData���ݹ���
			DmuCommonData�����LineSwitchInfoData���ܿɷֽ����£�
			1��	��LineSwitchInfoDataStru�ṹ��ָ�����ռ�
			2��	��ȡLineSwitchInfoData����
			3��	��ȡLineSwitchInfoData��Ϣ
			4��	��ȡָ��IDLineSwitchInfoDataStru�Ľṹ���±�
			5��	��ȡָ��IDLineSwitchInfoDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDLineSwitchInfoDataStru���л���·�ƽ�ZCID
			7��	��ȡָ��IDLineSwitchInfoDataStru���л���·�ӹ�ZCID
			8��	��ȡָ��IDLineSwitchInfoDataStru���л���·����
			9��	��ȡָ��IDLineSwitchInfoDataStru���л���·�������seg���
			10��	��ȡָ��IDLineSwitchInfoDataStru���л���·�������segƫ��
			11��	��ȡָ��IDLineSwitchInfoDataStru���л�������seg���
			12��	��ȡָ��IDLineSwitchInfoDataStru���л�������segƫ��
			13��	��ȡָ��IDLineSwitchInfoDataStru���л���·�յ�����seg���
			14��	��ȡָ��IDLineSwitchInfoDataStru���л���·�յ�����segƫ��
			15��	��ȡָ��IDLineSwitchInfoDataStru���л�����ؽ�·���
			16��	��ȡָ��IDLineSwitchInfoDataStru���л���·�ڰ����ĵ�����Ŀ
			17��	��ȡָ��IDLineSwitchInfoDataStru�ĵ�����Ϣ�ṹ��
			18��	��ȡ�л���·������ID��Ϣ

  ��ע    ���ޡ�
 
*************************************************/
#ifndef LINESWITCHINFO_DATA_H_
#define LINESWITCHINFO_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "DataCommondefine.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"

#define LINESWITCHINFO_SWITCH_NUM                         (6 + 4)                                         /*�������*/
#define LINESWITCHINFO_LINE_BYTE_NUM                    (53  + 16)                                          /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*�л���·��Ϣ���ݽṹ��*/
typedef struct BnfLineSwitchInfoStruct
{
    UINT16_S  indexId;                                                    /*�������*/
    UINT16_S  lineSwitchTraZcId;                                            /*�л���·�ƽ�ZCID*/
    UINT16_S  lineSwitchTakeOverZcId;                                        /*�л���·�ӹ�ZCID*/
    UINT8_S   lineSwitchDir;                                                /*�л���·����*/
    UINT16_S  startLineSwitchInfoId;                                        /*�л���·�������seg���*/
    UINT32_S  startSegOffset;                                                /*�л���·�������segƫ��*/
    UINT16_S  switchPointSegId;                                            /*�л�������seg���*/
    UINT32_S  switchPointOffset;                                            /*�л�������segƫ��*/
    UINT16_S  endLineSwitchInfoId;                                          /*�л���·�յ�����seg���*/
    UINT32_S  segEndOffset;                                                  /*�л���·�յ�����segƫ��*/
    UINT16_S  relationRouteNum;                                           /*�л�����ؽ�·���*/  
    UINT16_S  includeSwitchNum;                                            /*�л���·�ڰ����ĵ�����Ŀ*/ 
    BnfSngSwitchInfoStruct switchInfoStru[LINESWITCHINFO_SWITCH_NUM];   /*������Ϣ�ṹ��*/

    /*������*/
    UINT8_S segNum;                                                        /*SEGID����*/
    UINT16_S segIdBuff[BOTHSEG_INCLUDE_MAX_SEG];                            /*������SEGID����*/
    UINT8_S acNum;                                                        /*�������θ���*/
    UINT16_S acIdBuff[TWO_POINT_AC_NUM_MAX];                                /*�����ļ�������ID*/
}BnfLineSwitchInfoStruct;

/*
* ���������� ��LineSwitchInfoDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocLineSwitchInfoDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡLineSwitchInfoData����
* ����˵����
* ����ֵ  �� 
            BnfLineSwitchInfoStruct*
*/
BnfLineSwitchInfoStruct *GetLineSwitchInfoData(void);

/*
* ���������� ��ȡLineSwitchInfoData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfLineSwitchInfoStruct*
*/
BnfLineSwitchInfoStruct *GetLineSwitchInfoDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru�Ľṹ���±�
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetLineSwitchInfoDataStruIndex(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfLineSwitchInfoStruct* GetIndexIdLineSwitchInfoDataStru(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л���·�ƽ�ZCID
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л���·�ƽ�ZCID
*/ 
UINT16_S GetLineSwitchInfoDataStrulineSwitchTraZcId(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л���·�ӹ�ZCID
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л���·�ӹ�ZCID
*/ 
UINT16_S GetLinSwInfDatliSwTakeOvZcId(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л���·����
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л���·����
*/ 
UINT8_S GetLineSwInfoDatalineSwDir(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л���·�������seg���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л���·�������seg���
*/ 
UINT16_S GetLineSwitchInfoDataStrustartLineSwitchInfoId(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л���·�������segƫ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л���·�������segƫ��
*/ 
UINT32_S GetLineSwitchInfoDataStrustartSegOffset(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л�������seg���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л�������seg���
*/ 
UINT16_S GetLineSwitchInfoDataStruswitchPointSegId(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л�������segƫ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л�������segƫ��
*/ 
UINT32_S GetLineSwInfoDataSwPointOff(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л���·�յ�����seg���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л���·�յ�����seg���
*/ 
UINT16_S GetLineSwitchInfoDataStruendLineSwitchInfoId(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л���·�յ�����segƫ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л���·�յ�����segƫ��
*/ 
UINT32_S GetLineSwitchInfoDataStrusegEndOffset(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л�����ؽ�·���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л�����ؽ�·���
*/ 
UINT16_S GetLineSwitchInfoDataStrurelationRouteNum(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л���·�ڰ����ĵ�����Ŀ
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л���·�ڰ����ĵ�����Ŀ
*/ 
UINT16_S GetLineSwitchInfoDataStruincludeSwitchNum(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru�ĵ�����Ϣ�ṹ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ������Ϣ�ṹ��
*/ 
BnfSngSwitchInfoStruct* GetLineSwInfDataSwInfStru(const UINT16_S indexId);

/*
* ���������� ��ȡ�л���·������ID��Ϣ
* ��������� const UINT16_S localZcId, ����ZCid
*            UINT16_S changeLineIdBuf[]���л���·ID���飨���30����
* ����ֵ  �� 0xff: ��ȡ����ʧ��
*            0>: ����
*/
UINT8_S GetLocalZcChangeLineNum(const UINT16_S localZcId, UINT16_S changeLineIdBuf[]);

#ifdef __cplusplus
}
#endif

#endif
