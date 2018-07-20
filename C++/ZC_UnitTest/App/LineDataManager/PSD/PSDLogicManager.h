/************************************************************************
*
* 文件名   ：  PSDLogicManager.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  屏蔽门逻辑处理
* 备  注   ：  无
*
************************************************************************/
#ifndef PSD_LOGIC_MANAGER_H_
#define PSD_LOGIC_MANAGER_H_

#include "PSDDefine.h"
#include "../../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif
	/*
	* 功能描述： 处理通信故障Ci对应的单个屏蔽门信息
	* 参数说明： const UINT16 psdId，屏蔽门ID    
	* 返回值  ： void  
	*/
	void InitFailureSinglePsd(const UINT16_S psdId);

	/*
	* 功能描述： 处理通信故障Ci对应的屏蔽门信息
	* 参数说明： const UINT16 ciId，通信故障的CIID    
	* 返回值  ： void  
	*/
	void InitFailureCiPsd(const UINT16_S ciId);

	/*
	* 功能描述： 处理通信故障Ci对应的屏蔽门信息
	* 参数说明： const UINT16 nZcId，通信故障的相邻ZcID    
	* 返回值  ： void  
	*/
	void InitFailureNZcPsd(const UINT16_S nZcId);

#ifdef __cplusplus
}
#endif

#endif
