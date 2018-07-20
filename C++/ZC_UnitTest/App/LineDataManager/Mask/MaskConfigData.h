/************************************************************************
*
* �ļ���   ��  MaskConfigData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��λ��������
* ��  ע   ��  ��
*
************************************************************************/
#ifndef MASK_CONFIG_DATA_H_
#define MASK_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "MaskDefine.h"

#ifdef __cplusplus
extern "C" {
#endif


	/*��λ��Ϣ���ݽṹ��*/
	typedef struct MaskConfigDataStruct
	{
		UINT16_S MaskId;                                   /*��λID*/
		UINT8_S MaskType;                                  /*��λ����*/
		UINT8_S DeviceType;                                /*��λ��Ӧ���豸����*/
		UINT8_S DeviceSum;                                 /*��λ��Ӧ���豸����*/
		UINT16_S DeviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX];  /*��λ��Ӧ���豸IdBuff*/
		UINT16_S RelevanceMaskId;                          /*��λ��������λid*/
	} MaskConfigDataStruct;

	typedef struct ZcCiMaskConfigDataStruct
	{
		UINT16_S CommCiId;                   /*ͨѶ����ID*/
		UINT16_S MaskCurSum;                 /*Ŀǰ��λ����*/
		UINT16_S MaskIdMax;                  /*��λID�����ֵ*/
		UINT16_S MaskIdBuff[ZC_TO_CI_MASK_SUM_MAX];                                /*��λID������*/
		MaskConfigDataStruct MaskConfigDataStru[SINGLE_ZC_TO_CI_MASK_SUM_MAX];  /*��λ��Ϣ���ݽṹ������*/
	}ZcCiMaskConfigDataStruct;

	/*
	* ���������� ��ȡ����豸�ܸ���
	* ����˵���� const UINT8 destSystemType Ŀ��ϵͳ����  
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �豸��ǰ����
	*/
	UINT8_S GetSendCommTargetNum(const UINT8_S destSystemType);

	/*
	* ���������� ��ȡĳ���豸��Ӧ������
	* ����˵���� const UINT8 destSystemType Ŀ��ϵͳ����  
	*			 const UINT16_S destSystemId Ŀ��ID
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��λ��Ϣ��ǰ����
	*/
	UINT8_S GetSendCommTargetIndex(const UINT8_S destSystemType,const UINT16_S destSystemId);

	/*
	* ���������� ��ȡ��λ��Ϣ��������
	* ����˵���� const UINT8 destSystemType Ŀ��ϵͳ����
	*			 const UINT16_S destSystemId Ŀ��ϵͳId
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��λ��Ϣ��ǰ����
	*/
	UINT16_S GetSendToOtherMaskSum(const UINT8_S destSystemType,const UINT16_S destSystemId);

	/*
	* ���������� ��ȡ��λID���ֵ
	* ����˵���� const UINT8 destSystemType Ŀ��ϵͳ���� 
	*			 const UINT16_S destSystemId Ŀ��ϵͳId
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��λID���ֵ
	*/
	UINT16_S GetSendToOtherMaskIdMax(const UINT8_S destSystemType,const UINT16_S destSystemId);

	/*
	* ���������� ��ȡָ��ZC����ָ��ϵͳ��λ����
	* ����˵���� const UINT8 sourceSystemType, Դϵͳ����
	*			 const UINT16_S sourceSystemId ԴϵͳID
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��λ����      
	*/
	UINT16_S GetReceiveToZcMaskSum(const UINT8_S sourceSystemType,const UINT16_S sourceSystemId);

	/*
	* ���������� ��ȡ��λID���ֵ
	* ����˵���� const UINT8 sourceSystemType, Դϵͳ����   
	*			 const UINT16_S sourceSystemId ԴϵͳID
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��λID���ֵ
	*/
	UINT16_S GetReceiveToZcMaskIdMax(const UINT8_S sourceSystemType,const UINT16_S sourceSystemId);

	/*
	* ���������� ��ȡ���͸�������ϵͳָ�������±��Ӧ����λ�±�
	* ����˵���� const UINT16 bufIndex, �����±�
	*			 const UINT8_S destSystemType, Ŀ��ϵͳ����
	*			 const UINT16_S destSystemId, Ŀ��ϵͳID
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��λ�±�     
	*/
	UINT16_S GetSendMaskId(const UINT16_S bufIndex,const UINT8_S destSystemType,const UINT16_S destSystemId);

	/*
	* ���������� ��ȡָ��ID��λ������
	* ����˵���� const UINT16 maskId,��λID
	*			 const UINT8_S destSystemType, Ŀ��ϵͳ����
	*		     const UINT16_S destSystemId Ŀ��ϵͳId
	* ����ֵ  �� ZC_TO_CI_MASK_SUM_MAX; ��ȡ����ʧ��
	*			 >=0;���������ɹ�
	*/
	UINT16_S GetSendMaskBufIndex(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId);

	/*
	* ���������� ��ȡָ��ID��λ����λ����
	* ����˵���� const UINT16 maskId,��λID
	*			 const UINT8_S destSystemType, Ŀ��ϵͳ����
	*			 const UINT16_S destSystemId Ŀ��ϵͳId
	* ����ֵ  �� 0 : ��ȡ����ʧ��
	*			 >0; ��λ������Ϣ
	*/
	UINT8_S GetSendMaskType(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId);

	/*
	* ���������� ��ȡָ��ID��λ���豸����
	* ����˵���� const UINT16 maskId,��λID
	*			 const UINT8_S destSystemType, Ŀ��ϵͳ����
	*			 const UINT16_S destSystemId Ŀ��ϵͳId
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			 >0 �豸������Ϣ
	*/
	UINT8_S GetSendDeviceType(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId);

	/*
	* ���������� ��ȡָ��ID��λ���豸����
	* ����˵���� const UINT16 maskId,��λID
	*				const UINT8_S destSystemType, Ŀ��ϵͳ����
	*				const UINT16_S destSystemId Ŀ��ϵͳId
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			 >0 �豸����
	*/
	UINT8_S GetSendDeviceSum(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId);

	/*
	* ���������� ��ȡָ��ID��λ���豸ID����
	* ����˵���� const UINT16 maskId,��λID
	*		     const UINT8_S destSystemType, Ŀ��ϵͳ����
	*			 const UINT16_S destSystemId Ŀ��ϵͳId
	*			 const UINT8_S bufSize,�����С
	*			 UINT16_S deviceIdBuff[],�������
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			 1: �ɹ�
	*/
	UINT8_S GetSendDeviceIdBuff(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId,const UINT8_S bufSize,UINT16_S deviceIdBuff[]);

	/*
	* ���������� ��ȡָ��ID��λ�Ĺ�����λId
	* ����˵���� const UINT16 maskId,��λID
	*			 const UINT8_S destSystemType, Ŀ��ϵͳ����
	*			 const UINT16_S destSystemId Ŀ��ϵͳId
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			 >0 ������λID
	*/
	UINT16_S GetSendRelevanceMaskId(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId);

	/*
	* ���������� ��ȡ�����豸�ܸ���
	* ����˵���� const UINT8 sourceSystemId Դϵͳ����  
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �豸��ǰ����
	*/
	UINT8_S GetReceiveCommTargetNum(const UINT8_S sourceSystemId);

	/*
	* ���������� ��ȡ����ĳ���豸���±�
	* ����˵���� const UINT8 sourceSystemType Դϵͳ����  
	*			 const UINT16_S sourceSystemId ԴĿ��ID
	* ����ֵ  �� COMM_CI_SUM_MAX: ��ȡ����ʧ��
	*			>0: ͨѶ������±�
	*/
	UINT8_S GetReceiveCommTargetIndex(const UINT8_S sourceSystemType,const UINT16_S sourceSystemId);

	/*
	* ���������� ��ȡָ�����������±��Ӧ����λ�±�
	* ����˵���� const UINT16 bufIndex, �����±�
	*			 const UINT8_S sourceSystemType, Դϵͳ����
	*			 const UINT16_S sourceSystemId ԴϵͳID
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��λID     
	*/
	UINT16_S GetReceiveMaskId(const UINT16_S bufIndex,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId);

	/*
	* ���������� ��ȡָ��ID��λ������
	* ����˵���� const UINT16 maskId,��λID
	*			 const UINT8_S sourceSystemType, Դϵͳ����
	*			 const UINT16_S sourceSystemId ԴϵͳID
	* ����ֵ  �� CI_TO_ZC_MASK_SUM_MAX: ��ȡ����ʧ��
	*			 >0 ���������ɹ�
	*/
	UINT16_S GetReceiveMaskBufIndex(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId);

	/*
	* ���������� ��ȡָ��ID��λ����λ����
	* ����˵���� const UINT16 maskId,��λID
	*			const UINT8_S sourceSystemType, Դϵͳ����
	*			const UINT16_S sourceSystemId ԴϵͳID
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			 >0 ��λ������Ϣ
	*/
	UINT8_S GetReceiveMaskType(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId);

	/*
	* ���������� ��ȡָ��ID��λ���豸����
	* ����˵���� const UINT16 maskId,��λID
	*			 const UINT8_S sourceSystemType, Դϵͳ����
	*			 const UINT16_S sourceSystemId ԴϵͳID
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			 >0:�豸������Ϣ
	*/
	UINT8_S GetReceiveDeviceType(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId);

	/*
	* ���������� ��ȡָ��ID��λ���豸����
	* ����˵���� const UINT16 maskId,��λID
	*			 const UINT8_S sourceSystemType, Դϵͳ����
	*			 const UINT16_S sourceSystemId ԴϵͳID
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			 >0 �豸����
	*/
	UINT8_S GetReceiveDeviceSum(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId);

	/*
	* ���������� ��ȡָ��ID��λ���豸ID����
	* ����˵���� const UINT16 maskId,��λID
	*			 const UINT8_S sourceSystemType, Դϵͳ����
	*			 const UINT16_S sourceSystemId ԴϵͳID
	*			 const UINT8_S bufSize,�����С
	*			 UINT16_S deviceIdBuff[],�������
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			 1: ��ȡ���ݳɹ�
	*/
	UINT8_S GetReceiveDeviceIdBuff(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId,const UINT8_S bufSize,UINT16_S deviceIdBuff[]);

	/*
	* ���������� ��ȡָ��ID��λ�Ĺ�����λId
	* ����˵���� const UINT16 maskId,��λID
	*			 const UINT8_S sourceSystemType, Դϵͳ����
	*			 const UINT16_S sourceSystemId ԴϵͳID
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			 >0 ������λID
	*/
	UINT16_S GetReceiveRelevanceMaskId(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId);
	
	/*
	* ���������� ��ȡ��ZC�������źŻ���ѹ�����źŻ���
	* ����˵���� ��
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ����
	*/
	UINT16_S GetMaskOfSignalCorssNum(void);

	/*
	* ���������� ��ȡ��ZC�������źŻ���ѹ�����źŻ�Id��Ϣ
	* ����˵���� const UINT16 buffSize,buff��С
	*            UINT16_S signalIdBuff[],�źŻ�IdBuff
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ���ݳɹ�
	*/
	UINT8_S GetMaskOfSignalCorssIdBuff(const UINT16_S buffSize,UINT16_S signalIdBuff[]);

	/*
	* ���������� ��ȡ��ZC�������źŻ����������źŻ���
	* ����˵���� ��
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ����
	*/
	UINT16_S GetMaskOfSignalLightOffNum(void);

	/*
	* ���������� ��ȡ��ZC�������źŻ����������źŻ�Id��Ϣ
	* ����˵���� const UINT16 buffSize,buff��С
	*            UINT16_S signalIdBuff[],�źŻ�IdBuff
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ���ݳɹ�
	*/
	UINT8_S GetMaskOfSignalLightOffIdBuff(const UINT16_S buffSize,UINT16_S signalIdBuff[]);

#ifdef __cplusplus
}
#endif

#endif
