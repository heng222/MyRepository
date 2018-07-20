/************************************************************************
*
* 文件名   ：  SysTimeData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  ZC系统校时管理
* 备  注   ：  无
*
************************************************************************/
#include "SysTimeData.h"
#include "SysConfigData.h"
#include "../../Common/MemSet.h"
#include "math.h"
#include "SysStatusData.h"

LocalTimeInfoStruct gLocalTimeInfoStru;                  /*本地时间信息结构*/

/*
* 功能描述： 本地ZC时间数据结构
* 参数说明： void    
* 返回值  ： NULL: 获取数据失败
*			 !NULL: 本地ZC时间数据结构
*/
LocalTimeInfoStruct* LocalTimeInfoData(void)
{
	return &gLocalTimeInfoStru;
}

/*
* 功能描述： 获取ZC初始化校时成功标志
* 参数说明： 无    
* 返回值  ： 0: 获取数据失败
*			>0: ZC初始化校时成功标志
*/
UINT8_S GetNtpTimeSuccFlag(void)
{
	return gLocalTimeInfoStru.NtpTimeSuccFlag;
}

/*
* 功能描述： 设置ZC初始化校时成功标志
* 参数说明： UINT8 succFlag,成功标志    
* 返回值  ： 无
*/
void SetNtpTimeSuccFlag(UINT8_S succFlag)
{
	if ((ZC_INIT_NTP_TIME_SUCC_FLAG_SET == succFlag) || (ZC_INIT_NTP_TIME_SUCC_FLAG_UNSET == succFlag))
	{
		gLocalTimeInfoStru.NtpTimeSuccFlag = succFlag;
	} 
	else
	{
        /*不处理*/
	}
}

/*
* 功能描述： 获取ZC本地时间
* 参数说明： 无    
* 返回值  ： 0: 获取数据失败
*			>0: ZC本地时间
*/
UINT32_S GetLocalNtpTime(void)
{
	return gLocalTimeInfoStru.LocalNtpTime;
}

/*
* 功能描述： 设置ZC本地时间
* 参数说明： UINT32 localTime,本地时间    
* 返回值  ： 无
*/
void SetLocalNtpTime(UINT32_S localTime)
{
	gLocalTimeInfoStru.LocalNtpTime = localTime;
}

/*
* 功能描述： 获取发送NTP校时请求时的本地时间
* 参数说明： 无    
* 返回值  ： 0: 获取数据失败
*			>0: 发送NTP校时请求时的本地时间
*/
UINT32_S GetNtpApplyOfLocalTime(void)
{
	return gLocalTimeInfoStru.NtpApplyOfLocalTime;
}

/*
* 功能描述： 设置发送NTP校时请求时的本地时间
* 参数说明： UINT32 localTime,本地时间    
* 返回值  ： 无
*/
void SetNtpApplyOfLocalTime(UINT32_S localTime)
{
	gLocalTimeInfoStru.NtpApplyOfLocalTime = localTime;
}

/*
* 功能描述： 获取工作模式
* 参数说明： 无    
* 返回值  ： 0: 获取数据失败
*			>0: 工作模式
*/
UINT8_S GetWorkMode(void)
{
	return gLocalTimeInfoStru.WorkMode;
}

/*
* 功能描述： 设置工作模式
* 参数说明： UINT8 workMode,工作模式    
* 返回值  ： 无
*/
void SetWorkMode(UINT8_S workMode)
{
	gLocalTimeInfoStru.WorkMode = workMode;
}

/*
* 功能描述： 获取系统时钟的准确度
* 参数说明： 无    
* 返回值  ： 0: 获取数据失败
*			>0: 系统时钟的准确度
*/
UINT8_S GetStratum(void)
{
	return gLocalTimeInfoStru.Stratum;
}

/*
* 功能描述： 设置系统时钟的准确度
* 参数说明： UINT8 stratum,系统时钟的准确度    
* 返回值  ： 无
*/
void SetStratum(UINT8_S stratum)
{
	gLocalTimeInfoStru.Stratum = stratum;
}

/*
* 功能描述： 获取系统时钟最后一次被设定或更新的时间
* 参数说明： 无    
* 返回值  ： 0: 获取数据失败
*			>0: 系统时钟最后一次被设定或更新的时间
*/
NTPTimeStruct* GetReferenceTimestamp(void)
{
	return &gLocalTimeInfoStru.ReferenceTimestamp;
}

