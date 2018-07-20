/************************************************************************
*
* 文件名   ：  PSDConfigData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  屏蔽门配置数据
* 备  注   ：  无
*
************************************************************************/
#ifndef PSD_CONFIG_DATA_H_
#define PSD_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "PSDDefine.h"

#ifdef __cplusplus
extern "C" {
#endif


	/*屏蔽门数据结构体*/
	typedef struct PsdConfigDataStruct
	{
		UINT16_S PsdId;                     /*屏蔽门ID*/
		UINT8_S BelongCiId;                 /*所属联锁ID*/
		UINT8_S BelongZcId;                 /*所属ZCID*/
		UINT8_S ChangeAttribute;       /*共管区域属性(标志是否属于某个共管区域)*/
	} PsdConfigDataStruct;

	/*
	* 功能描述： 获取屏蔽门管理总数
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 屏蔽门当前总数
	*/
	UINT16_S GetPsdSum(void);

	/*
	* 功能描述： 获取指定数组下标对应的屏蔽门ID
	* 参数说明： const UINT16 bufIndex, 数组下标    
	* 返回值  ： 0: 获取数据失败
	*			>0: 屏蔽门ID      
	*/
	UINT16_S GetPsdId(const UINT16_S bufIndex);

	/*
	* 功能描述： 获取指定ID屏蔽门索引号
	* 参数说明： const UINT16 psbId,屏蔽门ID
	* 返回值  ： PSD_LOCAL_SUM_MAX; 获取数据失败
	*			  >=0;查找索引成功
	*/
	UINT16_S GetPsdConfigBufIndex(const UINT16_S psdId);

	/*
	* 功能描述： 获取指定ID站台屏蔽门所属联锁ID
	* 参数说明： const UINT16 psdId,屏蔽门ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 所属联锁ID      
	*/
	UINT8_S GetPsdBelongCiId(const UINT16_S psdId);

	/*
	* 功能描述： 获取指定ID屏蔽门所属联锁ID
	* 参数说明： const UINT16 psdId, 屏蔽门ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 所属ZcID      
	*/
	UINT8_S GetPsdBelongZcId(const UINT16_S psdId);

	/*
	* 功能描述： 获取指定ID屏蔽门共管区域属性
	* 参数说明： const UINT16 psdId, 屏蔽门ID     
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取成功      
	*/
	UINT16_S GetPsdChangeAttribute(const UINT16_S psdId);

#ifdef __cplusplus
}
#endif

#endif
