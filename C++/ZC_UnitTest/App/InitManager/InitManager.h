/********************************************************                                                                                                            
 文 件 名： InitManager.h  
 作    者： ZC组
 创建时间： 2015-06-04
 描述： 初始化使用数据
 备注： 无  
********************************************************/

#ifndef INIT_MANAGER_H_
#define INIT_MANAGER_H_

#include "../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

/*************************************************
  函数名:      InitAllLocalInfo
  功能描述:    初始化本地所有信息
  输入:        无
  输出:        无
  返回值:      0: 初始化失败
               1: 初始化成功
*************************************************/
INT8_S InitAllLocalInfo(void);

/*************************************************
  函数名:      InitAllConfigData
  功能描述:    初始化本地所有配置信息
  输入:        无
  输出:        无
  返回值:      RETURN_ERROR:   初始化失败
               RETURN_SUCCESS: 初始化成功
*************************************************/
UINT8_S InitAllConfigData(void);

/*************************************************
  函数名:      InitAllLocalLineData
  功能描述:    初始化本地所有线路信息
  输入:        无
  输出:        无
  返回值:      RETURN_ERROR:   初始化失败
               RETURN_SUCCESS: 初始化成功
*************************************************/
UINT8_S InitAllLocalLineData(void);

/*************************************************
  函数名:      InitAllStaticData
  功能描述:    初始化本地所有全局数据部分信息
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void InitAllStaticData(void);

#ifdef __cplusplus
}
#endif

#endif
