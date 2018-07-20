
/************************************************************************
*
* 文件名   ：  CRC32.h
* 版权说明 ：   
* 版本号   ：  1.0
* 创建时间 ：  2009.08.21
* 作者     ：   
* 功能描述 ：  计算32位CRC函数  
* 使用注意 ： 
* 修改记录 ：  
*
************************************************************************/

#ifndef CRC32_H_
#define CRC32_H_

#include "CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif



/*
*  功能描述： CRC32函数，计算过程如下，注意：计算CRC是从输入数据第一个字节的最高BIT开始的
*  参数说明：
*             pData,    数据指针
*             DataLen,  数据长度（字节）
*  返回值：   返回值为CRC值
*/
UINT32_S Crc32(const UINT8_S *pData,UINT32_S DataLen);


#ifdef __cplusplus
}
#endif

#endif

