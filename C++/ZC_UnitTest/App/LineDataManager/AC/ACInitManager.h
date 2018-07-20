/************************************************************************
*
* 文件名   ：  ACInitManager.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  计轴区段的初始化
* 备  注   ：  无
*
************************************************************************/

#ifndef AC_INIT_MANAGER_H_
#define AC_INIT_MANAGER_H_


#include "ACDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* 功能描述： 初始化本地管理的计轴区段初始信息
	* 参数说明： 无   
	* 返回值  ： 无     
	*/
	void InitAcInitializationData(void);

	/*
	* 功能描述： 初始化本地管理的计轴区段信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitACLocalInfo(void);

#ifdef __cplusplus
}
#endif

#endif
