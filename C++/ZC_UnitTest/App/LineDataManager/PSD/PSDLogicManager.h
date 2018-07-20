/************************************************************************
*
* �ļ���   ��  PSDLogicManager.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �������߼�����
* ��  ע   ��  ��
*
************************************************************************/
#ifndef PSD_LOGIC_MANAGER_H_
#define PSD_LOGIC_MANAGER_H_

#include "PSDDefine.h"
#include "../../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif
	/*
	* ���������� ����ͨ�Ź���Ci��Ӧ�ĵ�����������Ϣ
	* ����˵���� const UINT16 psdId��������ID    
	* ����ֵ  �� void  
	*/
	void InitFailureSinglePsd(const UINT16_S psdId);

	/*
	* ���������� ����ͨ�Ź���Ci��Ӧ����������Ϣ
	* ����˵���� const UINT16 ciId��ͨ�Ź��ϵ�CIID    
	* ����ֵ  �� void  
	*/
	void InitFailureCiPsd(const UINT16_S ciId);

	/*
	* ���������� ����ͨ�Ź���Ci��Ӧ����������Ϣ
	* ����˵���� const UINT16 nZcId��ͨ�Ź��ϵ�����ZcID    
	* ����ֵ  �� void  
	*/
	void InitFailureNZcPsd(const UINT16_S nZcId);

#ifdef __cplusplus
}
#endif

#endif
