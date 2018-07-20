/************************************************************************
*
* 文件名   ：  PSDStatusData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  屏蔽门状态管理
* 备  注   ：  无
*
************************************************************************/
#ifndef PSD_STATUS_DATA_H_
#define PSD_STATUS_DATA_H_


#include "PSDDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


	/*屏蔽门状态数据结构体*/
	typedef struct PsdDataStruct
	{
		UINT16_S PsdId;                     /*屏蔽门按钮ID*/
		UINT8_S PsdStatus;                  /*屏蔽门当前状态*/
	} PsdDataStruct;


	/*
	* 功能描述： 获取屏蔽门数据
	* 参数说明： void    
	* 返回值  ： NULL: 获取数据失败
	*			 !NULL: 屏蔽门数据
	*/
	PsdDataStruct* GetPsdStatusData(void);

	/*
	* 功能描述： 获取屏蔽门当前状态
	* 参数说明： psdId 屏蔽门ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 屏蔽门状态
	*/
	UINT8_S GetPsdStatus(const UINT16_S psdId);

	/*
	* 功能描述： 设置屏蔽门当前状态
	* 参数说明： psdId 屏蔽门ID; 
	             psdStatus 屏蔽门状态    
	* 返回值  ： 无
	*/
	UINT8_S SetPsdStatus(const UINT16_S psdId,UINT8_S psdStatus);

#ifdef __cplusplus
}
#endif

#endif
