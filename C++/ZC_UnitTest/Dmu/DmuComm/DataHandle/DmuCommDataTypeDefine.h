/********************************************************
* 
* 文 件 名： DmuCommDataTypeDefine.h 
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 公共查询函数头文件 
* 备    注： 无 
* 
********************************************************/ 

#ifndef DMU_COMM_DATATYPE_DEFINE_H_
#define DMU_COMM_DATATYPE_DEFINE_H_

#include "../../../Common/CommonTypes.h"

/*相对于SEG逻辑方向 */
#define LINESEG_SAME_DIR                                0x55u                            /*与SEG逻辑方向相同*/
#define LINESEG_CONVER_DIR                                0xAAu                            /*与SEG逻辑方向相反*/

#define SEG_LOGIC_DIR_DOWN                                0x55u                            /*下行(link逻辑方向为线路下行方向)*/
#define SEG_LOGIC_DIR_UP                                0xAAu                            /*上行(link逻辑方向为线路上行方向)*/

#define INCLINE_SAME_DIR                                0x55u                            /*坡度沿SEG逻辑方向向上倾斜，即上坡*/
#define INCLINE_CONVER_DIR                                0xAAu                            /*坡度沿SEG逻辑方向向下倾斜，即下坡*/

#define SWITCH_STATUS_SAME                                1u                                /*道岔定位*/
#define SWITCH_STATUS_CONTRA                            2u                                /*道岔反位*/
#define SWITCH_STATUS_LOSE                                3u                                /*道岔四开*/

#define SIGNPRO_DIR_SAME                                0x55u                            /*信号机防护方向为正向*/
#define SIGNPRO_DIR_CONTRA                                0xAAu                            /*信号机防护方向为反向*/

#define OPENSIGNAL_PASS_CLOSE                            0x55u                            /*非开口信号机标志*/
#define OPENSIGNAL_PASS_OPEN                            0xAAu                            /*开口信号机标志*/

#define PSD_STATUS_OPEN                                    0x55u                            /*屏蔽门状态为开启*/
#define PSD_STATUS_CLOSE                                0xAAu                            /*屏蔽门状态为关闭*/
#define ESP_STATUS_ACTIVITE                                0x55u                            /*站台紧急停车按钮按下*/
#define ESP_STATUS_UNACTIVITE                            0xAAu                            /*站台紧急停车按钮释放*/

#define DEFAULT_ZERO                                       0u                            /*变量初始值为0*/
#define DEFAULT_1_VALUE                                    1u                            /*变量初始值为1*/
#define DEFAULT_2_VALUE                                    2u                            /*变量初始值为2*/
#define UINT8_NULL                                        0xFFu                            /*一个字节的无效值*/
#define UINT16_NULL                                   0xFFFFu                            /*两个字节的无效值*/
#define UINT32_NULL                               0xFFFFFFFFu                            /*四个字节的无效值*/

/*点类型定义*/
#define POINTTYPE_SWITCH                                0x03u                            /*道岔*/
#define POINTTYPE_AXLE                                    0x02u                            /*计轴*/
#define START_POINT                                        0x01u                            /*起点*/
#define END_POINT                                        0x02u                            /*终点*/

/*障碍物类型宏定义*/
#define    LINEOBS_SIGNAL                                    0x01u                            /*信号机*/
#define    LINEOBS_PSD                                        0x02u                            /*屏蔽门*/
#define    LINEOBS_ESB                                        0x03u                            /*站台紧急停车按钮*/
#define    LINEOBS_SWITCH                                    0x04u                            /*道岔*/
#define    LINEOBS_PLATFORM                                0x05u                            /*站台区域*/
#define    LINEOBS_ZCDVIDE                                    0x07u                            /*ZC边界点*/
#define    LINEOBS_RES                                        0x08u                            /*限速区域*/
#define LINEOBS_TRAIN_TAIL                                0x09u                            /*前方列车车尾*/
#define LINEOBS_TRAIN_HEAD                                0x0au                            /*前方列车车头*/
#define LINEOBS_AXLESEC                                    0x0bu                            /*计轴区段*/    
#define LINEOBS_UT                                        0x0cu                            /*计轴区段（非通信车占用等使用计轴区段始端的情况）*/    
#define LINEOBS_OVERLAP                                    0x0du                            /*Overlap*/    
#define LINEOBS_ARBUTTON                                0x0eu                            /*无人折返按钮*/    
#define LINEOBS_ARLIGHT                                    0x0fu                            /*无人折返灯*/    
#define LINEOBS_ROUTE                                    0x10u                            /*进路*/    
#define LINEOBS_LS                                        0x11u                            /*逻辑区段*/

