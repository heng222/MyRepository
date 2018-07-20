/********************************************************
* 
* 文 件 名： LoadCommFailTime.h 
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： CommFailTime数据头文件 
* 备    注： 无 
* 
********************************************************/ 

#ifndef LOAD_COMMFAILTIME_H_
#define LOAD_COMMFAILTIME_H_


#include "../../../Common/CommonTypes.h"
#include "../Data/CommFailTimeData.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
* 功能描述： 载入CommFailTime数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadCommFailTimeData(void);

#ifdef __cplusplus
}
#endif
#endif
