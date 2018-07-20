/************************************************************************
 文件名：  MADefine.h
 作者  ：  ZC组
 创建时间 ：  2015-04-18
 描述 ：  移动授权宏定义
 备注 ： 无
************************************************************************/
#ifndef MA_DEFINE_H_
#define MA_DEFINE_H_

#include "../../SysDataManager/SysDefine.h"
#include "../../LineDataManager/Route/RouteDefine.h"
#include "../Train/TrainDefine.h"

/*移动授权内最大的障碍物数量*/
#define MA_AREA_OBS_SUM_MAX              (ROUTE_OF_OBS_SUM_MAX * SIZE_MAX_ROUTENUM)    /*定义屏蔽门最大值*/

/*移动授权内最大的临时限速数量*/
#define MA_AREA_TSR_SUM_MAX              20U                                          /*定义移动授权内最大的临时限速数量*/

/*MA终点属性定义*/
#define	MA_END_ATT_CBTC					 1U			                                  /*退出CBTC终点*/
#define MA_END_ATT_REVERT				 2U			                                  /*折返点*/
#define	MA_END_ATT_OTHER			     3U			                                  /*其他类型终点*/

/*MA终点障碍物类型*/
#define MA_OBS_TYPE_COMM_UNCT_TRAIN      1U

/*MA类型*/
#define NORMAL_MA_TYPE                   0xaaU                                        /*正常移动授权*/
#define ABNORMAL_MA_TYPE                 0x55U                                        /*紧急制动移动授权*/
#define CANCELLATION_MA_TYPE             0x88U                                        /*注销类型的移动授权*/
#define NO_MA_TYPE                       0xddU                                        /*无移动授权*/

#endif
