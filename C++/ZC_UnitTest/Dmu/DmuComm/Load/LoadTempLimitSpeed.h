/********************************************************
* 
* 文 件 名： LoadTempLimitSpeed.h  
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： TempLimitSpeed数据头文件 
* 备    注： 无 
* 
********************************************************/ 

#ifndef LOAD_TEMPLIMITSPEED_H_
#define LOAD_TEMPLIMITSPEED_H_


#include "../../../Common/CommonTypes.h"
#include "../Data/TempLimitSpeedData.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
* 功能描述： 载入TempLimitSpeed数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadTempLimitSpeedData(void);

#ifdef __cplusplus
}
#endif
#endif
