/************************************************************************
*
* 文件名   ：  SignalStatusData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  信号机状态管理
* 备  注   ：  无
*
************************************************************************/
#ifndef SIGNAL_STATUS_DATA_H_
#define SIGNAL_STATUS_DATA_H_


#include "SignalDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


	/*信号机状态数据结构体*/
	typedef struct SignalDataStruct
	{
		UINT16_S SignalId;                      /*信号机ID*/
		UINT8_S SignalStatus;                   /*信号机当前状态*/ 
		UINT8_S LightOffStatus;                 /*信号机亮灭状态*/                
		UINT8_S CrossStatus;                    /*列车跨过信号机状态*/
	} SignalDataStruct;


	/*
	* 功能描述： 获取信号机数据
	* 参数说明： void    
	* 返回值  ： NULL: 获取数据失败
	*			 !NULL: 信号机数据
	*/
	SignalDataStruct* GetSignalStatusData(void);

	/*
	* 功能描述： 获取信号机当前状态
	* 参数说明： const UINT16  signalId 信号机ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 信号机状态
	*/
	UINT8_S GetSignalStatus(const UINT16_S signalId);

	/*
	* 功能描述： 设置信号机当前状态
	* 参数说明： const UINT16 signalId 信号机ID; 
	*            UINT8_S signalStatus 信号机状态    
	* 返回值  ： 0;失败
	*            1;成功
	*/
	UINT8_S SetSignalStatus(const UINT16_S signalId,UINT8_S signalStatus);

	/*
	* 功能描述： 获取信号机信号机亮灭状态
	* 参数说明： const UINT16 signalId 信号机ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 信号机状态
	*/
	UINT8_S GetSignalLightOffStatus(const UINT16_S signalId);

	/*
	* 功能描述： 设置信号机信号机亮灭状态
	* 参数说明： const UINT16 signalId 信号机ID; 
	*	         UINT8_S  lightOffStatus 信号机状态    
	* 返回值  ： 0;失败
	*            1;成功
	*/
	UINT8_S SetSignalLightOffStatus(const UINT16_S signalId,UINT8_S lightOffStatus);

	/*
	* 功能描述： 获取信号机列车跨压信号机状态
	* 参数说明： const UINT16 signalId 信号机ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 信号机状态
	*/
	UINT8_S GetSignalCrossStatus(const UINT16_S signalId);

	/*
	* 功能描述： 设置信号机列车跨压信号机状态
	* 参数说明： const UINT16 signalId 信号机ID; 
	*	         UINT8_S  crossStatus 信号机状态    
	* 返回值  ： 0;失败
	*            1;成功
	*/
	UINT8_S SetSignalCrossStatus(const UINT16_S signalId,UINT8_S crossStatus);

#ifdef __cplusplus
}
#endif

#endif
