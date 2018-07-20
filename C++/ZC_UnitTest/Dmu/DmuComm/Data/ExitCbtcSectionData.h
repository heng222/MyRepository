/*************************************************
  �ļ���   ��ExitCbtcSectionData.h
  ����     ������      
  ����ʱ�� ��2016-8-12
  �������� �� ExitCbtcSectionData���ݹ���
			DmuCommonData�����ExitCbtcSectionData���ܿɷֽ����£�
			1��	��ExitCbtcSectionDataStru�ṹ��ָ�����ռ�
			2��	��ȡExitCbtcSectionData����
			3��	��ȡExitCbtcSectionData��Ϣ
			4��	��ȡָ��IDExitCbtcSectionDataStru�Ľṹ���±�
			5��	��ȡָ��IDExitCbtcSectionDataStru�Ľṹ��ָ��
			6��	 ��ȡָ��IDExitCbtcSectionDataStru���˳�CBTC����ʱ�г����з���
			7��	��ȡָ��IDExitCbtcSectionDataStru���˳�CBTC��������
			8��	 ��ȡָ��IDExitCbtcSectionDataStru���������seg���
			9��	��ȡָ��IDExitCbtcSectionDataStru���������Segƫ����
			10��	��ȡָ��IDExitCbtcSectionDataStru���յ�����Segƫ����
			11��	��ȡָ��IDExitCbtcSectionDataStru�İ�����Seg��Ŀ
			12��	��ȡָ��IDExitCbtcSectionDataStru��SEG���
			13��	��ѯĳ�����Ƿ���˳�CBTC�����յ��غ�
			14��	��ѯĳ�����Ƿ�����CBTC����

  ��ע    ���ޡ�
 
*************************************************/
#ifndef EXITCBTCSECTION_DATA_H_
#define EXITCBTCSECTION_DATA_H_

#include "../../../Common/CommonTypes.h"

#define EXITCBTCSECTION_SEG_MAX_NUM                      16                                                           /*���SEG����*/
#define EXITCBTCSECTION_LINE_BYTE_NUM                 48                                                        /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif


/*�˳�CBTC��������ݽṹ��*/
typedef struct BnfExitCbtcSectionStruct
{
    UINT16_S  indexId;                                        /*�������*/
    UINT16_S  dir;                                            /*�˳�CBTC����ʱ�г����з���*/
    UINT16_S  attribute;                                        /*�˳�CBTC��������*/
    UINT32_S  startOffset;                                    /*�������Segƫ����*/
    UINT32_S  endOffSet;                                        /*�յ�����Segƫ����*/
    UINT16_S  segNum;                                            /*������Seg��Ŀ*/
    UINT16_S  segInfoBuff[EXITCBTCSECTION_SEG_MAX_NUM];          /*SEG���*/

    /*��̬��������*/
    UINT16_S  startSegId;                                        /*�������seg���*/
    UINT16_S  endSegId;                                        /*�������seg���*/
}BnfExitCbtcSectionStruct;

/*
* ���������� ��ExitCbtcSectionDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocExitCbtcSectionDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡExitCbtcSectionData����
* ����˵����
* ����ֵ  �� 
            BnfExitCbtcSectionStruct*
*/
BnfExitCbtcSectionStruct *GetExitCbtcSectionData(void);

/*
* ���������� ��ȡExitCbtcSectionData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfExitCbtcSectionStruct*
*/
BnfExitCbtcSectionStruct *GetExitCbtcSectionDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDExitCbtcSectionDataStru�Ľṹ���±�
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetExitCbtcSectionDataStruIndex(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDExitCbtcSectionDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfExitCbtcSectionStruct* GetIndexIdExitCbtcSectionDataStru(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDExitCbtcSectionDataStru���˳�CBTC����ʱ�г����з���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �˳�CBTC����ʱ�г����з���
*/ 
UINT16_S GetExitCbtcSectionDataStrudir(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDExitCbtcSectionDataStru���˳�CBTC��������
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �˳�CBTC��������
*/ 
UINT16_S GetExitCbtcSectionDataStruattribute(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDExitCbtcSectionDataStru���������seg���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������seg���
*/ 
UINT16_S GetExitCbtcSectionDataStrustartSegId(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDExitCbtcSectionDataStru���������Segƫ����
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������Segƫ����
*/ 
UINT32_S GetExitCbtcSectDataStartOff(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDExitCbtcSectionDataStru���յ�����Segƫ����
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�����Segƫ����
*/ 
UINT32_S GetExitCbtcSectionDataStruendOffSet(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDExitCbtcSectionDataStru�İ�����Seg��Ŀ
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ������Seg��Ŀ
*/ 
UINT16_S GetExitCbtcSectionDataStrusegNum(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDExitCbtcSectionDataStru��SEG���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: SEG���
*/ 
UINT16_S* GetExitCbtcSectionDataStrusegInfoBuff(const UINT16_S indexId);

/* ���������� ��ѯĳ�����Ƿ���˳�CBTC�����յ��غ�
* ����˵���� 
* ����ֵ  �� 
*    1,�غ�
*    2,���غ�
*/
UINT8_S CheckAtQuitCbtcIsFindPoint(const UINT16_S seg,const UINT32_S offset);


/* ���������� ��ѯĳ�����Ƿ�����CBTC����
* ����˵���� 
* ����ֵ  �� 
*    0,������
*    1,����
*/
UINT8_S ExitCbtcSecIncludePoint(UINT16_S segId,UINT32_S offset);

#ifdef __cplusplus
}
#endif

#endif
