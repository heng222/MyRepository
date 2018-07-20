/************************************************************************
*
* 文件名   ：  MainLogicManager.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  应用函数主逻辑处理
* 备  注   ：  无
*
************************************************************************/
#ifndef MAIN_LOGIC_MANAGER_H_
#define MAIN_LOGIC_MANAGER_H_

#include "../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
* 功能描述： ZC子系统应用程序主逻辑管理
* 参数说明： 无
* 返回值  ： 1:逻辑执行正常
*            0:逻辑执行异常
*/
UINT8_S ZcAppMainLogicManager(void);

/*
* 功能描述： ZC子系统应用程序入口函数
* 参数说明： 无
* 返回值  ： 1:逻辑执行正常
*            0:逻辑执行异常
*/
INT8_S ZcSystemAppMain(void);

#ifdef __cplusplus
}
#endif

#endif
