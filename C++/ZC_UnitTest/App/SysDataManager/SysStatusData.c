/************************************************************************
*
* 文件名   ：  SysStatusData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  ZC系统状态管理
* 备  注   ：  无
*
************************************************************************/
#include "SysStatusData.h"

LocalZcInfoStruct gLocalZcInfoStru;                  /*本地ZC状态信息结构*/

/*
* 功能描述： 本地ZC状态属性数据结构
* 参数说明： void    
* 返回值  ： NULL: 获取数据失败
*			!NULL: 本地ZC状态属性数据结构
*/
LocalZcInfoStruct* LocalZcInfoData(void)
{
	return &gLocalZcInfoStru;
}

/*
* 功能描述： 获取ZC本地周期号
* 参数说明： 无    
* 返回值  ： 0: 获取数据失败
*			>0: localZC的周期号
*/
UINT32_S GetZcCycle(void)
{
	return gLocalZcInfoStru.ZcCycle;
}

/*
* 功能描述： 设置ZC周期号
* 参数说明： UINT32 zcCycle,周期号    
* 返回值  ： 无
*/
void SetZcCycle(UINT32_S zcCycle)
{
	if (zcCycle < 0xffffffffU)
	{
		gLocalZcInfoStru.ZcCycle = zcCycle;
	} 
	else
	{
		gLocalZcInfoStru.ZcCycle = 0U;
	}
}

/*
* 功能描述： 累加ZC周期号
* 参数说明： 无   
* 返回值  ： 无
*/
void AddZcCycle(void)
{
	if (gLocalZcInfoStru.ZcCycle < 0xffffffffU)
	{
		gLocalZcInfoStru.ZcCycle++;
	} 
	else
	{
		gLocalZcInfoStru.ZcCycle = 0U;
	}
}

/*
* 功能描述： 初始化ZC子系统状态信息
* 参数说明： 无   
* 返回值  ： 无
*/
void InitZcSysStatusData(void)
{
	gLocalZcInfoStru.ZcCycle = 0U;
}