/*停车区域属性定义*/
#define RUN_STATION_AREA                                0x01u                            /*站台区域*/
#define    RUN_REVERT_AREA                                    0x02u                            /*折返区域*/
#define    RUN_TRANSFORM_AREA                                0x04u                            /*转换轨区域*/

/*停车区域车门开门操作方式*/
#define RUN_DOOR_NO_OPEN                                0u                                /*左右均不开*/
#define RUN_DOOR_LEFT_OPEN                                1u                                /*开门方向左门*/
#define RUN_DOOR_RIGHT_OPEN                                2u                                /*开门方向右门*/
#define RUN_DOOR_LEFT_RIGHT_OPEN                        3u                                /*开门方向先左门后右门*/
#define RUN_DOOR_RIGHT_LEFT_OPEN                        4u                                /*开门方向先右后门左门*/
#define RUN_DOOR_BOTH_OPEN                                5u                                /*允许同时开两侧门*/

/*停车区域车门关门操作方式*/
#define RUN_DOOR_NO_CLOSE                                0u                                /*左右均不关*/
#define RUN_DOOR_LEFT_CLOSE                                1u                                /*关门方向左门*/
#define RUN_DOOR_RIGHT_CLOSE                            2u                                /*关门方向右门*/
#define RUN_DOOR_LEFT_RIGHT_CLOSE                        3u                                /*关门方向先左门后右门*/
#define RUN_DOOR_RIGHT_LEFT_CLOSE                        4u                                /*关门方向先右后门左门*/
#define RUN_DOOR_BOTH_CLOSE                                5u                                /*允许同时关两侧门*/

/*停车点属性定义*/
#define RUN_OPERAT_STOP_POINT                            0x01u                            /*站台运营停车点*/
#define RUN_EXITROUTE_STOP_POINT                        0x02u                            /*退出停车点（CBTC区域至非CBTC区域)*/
#define RUN_REVERT_STOP_POINT                            0x04u                            /*折返停车点*/ 
#define RUN_SIGNAL_STOP_POINT                            0x08u                            /*站外信号机停车点(非折返)*/  /*通过停车点*/
#define RUN_REVERTEND_STOP_POINT                        0x10u                            /*折返后停车点*/
#define RUN_SWITCH_STOP_POINT                            0x20u                            /*转换轨(小站台)停车点（非CBTC区域至CBTC区域）*/

/*进路性质*/
#define  LINE_TRAIN_ROUTE                                0x01u                            /*列车进路*/
#define  LINE_REVERSE_ROUTE                                0x02u                            /*折返进路*/
#define  LINE_IN_SGMT_ROUTE                                0x04u                            /*回段进路*/
#define  LINE_OUT_SGMT_ROUTE                            0x08u                            /*出段进路*/
#define  LINE_IN_DEPOT_ROUTE                            0x10u                             /*回库进路*/
#define  LINE_OUT_DEPOT_ROUTE                            0x20u                            /*出库进路*/
#define  LINE_EXIT_CBTC_ROUTE                            0x40u                            /*CBTC级别退出进路*/
#define  LINE_EXIT_BLOC_ROUTE                            0x80u                            /*点式级别退出进路*/

/*退出CBTC区域属性*/
#define LINE_ITC_EXIT_SEC                                0x01u                            /*点式退出区域*/
#define LINE_CBTC_EXIT_SEC                                0x02u                            /*CBTC退出区域*/
#define LINE_IN_SGMT_SEC                                0x04u                            /*回段属性区域*/
#define LINE_IN_DEPOT_SEC                                0x08u                            /*回库属性区域*/

