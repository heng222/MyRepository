/********************************************************                                                                                                            
 �� �� ���� TrainStatusData.h   
 ��    �ߣ� ZC��
 ����ʱ�䣺 2015-07-05
 ������ �г��߼����� 
 ��ע�� ��  
********************************************************/
#ifndef TRAIN_LOGIC_MANAGER_H_
#define TRAIN_LOGIC_MANAGER_H_

#include "../../../Common/CommonTypes.h"
#include "TrainDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************
  ������:      SetTrainToModeToRM0
  ��������:    �г���������
  ����:        const UINT16_S trainId �г�ID
  ���:        ��
  ����ֵ:      ��
*************************************************/
void SetTrainToModeToRM0(const UINT16_S trainId);

/*************************************************
  ������:      TrainDirChangeForCheck
  ��������:    ת���г��������ڷ����ѯ
  ����:        const UINT16_S trainId �г�ID
  ���:        ��
  ����ֵ:      ת��ֵ 
*************************************************/
UINT8_S TrainDirChangeForCheck(const UINT16_S trainId);

/*************************************************
  ������:      JudgeTrainNeedCalculate
  ��������:    �ж��г��Ƿ���Ҫ������Ӧ�ļ���
  ����:        const UINT16_S trainId �г�ID
  ���:        ��
  ����ֵ:      1U:��Ҫ
               0U:����Ҫ
*************************************************/
UINT8_S JudgeTrainNeedCalculate(const UINT16_S trainId);

/*************************************************
  ������:      CalculateTrainSafePos
  ��������:    �����г���ȫλ��
  ����:        ��
  ���:        ��
  ����ֵ:      ��
*************************************************/
void CalculateTrainSafePos(void);

/*************************************************
  ������:      CalculateTrainHeadSafePos
  ��������:    �����г���ȫ��ͷλ��
  ����:        const UINT16_S trainId,�г�ID
  ���:        ��
  ����ֵ:      ��
*************************************************/
void CalculateTrainHeadSafePos(const UINT16_S trainId);

/*************************************************
  ������:      CalculateTrainTailSafePos
  ��������:    �����г���ȫ��βλ��
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      ��
*************************************************/
void CalculateTrainTailSafePos(const UINT16_S trainId);

/*************************************************
  ������:      CalculateTrainHeadDistance
  ��������:    �����г���ȫ��ͷλ����Ҫ�ľ���
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      ����ֵ
*************************************************/
UINT32_S CalculateTrainHeadDistance(const UINT16_S trainId);

/*************************************************
  ������:      CalculateTrainTailDistance
  ��������:    �����г���ȫ��βλ����Ҫ�ľ���
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      ����ֵ
*************************************************/
UINT32_S CalculateTrainTailDistance(const UINT16_S trainId);

/*************************************************
  ������:      JudgeSwitchBelongAcOccStatus
  ��������:    �����г���ȫ��βλ����Ҫ�ľ���
  ����:        cosnt UINT16_S swtichId ����ID
  ���:        ��
  ����ֵ:      0u:ռ��
               1u:δռ��
*************************************************/
UINT8_S JudgeSwitchBelongAcOccStatus(const UINT16_S swtichId);

