/************************************************************************
*
* 文件名   ：  SwitchInitManager.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  道岔初始化管理
* 备  注   ：  无
*
************************************************************************/
#ifndef SWITCH_INIT_MANAGER_H_
#define SWITCH_INIT_MANAGER_H_


#include "SwitchDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* 功能描述： 初始化本地管理的道岔初始信息
	* 参数说明： 无   
	* 返回值  ： 无      
	*/
	void InitSwitchInitializationData(void);

	/*
	* 功能描述： 初始化本地管理的道岔信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitSwitchLocalInfo(void);


#ifdef __cplusplus
}
#endif

#endif