/*应答器类型*/
#define BALI_WHEELCALI                                     0x0001u                            /*校轮应答器*/
#define BALI_FIXED                                        0x0002u                            /*固定应答器*/
#define BALI_VARIABLE_DATA                                0x0004u                            /*可变数据应答器*/
#define BALI_INFILLED                                     0x0008u                            /*填充应答器*/
#define BALI_ATO                                        0x0020u                            /*ATO应答器*/
#define BALI_LOCCALI                                     0x0040u                            /*位置校正应答器*/
#define BALI_NORMAL                                        0x0080u                            /*普通应答器*/
#define BALI_LOOP                                        0x0010u                            /*环线*/

/*线路基本信息定义*/
#define SEG_INCLUDE_LIMITSPEED_MAX_NUM                  5u                               /*一个SEG包含的临时限速的个数*/
#define MAX_ACOFSWITCH_NUM                                12u                                /*道岔所属计轴区段的数量*/
#define BOTHSEG_INCLUDE_MAX_SEG                            100u                                /*两个SEGID之间包含的SEGID个数*/
#define TWO_POINT_AC_NUM_MAX                            20u                                /*两个SEGID之间包含的计轴区段个数*/
#define TWO_POINT_SWITCH_NUM_MAX                        30u                                /*两个SEGID之间包含的道岔个数*/
#define TWO_POINT_LOGICSEC_NUM_MAX                        50u                                /*两点之间包含逻辑区段的最大个数*/
#define TWO_POINT_STATION_NUM_MAX                        30u                                /*两个SEGID之间包含的站台个数*/
#define TWO_POINT_PSD_NUM_MAX                            10u                                /*两个SEGID之间包含的屏蔽门个数*/
#define TWO_POINT_ESB_NUM_MAX                            10u                                /*两个SEGID之间包含的紧急停车按钮个数*/
#define AXLESEC_ADJACENT_MAX_NUM                        3u                                /*计轴区段相邻计轴区段的最大数量*/
#define SNGZC_INCLUDE_SWITCH_NUM                        400u                                /*单个ZC内包含的道岔数量*/
#define ONEPOINT_SAMEDIR_INCLUDE_SEG                    2u                                /*一个当按照同一方向包含的SEG最大值*/
#define BOTHSEG_NOSWITCHSTATUS_INCLUDE_MAX_SEG            20u                                /*道岔状态未知时,两个SEGID之间包含的SEGID个数*/
#define ROUTE_INCLUDE_PLATFORM_MAX_NUM                    3u                                /*一条进路包含的最大站台个数*/
#define STACK_PUSH_SEG_MAX_NUM                            100u                                /*压入栈的SEG个数*/


#define MA_OBST_MAX_NUM                                    30u                                /*MA中最大障碍物数量*/
#define MA_TLS_MAX_NUM                                    20u                                /*MA中的最大临时限速数量*/
#define MA_SWITCH_MAX_NUM                                20u                                /*MA中最大道岔数量*/

/*设备类型定义*/
#define DEV_ZC_TYPE                                        0x1eu                            /*ZC设备类型*/
#define DEV_ATS_TYPE                                    0x03u                            /*ATS设备类型*/
#define DEV_CI_TYPE                                        0x3Cu                            /*CI设备类型*/


/*MA终点类型*/
#define MA_CBTC_END_TYPE                                   0x01u                            /*MA终点类型为CBTC终点*/
#define MA_REVERSE_END_TYPE                              0x02u                            /*MA终点折返进路*/
#define MA_OTHER_END_TYPE                               0x03u                            /*线路上的其他障碍物(ATP不关心其具体类型)*/

/*CI区域属性*/
#define CI_MAIN_LINE_TYPE                               0x01u                            /*正线联锁属性*/                      
#define CI_TRAIN_DEPOT_TYPE                             0x02u                            /*车辆段/停车场联锁属性*/

/*ZC区域属性*/
#define ZC_MAIN_LINE_TYPE                               0x01u                            /*正线区域控制器属性*/
#define ZC_TRAIN_DEPOT_TYPE                             0x02u                            /*车辆段/停车场区域控制器属性*/

#endif
