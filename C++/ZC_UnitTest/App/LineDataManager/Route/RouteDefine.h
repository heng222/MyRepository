/************************************************************************
*
* 文件名   ：  RouteDefine.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  进路宏定义
* 备  注   ：  无
*
************************************************************************/
#ifndef ROUTE_DEFINE_H_
#define ROUTE_DEFINE_H_

#include "../../SysDataManager/SysDefine.h"

/*进路总数最大值*/
#define ROUTE_SUM_MAX                             1200U   /*定义进路最大值*/

/*本地管理的进路总数最大值*/
#define ROUTE_LOCAL_SUM_MAX                       (100U + 210U)    /*定义本地管理的进路最大值*/ /* 210->310 */

/*单个进路内包含的最大计轴区段数量*/
#define ROUTE_OF_AC_SUM_MAX                       20U     /*进路内包含的最大计轴区段数量*/

/*单个进路内包含的最大保护区段数量*/
#define ROUTE_OF_OVERLAP_SUM_MAX                  5U      /*进路内包含的最大计轴区段数量*/

/*单个进路内包含的最大障碍物数量*/
#define ROUTE_OF_OBS_SUM_MAX                      10U     /*进路内包含的最大障碍物数量*/

/*进路状态*/
#define ROUTE_STATE_SET                           0x55U   /*进路已设置*/
#define ROUTE_STATE_UNSET                         0xaaU   /*进路未设置*/

#define ROUTE_STOP_REQ_SET                        0x55U   /* 有进路停车保证请求 */
#define ROUTE_STOP_REQ_UNSET                      0xaaU   /* 无进路停车保证请求 */

#define ROUTE_STOP_CONFIRM_SET                        0x55U   /* 有进路停车保证确认 */
#define ROUTE_STOP_CONFIRM_UNSET                      0xaaU   /* 无进路停车保证确认 */

#endif
