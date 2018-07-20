/********************************************************
*                                                                                                            
* 文 件 名： AbsFun.c
* 版权说明：  
* 创建时间： 2013-10-25
* 作    者： 郭文章
* 功能描述： 求绝对值函数 
* 修改记录：   
*
********************************************************/
#include "AbsFun.h"
#include "stdlib.h"
#include "math.h"

/*
*  功能描述:求DouBle类型的数据的绝对值
*  参数说明：  
*  返回值：    
*/
FLOAT64_S AbsFloat64Func(FLOAT64_S value)
{
    FLOAT64_S retVal = 0;/*函数返回值*/
    retVal = fabs(value);

    return retVal;
}


/*
*  功能描述:求Float类型的数据的绝对值
*  参数说明：  
*  返回值：    
*/
FLOAT32_S AbsFloat32Func(FLOAT32_S value)
{
    FLOAT32_S retVal = (FLOAT32_S)0;/*函数返回值*/
    retVal = (FLOAT32_S)fabs((FLOAT64_S)value);

    return retVal;
}

/*
*  功能描述:求INI32类型的数据的绝对值
*  参数说明：  
*  返回值：    
*/
INT32_S AbsInt32Func(INT32_S value)
{
    INT32_S retVal = 0;/*函数返回值*/
    retVal = abs(value);

    return retVal;
}

/*
*  功能描述:求INI16类型的数据的绝对值
*  参数说明：  
*  返回值：    
*/
INT16_S AbsInt16Func(INT16_S value)
{
    INT16_S retVal = 0;/*函数返回值*/
    retVal = abs(value);

    return retVal;
}
