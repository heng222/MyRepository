/********************************************************
*                                                                                                            
* 文 件 名： AbsFun.h
* 版权说明：  
* 创建时间： 2013-10-25
* 作    者： 
* 功能描述： 求绝对值函数头文件
* 修改记录：   
*
********************************************************/
#ifndef ABS_FUN_H_
#define ABS_FUN_H_

#include "CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

/*
*  功能描述:求DouBle类型的数据的绝对值
*  参数说明：  
*  返回值：    
*/
FLOAT64_S AbsFloat64Func(FLOAT64_S value);


/*
*  功能描述:求Float类型的数据的绝对值
*  参数说明：  
*  返回值：    
*/
FLOAT32_S AbsFloat32Func(FLOAT32_S value);

/*
*  功能描述:求INI32类型的数据的绝对值
*  参数说明：  
*  返回值：    
*/
INT32_S AbsInt32Func(INT32_S value);

/*
*  功能描述:求INI16类型的数据的绝对值
*  参数说明：  
*  返回值：    
*/
INT16_S AbsInt16Func(INT16_S value);

#ifdef __cplusplus
}
#endif

#endif
