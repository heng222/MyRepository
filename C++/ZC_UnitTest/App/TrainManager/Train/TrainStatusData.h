/********************************************************                                                                                                            
 �� �� ���� TrainStatusData.h   
 ��    �ߣ� ZC��
 ����ʱ�䣺 2015-07-01
 ������ �г�״̬���ݹ���  
 ��ע�� ��  
********************************************************/
#ifndef TRAIN_STATUS_DATA_H_
#define TRAIN_STATUS_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "TrainDefine.h"
#include "../../SysDataManager/SysDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

/*�г�λ�����ݽṹ*/
typedef struct STrainSafeLocStruct
{
	UINT16_S  TrainHeadLink;                         /* �г���ͷ��ȫλ�����κţ�Link��*/
	UINT32_S  TrainHeadOffset;                       /* �г���ͷ��ȫλ��ƫ��λ�ã�Offset��*/
	UINT16_S  TrainTailLink;                         /* �г�β����ȫλ�����κţ�Link��*/
	UINT32_S  TrainTailOffset;                       /* �г�β����ȫλ��ƫ��λ�ã�Offset��*/
}TrainSafeLocStruct;

/*�г�״̬���ݽṹ��*/
typedef struct STrainInfoStruct
{
	UINT16_S  TrainID;                                       /*�г�ID*/
	UINT16_S  TrainControlZC;                                /*�г���ǰ�ܿ�ZCID*/
	UINT32_S  TrainCycle;                                    /*����ATP������Ϣʱ�ı���ʱ�䣨����ATP��ǰ���ںţ�*/
	UINT8_S   TrainType;                                     /*�г�����*/
	UINT8_S   SuspectHead;                                   /*ǰ�˿��ɱ�־*/
	UINT8_S   SuspectTail;                                   /*��˿��ɱ�־*/
	UINT16_S  TrainHeadAC;                                   /*�г���ȫ��ͷ���ڼ�������*/		
	UINT16_S  TrainTailAC;                                   /*�г���ȫ��β���ڼ�������*/
	UINT16_S  TrainUnsafeHeadAC;                             /*�г��ǰ�ȫ��ͷ���ڼ�������*/		
	UINT16_S  TrainUnsafeTailAC;                             /*�г��ǰ�ȫ��β���ڼ�������*/
	UINT16_S  TrainFrontSignal;                              /*�г�ǰ����Ҫ�������źŻ�*/
	UINT8_S   SignalProtection;                              /*�г������źŻ�������־*/
	UINT8_S   CommStatus;                                    /*��ʾ���г�ͨ����·��״̬*/
	UINT8_S   CommRedundancy;                                /*�г�ͨ�ż�ʱλ*/
	UINT8_S   PrtclDelay;                                    /*�г�ͨ��Э���ӳ�ʱ��*/
	UINT8_S   TrainStatus;                                   /*��ʾ�ڲ������г��ĸ���״̬*/
	UINT8_S   TrainInType;                                   /*����ATP�������Ϣ֡����*/
	UINT8_S   TrainOutType;                                  /*������ATP�������Ϣ֡����*/
	UINT8_S   HandoverInType;                                /*����ZC������Ϣ֡����*/
	UINT8_S   HandoverOutType;                               /*������ZC�����Ϣ֡����*/
	TrainSafeLocStruct  TrainSafeLocStru;                    /*�г���ȫλ�ýṹ��*/
	TrainSafeLocStruct  TrainUnSafeLocStru;                  /*�г��ǰ�ȫλ�ýṹ��*/
	UINT8_S  TrainUnsafeDirection;                           /*�г�ͷ���ǰ�ȫλ�ö�Ӧ���������з���:0x55-�߼�������;0xaa-�߼�������*/
	UINT8_S  TrainRealDirection;                             /*�г�ͷ���ǰ�ȫλ��ʵ�����з���:0x55-�߼�������;0xaa-�߼�������*/
	UINT8_S  TrainMode;                                      /*�г���ʻģʽ��Ϣ*/
	UINT8_S  TrainLevel;                                     /*�г����м���*/      
	UINT16_S TrainSpeed;                                     /*�г�ʵ���ٶ���Ϣ����λcm/s*/
	UINT8_S  TrainStopArea;                                  /*�г�ͣ������ͣ����Ϣ*/
	UINT8_S  TrainIntegrity;                                 /*�г������Ա�ʾ��*/
	UINT8_S  TrainEmergency;                                 /*�г�����ͣ����ʾ��Ϣ*/
	UINT16_S TrainError;                                     /*�г���ȷ�����*/
	UINT8_S MatchRouteNum;                                   /*�г�ƥ���·����*/
	UINT16_S MatchedRouteIDBuff[SIZE_MAX_ROUTENUM];          /*�г���ǰ���Ž�·ID*/
	UINT16_S ChangeLineId;                                   /*�л���·ID*/
	UINT8_S PreSectionNum;                                   /*������ռѹ�߼���������*/
	UINT16_S PreSectionIdBuff[SIZE_MAX_SECTION_OF_TRAIN];    /*������ռѹ�߼�����ID*/
}TrainInfoStruct;

