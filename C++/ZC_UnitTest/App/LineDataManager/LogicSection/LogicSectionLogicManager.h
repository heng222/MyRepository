/************************************************************************
*
* �ļ���   ��  LogicSectionLogicManager.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �߼������߼�����
* ��  ע   ��  ��
*
************************************************************************/
#ifndef LOGIC_SECTION_LOGIC_MANAGER_H_
#define LOGIC_SECTION_LOGIC_MANAGER_H_

#include "../../SysDataManager/SysDefine.h"
#include "../../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*
	* ���������� ������϶�Ӧ�ĵ����߼�������Ϣ
	* ����˵���� const UINT16 logicSectionId���߼�����ID    
	* ����ֵ  �� void  
	*/
	void InitFailureSingleLogicSetion(const UINT16_S logicSectionId);

	/*
	* ���������� ����ͨ�Ź���Ci��Ӧ���߼�������Ϣ
	* ����˵���� const UINT16 ciId��ͨ�Ź��ϵ�CIID    
	* ����ֵ  �� void  
	*/
	void InitFailureCiLogicSection(const UINT16_S ciId);

	/*
	* ���������� �߼����θ���ռ��״̬
	* ����˵���� void    
	* ����ֵ  �� void
	*/
	void UpdataLogicSectionManager(void);

	/*
	* ���������� ���µ������������߼�����ռ��״̬
	* ����˵���� const UINT16 acId;�������α��    
	* ����ֵ  �� void
	*/
	void UpdateSingalAcLogicSection(const UINT16_S acId);

	/*
	* ���������� ��ʼ�������������߼�����״̬ΪUT
	* ����˵���� const UINT16 acId;�������α��    
	* ����ֵ  �� void
	*/
	void InitLogicStatusOfSingleAc(const UINT16_S acId);

	/*
	* ���������� ���µ��������ڵ������г�ռѹ�߼�����
	* ����˵���� const UINT16 acId;�������α�� 
	*            const UINT16_S trainId;�г�ID
	* ����ֵ  �� void
	*/
	void UpdateLogicStatusOfSingleTrain(const UINT16_S acId,const UINT16_S trainId);

	/*
	* ���������� ���µ��������ڵ��г�ռѹ�߼�����
	* ����˵���� const UINT16 acId;�������α��   
	* ����ֵ  �� void
	*/
	void UpdateLogicStatusOfTrain(const UINT16_S acId);

	/*
	* ���������� ���µ������������г������г������˵�֮���߼�����״̬
	* ����˵���� const UINT16 acId ���жϼ���ID    
	* ����ֵ  �� void
	*/
	void UpdateLogicStatusBetweenTrains(const UINT16_S acId);

	/*
	* ���������� ����2���г�֮����߼�����״̬
	* ����˵���� const UINT16 trainId1;ǰ��ID
	*            const UINT16_S trainId2;��ID
	* ����ֵ  �� void
	*/
	void UpdateLogicStatusBetweenTwoTrains(const UINT16_S trainId1,const UINT16_S trainId2);

	/*
	* ���������� ���µ��������ڵ�һ����ǰ���߼�����״̬
	* ����˵���� const UINT16 acId;�������α��
	*            const UINT16_S trainId;�г�ID
	* ����ֵ  �� void
	*/
	void UpdateLogicStatusBeforeFirstTrain(const UINT16_S acId,const UINT16_S trainId);

	/*
	* ���������� ���µ������������һ�������߼�����״̬
	* ����˵���� const UINT16 acId;�������α��
	*            const UINT16_S trainId;�г�ID
	* ����ֵ  �� void
	*/
	void UpdateLogicStatusRearLastTrain(const UINT16_S acId,const UINT16_S trainId);

	/*
	* ���������� �ж�����ͨ�ų�֮����߼�����״̬
	* ����˵���� const UINT16 trainId1;ǰ��ID
	*            const UINT16_S trainId2;��ID  
	* ����ֵ  �� 0x55 �Ϲ��
	*			 0xaa ����			 
	*			 0    ʧ��
	*/
	UINT8_S JudgeLogicStatusBetweenTwoTrains(const UINT16_S trainId1,const UINT16_S trainId2);

	/*
	* ���������� �ڱ������ڣ��Աȱ������г�ռѹ���߼����κͻ����������ռѹ���߼����Σ�
	�ж��Ƿ����غϲ���
	* ����˵���� const UINT16 preSectionId[]  ������ռѹ�߼�����
	*			 cosnt UINT16_S oldSectionId[]   ����������ռѹ�߼�����
	*			 UINT8_S preSectionNum      ������ռѹ�߼���������
	*			 UINT8_S oldSectionNum       ������ռѹ�߼���������
	* ����ֵ  �� RETURN_SUCCESS �غ�
	*			 RETURN_ERROR ���غ�			 
	*/
	/*�߼������غ����жϺ���*/
	UINT8_S JudgeLogicSectionSuperPosition(const UINT16_S preSectionId[],const UINT16_S oldSectionId[],
		UINT8_S preSectionNum,UINT8_S oldSectionNum);

	/*
	* ���������� �г�ռѹ�߼����������Լ�飬����⵽�������󣬿��Ʊ�ZC崻�
	* ����˵���� ��
	* ����ֵ  �� 0:������У��ʧ��
	*            1:������У��ɹ�
	*/
	UINT8_S JudgeTrainLogicContinuity(void);

#ifdef __cplusplus
}
#endif

#endif
