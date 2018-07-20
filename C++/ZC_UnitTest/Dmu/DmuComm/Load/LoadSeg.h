/********************************************************
* 
* 文 件 名： LoadSeg.h  
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： Seg数据头文件 
* 备    注： 无 
* 
********************************************************/ 

#ifndef LOAD_SEG_H_
#define LOAD_SEG_H_


#include "../../../Common/CommonTypes.h"
#include "../Data/SegData.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
* 功能描述： 载入Seg数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadSegData(void);

#ifdef __cplusplus
}
#endif
#endif