/*
* 功能描述： 设置系统时钟最后一次被设定或更新的时间
* 参数说明： NTPTimeStruct ReferenceTimestamp,系统时钟最后一次被设定或更新的时间    
* 返回值  ： 无
*/
void SetReferenceTimestamp(NTPTimeStruct referenceTimestamp)
{
	gLocalTimeInfoStru.ReferenceTimestamp.Integer = referenceTimestamp.Integer;
	gLocalTimeInfoStru.ReferenceTimestamp.Fractional = referenceTimestamp.Fractional;
}

/*
* 功能描述： 获取服务器收到的请求报文离开本地的本地时间
* 参数说明： 无    
* 返回值  ： 0: 获取数据失败
*			>0: 服务器收到的请求报文离开本地的本地时间
*/
NTPTimeStruct* GetOriginateTimestamp(void)
{
	return &gLocalTimeInfoStru.OriginateTimestamp;
}

/*
* 功能描述： 设置服务器收到的请求报文离开本地的本地时间
* 参数说明： NTPTimeStruct OriginateTimestamp,服务器收到的请求报文离开本地的本地时间    
* 返回值  ： 无
*/
void SetOriginateTimestamp(NTPTimeStruct originateTimestamp)
{
	gLocalTimeInfoStru.OriginateTimestamp.Integer = originateTimestamp.Integer;
	gLocalTimeInfoStru.OriginateTimestamp.Fractional = originateTimestamp.Fractional;
}

/*
* 功能描述： 获取应答报文离开服务器的服务器时间
* 参数说明： 无    
* 返回值  ： 0: 获取数据失败
*			>0: 应答报文离开服务器的服务器时间
*/
NTPTimeStruct* GetTransmitTimestamp(void)
{
	return &gLocalTimeInfoStru.TransmitTimestamp;
}

/*
* 功能描述： 设置应答报文离开服务器的服务器时间
* 参数说明： NTPTimeStruct transmitTimestamp,应答报文离开服务器的服务器时间    
* 返回值  ： 无
*/
void SetTransmitTimestamp(NTPTimeStruct transmitTimestamp)
{
	gLocalTimeInfoStru.TransmitTimestamp.Integer = transmitTimestamp.Integer;
	gLocalTimeInfoStru.TransmitTimestamp.Fractional = transmitTimestamp.Fractional;
}

/*
* 功能描述： 获取请求报文到达服务器的服务器时间
* 参数说明： 无    
* 返回值  ： 0: 获取数据失败
*			>0: 请求报文到达服务器的服务器时间
*/
NTPTimeStruct* GetReceiveTimestamp(void)
{
	return &gLocalTimeInfoStru.ReceiveTimestamp;
}

/*
* 功能描述： 设置请求报文到达服务器的服务器时间
* 参数说明： NTPTimeStruct receiveTimestamp,请求报文到达服务器的服务器时间    
* 返回值  ： 无
*/
void SetReceiveTimestamp(NTPTimeStruct receiveTimestamp)
{
	gLocalTimeInfoStru.ReceiveTimestamp.Integer = receiveTimestamp.Integer;
	gLocalTimeInfoStru.ReceiveTimestamp.Fractional = receiveTimestamp.Fractional;
}

