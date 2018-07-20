/************************************************************************
*
* 文件名   ：  SwitchDefine.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  道岔宏定义
* 备  注   ：  无
*
************************************************************************/
#ifndef SWITCH_DEFINE_H_
#define SWITCH_DEFINE_H_

#include "../../SysDataManager/SysDefine.h"

/*道岔总数最大值*/
#define SWITCH_SUM_MAX                            500U    /*定义道岔最大值*/

/*本地管理的道岔总数最大值*/
#define SWITCH_LOCAL_SUM_MAX                      50U     /*定义本地管理的道岔最大值*/

/*道岔锁闭/未锁闭状态*/
#define SWITCH_STATE_LOCK                         0x55U   /*道岔锁闭*/
#define SWITCH_STATE_UNLOCK                       0xaaU   /*道岔未锁闭*/

/*道岔占用/空闲状态*/
#define SWITCH_STATE_OCCUPY                       0x55U   /*道岔占用*/
#define SWITCH_STATE_FREE                         0xaaU   /*道岔空闲*/

/*道岔状态(定，反，四开)*/
#define SWITCH_STATE_MAIN                         1U	     /*道岔定位状态*/
#define SWITCH_STATE_SIDE                         2U		 /*道岔反位状态*/
#define SWITCH_STATE_LOSE                         3U		 /*道岔失表状态*/

/*道岔位置区域*/
#define SWITCH_POSITION_DEPOT                     0x55U   /*车辆段/停车场道岔*/
#define SWITCH_POSITION_MAIN                      0xaaU   /*正线道岔*/

/*道岔包含的最大计轴区段数量*/
#define SWITCH_BELONG_AC_SUM_MAX                  12U     /*道岔包含的最大计轴区段数量*/

#endif
