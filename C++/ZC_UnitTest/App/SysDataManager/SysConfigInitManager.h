/************************************************************************
*
* �ļ���   ��  SysConfigInitManager.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ZCϵͳ���õĳ�ʼ������
* ��  ע   ��  ��
*
************************************************************************/
#ifndef SYS_CONFIG_DATA_INIT_MANAGER_H_
#define SYS_CONFIG_DATA_INIT_MANAGER_H_

#include "../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* ���������� ��ʼ��ϵͳ������Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitSystemConfigData(void);

	/*
	* ���������� ��ʼ��ϵͳ������Ϣ���г���Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitTrainConfigInfo(void);

	/*
	* ���������� ��ʼ��ZC��ϵͳ������Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitZcSubSystemConfigData(void);

	/*
	* ���������� ��ʼ������ZCId������Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitLocalZcIdConfigData(void);

	/*
	* ���������� ��ʼ������Ntp������Ϣ
	* ����˵���� ��   
	* ����ֵ  �� ��      
	*/
	void InitLocalNtpConfigData(void);

#ifdef __cplusplus
}
#endif

#endif