/*************************************************
  ������:      GetTrainCurSum
  ��������:    ��ȡָ���г�ID������
  ����:        ��
  ���:        ��
  ����ֵ:      0U: ��ȡ����ʧ��
               <SIZE_MAX_CONTROLE_TRAIN: ���ҳɹ�
*************************************************/
UINT8_S GetTrainCurSum(void);

/*************************************************
  ������:      GetSingalTrainInfoOfIndex
  ��������:    ��ȡָ���г��г���Ϣ�׵�ַ
  ����:        const UINT16_S index, �����±�
  ���:        ��
  ����ֵ:      Null: ��ȡ����ʧ��
               >0: �����г���Ϣ�׵�ַ
*************************************************/
TrainInfoStruct* GetSingalTrainInfoOfIndex(const UINT16_S index);

/*
* ���������� ��ȡָ�������ŵ��г�ID
* ����˵���� const UINT8_S index, �г�ID���±�
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
*			<SIZE_MAX_LINE_TRAIN: ���ҳɹ�
*/
UINT16_S GetTrainIdOfIndex(const UINT8_S index);

/*************************************************
  ������:      GetTrainStatusBufIndex
  ��������:    ��ȡָ���г�ID������
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE: ��ȡ����ʧ��
               <SIZE_MAX_LINE_TRAIN: ���ҳɹ�
*************************************************/
UINT8_S GetTrainStatusBufIndex(const UINT16_S trainId);

/*************************************************
  ������:      GetSingleTrainInfo
  ��������:    ��ȡָ���г�ID�г���Ϣ
  ����:        const UINT16_S trainId, �г�ID
  ���:        TrainInfoStruct *pSingleTrainInfo, �г���Ϣ�ṹ��
  ����ֵ:      RETURN_ERROR:   ��ȡ����ʧ��
               RETURN_SUCCESS: ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetSingleTrainInfo(const UINT16_S trainId,TrainInfoStruct *pSingleTrainInfo);

/*************************************************
  ������:      SetSingleTrainNextZcInputDataInfo
  ��������:    ��������ZC�����ָ���г�ID�г���Ϣ
  ����:        const UINT16_S trainId, �г�ID
               const TrainInfoStruct *pSingleTrainInfo, �г���Ϣ�ṹ��
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��������ʧ��
               RETURN_SUCCESS: �������ݳɹ�
*************************************************/
UINT8_S SetSingleTrainNextZcInputDataInfo(const UINT16_S trainId,const TrainInfoStruct *pSingleTrainInfo);

/*************************************************
  ������:      SetSingleTrainInputDataInfo
  ��������:    �����г�������Ϣ��ָ���г�ID�г���Ϣ
  ����:        const UINT16_S trainId, �г�ID
               const TrainInfoStruct *pSingleTrainInfo, �г���Ϣ�ṹ��
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��������ʧ��
               RETURN_SUCCESS: �������ݳɹ�
*************************************************/
UINT8_S SetSingleTrainInputDataInfo(const UINT16_S trainId,const TrainInfoStruct *pSingleTrainInfo);

