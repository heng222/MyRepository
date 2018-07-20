/************************************************************************
*
* 文件名   ：  SysConfigData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  获取ZC系统配置数据管理
* 备  注   ：  无
*
************************************************************************/
#ifndef SYS_CONFIG_DATA_H_
#define SYS_CONFIG_DATA_H_

#include "../../Common/CommonTypes.h"
#include "SysDefine.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*定义ZC子系统配置信息*/
	typedef struct ZcSubsystemConfigDataStruct
	{
		UINT32_S  SignalLightLength;                         /*定义运营的信号机亮灭灯需要的长度*/
		UINT16_S  LineMinTrainLength;                        /*定义线路最小可能车长*/
		UINT16_S  RetreatProtectDistance;                    /*定义列车最大退行防护距离*/
		UINT8_S SectionRedundantCycle;                       /*定义区段冗余判断周期数*/
		UINT8_S  ZCToATSCycleCycle;                          /*定义ZC向ATS汇报列车占用区段信息的周期数*/
		UINT8_S  ReverseCycle;                               /*定义列车CBTC折返周期数*/
		UINT8_S  ZCDowntimeFlag;                             /*定义ZC是否需要宕机标志*/
		UINT8_S ToCiSectionType;                             /*定义发送给CI的逻辑区段占用码位类型*/
		UINT16_S TrainAcrossSignalDis;                       /*定义列车跨压信号机判断距离*/
		UINT32_S NtpCheckDiffTime;                           /*定义NTP校时误差（ms）*/
		UINT16_S SendNtpApplyCycle;                          /*定义本系统与时钟服务器校时的周期*/
		UINT8_S ZcTraceRmTrainType;                          /*定义追踪不带后方检查标记RM列车方式*/
        UINT16_S LineMaxTrainLength;                         /*定义线路最大车长*/
	}ZcSubsystemConfigDataStruct;

	/*定义CBTC系统配置信息*/
	typedef struct TrainPerParameterStruct 
	{
		UINT16_S  TrainID;                                   /*列车ID*/
		UINT16_S  TrainType;                                 /*列车车型*/
		UINT16_S  TrainLength;                               /*列车长度*/
		UINT16_S  MaxLineDeclGradient;                       /*线路最大下坡坡度*/
		UINT16_S  MaxTrainTractionAcc;                       /*列车最大牵引加速度*/
	}TrainPerParameterStruct;

	typedef struct SystemConfigDataStruct
	{
		UINT16_S  LineMinOverlapLength;                        /*定义系统最小保护区段长度*/
		UINT16_S  LineMaxSpeed;                                /*定义线路最高限速*/
		UINT16_S  LineMaxTSRSpeed;                             /*定义临时限速最高限速*/
		UINT16_S  LineMaBackDistance;                          /*定义安全防护距离*/
		UINT8_S  NtpTimeZoneDiff;                              /*NTP校时时区差(小时)*/
		UINT8_S  TrainAtpCommCycle;                            /*定义与车载ATP通信故障周期数*/
		UINT8_S  NZcCommCycle;                                 /*定义与相邻ZC通信故障周期数*/
		UINT8_S  CICommCycle;                                  /*定义与CI通信故障周期数*/
		UINT8_S  ATSCommCycle;                                 /*定义与ATS通信故障周期数*/	
		TrainPerParameterStruct  TrainPerParameterStruBuff[LINE_MAX_TRAIN_ID];/*本线路列车性能参数结构体*/
		UINT8_S LinkLogicDirUpAndDown;                      /*ZC内部逻辑方向与CI上下行方向之间的关系*/
	}SystemConfigDataStruct;

	/*本地ZC配置属性数据结构*/
	typedef struct LocalZcConfigDataStruct
	{
		UINT16_S  wZCID;                                      /*ZC的ID号*/
	}LocalZcConfigDataStruct;

	/*
	* 功能描述： 获取本地ZC的id
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 本地ZCid      
	*/
	UINT16_S GetLocalZcId(void);

	/*
	* 功能描述： 获取运营的信号机亮灭灯需要的长度
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 运营的信号机亮灭灯需要的长度      
	*/
	UINT32_S GetSignalLightLength(void);

	/*
	* 功能描述： 获取线路最小可能车长
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 线路最小可能车长      
	*/
	UINT16_S GetLineMinTrainLength(void);

	/*
	* 功能描述： 获取列车最大退行防护距离
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 列车最大退行防护距离      
	*/
	UINT16_S GetRetreatProtectDistance(void);

	/*
	* 功能描述： 获取区段冗余判断周期数
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 区段冗余判断周期数     
	*/
	UINT16_S GetSectionRedundantCycle(void);

	/*
	* 功能描述： 获取NTP校时时区差
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: NTP校时时区差     
	*/
	UINT8_S GetNtpTimeZoneDiff(void);

	/*
	* 功能描述： 获取ZC向ATS汇报列车占用区段信息的周期数
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: ZC向ATS汇报列车占用区段信息的周期数     
	*/
	UINT8_S GetZCToATSCycleCycle(void);

	/*
	* 功能描述： 获取列车CBTC折返周期数
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 列车CBTC折返周期数    
	*/
	UINT8_S GetReverseCycle(void);

	/*
	* 功能描述： 获取ZC是否需要宕机标志
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: ZC是否需要宕机标志    
	*/
	UINT8_S GetZCDowntimeFlag(void);

	/*
	* 功能描述： 获取发送给CI的逻辑区段占用码位类型
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 发送给CI的逻辑区段占用码位类型    
	*/
	UINT8_S GetToCiSectionType(void);

	/*
	* 功能描述： 获取列车跨压信号机判断距离
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 列车跨压信号机判断距离   
	*/
	UINT16_S GetTrainAcrossSignalDis(void);

	/*
	* 功能描述： 获取NTP校时误差时间
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: NTP校时误差时间   
	*/
	UINT32_S GetNtpCheckDiffTime(void);

	/*
	* 功能描述： 获取校时周期
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 校时周期   
	*/
	UINT16_S GetSendNtpApplyCycle(void);

	/*
	* 功能描述： 获取系统最小保护区段长度
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 系统最小保护区段长度   
	*/
	UINT16_S GetLineMinOverlapLength(void);

	/*
	* 功能描述： 获取系线路最高限速
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 线路最高限速   
	*/
	UINT16_S GetLineMaxSpeed(void);

	/*
	* 功能描述： 获取临时限速最高限速
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 临时限速最高限速   
	*/
	UINT16_S GetLineMaxTSRSpeed(void);

	/*
	* 功能描述： 获取安全防护距离
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 安全防护距离   
	*/
	UINT16_S GetLineMaBackDistance(void);

	/*
	* 功能描述： 获取与车载ATP通信故障周期数
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 与车载ATP通信故障周期数   
	*/
	UINT8_S GetTrainAtpCommCycle(void);

	/*
	* 功能描述： 获取与相邻ZC通信故障周期数
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 与相邻ZC通信故障周期数  
	*/
	UINT8_S GetNZcCommCycle(void);

	/*
	* 功能描述： 获取与CI通信故障周期数
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 与CI通信故障周期数   
	*/
	UINT8_S GetCICommCycle(void);

	/*
	* 功能描述： 获取与ATS通信故障周期数
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 与ATS通信故障周期数   
	*/
	UINT8_S GetATSCommCycle(void);

	/*
	* 功能描述： 获取ZC内部逻辑方向与CI上下行方向之间的关系
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: ZC内部逻辑方向与CI上下行方向之间的关系   
	*/
	UINT8_S GetLinkLogicDirUpAndDown(void);

	/*
	* 功能描述： 获取指定ZcId对应的列车类型
	* 参数说明： const UINT16 trainId 列车Id    
	* 返回值  ： 0: 获取数据失败
	*			>0: 列车类型   
	*/
	UINT16_S GetLineTrainType(const UINT16_S trainId);

	/*
	* 功能描述： 获取指定ZcId对应的列车车长
	* 参数说明： const UINT16 trainId 列车Id    
	* 返回值  ： 0: 获取数据失败
	*			>0: 列车车长   
	*/
	UINT16_S GetTrainLength(const UINT16_S trainId);

	/*
	* 功能描述： 获取指定ZcId对应的列车线路最大下坡坡度
	* 参数说明： const UINT16 trainId 列车Id    
	* 返回值  ： 0: 获取数据失败
	*			>0: 列车线路最大下坡坡度   
	*/
	UINT16_S GetMaxLineDeclGradient(const UINT16_S trainId);

	/*
	* 功能描述： 获取指定ZcId对应的列车最大牵引加速度
	* 参数说明： const UINT16 trainId 列车Id    
	* 返回值  ： 0: 获取数据失败
	*			>0: 列车最大牵引加速度  
	*/
	UINT16_S GetMaxTrainTractionAcc(const UINT16_S trainId);

	/*
	* 功能描述： 追踪不带后方检查标记RM列车方式
	* 参数说明:  无
	* 返回值  :  UINT8_NULL: 获取数据失败
	*			<UINT8_NULL: 追踪不带后方检查标记RM列车方式
	*/ 
	UINT8_S GetZcTraceRmTrainType(void);

   /*
	* 功能描述： 获取线路上最大车长
	* 参数说明:  无
	* 返回值  :  线路列车最大长度
	*/ 
	UINT16_S GetLineMaxTrainLength(void);

   /*
	* 功能描述： 设置线路上最大车长
	* 参数说明:  const UINT16_S trainMaxLen  线路列车最大长度
	* 返回值  :  无
	*/ 
	void SetLineMaxTrainLength(const UINT16_S trainMaxLen);

#ifdef __cplusplus
}
#endif

#endif
