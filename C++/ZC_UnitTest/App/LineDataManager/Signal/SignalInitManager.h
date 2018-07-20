/************************************************************************
*
* 文件名   ：  SignalInitManager.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  信号机初始化管理
* 备  注   ：  无
*
************************************************************************/
#ifndef SIGNAL_INIT_MANAGER_H_
#define SIGNAL_INIT_MANAGER_H_


#include "SignalDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* 功能描述： 初始化本地管理的信号机初始信息
	* 参数说明： 无   
	* 返回值  ： 无      
	*/
	void InitSignalInitializationData(void);

	/*
	* 功能描述： 初始化本地管理的信号机信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitSignalLocalInfo(void);

	/*
	* 功能描述： 初始化本地管理的信号机亮灭灯信息
	* 参数说明： const UINT16 signalId，信号机ID   
	* 返回值  ： 0: 失败
	*			 0x55: 属于
	*            0xaa: 不属于
	*/
	UINT8_S InitSignalLightOffType(const UINT16_S signalId);

	/*
	* 功能描述： 初始化本地管理的信号机跨压信息
	* 参数说明： const UINT16 signalId，信号机ID   
	* 返回值  ： 0: 失败
	*			 0x55: 属于
	*            0xaa: 不属于
	*/
	UINT8_S InitSignalCorssType(const UINT16_S signalId);

#ifdef __cplusplus
}
#endif

#endif
