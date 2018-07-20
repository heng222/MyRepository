/************************************************************************
*
* 文件名   ：  MaskDefine.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  码位的宏定义
* 备  注   ：  无
*
************************************************************************/
#ifndef MASK_DEFINE_H_
#define MASK_DEFINE_H_

#include "../../SysDataManager/SysDefine.h"

/*ZC到CI的码位数量总数最大值*/
#define ZC_TO_CI_MASK_SUM_MAX                5000U      /*ZC到CI的码位数量总数最大值*/

/*单个ZC到CI的码位数量总数最大值*/
#define SINGLE_ZC_TO_CI_MASK_SUM_MAX         1000U      /*ZC到CI的码位数量总数最大值*/

/*CI到ZC的码位数量总数最大值*/
#define CI_TO_ZC_MASK_SUM_MAX                5000U      /*CI到ZC的码位数量总数最大值*/

/*单个CI到ZC的码位数量总数最大值*/
#define SINGLE_CI_TO_ZC_MASK_SUM_MAX         1000U      /*CI到ZC的码位数量总数最大值*/

/*本地管理的单个码位对应的设备数量最大值*/
#define SINGLE_MASK_DEVICE_SUM_MAX           5U         /*本地管理的单个码位对应的设备数量最大值*/


/*定义ZC与CI通信码位长度信息*/
#define CI_ZC_SWITCH_MASK_LEN                8U         /*CI-ZC道岔长度信息*/
#define CI_ZC_SIGNAL_MASK_LEN                8U         /*CI-ZC信号机长度信息*/
#define CI_ZC_PSD_MASK_LEN                   4U         /*CI-ZC-PSD长度信息*/
#define CI_ZC_ESB_MASK_LEN                   4U         /*CI-ZC-ESB长度信息*/
#define CI_ZC_AC_SGMT_MASK_LEN               14U        /*CI-ZC计轴区段长度信息*/ 
#define CI_ZC_SECTION_MASK_LEN               6U         /*CI-ZC逻辑区段长度信息*/
#define CI_ZC_ROUTE_MASK_LEN                 8U         /*CI-ZC进路长度信息*/  /* 4->8 */
#define CI_ZC_OVERLAP_MASK_LEN               4U         /*CI-ZC保护区段长度信息*/
#define CI_ZC_DR_MASK_LEN                    8U         /*CI-ZC无人折返长度信息*/

/*定义ZC与CI码位类型信息*/
#define SWITCH_FRONT_MASK_TYPE               1U         /*道岔定位信息码位类型*/
#define SWITCH_SIDE_MASK_TYPE                2U         /*道岔反位信息码位类型*/
#define SWITCH_LOCK_MASK_TYPE                3U         /*道岔锁闭信息码位类型*/
#define SIGNAL_STATUS_MASK_TYPE              4U         /*信号机状态信息码位信息*/
#define SIGNAL_CROSS_MASK_TYPE               5U         /*信号机跨压信息码位信息*/
#define SIGNAL_LIGHT_OFF_MASK_TYPE           6U         /*信号机亮灭灯信息码位信息*/
#define PSD_STATUS_MASK_TYPE                 7U         /*PSD状态信息码位信息*/
#define ESB_STATUS_MASK_TYPE                 8U         /*ESB状态信息码位信息*/
#define AC_UP_DIR_MASK_TYPE                  9U         /*计轴上行方向状态信息码位信息*/
#define AC_DOWN_DIR_MASK_TYPE                10U        /*计轴下行方向状态信息码位信息*/
#define AC_OCC_STATUS_MASK_TYPE              11U        /*计轴占用状态信息码位信息*/
#define AC_LOCK_STATUS_MASK_TYPE             12U        /*计轴锁闭状态信息码位信息*/
#define AC_ARB_STATUS_MASK_TYPE              13U        /*计轴ARB状态信息码位信息*/
#define AC_STOP_STATUS_MASK_TYPE             14U        /*计轴停稳状态信息码位信息*/
#define SECTION_UT_OCC_MASK_TYPE             15U        /*逻辑区段UT占用状态信息码位信息*/
#define SECTION_CT_OCC_MASK_TYPE             16U        /*逻辑区段CT占用状态信息码位信息*/
#define SECTION_TSR_MASK_TYPE                17U        /*逻辑区段临时限速状态信息码位信息*/
#define ROUTE_STATUS_MASK_TYPE               18U        /*进路状态信息码位信息*/
#define OVERLAP_STATUS_MASK_TYPE             19U        /*保护区段状态信息码位信息*/
#define DR_LAMP_TWINKLE_STATUS_MASK_TYPE     20U        /*无人折返灯闪灯信息码位信息*/
#define DR_LAMP_STEADY_STATUS_MASK_TYPE      21U        /*无人折返灯稳灯信息码位信息*/
#define DR_BUTTON_STATUS_MASK_TYPE           22U        /*无人折返按钮站台信息码位信息*/
#define ROUTE_STOP_REQUEST_MASK_TYPE         23U        /* 进路停车保证请求码位 */
#define ROUTE_STOP_CONFIRM_MASK_TYPE         24U        /* 进路停车保证确认码位 */

#endif
