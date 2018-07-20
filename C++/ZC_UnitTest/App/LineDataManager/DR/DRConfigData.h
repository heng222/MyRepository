/************************************************************************
*
* 文件名   ：  DRConfigData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  无人折返配置数据
* 备  注   ：  无
*
************************************************************************/
#ifndef DR_CONFIG_DATA_H_
#define DR_CONFIG_DATA_H_


#include "DRDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


	/*DR按钮配置数据结构体*/
	typedef struct DRButtonConfigDataStruct
	{
		UINT16_S DRButtonId;                /*无人折返按钮ID*/
		UINT8_S BelongCiId;                 /*所属联锁ID*/
		UINT8_S BelongZcId;                 /*所属ZCID*/
		UINT8_S ChangeAttribute;       /*共管区域属性(标志是否属于某个共管区域)*/
	} DRButtonConfigDataStruct;

	/*DR灯配置数据结构体*/
	typedef struct DRLampConfigDataStruct
	{
		UINT16_S DRLampId;                  /*无人折返灯ID*/
		UINT8_S BelongCiId;                 /*所属联锁ID*/
		UINT8_S BelongZcId;                 /*所属ZCID*/
		UINT8_S ChangeAttribute;       /*共管区域属性(标志是否属于某个共管区域)*/
	} DRLampConfigDataStruct;


	/*
	* 功能描述： 获取无人折返按钮管理总数
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 无人折返按钮当前总数
	*/
	UINT16_S GetDRButtonSum(void);

	/*
	* 功能描述： 获取无人折返灯管理总数
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 无人折返灯当前总数
	*/
	UINT16_S GetDRLampSum(void);

	/*
	* 功能描述： 获取指定数组下标对应的无人折返按钮ID
	* 参数说明： const UINT16 bufIndex, 数组下标    
	* 返回值  ： 0: 获取数据失败
	*			>0: 无人折返按钮ID      
	*/
	UINT16_S GetDRButtonId(const UINT16_S bufIndex);

	/*
	* 功能描述： 获取指定数组下标对应的无人折返按灯ID
	* 参数说明： const UINT16 bufIndex, 数组下标    
	* 返回值  ： 0: 获取数据失败
	*			>0: 无人折返灯ID    
	*/
	UINT16_S GetDRLampId(const UINT16_S bufIndex);

	/*
	* 功能描述： 获取指定无人折返按钮ID索引号
	* 参数说明： const UINT16 drButtonId, 无人折返按钮ID
	* 返回值  ： DR_BUTTON_LOCAL_SUM_MAX: 获取数据失败
	*			<DR_BUTTON_LOCAL_SUM_MAX: 查找成功
	*/
	UINT16_S GetDRButtonConfigBufIndex(const UINT16_S drButtonId);

	/*
	* 功能描述： 获取指定无人折返灯ID索引号
	* 参数说明： const UINT16 drLampId, 无人折返灯ID
	* 返回值  ： DR_LAMP_LOCAL_SUM_MAX: 获取数据失败
	*			<DR_LAMP_LOCAL_SUM_MAX: 查找成功
	*/
	UINT16_S GetDRLampConfigBufIndex(const UINT16_S drLampId);

	/*
	* 功能描述： 获取指定ID无人折返按钮所属联锁ID
	* 参数说明： const UINT16 drButtonId ,无人折返按钮ID   
	* 返回值  ： 0: 获取数据失败
	*			>0: 所属联锁ID      
	*/
	UINT8_S GetDRButtonBelongCiId(const UINT16_S drButtonId);

	/*
	* 功能描述： 获取指定ID无人折返灯所属联锁ID
	* 参数说明： const UINT16 drLampId  ,无人折返灯ID 
	* 返回值  ： 0: 获取数据失败
	*			>0: 所属联锁ID      
	*/
	UINT8_S GetDRLampBelongCiId(const UINT16_S drLampId);

	/*
	* 功能描述： 获取指定ID无人折返按钮所属ZCID
	* 参数说明： const UINT16 drButtonId ,无人折返按钮ID
	* 返回值  ： 0: 获取数据失败
	*			>0: 所属ZC的ID      
	*/
	UINT8_S GetDRButtonBelongZcId(const UINT16_S drButtonId);

	/*
	* 功能描述： 获取指定ID无人折返灯所属ZCID
	* 参数说明： const UINT16 drLampId,无人折返灯ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 所属ZC的ID      
	*/
	UINT8_S GetDRLampBelongZcId(const UINT16_S drLampId);

	/*
	* 功能描述： 获取指定ID无人折返按钮共管区域属性
	* 参数说明： const UINT16 drButtonId, 无人折返按钮ID    
	* 返回值  ： 0: 不属于
	*			 FLAG_SET: 属于      
	*/
	UINT8_S GetDRButtonChangeAttribute(const UINT16_S drButtonId);

	/*
	* 功能描述： 获取指定ID无人折返灯共管区域属性
	* 参数说明： const UINT16 drLampId, 无人折返灯ID    
	* 返回值  ： 0: 不属于
	*			 FLAG_SET: 属于      
	*/
	UINT8_S GetDRLampChangeAttribute(const UINT16_S drLampId);

#ifdef __cplusplus
}
#endif

#endif
