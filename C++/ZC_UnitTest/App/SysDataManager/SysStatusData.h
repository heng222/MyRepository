/************************************************************************
*
* �ļ���   ��  SysStatusData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ZCϵͳ״̬����
* ��  ע   ��  ��
*
************************************************************************/
#ifndef SYS_STATUS_DATA_H_
#define SYS_STATUS_DATA_H_

#include "../../Common/CommonTypes.h"
#include "SysDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*����ZC״̬�������ݽṹ*/
	typedef struct LocalZcInfoStruct
	{
		UINT32_S ZcCycle;                               /*ZC��������*/
	}LocalZcInfoStruct;

	/*
	* ���������� ����ZC״̬�������ݽṹ
	* ����˵���� void    
	* ����ֵ  �� NULL: ��ȡ����ʧ��
	*			 !NULL: ����ZC״̬�������ݽṹ
	*/
	LocalZcInfoStruct* LocalZcInfoData(void);

	/*
	* ���������� ��ȡZC�������ں�
	* ����˵���� ��    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: localZC�����ں�
	*/
	UINT32_S GetZcCycle(void);

	/*
	* ���������� ����ZC���ں�
	* ����˵���� UINT32 zcCycle,���ں�    
	* ����ֵ  �� ��
	*/
	void SetZcCycle(UINT32_S zcCycle);

	/*
	* ���������� �ۼ�ZC���ں�
	* ����˵���� ��   
	* ����ֵ  �� ��
	*/
	void AddZcCycle(void);

	/*
	* ���������� ��ʼ��ZC��ϵͳ״̬��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� ��
	*/
	void InitZcSysStatusData(void);

#ifdef __cplusplus
}
#endif

#endif
