/************************************************************************
 文件名：  TrainDefine.h
 作者  ：  ZC组
 创建时间 ：  2015-07-01
 描述 ：  列车宏定义
 备注 ： 无
************************************************************************/
#ifndef TRAIN_DEFINE_H_
#define TRAIN_DEFINE_H_

#define SIZE_MAX_ROUTENUM  3U			/*列车已匹配进路数量*/
#define SIZE_MAX_LINE_TRAIN 150U         /*本线最大可能的列车数量*/
#define SIZE_MAX_CONTROLE_TRAIN 40U		/*本ZC控制范围内最大列车数量*/

#define TRAIN_ERROR_MAX_NUM      500U    /*列车最大不确定误差*/

#define TRAIN_MIN_SPEED          14U     /*定义列车最小的速度*/

/*列车类型*/
#define TRAIN_MODE_CBTC                     1U                 /*受ZC控制列车*/
#define TRAIN_MODE_TO_RM0                   2U                 /*等待降级为RM0的列车*/
#define TRAIN_MODE_RM                       3U                 /*正线恢复列车*/
#define TRAIN_MODE_RM0                      4U                 /*正线恢复RM0列车*/
#define TRAIN_MODE_IN                       5U                 /*出段列车*/
#define TRAIN_MODE_OUT                      6U                 /*注销列车*/

/*列车状态*/
#define TRAIN_STATE_MOVING                  1U                 /*正常运行状态*/
#define TRAIN_STATE_HANDOVER                2U                 /*移交状态*/
#define TRAIN_STATE_TAKEOVER                3U                 /*接管状态*/
#define TRAIN_STATE_REVERSE                 4U                 /*折返状态*/
#define TRAIN_STATE_CANCELLATION            5U                 /*注销状态*/
#define TRAIN_STATE_FAILURE                 6U                 /*故障状态*/

/*列车当前输入模式*/
#define TRAIN_IN_MODE_RM                    1U                 /*RM模式*/
#define TRAIN_IN_MODE_CM                    2U                 /*ATP模式*/
#define TRAIN_IN_MODE_AM                    3U                 /*ATO模式*/
#define TRAIN_IN_MODE_EUM                   4U                 /*BYPASS模式*/
#define TRAIN_IN_MODE_RD                    5U                 /*RD模式*/

/*列车运行级别*/
#define TRAIN_IN_LEVEL_CBTC                    3U                 /*CBTC运行级别*/
#define TRAIN_IN_LEVEL_BLOC                    2U                 /*BLOC运行级别*/
#define TRAIN_IN_LEVEL_IL                      1U                 /*IL运行级别*/

/*列车输入信息*/
#define TRAIN_IN_APPLY_MA                   1U                 /*申请MA*/
#define TRAIN_IN_HANDOVERTOCANCEL           2U                 /*切换注销申请*/
#define TRAIN_IN_REVERSETOCANCEL            4U                 /*折返注销申请*/
#define TRAIN_IN_TOEXITCBTC                 3U                 /*退出CBTC申请*/
#define TRAIN_IN_CHANGED                    5U                 /*列车换端完成*/


/*列车输出信息*/
#define OUT_TRAIN_MOVING                    1U                 /*正常运行(发出MA)*/
#define OUT_TRAIN_HANDOVERTOCANCEL          2U                 /*切换注销确认*/
#define OUT_TRAIN_REVERSETOCANCEL           4U                 /*折返注销确认*/
#define OUT_TRAIN_TOEXITCBTC                3U                 /*退出CBTC确认*/
#define OUT_TRAIN_CHANGED                   5U                 /*列车换端完成确认*/

/*与ZC交互切换信息*/
#define NZC_TRAIN_DEFAULT                   0U                 /*无状态*/
#define NZC_TRAIN_HANDOVER                  1U                 /*移交申请*/
#define NZC_TRAIN_CONFIRMATION              2U                 /*移交申请确认*/
#define NZC_TRAIN_HADTOOKOVER               3U                 /*已接管*/
#define NZC_TRAIN_MANAGENOHAND              4U                 /*移交未切换*/
#define NZC_TRAIN_MANAGENOTAKE              5U                 /*接管未切换*/

/*列车期望运行方向*/
#define TRAIN_UNSAFE_DIR_UP                 0x55U              /*列车期望运行方向-上行*/
#define TRAIN_UNSAFE_DIR_DOWN               0xaaU              /*列车期望运行方向-下行*/

#define SIZE_MAX_SECTION_OF_TRAIN            10U      /*列车占压的最大逻辑区段数量*/

#define SIZE_MAX_SWITCH_MUM_OF_SAFE_TRAIN   10U                /*列车安全位置计算时使用的道岔数量*/

#endif
