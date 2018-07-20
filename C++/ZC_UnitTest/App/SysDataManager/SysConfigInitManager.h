/************************************************************************
*
* 文件名   ：  SysConfigInitManager.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  ZC系统配置的初始化管理
* 备  注   ：  无
*
************************************************************************/
#ifndef SYS_CONFIG_DATA_INIT_MANAGER_H_
#define SYS_CONFIG_DATA_INIT_MANAGER_H_

#include "../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* 功能描述： 初始化系统配置信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitSystemConfigData(void);

	/*
	* 功能描述： 初始化系统配置信息中列车信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitTrainConfigInfo(void);

	/*
	* 功能描述： 初始化ZC子系统配置信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitZcSubSystemConfigData(void);

	/*
	* 功能描述： 初始化本地ZCId配置信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitLocalZcIdConfigData(void);

	/*
	* 功能描述： 初始化本地Ntp配置信息
	* 参数说明： 无   
	* 返回值  ： 无      
	*/
	void InitLocalNtpConfigData(void);

#ifdef __cplusplus
}
#endif

#endif
