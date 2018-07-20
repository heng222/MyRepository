/************************************************************************
 文件名：  MAInitManager.h
 作者  ：  ZC组
 创建时间 ：  2015-04-18
 描述 ：  移动授权初始化管理
 备注 ： 无
************************************************************************/
#ifndef MA_INIT_MANAGER_H_
#define MA_INIT_MANAGER_H_


#include "MADefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

/*************************************************
  函数名:      InitMaLocalInfo
  功能描述:    初始化本地管理的移动授权信息
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void InitMaLocalInfo(void);

#ifdef __cplusplus
}
#endif

#endif
