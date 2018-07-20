/************************************************************************
*
* 文件名   ：  LogicSectionConfigData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  逻辑区段配置数据
* 备  注   ：  无
*
************************************************************************/
#ifndef LOGIC_SECTION_CONFIG_DATA_H_
#define LOGIC_SECTION_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "LogicSectionDefine.h"

#ifdef __cplusplus
extern "C" {
#endif


	/*屏蔽门数据结构体*/
	typedef struct LogicSectionConfigDataStruct
	{
		UINT16_S LogicSectionId;            /*逻辑区段ID*/
		UINT8_S BelongCiId;                 /*所属联锁ID*/
		UINT8_S BelongZcId;                 /*所属ZCID*/
		UINT16_S BelongAcId;                /*所属计轴区段Id*/
	} LogicSectionConfigDataStruct;

	/*
	* 功能描述： 获取逻辑区段管理总数
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 逻辑区段当前总数
	*/
	UINT16_S GetLogicSectionSum(void);

	/*
	* 功能描述： 获取指定数组下标对应的逻辑区段ID
	* 参数说明： const UINT16 bufIndex, 数组下标    
	* 返回值  ： 0: 获取数据失败
	*			>0: 逻辑区段ID      
	*/
	UINT16_S GetLogicSectionId(const UINT16_S bufIndex);

	/*
	* 功能描述： 获取指定ID逻辑区段索引号
	* 参数说明： const UINT16 logicSectionId,逻辑区段ID
	* 返回值  ：  LOGIC_SECTION_SUM_MAX;获取数据失败
	*			  >=0;查找索引成功
	*/
	UINT16_S GetLogicSectionConfigBufIndex(const UINT16_S logicSectionId);

	/*
	* 功能描述： 获取指定ID站台逻辑区段所属联锁ID
	* 参数说明： const UINT16 logicSectionId,逻辑区段ID   
	* 返回值  ： 0: 获取数据失败
	*			>0: 所属联锁ID      
	*/
	UINT8_S GetLogicSectionBelongCiId(const UINT16_S logicSectionId);

	/*
	* 功能描述： 获取指定ID逻辑区段所属ZC的ID
	* 参数说明： const UINT16 logicSectionId,逻辑区段ID   
	* 返回值  ： 0: 获取数据失败
	*			>0: 所属ZcID      
	*/
	UINT8_S GetLogicSectionBelongZcId(const UINT16_S logicSectionId);

	/*
	* 功能描述： 获取指定ID逻辑区段所属计轴区段ID
	* 参数说明： const UINT16 logicSectionId,逻辑区段ID     
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取成功      
	*/
	UINT16_S GetLogicSectionBelongAcId(const UINT16_S logicSectionId);

#ifdef __cplusplus
}
#endif

#endif
