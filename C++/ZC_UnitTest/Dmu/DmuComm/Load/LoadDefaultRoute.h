/********************************************************
* 
* 文 件 名： LoadDefaultRoute.h 
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： DefaultRoute数据头文件 
* 备    注： 无 
* 
********************************************************/ 

#ifndef LOAD_DEFAULTROUTE_H_
#define LOAD_DEFAULTROUTE_H_


#include "../../../Common/CommonTypes.h"
#include "../Data/DefaultRouteData.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
* 功能描述： 载入DefaultRoute数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadDefaultRouteData(void);

#ifdef __cplusplus
}
#endif
#endif
