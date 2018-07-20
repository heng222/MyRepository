/********************************************************
*                                                                                                            
* 文 件 名： Convert.h
* 版权说明：  
* 创建时间： 2013-10-25
* 作    者： 
* 功能描述： 通用类型转换函数头文件
* 修改记录：   
*
********************************************************/
#ifndef CONVERT_H_
#define CONVERT_H_

#include "CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif


/*
*  功能描述：  用于将2字节数据变为UINT16， BIG endian
*  参数说明：  pInput, 为输入
*  返回值：    变换后的UINT16值
*/
UINT16_S ShortFromChar(const UINT8_S *pInput);

/*
*  功能描述：  用于将4字节数据变为UINT32， BIG endian
*  参数说明：  pInput, 为输入
*  返回值：    变换后的UINT32值
*/
UINT32_S LongFromChar(const UINT8_S *pInput);


/*
*  功能描述：  将2个字节长的整型变为字节表示  BIG endian
*  参数说明：  Input, 为输入
*              pOutput,为输出
*  返回值：  
*/
void ShortToChar ( UINT16_S Input, UINT8_S *pOutput);

/*
*  功能描述：  将3个字节长的整型变为字节表示  BIG endian
*  参数说明：  Input, 为输入
*              pOutput,为输出
*  返回值：  
*/
void ThreeToChar ( UINT32_S Input, UINT8_S *pOutput);

/*
*  功能描述：  将4个字节长的整型变为字节表示  BIG endian
*  参数说明：  Input, 为输入
*              pOutput,为输出
*  返回值：  
*/
void LongToChar(UINT32_S Input, UINT8_S *pOutput);



/*
*  功能描述：  用于将UINT8变为UINT16， LITTLE endian
*  参数说明：  pInput, 为输入
*  返回值：    变换后的UINT16值
*/
UINT16_S ShortFromCharLE(const UINT8_S *pInput);


/*
*  功能描述：  用于将UINT8变为UINT32， LITTLE endian
*  参数说明：  pInput, 为输入
*  返回值：    变换后的UINT32值
*/
UINT32_S LongFromCharLE(const UINT8_S *pInput);

/*
*  功能描述： 将2个字节的整型变为字节表示  LITTLE endian
*  参数说明： Input, 为输入
*             pOutput,为输出
*  返回值： 
*/
void ShortToCharLE ( UINT16_S Input, UINT8_S *pOutput);

/*
*  功能描述： 将4个字节的整型变为字节表示  LITTLE endian
*  参数说明： Input, 为输入
*             pOutput,为输出
*  返回值： 
*/
void LongToCharLE(UINT32_S Input, UINT8_S *pOutput);


#ifdef __cplusplus
}
#endif

#endif
