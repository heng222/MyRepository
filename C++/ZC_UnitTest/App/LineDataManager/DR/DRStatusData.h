/************************************************************************
*
* 文件名   ：  DRStatusData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  无人折返状态
* 备  注   ：  无
*
************************************************************************/
#ifndef DR_STATUS_DATA_H_
#define DR_STATUS_DATA_H_


#include "DRDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


	/*DR按钮状态数据结构体*/
	typedef struct DRButtonDataStruct
	{
		UINT16_S DRButtonId;                /*无人折返按钮ID*/
		UINT16_S TrainId;                   /*无人折返按钮对应列车ID*/
		UINT8_S DRButtonStatus;             /*无人折返按钮当前状态*/
	} DRButtonDataStruct;

	/*DR灯状态数据结构体*/
	typedef struct DRLampDataStruct
	{
		UINT16_S DRLampId;                /*无人折返按钮ID*/
		UINT16_S TrainId;                 /*无人折返按钮对应列车ID*/
		UINT8_S DRLampCmd;                /*无人折返灯控制命令*/
	} DRLampDataStruct;


	/*
	* 功能描述： 获取无人折返按钮数据
	* 参数说明： void    
	* 返回值  ： 无人折返按钮结构体数组首地址
	*/
	DRButtonDataStruct* GetDRButtonStatusData(void);

	/*
	* 功能描述： 获取无人折返灯数据
	* 参数说明： void    
	* 返回值  ： 无人折返灯结构体数组首地址
	*/
	DRLampDataStruct* GetDRLampData(void);

	/*
	* 功能描述： 获取无人折返按钮关联的列车ID
	* 参数说明： const UINT16 drButtonId,无人折返按钮ID   
	* 返回值  ： 0: 获取数据失败
	*			>0: 列车ID
	*/
	UINT16_S GetDRButtonOfTrainId(const UINT16_S drButtonId);

	/*
	* 功能描述： 设置无人折返按钮关联的列车ID
	* 参数说明： const UINT16 drButtonId, 无人折返按钮ID
	*            UINT16_S trainId,列车ID
	* 返回值  ： 0:获取数据失败
	*            1：获取数据成功
	*/
	UINT8_S SetDRButtonOfTrainId(const UINT16_S drButtonId,UINT16_S trainId);

	/*
	* 功能描述： 获取无人折返灯关联列车ID
	* 参数说明： const UINT16 drLampId,无人折返灯ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 列车ID
	*/
	UINT16_S GetDRLampOfTrainId(const UINT16_S drLampId);

	/*
	* 功能描述： 设置无人折返灯关联列车ID
	* 参数说明： const UINT16 drLampId,无人折返灯ID  
	*            UINT16_S trainId,列车ID
	* 返回值  ： 0:获取数据失败
	*            1：获取数据成功
	*/
	UINT8_S SetDRLampOfTrainId(const UINT16_S drLampId,UINT16_S trainId);

	/*
	* 功能描述： 获取无人折返灯控制命令
	* 参数说明： const UINT16 drLampId,无人折返灯ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 控制命令
	*/
	UINT8_S GetDRLampCommand(const UINT16_S drLampId);

	/*
	* 功能描述： 设置无人折返灯控制命令
	* 参数说明： const UINT16 drLampId,无人折返灯ID  
	*            UINT8_S drLampCmd,无人折返灯命令   
	* 返回值  ： 0:获取数据失败
	*            1：获取数据成功
	*/
	UINT8_S SetDRLampCommand(const UINT16_S drLampId,UINT8_S drLampCmd);

	/*
	* 功能描述： 获取无人折返按钮当前状态
	* 参数说明： const UINT16 drButtonId,无人折返按钮ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 控制命令
	*/
	UINT8_S GetDRButtonStatus(const UINT16_S drButtonId);

	/*
	* 功能描述： 设置无人折返按钮控制命令
	* 参数说明： const UINT16 drButtonId,无人折返按钮ID  
	*            UINT8_S drButtonStatus,无人折返按钮命令   
	* 返回值  ： 0:获取数据失败
	*            1：获取数据成功
	*/
	UINT8_S SetDRButtonStatus(const UINT16_S drButtonId,UINT8_S drButtonStatus);

#ifdef __cplusplus
}
#endif

#endif
