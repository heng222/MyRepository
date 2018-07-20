/********************************************************                                                                                                            
 �� �� ���� MAStatusData.h  
 ��    �ߣ� ZC��
 ����ʱ�䣺 2015-04-18
 ������ �г�״̬���ݹ���  
 ��ע�� ��  
********************************************************/
#ifndef MA_STATUS_DATA_H_
#define MA_STATUS_DATA_H_


#include "MADefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

/*MA��ʹ�õ����ϰ�����Ϣ���ݽṹ*/
typedef struct ObsOfMAStruct
{
	UINT16_S  ObsId;                                      /*�ϰ���ID*/
	UINT8_S  ObsType;                                     /*�ϰ�������*/
	UINT8_S ObsStatus;                                    /*�ϰ���״̬*/
	UINT8_S ObsLockStatus;                                /*�ϰ�������״̬*/
}ObsOfMAStruct;

/*MA��ʹ�õ�����ʱ������Ϣ���ݽṹ*/
typedef struct TsrOfMAStruct
{
	UINT16_S TsrSpeed;                                   /*��ʱ����ֵ��cm/s��*/
	UINT16_S TsrHeadLink;                                /*��ʱ����ʼ��Link*/
	UINT32_S TsrHeadOffset;                              /*��ʱ����ʼ��Offset*/
	UINT16_S TsrTailLink;                                /*��ʱ�����ն�Link*/
	UINT32_S TsrTailOffset;                              /*��ʱ�����յ�Offset*/
	UINT16_S BelongZcId;                                 /*��ʱ��������ZCID*/
}TsrOfMAStruct;


/*�г��ƶ���Ȩ��Ϣ(MA)״̬���ݽṹ��*/
typedef struct MaDataStruct
{
	UINT16_S TrainID;                                    /*�г�ID��*/
	UINT8_S MaType;                                      /*MA���ͣ�0x55-�����ƶ�MA;0xaa-�ǽ����ƶ�MA;0-��MA��Ϣ*/
	UINT16_S MaHeadLink;                                 /*MA������κ�*/
	UINT32_S MaHeadOffset;                               /*MA���ƫ��λ��*/
	UINT8_S MaHeadDir;                                   /*MA��㷽��*/
	UINT16_S MaTailLink;                                 /*MA�յ����κ�*/
	UINT32_S MaTailOffset;                               /*MA�յ�ƫ��λ��*/
	UINT8_S MaTailDir;                                   /*MA�յ㷽��*/
	UINT16_S MaEndObsId;                                 /*MA�յ��ϰ���ID*/
	UINT8_S  MaEndObsType;                               /*MA�յ��ϰ��������*/
	UINT8_S  MaEndAttribute;                             /*MA�յ�����*/
	UINT8_S ObsNum;                                      /*MA��Χ�ڵ��ϰ�������*/
	ObsOfMAStruct ObsOfMAStru[MA_AREA_OBS_SUM_MAX];      /*�ϰ���ṹ��*/
	UINT8_S TsrNum;                                      /*��ʱ��������*/
	TsrOfMAStruct TsrOfMAStru[MA_AREA_TSR_SUM_MAX];      /*��ʱ���ٽṹ��*/
}MaDataStruct;

/*����ZC�г��ƶ���Ȩ��Ϣ(MA2)״̬���ݽṹ��*/
typedef struct NextZcMaDataStruct
{
	UINT16_S TrainID;                                    /*�г�ID��*/
	UINT16_S NextId;                                     /*����MA2������ZCID*/
	UINT8_S HandOutType;                                 /*����ZC������Ϣ֡����*/
	UINT8_S MaInfoFlag;                                  /*MA2���ڱ�־��0x55-��MA���ڣ�0xaa-��MA����*/
	UINT8_S ExceedBoundaryFlag;                          /*MA2�Ƿ���Խ���ֽ��*/
	UINT8_S MaLength;                                    /*MA2����*/
	UINT16_S MaHeadLink;                                 /*MA������κ�*/
	UINT32_S MaHeadOffset;                               /*MA���ƫ��λ��*/
	UINT8_S MaHeadDir;                                   /*MA��㷽��*/
	UINT16_S MaTailLink;                                 /*MA�յ����κ�*/
	UINT32_S MaTailOffset;                               /*MA�յ�ƫ��λ��*/
	UINT8_S MaTailDir;                                   /*MA�յ㷽��*/
	UINT8_S  MaEndAttribute;                             /*MA�յ�����*/
	UINT16_S OverlapId;                                  /*MA������overlapID*/
	UINT8_S ObsNum;                                      /*MA��Χ�ڵ��ϰ�������*/
	ObsOfMAStruct ObsOfMAStru[MA_AREA_OBS_SUM_MAX];      /*�ϰ���ṹ��*/
	UINT8_S TsrNum;                                      /*��ʱ��������*/
	TsrOfMAStruct TsrOfMAStru[MA_AREA_TSR_SUM_MAX];      /*��ʱ���ٽṹ��*/
}NextZcMaDataStruct;

