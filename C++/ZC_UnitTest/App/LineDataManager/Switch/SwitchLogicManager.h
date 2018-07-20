/************************************************************************
*
* 文件名   ：  SwitchLogicManager.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  道岔逻辑处理管理
* 备  注   ：  无
*
************************************************************************/
#ifndef SWITCH_LOGIC_DATA_H_
#define SWITCH_LOGIC_DATA_H_


#include "SwitchDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* 功能描述： 处理通信故障Ci对应的单个道岔信息
	* 参数说明： const UINT16 switchId，道岔ID    
	* 返回值  ： void  
	*/
	void InitFailureSingleSwitch(const UINT16_S switchId);

	/*
	* 功能描述： 处理通信故障Ci对应的道岔信息
	* 参数说明： const UINT16 ciId;通信故障的联锁ID   
	* 返回值  ： void  
	*/
	void InitFailureCiSwitch(const UINT16_S ciId);

	/*
	* 功能描述： 处理通信故障NZc对应的道岔信息
	* 参数说明： const UINT16 nZcId,相邻ZC    
	* 返回值  ： void  
	*/
	void InitFailureNZcSwitch(const UINT16_S nZcId);

	/*
	* 功能描述： 组织给查询函数DMU的本地道岔信息
	* 参数说明： void    
	* 返回值  ： void  
	*/
	void SetDmuSwitchStatusInfo(void);

#ifdef __cplusplus
}
#endif

#endif
