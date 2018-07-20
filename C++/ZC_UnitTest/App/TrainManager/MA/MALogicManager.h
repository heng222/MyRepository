/********************************************************                                                                                                            
 *
 * �� �� ���� MALogicManager.h
 * ��    �ߣ� ZC��
 * ����ʱ�䣺 2015-04-18
 * ����    �� �ƶ���Ȩ�߼����� 
 * ��ע    �� �� 
 *
********************************************************/
#ifndef MA_LOGIC_MANAGER_H_
#define MA_LOGIC_MANAGER_H_

#include "../../../Common/CommonTypes.h"
#include "MAStatusData.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
* �������ƣ� ManageTrainMaInfo
* ���������� �г����ƶ���Ȩ��Ϣ����
* ��������� ��
* ��������� ��
* ����ֵ  �� ��
*/
void ManageTrainMaInfo(void);

/*
* �������ƣ� JudgeTrainStateFailure
* ���������� ����״̬�г�����
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeTrainStateFailure(const UINT16_S trainId);

/*
* �������ƣ� JudgeHandOverTrain
* ���������� �ƽ�״̬�µ��ƶ���Ȩ����
* ��������� const UINT16_S trainId,�г�ID
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeHandOverTrain(const UINT16_S trainId);

/*
* �������ƣ� CalculateTrainMa
* ���������� �г����ƶ���Ȩ��Ϣ����
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
*/
void CalculateTrainMa(const UINT16_S trainId);

/*
* �������ƣ� JudgeTrainMaByRouteInfo
* ���������� �����Խ�·Ϊ�������г����ƶ���Ȩ��Ϣ����
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeTrainMaByRouteInfo(const UINT16_S trainId);

/*
* �������ƣ� JudgeRouteOfLockOverlap
* ���������� �жϽ�·�Ƿ�������գ������ı�������
* ��������� const UINT16_S routeId,�г�Id
* ��������� ��
* ����ֵ  �� 0u:��overlap
*			 >0u:overlapId
*/
UINT16_S JudgeRouteOfLockOverlap(const UINT16_S routeId);

/*
* �������ƣ� JudgeOverlapOfAcFree
* ���������� �жϱ������ι����ļ��������Ƿ����
* ��������� const UINT8_S overlapOfAcNum,�������ΰ����ļ�������
*            const UINT16_S overlapAcIdBuff[]���������ΰ����ļ���ID
* ��������� ��
* ����ֵ  �� RETURN_SUCCESS:����
*			 RETURN_ERROR:�ǿ���
*/
UINT8_S JudgeOverlapOfAcFree(const UINT8_S overlapOfAcNum,const UINT16_S overlapAcIdBuff[]);

/*
* �������ƣ� CalulateOverlapLength
* ���������� �жϱ������ι����ļ��������Ƿ����
* ��������� const UINT8_S overlapOfAcNum,�������ΰ����ļ�������
*            const UINT16_S overlapAcIdBuff[]���������ΰ����ļ���ID
* ��������� UINT32_S *overlapLength,����
* ����ֵ  �� RETURN_SUCCESS:����ɹ�
*			 RETURN_ERROR  :����ʧ��
*/
UINT8_S CalulateOverlapLength(const UINT8_S overlapOfAcNum,const UINT16_S overlapAcIdBuff[],UINT32_S *overlapLength);

/*
* �������ƣ� JudgeTrainMaByOutwardAcInfo
* ���������� �Խ�·���߱��������ⷽһ������������ϢΪ��׼�����ƶ���Ȩ��Ϣ
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeTrainMaByOutwardAcInfo(const UINT16_S trainId);

/*
* �������ƣ� CalculateAcOrderHaveOtherTrain
* ���������� �жϴӳ�ͷ��MA�յ�����������Ƿ���������г�/����ռ��
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� 0u:�����������г�/����ռ��
*            1u:���������г�/����ռ��
*            2u:��������ѽ���
*/
UINT8_S CalculateAcOrderHaveOtherTrain(const UINT16_S trainId);

/*
* �������ƣ� JudgeTrainMaByAcInfo
* ���������� �Լ���������ϢΪ��׼�����ƶ���Ȩ��Ϣ
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeTrainMaByAcInfo(const UINT16_S trainId);

/*
* �������ƣ� JudgeCommUnCtTrainForMa
* ���������� �ж��Ƿ�����׷�ٷ�ͨ���г�����MA�س�Ӱ����������
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeCommUnCtTrainForMa(const UINT16_S trainId);

/*
* �������ƣ� JudgeTrainMaByAcOfFrontAcInfo
* ���������� ����ǰ�����������ڵ��г��Ե�ǰ�г��ƶ���Ȩ��Ӱ��
* ��������� const UINT8_S flagType,(������Ϣ:0x55,����ǰ���������г���Ϣ;0xaa,������ǰ���������г���Ϣ)
*            const UINT16_S trainId,�г�Id
*            const UINT16_S acId,��ǰ����
*            const UINT16_S frontAcId,ǰ����������    
* ��������� ��
* ����ֵ  �� RETURN_SUCCESS,����ɹ�
*            RETURN_ERROR  ,����ʧ��
*/
UINT8_S JudgeTrainMaByAcOfFrontAcInfo(const UINT8_S flagType,const UINT16_S trainId,const UINT16_S acId,const UINT16_S frontAcId);