/*************************************************
  ������:      GetNextZcMaStatusSum
  ��������:    ��ȡ����ZC�г��ƶ���Ȩ��������
  ����:        ��
  ���:        ��
  ����ֵ:      0u: ��ȡ����ʧ��
               >0u: �г��ƶ���Ȩ��������
*************************************************/
UINT16_S GetNextZcMaStatusSum(void);

/*************************************************
  ������:      SetNextZcMaStatusSum
  ��������:    ��������ZC�г��ƶ���Ȩ��������
  ����:        const UINT8 maCurSum  �ƶ���ȨĿǰ���� 
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ��������ʧ��
               RETURN_SUCCESS: �������ݳɹ�
*************************************************/
UINT16_S SetNextZcMaStatusSum(const UINT8_S maCurSum);

/*************************************************
  ������:      GetNextZcMaStatusBufIndex
  ��������:    �����г�ID����ȡ����ZC�г��ƶ���Ȩ���������±�
  ����:        const UINT16_S trainId  �г�ID
  ���:        ��
  ����ֵ:      LINE_MAX_TRAIN_ID:      ��ȡ����ʧ��
               (0u,LINE_MAX_TRAIN_ID): ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetNextZcMaStatusBufIndex(const UINT16_S trainId);

/*************************************************
  ������:      GetNextZcHandOutType
  ��������:    �����г�ID����ȡ������ƶ���Ȩ������ZC��������
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE:    ��ȡ����ʧ��
               <RETURN_UINT8_MAX_VALUE:   ����ZC��������
*************************************************/
UINT8_S GetNextZcHandOutType(const UINT16_S trainId);

/*************************************************
  ������:      SetNextZcHandOutType
  ��������:    �����г�ID�����ü�����ƶ���Ȩ������ZC��������
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��������ʧ��
               RETURN_SUCCESS: �ɹ���������ZC��������
*************************************************/
UINT8_S SetNextZcHandOutType(const UINT16_S trainId,const UINT8_S handOutType);

/*************************************************
  ������:      GetNextZcId
  ��������:    �����г�ID����ȡ������ƶ���Ȩ������ZCID
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_UINT16_MAX_VALUE: ��ȡ����ʧ��
               <RETURN_UINT16_MAX_VALUE: ����ZCID
*************************************************/
UINT16_S GetNextZcId(const UINT16_S trainId);

/*************************************************
  ������:      SetNextZcId
  ��������:    �����г�ID�����ü�����ƶ���Ȩ������ZCID
  ����:        const UINT16_S trainId  �г�ID 
               const UINT16_S zcId  ����ZC�ı��
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT16_S SetNextZcId(const UINT16_S trainId,const UINT16_S zcId);

/*************************************************
  ������:      GetNextZcMaInfoFlag
  ��������:    �����г�ID����ȡ����ZC�г��ƶ���Ȩ���ڱ�־
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE: ��ȡ����ʧ��
               FLAG_SET: ����MA
               FLAG_UNSET:������MA
*************************************************/
UINT8_S GetNextZcMaInfoFlag(const UINT16_S trainId);

/*************************************************
  ������:      SetNextZcMaInfoFlag
  ��������:    �����г�ID����������ZC�г��ƶ���Ȩ���ڱ�־
  ����:        const UINT16_S trainId  �г�ID 
               const UINT8_S maInfoFlag  ��ʶ
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��������ʧ��
               RETURN_SUCCESS: �������ݳɹ�
*************************************************/
UINT8_S SetNextZcMaInfoFlag(const UINT16_S trainId,const UINT8_S maInfoFlag);

/*************************************************
  ������:      GetNextZcMaStatusMaLength
  ��������:    �����г�ID����ȡ����ZC�г��ƶ���Ȩ����
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE: ��ȡ����ʧ��
               <RETURN_UINT8_MAX_VALUE:MA2����
*************************************************/
UINT8_S GetNextZcMaStatusMaLength(const UINT16_S trainId);

