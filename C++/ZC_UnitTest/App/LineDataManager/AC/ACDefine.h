/********************************************************
*                                                                                                            
* 文 件 名： ACDefine.h  
* 创建时间： 2015-05-01
* 作    者： 
* 功能描述： 计轴区段宏定义 
* 备  注  ：  无
*
********************************************************/ 

#ifndef AC_DEFINE_H_
#define AC_DEFINE_H_

/*全线ZC最大ID及本ZC计轴最大数量*/
#define AC_SUM_MAX 2000U
#define LOCAL_AC_SUM_MAX 400U

/*计轴所属区域*/
#define AC_MIAN_CI  0x55U                      /*计轴属于正线CI*/
#define AC_DEPOT_CI  0xaaU                      /*计轴属于车辆段CI*/

/*计轴边界点属性*/
#define CONDOMINIUM_AC_SELF_ZC  0x55U            /*计轴在某个共管区域内，且属于自身ZC*/
#define CONDOMINIUM_AC_NEXT_ZC  0xaaU			 /*计轴在某个共管区域内，且属于相邻ZC*/

/*计轴内列车和逻辑区段*/
#define SIZE_MAX_SECTIONNUM           20U                /*计轴区段内最大逻辑区段数量*/
#define SIZE_MAX_TRAINOFAC            15U                /*计轴区内允许运行的最大列车数量*/

/*计轴区段方向属性*/
#define AC_DIR_UP_STATUS                     0xaaU       /*上行*/
#define AC_DIR_DOWN_STATUS                   0x55U       /*下行*/
#define FORWORD_DIRCTION                     0x55U       /*逻辑正方向*/
#define NEGATIVE_DIRCTION                    0xaaU       /*逻辑反方向*/

/*计轴区段内列车运行方向信息*/
#define AC_DIR_FARAWAY                       1U          /*计轴内运行方向为远离*/
#define AC_DIR_CLOSED                        2U          /*计轴内运行方向为接近*/
#define AC_DIR_DEFAULT                       3U          /*计轴内运行方向为无方向*/

/*计轴区段锁闭/未锁闭属性*/
#define AC_LOCK_STATUS                       0x55U       /*锁闭*/
#define AC_UNLOCK_STATUS                     0xaaU       /*未锁闭*/

/*计轴区段占用/空闲属性*/
#define AC_OCC_STATUS                        0x55U       /*占用*/
#define AC_FREE_STATUS                       0xaaU       /*空闲*/

/*定义计轴区段包含的最大道岔数量*/
#define AC_SWITCH_SUM_MAX                    4U          /*计轴区段包含的最大道岔数量*/

/*计轴区段非通信列车占用/未非通信列车占用属性*/
#define AC_UT_OCC_STATUS                     0x55U       /*计轴非通信列车占用状态*/
#define AC_UT_FREE_STATUS                    0xaaU       /*计轴未非通信列车占用状态*/

/*计轴区段ARB占用/未ARB占用属性*/
#define AC_ARB_OCC_STATUS                    0x55U       /*计轴ARB占用状态*/
#define AC_ARB_FREE_STATUS                   0xaaU       /*计轴未ARB占用状态*/

#define LINK_BELONG_TO_AC_SUM_MAX            5U          /*link所属计轴区段最大数量*/

/*当相邻计轴道岔为四开时，相邻计轴的最大数量*/
#define  MAX_ADJACENT_LOSE_AC                4U

/*计轴清扫状态*/
#define CLEAN_STATUS_DEFAULT                 0U         /*默认状态*/
#define CLEAN_STATUS_HEAD_ENTRY			     1U	       /*车头进入待清扫计轴*/
#define CLEAN_STATUS_ALL_ENTRY			     2U         /*车头车尾均进入待清扫计轴*/
#define CLEAN_STATUS_HEAD_OUT				 3U         /*车头出清待清扫计轴*/
#define CLEAN_STATUS_ALL_OUT				 4U         /*车尾出清待清扫计轴*/

#endif 
