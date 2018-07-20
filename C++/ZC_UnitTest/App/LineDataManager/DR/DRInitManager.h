/************************************************************************
*
* 文件名   ：  DRInitManager.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  无人折返初始化管理
* 备  注   ：  无
*
************************************************************************/
#ifndef DR_INIT_MANAGER_H_
#define DR_INIT_MANAGER_H_


#include "DRDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* 功能描述： 初始化本地管理的无人折返按钮初始信息
	* 参数说明： 无   
	* 返回值  ： 无      
	*/
	void InitDrButtonInitializationData(void);

	/*
	* 功能描述： 初始化本地管理的无人折返灯初始信息
	* 参数说明： 无   
	* 返回值  ： 无      
	*/
	void InitDrLampInitializationData(void);

	/*
	* 功能描述： 初始化本地管理的无人折返按钮信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitDrButtonLocalInfo(void);

	/*
	* 功能描述： 初始化本地管理的无人折返灯信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitDrLampLocalInfo(void);

#ifdef __cplusplus
}
#endif

#endif
