/************************************************************************
*
* 文件名   ：  ESBLogicManager.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  紧急停车按钮逻辑处理
* 备  注   ：  无
*
************************************************************************/
#ifndef ESB_LOGIC_MANAGER_H_
#define ESB_LOGIC_MANAGER_H_


#include "ESBDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* 功能描述： 处理故障对应的单个ESB信息
	* 参数说明： const UINT16 esbId，ESBID    
	* 返回值  ： void  
	*/
	void InitFailureSingleEsb(const UINT16_S esbId);

	/*
	* 功能描述： 处理通信故障Ci对应的紧急停车按钮信息
	* 参数说明： const UINT16 ciId，通信故障的CIID    
	* 返回值  ： void  
	*/
	void InitFailureCiEsb(const UINT16_S ciId);

	/*
	* 功能描述： 处理通信故障ZC对应的紧急停车按钮信息
	* 参数说明： const UINT16 nZcId，通信故障的nZcID    
	* 返回值  ： void  
	*/
	void InitFailureNZcEsb(const UINT16_S nZcId);

#ifdef __cplusplus
}
#endif

#endif
