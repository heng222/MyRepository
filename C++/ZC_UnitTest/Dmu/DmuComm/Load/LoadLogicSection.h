/********************************************************
* 
* 文 件 名： LoadLogicSection.h 
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： LogicSection数据头文件 
* 备    注： 无 
* 
********************************************************/ 

#ifndef LOAD_LOGICSECTION_H_
#define LOAD_LOGICSECTION_H_


#include "../../../Common/CommonTypes.h"
#include "../Data/LogicSectionData.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
* 功能描述： 载入LogicSection数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadLogicSectionData(void);

#ifdef __cplusplus
}
#endif
#endif
