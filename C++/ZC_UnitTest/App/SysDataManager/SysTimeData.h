/************************************************************************
*
* 文件名   ：  SysTimeData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  ZC系统校时管理
* 备  注   ：  无
*
************************************************************************/
#ifndef SYS_TIME_DATA_H_
#define SYS_TIME_DATA_H_

#include "../../Common/CommonTypes.h"
#include "SysDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*ntp时间格式*/
	typedef struct NTPTimeStruct
	{
		UINT32_S Integer;                                    /*秒数的整数部分*/
		UINT32_S Fractional;                                 /*秒数的小数部分*/
	}NTPTimeStruct;

	/*本地ZC时间数据结构*/
	typedef struct LocalTimeInfoStruct
	{
		UINT8_S NtpTimeSuccFlag;                             /*初始化校时成功标记*/		
		UINT8_S WorkMode;                                    /*闰秒数，版本号，工作模式*/		
		UINT8_S Stratum;                                     /*系统时钟的准确度*/
		UINT32_S LocalNtpTime;                               /*本地时间*/
		UINT32_S NtpApplyOfLocalTime;                        /*发送NTP校时请求时的本地时间*/
		NTPTimeStruct ReferenceTimestamp;                  /*系统时钟最后一次被设定或更新的时间*/	
		NTPTimeStruct OriginateTimestamp;                  /*服务器收到的请求报文离开本地的本地时间*/
		NTPTimeStruct ReceiveTimestamp;                    /*请求报文到达服务器的服务器时间*/
		NTPTimeStruct TransmitTimestamp;                   /*应答报文离开服务器的服务器时间*/
	}LocalTimeInfoStruct;

	/*
	* 功能描述： 本地ZC时间数据结构
	* 参数说明： void    
	* 返回值  ： NULL: 获取数据失败
	*			 !NULL: 本地ZC时间数据结构
	*/
	LocalTimeInfoStruct* LocalTimeInfoData(void);

	/*
	* 功能描述： 获取ZC初始化校时成功标志
	* 参数说明： 无    
	* 返回值  ： 0: 获取数据失败
	*			>0: ZC初始化校时成功标志
	*/
	UINT8_S GetNtpTimeSuccFlag(void);

	/*
	* 功能描述： 设置ZC初始化校时成功标志
	* 参数说明： UINT8 succFlag,成功标志    
	* 返回值  ： 无
	*/
	void SetNtpTimeSuccFlag(UINT8_S succFlag);

	/*
	* 功能描述： 获取ZC本地时间
	* 参数说明： 无    
	* 返回值  ： 0: 获取数据失败
	*			>0: ZC本地时间
	*/
	UINT32_S GetLocalNtpTime(void);

	/*
	* 功能描述： 设置ZC本地时间
	* 参数说明： UINT32 localTime,本地时间    
	* 返回值  ： 无
	*/
	void SetLocalNtpTime(UINT32_S localTime);

	/*
	* 功能描述： 获取发送NTP校时请求时的本地时间
	* 参数说明： 无    
	* 返回值  ： 0: 获取数据失败
	*			>0: 发送NTP校时请求时的本地时间
	*/
	UINT32_S GetNtpApplyOfLocalTime(void);

	/*
	* 功能描述： 设置发送NTP校时请求时的本地时间
	* 参数说明： UINT32 localTime,本地时间    
	* 返回值  ： 无
	*/
	void SetNtpApplyOfLocalTime(UINT32_S localTime);

	/*
	* 功能描述： 获取工作模式
	* 参数说明： 无    
	* 返回值  ： 0: 获取数据失败
	*			>0: 工作模式
	*/
	UINT8_S GetWorkMode(void);

	/*
	* 功能描述： 设置工作模式
	* 参数说明： UINT8 workMode,工作模式    
	* 返回值  ： 无
	*/
	void SetWorkMode(UINT8_S workMode);

	/*
	* 功能描述： 获取系统时钟的准确度
	* 参数说明： 无    
	* 返回值  ： 0: 获取数据失败
	*			>0: 系统时钟的准确度
	*/
	UINT8_S GetStratum(void);

	/*
	* 功能描述： 设置系统时钟的准确度
	* 参数说明： UINT8 stratum,系统时钟的准确度    
	* 返回值  ： 无
	*/
	void SetStratum(UINT8_S stratum);

	/*
	* 功能描述： 获取系统时钟最后一次被设定或更新的时间
	* 参数说明： 无    
	* 返回值  ： 0: 获取数据失败
	*			>0: 系统时钟最后一次被设定或更新的时间
	*/
	NTPTimeStruct* GetReferenceTimestamp(void);

	/*
	* 功能描述： 设置系统时钟最后一次被设定或更新的时间
	* 参数说明： NTPTimeStruct ReferenceTimestamp,系统时钟最后一次被设定或更新的时间    
	* 返回值  ： 无
	*/
	void SetReferenceTimestamp(NTPTimeStruct referenceTimestamp);

	/*
	* 功能描述： 获取服务器收到的请求报文离开本地的本地时间
	* 参数说明： 无    
	* 返回值  ： 0: 获取数据失败
	*			>0: 服务器收到的请求报文离开本地的本地时间
	*/
	NTPTimeStruct* GetOriginateTimestamp(void);

	/*
	* 功能描述： 设置服务器收到的请求报文离开本地的本地时间
	* 参数说明： NTPTimeStruct OriginateTimestamp,服务器收到的请求报文离开本地的本地时间    
	* 返回值  ： 无
	*/
	void SetOriginateTimestamp(NTPTimeStruct originateTimestamp);

	/*
	* 功能描述： 获取应答报文离开服务器的服务器时间
	* 参数说明： 无    
	* 返回值  ： 0: 获取数据失败
	*			>0: 应答报文离开服务器的服务器时间
	*/
	NTPTimeStruct* GetTransmitTimestamp(void);

	/*
	* 功能描述： 设置应答报文离开服务器的服务器时间
	* 参数说明： NTPTimeStruct transmitTimestamp,应答报文离开服务器的服务器时间    
	* 返回值  ： 无
	*/
	void SetTransmitTimestamp(NTPTimeStruct transmitTimestamp);

	/*
	* 功能描述： 获取请求报文到达服务器的服务器时间
	* 参数说明： 无    
	* 返回值  ： 0: 获取数据失败
	*			>0: 请求报文到达服务器的服务器时间
	*/
	NTPTimeStruct* GetReceiveTimestamp(void);

	/*
	* 功能描述： 设置请求报文到达服务器的服务器时间
	* 参数说明： NTPTimeStruct receiveTimestamp,请求报文到达服务器的服务器时间    
	* 返回值  ： 无
	*/
	void SetReceiveTimestamp(NTPTimeStruct receiveTimestamp);

	/*
	* 功能描述： NTP校时函数
	* 参数说明： 无    
	* 返回值  ： 1：成功
	*            0：失败
	*/
	UINT8_S CalculateNtpTime(void);

	/*
	* 功能描述： 初始化ZC子系统状态信息
	* 参数说明： 无   
	* 返回值  ： 无
	*/
	void InitSysTimeData(void);

	/*
	* 功能描述： 累加ZC时间
	* 参数说明： 无   
	* 返回值  ： 无
	*/
	void AddLocalTime(void);

#ifdef __cplusplus
}
#endif

#endif
