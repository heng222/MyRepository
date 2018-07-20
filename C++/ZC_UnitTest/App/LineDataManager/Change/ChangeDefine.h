/********************************************************                                                                                                           
 文 件 名： ChangeDefine.h
 作    者： ZC组
 创建时间： 2015.04.18
 描述： 切换区域宏定义  
 备注： 无  
********************************************************/ 


#ifndef CHANGE_DEFINE_H_
#define CHANGE_DEFINE_H_

#include "../../SysDataManager/SysDefine.h"

/*切换线路总数最大值*/
#define CHANGE_LINE_SUM_MAX                      300U    /*定义切换线路最大值*/

/*本地管理的切换线路总数最大值*/
#define CHANGE_LINE_LOCAL_SUM_MAX                30U     /*定义本地管理的切换线路最大值*/

#define CHANGE_LINE_SWITCH_MAX                   10U     /*定义单条线路包含的最大道岔数量*/

/*切换区域总数最大值*/
#define CHANGE_AREA_SUM_MAX                      50U    /*定义切换区域最大值*/

/*本地管理的切区域路总数最大值*/
#define CHANGE_AREA_LOCAL_SUM_MAX                30U     /*定义本地管理的切换区域最大值*/

#define CHANGE_AREA_OBS_MAX                      50U     /*定义单个区域包含的最大障碍物数量*/

#define CHANGE_AREA_ROUTE_MAX                    20U
#define CHANGE_AREA_OVERLAP_MAX                  20U
#define CHANGE_AREA_SIGNAL_MAX                   20U
#define CHANGE_AREA_SWITCH_MAX                   20U
#define CHANGE_AREA_PSD_MAX                      20U
#define CHANGE_AREA_ESB_MAX                      20U
#define CHANGE_AREA_DRBUTTON_MAX                 20U
#define CHANGE_AREA_DRLAMP_MAX                   20U
#define CHANGE_AREA_AC_MAX                       50U
#define CHANGE_AREA_LOGIC_MAX                    500U

/*相邻ZC码位值*/
#define  BIT_TRUE				1U
#define  BIT_FALSE              0U
#define  BIT_DEFAULT            2U
#define  BIT_LOSE               3U               /*道岔四开*/

/*相邻ZC切换区域最大的障碍物码位大小*/
#define ZC_NZC_MASK_NUM_MAX     1000U             /*码位最大值*/

/*定义ZC-NZC码位表大小*/
#define ZC_NZC_SWITCH_MASK_SUM     10U           /*道岔码位数据大小*/
#define ZC_NZC_SIGNAL_MASK_SUM     8U            /*信号机码位数据大小*/
#define ZC_NZC_PSD_MASK_SUM        8U            /*屏蔽门码位数据大小*/
#define ZC_NZC_ESB_MASK_SUM        8U            /*紧急停车按钮码位数据大小*/
#define ZC_NZC_AC_MASK_SUM         9U            /*计轴区段码位数据大小*/  /*8->9*/
#define ZC_NZC_ROUTE_MASK_SUM      8U            /*进路码位数据大小*/
#define ZC_NZC_OVERLAP_MASK_SUM    8U            /*保护区段码位数据大小*/
#define ZC_NZC_DR_MASK_SUM         10U           /*无人折返（包括按钮和灯）码位数据大小*/

/* 定义计轴区段可切换的方向 */
#define AC_CHANGER_DIR_DOUBLE  0xccU   /* 正切和反切 */
#endif
