/************************************************************************
*
* 文件名   ：  SignalConfigData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  信号机配置数据
* 备  注   ：  无
*
************************************************************************/
#ifndef SIGNAL_CONFIG_DATA_H_
#define SIGNAL_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "SignalDefine.h"

#ifdef __cplusplus
extern "C" {
#endif


	/*信号机配置数据结构体*/
	typedef struct SignalConfigDataStruct
	{
		UINT16_S SignalId;                      /*信号机ID*/
		UINT8_S BelongCiId;                     /*所属联锁ID*/
		UINT8_S BelongZcId;                     /*所属ZCID*/
		UINT8_S ChangeAttribute;                /*共管区域属性(标志是否属于某个共管区域)*/
		UINT8_S SignalType;                     /*信号机属性*/
		UINT8_S ProtectDir;                     /*信号机防护方向*/
		UINT8_S DefaultStatus;                  /*信号机默认状态*/
		UINT8_S LightOffType;                   /*信号机是否需要判断亮灭的类型*/
		UINT8_S CbtcLightOffType;               /*CBTC类型列车对应信号机的亮灭类型*/
		UINT8_S CrossType;                      /*信号机是否需要判断跨压状态类型*/
		UINT8_S CrashType;                      /*信号机是否需要判断闯过信号机状态类型*/
	} SignalConfigDataStruct;

	/*
	* 功能描述： 获取信号机管理总数
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 信号机当前总数
	*/
	UINT16_S GetSignalSum(void);

	/*
	* 功能描述： 获取指定数组下标对应的信号机ID
	* 参数说明： const UINT16 bufIndex, 数组下标    
	* 返回值  ： 0: 获取数据失败
	*			>0: 信号机ID      
	*/
	UINT16_S GetSignalId(const UINT16_S bufIndex);

	/*
	* 功能描述： 获取指定ID信号机索引号
	* 参数说明： const UINT16 signalId,信号机ID
	* 返回值  ： SIGNAL_SUM_MAX ;获取数据失败
	*			 >0; 查找索引成功
	*/
	UINT16_S GetSignalConfigBufIndex(const UINT16_S signalId);

	/*
	* 功能描述： 获取指定ID站台信号机所属联锁ID
	* 参数说明： const UINT16 signalId,信号机ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 所属联锁ID      
	*/
	UINT8_S GetSignalBelongCiId(const UINT16_S signalId);

	/*
	* 功能描述： 获取指定ID信号机所属ZC的ID
	* 参数说明： const UINT16 signalId, 信号机ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 所属ZcID      
	*/
	UINT8_S GetSignalBelongZcId(const UINT16_S signalId);

	/*
	* 功能描述： 获取指定ID信号机共管区域属性
	* 参数说明： const UINT16 signalId, 信号机ID     
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取成功      
	*/
	UINT16_S GetSignalChangeAttribute(const UINT16_S signalId);

	/*
	* 功能描述： 获取指定ID信号机类型
	* 参数说明： const UINT16 signalId, 信号机ID     
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取成功      
	*/
	UINT8_S GetSignalSignalType(const UINT16_S signalId);

	/*
	* 功能描述： 获取指定ID信号机防护方向
	* 参数说明： const UINT16 signalId, 信号机ID     
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取成功      
	*/
	UINT8_S GetSignalProtectDir(const UINT16_S signalId);

	/*
	* 功能描述： 获取指定ID信号机默认状态
	* 参数说明： const UINT16 signalId, 信号机ID     
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取成功      
	*/
	UINT8_S GetSignalDefaultStatus(const UINT16_S signalId);

	/*
	* 功能描述： 获取指定ID信号机是否需要判断亮灭状态
	* 参数说明： const UINT16 signalId, 信号机ID     
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取成功      
	*/
	UINT8_S GetSignalLightOffType(const UINT16_S signalId);

	/*
	* 功能描述： 获取指定ID信号机CBTC类型下的亮灭灯状态
	* 参数说明： const UINT16 signalId, 信号机ID     
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取成功      
	*/
	UINT8_S GetSignalCbtcLightOffType(const UINT16_S signalId);

	/*
	* 功能描述： 获取指定ID信号机是否需要判断跨压状态
	* 参数说明： const UINT16 signalId, 信号机ID     
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取成功      
	*/
	UINT8_S GetSignalCrossType(const UINT16_S signalId);

	/*
	* 功能描述： 获取指定ID信号机是否需要判断闯过红灯信号机类型
	* 参数说明： const UINT16 signalId, 信号机ID     
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取成功      
	*/
	UINT8_S GetSignalCrashType(const UINT16_S signalId);

#ifdef __cplusplus
}
#endif

#endif
