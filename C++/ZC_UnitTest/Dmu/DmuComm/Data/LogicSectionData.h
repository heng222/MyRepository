/*************************************************
  �ļ���   ��LogicSectionData.h
  ����     ������      
  ����ʱ�� ��2016-8-12
  �������� �� LogicSectionData���ݹ���
			DmuCommonData�����LogicSectionData���ܿɷֽ����£�
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
#ifndef LOGICSECTION_DATA_H_
#define LOGICSECTION_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "DataCommondefine.h"

#define LOGICSECTION_NAME_BYTE_LEN                 16                               /*���Ƴ���*/
#define LOGICSECTION_SEGID_MAX_NUM                    5                                /*�߼����ΰ��������SEGID*/
#define LOGICSECTION_OF_SWITCH_MAX_NUM                2                                /*һ���߼����ΰ����ĵ������*/
#define LOGICSECTION_LINE_BYTE_NUM                 30                                /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BnfRelateLogicSecInfoStruct
{
    UINT16_S relateLogicId;                            /*������߼����ε�ID*/
    UINT16_S relateSegId;                                /*�����SEG��ID*/
    UINT8_S  pointFalg;                                /*��� �����յ�*/
}BnfRelateLogicSecInfoStruct;


/*�߼����α����ݽṹ��*/
typedef struct BnfLogicSectionStruct
{
    UINT16_S  indexId;                                /*�������*/
    UINT8_S     name[LOGICSECTION_NAME_BYTE_LEN];        /*����*/
    UINT16_S  startSegId;                                /*�������Seg���*/
    UINT32_S  startSegOffset;                            /*�������Segƫ����*/
    UINT16_S  endSegId;                                /*�յ�����Seg���*/
    UINT32_S  endSegOffset;                            /*�յ�����Segƫ����*/

    /*�����ȡ�߼����������ļ�������ID*/
    UINT16_S  belongAxleSecId;                        /*������������ID*/
    UINT16_S  mainOrgnLogicSgmtId;                    /*��������������ǰ���߼����εı��*/
    UINT16_S  mainTmnlLogicSgmtId;                    /*�������������ں����߼����εı��*/    
    UINT16_S  startJointMainLogicId;                    /*������������߼�����ID*/
    UINT16_S  startJointSideLogicId;                    /*�����������߼�����ID*/
    UINT16_S  tmnlJointMainLogicId;                    /*�յ����������߼�����ID*/
    UINT16_S  tmnlJointSideLogicId;                    /*�յ���������߼�����ID*/ 
    UINT8_S   relateLogicNum;                            /*������߼����θ���*/
    BnfRelateLogicSecInfoStruct  relateLogicInfo[LOGICSECTION_OF_SWITCH_MAX_NUM];        /*������߼�������Ϣ*/
    UINT16_S  manageZCId;                                /*����ZC����ID*/
    UINT16_S  manageCIId;                                /*����CI����ID*/
    UINT16_S includeSegIdNum;                            /*������segId����*/
    UINT16_S segIdBuff[LOGICSECTION_SEGID_MAX_NUM];    /*������SEGID*/
    UINT8_S switchIdNum;                                                                /*���߼����ΰ�������ĸ���*/
    BnfSngSwitchInfoStruct switchIdStru[LOGICSECTION_OF_SWITCH_MAX_NUM];            /*���߼����ΰ����ĵ�����Ϣ*/
}BnfLogicSectionStruct;

/*
* ���������� ��LogicSectionDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocLogicSectionDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡLogicSectionData����
* ����˵����
* ����ֵ  �� 
            BnfLogicSectionStruct*
*/
BnfLogicSectionStruct *GetLogicSectionData(void);