/*************************************************
  ������:      SetNextZcMaStatusMaLength
  ��������:    �����г�ID����ȡ����ZC�г��ƶ���Ȩ����
  ����:        const UINT16_S trainId  �г�ID 
               const UINT8_S maLength  MA����
  ���:        ��
  ����ֵ:      RETURN_ERROR:  ��������ʧ��
               RETURN_SUCCESS:�������ݳɹ�
*************************************************/
UINT8_S SetNextZcMaStatusMaLength(const UINT16_S trainId,const UINT8_S maLength);

/*************************************************
  ������:      GetNextZcMaHeadLink
  ��������:    ��ȡ�ƶ���Ȩ���LINK
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_ERROR:  ��ȡ����ʧ��
               >0u: ���LINK
*************************************************/
UINT16_S GetNextZcMaHeadLink(const UINT16_S trianId);

/*************************************************
  ������:      SetNextZcMaHeadLink
  ��������:    �����ƶ���Ȩ���LINK
  ����:        const UINT16_S trainId  �г�ID 
               const UINT16_S link MA���link
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetNextZcMaHeadLink(const UINT16_S trianId, const UINT16_S link);

/*************************************************
  ������:      GetNextZcMaHeadOffset
  ��������:    ��ȡMA2�ƶ���Ȩ���offset
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_UINT32_MAX_VALUE: ��ȡ����ʧ��
               <RETURN_UINT32_MAX_VALUE: ���offset
*************************************************/
UINT32_S GetNextZcMaHeadOffset(const UINT16_S trianId);

/*************************************************
  ������:      SetNextZcMaHeadOffset
  ��������:    ����MA2�ƶ���Ȩ���offset
  ����:        const UINT16_S trainId  �г�ID 
               const UINT32_S offset  ���ƫ����
  ���:        ��
  ����ֵ:      RETURN_SUCCESS: ���óɹ�
               RETURN_ERROR:   ����ʧ��
*************************************************/
UINT8_S SetNextZcMaHeadOffset(const UINT16_S trianId, const UINT32_S offset);

/*************************************************
  ������:      GetNextZcMaHeadDir
  ��������:    ��ȡ����ZC�ƶ���Ȩ��㷽��
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE: ���óɹ�
               <RETURN_UINT8_MAX_VALUE: ���LINK����
*************************************************/
UINT8_S GetNextZcMaHeadDir(const UINT16_S trainId);

/*************************************************
  ������:      SetNextZcMaHeadDir
  ��������:    ��������ZC�ƶ���Ȩ��㷽��
  ����:        const UINT16_S trainId  �г�ID 
               const UINT8_S maHeadDir ���MA����
  ���:        ��
  ����ֵ:      RETURN_SUCCESS: ���óɹ�
               RETURN_ERROR:   ����ʧ��
*************************************************/
UINT8_S SetNextZcMaHeadDir(const UINT16_S trainId,const UINT8_S maHeadDir);

/*************************************************
  ������:      GetNextZcMaTailLink
  ��������:    ��ȡMA2�ƶ���Ȩ�յ�LINK
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      DEFAULT_UINT16_VALUE: ��ȡ����ʧ��
               >0u: ���LINK
*************************************************/
UINT16_S GetNextZcMaTailLink(const UINT16_S trianId);

/*************************************************
  ������:      SetNextZcMaTailLink
  ��������:    �����ƶ���Ȩ�յ�LINK
  ����:        const UINT16_S trainId  �г�ID 
               const UINT16_S link MA�յ�link
  ���:        ��
  ����ֵ:      RETURN_SUCCESS: ���óɹ�
               RETURN_ERROR:   ����ʧ��
*************************************************/
UINT8_S SetNextZcMaTailLink(const UINT16_S trianId, const UINT16_S link);

/*************************************************
  ������:      GetNextZcMaTailOffset
  ��������:    ��ȡMA2�ƶ���Ȩ�յ�offset
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_UINT32_MAX_VALUE: ��ȡ����ʧ��
               <RETURN_UINT32_MAX_VALUE: ���offset
*************************************************/
UINT32_S GetNextZcMaTailOffset(const UINT16_S trianId);

/*************************************************
  ������:      SetNextZcMaTailOffset
  ��������:    ����MA2�ƶ���Ȩ�յ�offset
  ����:        const UINT16_S trainId  �г�ID 
               const UINT32_S offset MA�յ�offset
  ���:        ��
  ����ֵ:      RETURN_SUCCESS: ���óɹ�
               RETURN_ERROR:   ����ʧ��
*************************************************/
UINT8_S SetNextZcMaTailOffset(const UINT16_S trianId, const UINT32_S offset);

