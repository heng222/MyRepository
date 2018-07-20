
/*************************************************
  文件名   ：ReadDataTypeDefine.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： 文件系统文件相关配置类型定义
  备注    ：无。 
*************************************************/


#ifndef    READ_DATA_TYPE_DEFINE_H
#define    READ_DATA_TYPE_DEFINE_H

#define BNF_TABLE_NUM              0xC0u                          /*表个数*/
#define BNP_TABLE_SHEET_MAX_NUM    24u                            /*表中最大SHEET的个数*/

/*线路数据 宏定义*/
#define LINE_DATA_TYPE                             0x10u         /*线路数据ID*/
#define LINE_POINT_ID                             1u            /*点表*/
#define LINE_SEG_ID                              2u            /*Seg表ID*/
#define LINE_AXLE_SGMT_ID                        3u            /*计轴区段表ID*/
#define LINE_PHYSICAL_SGMT_ID                    4u            /*物理区段表ID*/
#define LINE_LGC_SGMT_ID                         5u            /*逻辑区段表*/
#define LINE_AXLE_ID                             6u            /*计轴器表ID*/
#define LINE_SWITCH_ID                           7u            /*道岔表ID*/
#define LINE_SIGNAL_ID                           8u            /*信号机表ID*/
#define LINE_SHIELD_DOOR_ID                      9u            /*屏蔽门表ID*/
#define LINE_EMERG_STOP_BUTTON_ID               10u           /*紧急停车按钮表ID*/
#define LINE_TRAIN_STATION_ID                    11u              /*车站ID*/
#define LINE_PLATFORM_ID                        12u           /*站台表ID*/
#define LINE_BALISE_ID                          13u           /*应答器表ID*/
#define LINE_GRADE_ID                           14u           /*坡度表ID*/
#define LINE_STATIC_RES_SPEED_ID                15u           /*静态限速表ID*/
#define LINE_ROUTE_ID                           16u           /*进路表ID*/
#define LINE_PROTECT_ZONE_ID                    17u           /*保护区段表ID*/
#define LINE_BLOC_APPTCH_SECTION_ID             18u           /*点式接近区段表ID*/
#define LINE_CBTC_APPTCH_SECTION_ID             19u           /*CBTC接近区段表ID*/
#define LINE_BLOC_TRG_ZONE_ID                   20u           /*点式触发区段表ID*/
#define LINE_CBTC_TRG_ZONE_ID                   21u           /*CBTC触发区段表ID*/
#define LINE_SECTION_TYPE_ID                    22u              /*区域属性表*/
#define LINE_CONRESSPEED_ID                        23u              /*统一限速查询*/
#define LINE_CONGRADE_ID                        24u              /*统一坡度查询*/


/*运营数据*/
#define RUN_DATA_TYPE                            0x20u       /*运营数据 类型*/
#define RUN_STOPSECTION_ID                        1u            /*停车区域表ID*/
#define RUN_STOPPOINT_ID                        2u            /*停车点表ID*/
#define RUN_DEFAULT_ROUTE_ID                    3u            /*默认运行序列表ID*/
#define RUN_STA_RUN_LEVEL_ID                    4u            /*站间运营级别表ID*/
#define RUN_AR_ID                                5u            /*无人折返表ID*/
#define RUN_EXIT_CBTC_SECTION_ID                6u            /*退出CBTC区域表ID*/
#define RUN_TRAIN_CONTROL_LEVEL_ID                7u            /*非CBTC区域表ID*/

/*系统数据  宏定义*/
#define  SYSTEM_CONFIGDATA_TYPE                    0x30u        /*系统数据*/
#define  SYSTEM_CONFIGDATA_ID                    1u            /*系统数据配置表*/
#define  SYSTEM_TEMPLIMITSPEED_CONFIG_ID        2u            /*临时限速配置表*/
#define  SYSTEM_TRAINTYPE_CONFIG_ID                3u            /*列车车型配置数据ID*/
#define  SYSTEM_TRAININFO_ID                    4u            /*车型性能参数ID*/
#define  SYSTEM_RAILINFO_ID                        5u            /*线路参数*/
#define  SYSTEM_ACCTABLE_ID                        6u            /*最大牵引加速度分段取值表*/
#define  SYSTEM_COMMFAILTIME_ID                 7u            /*通信故障时间表*/
#define  SYSTEM_DEV_COMM_ID                        8u            /*设备通信关系表*/

