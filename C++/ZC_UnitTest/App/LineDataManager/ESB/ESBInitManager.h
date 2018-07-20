/************************************************************************
*
* 文件名   ：  ESBInitManager.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  紧急停车按钮初始化管理
* 备  注   ：  无
*
************************************************************************/
#ifndef ESB_INIT_MANAGER_H_
#define ESB_INIT_MANAGER_H_


#include "ESBDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* 功能描述： 初始化本地管理的紧急停车按钮初始信息
	* 参数说明： 无   
	* 返回值  ： 无      
	*/
	void InitEsbInitializationData(void);

	/*
	* 功能描述： 初始化本地管理的紧急停车按钮信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			 1: 初始化成功      
	*/
	UINT8_S InitESBLocalInfo(void);

#ifdef __cplusplus
}
#endif

#endif
