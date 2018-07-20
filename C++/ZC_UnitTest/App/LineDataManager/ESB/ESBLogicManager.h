/************************************************************************
*
* �ļ���   ��  ESBLogicManager.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ����ͣ����ť�߼�����
* ��  ע   ��  ��
*
************************************************************************/
#ifndef ESB_LOGIC_MANAGER_H_
#define ESB_LOGIC_MANAGER_H_


#include "ESBDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* ���������� ������϶�Ӧ�ĵ���ESB��Ϣ
	* ����˵���� const UINT16 esbId��ESBID    
	* ����ֵ  �� void  
	*/
	void InitFailureSingleEsb(const UINT16_S esbId);

	/*
	* ���������� ����ͨ�Ź���Ci��Ӧ�Ľ���ͣ����ť��Ϣ
	* ����˵���� const UINT16 ciId��ͨ�Ź��ϵ�CIID    
	* ����ֵ  �� void  
	*/
	void InitFailureCiEsb(const UINT16_S ciId);

	/*
	* ���������� ����ͨ�Ź���ZC��Ӧ�Ľ���ͣ����ť��Ϣ
	* ����˵���� const UINT16 nZcId��ͨ�Ź��ϵ�nZcID    
	* ����ֵ  �� void  
	*/
	void InitFailureNZcEsb(const UINT16_S nZcId);

#ifdef __cplusplus
}
#endif

#endif
