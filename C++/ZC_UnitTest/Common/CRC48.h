/******************************************************************************
*  File Name:   CRC48.h
*  Copyright:   Zhuzhou CSR Times Electric Co.,Ltd. All Rights Reserved.
*  Create Date: 20-四月-2012 11:33:59
*  Description: 公用的类型定义、枚举定义，结构定义.
*  REV1.0.0 20054209
******************************************************************************/

#ifndef CRC48_H_
#define CRC48_H_


#include "CommonTypes.h"

/*
*  功能描述： CRC48函数，计算过程如下，注意：计算CRC是从输入数据第一个字节的最高BIT开始的
*             采用的多项式0x4c11db7L，初始值为0x00000000,未镜像，结果异或系数为0x00000000
*             如果DataLen=0，返回值也为0.
*  参数说明： pData,    数据指针
*             DataLen,  数据长度（字节）
*              UINT8_S* reg_aU8 CRC值
*  返回值：   1 成功  0 失败
*/
UINT8_S CRC48(const UINT8_S *pData,UINT32_S DataLen,UINT8_S* reg_aU8);

#endif

