/************************************************************************
*
* �ļ���   ��  SysTimeData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ZCϵͳУʱ����
* ��  ע   ��  ��
*
************************************************************************/
#include "SysTimeData.h"
#include "SysConfigData.h"
#include "../../Common/MemSet.h"
#include "math.h"
#include "SysStatusData.h"

LocalTimeInfoStruct gLocalTimeInfoStru;                  /*����ʱ����Ϣ�ṹ*/

/*
* ���������� ����ZCʱ�����ݽṹ
* ����˵���� void    
* ����ֵ  �� NULL: ��ȡ����ʧ��
*			 !NULL: ����ZCʱ�����ݽṹ
*/
LocalTimeInfoStruct* LocalTimeInfoData(void)
{
	return &gLocalTimeInfoStru;
}

/*
* ���������� ��ȡZC��ʼ��Уʱ�ɹ���־
* ����˵���� ��    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ZC��ʼ��Уʱ�ɹ���־
*/
UINT8_S GetNtpTimeSuccFlag(void)
{
	return gLocalTimeInfoStru.NtpTimeSuccFlag;
}

/*
* ���������� ����ZC��ʼ��Уʱ�ɹ���־
* ����˵���� UINT8 succFlag,�ɹ���־    
* ����ֵ  �� ��
*/
void SetNtpTimeSuccFlag(UINT8_S succFlag)
{
	if ((ZC_INIT_NTP_TIME_SUCC_FLAG_SET == succFlag) || (ZC_INIT_NTP_TIME_SUCC_FLAG_UNSET == succFlag))
	{
		gLocalTimeInfoStru.NtpTimeSuccFlag = succFlag;
	} 
	else
	{
        /*������*/
	}
}

/*
* ���������� ��ȡZC����ʱ��
* ����˵���� ��    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ZC����ʱ��
*/
UINT32_S GetLocalNtpTime(void)
{
	return gLocalTimeInfoStru.LocalNtpTime;
}

/*
* ���������� ����ZC����ʱ��
* ����˵���� UINT32 localTime,����ʱ��    
* ����ֵ  �� ��
*/
void SetLocalNtpTime(UINT32_S localTime)
{
	gLocalTimeInfoStru.LocalNtpTime = localTime;
}

/*
* ���������� ��ȡ����NTPУʱ����ʱ�ı���ʱ��
* ����˵���� ��    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����NTPУʱ����ʱ�ı���ʱ��
*/
UINT32_S GetNtpApplyOfLocalTime(void)
{
	return gLocalTimeInfoStru.NtpApplyOfLocalTime;
}

/*
* ���������� ���÷���NTPУʱ����ʱ�ı���ʱ��
* ����˵���� UINT32 localTime,����ʱ��    
* ����ֵ  �� ��
*/
void SetNtpApplyOfLocalTime(UINT32_S localTime)
{
	gLocalTimeInfoStru.NtpApplyOfLocalTime = localTime;
}

/*
* ���������� ��ȡ����ģʽ
* ����˵���� ��    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����ģʽ
*/
UINT8_S GetWorkMode(void)
{
	return gLocalTimeInfoStru.WorkMode;
}

/*
* ���������� ���ù���ģʽ
* ����˵���� UINT8 workMode,����ģʽ    
* ����ֵ  �� ��
*/
void SetWorkMode(UINT8_S workMode)
{
	gLocalTimeInfoStru.WorkMode = workMode;
}

/*
* ���������� ��ȡϵͳʱ�ӵ�׼ȷ��
* ����˵���� ��    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ϵͳʱ�ӵ�׼ȷ��
*/
UINT8_S GetStratum(void)
{
	return gLocalTimeInfoStru.Stratum;
}

/*
* ���������� ����ϵͳʱ�ӵ�׼ȷ��
* ����˵���� UINT8 stratum,ϵͳʱ�ӵ�׼ȷ��    
* ����ֵ  �� ��
*/
void SetStratum(UINT8_S stratum)
{
	gLocalTimeInfoStru.Stratum = stratum;
}

/*
* ���������� ��ȡϵͳʱ�����һ�α��趨����µ�ʱ��
* ����˵���� ��    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ϵͳʱ�����һ�α��趨����µ�ʱ��
*/
NTPTimeStruct* GetReferenceTimestamp(void)
{
	return &gLocalTimeInfoStru.ReferenceTimestamp;
}