/*分界点表*/
#define  DIVIDPOINT_TYPE                        0x40u        /*分界点表类型*/
#define  DIVIDPOINT_LINRSWITCH_INFO_ID            1u            /*切换线路信息ID*/

/*ZC数据表 宏定义*/
#define  ZC_DATA_TYPE                            0x60u
#define  ZC_SIGN_INFO_ID                        1u            /*信号机信息ID*/

/*ZC配置数据*/
#define  ZC_CONFIG_TYPE                            0x61u        /*ZC配置数据类型*/
#define  ZC_CONFIG_DATA_ID                        1u            /*ZC配置数据ID*/
#define  ZC_TIME_CONFIG_DATA_ID                    2u            /*ZC校时配置表ID*/
#define  ZC_COMM_CONFIG_DATA_ID                    3u            /*ZC通信配置表ID*/
#define  ZC_SYSTEM_CONFIG_DATA_ID                4u            /*ZC系统配置表ID*/

/*ZC_NZC接口码位数据*/
#define ZC_NZC_INTERCODE_TYPE                   0xB4u           /*ZC_NZC接口码位数据类型*/    
#define ZC_NZC_SWITCHCODE_TYPE                   1u              /*ZC_NZC道岔码位*/    
#define ZC_NZC_SIGNCODE_TYPE                       2u              /*ZC_NZC信号机码位*/    
#define ZC_NZC_PSDCODE_TYPE                       3u              /*ZC_NZC屏蔽门码位*/    
#define ZC_NZC_ESBCODE_TYPE                       4u              /*ZC_NZC紧急停车按钮码位*/    
#define ZC_NZC_AXLESECCODE_TYPE                   5u              /*ZC_NZC计轴区段码位*/    
#define ZC_NZC_ROUTECODE_TYPE                   6u              /*ZC_NZC进路码位*/    
#define ZC_NZC_PROSECCODE_TYPE                   7u              /*ZC_NZC保护区段码位*/    
#define ZC_NZC_ARCODE_TYPE                       8u              /*ZC_NZC无人折返码位*/    

/*CI_ZC接口码位数据*/
#define ZC_CI_INTERCODE_TYPE                       0xB3u           /*CI_ZC接口码位数据类型*/    
#define ZC_CI_SWITCHCODE_TYPE                   1u              /*CI_ZC道岔码位*/    
#define ZC_CI_SIGNCODE_TYPE                       2u              /*CI_ZC信号机码位*/    
#define ZC_CI_PSDCODE_TYPE                       3u              /*CI_ZC屏蔽门码位*/    
#define ZC_CI_ESBCODE_TYPE                       4u              /*CI_ZC紧急停车按钮码位*/    
#define ZC_CI_AXLESECCODE_TYPE                   5u              /*CI_ZC计轴区段码位*/
#define ZC_CI_LOGICSECTION_TYPE                    6u                /*CI_ZC逻辑区段码位*/
#define ZC_CI_ROUTECODE_TYPE                       7u              /*CI_ZC进路码位*/    
#define ZC_CI_PROSECCODE_TYPE                   8u              /*CI_ZC保护区段码位*/    
#define ZC_CI_ARCODE_TYPE                       9u              /*CI_ZC无人折返码位*/    

/*DMS配置数据*/
#define  DMS_CONFIGDATA_TYPE                    0xC0u        /*DMS配置数据 类型*/
#define  DMS_CONFIGDATA_ID                        1u            /*DMS配置数据ID*/

