
/*************************************************
  �ļ���   ��AxleSectionData.c
  ����     ������      
  ����ʱ�� ��2016-8-10
  �������� �� AxleSectionData���ݹ���
			DmuCommonData�����AxleSectionData���ܿɷֽ����£�
			1��	��AxleSectionDataStru�ṹ��ָ�����ռ�
			2��	��ȡAxleSectionData����
			3��	��ȡAxleSectionData��Ϣ
			4��	��ȡָ��IDAxleSectionDataStru�Ľṹ���±�
			5��	��ȡָ��IDAxleSectionDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDAxleSectionDataStru������
			7��	��ȡָ��IDAxleSectionDataStru�İ���Seg��Ŀ
			8��	��ȡָ��IDAxleSectionDataStru��Seg���
			9��	��ȡ�������ΰ�����SegId����Ϣ
			10��	��ȡSEGID�����ļ�������ID
			11��	��ȡSEGID�����ļ������νṹ��ָ��
			12��	��ȡ��·�����������ID
			13��	��ȡָ��IDAxleSectionDataStru��Seg��Ϣ
			14��	��ȡ������������CIID
			15��	��ȡ������������ZC
			16��	��ȡ�������ΰ����߼�������Ϣ

  ��ע    ���ޡ�
 
*************************************************/
#ifndef AXLESECTION_DATA_H_
#define AXLESECTION_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  AXLESECTION_NAME_BYTE_NUM       16                                                                  /*���Ƶ��ֽ���*/
#define  AXLESECTION_SEG_MAX_NUM          5                                                                /*SEG�����Ŀ*/    
#define  AXLESECTION_LINE_BYTE_NUM       30                                                             /*һ�����ݵ��ֽ���*/
#define  AXLESECTION_BELONG_LOGICSEC_MAX_NUM      20                                                    /*�������ΰ����߼�����������*/        