/*************************************************
  ������:      GetNextZcMaTailDir
  ��������:    ��ȡ����ZC�ƶ���Ȩ�յ㷽��
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE: ��ȡ����ʧ��
               <RETURN_UINT8_MAX_VALUE: �յ�LINK����
*************************************************/
UINT8_S GetNextZcMaTailDir(const UINT16_S trainId);

/*************************************************
  ������:      SetNextZcMaTailDir
  ��������:    ��ȡ����ZC�ƶ���Ȩ�յ㷽��
  ����:        const UINT16_S trainId  �г�ID 
               const UINT8_S maTailDir �յ�MA����
  ���:        ��
  ����ֵ:      RETURN_SUCCESS: ���óɹ�
               RETURN_ERROR:   ����ʧ��
*************************************************/
UINT8_S SetNextZcMaTailDir(const UINT16_S trainId,const UINT8_S maTailDir);

/*************************************************
  ������:      GetNextZcMaEndAttribute
  ��������:    ��ȡ����ZC�ƶ���Ȩ�յ�����
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE: ��ȡ����ʧ��
               >0u:                    �յ�����
*************************************************/
UINT8_S GetNextZcMaEndAttribute(const UINT16_S trainId);

/*************************************************
  ������:      SetNextZcMaEndAttribute
  ��������:    ��������ZC�ƶ���Ȩ�յ�����
  ����:        const UINT16_S trainId  �г�ID 
               const UINT8_S endAttribute �յ�����
  ���:        ��
  ����ֵ:      RETURN_SUCCESS: ���óɹ�
               RETURN_ERROR:   ����ʧ��
*************************************************/
UINT8_S SetNextZcMaEndAttribute(const UINT16_S trainId, const UINT8_S endAttribute);

/*************************************************
  ������:      GetNextZcMaObsNum
  ��������:    ��ȡ����ZC�ƶ���Ȩ��Ӧ�ϰ�������
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE: ��ȡ����ʧ��
               <RETURN_UINT8_MAX_VALUE: �ϰ�������
*************************************************/
UINT8_S GetNextZcMaObsNum(const UINT16_S trainId);

/*************************************************
  ������:      SetNextZcMaObsNum
  ��������:    ��������ZC�ƶ���Ȩ��Ӧ�ϰ�������
  ����:        const UINT16_S trainId  �г�ID 
               const UINT8_S obsNum �ϰ�������
  ���:        ��
  ����ֵ:      RETURN_SUCCESS: ���óɹ�
               RETURN_ERROR:   ����ʧ��
*************************************************/
UINT8_S SetNextZcMaObsNum(const UINT16_S trainId, const UINT8_S obsNum);

/*************************************************
  ������:      GetNextZcObsOfMAStru
  ��������:    ��ȡ����ZC�ƶ���Ȩ�ϰ�����Ϣ
  ����:        const UINT16_S trainId  �г�ID                
  ���:        ObsOfMAStruct obsStru[] �ϰ�����Ϣ���� 
  ����ֵ:      RETURN_SUCCESS: ��ȡ�ɹ�
               RETURN_ERROR:   ��ȡʧ��
*************************************************/
UINT8_S GetNextZcObsOfMAStru(const UINT16_S trainId, ObsOfMAStruct obsStru[]);

/*************************************************
  ������:      SetNextZcObsOfMAStru
  ��������:    ��������ZC�ƶ���Ȩ�ϰ�����Ϣ
  ����:        const UINT16_S trainId  �г�ID                
               const ObsOfMAStruct obsStru[] �ϰ�����Ϣ����
               const UINT8_S obsNum �ϰ�������
  ���:        ��
  ����ֵ:      RETURN_SUCCESS: ��ȡ�ɹ�
               RETURN_ERROR:   ��ȡʧ��
*************************************************/
UINT8_S SetNextZcObsOfMAStru(const UINT16_S trainId,const ObsOfMAStruct obsStru[],const UINT8_S obsNum);

/*************************************************
  ������:      GetNextZcMaTsrNum
  ��������:    ��ȡ����ZC�ƶ���Ȩ��ӦTrs����
  ����:        const UINT16_S trainId  �г�ID                
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE: ��ȡ����ʧ��
               <RETURN_UINT8_MAX_VALUE: ��ʱ��������
*************************************************/
UINT8_S GetNextZcMaTsrNum(const UINT16_S trainId);