/*************************************************
  ������:      GetTrainControlZc
  ��������:    ��ȡָ���г��ܿ�ZC
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               <RETURN_UINT8_MAX_VALUE: ��ȡ���ݳɹ�
*************************************************/
UINT16_S GetTrainControlZc(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainControlZc
  ��������:    ����ָ���г��ܿ�ZC
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S zcId, ZC�ı��
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��������ʧ��
               RETURN_SUCCESS: �������ݳɹ�
*************************************************/
UINT8_S SetTrainControlZc(const UINT16_S trainId,const UINT16_S zcId);

/*************************************************
  ������:      GetTrainCycle
  ��������:    ��ȡָ���г����ں�
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ȡ����ʧ��
               >0:             ��ȡ���ݳɹ�
*************************************************/
UINT32_S GetTrainCycle(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainCycle
  ��������:    ����ָ���г����ں�
  ����:        const UINT16_S trainId, �г�ID
               const UINT32_S trainCycle�� �г����ں�
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetTrainCycle(const UINT16_S trainId,const UINT32_S trainCycle);

/*************************************************
  ������:      GetTrainType
  ��������:    ��ȡָ���г�����
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ȡʧ��
               >0:             ��ȡ�ɹ�
*************************************************/
UINT8_S GetTrainType(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainType
  ��������:    ����ָ���г�����
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainType, �г�����
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetTrainType(const UINT16_S trainId,const UINT8_S trainType);

/*************************************************
  ������:      GetTrainSuspectHead
  ��������:    ��ȡָ���г�ǰ�˿��ɱ�־
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ȡʧ��
               >0:             ��ȡ�ɹ�
*************************************************/
UINT8_S GetTrainSuspectHead(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainSuspectHead
  ��������:    ����ָ���г�ǰ�˿��ɱ�־
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S suspectHead, �г�ǰ�˿��ɱ�־
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetTrainSuspectHead(const UINT16_S trainId,const UINT8_S suspectHead);

/*************************************************
  ������:      GetTrainSuspectTail
  ��������:    ��ȡָ���г���˿��ɱ�־
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ȡʧ��
               >0:             ��ȡ�ɹ�
*************************************************/
UINT8_S GetTrainSuspectTail(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainSuspectTail
  ��������:    ����ָ���г���˿��ɱ�־
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S suspectTail, �г���˿��ɱ�־
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetTrainSuspectTail(const UINT16_S trainId,const UINT8_S suspectTail);

/*************************************************
  ������:      GetTrainTrainHeadAC
  ��������:    ��ȡָ���г���ͷ���ڼ�������
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ȡ����ʧ��
               >0:             ���óɹ�
*************************************************/
UINT16_S GetTrainTrainHeadAC(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainTrainHeadAC
  ��������:    ����ָ���г���ͷ���ڼ�������
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S trainHeadAC, ��ͷ���ڵļ�������
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetTrainTrainHeadAC(const UINT16_S trainId,const UINT16_S trainHeadAC);

/*************************************************
  ������:      GetTrainTrainTailAC
  ��������:    ��ȡָ���г���β���ڼ�������
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ȡʧ��
               >0:             ��ȡ�ɹ�
*************************************************/
UINT16_S GetTrainTrainTailAC(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainTrainTailAC
  ��������:    ����ָ���г���β���ڼ�������
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S trainTailAC, �г���β���ڼ���
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetTrainTrainTailAC(const UINT16_S trainId,const UINT16_S trainTailAC);

/*************************************************
  ������:      GetTrainUnsafeTrainHeadAC
  ��������:    ��ȡָ���г��ǰ�ȫ��ͷ���ڼ�������
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ȡʧ��
               >0:             ��ȡ�ɹ�
*************************************************/
UINT16_S GetTrainUnsafeTrainHeadAC(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainUnsafeTrainHeadAC
  ��������:    ����ָ���г��ǰ�ȫ��ͷ���ڼ�������
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S trainUnsafeHeadAC, �г��ǰ�ȫ��ͷ���ڼ�������
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetTrainUnsafeTrainHeadAC(const UINT16_S trainId,const UINT16_S trainUnsafeHeadAC);

/*************************************************
  ������:      GetTrainUnsafeTrainTailAC
  ��������:    ��ȡָ���г��ǰ�ȫ��β���ڼ�������
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ȡʧ��
               RETURN_SUCCESS: ��ȡ�ɹ�
*************************************************/
UINT16_S GetTrainUnsafeTrainTailAC(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainUnsafeTrainTailAC
  ��������:    ��ȡָ���г��ǰ�ȫ��β���ڼ�������
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S trainUnsafeTailAC, �г��ǰ�ȫ��β���ڼ�������
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetTrainUnsafeTrainTailAC(const UINT16_S trainId,const UINT16_S trainUnsafeTailAC);

/*************************************************
  ������:      GetTrainFrontSignal
  ��������:    ��ȡָ���г�ǰ����Ҫ�����źŻ�
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ȡʧ��
               >0:             ��ȡ�ɹ�
*************************************************/
UINT16_S GetTrainFrontSignal(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainFrontSignal
  ��������:    ����ָ���г�ǰ����Ҫ�����źŻ�
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S trainFrontSignal, �г�ǰ���źŻ�
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetTrainFrontSignal(const UINT16_S trainId,const UINT16_S trainFrontSignal);

/*************************************************
  ������:      GetTrainSignalProtection
  ��������:    ��ȡָ���г����źű�־
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ȡʧ��
               >0:             ��ȡ�ɹ�
*************************************************/
UINT8_S GetTrainSignalProtection(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainSignalProtection
  ��������:    ����ָ���г����źű�־
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S signalProtection, �г����źŻ�������־
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainSignalProtection(const UINT16_S trainId,const UINT8_S signalProtection);

/*************************************************
  ������:      GetTrainCommStatus
  ��������:    ��ȡָ���г�ͨ����·״̬
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ��ȡʧ��
               >0:              ��ȡ�ɹ�
*************************************************/
UINT8_S GetTrainCommStatus(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainCommStatus
  ��������:    ����ָ���г�ͨ����·״̬
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S commStatus, �г�ͨ����·״̬
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainCommStatus(const UINT16_S trainId,const UINT8_S commStatus);

/*************************************************
  ������:      GetTrainCommRedundancy
  ��������:    ��ȡָ���г�ͨ�ż�ʱλ
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ��ȡʧ��
               >0:              ��ȡ�ɹ�
*************************************************/
UINT8_S GetTrainCommRedundancy(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainCommRedundancy
  ��������:    ����ָ���г�ͨ�ż�ʱλ
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S commRedundancy, �г�ͨ�ż�ʱλ
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainCommRedundancy(const UINT16_S trainId,const UINT8_S commRedundancy);

/*************************************************
  ������:      GetTrainPrtclDelay
  ��������:    ��ȡָ���г�ͨ��Э���ӳ�ʱ��
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ��ȡʧ��
               >0:              ��ȡ�ɹ�
*************************************************/
UINT8_S GetTrainPrtclDelay(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainPrtclDelay
  ��������:    ����ָ���г�ͨ��Э���ӳ�ʱ��
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S prtclDelay, �г�ͨ��Э���ӳ�ʱ��
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainPrtclDelay(const UINT16_S trainId,const UINT8_S prtclDelay);

/*************************************************
  ������:      GetTrainStatus
  ��������:    ��ȡָ���г�״̬
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainStatus(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainPrtclDelay
  ��������:    ����ָ���г�״̬
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainStatus, �г��г�״̬
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainStatus(const UINT16_S trainId,const UINT8_S trainStatus);

/*************************************************
  ������:      GetTrainInType
  ��������:    ��ȡָ���г���������
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainInType(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainInType
  ��������:    ����ָ���г���������
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainInType, �г���������
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainInType(const UINT16_S trainId,const UINT8_S trainInType);

/*************************************************
  ������:      GetTrainOutType
  ��������:    ��ȡָ���г��������
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainOutType(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainOutType
  ��������:    ����ָ���г��������
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainOutType, �г��������
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainOutType(const UINT16_S trainId,const UINT8_S trainOutType);

/*************************************************
  ������:      GetTrainHandoverInType
  ��������:    ��ȡָ������ZC��������
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainHandoverInType(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainHandoverInType
  ��������:    ����ָ���г�����ZC��������
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S handoverInType, �г�����ZC��������
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainHandoverInType(const UINT16_S trainId,const UINT8_S handoverInType);

/*************************************************
  ������:      GetTrainHandoverOutType
  ��������:    ��ȡָ������ZC�������
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainHandoverOutType(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainHandoverOutType
  ��������:    ����ָ���г�����ZC�������
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S handoverOutType, �г�����ZC�������
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainHandoverOutType(const UINT16_S trainId,const UINT8_S handoverOutType);

/*************************************************
  ������:      GetTrainUnsafeDirection
  ��������:    ��ȡָ���г��������з���
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainUnsafeDirection(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainUnsafeDirection
  ��������:    ����ָ���г��������з���
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainUnsafeDirection, �г��������з���
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainUnsafeDirection(const UINT16_S trainId,const UINT8_S trainUnsafeDirection);

/*************************************************
  ������:      GetTrainRealDirection
  ��������:    ��ȡָ���г�ʵ�����з���
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainRealDirection(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainRealDirection
  ��������:    ����ָ���г�ʵ�����з���
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainRealDirection, �г�ʵ�����з���
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainRealDirection(const UINT16_S trainId,const UINT8_S trainRealDirection);

/*************************************************
  ������:      GetTrainMode
  ��������:    ��ȡָ���г�ģʽ
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainMode(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainMode
  ��������:    ����ָ���г�ģʽ
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainMode, �г��г�ģʽ
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainMode(const UINT16_S trainId,const UINT8_S trainMode);

/*************************************************
  ������:      GetTrainLevel
  ��������:    ��ȡָ���г�����
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainLevel(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainMode
  ��������:    ����ָ���г�����
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainLevel, �г��г�����
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainLevel(const UINT16_S trainId,const UINT8_S trainLevel);

/*************************************************
  ������:      GetTrainSpeed
  ��������:    ��ȡָ���г��ٶ�
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT16_S GetTrainSpeed(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainSpeed
  ��������:    ����ָ���г��ٶ�
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S trainSpeed, �г��ٶ�
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainSpeed(const UINT16_S trainId,const UINT16_S trainSpeed);

/*************************************************
  ������:      GetTrainStopArea
  ��������:    ��ȡָ���г�ͣ�ȱ�־
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainStopArea(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainStopArea
  ��������:    ����ָ���г�ͣ�ȱ�־
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainStopArea, �г�ͣ�ȱ�־
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainStopArea(const UINT16_S trainId,const UINT8_S trainStopArea);

/*************************************************
  ������:      GetTrainEmergency
  ��������:    ��ȡָ���г������Ա�־
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainIntegrity(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainIntegrity
  ��������:    ����ָ���г������Ա�־
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainIntegrity, �г������Ա�־
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainIntegrity(const UINT16_S trainId,const UINT8_S trainIntegrity);

/*************************************************
  ������:      GetTrainEmergency
  ��������:    ��ȡָ���г�����ͣ����־
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainEmergency(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainEmergency
  ��������:    ����ָ���г�����ͣ����־
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainEmergency, �г�����ͣ����־
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainEmergency(const UINT16_S trainId,const UINT8_S trainEmergency);

/*************************************************
  ������:      GetMatchRouteNum
  ��������:    ��ȡָ���г���ƥ���·����
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      >=0,����
*************************************************/
UINT8_S GetMatchRouteNum(const UINT16_S trainId);

/*************************************************
  ������:      GetTrainMatchedRouteIdBuff
  ��������:    ��ȡָ���г���ƥ���·��Ϣ
  ����:        const UINT16_S trainId, �г�ID
  ���:        UINT16_S routeIdBuff[], ƥ��Ľ�·�ı��
  ����ֵ:      RETURN_ERROR:    ��ȡ����ʧ��
               RETURN_SUCCESS:  ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainMatchedRouteIdBuff(const UINT16_S trainId,UINT16_S routeIdBuff[]);

/*************************************************
  ������:      GetTrainMatchedLastRouteId
  ��������:    ��ȡָ���г���ƥ������һ����·��Ϣ
  ����:        const UINT16_S trainId, �г�ID
  ���:        UINT16_S *pLastRouteId, ���һ����·Id
  ����ֵ:      RETURN_ERROR:    ��ȡ����ʧ��
               RETURN_SUCCESS:  ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainMatchedLastRouteId(const UINT16_S trainId,UINT16_S *pLastRouteId);

/*************************************************
  ������:      SetTrainMatchedRouteIdBuf
  ��������:    ����ָ���г���ƥ���·��Ϣ
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S routeIdBuff[] ��·ID����
               const UINT8_S routeNum ��·����
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainMatchedRouteIdBuf(const UINT16_S trainId,const UINT16_S routeIdBuff[],const UINT8_S routeNum);

/*************************************************
  ������:      GetTrainSafeLoc
  ��������:    ��ȡָ���г��л���·ID
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ��ȡ����ʧ��
               >0:              ��ȡ���ݳɹ�
*************************************************/
UINT16_S GetTrainChangeLineId(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainChangeLineId
  ��������:    ����ָ���г��л���·ID
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S changeLineId, �г��л���·ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainChangeLineId(const UINT16_S trainId,const UINT16_S changeLineId);

/*************************************************
  ������:      GetTrainSafeLoc
  ��������:    ��ȡָ���г���ȫλ����Ϣ
  ����:        const UINT16_S trainId, �г�ID
  ���:        TrainSafeLocStruct *pTrainSafeLocStru, �г�λ����Ϣ�ṹ��
  ����ֵ:      RETURN_ERROR:    ��ȡ����ʧ��
               RETURN_SUCCESS:  ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainSafeLoc(const UINT16_S trainId,TrainSafeLocStruct *pTrainSafeLocStru);

/*************************************************
  ������:      SetTrainSafeLoc
  ��������:    ����ָ���г���ȫλ����Ϣ
  ����:        const UINT16_S trainId, �г�ID
               TrainSafeLocStruct *pTrainSafeLocStru, �г�λ�ýṹ��
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainSafeLoc(const UINT16_S trainId,const TrainSafeLocStruct *pTrainSafeLocStru);

/*************************************************
  ������:      SetTrainSafeHeadLoc
  ��������:    ����ָ���г���ȫ��ͷλ����Ϣ
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S trainSafeHeadLink, ��ȫ��ͷlink
               const UINT32_S trainSafeHeadOffset, ��ȫ��ͷoffset
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainSafeHeadLoc(const UINT16_S trainId,const UINT16_S trainSafeHeadLink,const UINT32_S trainSafeHeadOffset);

/*************************************************
  ������:      SetTrainSafeTailLoc
  ��������:    ����ָ���г���ȫ��βλ����Ϣ
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S trainSafeTailLink, ��ȫ��βlink
               const UINT32_S trainSafeTailOffset, ��ȫ��βoffset
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainSafeTailLoc(const UINT16_S trainId,const UINT16_S trainSafeTailLink,const UINT32_S trainSafeTailOffset);

/*************************************************
  ������:      GetTrainUnSafeLoc
  ��������:    ��ȡָ���г��ǰ�ȫλ����Ϣ
  ����:        const UINT16_S trainId, �г�ID
  ���:        TrainSafeLocStruct *pTrainUnSafeLocStru, �г�λ����Ϣ�ṹ��
  ����ֵ:      RETURN_ERROR:    ��ȡ����ʧ��
               RETURN_SUCCESS:  ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainUnSafeLoc(const UINT16_S trainId,TrainSafeLocStruct *pTrainUnSafeLocStru);

/*************************************************
  ������:      SetTrainUnSafeLoc
  ��������:    ����ָ���г��ǰ�ȫλ����Ϣ
  ����:        const UINT16_S trainId, �г�ID
               const TrainSafeLocStruct trainUnSafeLocStru, λ����Ϣ�ṹ��
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainUnSafeLoc(const UINT16_S trainId,const TrainSafeLocStruct trainUnSafeLocStru);

/*************************************************
  ������:      GetTrainError
  ��������:    ��ȡָ���г�ID��ȷ�����
  ����:        const UINT16_S trainId, �г�ID
  ���:        UINT16_S sectionIdBuff[], �߼�����ID����
  ����ֵ:      TRAIN_ERROR_MAX_NUM:      ��ȡ����ʧ��
               >0:    ��ȡ���ݳɹ�
*************************************************/
UINT16_S GetTrainError(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainError
  ��������:    ����ָ���г�ID��ȷ�����
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S trainError, ��ȷ�����
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainError(const UINT16_S trainId, const UINT16_S trainError);

/*************************************************
  ������:      AllotTrainIndex
  ��������:    ����ȷ���г�����Ļ����±�
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      SIZE_MAX_CONTROLE_TRAIN: �����±�ʧ��
               (0,SIZE_MAX_CONTROLE_TRAIN): �����±�ɹ�
*************************************************/
UINT8_S AllotTrainIndex(const UINT16_S trainId);

/*************************************************
  ������:      GetTrainPreSectionId
  ��������:    ��ȡָ���г��������߼�����ID
  ����:        const UINT16_S trainId, �г�ID
  ���:        UINT16_S sectionIdBuff[], �߼�����ID����
  ����ֵ:      RETURN_ERROR:      ��ȡ����ʧ��
               RETURN_SUCCESS:    ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainPreSectionId(const UINT16_S trainId,UINT16_S sectionIdBuff[]);

/*************************************************
  ������:      GetTrainPreSectionNum
  ��������:    ��ȡָ���г��������߼���������
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE:      ��ȡ����ʧ��
               [0,RETURN_UINT8_MAX_VALUE):  ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainPreSectionNum(const UINT16_S trainId);

/*************************************************
  ������:      SetTrainPreSectionId
  ��������:    ����ָ���г��������߼�������Ϣ
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S sectionIdBuff[], �߼�����ID����
               const UINT8_S sectionNum, �߼����ε�����
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainPreSectionId(const UINT16_S trainId,const UINT16_S sectionIdBuff[],const UINT8_S sectionNum);

/*************************************************
  ������:      DeleteSingleTrainInfo
  ��������:    ɾ�������г���Ϣ
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      ��
*************************************************/
void DeleteSingleTrainInfo(const UINT16_S trainId);

#ifdef __cplusplus
}
#endif

#endif
