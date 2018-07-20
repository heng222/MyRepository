/********************************************************
*                                                                                                            
* 文 件 名： AdptAppCommonDef.h   
* 作    者： 董欣 
* 创建时间： 2016-09-01
* 功能描述： 接口定义头文件 
* 备    注： 无 
*
********************************************************/ 

#ifndef ADPT_APP_COMMON_DEF_H
#define ADPT_APP_COMMON_DEF_H

#include "../../Common/CommonTypes.h"

#define UDP_OUT_FRAME_LEN           1400u                /*UDP输出一帧数据最大长度*/

/*设备状态相关宏定义*/
#define DEV_STATE_EXIST_NO         1u                   /*设备不存在*/
#define DEV_STATE_INIT             2u                   /*设备初始化*/
#define DEV_STATE_NORMAL           4u                   /*设备正常状态 */
#define DEV_STATE_FAULT            5u                   /*设备故障状态 */
#define DEV_STATE_SELFCHECK        6u                   /*设备自检*/

/*网关-通信设备类型*/
#define MIC_R_NUM        3u                       /* 普通设备网关数目 */
#define DEVTYPE_MIC_R    0x0bu                    /* 普通设备网关类型 */ 
#define DEVTYPE_MIC_NTP  0x0cu                    /* NTP设备网关类型 */ 

#define DEVTYPE_CI       0x3cu                    /*CI数据类型恒比码*/    
#define DEVTYPE_ZC       0x1eu                    /*相邻ZC数据恒比码*/    
#define DEVTYPE_ATS      0x03u                    /*ATS数据恒比码*/
#define DEVTYPE_VOBC     0x14u                    /*VOBC恒比码*/
#define DEVTYPE_NTP      0x33u                    /*NTP恒比码*/

#define DEVTYPE_SIM      0x1au                    /*仿真恒比码*/
#define DEVTYPE_NMS      0x34u                    /*NMS恒比码*/
#define DEVTYPE_DMS      0x2bu                    /* DMS数据恒比码 */  
#define DEVTYPE_TESTPC   0x11u                    /*动静调上位机恒比码*/

/*非网关-通信设备类型(类型不变)*/
#define DEVTYPE_ATP      0x13u                    /*ATP恒比码1d*/
#define DEVTYPE_ATO      0x08u                    /*ATO恒比码1c*/
#define DEVTYPE_DMI      0x07u                    /*DMI恒比码2a*/
#define DEVTYPE_RADA     0x0Au                    /*雷达恒比码2c*/
#define DEVTYPE_BTM      0x09u                    /*BTM恒比码2d*/
#define DEVTYPE_UNUSED   0xffu                    /*不用的恒比码*/

#define DEVTYPE_MAINTAIN 0x1bu                    /* 调试日志设备类型 */
#define DEVTYPE_RECORD   0x1cu                    /* 记录仪设备类型 */
#define DEVTYPE_TEST     0x0fu                    /* 为调试BTM仿真增加设备类型 */ 




#define  FUNC_TURE                  0x55u               /*成功*/
#define  FUNC_FALSE                 0xAAu               /*失败*/
#define  FUNC_WAIT                  0xFFu               /*等待*/





/*开关相关宏定义*/

#define SWITCH_COL_INVALID          0xAAu               /*采集开关有效*/
#define SWITCH_COL_VALID            0x55u               /*采集开关无效*/

#define SWITCH_DRV_INVALID          0xAAu               /*驱动开关无效*/
#define SWITCH_DRV_VALID            0x55u               /*驱动开关有效*/


/*速度相关宏定义*/
#define TRAIN_DIR_FORWARD           0x55u               /*运行方向:前进*/
#define TRAIN_DIR_BACK              0xAAu               /*运行方向:后退*/
#define TRAIN_DIR_NO                0x00u               /*运行方向:未知(未获取到)*/
#define TRAIN_DIR_INVALID           0xFFu               /*运行方向:无效(获取到方向，但方向不合法)*/

#define ACC_DIR_FRONT               0x55u               /*正向加速度(加速度)*/
#define ACC_DIR_BACK                0xAAu               /*反向加速度(减速度)*/


#define WHEEL_STATUS_NORMAL         0x55u               /*轮转状态正常*/
#define WHEEL_STATUS_SPIN           0x11u               /*轮转状态空转*/
#define WHEEL_STATUS_ROLLER         0x22u               /*轮转状态轮滑*/
#define WHEEL_STATUS_UNKOWN         0xAAu               /*轮转状态未知*/


#define TRAIN_SPEED_INVLID          0xFFFFu             /*速度无效值*/
#define ACC_INVLID                  0xFFFFu             /*加速度无效值*/
#define SPACE_INVLID                FLOAT32_MAX         /*距离无效值*/
#define SENSOR_SPACE_INVLID         0xFFFFFFFFu         /*速度传感器累计距离无效值*/