/*************************************************
  ������:      SetNextZcMaTsrNum
  ��������:    �����ƶ���Ȩ��Ӧ��ʱ��������
  ����:        const UINT16_S trainId  �г�ID
               const UINT8_S tsrNum    ��ʱ��������
  ���:        ��
  ����ֵ:      RETURN_SUCCESS:  ���óɹ�
               RETURN_ERROR:    ����ʧ��
*************************************************/
UINT8_S SetNextZcMaTsrNum(const UINT16_S trainId, const UINT8_S tsrNum);

/*************************************************
  ������:      GetNextZcTsrOfMAStru
  ��������:    ��ȡ����ZC�ƶ���ȨTsr��Ϣ
  ����:        const UINT16_S trainId    �г�ID
  ���:        TsrOfMAStruct ObsOfMAStru Tsr��Ϣ
  ����ֵ:      RETURN_SUCCESS:  ��ȡ�ɹ�
               RETURN_ERROR:    ��ȡʧ��
*************************************************/
UINT8_S GetNextZcTsrOfMAStru(const UINT16_S trainId, TsrOfMAStruct tsrOfMAStru[]);

/*************************************************
  ������:      SetNextZcTsrOfMAStru
  ��������:    ��������ZC�ƶ���ȨTsr��Ϣ
  ����:        const UINT16_S trainId    �г�ID
               const TsrOfMAStruct* tsrOfMAStru Tsr��Ϣ
               const UINT8_S tsrNum  TSR����
  ���:        ��
  ����ֵ:      RETURN_SUCCESS:  ���óɹ�
               RETURN_ERROR:    ����ʧ��
*************************************************/
UINT8_S SetNextZcTsrOfMAStru(const UINT16_S trainId, const TsrOfMAStruct* tsrOfMAStru,const UINT8_S tsrNum);

/*************************************************
  ������:      SetNextZcMaStatusTrainId
  ��������:    ��������ZC����ĳ�±��Ӧ���г�ID
  ����:        const UINT16_S trainId    �г�ID
  ���:        ��
  ����ֵ:      RETURN_SUCCESS:  ���óɹ�
               RETURN_ERROR:    ����ʧ��
*************************************************/
UINT8_S SetNextZcMaStatusTrainId(const UINT16_S trainId);

/*************************************************
  ������:      DeleteNextZcSingleTrainMaInfo
  ��������:    ɾ������ZC���뵥���г��ƶ���Ȩ��Ϣ
  ����:        const UINT16_S trainId    �г�ID
  ���:        ��
  ����ֵ:      ��
*************************************************/
void DeleteNextZcSingleTrainMaInfo(const UINT16_S trainId);

/*************************************************
  ������:      ClearNextZcSingleTrainMaInfo
  ��������:    �������ZC���뵥���г��ƶ���Ȩ��Ϣ
  ����:        const UINT16_S trainId    �г�ID
  ���:        ��
  ����ֵ:      ��
*************************************************/
void ClearNextZcSingleTrainMaInfo(const UINT16_S trainId);

/*************************************************
  ������:      GetMaStatusData
  ��������:    ��ȡ�ƶ���Ȩ����
  ����:        ��
  ���:        ��
  ����ֵ:      �ƶ���Ȩ�ṹ��������׵�ַ
*************************************************/
MaDataStruct* GetMaStatusData(void);

/*************************************************
  ������:      GetMaStatusSum
  ��������:    ��ȡ�г��ƶ���Ȩ��������
  ����:        ��
  ���:        ��
  ����ֵ:      �г��ƶ���Ȩ��������
*************************************************/
UINT16_S GetMaStatusSum(void);

/*************************************************
  ������:      GetMaStatusTrainId
  ��������:    ��ȡĳ�±��Ӧ���г�ID
  ����:        const UINT16_S bufIndex, �����±� 
  ���:        ��
  ����ֵ:      0u:  ��ȡ����ʧ��
               >0u: �г�ID 
*************************************************/
UINT16_S GetMaStatusTrainId(const UINT16_S bufIndex);

/*************************************************
  ������:      SetMaStatusTrainId
  ��������:    ����ĳ�±��Ӧ���г�ID
  ����:        const UINT16_S trainId, �г�Id  
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetMaStatusTrainId(const UINT16_S trainId);

/*************************************************
  ������:      GetMaStatusBufIndex
  ��������:    ��ȡָ���г�ID������
  ����:        const UINT16_S trainId, �г�Id  
  ���:        ��
  ����ֵ:      LINE_MAX_TRAIN_ID:      ��ȡʧ��
               [1u,LINE_MAX_TRAIN_ID): ��ȡ�ɹ�
*************************************************/
UINT8_S GetMaStatusBufIndex(const UINT16_S trainId);