/*
* ���������� ����ϵͳʱ�����һ�α��趨����µ�ʱ��
* ����˵���� NTPTimeStruct ReferenceTimestamp,ϵͳʱ�����һ�α��趨����µ�ʱ��    
* ����ֵ  �� ��
*/
void SetReferenceTimestamp(NTPTimeStruct referenceTimestamp)
{
	gLocalTimeInfoStru.ReferenceTimestamp.Integer = referenceTimestamp.Integer;
	gLocalTimeInfoStru.ReferenceTimestamp.Fractional = referenceTimestamp.Fractional;
}

/*
* ���������� ��ȡ�������յ����������뿪���صı���ʱ��
* ����˵���� ��    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �������յ����������뿪���صı���ʱ��
*/
NTPTimeStruct* GetOriginateTimestamp(void)
{
	return &gLocalTimeInfoStru.OriginateTimestamp;
}

/*
* ���������� ���÷������յ����������뿪���صı���ʱ��
* ����˵���� NTPTimeStruct OriginateTimestamp,�������յ����������뿪���صı���ʱ��    
* ����ֵ  �� ��
*/
void SetOriginateTimestamp(NTPTimeStruct originateTimestamp)
{
	gLocalTimeInfoStru.OriginateTimestamp.Integer = originateTimestamp.Integer;
	gLocalTimeInfoStru.OriginateTimestamp.Fractional = originateTimestamp.Fractional;
}

/*
* ���������� ��ȡӦ�����뿪�������ķ�����ʱ��
* ����˵���� ��    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: Ӧ�����뿪�������ķ�����ʱ��
*/
NTPTimeStruct* GetTransmitTimestamp(void)
{
	return &gLocalTimeInfoStru.TransmitTimestamp;
}

/*
* ���������� ����Ӧ�����뿪�������ķ�����ʱ��
* ����˵���� NTPTimeStruct transmitTimestamp,Ӧ�����뿪�������ķ�����ʱ��    
* ����ֵ  �� ��
*/
void SetTransmitTimestamp(NTPTimeStruct transmitTimestamp)
{
	gLocalTimeInfoStru.TransmitTimestamp.Integer = transmitTimestamp.Integer;
	gLocalTimeInfoStru.TransmitTimestamp.Fractional = transmitTimestamp.Fractional;
}

/*
* ���������� ��ȡ�����ĵ���������ķ�����ʱ��
* ����˵���� ��    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �����ĵ���������ķ�����ʱ��
*/
NTPTimeStruct* GetReceiveTimestamp(void)
{
	return &gLocalTimeInfoStru.ReceiveTimestamp;
}

/*
* ���������� ���������ĵ���������ķ�����ʱ��
* ����˵���� NTPTimeStruct receiveTimestamp,�����ĵ���������ķ�����ʱ��    
* ����ֵ  �� ��
*/
void SetReceiveTimestamp(NTPTimeStruct receiveTimestamp)
{
	gLocalTimeInfoStru.ReceiveTimestamp.Integer = receiveTimestamp.Integer;
	gLocalTimeInfoStru.ReceiveTimestamp.Fractional = receiveTimestamp.Fractional;
}

