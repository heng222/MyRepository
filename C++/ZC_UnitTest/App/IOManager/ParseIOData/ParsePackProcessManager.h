/************************************************************************
*
* 文件名   ：  ParsePackProcessManager.h
* 创建时间 ：  2015.08.14
* 作者     ：  ZC组
* 功能描述 ：  解析和组包ZC数据管理
* 备  注	：  无
*
************************************************************************/

#ifndef PARSE_PACK_PROCESS_MANAGER_H_
#define PARSE_PACK_PROCESS_MANAGER_H_

#include "../../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*
	* 功能描述： 解析输入数据
	* 参数说明： void
	* 返回值  ： void      
	*/
	void ParseInputData(void);

	/*
	* 功能描述： 清空输入数据处理
	* 参数说明： 无
	* 返回值  ： 无      
	*/
	void ClearInputDataProcess(void);

	/*
	* 功能描述： 组包输出数据
	* 参数说明： void
	* 返回值  ： void      
	*/
	void PackOutputData(void);

	/*
	* 功能描述： 清空输出数据处理
	* 参数说明： 无
	* 返回值  ： 无      
	*/
	void ClearOutputDataProcess(void);

	/*
	* 功能描述： 解析CI输入数据
	* 参数说明： void
	* 返回值  ： void      
	*/
	UINT8_S ParseCiToZcData(void);

	/*
	* 功能描述： 解析车载ATP输入数据
	* 参数说明： void
	* 返回值  ： void      
	*/
	UINT8_S ParseTrainToZcData(void);

	/*
	* 功能描述： 解析NZc输入数据
	* 参数说明： void
	* 返回值  ： void      
	*/
	/*解析CI输入数据*/
	UINT8_S ParseNZcToZcData(void);

	/*
	* 功能描述： 解析ats输入数据
	* 参数说明： void
	* 返回值  ： 成功解析的数据包的数量    
	*/
	extern UINT8_S ParseAtsToZcData(void);

	/*
	* 功能描述： 解析Ntp输入数据
	* 参数说明： void
	* 返回值  ： 1,添加成功
	*            0,添加失败      
	*/
	UINT8_S ParseNtpToZcData(void);
	
	/*
	* 功能描述： 组帧输出给CI的数据
	* 参数说明： void
	* 返回值  ： void      
	*/
	UINT8_S PackZcToCiData(void);

	/*
	* 功能描述： 组帧输出给车载ATP的数据
	* 参数说明： void
	* 返回值  ： void      
	*/
	UINT8_S PackZcToTrainData(void);

	/*
	* 功能描述： 组帧输出给Ntp的数据
	* 参数说明： void
	* 返回值  ： 1,添加成功
	*            0,添加失败      
	*/
	UINT8_S PackZcToNtpData(void);

	/*
	* 功能描述： 组帧输出给NZc的数据
	* 参数说明： void
	* 返回值  ： void      
	*/
	UINT8_S PackZcToNZcData(void);

	/*
	* 功能描述： 组帧输出给Ats的数据
	* 参数说明： void
	* 返回值  ： void      
	*/
	void PackZcToAtsData(void);/*-bye-*/

#ifdef __cplusplus
}
#endif

#endif
