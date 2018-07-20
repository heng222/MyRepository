/************************************************************************
*
* 文件名   ：  SwitchStatusData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  道岔状态管理
* 备  注   ：  无
*
************************************************************************/
#ifndef SWITCH_STATUS_DATA_H_
#define SWITCH_STATUS_DATA_H_


#include "SwitchDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


	/*道岔状态数据结构体*/
	typedef struct SwitchDataStruct
	{
		UINT16_S SwitchId;                     /*道岔按钮ID*/
		UINT8_S SwitchPosStatus;               /*道岔当前位置状态*/
		UINT8_S SwitchLock;                    /*道岔锁闭状态*/
	} SwitchDataStruct;


	/*
	* 功能描述： 获取道岔数据
	* 参数说明： void    
	* 返回值  ： NULL: 获取数据失败
	*			 !NULL: 道岔数据
	*/
	SwitchDataStruct* GetSwitchStatusData(void);

	/*
	* 功能描述： 获取道岔当前状态
	* 参数说明： const UINT16 switchId 道岔ID    
	* 返回值  ： 3: 获取数据失败
	*			不等于3: 道岔状态
	*/
	UINT8_S GetSwitchPosStatus(const UINT16_S switchId);

	/*
	* 功能描述： 设置道岔当前状态
	* 参数说明： const UINT16 switchId 道岔ID; 
	*	         UINT8_S  SwitchPosStatus 道岔状态    
	* 返回值  ： 0;失败
	*            1;成功
	*/
	UINT8_S SetSwitchPosStatus(const UINT16_S switchId,UINT8_S switchPosStatus);

	/*
	* 功能描述： 获取道岔锁闭状态
	* 参数说明： const UINT16 switchId 道岔ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 道岔锁闭状态
	*/
	UINT8_S GetSwitchLock(const UINT16_S switchId);

	/*
	* 功能描述： 设置道岔锁闭状态
	* 参数说明： const UINT16 switchId 道岔ID; 
	*	         UINT8_S  lockStatus 道岔锁闭状态    
	* 返回值  ： 0;失败
	*            1;成功
	*/
	UINT8_S SetSwitchLock(const UINT16_S switchId,UINT8_S lockStatus);

#ifdef __cplusplus
}
#endif

#endif