/*
* ���������� NTPУʱ����
* ����˵���� ��    
* ����ֵ  �� 1���ɹ�
*            0��ʧ��
*/
UINT8_S CalculateNtpTime(void)
{
	UINT32_S t1 = DEFAULT_ZERO;                           /*�����ķ���ʱ��*/
	UINT32_S t2 = DEFAULT_ZERO;                           /*�����ĵ��������ʱ��*/
	UINT32_S t3 = DEFAULT_ZERO;                           /*����������Ӧ����ʱ��*/
	UINT32_S t4 = DEFAULT_ZERO;                           /*�յ�Ӧ����ʱ�ı���ʱ��*/
	INT32_S t2Subt1 = 0;                       /*T2��T1*/
	INT32_S t3Subt4 = 0;                       /*T3��T4*/
	INT32_S t2SubT1Divide2 = 0;                /*T2��T1�ٳ�2*/
	INT32_S t3SubT4Divide2 = 0;                /*T3��T4�ٳ�2*/
	INT32_S waitRecTime = 0;                   /*�ȴ�Ӧ���ĵ�ʱ��*/
	UINT8_S  rtnValue = DEFAULT_ZERO; 
	UINT32_S localTime = DEFAULT_ZERO;
	UINT8_S ntpTimeZoneDiff = DEFAULT_ZERO;
	UINT32_S ntpApplyOfLocalTime = DEFAULT_ZERO;
	NTPTimeStruct *pTempNtpTimeStru = NULL;
	INT32_S diffTime = 0;

	/*��ȡ����*/
	localTime = GetLocalNtpTime();
	ntpTimeZoneDiff = GetNtpTimeZoneDiff();
	ntpApplyOfLocalTime = GetNtpApplyOfLocalTime();

	/*����ӷ�������ʼ���ȴ�Ӧ���ĵ�ʱ������λ��s��*/
	waitRecTime = (INT32_S)(((localTime - (3600U * ntpTimeZoneDiff)) + TIME_DIFF_1970) - ntpApplyOfLocalTime);
	
    if((waitRecTime < TIME_MAX_WAIT_REC) && (waitRecTime >= 0))
    {
		/*��ȡ�յ�Ӧ����ʱ�ı���ʱ�䣬��ת��Ϊntpʱ���ʽ*/
		t4 = (localTime - (3600U * ntpTimeZoneDiff)) + TIME_DIFF_1970;
		
		/*����Ӧ���ģ��õ������ķ���ʱ�䣬���������ʱ�䣬����������Ӧ����ʱ��*/
		pTempNtpTimeStru = GetOriginateTimestamp();
		t1 = pTempNtpTimeStru->Integer;
		

		pTempNtpTimeStru = GetReceiveTimestamp();
		t2 = pTempNtpTimeStru->Integer;


		pTempNtpTimeStru = GetTransmitTimestamp();
		t3 = pTempNtpTimeStru->Integer;


		if(t1 == ntpApplyOfLocalTime)
		{
			/*����յ���Ӧ�����е�����ʱ���ǵ�ǰ���һ�η��ͱ��ĵ�ʱ�䣬˵����Ӧ���ǶԵ�ǰ�����Ӧ������㱾��ʱ���������ʱ���ƫ��*/
			t2Subt1 = t2 - t1;
			t3Subt4 = t3 - t4;
			t2SubT1Divide2 = t2Subt1/2;
			t3SubT4Divide2 = t3Subt4/2;
			diffTime = t2SubT1Divide2 + t3SubT4Divide2;

			/*�ж��Ƿ���ҪУʱ*/
			if ((UINT32_S)(abs(diffTime)) > GetNtpCheckDiffTime())
			{
				/*������ʱ���ֵ���ڹ涨ֵ30sʱ���±���ʱ�ӣ����ڼ�¼ϵͳ��¼*/
				localTime = (UINT32_S)(localTime + (UINT32_S)diffTime);

				/*�ж��Ƿ������ϵͳ���ʱ��*/
				if (localTime >= 0x7C55F200U)
				{
					localTime = DEFAULT_ZERO;
				} 
				else
				{
                    /*������*/
				}

				SetLocalNtpTime(localTime);
			}
			else
			{
				/*������ʱ���ֵС�ڵ��ڹ涨ֵ30s���˳�*/
			}

			/*�����ѳɹ�Уʱ��־*/
			SetNtpTimeSuccFlag(ZC_INIT_NTP_TIME_SUCC_FLAG_SET);
			
			rtnValue = RETURN_SUCCESS;
		}
		else
		{
			rtnValue = RETURN_ERROR;
		}
	}
	else
	{
		/*�ȴ�Ӧ��ʱ*/
		rtnValue = RETURN_ERROR;
	}
	
	return rtnValue;
}


/*
* ���������� ��ʼ��ZCϵͳʱ��
* ����˵���� ��   
* ����ֵ  �� ��
*/
void InitSysTimeData(void)
{
	/*��ʼ��*/
	MemorySet(&gLocalTimeInfoStru,sizeof(LocalTimeInfoStruct),DEFAULT_ZERO,sizeof(LocalTimeInfoStruct));

	SetNtpTimeSuccFlag(ZC_INIT_NTP_TIME_SUCC_FLAG_UNSET);

	/*����Leap indicator(2),version(3),mode(3)*/
	SetWorkMode(27U);
}

/*
* ���������� �ۼ�ZCʱ��
* ����˵���� ��   
* ����ֵ  �� ��
*/
void AddLocalTime(void)
{
	UINT8_S remainder = DEFAULT_ZERO;

	/*�Ա�����������*/
	remainder = (UINT8_S)(GetZcCycle() % 5U);

	/*�ж��Ƿ�����ۼ�����*/
	if((DEFAULT_ZERO == remainder)
		&& (0U != GetZcCycle()))
	{
		/*˵�������ۼ�������������ʱ���2*/
		SetLocalNtpTime(GetLocalNtpTime() + 2U);
	}
	else
	{
		/*˵���������ۼ�����*/
	}
}
