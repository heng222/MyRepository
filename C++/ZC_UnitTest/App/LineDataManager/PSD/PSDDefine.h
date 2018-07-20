/************************************************************************
*
* 文件名   ：  PSDDefine.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  屏蔽门宏定义
* 备  注   ：  无
*
************************************************************************/
#ifndef PSD_DEFINE_H_
#define PSD_DEFINE_H_

#include "../../SysDataManager/SysDefine.h"

/*屏蔽门总数最大值*/
#define PSD_SUM_MAX                          200U    /*定义屏蔽门最大值*/

/*本地管理的屏蔽门总数最大值*/
#define PSD_LOCAL_SUM_MAX                    20U     /*定义本地管理的屏蔽门最大值*/

/*紧急停车按钮状态*/
#define PSD_STATE_OPEN                       0x55U   /*屏蔽门打开*/
#define PSD_STATE_CLOSE                      0xaaU   /*屏蔽门关闭*/

#endif
