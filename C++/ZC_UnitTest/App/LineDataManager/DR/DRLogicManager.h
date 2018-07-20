/************************************************************************
*
* �ļ���   ��  DRLogicManager.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �����۷��߼�����
* ��  ע   ��  ��
*
************************************************************************/
#ifndef DR_LOGIC_MANAGER_H_
#define DR_LOGIC_MANAGER_H_


#include "DRDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* ���������� ������϶�Ӧ�ĵ��������۷���ť��Ϣ
	* ����˵���� const UINT16 drButtonId�������۷���ťID    
	* ����ֵ  �� void  
	*/
	void InitFailureSingleDrButton(const UINT16_S drButtonId);

	/*
	* ���������� ����ͨ�Ź���Ci��Ӧ�������۷���ť��Ϣ
	* ����˵���� const UINT16 ciId��ͨ�Ź��ϵ�CIID    
	* ����ֵ  �� void  
	*/
	void InitFailureCiDrButoon(const UINT16_S ciId);

	/*
	* ���������� ����ͨ�Ź���ZC��Ӧ�������۷���ť��Ϣ
	* ����˵���� const UINT16 nZcId��ͨ�Ź��ϵ�nZcID    
	* ����ֵ  �� void  
	*/
	void InitFailureNZcDrButton(const UINT16_S nZcId);

	/*
	* ���������� ������϶�Ӧ�ĵ��������۷�����Ϣ
	* ����˵���� const UINT16 drLampId�������۷���ID    
	* ����ֵ  �� void  
	*/
	void InitFailureSingleDrLamp(const UINT16_S drLampId);

	/*
	* ���������� ����ͨ�Ź���Ci��Ӧ�������۷�����Ϣ
	* ����˵���� const UINT16 ciId��ͨ�Ź��ϵ�CIID    
	* ����ֵ  �� void  
	*/
	void InitFailureCiDrLamp(const UINT16_S ciId);

	/*
	* ���������� ����ͨ�Ź���ZC��Ӧ�������۷�����Ϣ
	* ����˵���� const UINT16 nZcId��ͨ�Ź��ϵ�nZcID    
	* ����ֵ  �� void  
	*/
	void InitFailureNZcDrLamp(const UINT16_S nZcId);

#ifdef __cplusplus
}
#endif

#endif