/*************************************************
  ������:      GeSingleMaInfo
  ��������:    ��ȡָ���г�ID��MA��Ϣ
  ����:        const UINT16_S trainId, �г�Id  
  ���:        MaDataStruct *singleMaInfo ,MA�ṹ��ָ��
  ����ֵ:      RETURN_ERROR:  ��ȡʧ��
               RETURN_SUCESS: ��ȡ�ɹ�
*************************************************/
UINT8_S GeSingleMaInfo(const UINT16_S trainId,MaDataStruct *singleMaInfo);

/*************************************************
  ������:      GetMaType
  ��������:    ��ȡ�ƶ���Ȩ����
  ����:        const UINT16_S trainId, �г�Id  
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE:  ��ȡʧ��
               >0u:                     ��ȡ�ɹ�
*************************************************/
UINT8_S GetMaType(const UINT16_S trianId);

/*************************************************
  ������:      SetMaType
  ��������:    �����ƶ���Ȩ����
  ����:        const UINT16_S trainId, �г�Id  
               const UINT8_S maType, MA����
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetMaType(const UINT16_S trianId,const UINT8_S maType);

/*************************************************
  ������:      GetMaHeadLink
  ��������:    ��ȡ�ƶ���Ȩ���LINK
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      RETURN_UINT16_MAX_VALUE:    ��ȡʧ��
               >0u:  ��ȡ�ɹ�
*************************************************/
UINT16_S GetMaHeadLink(const UINT16_S trianId);

/*************************************************
  ������:      SetMaHeadLink
  ��������:    �����ƶ���Ȩ���LINK
  ����:        const UINT16_S trainId, �г�Id
               const UINT16_S link, MA���link
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetMaHeadLink(const UINT16_S trianId, const UINT16_S link);

/*************************************************
  ������:      GetMaHeadOffset
  ��������:    ��ȡ�ƶ���Ȩ���offset
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      RETURN_UINT32_MAX_VALUE:  ��ȡʧ��
               >0u:                      ��ȡ�ɹ�
*************************************************/
UINT32_S GetMaHeadOffset(const UINT16_S trianId);

/*************************************************
  ������:      SetMaHeadOffset
  ��������:    �����ƶ���Ȩ���offset
  ����:        const UINT16_S trainId, �г�Id
               const UINT32_S offset,  MA���offset
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetMaHeadOffset(const UINT16_S trianId, const UINT32_S offset);

/*************************************************
  ������:      GetMaHeadDir
  ��������:    ��ȡ�ƶ���Ȩ��㷽��
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      DEFAULT_UINT8_VALUE:  ��ȡʧ��
               >0u:                  ��ȡ�ɹ�
*************************************************/
UINT8_S GetMaHeadDir(const UINT16_S trianId);

/*************************************************
  ������:      SetMaHeadDir
  ��������:    �����ƶ���Ȩ��㷽��
  ����:        const UINT16_S trainId, �г�Id
               const UINT8_S dir,      MA��㷽��
  ���:        ��
  ����ֵ:      RETURN_ERROR:       ����ʧ��
               RETURN_SUCCESS:     ���óɹ�
*************************************************/
UINT8_S SetMaHeadDir(const UINT16_S trianId, const UINT8_S dir);

/*************************************************
  ������:      GetMaTailLink
  ��������:    ��ȡ�ƶ���Ȩ�յ�LINK
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      0:    ��ȡʧ��
               >0u:  ��ȡ�ɹ�
*************************************************/
UINT16_S GetMaTailLink(const UINT16_S trianId);

/*************************************************
  ������:      SetMaTailLink
  ��������:    �����ƶ���Ȩ�յ�LINK
  ����:        const UINT16_S trainId, �г�Id
               const UINT16_S link, MA�յ�link
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetMaTailLink(const UINT16_S trianId, const UINT16_S link);

/*************************************************
  ������:      GetMaTailOffset
  ��������:    ��ȡ�ƶ���Ȩ�յ�offset
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      RETURN_UINT32_MAX_VALUE:  ��ȡʧ��
               [0u,RETURN_UINT32_MAX_VALUE): ��ȡ�ɹ�
*************************************************/
UINT32_S GetMaTailOffset(const UINT16_S trianId);

