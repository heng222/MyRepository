/*******************************************
 * 文件名	：  ZcTimeConfigData.h
 * 版本号	：  1.0  
 * 创建时间	：  2015-5-25
 * 功能描述	：	ZcTimeConfigData数据管理头文件
 * 使用注意	：  
 * 修改记录	：	
*******************************************/
#ifndef ZCTIMECONFIG_DATA_H_
#define ZCTIMECONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"

#define ZCTIMECONFIG_LINE_BYTE_NUM                 	 8U                         /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*校时配置表数据结构体*/
typedef struct BnfZcTimeConfigStruct
{
	UINT32_S errorTime;			/*NTP校时误差时间(ms)*/
	UINT32_S duration;			/*本系统与时钟服务器校时的时长（ms）*/	
}BnfZcTimeConfigStruct;

/*
* 功能描述： 给ZcTimeConfigDataStru结构体指针分配空间
* 参数说明： UINT16 lineNum 表的数据行数
* 返回值  ： void
*/
void MallocZcTimeConfigDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取ZcTimeConfigData数据
* 参数说明：
* 返回值  ： 
			BnfZcTimeConfigStruct*
*/
BnfZcTimeConfigStruct *GetZcTimeConfigData(void);


/*
* 功能描述： 获取ZcTimeConfigData信息
* 参数说明：输出参数:UINT16* lineNum  数据行数
* 返回值  ： 
			BnfZcTimeConfigStruct*
*/
BnfZcTimeConfigStruct *GetZcTimeDataInfo(UINT16_S* lineNum);

/*
** 功能描述： 获取NTP校时误差时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*			<UINT32_NULL: NTP校时误差时间(ms)
*/ 
UINT32_S GetZcTimeNtprrorTime(void);

/*
** 功能描述： 获取本系统与时钟服务器校时的时长（ms）
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*			<UINT32_NULL: 本系统与时钟服务器校时的时长（ms）
*/ 
UINT32_S GetZcTimeSystemDuration(void);

#ifdef __cplusplus
}
#endif

#endif