#ifdef __cplusplus
extern "C" {
#endif

/*�������α�*/
typedef struct BnfAxleSectionStruct
{ 
    UINT16_S  indexId;                                                    /*�������*/
    UINT8_S      axleStcName[AXLESECTION_NAME_BYTE_NUM];                        /*����*/        
    UINT16_S  includeSegNum;                                                /*����Seg��Ŀ*/    
    UINT16_S     segIdBuff[AXLESECTION_SEG_MAX_NUM];                            /*Seg���*/

    /*�����ȡ�߼����������İ������߼����θ����Լ��߼�����ID*/
    UINT8_S includeLogicAxleSecNum;                                        /*�������߼����θ���*/
    UINT16_S logicSecId[AXLESECTION_BELONG_LOGICSEC_MAX_NUM];                /*�������߼�����ID*/
    UINT16_S orgnSegId;                                                    /*�������seg���*/
    UINT16_S tmnlSegId;                                                    /*�յ�����seg���*/
    UINT32_S orgnSegOfst;                                                    /*�������segƫ����*/
    UINT32_S tmnlSegOfst;                                                    /*�յ�����segƫ����*/
    UINT16_S  orgnAxleId;                                                    /*�����������*/
    UINT16_S  tmnlAxleId;                                                    /*�յ���������*/
    UINT8_S  orgnAxleSecNum;                                                /*��������������Ӽ������θ���*/
    UINT16_S  orgnAxleSgmtId[3];                                            /*��������������Ӽ������α��*/
    UINT8_S  tmnlAxleSecNum;                                                /*���������յ�����Ӽ������θ���*/
    UINT16_S  tmnlAxleSgmtId[3];                                            /*���������յ����Ӽ������α��*/
    UINT16_S  relatPointNum;                                                /*����������Ŀ*/    
    UINT16_S  relatPointId[4];                                            /*����������*/
    UINT16_S  relatPointStatus[4];                                         /*��������״̬*/
    UINT16_S  manageZCId;                                                    /*����ZC����ID*/
    UINT16_S  manageCIId;                                                    /*����CI����ID*/ 
}BnfAxleSectionStruct;

/*
* �������ƣ�MallocAxleSectionDataStru
* ���������� ��AxleSectionDataStru�ṹ��ָ�����ռ�
* ��������� UINT16_S lineNum �����������
* ��������� ��
* ����ֵ  �� void
*/
void MallocAxleSectionDataStru(UINT16_S lineNum);

/*
* �������ƣ� GetAxleSectionData
* ���������� ��ȡAxleSectionData����
* ��������� ��
* ��������� ��
* ����ֵ  ��
*           BnfAxleSectionStruct*
*/
BnfAxleSectionStruct *GetAxleSectionData(void);

/*
* �������ƣ� GetAxleSectionData
* ���������� ��ȡAxleSectionData����
* ��������� ��
* ��������� ��
* ����ֵ  ��
*           BnfAxleSectionStruct*
*/
BnfAxleSectionStruct *GetAxleSectionDataInfo(UINT16_S* lineNum);

/*
* �������ƣ� GetAxleSectionDataStruIndex
* ���������� ��ȡָ��IDAxleSectionDataStru�Ľṹ���±�
* ��������� const UINT16_S indexId;�������
* ��������� ��
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetAxleSectionDataStruIndex(const UINT16_S indexId);

/*
* �������ƣ� GetIndexIdAxleSectionDataStru
* ���������� ��ȡָ��IDAxleSectionDataStru�Ľṹ��ָ��
* ��������� const UINT16_S indexId;�������
* ��������� ��
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/
BnfAxleSectionStruct* GetIndexIdAxleSectionDataStru(const UINT16_S indexId);

/*
* �������ƣ� GetAxleSectionDataStruaxleStcName
* ���������� ��ȡָ��IDAxleSectionDataStru������
* ��������� const UINT16_S indexId;�������
* ��������� ��
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ����
*/ 
UINT8_S* GetAxleSectionDataStruaxleStcName(const UINT16_S indexId);

/*
* �������ƣ� GetAxleSectionDataStruincludeSegNum
* ���������� ��ȡָ��IDAxleSectionDataStru�İ���Seg��Ŀ
* ��������� const UINT16_S indexId;�������
* ��������� ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����Seg��Ŀ
*/ 
UINT16_S GetAxleSectionDataStruincludeSegNum(const UINT16_S indexId);

/*
* �������ƣ� GetAxleSectionDataStrusegIdBuff
* ���������� ��ȡָ��IDAxleSectionDataStru��Seg���
* ��������� const UINT16_S indexId;�������
* ��������� ��
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: Seg���
*/ 
UINT16_S* GetAxleSectionDataStrusegIdBuff(const UINT16_S indexId);

/*
* �������ƣ� GetAxleSectionOfSegInfo
* ���������� ��ȡ�������ΰ�����SegId����Ϣ
* ��������� const UINT16_S AxleSecId,��������ID
* ��������� UINT16_S* pSegId��SegID����
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:SegId����
*/
UINT16_S GetAxleSectionOfSegInfo(const UINT16_S AxleSecId,UINT16_S* pSegId);

/*
* �������ƣ� GetSegIdBelongofAxleSecId
* ���������� ��ȡSEGID�����ļ�������ID
* ��������� const UINT16_S  segId��SegID
*             const UINT8_S segNum      SEG����
*             const UINT8_S findNum  ��Ҫ���Ҽ���
* ��������� ��
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:��������ID
*/
UINT16_S GetSegIdBelongofAxleSecId(const UINT16_S* segIdbuff,const UINT8_S segNum,const UINT8_S findNum);

/*
* �������ƣ� GetSegIdBelongofAxleSecInfo
* ���������� ��ȡSEGID�����ļ������νṹ��ָ��
* ��������� const UINT16_S  segId��SegID
*             const UINT8_S segNum      SEG����
* ��������� ��
* ����ֵ  �� NULL: ��ȡ����ʧ��
*             !NULL:�������νṹ��ָ��
*/
BnfAxleSectionStruct* GetSegIdBelongofAxleSecInfo(const UINT16_S* segIdbuff,const UINT8_S segNum);

/*
* �������ƣ� GetLineAcMaxId
* ���������� ��ȡ��·�����������ID
* ��������� ��
* ��������� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:�����������ID
*/
UINT16_S GetLineAcMaxId(void);

/*
* �������ƣ� GetAxleSectionDataStruSegInfo
* ���������� ��ȡָ��IDAxleSectionDataStru��Seg��Ϣ
* ��������� const UINT16_S indexId;�������
* ��������� ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����SEG�ĸ���
*/ 
UINT16_S GetAxleSectionDataStruSegInfo(const UINT16_S indexId,UINT16_S* pSegId);

/*
* �������ƣ� GetLineAcBelongCiId
* ���������� ��ȡ������������CIID
* ��������� const UINT16_S acId����������ID
* ��������� ��
* ����ֵ  �� 0: ��ȡʧ��
*             ����ID
*/
UINT16_S GetLineAcBelongCiId(const UINT16_S acId);

/*
* �������ƣ� GetLineAcBelongZcId
* ���������� ��ȡ������������ZC
* ��������� const UINT16_S acId����������ID
* ��������� ��
* ����ֵ  �� 0: ��ȡʧ��
*            >0:����ZCID
*/
UINT16_S GetLineAcBelongZcId(const UINT16_S acId);

/*
* �������ƣ� GetLineAcIncludeLogicSectionInfo
* ���������� ��ȡ�������ΰ����߼�������Ϣ
* ��������� const UINT16_S acId����������ID
* ��������� UINT8_S *logicSectionNum,�߼���������
*            UINT16_S logicSectionIdBuf[]���߼�����ID����
* ����ֵ  �� 0: ��ȡʧ��
*            1: ��ȡ�ɹ�
*/
UINT8_S GetLineAcIncludeLogicSectionInfo(const UINT16_S acId,UINT8_S *logicSectionNum,UINT16_S logicSectionIdBuf[]);

#ifdef __cplusplus
}
#endif

#endif