/*************************************************
  ������:      CalculateTrainSafeLocAcOfSwitch
  ��������:    �����г���ȫλ�û�����Ҫ�ľ���ļ����ڵ�����߾�ͷ�����
  ����:        const UINT8_S flag,��־��Ϣ(1u:��ͷ��2u:��β)
               const UINT32_S distance,����ֵ
               const UINT8_S dir,����
  ���:        UINT16_S errorSwitchOrAcId[SIZE_MAX_SWITCH_MUM_OF_SAFE_TRAIN],���������˹�ϵ������
               UINT8_S * pSwitchOrAcNum,���������˹�ϵ���������
               UINT16_S *endAcOfLine,��ͷ�߼������α��
  ����ֵ:      0x03u��λ�ü���ɹ�
               0x02u��λ�ü���ʧ�ܣ�ԭ�����λ�ô���,errorSwitchOrAcIdΪ���������˹�ϵ������;pSwitchOrAcNumΪ���������˹�ϵ�����������
               0x01u��λ�ü���ʧ�ܣ�ԭ����·��ͷ,endAcOfLine,��ͷ�߼������α�ţ�
               0x00u��λ�ü���ʧ�ܣ�����ԭ��
*************************************************/
UINT8_S CalculateTrainSafeLocAcOfSwitch(const UINT8_S flag,const UINT16_S trainId,const UINT32_S distance,const UINT8_S dir,UINT16_S errorSwitchOrAcId[SIZE_MAX_SWITCH_MUM_OF_SAFE_TRAIN],UINT8_S * pSwitchOrAcNum,UINT16_S *endAcOfLine);

/*************************************************
  ������:      ManageTrainDangerousSource
  ��������:    �����г�ǰ���ͺ�Σ��Դ��Ϣ
  ����:        ��
  ���:        ��
  ����ֵ:      ��
*************************************************/
void ManageTrainDangerousSource(void);

/*************************************************
  ������:      ManageAddTrainHeadSuspect
  ��������:    �����г�ǰ��Σ��Դ��Ϣ���Ƿ�����Σ��Դ�����ǰ��Σ�������ǣ�
  ����:        const UINT16_S trainId �г�ID
  ���:        ��
  ����ֵ:      ��
*************************************************/
void ManageAddTrainHeadSuspect(const UINT16_S trainId);

/*************************************************
  ������:      ManageAddTrainTailSuspect
  ��������:    �����г���Σ��Դ��Ϣ���Ƿ�����Σ��Դ����Ӻ�Σ�������ǣ�
  ����:        const UINT16_S trainId �г�ID
  ���:        ��
  ����ֵ:      ��
*************************************************/
void ManageAddTrainTailSuspect(const UINT16_S trainId);

/*************************************************
  ������:      JudgeTrainHeadSuspect
  ��������:    �ж��Ƿ����ȥ���г�ǰ��Σ��Դ��Ϣ
  ����:        const UINT16_S trainId �г�ID
  ���:        ��
  ����ֵ:      1u������ɹ���ǰ����Σ��Դ��
               0u������ʧ�ܣ�ǰ������Σ��Դ��
*************************************************/
UINT8_S JudgeTrainHeadSuspect(const UINT16_S trainId);

/*************************************************
  ������:      JudgeTrainTailSuspect
  ��������:    �ж��Ƿ����ȥ���г���Σ��Դ��Ϣ
  ����:        const UINT16_S trainId �г�ID
  ���:        ��
  ����ֵ:      1u������ɹ�������Σ��Դ��
               0u������ʧ�ܣ��󷽴���Σ��Դ��
*************************************************/
UINT8_S JudgeTrainTailSuspect(const UINT16_S trainId);

/*************************************************
  ������:      CalulateTrainLocToAcInfo
  ��������:    �����г�ռѹ�İ�ȫ�ͷǰ�ȫ��������
  ����:        ��
  ���:        ��
  ����ֵ:      ��
*************************************************/
void CalulateTrainLocToAcInfo(void);

/*************************************************
  ������:      CalculateCommTrainMatchingRoute
  ��������:    ����ͨ���г��Ƿ���ƥ���Ͽ��õĽ�·��Ϣ
  ����:        ��
  ���:        ��
  ����ֵ:      ��
*************************************************/
void CalculateCommTrainMatchingRoute(void);

/*************************************************
  ������:      CalculateCommTrainMatchingRoute
  ��������:    ����ͨ���г��Ƿ���ƥ���Ͽ��õĽ�·��Ϣ
  ����:        const UINT16_S trainId,��ƥ���г�ID
  ���:        UINT8_S matchRouteIndex,ƥ���·���±�
               UINT16_S mathRouteIdBuff[],ƥ���·��ID����
  ����ֵ:      0u:ƥ��ʧ��
               1u:ƥ��ɹ�
*************************************************/
UINT8_S MatchTrainSingleRoute(const UINT16_S trainId,UINT8_S matchRouteIndex,UINT16_S matchRouteIdBuff[]);

