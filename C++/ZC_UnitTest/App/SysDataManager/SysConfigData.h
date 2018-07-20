/************************************************************************
*
* �ļ���   ��  SysConfigData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��ȡZCϵͳ�������ݹ���
* ��  ע   ��  ��
*
************************************************************************/
#ifndef SYS_CONFIG_DATA_H_
#define SYS_CONFIG_DATA_H_

#include "../../Common/CommonTypes.h"
#include "SysDefine.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*����ZC��ϵͳ������Ϣ*/
	typedef struct ZcSubsystemConfigDataStruct
	{
		UINT32_S  SignalLightLength;                         /*������Ӫ���źŻ��������Ҫ�ĳ���*/
		UINT16_S  LineMinTrainLength;                        /*������·��С���ܳ���*/
		UINT16_S  RetreatProtectDistance;                    /*�����г�������з�������*/
		UINT8_S SectionRedundantCycle;                       /*�������������ж�������*/
		UINT8_S  ZCToATSCycleCycle;                          /*����ZC��ATS�㱨�г�ռ��������Ϣ��������*/
		UINT8_S  ReverseCycle;                               /*�����г�CBTC�۷�������*/
		UINT8_S  ZCDowntimeFlag;                             /*����ZC�Ƿ���Ҫ崻���־*/
		UINT8_S ToCiSectionType;                             /*���巢�͸�CI���߼�����ռ����λ����*/
		UINT16_S TrainAcrossSignalDis;                       /*�����г���ѹ�źŻ��жϾ���*/
		UINT32_S NtpCheckDiffTime;                           /*����NTPУʱ��ms��*/
		UINT16_S SendNtpApplyCycle;                          /*���屾ϵͳ��ʱ�ӷ�����Уʱ������*/
		UINT8_S ZcTraceRmTrainType;                          /*����׷�ٲ����󷽼����RM�г���ʽ*/
        UINT16_S LineMaxTrainLength;                         /*������·��󳵳�*/
	}ZcSubsystemConfigDataStruct;

	/*����CBTCϵͳ������Ϣ*/
	typedef struct TrainPerParameterStruct 
	{
		UINT16_S  TrainID;                                   /*�г�ID*/
		UINT16_S  TrainType;                                 /*�г�����*/
		UINT16_S  TrainLength;                               /*�г�����*/
		UINT16_S  MaxLineDeclGradient;                       /*��·��������¶�*/
		UINT16_S  MaxTrainTractionAcc;                       /*�г����ǣ�����ٶ�*/
	}TrainPerParameterStruct;

	typedef struct SystemConfigDataStruct
	{
		UINT16_S  LineMinOverlapLength;                        /*����ϵͳ��С�������γ���*/
		UINT16_S  LineMaxSpeed;                                /*������·�������*/
		UINT16_S  LineMaxTSRSpeed;                             /*������ʱ�����������*/
		UINT16_S  LineMaBackDistance;                          /*���尲ȫ��������*/
		UINT8_S  NtpTimeZoneDiff;                              /*NTPУʱʱ����(Сʱ)*/
		UINT8_S  TrainAtpCommCycle;                            /*�����복��ATPͨ�Ź���������*/
		UINT8_S  NZcCommCycle;                                 /*����������ZCͨ�Ź���������*/
		UINT8_S  CICommCycle;                                  /*������CIͨ�Ź���������*/
		UINT8_S  ATSCommCycle;                                 /*������ATSͨ�Ź���������*/	
		TrainPerParameterStruct  TrainPerParameterStruBuff[LINE_MAX_TRAIN_ID];/*����·�г����ܲ����ṹ��*/
		UINT8_S LinkLogicDirUpAndDown;                      /*ZC�ڲ��߼�������CI�����з���֮��Ĺ�ϵ*/
	}SystemConfigDataStruct;

	/*����ZC�����������ݽṹ*/
	typedef struct LocalZcConfigDataStruct
	{
		UINT16_S  wZCID;                                      /*ZC��ID��*/
	}LocalZcConfigDataStruct;

	/*
	* ���������� ��ȡ����ZC��id
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ����ZCid      
	*/
	UINT16_S GetLocalZcId(void);

	/*
	* ���������� ��ȡ��Ӫ���źŻ��������Ҫ�ĳ���
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��Ӫ���źŻ��������Ҫ�ĳ���      
	*/
	UINT32_S GetSignalLightLength(void);

	/*
	* ���������� ��ȡ��·��С���ܳ���
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��·��С���ܳ���      
	*/
	UINT16_S GetLineMinTrainLength(void);

	/*
	* ���������� ��ȡ�г�������з�������
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �г�������з�������      
	*/
	UINT16_S GetRetreatProtectDistance(void);

	/*
	* ���������� ��ȡ���������ж�������
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ���������ж�������     
	*/
	UINT16_S GetSectionRedundantCycle(void);

	/*
	* ���������� ��ȡNTPУʱʱ����
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: NTPУʱʱ����     
	*/
	UINT8_S GetNtpTimeZoneDiff(void);

	/*
	* ���������� ��ȡZC��ATS�㱨�г�ռ��������Ϣ��������
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ZC��ATS�㱨�г�ռ��������Ϣ��������     
	*/
	UINT8_S GetZCToATSCycleCycle(void);

	/*
	* ���������� ��ȡ�г�CBTC�۷�������
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �г�CBTC�۷�������    
	*/
	UINT8_S GetReverseCycle(void);

	/*
	* ���������� ��ȡZC�Ƿ���Ҫ崻���־
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ZC�Ƿ���Ҫ崻���־    
	*/
	UINT8_S GetZCDowntimeFlag(void);

	/*
	* ���������� ��ȡ���͸�CI���߼�����ռ����λ����
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ���͸�CI���߼�����ռ����λ����    
	*/
	UINT8_S GetToCiSectionType(void);

	/*
	* ���������� ��ȡ�г���ѹ�źŻ��жϾ���
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �г���ѹ�źŻ��жϾ���   
	*/
	UINT16_S GetTrainAcrossSignalDis(void);

	/*
	* ���������� ��ȡNTPУʱ���ʱ��
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: NTPУʱ���ʱ��   
	*/
	UINT32_S GetNtpCheckDiffTime(void);

	/*
	* ���������� ��ȡУʱ����
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: Уʱ����   
	*/
	UINT16_S GetSendNtpApplyCycle(void);

	/*
	* ���������� ��ȡϵͳ��С�������γ���
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ϵͳ��С�������γ���   
	*/
	UINT16_S GetLineMinOverlapLength(void);

	/*
	* ���������� ��ȡϵ��·�������
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��·�������   
	*/
	UINT16_S GetLineMaxSpeed(void);

	/*
	* ���������� ��ȡ��ʱ�����������
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ʱ�����������   
	*/
	UINT16_S GetLineMaxTSRSpeed(void);

	/*
	* ���������� ��ȡ��ȫ��������
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȫ��������   
	*/
	UINT16_S GetLineMaBackDistance(void);

	/*
	* ���������� ��ȡ�복��ATPͨ�Ź���������
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �복��ATPͨ�Ź���������   
	*/
	UINT8_S GetTrainAtpCommCycle(void);

	/*
	* ���������� ��ȡ������ZCͨ�Ź���������
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ������ZCͨ�Ź���������  
	*/
	UINT8_S GetNZcCommCycle(void);

	/*
	* ���������� ��ȡ��CIͨ�Ź���������
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��CIͨ�Ź���������   
	*/
	UINT8_S GetCICommCycle(void);

	/*
	* ���������� ��ȡ��ATSͨ�Ź���������
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ATSͨ�Ź���������   
	*/
	UINT8_S GetATSCommCycle(void);

	/*
	* ���������� ��ȡZC�ڲ��߼�������CI�����з���֮��Ĺ�ϵ
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ZC�ڲ��߼�������CI�����з���֮��Ĺ�ϵ   
	*/
	UINT8_S GetLinkLogicDirUpAndDown(void);

	/*
	* ���������� ��ȡָ��ZcId��Ӧ���г�����
	* ����˵���� const UINT16 trainId �г�Id    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �г�����   
	*/
	UINT16_S GetLineTrainType(const UINT16_S trainId);

	/*
	* ���������� ��ȡָ��ZcId��Ӧ���г�����
	* ����˵���� const UINT16 trainId �г�Id    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �г�����   
	*/
	UINT16_S GetTrainLength(const UINT16_S trainId);

	/*
	* ���������� ��ȡָ��ZcId��Ӧ���г���·��������¶�
	* ����˵���� const UINT16 trainId �г�Id    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �г���·��������¶�   
	*/
	UINT16_S GetMaxLineDeclGradient(const UINT16_S trainId);

	/*
	* ���������� ��ȡָ��ZcId��Ӧ���г����ǣ�����ٶ�
	* ����˵���� const UINT16 trainId �г�Id    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �г����ǣ�����ٶ�  
	*/
	UINT16_S GetMaxTrainTractionAcc(const UINT16_S trainId);

	/*
	* ���������� ׷�ٲ����󷽼����RM�г���ʽ
	* ����˵��:  ��
	* ����ֵ  :  UINT8_NULL: ��ȡ����ʧ��
	*			<UINT8_NULL: ׷�ٲ����󷽼����RM�г���ʽ
	*/ 
	UINT8_S GetZcTraceRmTrainType(void);

   /*
	* ���������� ��ȡ��·����󳵳�
	* ����˵��:  ��
	* ����ֵ  :  ��·�г���󳤶�
	*/ 
	UINT16_S GetLineMaxTrainLength(void);

   /*
	* ���������� ������·����󳵳�
	* ����˵��:  const UINT16_S trainMaxLen  ��·�г���󳤶�
	* ����ֵ  :  ��
	*/ 
	void SetLineMaxTrainLength(const UINT16_S trainMaxLen);

#ifdef __cplusplus
}
#endif

#endif
