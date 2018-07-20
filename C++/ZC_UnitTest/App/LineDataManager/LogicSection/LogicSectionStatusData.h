/************************************************************************
*
* 文件名   ：  LogicSectionStatusData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  逻辑区段状态管理
* 备  注   ：  无
*
************************************************************************/
#ifndef LOGIC_SECTION_STATUS_DATA_H_
#define LOGIC_SECTION_STATUS_DATA_H_

#include "LogicSectionDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


	/*逻辑区段状态数据结构体*/
	typedef struct LogicSectionStruct
	{
		UINT16_S LogicSectionId;                     /*逻辑区段ID*/
		UINT8_S LogicSectionOccStatus;               /*逻辑区段当前状态*/
	} LogicSectionStruct;


	/*
	* 功能描述： 获取逻辑区段数据
	* 参数说明： void    
	* 返回值  ： NULL: 获取数据失败
	*			 !NULL: 逻辑区段数据
	*/
	LogicSectionStruct* GetLogicSectionStatusData(void);

	/*
	* 功能描述： 获取逻辑区段当前状态
	* 参数说明： const UINT16 logicSectionId 逻辑区段ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 逻辑区段状态
	*/
	UINT8_S GetLogicSectionOccStatus(const UINT16_S logicSectionId);

	/*
	* 功能描述： 设置逻辑区段当前状态
	* 参数说明： const UINT16  logicSectionId 逻辑区段ID; 
	*	         UINT8_S logicSectionStatus 逻辑区段状态    
	* 返回值  ： 0;失败
	*            1;成功
	*/
	UINT8_S SetLogicSectionOccStatus(const UINT16_S logicSectionId,UINT8_S logicSectionStatus);

#ifdef __cplusplus
}
#endif

#endif