/*************************************************
  ������:      MatchTrainHeadFrontAcInRoute
  ��������:    ����ͨ���г��Ƿ���ƥ���Ͽ��õĽ�·��Ϣ
  ����:        const UINT16_S trainHeadAcId,�г���ͷ��������ID
               const UINT16_S trainId,��ƥ���г�Id
  ���:        UINT16_S *pMatchRouteId,ƥ���·��Ϣ
  ����ֵ:      0u:ƥ��ʧ��
               1u:ƥ��ɹ�
*************************************************/
UINT8_S MatchTrainHeadFrontAcInRoute(const UINT16_S trainHeadAcId,const UINT16_S trainId,UINT16_S *pMatchRouteId);

/*************************************************
  ������:      CalculateSignalLocBetweenTrainLoc
  ��������:    �����źŻ���λ���Ƿ�λ���г���ͷ��β֮��
  ����:        const UINT16_S trainId,�г�ID
               const UINT16_S signalId,�źŻ�ID
  ���:        ��
  ����ֵ:      0u:�Ƚ�ʧ��
               1u:λ���г���ͷ��βλ��֮��
               2u:��λ���г���ͷ��βλ��֮��
*************************************************/
UINT8_S CalculateSignalLocBetweenTrainLoc(const UINT16_S trainId,const UINT16_S signalId);

/*************************************************
  ������:      CalulateAcIdBelongUseableRoute
  ��������:    ����ͨ���г��Ƿ���ƥ���Ͽ��õĽ�·��Ϣ
  ����:        const UINT16_S acId,��������ID
               const UINT8_S dir,ƥ���·����
  ���:        UINT16_S *pMathRouteId,�����ƥ���· 
  ����ֵ:      0u:���᲻���ڰ����·
               1u:�������ڰ����·����·���ɱ�ƥ��
               2u:�������ڰ����·�ҽ�·�ɱ�ƥ��
*************************************************/
UINT8_S CalulateAcIdBelongUseableRoute(const UINT16_S acId,const UINT8_S dir,UINT16_S *pMathRouteId);

/*************************************************
  ������:      CalulateRouteMathToTrain
  ��������:    ����ָ���г�ID�Ƿ���ƥ��ָ����·
  ����:        const UINT16_S routeId,��·ID
               const UINT16_S trainId,�г�ID
  ���:        ��
  ����ֵ:      0u:ƥ��ʧ��
               1u:ƥ��ɹ�
*************************************************/
UINT8_S CalulateRouteMathToTrain(const UINT16_S routeId,const UINT16_S trainId);

/*************************************************
  ������:      CalculateBeCloseRouteMatch
  ��������:    ����ָ���г�ID�Ƿ��ܰ���·�ӽ�ƥ��ԭ��ƥ��ָ����·
  ����:        const UINT16_S routeId,��·ID
  ���:        UINT16_S *pMathRouteId,����ƥ��Ľ�·ID
  ����ֵ:      0u:ƥ��ʧ��
               1u:ƥ��ɹ�
*************************************************/
UINT8_S CalculateBeCloseRouteMatch(const UINT16_S trainId,UINT16_S *pMatchRouteId);

/*************************************************
  ������:      CalculateRouteAcLockStatusIntegrality
  ��������:    ����ָ����·�ڼ������ε�����������
  ����:        const UINT16_S routeId,��·ID
  ���:        ��
  ����ֵ:      0u:δ��������
               1u:��������
*************************************************/
UINT8_S CalculateRouteAcLockStatusIntegrality(const UINT16_S routeId);