/*
* 功能描述： NTP校时函数
* 参数说明： 无    
* 返回值  ： 1：成功
*            0：失败
*/
UINT8_S CalculateNtpTime(void)
{
	UINT32_S t1 = DEFAULT_ZERO;                           /*请求报文发送时间*/
	UINT32_S t2 = DEFAULT_ZERO;                           /*请求报文到达服务器时间*/
	UINT32_S t3 = DEFAULT_ZERO;                           /*服务器发送应答报文时间*/
	UINT32_S t4 = DEFAULT_ZERO;                           /*收到应答报文时的本地时间*/
	INT32_S t2Subt1 = 0;                       /*T2减T1*/
	INT32_S t3Subt4 = 0;                       /*T3减T4*/
	INT32_S t2SubT1Divide2 = 0;                /*T2减T1再除2*/
	INT32_S t3SubT4Divide2 = 0;                /*T3减T4再除2*/
	INT32_S waitRecTime = 0;                   /*等待应答报文的时长*/
	UINT8_S  rtnValue = DEFAULT_ZERO; 
	UINT32_S localTime = DEFAULT_ZERO;
	UINT8_S ntpTimeZoneDiff = DEFAULT_ZERO;
	UINT32_S ntpApplyOfLocalTime = DEFAULT_ZERO;
	NTPTimeStruct *pTempNtpTimeStru = NULL;
	INT32_S diffTime = 0;

	/*获取数据*/
	localTime = GetLocalNtpTime();
	ntpTimeZoneDiff = GetNtpTimeZoneDiff();
	ntpApplyOfLocalTime = GetNtpApplyOfLocalTime();

	/*计算从发送请求开始，等待应答报文的时长（单位：s）*/
	waitRecTime = (INT32_S)(((localTime - (3600U * ntpTimeZoneDiff)) + TIME_DIFF_1970) - ntpApplyOfLocalTime);
	
    if((waitRecTime < TIME_MAX_WAIT_REC) && (waitRecTime >= 0))
    {
		/*获取收到应答报文时的本地时间，并转换为ntp时间格式*/
		t4 = (localTime - (3600U * ntpTimeZoneDiff)) + TIME_DIFF_1970;
		
		/*解析应答报文，得到请求报文发送时间，到达服务器时间，服务器发送应答报文时间*/
		pTempNtpTimeStru = GetOriginateTimestamp();
		t1 = pTempNtpTimeStru->Integer;
		

		pTempNtpTimeStru = GetReceiveTimestamp();
		t2 = pTempNtpTimeStru->Integer;


		pTempNtpTimeStru = GetTransmitTimestamp();
		t3 = pTempNtpTimeStru->Integer;


		if(t1 == ntpApplyOfLocalTime)
		{
			/*如果收到的应答报文中的请求时间是当前最近一次发送报文的时间，说明该应答是对当前请求的应答，则计算本地时间与服务器时间的偏差*/
			t2Subt1 = t2 - t1;
			t3Subt4 = t3 - t4;
			t2SubT1Divide2 = t2Subt1/2;
			t3SubT4Divide2 = t3Subt4/2;
			diffTime = t2SubT1Divide2 + t3SubT4Divide2;

			/*判断是否需要校时*/
			if ((UINT32_S)(abs(diffTime)) > GetNtpCheckDiffTime())
			{
				/*报文里时间差值大于规定值30s时更新本地时钟，并在记录系统记录*/
				localTime = (UINT32_S)(localTime + (UINT32_S)diffTime);

				/*判断是否大于了系统最大时间*/
				if (localTime >= 0x7C55F200U)
				{
					localTime = DEFAULT_ZERO;
				} 
				else
				{
                    /*不处理*/
				}

				SetLocalNtpTime(localTime);
			}
			else
			{
				/*报文里时间差值小于等于规定值30s，退出*/
			}

			/*设置已成功校时标志*/
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
		/*等待应答超时*/
		rtnValue = RETURN_ERROR;
	}
	
	return rtnValue;
}


/*
* 功能描述： 初始化ZC系统时间
* 参数说明： 无   
* 返回值  ： 无
*/
void InitSysTimeData(void)
{
	/*初始化*/
	MemorySet(&gLocalTimeInfoStru,sizeof(LocalTimeInfoStruct),DEFAULT_ZERO,sizeof(LocalTimeInfoStruct));

	SetNtpTimeSuccFlag(ZC_INIT_NTP_TIME_SUCC_FLAG_UNSET);

	/*设置Leap indicator(2),version(3),mode(3)*/
	SetWorkMode(27U);
}

/*
* 功能描述： 累加ZC时间
* 参数说明： 无   
* 返回值  ： 无
*/
void AddLocalTime(void)
{
	UINT8_S remainder = DEFAULT_ZERO;

	/*对本地周期求余*/
	remainder = (UINT8_S)(GetZcCycle() % 5U);

	/*判断是否符合累加条件*/
	if((DEFAULT_ZERO == remainder)
		&& (0U != GetZcCycle()))
	{
		/*说明符合累加条件，将本地时间加2*/
		SetLocalNtpTime(GetLocalNtpTime() + 2U);
	}
	else
	{
		/*说明不符合累加条件*/
	}
}
