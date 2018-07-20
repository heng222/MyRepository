/************************************************************************
*
* �ļ���   ��  SysTimeData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ZCϵͳУʱ����
* ��  ע   ��  ��
*
************************************************************************/
#ifndef SYS_TIME_DATA_H_
#define SYS_TIME_DATA_H_

#include "../../Common/CommonTypes.h"
#include "SysDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*ntpʱ���ʽ*/
	typedef struct NTPTimeStruct
	{
		UINT32_S Integer;                                    /*��������������*/
		UINT32_S Fractional;                                 /*������С������*/
	}NTPTimeStruct;

	/*����ZCʱ�����ݽṹ*/
	typedef struct LocalTimeInfoStruct
	{
		UINT8_S NtpTimeSuccFlag;                             /*��ʼ��Уʱ�ɹ����*/		
		UINT8_S WorkMode;                                    /*���������汾�ţ�����ģʽ*/		
		UINT8_S Stratum;                                     /*ϵͳʱ�ӵ�׼ȷ��*/
		UINT32_S LocalNtpTime;                               /*����ʱ��*/
		UINT32_S NtpApplyOfLocalTime;                        /*����NTPУʱ����ʱ�ı���ʱ��*/
		NTPTimeStruct ReferenceTimestamp;                  /*ϵͳʱ�����һ�α��趨����µ�ʱ��*/	
		NTPTimeStruct OriginateTimestamp;                  /*�������յ����������뿪���صı���ʱ��*/
		NTPTimeStruct ReceiveTimestamp;                    /*�����ĵ���������ķ�����ʱ��*/
		NTPTimeStruct TransmitTimestamp;                   /*Ӧ�����뿪�������ķ�����ʱ��*/
	}LocalTimeInfoStruct;

	/*
	* ���������� ����ZCʱ�����ݽṹ
	* ����˵���� void    
	* ����ֵ  �� NULL: ��ȡ����ʧ��
	*			 !NULL: ����ZCʱ�����ݽṹ
	*/
	LocalTimeInfoStruct* LocalTimeInfoData(void);

	/*
	* ���������� ��ȡZC��ʼ��Уʱ�ɹ���־
	* ����˵���� ��    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ZC��ʼ��Уʱ�ɹ���־
	*/
	UINT8_S GetNtpTimeSuccFlag(void);

	/*
	* ���������� ����ZC��ʼ��Уʱ�ɹ���־
	* ����˵���� UINT8 succFlag,�ɹ���־    
	* ����ֵ  �� ��
	*/
	void SetNtpTimeSuccFlag(UINT8_S succFlag);

	/*
	* ���������� ��ȡZC����ʱ��
	* ����˵���� ��    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ZC����ʱ��
	*/
	UINT32_S GetLocalNtpTime(void);

	/*
	* ���������� ����ZC����ʱ��
	* ����˵���� UINT32 localTime,����ʱ��    
	* ����ֵ  �� ��
	*/
	void SetLocalNtpTime(UINT32_S localTime);

	/*
	* ���������� ��ȡ����NTPУʱ����ʱ�ı���ʱ��
	* ����˵���� ��    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ����NTPУʱ����ʱ�ı���ʱ��
	*/
	UINT32_S GetNtpApplyOfLocalTime(void);

	/*
	* ���������� ���÷���NTPУʱ����ʱ�ı���ʱ��
	* ����˵���� UINT32 localTime,����ʱ��    
	* ����ֵ  �� ��
	*/
	void SetNtpApplyOfLocalTime(UINT32_S localTime);

	/*
	* ���������� ��ȡ����ģʽ
	* ����˵���� ��    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ����ģʽ
	*/
	UINT8_S GetWorkMode(void);

	/*
	* ���������� ���ù���ģʽ
	* ����˵���� UINT8 workMode,����ģʽ    
	* ����ֵ  �� ��
	*/
	void SetWorkMode(UINT8_S workMode);

	/*
	* ���������� ��ȡϵͳʱ�ӵ�׼ȷ��
	* ����˵���� ��    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ϵͳʱ�ӵ�׼ȷ��
	*/
	UINT8_S GetStratum(void);

	/*
	* ���������� ����ϵͳʱ�ӵ�׼ȷ��
	* ����˵���� UINT8 stratum,ϵͳʱ�ӵ�׼ȷ��    
	* ����ֵ  �� ��
	*/
	void SetStratum(UINT8_S stratum);

	/*
	* ���������� ��ȡϵͳʱ�����һ�α��趨����µ�ʱ��
	* ����˵���� ��    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ϵͳʱ�����һ�α��趨����µ�ʱ��
	*/
	NTPTimeStruct* GetReferenceTimestamp(void);

	/*
	* ���������� ����ϵͳʱ�����һ�α��趨����µ�ʱ��
	* ����˵���� NTPTimeStruct ReferenceTimestamp,ϵͳʱ�����һ�α��趨����µ�ʱ��    
	* ����ֵ  �� ��
	*/
	void SetReferenceTimestamp(NTPTimeStruct referenceTimestamp);

	/*
	* ���������� ��ȡ�������յ����������뿪���صı���ʱ��
	* ����˵���� ��    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �������յ����������뿪���صı���ʱ��
	*/
	NTPTimeStruct* GetOriginateTimestamp(void);

	/*
	* ���������� ���÷������յ����������뿪���صı���ʱ��
	* ����˵���� NTPTimeStruct OriginateTimestamp,�������յ����������뿪���صı���ʱ��    
	* ����ֵ  �� ��
	*/
	void SetOriginateTimestamp(NTPTimeStruct originateTimestamp);

	/*
	* ���������� ��ȡӦ�����뿪�������ķ�����ʱ��
	* ����˵���� ��    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: Ӧ�����뿪�������ķ�����ʱ��
	*/
	NTPTimeStruct* GetTransmitTimestamp(void);

	/*
	* ���������� ����Ӧ�����뿪�������ķ�����ʱ��
	* ����˵���� NTPTimeStruct transmitTimestamp,Ӧ�����뿪�������ķ�����ʱ��    
	* ����ֵ  �� ��
	*/
	void SetTransmitTimestamp(NTPTimeStruct transmitTimestamp);

	/*
	* ���������� ��ȡ�����ĵ���������ķ�����ʱ��
	* ����˵���� ��    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �����ĵ���������ķ�����ʱ��
	*/
	NTPTimeStruct* GetReceiveTimestamp(void);

	/*
	* ���������� ���������ĵ���������ķ�����ʱ��
	* ����˵���� NTPTimeStruct receiveTimestamp,�����ĵ���������ķ�����ʱ��    
	* ����ֵ  �� ��
	*/
	void SetReceiveTimestamp(NTPTimeStruct receiveTimestamp);

	/*
	* ���������� NTPУʱ����
	* ����˵���� ��    
	* ����ֵ  �� 1���ɹ�
	*            0��ʧ��
	*/
	UINT8_S CalculateNtpTime(void);

	/*
	* ���������� ��ʼ��ZC��ϵͳ״̬��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� ��
	*/
	void InitSysTimeData(void);

	/*
	* ���������� �ۼ�ZCʱ��
	* ����˵���� ��   
	* ����ֵ  �� ��
	*/
	void AddLocalTime(void);

#ifdef __cplusplus
}
#endif

#endif