/*************************************************
  ������:      ManageTrainTypeTransform
  ��������:    �����г�����ת��
  ����:        ��
  ���:        ��
  ����ֵ:      ��
*************************************************/
void ManageTrainTypeTransform(void);

/*************************************************
  ������:      ManageTrainStatusTransform
  ��������:    �����г�״̬ת����Ϣ
  ����:        ��
  ���:        ��
  ����ֵ:      ��
*************************************************/
void ManageTrainStatusTransform(void);

/*************************************************
  ������:      ManageOutTrainType
  ��������:    �����г����״̬��Ϣ
  ����:        ��
  ���:        ��
  ����ֵ:      ��
*************************************************/
void ManageOutTrainType(void);

/*************************************************
  ������:      ManageNZcOutTrainType
  ��������:    �����г�����ZC���״̬��Ϣ
  ����:        ��
  ���:        ��
  ����ֵ:      ��
*************************************************/
void ManageNZcOutTrainType(void);

/*************************************************
  ������:      JudegeNZcDefaultStatusTransform
  ��������:    ��������ZC����״̬Ϊ��״̬���߿�ѹ�л�����µ�����ZC���ת��
  ����:        const UINT16_S trainId,�г�Id
  ���:        ��
  ����ֵ:      ��
*************************************************/
void JudegeNZcDefaultStatusTransform(const UINT16_S trainId);

/*************************************************
  ������:      JudegeNZcHandStatusTransform
  ��������:    ��������ZC����״̬Ϊ�ƽ�����״̬���µ�����ZC���ת��
  ����:        const UINT16_S trainId,�г�Id
  ���:        ��
  ����ֵ:      ��
*************************************************/
void JudegeNZcHandStatusTransform(const UINT16_S trainId);

/*************************************************
  ������:      JudgeNZcConfirmationStatusTransform
  ��������:    ��������ZC����״̬Ϊ�ƽ�����ȷ��״̬���µ�����ZC���ת��
  ����:        const UINT16_S trainId,�г�Id
  ���:        ��
  ����ֵ:      ��
*************************************************/
void JudgeNZcConfirmationStatusTransform(const UINT16_S trainId);

/*************************************************
  ������:      JudgeNZcManagenohandStatusTransform
  ��������:    ��������ZC����״̬Ϊ�ƽ�δ�л�״̬���µ�����ZC���ת��
  ����:        const UINT16_S trainId,�г�Id
  ���:        ��
  ����ֵ:      ��
*************************************************/
void JudgeNZcManagenohandStatusTransform(const UINT16_S trainId);

/*************************************************
  ������:      JudgeTrainDefaultStatusTransform
  ��������:    ����Ĭ��״̬��ת��
  ����:        const UINT16_S trainId,�г�Id
  ���:        ��
  ����ֵ:      ��
*************************************************/
void JudgeTrainDefaultStatusTransform(const UINT16_S trainId);

/*************************************************
  ������:      JudgeTrainStateMovingTransform
  ��������:    ����STATE_MOVING״̬�г�״̬��ת��
  ����:        const UINT16_S trainId,�г�Id
  ���:        ��
  ����ֵ:      ��
*************************************************/
void JudgeTrainStateMovingTransform(const UINT16_S trainId);

/*************************************************
  ������:      JudgeTrainHandOverTransform
  ��������:    ����STATE_HANDOVER״̬�г�״̬��ת��
  ����:        const UINT16_S trainId,�г�Id
  ���:        ��
  ����ֵ:      ��
*************************************************/
void JudgeTrainHandOverTransform(const UINT16_S trainId);

/*************************************************
  ������:      JudgeTrainTakeOverTransform
  ��������:    ����STATE_TAKEOVER״̬�г�״̬��ת��
  ����:        const UINT16_S trainId,�г�Id
  ���:        ��
  ����ֵ:      ��
*************************************************/
void JudgeTrainTakeOverTransform(const UINT16_S trainId);

