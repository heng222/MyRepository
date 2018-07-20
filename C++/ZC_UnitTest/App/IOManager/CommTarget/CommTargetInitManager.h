/************************************************************************
*
* 文件名   ：  CommTargetInitManager.h
* 作者     ：  ZC组
* 创建时间 ：  2015.07.14
* 功能描述 ：  通讯目标初始化
* 备  注   ：  无
*
************************************************************************/

#ifndef COMM_TARGET_INIT_MANAGER_H_
#define COMM_TARGET_INIT_MANAGER_H_

#include "../../../Common/CommonTypes.h"
#include "CommTargetDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
* 函数名称： InitCommTargetInfo
* 功能描述： 初始化通信对象关系
* 输入参数： void    
* 输出参数： 无
* 返回值  ： 0u: 初始化失败
*			 1u: 初始化成功
*/
UINT8_S InitCommTargetInfo(void);

/*
* 函数名称： InitOtherCommTargetInfo
* 功能描述： 初始化其他通信对象（非列车）的通信关系
* 输入参数： void   
* 输出参数： 无
* 返回值  ： 0u: 初始化失败
*			 1u: 初始化成功
*/
UINT8_S InitOtherCommTargetInfo(void);

/*
* 函数名称： InitTrainCommTargetInfo
* 功能描述： 初始化列车通信对象的通信关系
* 输入参数： void    
* 输出参数： 无
* 返回值  ： 无
*/
void InitTrainCommTargetInfo(void);
	
#ifdef __cplusplus
}
#endif

#endif
