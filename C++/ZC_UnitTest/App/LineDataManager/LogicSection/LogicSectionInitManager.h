/************************************************************************
*
* 文件名   ：  LogicSectionInitManager.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  逻辑区段初始化管理
* 备  注   ：  无
*
************************************************************************/
#ifndef LOGIC_SECTION_INIT_MANAGER_H_
#define LOGIC_SECTION_INIT_MANAGER_H_


#include "LogicSectionDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* 功能描述： 初始化本地管理的逻辑区段初始信息
	* 参数说明： 无   
	* 返回值  ： 无      
	*/
	void InitLogicSectionInitializationData(void);

	/*
	* 功能描述： 初始化本地管理的逻辑区段信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitLogicSectionLocalInfo(void);

#ifdef __cplusplus
}
#endif

#endif
