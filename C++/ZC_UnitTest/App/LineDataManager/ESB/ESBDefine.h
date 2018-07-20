/************************************************************************
*
* 文件名   ：  ESBDefine.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  紧急停车按钮宏定义
* 备  注   ：  无
*
************************************************************************/
#ifndef ESB_DEFINE_H_
#define ESB_DEFINE_H_

#include "../../SysDataManager/SysDefine.h"

/*紧急停车按钮总数最大值*/
#define ESB_SUM_MAX                 200U    /*定义紧急停车按钮最大值*/

/*本地管理的紧急停车按钮总数最大值*/
#define ESB_LOCAL_SUM_MAX           20U     /*定义本地管理的紧急停车按钮最大值*/

/*紧急停车按钮状态*/
#define ESB_STATE_DOWN                     0x55U   /*紧急停车按钮按下*/
#define ESB_STATE_UP                       0xaaU   /*紧急停车按钮未按下*/

#endif