/*************************************************
  ������:      JudgeTrainReverseTransform
  ��������:    ����STATE_REVERSE״̬�г�״̬��ת��
  ����:        const UINT16_S trainId,�г�Id
  ���:        ��
  ����ֵ:      ��
*************************************************/
void JudgeTrainReverseTransform(const UINT16_S trainId);

/*************************************************
  ������:      CheckTrainLocSwitchLockState
  ��������:    ��鳵��Χ�ڵĵ�������״̬
  ����:        const UINT16_S trainId,�г�Id
  ���:        ��
  ����ֵ:      0u�������쳣
               1u����������
*************************************************/
UINT8_S CheckTrainLocSwitchLockState(const UINT16_S trainId);

/*************************************************
  ������:      JudgeTrainLocalInChangeLine
  ��������:    ����г��Ƿ�λ�ڱ�ZC�л���·���ƽ�ZC��Χ��
  ����:        const UINT16_S trainId,�г�Id
  ���:        UINT16_S *pOutChangeLineId,������л���·ID
  ����ֵ:      0u��������
               1u������
*************************************************/
UINT8_S JudgeTrainLocalInChangeLine(const UINT16_S trainId,UINT16_S *pOutChangeLineId);

/*************************************************
  ������:      JudgeTrainInfoOfCiCommFailure
  ��������:    ��������CIͨ�Ź��ϵ��µ��г���Ϣ�仯
  ����:        const UINT16_S ciId,����ID
  ���:        ��
  ����ֵ:      ��
*************************************************/
void JudgeTrainInfoOfCiCommFailure(const UINT16_S ciId);

/*************************************************
  ������:      JudgeTrainInfoOfNZcCommFailure
  ��������:    ������������Zcͨ�Ź��ϵ��µ��г���Ϣ�仯
  ����:        const UINT16_S nZcId,����ZcId
  ���:        ��
  ����ֵ:      ��
*************************************************/
void JudgeTrainInfoOfNZcCommFailure(const UINT16_S nZcId);

/*************************************************
  ������:      CalculateTrainInChangeLineId
  ��������:    �����г��Ƿ�λ��ĳ���л���·
  ����:        ��
  ���:        ��
  ����ֵ:      ��
*************************************************/
void CalculateTrainInChangeLineId(void);

/*************************************************
  ������:      JudgeSignalTrainChangeLineId
  ��������:    �����г��Ƿ�λ��ĳ���л���·
  ����:        const UINT16_S trainId,�г�ID
  ���:        ��
  ����ֵ:      0u:��λ���л���·��
               >0u:λ���л�������
*************************************************/
UINT16_S JudgeSignalTrainChangeLineId(const UINT16_S trainId);

/*************************************************
  ������:      CalculateChangeLineSwtichPosInNeed
  ��������:    �����л���·�ĵ����Ƿ�����Ҫ��λ��
  ����:        const UINT16_S changeLineId,�л���·ID
  ���:        ��
  ����ֵ:      0u:������
               1u:����
*************************************************/
UINT8_S CalculateChangeLineSwtichPosInNeed(const UINT16_S changeLineId);

/*************************************************
  ������:      JudgeTrainChangeId
  ��������:    ���������г����л���·ID
  ����:        ��
  ���:        ��
  ����ֵ:      ��
*************************************************/
void JudgeTrainChangeId(void);

/*************************************************
  ������:      JudgeSingleTrainChangeId
  ��������:    ���ҵ����г���ƥ���ϵ��л���·��ID
  ����:        const UINT16_S trainId,�г�ID
  ���:        ��
  ����ֵ:      >0u:�л�����ID
               0u:�����л�����
               0xffu:ʧ��
*************************************************/
UINT8_S JudgeSingleTrainChangeId(const UINT16_S trainId);

