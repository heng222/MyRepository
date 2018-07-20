/********************************************************
* 
* 文 件 名： LoadSystemConfig.h  
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： SystemConfig数据头文件 
* 备    注： 无 
* 
********************************************************/ 

#ifndef LOAD_SYSTEMCONFIG_H_
#define LOAD_SYSTEMCONFIG_H_


#include "../../../Common/CommonTypes.h"
#include "../Data/SystemConfigData.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
* 功能描述： 载入SystemConfig数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadSystemConfigData(void);

#ifdef __cplusplus
}
#endif
#endif