#define INFOR_FLAG_VALID            0x55u               /*信息有效*/
#define INFOR_FLAG_INVALID          0xAAu               /*信息无效*/



/*是否需要更新SFI参数*/
#define ODO_PARA_UPDATE_YES            1u                /* 需要更新参数*/
#define ODO_PARA_UPDATE_NO             0u                /* 无需更新参数*/

/*是否需要校正距离*/
#define ODO_CALIB_YES            1u                /* 需要校正距离*/
#define ODO_CALIB_NO             0u                /* 无需校正距离*/

/*************************************************输出开关量定义*******************************************/
/*ATP应用使用的所有开关量输出包括:紧急制动,左门使能,右门使能,牵引切断,AR指示灯输出,ATO使能输出,AR继电器输出,共7个*/


/*安全输出:7*/
#define ATP_EB_OUTPUT                      ((UINT32_S)0x00000001u)    /*紧急制动*/
#define ATP_QYQD_OUTPUT                    ((UINT32_S)0x00000010u)    /*牵引切断*/
#define ATP_LEFTDOOR_EN_OUTPUT             ((UINT32_S)0x00000004u)    /*左门使能*/
#define ATP_RIGHTDOOR_EN_OUTPUT            ((UINT32_S)0x00000008u)    /*右门使能*/
#define ATP_ATO_ENABLE1_OUTPUT             ((UINT32_S)0x00000040u)    /*ATO使能输出1*/
#define ATP_ATO_ENABLE2_OUTPUT             ((UINT32_S)0x00000100u)    /*ATO使能输出2*/
#define ATP_ZERO_SPEEDSIG_OUTPUT           ((UINT32_S)0x00000200u)    /*零速信号*/

/*非安全输出:2*/
#define ATP_AR_LAMP_OUTPUT                 ((UINT32_S)0x00000020u)    /*AR指示灯输出*/
#define ATP_AR_RELAY_OUTPUT                ((UINT32_S)0x00000080u)    /*AR继电器吸起输出*/


/********************************************end of 输出开关量定义******************************************/



/*******************************************输入开关量定义  START*******************************************/




/*ATP安全输入:8个*/
#define ATP_KEY_OPEN_INPUT              ((UINT32_S)0x00001000u)   /*司机钥匙输入,即驾驶室激活*/
#define ATP_TRAIN_INTEG_INPUT           ((UINT32_S)0x00002000u)   /*列车完整*/
#define ATP_DOOR_CLOSED_INPUT           ((UINT32_S)0x00004000u)   /*车门关闭且锁闭*/
#define ATP_QYQD_VALID_INPUT            ((UINT32_S)0x00008000u)   /*牵引已切断*/
#define ATP_EB_VALID_INPUT              ((UINT32_S)0x00010000u)   /*列车已实施紧急制动*/
#define ATP_BCZD_VALID_INPUT            ((UINT32_S)0x00020000u)   /*已实施保持制动*/
#define ATP_SB_RIGHT_INPUT              ((UINT32_S)0x00040000u)   /*牵引制动手柄在零位且方向手柄在向前位*/
#define ATP_ASSURE_INPUT                ((UINT32_S)0x00080000u)   /*确认按钮按下*/

/*ATP非安全输入:10个*/
#define ATP_EUM_SWITCH_INPUT            ((UINT32_S)0x00000100u)   /*EUM开关激活*/
#define ATP_ATO_START_INPUT             ((UINT32_S)0x00000001u)   /*ATO启动1按钮已按下*/
#define ATP_ATO_START2_INPUT            ((UINT32_S)0x01000000u)   /*ATO启动2按钮已按下*/
#define ATP_MODE_UP_INPUT               ((UINT32_S)0x00000002u)   /*模式升选择*/
#define ATP_MODE_DOWN_INPUT             ((UINT32_S)0x00000004u)   /*模式降选择*/
#define ATP_AR_INPUT                    ((UINT32_S)0x00000008u)   /*AR按钮按下*/
#define ATP_RIGHT_DOOR_OPEN_INPUT       ((UINT32_S)0x00000040u)   /*右门开门按钮按下*/
#define ATP_RIGHT_DOOR_CLOSE_INPUT      ((UINT32_S)0x00000080u)   /*右门关门按钮按下*/
#define ATP_LEFT_DOOR_OPEN_INPUT        ((UINT32_S)0x00000200u)   /*左门开门按钮按下*/
#define ATP_LEFT_DOOR_CLOSE_INPUT       ((UINT32_S)0x00000400u)   /*左门关门按钮按下*/





/********************************************输入开关量定义 end*****************************************/


#endif
