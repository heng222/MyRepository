/************************************************************************
*
* 文件名   ：  CommTargetDefine.h
* 作  者   ：  ZC组
* 创建时间 ：  2015.07.14
* 功能描述 ：  通讯目标定义 
* 备  注   ：  无
*
************************************************************************/
#ifndef COMM_TARGET_DEFINE_H_
#define COMM_TARGET_DEFINE_H_

#include "../../SysDataManager/SysDefine.h"

/*zc单个设备类型通信对象总数最大值(除列车外的其他固定设备)*/
#define SINGLE_TYPE_COMM_TARGET_SUM_MAX                 6U                           /*通信对象总数最大值*/

/*设备类型通信对象总数最大值（其他通信对象）*/
#define COMM_TARGET_ID_MAX                              (LINE_CI_SUM_MAX)             /*通信对象总数最大值（其他通信对象）*/

/*设备类型通信对象总数最大值（通信列车）*/
#define COMM_TRAIN_ID_MAX                               (LINE_MAX_TRAIN_ID)           /*通信对象总数最大值（通信列车）*/

/*定义ZC通信的最大设备类型数量（除去列车外的其他固定设备）*/
#define COMM_TYPE_SUM_MAX                               6U                           /*ZC通信的最大设备类型数量*/  


/*通信状态定义*/
#define COMM_STATUS_NORMAL                              ((UINT8_S)(0xaaU))                        /*通信状态正常*/
#define COMM_STATUS_ABNORMAL                            ((UINT8_S)(0x55U))                        /*通信状态异常*/

#endif
