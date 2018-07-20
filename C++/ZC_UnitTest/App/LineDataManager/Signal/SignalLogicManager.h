/************************************************************************
*
* �ļ���   ��  SignalLogicManager.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ά������
* ��  ע   ��  ��
*
************************************************************************/
#ifndef SIGNAL_LOGIC_MANAGER_DATA_H_
#define SIGNAL_LOGIC_MANAGER_DATA_H_

#include "SignalDefine.h"
#include "../../../Common/CommonTypes.h"
#include "../../SysDataManager/SysConfigData.h"

#ifdef __cplusplus
extern "C" {
#endif


	/*
	* ���������� ����ͨ�Ź���Ci��Ӧ�ĵ����źŻ���Ϣ
	* ����˵���� const UINT16 signalId���źŻ�ID    
	* ����ֵ  �� void  
	*/
	void InitFailureSingleSignal(const UINT16_S signalId);

	/*
	* ���������� ����ͨ�Ź���Ci��Ӧ���źŻ���Ϣ
	* ����˵���� const UINT16 ciId������ID    
	* ����ֵ  �� void  
	*/
	void InitFailureCiSignal(const UINT16_S ciId);

	/*
	* ���������� ����ͨ�Ź���NZc��Ӧ���źŻ���Ϣ
	* ����˵���� const UINT16 nZCId    
	* ����ֵ  �� void  
	*/
	void InitFailureNZcSignal(const UINT16_S nZCId);

	/*
	* ���������� �źŻ��������
	* ����˵���� void
	* ����ֵ  �� void     
	*/
	void SignalControl(void);

	/*
	* ���������� �źŻ����������
	* ����˵���� UINT16 signalId,�źŻ�Id
	* ����ֵ  �� void      
	*/
	void SignalLightAndOffDeal(UINT16_S signalId);

	/*
	* ���������� �����źŻ����������ʱ�ļ�����������
	* ����˵���� const UINT16 signalId,�źŻ�Id
	*            UINT8_S *acNum,������������
	*            UINT16_S acIdBuff[],��������ID����
	* ����ֵ  �� 0: ����ʧ��
	*			 1: ����ɹ�      
	*/
	UINT8_S CalculateAcOfSignalLighten(const UINT16_S signalId,UINT8_S *acNum,UINT16_S acIdBuff[]);

	/*
	* ���������� �г����ź��ж�
	* ����˵���� ��
	* ����ֵ  �� ��     
	*/
	void TrainCrashSignal(void);

	/*
	* ���������� �����г���ѹ�źŻ�״̬
	* ����˵���� ��
	* ����ֵ  �� ��      
	*/
	void TrainAcrossSingalManager(void);

	/*
	* ���������� �����г���ѹ�źŻ�״̬����
	* ����˵���� UINT16 signalId,�źŻ�Id
	* ����ֵ  �� 0: ����ʧ��
	*			 1: ����ɹ�      
	*/
	UINT8_S JudgeTrainAcrossOfSingalSignal(const UINT16_S signalId);

	/*
	* ���������� �ж��г�λ���Ƿ�������źŻ��Ĵ��п�ѹ
	* ����˵���� UINT16 signalId,�źŻ�Id
	*            const UINT8_S trainId,�г�Id
	* ����ֵ  �� 0: ����ʧ��
	*			 1: ����ɹ�      
	*/
	UINT8_S JudgeTrainNeedSingalLoc(const UINT16_S signalId, const UINT16_S trainId);

#ifdef __cplusplus
}
#endif

#endif
