/************************************************************************
*
* 文件名   ：  DRDefine.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  无人折返宏定义
* 备  注   ：  无
*
************************************************************************/
#ifndef DR_DEFINE_H_
#define DR_DEFINE_H_

#include "../../SysDataManager/SysDefine.h"

/*无人折返按钮总数最大值*/
#define DR_BUTTON_SUM_MAX                  20U     /*定义无人折返按钮最大值*/

/*无人折返灯总数最大值*/
#define DR_LAMP_SUM_MAX                    20U     /*定义无人折返灯最大值*/

/*本地管理的无人折返灯总数最大值*/
#define DR_BUTTON_LOCAL_SUM_MAX            5U      /*定义本地管理的无人折返按钮最大值*/

/*本地管理的无人折返灯总数最大值*/
#define DR_LAMP_LOCAL_SUM_MAX              5U      /*定义本地管理的无人折返灯最大值*/


/*无人折返灯状态*/
#define DR_LAMP_TWINKLE_STATUS             0x55U   /*无人折返灯闪灯状态*/
#define DR_LAMP_STEADY_STATUS              0xaaU   /*无人折返灯稳灯状态*/
#define DR_LAMP_DEFAULT_STATUS             0xffU   /*无人折返灯无效状态*/

/*无人折返按钮状态*/
#define DR_BUTTON_STATE_DOWN               0x55U   /*无人折返按钮按下*/
#define DR_BUTTON_STATE_UP                 0xaaU   /*无人折返按钮未按下*/


#endif
