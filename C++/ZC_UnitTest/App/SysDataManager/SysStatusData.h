/************************************************************************
*
* 文件名   ：  SysStatusData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  ZC系统状态管理
* 备  注   ：  无
*
************************************************************************/
#ifndef SYS_STATUS_DATA_H_
#define SYS_STATUS_DATA_H_

#include "../../Common/CommonTypes.h"
#include "SysDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*本地ZC状态属性数据结构*/
	typedef struct LocalZcInfoStruct
	{
		UINT32_S ZcCycle;                               /*ZC运行周期*/
	}LocalZcInfoStruct;

	/*
	* 功能描述： 本地ZC状态属性数据结构
	* 参数说明： void    
	* 返回值  ： NULL: 获取数据失败
	*			 !NULL: 本地ZC状态属性数据结构
	*/
	LocalZcInfoStruct* LocalZcInfoData(void);

	/*
	* 功能描述： 获取ZC本地周期号
	* 参数说明： 无    
	* 返回值  ： 0: 获取数据失败
	*			>0: localZC的周期号
	*/
	UINT32_S GetZcCycle(void);

	/*
	* 功能描述： 设置ZC周期号
	* 参数说明： UINT32 zcCycle,周期号    
	* 返回值  ： 无
	*/
	void SetZcCycle(UINT32_S zcCycle);

	/*
	* 功能描述： 累加ZC周期号
	* 参数说明： 无   
	* 返回值  ： 无
	*/
	void AddZcCycle(void);

	/*
	* 功能描述： 初始化ZC子系统状态信息
	* 参数说明： 无   
	* 返回值  ： 无
	*/
	void InitZcSysStatusData(void);

#ifdef __cplusplus
}
#endif

#endif
