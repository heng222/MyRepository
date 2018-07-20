/************************************************************************
*
* 文件名   ：  TsrInitManager.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  临时限速初始化管理
* 备  注   ：  无
*
************************************************************************/
#ifndef TSR_INIT_MANAGER_H_
#define TSR_INIT_MANAGER_H_


#include "TsrDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* 功能描述： 初始化本地管理的临时限速信息
	* 参数说明： 无   
	* 返回值  ： 无      
	*/
	void InitTsrLocalInfo(void);

#ifdef __cplusplus
}
#endif

#endif
