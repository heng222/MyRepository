/************************************************************************
*
* 文件名   ：  PSDInitManager.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  屏蔽门初始化管理
* 备  注   ：  无
*
************************************************************************/
#ifndef PSD_INIT_MANAGER_H_
#define PSD_INIT_MANAGER_H_


#include "PSDDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* 功能描述： 初始化本地管理的屏蔽门初始信息
	* 参数说明： 无   
	* 返回值  ： 无      
	*/
	void InitPsdInitializationData(void);

	/*
	* 功能描述： 初始化本地管理的屏蔽门信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitPSDLocalInfo(void);

#ifdef __cplusplus
}
#endif

#endif
