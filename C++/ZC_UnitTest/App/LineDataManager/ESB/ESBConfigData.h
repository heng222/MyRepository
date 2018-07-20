/************************************************************************
*
* 文件名   ：  ESBConfigData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  紧急停车按钮配置数据
* 备  注   ：  无
*
************************************************************************/
#ifndef ESB_CONFIG_DATA_H_
#define ESB_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "ESBDefine.h"

#ifdef __cplusplus
extern "C" {
#endif


	/*紧急停车按钮配置数据结构体*/
	typedef struct EsbConfigDataStruct
	{
		UINT16_S EsbId;                     /*紧急停车按钮ID*/
		UINT8_S BelongCiId;                 /*所属联锁ID*/
		UINT8_S BelongZcId;                 /*所属ZCID*/
		UINT8_S ChangeAttribute;       /*共管区域属性(标志是否属于某个共管区域)*/
	} EsbConfigDataStruct;

	/*
	* 功能描述： 获取紧急停车按钮管理总数
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 紧急停车按钮当前总数
	*/
	UINT16_S GetEsbSum(void);

	/*
	* 功能描述： 获取指定数组下标对应的紧急停车按钮ID
	* 参数说明： const UINT16 bufIndex, 数组下标    
	* 返回值  ： 0: 获取数据失败
	*			>0: 紧急停车按钮ID      
	*/
	UINT16_S GetEsbId(const UINT16_S bufIndex);

	/*
	* 功能描述： 获取指定ID紧急停车按钮索引号
	* 参数说明： const UINT16 esbId,紧急停车按钮ID
	* 返回值  ： ESB_LOCAL_SUM_MAX: 获取数据失败
	*			<ESB_LOCAL_SUM_MAX: 查找成功
	*/
	UINT16_S GetEsbConfigBufIndex(const UINT16_S esbId);

	/*
	* 功能描述： 获取指定ID站台紧急停车按钮所属联锁ID
	* 参数说明： const UINT16 esbId,紧急停车按钮ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 所属联锁ID      
	*/
	UINT8_S GetEsbBelongCiId(const UINT16_S esbId);

	/*
	* 功能描述： 获取指定ID紧急停车按钮所属联锁ID
	* 参数说明： const UINT16 esbId, 紧急停车按钮ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 所属ZcID      
	*/
	UINT8_S GetEsbBelongZcId(const UINT16_S esbId);

	/*
	* 功能描述： 获取指定ID紧急停车按钮共管区域属性
	* 参数说明： const UINT16 esbId, 紧急停车按钮ID     
	* 返回值  ： 0: 不属于
	*			 FLAG_SET: 属于      
	*/
	UINT8_S GetEsbChangeAttribute(const UINT16_S esbId);

#ifdef __cplusplus
}
#endif

#endif
