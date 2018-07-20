/************************************************************************
*
* 文件名   ：  SignalDefine.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  信号机宏定义
* 备  注   ：  无
*
************************************************************************/
#ifndef SIGNAL_DEFINE_H_
#define SIGNAL_DEFINE_H_

#include "../../SysDataManager/SysDefine.h"

/*紧信号机总数最大值*/
#define SIGNAL_SUM_MAX                        500U    /*定义信号机最大值*/

/*本地管理的信号机总数最大值*/
#define SIGNAL_LOCAL_SUM_MAX                  (100U+120U)     /*定义本地管理的信号机最大值*/

/*信号机的当前状态*/
#define SIGNAL_STATE_PASS                     0x55U   /*信号机通过信号*/
#define SIGNAL_STATE_STOP                     0xaaU   /*信号机停止信号*/

/*信号机的亮灭灯命令状态*/
#define SIGNAL_LIGHT_COMMAND                  0x55U   /*信号机亮灯命令*/
#define SIGNAL_OFF_COMMAND                    0xaaU   /*信号机灭灯命令*/

/*信号机的列车跨压状态*/
#define SIGNAL_TRAIN_ALREADY_CROSS            0x55U   /*信号机列车已跨压状态*/
#define SIGNAL_TRAIN_NOT_CROSS                0xaaU   /*信号机列车未跨压状态*/

/*判断信号机亮灭区域包含的最大计轴数量*/
#define SIGNAL_LIGHT_OFF_AC_NUM_MAX           10U     /*包含的计轴区段最大数量*/

#endif