/*
* ���������� ��ȡLogicSectionData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfLogicSectionStruct*
*/
BnfLogicSectionStruct *GetLogicSectionDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDLogicSectionDataStru�Ľṹ���±�
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetLogicSectionDataStruIndex(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDLogicSectionDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfLogicSectionStruct* GetIndexIdLogicSectionDataStru(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDLogicSectionDataStru������
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ����
*/ 
UINT8_S* GetLogicSectionDataStruname(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDLogicSectionDataStru���������Seg���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������Seg���
*/ 
UINT16_S GetLogicSectionDataStrustartSegId(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDLogicSectionDataStru���������Segƫ����
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������Segƫ����
*/ 
UINT32_S GetLogSecDataStartSegOff(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDLogicSectionDataStru���յ�����Seg���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�����Seg���
*/ 
UINT16_S GetLogicSectionDataStruendSegId(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDLogicSectionDataStru���յ�����Segƫ����
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�����Segƫ����
*/ 
UINT32_S GetLogicSectionDataStruendSegOffset(const UINT16_S indexId);

/*
* ���������� ��ȡ��·�߼��������ID
* ����˵���� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:�߼��������ID
*/
UINT16_S GetLineLogicSectionMaxId(void);

/*
* ���������� ���������SEGID��ȡ�߼����ε���Ϣ
* ����˵���� const UINT16_S* pSegId;SEGIDָ��ָ��
             const UINT16_S segIdNum;SEGID����
             UINT16_S logicSectionIdBuf[];�߼�����ID����
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �߼����θ���
*/ 
UINT8_S GetSegIdBuffOfLogSecInfo(const UINT16_S* pSegId,const UINT16_S segIdNum,UINT16_S logicSectionIdBuf[]);

/*
* ���������� ��ȡ�߼���������ZC
* ����˵���� const UINT16_S logicSectionId���߼�����ID
* ����ֵ  �� 0: ��ȡʧ��
*            >0:����ZCID
*/
UINT16_S GetLineLogicSectionBelongZcId(const UINT16_S logicSectionId);

/*
* ���������� ��ȡ�߼���������CI
* ����˵���� const UINT16_S logicSectionId���߼�����ID
* ����ֵ  �� 0: ��ȡʧ��
*            >0:����CIID
*/
UINT16_S GetLineLogicSectionBelongCiId(const UINT16_S logicSectionId);

/*
* ���������� ��ȡ�߼���������AC
* ����˵���� const UINT16_S logicSectionId���߼�����ID
* ����ֵ  �� 0: ��ȡʧ��
*            >0:����ACID
*/
UINT16_S GetLineLogicSectionBelongAcId(const UINT16_S logicSectionId);

/*
* ���������� ��ѯ��SEGǰ�����߼�����
*            (1)����һ���߼�����ֱ�ӷ���
*            (2)���ж���������߼�����ƫ��������
*            (3)����SEG�����������߼������У��������������߼�����ID
* ����˵���� const UINT16_S startSegId,const UINT32_S startOffset,const UINT32_S endOffset
             UINT16_S logicSectionIdBuf[];�߼�����ID����
* ����ֵ  :  0: ʧ��
*             1: �ɹ�
*/ 
UINT8_S GetSegFontSecOfLogSecInfo(const UINT16_S startSegId,const UINT32_S startSegLen,UINT16_S* mainLogicId,UINT16_S* sideLogicId);

/*
* ���������� ��ѯ��SEG�󷽵��߼�����
*            (1)����һ���߼�����ֱ�ӷ���
*            (2)���ж���������߼�����ƫ��������
*            (3)����SEG�����������߼������У��������������߼�����ID
* ����˵���� const UINT16_S startSegId,const UINT32_S startOffset,const UINT32_S endOffset
             UINT16_S logicSectionIdBuf[];�߼�����ID����
* ����ֵ  :  0: ʧ��
*             1: �ɹ�
*/ 
UINT8_S GetSegRearSecOfLogSecInfo(const UINT16_S startSegId,const UINT32_S startSegLen,UINT16_S* mainLogicId,UINT16_S* sideLogicId);

/*
* ���������� ��ȡ�߼�����ID��������߼�����ID
* ����˵���� const UINT16_S logicSectionId���߼�����ID
* ����ֵ  �� UINT16_NULL: ��ѯʧ��
*            >0: �������߼�����ID
*/
UINT8_S GetLineLogicSectionBelongRelareLc(const UINT16_S logicSectionId,UINT8_S* relateLogicNum,BnfRelateLogicSecInfoStruct* relateLogicInfo);

#ifdef __cplusplus
}
#endif

#endif
