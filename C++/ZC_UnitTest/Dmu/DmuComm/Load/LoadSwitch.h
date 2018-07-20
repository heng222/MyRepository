/********************************************************
* 
* 文 件 名： LoadSwitch.h  
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述：  Switch数据头文件 
* 备    注： 无 
* 
********************************************************/ 

#ifndef LOAD_SWITCH_H_
#define LOAD_SWITCH_H_


#include "../../../Common/CommonTypes.h"
#include "../Data/SwitchData.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
* 功能描述： 载入Switch数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadSwitchData(void);

#ifdef __cplusplus
}
#endif
#endif
