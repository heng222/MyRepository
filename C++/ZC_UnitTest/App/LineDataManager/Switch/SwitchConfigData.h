/************************************************************************
*
* 文件名   ：  SwitchConfigData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  道岔配置数据管理
* 备  注   ：  无
*
************************************************************************/
#ifndef SWITCH_CONFIG_DATA_H_
#define SWITCH_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "SwitchDefine.h"

#ifdef __cplusplus
extern "C" {
#endif


	/*道岔数据结构体*/
	typedef struct SwitchConfigDataStruct
	{
		UINT16_S SwitchId;                      /*道岔ID*/
		UINT8_S BelongCiId;                     /*所属联锁ID*/
		UINT8_S BelongZcId;                     /*所属ZCID*/
		UINT8_S ChangeAttribute;           /*共管区域属性(标志是否属于某个共管区域)*/
		UINT8_S SwitchPosition;                 /*道岔位子(标志该道岔位置区域)*/
	} SwitchConfigDataStruct;

	/*
	* 功能描述： 获取道岔管理总数
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 道岔当前总数
	*/
	UINT16_S GetSwitchSum(void);

	/*
	* 功能描述： 获取指定数组下标对应的道岔ID
	* 参数说明： const UINT16 bufIndex, 数组下标    
	* 返回值  ： 0: 获取数据失败
	*			>0: 道岔ID      
	*/
	UINT16_S GetSwitchId(const UINT16_S bufIndex);

	/*
	* 功能描述： 获取指定ID道岔索引号
	* 参数说明： const UINT16 switchId,道岔ID
	* 返回值  ： SWITCH_SUM_MAX; 获取数据失败
	*			 >0; 查找索引成功
	*/
	UINT16_S GetSwitchConfigBufIndex(const UINT16_S switchId);

	/*
	* 功能描述： 获取指定ID站台道岔所属联锁ID
	* 参数说明： const UINT16 switchId,道岔ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 所属联锁ID      
	*/
	UINT8_S GetSwitchBelongCiId(const UINT16_S switchId);

	/*
	* 功能描述： 获取指定ID道岔所属ZC的ID
	* 参数说明： const UINT16 switchId, 道岔ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 所属ZcID      
	*/
	UINT8_S GetSwitchBelongZcId(const UINT16_S switchId);

	/*
	* 功能描述： 获取指定ID道岔共管区域属性
	* 参数说明： const UINT16 switchId, 道岔ID     
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取成功      
	*/
	UINT16_S GetSwitchChangeAttribute(const UINT16_S switchId);

	/*
	* 功能描述： 获取指定ID道岔位置区域
	* 参数说明： const UINT16 switchId, 道岔ID     
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取成功      
	*/
	UINT16_S GetSwitchPosition(const UINT16_S switchId);

#ifdef __cplusplus
}
#endif

#endif
