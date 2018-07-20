/************************************************************************
 文件名   ：  TrainInitManager.h 
 创建时间 ：  2015.07.02
 作者     ：  ZC组
 描述 ：  列车初始化管理
 备注 ： 无
************************************************************************/
#ifndef TRAIN_INIT_MANAGER_H_
#define TRAIN_INIT_MANAGER_H_


#include "TrainDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

/*************************************************
  函数名:      InitTrainLocalInfo
  功能描述:    初始化本地管理的列车信息
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void InitTrainLocalInfo(void);

#ifdef __cplusplus
}
#endif

#endif