/*************************************************
  ������:      SetMaTailOffset
  ��������:    �����ƶ���Ȩ�յ�offset
  ����:        const UINT16_S trainId, �г�Id
               const UINT32_S offset,  MA�յ�offset
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetMaTailOffset(const UINT16_S trianId, const UINT32_S offset);

/*************************************************
  ������:      GetMaTailDir
  ��������:    ��ȡ�ƶ���Ȩ�յ㷽��
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      RETURN_ERROR:  ��ȡʧ��
               >0u:                  ��ȡ�ɹ�
*************************************************/
UINT8_S GetMaTailDir(const UINT16_S trianId);

/*************************************************
  ������:      SetMaTailDir
  ��������:    �����ƶ���Ȩ�յ㷽��
  ����:        const UINT16_S trainId, �г�Id
               const UINT8_S dir,      MA�յ㷽��
  ���:        ��
  ����ֵ:      RETURN_ERROR:       ����ʧ��
               RETURN_SUCCESS:     ���óɹ�
*************************************************/
UINT8_S SetMaTailDir(const UINT16_S trianId, const UINT8_S dir);

/*************************************************
  ������:      GetMaEndObsId
  ��������:    ��ȡ�ƶ���Ȩ�յ��ϰ���Id
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      RETURN_ERROR:  ��ȡʧ��
               >0u:                  ��ȡ�ɹ�
*************************************************/
UINT16_S GetMaEndObsId(const UINT16_S trianId);

/*************************************************
  ������:      SetMaEndObsId
  ��������:    �����ƶ���Ȩ�յ��ϰ���Id
  ����:        const UINT16_S trainId, �г�Id
               const UINT8_S endObstacleId, �յ��ϰ���Id
  ���:        ��
  ����ֵ:      RETURN_ERROR:         ����ʧ��
               RETURN_SUCCESS:       ��ȡ�ɹ�
*************************************************/
UINT8_S SetMaEndObsId(const UINT16_S trianId, const UINT8_S endObstacleId);

/*************************************************
  ������:      GetMaEndObsType
  ��������:    ��ȡ�ƶ���Ȩ�յ��ϰ�������
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      RETURN_ERROR:  ��ȡʧ��
               >0u:           ��ȡ�ɹ�
*************************************************/
UINT8_S GetMaEndObsType(const UINT16_S trianId);

/*************************************************
  ������:      SetMaEndObsType
  ��������:    �����ƶ���Ȩ�յ��ϰ�������
  ����:        const UINT16_S trainId, �г�Id
               const UINT8_S endObstacleType, �յ��ϰ�������
  ���:        ��
  ����ֵ:      RETURN_ERROR:         ����ʧ��
               RETURN_SUCCESS:       ��ȡ�ɹ�
*************************************************/
UINT8_S SetMaEndObsType(const UINT16_S trianId, const UINT8_S endObstacleType);

/*************************************************
  ������:      GetMaEndAttribute
  ��������:    ��ȡ�ƶ���Ȩ�յ�����
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      RETURN_ERROR:  ��ȡʧ��
               >0u:           ��ȡ�ɹ�
*************************************************/
UINT8_S GetMaEndAttribute(const UINT16_S trianId);

/*************************************************
  ������:      SetMaEndAttribute
  ��������:    �����ƶ���Ȩ�յ�����
  ����:        const UINT16_S trainId, �г�Id
               const UINT8_S endAttribute, �յ�����
  ���:        ��
  ����ֵ:      RETURN_ERROR:         ����ʧ��
               RETURN_SUCCESS:       ��ȡ�ɹ�
*************************************************/
UINT8_S SetMaEndAttribute(const UINT16_S trianId, const UINT8_S endAttribute);

/*************************************************
  ������:      GetMaObsNum
  ��������:    ��ȡ�ƶ���Ȩ��Ӧ�ϰ�������
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      RETURN_ERROR:  ��ȡʧ��
               >0u:           ��ȡ�ɹ�
*************************************************/
UINT8_S GetMaObsNum(const UINT16_S trianId);

/*************************************************
  ������:      SetMaObsNum
  ��������:    �����ƶ���Ȩ��Ӧ�ϰ�������
  ����:        const UINT16_S trainId, �г�Id
               const UINT8_S obsNum, �ϰ�������
  ���:        ��
  ����ֵ:      RETURN_ERROR:         ����ʧ��
               RETURN_SUCCESS:       ��ȡ�ɹ�
*************************************************/
UINT8_S SetMaObsNum(const UINT16_S trianId, const UINT8_S obsNum);

