/************************************************************************
*
* 文件名   ：  DRLogicManager.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  无人折返逻辑处理
* 备  注   ：  无
*
************************************************************************/
#ifndef DR_LOGIC_MANAGER_H_
#define DR_LOGIC_MANAGER_H_


#include "DRDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* 功能描述： 处理故障对应的单个无人折返按钮信息
	* 参数说明： const UINT16 drButtonId，无人折返按钮ID    
	* 返回值  ： void  
	*/
	void InitFailureSingleDrButton(const UINT16_S drButtonId);

	/*
	* 功能描述： 处理通信故障Ci对应的无人折返按钮信息
	* 参数说明： const UINT16 ciId，通信故障的CIID    
	* 返回值  ： void  
	*/
	void InitFailureCiDrButoon(const UINT16_S ciId);

	/*
	* 功能描述： 处理通信故障ZC对应的无人折返按钮信息
	* 参数说明： const UINT16 nZcId，通信故障的nZcID    
	* 返回值  ： void  
	*/
	void InitFailureNZcDrButton(const UINT16_S nZcId);

	/*
	* 功能描述： 处理故障对应的单个无人折返灯信息
	* 参数说明： const UINT16 drLampId，无人折返灯ID    
	* 返回值  ： void  
	*/
	void InitFailureSingleDrLamp(const UINT16_S drLampId);

	/*
	* 功能描述： 处理通信故障Ci对应的无人折返灯信息
	* 参数说明： const UINT16 ciId，通信故障的CIID    
	* 返回值  ： void  
	*/
	void InitFailureCiDrLamp(const UINT16_S ciId);

	/*
	* 功能描述： 处理通信故障ZC对应的无人折返灯信息
	* 参数说明： const UINT16 nZcId，通信故障的nZcID    
	* 返回值  ： void  
	*/
	void InitFailureNZcDrLamp(const UINT16_S nZcId);

#ifdef __cplusplus
}
#endif

#endif