/*************************************************
  ������:      JudgeRelationBetweenAcSqu
  ��������:    �ж�������������֮��Ĺ�ϵ���������1��ȫ����������2�У����سɹ������򣬷���ʧ��
  ����:        const UINT8 acNum1,��������1����
  			   const UINT16_S acSqu1[CHANGE_AREA_AC_MAX]����������1ID
  			   const UINT8_S acNum1,��������2����
     		   const UINT16_S acSqu1[CHANGE_AREA_AC_MAX]����������2ID
  ���:        ��
  ����ֵ:      1u:����
               0u:������
*************************************************/
UINT8_S JudgeRelationBetweenAcSqu(const UINT8_S acNum1,const UINT16_S acSqu1[],const UINT8_S acNum2,const UINT16_S acSqu2[]);

/*************************************************
  ������:      JudgeSwitchStatusInChangeLine
  ��������:    ���Ҽ��������ڰ����ĵ�������״̬���л�����״̬��һ����
  ����:        const UINT16_S switchSquBuff[CHANGE_LINE_SWITCH_MAX],�����������
  			   const UINT8_S switchNum�������������
  ���:        ��
  ����ֵ:      >0u:���ϵ��л�����ID
               0u: ʧ��
*************************************************/
UINT8_S JudgeSwitchStatusInChangeLine(const UINT16_S switchSquBuff[],const UINT8_S switchNum);

/*************************************************
  ������:      JudgeSwitchIdInAcSqu
  ��������:    ���Ҽ��������ڰ����ĵ�������
  ����:        const UINT16_S acSquBuff[CHANGE_AREA_AC_MAX], ������������
  			   const UINT8_S acNum, ������������
  ���:        UINT16_S switchSquBuff[CHANGE_LINE_SWITCH_MAX]�������������
               UINT8_S *pSwitchNum�������������
  ����ֵ:      RETURN_SUCCESS:�ɹ�
               RETURN_ERROR: ʧ��
*************************************************/
UINT8_S JudgeSwitchIdInAcSqu(const UINT16_S acSquBuff[],const UINT8_S acNum,UINT16_S switchSquBuff[],UINT8_S *pSwitchNum);

/*************************************************
  ������:      JudgetrainStartIdInChange
  ��������:    �����г�λ�ڹ����������ʼ����
  ����:        const UINT16_S trainId,�г�ID
  ���:        ��
  ����ֵ:      ��ʼ��������ID
*************************************************/
UINT16_S JudgetrainStartIdInChange(const UINT16_S trainId);

/*************************************************
  ������:      JudgeTrainLocInChangeLine
  ��������:    �ж��г�λ���л������λ��
  ����:        const UINT16_S trainId,�г�ID
  ���:        ��
  ����ֵ:      0u ʧ��
               1u ��ͷ��β��λ���л�������
               2u ��ͷλ���л������ڣ���β��λ���л�������
               3u ��ͷλ���л������⣬��β��λ���л�������
               4u �г�λ���л�������
*************************************************/
UINT8_S JudgeTrainLocInChangeLine(const UINT16_S trainId);

/*************************************************
  ������:      JudgeAcSquToChangeEnd
  ��������:    ��ȡָ�����ᵽ�л������ն˵ļ�������
  ����:        const UINT16_S acId  ��ʼ����ID
               const UINT8_S direction ����
  ���:        UINT8_S *pOutAcNum ���ؼ�������
               UINT16_S acSquBuff[CHANGE_AREA_AC_MAX] ���ؼ�������
  ����ֵ:      RETURN_ERROR ʧ��
               RETURN_SUCCESS �ɹ�
*************************************************/
UINT8_S JudgeAcSquToChangeEnd(const UINT16_S acId,const UINT8_S direction,UINT8_S *pOutAcNum,UINT16_S acSquBuff[]);

/*************************************************
  ������:      ManageDeleteTrainInfo
  ��������:    ������Ҫɾ���г���Ϣ����������Ҫɾ�����г�����ɾ����
  ����:        ��
  ���:        ��
  ����ֵ:      ��
*************************************************/
void ManageDeleteTrainInfo(void);

#ifdef __cplusplus
}
#endif

#endif