/*************************************************
  ������:      GetObsOfMAStru
  ��������:    ��ȡ�ƶ���Ȩ�ϰ�����Ϣ
  ����:        const UINT16_S trainId, �г�Id
               const UINT8_S bufSize,����ϰ���ṹ�����С(Ԥ��)
  ���:        ObsOfMAStruct obsOfMaStrBuff[],����ϰ���ṹ����
  ����ֵ:      RETURN_ERROR:     ��ȡʧ��
               RETURN_SUCCESS:   ��ȡ�ɹ�
*************************************************/
UINT8_S GetObsOfMAStru(const UINT16_S trianId,const UINT8_S bufSize,ObsOfMAStruct obsOfMaStrBuff[]);

/*************************************************
  ������:      SetObsOfMAStru
  ��������:    �����ƶ���Ȩ�ϰ�����Ϣ
  ����:        const UINT16_S trainId, �г�Id
               const ObsOfMAStruct obsOfMABuff[],�ϰ�����Ϣ����
               const UINT8_S obsNum,�ϰ�������
  ���:        ��
  ����ֵ:      RETURN_ERROR:     ����ʧ��
               RETURN_SUCCESS:   ���óɹ�
*************************************************/
UINT8_S SetObsOfMAStru(const UINT16_S trianId, const ObsOfMAStruct obsOfMABuff[],const UINT8_S obsNum);

/*************************************************
  ������:      GetMaTsrNum
  ��������:    ��ȡ�ƶ���Ȩ��ӦTsr����
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      RETURN_ERROR:     ��ȡʧ��
               >0u:   Tsr����
*************************************************/
UINT8_S GetMaTsrNum(const UINT16_S trianId);

/*************************************************
  ������:      SetMaTsrNum
  ��������:    �����ƶ���Ȩ��Ӧ��ʱ��������
  ����:        const UINT16_S trainId, �г�Id
               const UINT8_S tsrNum, ��ʱ��������
  ���:        ��
  ����ֵ:      RETURN_ERROR:     ����ʧ��
               RETURN_SUCCESS:   ���óɹ�
*************************************************/
UINT8_S SetMaTsrNum(const UINT16_S trianId, const UINT8_S tsrNum);

/*************************************************
  ������:      GetTsrOfMAStru
  ��������:    ��ȡ�ƶ���ȨTsr��Ϣ
  ����:        const UINT16_S trainId, �г�Id
               const UINT8_S bufSize,����ϰ���ṹ�����С(Ԥ��)
  ���:        TsrOfMAStruct tsrOfMaStrBuff[],�����ʱ���ٽṹ����
  ����ֵ:      RETURN_ERROR:     ��ȡʧ��
               RETURN_SUCCESS:   ��ȡ�ɹ�
*************************************************/
UINT8_S GetTsrOfMAStru(const UINT16_S trianId,const UINT8_S bufSize,TsrOfMAStruct tsrOfMaStrBuff[]);

/*************************************************
  ������:      SetTsrOfMAStru
  ��������:    �����ƶ���ȨTsr��Ϣ
  ����:        const UINT16_S trainId, �г�Id
               const TsrOfMAStruct tsrOfMAStru[],Tsr��Ϣ
               const UINT8_S tsrNum,Tsr����
  ���:        ��
  ����ֵ:      RETURN_ERROR:     ����ʧ��
               RETURN_SUCCESS:   ���óɹ�
*************************************************/
UINT8_S SetTsrOfMAStru(const UINT16_S trianId, const TsrOfMAStruct tsrOfMAStru[],const UINT8_S tsrNum);

/*
* ���������� �����г�ID����ȡ����ZC�г��ƶ���ȨԽ���ֽ���־
* ����˵���� const UINT16 trainId    
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
*			 FLAG_SET: Խ���ֽ��
*	         FLAG_UNSET:δԽ���ֽ��
*/
UINT8_S GetNextZcMaExceedBoundaryFlag(const UINT16_S trainId);

/*************************************************
  ������:      DeleteSingleTrainMaInfo
  ��������:    ɾ�������г��ƶ���Ȩ��Ϣ
  ����:        const UINT16_S trainId, �г�Id             
  ���:        ��
  ����ֵ:      ��
*************************************************/
void DeleteSingleTrainMaInfo(const UINT16_S trainId);

/*************************************************
  ������:      ClearSingleTrainMaInfo
  ��������:    ��������г��ƶ���Ȩ��Ϣ
  ����:        const UINT16_S trainId, �г�Id             
  ���:        ��
  ����ֵ:      ��
*************************************************/
void ClearSingleTrainMaInfo(const UINT16_S trainId);

#ifdef __cplusplus
}
#endif

#endif