/*
* �������ƣ� JudgeTrainMaByAcOfSameAcInfo
* ���������� ����ͬ���������ڵ��г��Ե�ǰ�г��ƶ���Ȩ��Ӱ��
* ��������� const UINT16_S trainId,�г�Id
*            const UINT16_S acId���г�ռѹ��������
*            const UINT8_S frontTrainIndex��ǰ���г����������±�
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeTrainMaByAcOfSameAcInfo(const UINT16_S trainId,const UINT16_S acId,const UINT8_S frontTrainIndex);

/*
* �������ƣ� CalculateTrainMaByFrontTrainTail
* ���������� ����ǰ���г���β������ƶ���Ȩ����
* ��������� const UINT16_S trainId,�г�Id
*            const UINT16_S frontTrainId,ǰ���г�ID
*            const UINT16_S acId,���������Id
* ��������� ��
* ����ֵ  �� ��
*/
void CalculateTrainMaByFrontTrainTail(const UINT16_S trainId,const UINT16_S frontTrainId,const UINT16_S acId);

/*
* �������ƣ� CalculateTrainMaByFrontTrainHead
* ���������� ����ǰ���г���ͷ������ƶ���Ȩ����
* ��������� const UINT16_S trainId,�г�Id
*            const UINT16_S frontTrainId,ǰ���г�ID
*            const UINT16_S acId,���������Id
* ��������� ��
* ����ֵ  �� ��
*/
void CalculateTrainMaByFrontTrainHead(const UINT16_S trainId,const UINT16_S frontTrainId,const UINT16_S acId);

/*
* �������ƣ� JudgeTrainMaByStationInfo
* ���������� ������վ̨Ϊ�������г����ƶ���Ȩ��Ϣ����
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeTrainMaByStationInfo(const UINT16_S trainId);

/*
* �������ƣ� CalculateObsInfoBelongToMaArea
* ���������� �����ƶ���Ȩ��Χ�ڵ��ϰ�����Ϣ
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
*/
void CalculateObsInfoBelongToMaArea(const UINT16_S trainId);

/*
* �������ƣ� CalculateTsrInfoBelongToMaArea
* ���������� �����ƶ���Ȩ��Χ�ڵ���ʱ������Ϣ
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
*/
void CalculateTsrInfoBelongToMaArea(const UINT16_S trainId);

/*
* �������ƣ� JudgeReverseStateMaInfo
* ���������� �����۷�״̬�µ��ƶ���Ȩ��Ϣ
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeReverseStateMaInfo(const UINT16_S trainId);

/*
* �������ƣ� CalculaReverseStateMaInfo
* ���������� �����۷�λ�õ��ƶ���Ȩ��Ϣ
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
*/
void CalculaReverseStateMaInfo(const UINT16_S trainId);

/*
* �������ƣ� JudgeCancellationStateMaInfo
* ���������� ����ע��״̬�µ��ƶ���Ȩ��Ϣ
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeCancellationStateMaInfo(const UINT16_S trainId);

/*
* �������ƣ� CalculatAdjustMaEndInfo
* ���������� �����Ƿ���Ҫ�����ƶ���Ȩ�յ㲢�����ƶ���Ȩ�յ�
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
*/
void CalculatAdjustMaEndInfo(const UINT16_S trainId);

/*
* �������ƣ� CalculateMaEndAttribute
* ���������� �����ƶ���Ȩ�յ�������Ϣ
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
*/
void CalculateMaEndAttribute(const UINT16_S trainId);

/*
* �������ƣ� MixObsOfMa
* ���������� ����ƶ���Ȩ��Ϣ�е��ϰ�����Ϣ
* ��������� const UINT16_S trainId,�г�Id
* ��������� ObsOfMAStruct mixObsBuff[],����ϰ�����Ϣ
* ����ֵ  �� RETURN_UINT8_MAX_VALUE:ʧ��
*            [0,RETURN_UINT8_MAX_VALUE):�ϰ�������
*/
UINT8_S MixObsOfMa(const UINT16_S trainId,ObsOfMAStruct mixObsBuff[]);

/*
* �������ƣ� MixTsrOfMa
* ���������� ����ƶ���Ȩ��Ϣ�е���ʱ������Ϣ
* ��������� const UINT16_S trainId,�г�Id
* ��������� TsrOfMAStruct mixTsrBuff[],�����Ϻ����ʱ����
* ����ֵ  �� RETURN_UINT8_MAX_VALUE:ʧ��
*            [0,RETURN_UINT8_MAX_VALUE):��ʱ��������
*/
UINT8_S MixTsrOfMa(const UINT16_S trainId,TsrOfMAStruct mixTsrBuff[]);

/*
* �������ƣ� SingleTrainHandMixMA
* ���������� �����г�����ƶ���Ȩ���л��г���
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
*/
void SingleTrainHandMixMA(const UINT16_S trainId);
	
/*
* �������ƣ� CalPointIsOnOverlap
* ���������� ����1���Ƿ�λ�ڱ���������
* ��������� const UINT16_S segId, seg���
*          const UINT32_S offset,segƫ����
*          const UINT8_S dir,����
* ��������� UINT16_S *OutOverlapId,�������α��
* ����ֵ  �� 0:ʧ��
*          1��λ�ڱ��������ڲ�(�������˵�)
*          2: λ�������з��򱣻��������
*          3: λ�������з��򱣻������յ�
*/
UINT8_S CalPointIsOnOverlap(const UINT16_S segId,const UINT32_S offset,const UINT8_S dir,UINT16_S *OutOverlapId);
#ifdef __cplusplus
}
#endif

#endif
