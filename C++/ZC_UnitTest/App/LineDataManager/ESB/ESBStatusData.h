/************************************************************************
*
* 文件名   ：  ESBStatusData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  紧急停车按钮状态管理
* 备  注   ：  无
*
************************************************************************/
#ifndef ESB_STATUS_DATA_H_
#define ESB_STATUS_DATA_H_


#include "ESBDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


	/*紧急停车按钮状态数据结构体*/
	typedef struct EsbDataStruct
	{
		UINT16_S EsbId;                     /*紧急停车按钮按钮ID*/
		UINT8_S EsbStatus;                  /*紧急停车按钮当前状态*/
	} EsbDataStruct;


	/*
	* 功能描述： 获取紧急停车按钮数据
	* 参数说明： void    
	* 返回值  ： NULL: 获取数据失败
	*			 !NULL: 紧急停车按钮数据
	*/
	EsbDataStruct* GetEsbStatusData(void);

	/*
	* 功能描述： 获取紧急停车按钮当前状态
	* 参数说明： esbId 紧急停车按钮ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 紧急停车按钮状态
	*/
	UINT8_S GetEsbStatus(const UINT16_S esbId);

	/*
	* 功能描述： 设置紧急停车按钮当前状态
	* 参数说明： esbId 紧急停车按钮ID; 
	*	         esbStatus 紧急停车按钮状态    
	* 返回值  ： 0;失败
	*            1;成功
	*/
	UINT8_S SetEsbStatus(const UINT16_S esbId,UINT8_S esbStatus);

#ifdef __cplusplus
}
#endif

#endif
