/*******************************************
 * 文件名	：  LoadZcSystemConfig.h
 * 版权说明	：  北京三模科技有限公司
 * 版本号	：  1.0  
 * 创建时间	：  2015-5-25
 * 功能描述	：	ZcSystemConfig数据头文件
 * 使用注意	：  
 * 修改记录	：	
*******************************************/
#ifndef LOAD_ZCSYSTEMCONFIG_H_
#define LOAD_ZCSYSTEMCONFIG_H_


#include "../../../Common/CommonTypes.h"
#include "../Data/ZcSystemConfigData.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
* 功能描述： 载入ZcSystemConfig数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadZcSystemConfigData(void);

#ifdef __cplusplus
}
#endif
#endif