/*ATO配置数据  宏定义*/
#define  ATO_CONFIGDATA_TYPE                    0x07u        /*ATO配置数据 类型*/
#define  ATO_CONFIGDATA_ID                        1u            /*ATO配置参数表ID*/
#define  ATO_DOOR_CONFIGDATA_ID                    2u            /*ATO门配置数据ID*/
#define  ATO_TMS_CONFIGDATA_ID                    3u            /*ATOTMS配置参数表ID*/
#define  ATO_BRIDGE_CONFIGDATA_ID                4u            /*ATO驾驶台配置数据ID*/
/*ATO数据  宏定义*/
#define  ATO_DATA_TYPE                            0x80u        /*ATO数据 类型*/
#define  ATO_TRACTIONSAMPLE_ID                    1u            /*车辆牵引性能拟合曲线表ID*/
#define  ATO_BREAKSAMPLE_ID                        2u            /*车辆制动性能拟合曲线表ID*/ 
#define  ATO_ESPECIALTRIPNUM_ID                    3u            /*特殊车次号段ID*/
#define  ATO_SPEED_CONFIGDATA_ID                4u            /*ATO速度参数表ID*/
#define  ATO_DFTSQC_ID                            5u            /*默认序列表*/

/*ATP配置数据  宏定义*/
#define  ATP_CONFIGDATA_TYPE                    0x71u        /*ATP配置数据 类型*/
#define  ATP_TRAIN_CONFIGDATA_ID                1u            /*ATP车辆参数配置表ID*/
#define  ATP_RM_CONFIGDATA_ID                    2u            /*ATPRM配置表ID*/
#define  ATP_SIGN_CONFIGDATA_ID                    3u            /*ATPATP信号机配置表ID*/
#define  ATP_BACKRUN_CONFIGDATA_ID                4u            /*ATP退行配置表ID*/
#define  ATP_BALISE_CONFIGDATA_ID                5u            /*ATP应答器配置表ID*/
#define  ATP_LOOP_CONFIGDATA_ID                    6u            /*ATP环线配置表ID*/
#define  ATP_WHEEL_CONFIGDATA_ID                7u            /*ATP轮径配置表ID*/
#define  ATP_SELFPOWER_CONFIGDATA_ID            8u            /*ATP自关断配置表ID*/
#define  ATP_ZEROSPEED_CONFIGDATA_ID            9u            /*ATP零速配置表ID*/
#define  ATP_EB_CONFIGDATA_ID                    10u            /*ATPEB配置表ID*/
#define  ATP_ATO_CONFIGDATA_ID                    11u            /*ATPATO配置表ID*/
#define  ATP_MEASPEED_CONFIGDATA_ID                12u            /*ATP测速配置表ID*/
#define  ATP_MODE_CONFIGDATA_ID                    13u            /*ATP驾驶模式配置表ID*/
#define  ATP_NET_CONFIGDATA_ID                    14u            /*ATP网络配置表ID*/
#define  ATP_NMS_CONFIGDATA_ID                    15u            /*ATPNMS配置表ID*/
#define  ATP_NTP_CONFIGDATA_ID                    16u            /*ATPNTP配置表ID*/
#define  ATP_DOOR_CONFIGDATA_ID                 17u         /* ATP车门配置表ID */

/*ATP数据  宏定义*/
#define  ATP_DATA_TYPE                            0x70u        /*ATP数据 类型*/
#define  ATP_SINGOPEN_INFO_ID                    1u             /*ATP信号机表ID*/
#define  ATP_BTRSPD_ID                            2u             /*ATP应答器表*/
#define  ATP_VRBTRSPD_VERSION_ID                3u             /*可变应答器版本ID*/

/*数据ID宏定义结束*/

/*系统间数据文件比较涉及的版本号索引*/
#define INTERSYSVERCMP_IDX_ATPZC                1u           /*ATP-ZC间的比较数据版本的索引*/
#define INTERSYSVERCMP_IDX_ATPATO               2u           /*ATP-ATO间的比较数据版本的索引*/
#define INTERSYSVERCMP_IDX_ZCDMS                3u           /*ZC-DMS间的比较数据版本的索引*/

#endif
