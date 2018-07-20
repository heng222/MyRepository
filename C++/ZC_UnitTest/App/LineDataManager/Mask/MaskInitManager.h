/************************************************************************
*
* �ļ���   ��  MaskInitManager.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��λ��ʼ������
* ��  ע   ��  ��
*
************************************************************************/
#ifndef MASK_INIT_MANAGER_H_
#define MASK_INIT_MANAGER_H_


#include "MaskDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* ���������� ��ʼ�����ع������λ��Ϣ�еĻ�����Ϣ
	* ����˵���� ��   
	* ����ֵ  �� ��      
	*/
	void InitMaskValueData(void);

	/*
	* ���������� ��ȡ�豸����������ID
	* ����˵���� const UINT16 devId, �豸ID
	*            const UINT8_S devType,�豸����
	* ����ֵ  �� 0: ��ȡʧ��
	*			>0: ����CIID      
	*/
	UINT16_S GetLineDeviceBelongCiId(const UINT16_S devId,const UINT8_S devType);

	/*
	* ���������� ��ʼ�����ع������λ��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitZcCiMaskLocalInfo(void);

	/*
	* ���������� ��ʼ����λ������Ϣ��ͨѶ����
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			 1: ��ʼ���ɹ�      
	*/
	UINT8_S InitZcCiMaskConfigCommTargetData(void);

	/*
	* ���������� ��ʼ�����ع���ķ��͸�CIϵͳ����λ��Ϣ
	* ����˵���� UINT16 maskId;��λID
	*            UINT8_S maskType;��λ����
	*            UINT16_S devId;�豸ID
	*            UINT8_S devType;�豸����
	*            UINT16_S relevanceMaskId;������λID
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			 1: ��ʼ���ɹ�      
	*/
	UINT8_S InitSendToCiMaskInfo(UINT16_S maskId,UINT8_S maskType,UINT16_S devId,UINT8_S devType,UINT16_S relevanceMaskId);

	/*
	* ���������� ��ʼ�����ع���Ľ���CI����ZCϵͳ����λ��Ϣ
	* ����˵���� UINT16 maskId;��λID
	*            UINT8_S maskType;��λ����
	*            UINT16_S devId;�豸ID
	*            UINT8_S devType;�豸����
	*            UINT16_S relevanceMaskId;������λID
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			 1: ��ʼ���ɹ�      
	*/
	UINT8_S InitReceiveToCiMaskInfo(UINT16_S maskId,UINT8_S maskType,UINT16_S devId,UINT8_S devType,UINT16_S relevanceMaskId);

	/*
	* ���������� ��ʼ�����ع���ĵ�����λ��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitZcCiMaskOfSwitchInfo(void);

	/*
	* ���������� ��ʼ�����ع�����źŻ���λ��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitZcCiMaskOfSignalInfo(void);

	/*
	* ���������� ��ʼ�����ع������������λ��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitZcCiMaskOfPsdInfo(void);

	/*
	* ���������� ��ʼ�����ع���Ľ���ͣ����ť��λ��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitZcCiMaskOfEsbInfo(void);

	/*
	* ���������� ��ʼ�����ع���ļ���������λ��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitZcCiMaskOfAcInfo(void);

	/*
	* ���������� ��ʼ�����ع�����߼�������λ��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitZcCiMaskOfSectionInfo(void);

	/*
	* ���������� ��ʼ�����ع���Ľ�·��λ��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitZcCiMaskOfRouteInfo(void);

	/*
	* ���������� ��ʼ�����ع���ı���������λ��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitZcCiMaskOfOverlapInfo(void);

	/*
	* ���������� ��ʼ�����ع���������۷���λ��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitZcCiMaskOfDrInfo(void);

	/*
	* ���������� ��ʼ���źŻ���ѹ��Ϣ
	* ����˵���� const UINT16 signalId,�źŻ�ID 
	*            const UINT16_S maskId,��λֵ
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitSignalCrossInfo(const UINT16_S signalId,const UINT16_S maskId);

	/*
	* ���������� ��ʼ���źŻ�������Ϣ
	* ����˵���� const UINT16 signalId,�źŻ�ID 
	*            const UINT16_S maskId,��λֵ
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitSignalLightOffInfo(const UINT16_S signalId,const UINT16_S maskId);

#ifdef __cplusplus
}
#endif

#endif
