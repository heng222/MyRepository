/************************************************************************
*
* �ļ���   ��  SwitchLogicManager.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �����߼��������
* ��  ע   ��  ��
*
************************************************************************/
#ifndef SWITCH_LOGIC_DATA_H_
#define SWITCH_LOGIC_DATA_H_


#include "SwitchDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* ���������� ����ͨ�Ź���Ci��Ӧ�ĵ���������Ϣ
	* ����˵���� const UINT16 switchId������ID    
	* ����ֵ  �� void  
	*/
	void InitFailureSingleSwitch(const UINT16_S switchId);

	/*
	* ���������� ����ͨ�Ź���Ci��Ӧ�ĵ�����Ϣ
	* ����˵���� const UINT16 ciId;ͨ�Ź��ϵ�����ID   
	* ����ֵ  �� void  
	*/
	void InitFailureCiSwitch(const UINT16_S ciId);

	/*
	* ���������� ����ͨ�Ź���NZc��Ӧ�ĵ�����Ϣ
	* ����˵���� const UINT16 nZcId,����ZC    
	* ����ֵ  �� void  
	*/
	void InitFailureNZcSwitch(const UINT16_S nZcId);

	/*
	* ���������� ��֯����ѯ����DMU�ı��ص�����Ϣ
	* ����˵���� void    
	* ����ֵ  �� void  
	*/
	void SetDmuSwitchStatusInfo(void);

#ifdef __cplusplus
}
#endif

#endif
