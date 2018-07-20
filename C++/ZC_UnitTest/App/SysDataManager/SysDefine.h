/************************************************************************
*
* 文件名   ：  SysDefine.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  定义系统使用的宏
* 备  注   ：  无
*
************************************************************************/

#ifndef SYS_DEFINE_H_
#define SYS_DEFINE_H_

#include "../../Dmu/DmuComm/DataHandle/DmuCommDataTypeDefine.h"
#include "../../PlatformAdapter/AppItf/AdptAppCommonDef.h"

/*----------Common----------*/
#define RETURN_ERROR                        ((UINT8_S)(0x00U))	          /*函数返回失败*/
#define RETURN_SUCCESS                      ((UINT8_S)(0x01U))	          /*函数返回成功*/
#define SIGNED_RETURN_SUCCESS               0x01	                      /*函数返回成功-有符号*//*-bye-*/
#define RETURN_NULL                         ((UINT8_S)(0x00U))              /*返回空指针*/
#define RETURN_UINT8_MAX_VALUE              ((UINT8_S)(0xffU))              /*函数返回默认最大值（8位）*/
#define RETURN_UINT16_MAX_VALUE             ((UINT16_S)(0xffffU))            /*函数返回默认最大值（16位）*/
#define RETURN_UINT32_MAX_VALUE             ((UINT32_S)(0xffffffffU))        /*函数返回默认最大值（32位）*/

#define FLAG_SET                            ((UINT8_S)(0x55U))              /*标志位已置位*/
#define FLAG_UNSET                          ((UINT8_S)(0xAAU))              /*标志位未置位*/
#define DEFAULT_0XFF                        ((UINT8_S)(0xffU))              /*变量初始值为0xff*/
#define SIZE_UINT8                          (sizeof(UINT8_S))    /*UINT8变量对应字节长度*/
#define SIZE_UINT16                         (sizeof(UINT16_S))    /*UINT16变量对应字节长度*/
#define SIZE_UINT32                         (sizeof(UINT32_S))   /*UINT32变量对应字节长度*/
#define DEFAULT_UINT8_VALUE                 ((UINT8_S)(0xffU))              /*列车使用的默认值（8位）*/
#define DEFAULT_UINT16_VALUE                ((UINT16_S)(0xffffU))            /*列车使用的默认值（16位）*/
#define DEFAULT_UINT32_VALUE                ((UINT32_S)(0xffffffffU))        /*列车使用的默认值（32位）*/

#define COMM_CI_SUM_MAX                      6U                /*与ZC通信的最大联锁数量*/
#define COMM_ATS_SUM_MAX                     1U                /*与ZC通信的最大ATS数量*/
#define COMM_DSU_SUM_MAX                     1U                /*与ZC通信的最大DSU数量*/
#define COMM_ZC_SUM_MAX                      6U                /*与ZC通信的最大nZC数量*/
#define COMM_TRAIN_SUM_MAX                   40U                /*与ZC通信的最大列车数量*/

#define LOG_SUM_MAX                          15U               /* 日志分包总数 */

#define LINE_ZC_SUM_MAX                      20U              /*线路最大的ZC数量*/
#define LINE_CI_SUM_MAX                      20U               /*线路最大的CI数量(最大的CIID)*/

/* 为了使用集成配置类型定义 */
#define	INNER_DEVTYPE_CI	                         ((UINT8_S)(DEVTYPE_CI))             /*CI数据类型恒比码*/	
#define	INNER_DEVTYPE_ZC	                         ((UINT8_S)(DEVTYPE_ZC))             /*相邻ZC数据恒比码*/	
#define	INNER_DEVTYPE_ATS	                         ((UINT8_S)(DEVTYPE_ATS))               /*ATS数据恒比码*/	
#define	INNER_DEVTYPE_TRAIN                          ((UINT8_S)(DEVTYPE_VOBC))             /*车载ATP数据恒比码*/
#define	INNER_DEVTYPE_NTP		                     ((UINT8_S)(DEVTYPE_NTP))             /*NTP数据恒比码*/
#define ZC_DEVTYPE_MIC                                    ((UINT32_S)(0x0302))             /*通信板恒比码*/
#define ZC_DEVTYPE_SME                                    ((UINT32_S)(0x0301))             /*主机板恒比码*/

/*增设日志恒比码*/
#define	INNER_DEVTYPE_LOG		                     ((UINT8_S)(DEVTYPE_MAINTAIN))             /*日志数据恒比码*/

#define LINE_MAX_TRAIN_ID                    151U              /*线路最大的列车ID*/

#define ZC_RESET_STATUS_FLAG_SET             ((UINT8_S)(0x55U))             /*zc复位标志位已置位*/
#define ZC_RESET_STATUS_FLAG_UNSET           ((UINT8_S)(0xAAU))             /*zc复位标志位未置位*/

#define ZC_INIT_NTP_TIME_SUCC_FLAG_SET       ((UINT8_S)(0x55U))             /*ZC初始化上电校时成功*/
#define ZC_INIT_NTP_TIME_SUCC_FLAG_UNSET     ((UINT8_S)(0xAAU))             /*ZC初始化上电校时不成功*/

#define ZC_TWO_POINT_AC_NUM_MAX                 20U               /*两点之间最大的计轴区段数量*/
#define ZC_TWO_POINT_SWITCH_NUM_MAX             30U               /*两点之间最大的道岔数量*/
#define ZC_TWO_POINT_PSD_NUM_MAX                10U               /*两点之间最大的屏蔽门数量*/
#define ZC_TWO_POINT_ESB_NUM_MAX                10U               /*两点之间最大的紧急停车按钮数量*/

/*障碍物宏定义*/
#define	OBS_TYPE_SIGNAL		((UINT8_S)(0x01U))    /*信号机*/
#define	OBS_TYPE_PSD  		((UINT8_S)(0x02U))    /*屏蔽门*/
#define	OBS_TYPE_ESB        ((UINT8_S)(0x03U))    /*站台紧急停车按钮*/
#define	OBS_TYPE_POINT		((UINT8_S)(0x04U))    /*道岔*/
#define	OBS_TYPE_PLATFORM	((UINT8_S)(0x05U))    /*站台区域*/
#define	OBS_TYPE_EXIT	    ((UINT8_S)(0x06U))    /*共管区域*/
#define	OBS_TYPE_ZC_CHANGE	((UINT8_S)(0x07U))    /*ZC边界点*/
#define	OBS_TYPE_RES		((UINT8_S)(0x08U))    /*限速区域*/
#define OBS_TYPE_TRAIN_TAIL	((UINT8_S)(0x09U))    /*前方列车车尾*/
#define OBS_TYPE_TRAIN_HEAD	((UINT8_S)(0x0aU))    /*前方列车车头*/
#define OBS_TYPE_AC	        ((UINT8_S)(0x0bU))    /*计轴区段*/	
#define OBS_TYPE_UT	        ((UINT8_S)(0x0cU))    /*计轴区段（非通信车占用等使用计轴区段始端的情况）*/	
#define OBS_TYPE_OVERLAP	((UINT8_S)(0x0dU))    /*Overlap*/	
#define OBS_TYPE_DRB	    ((UINT8_S)(0x0eU))    /*无人折返按钮*/	
#define OBS_TYPE_DRL	    ((UINT8_S)(0x0fU))   /*无人折返灯*/	
#define OBS_TYPE_ROUTE	    ((UINT8_S)(0x10U))    /*进路*/	
#define OBS_TYPE_LS	        ((UINT8_S)(0x11U))    /*逻辑区段*/

#define ZC_TO_ATS_BLOCK_INFO          101U               /*ZC给ATS的列车占用消息*/
#define ZC_ATS_PRTCL_VERSION          ((UINT16_S)(0x3001U))            /*ZC与ATS应用层通信协议版本号*/

/*定义追踪不带后方检查区域标记的RM列车类型*/
#define TRACE_RM_TRAIN_TYPE_TAIL    ((UINT8_S)(0x55U))  /*追踪至不带后方检查区域列车车尾回撤安全距离*/
#define TRACE_RM_TRAIN_TYPE_BACK    ((UINT8_S)(0xAAU))  /*追踪至不带后方检查区域列车车尾所在计轴区段始端回撤安全距离*/

/*本地ZC配置数据文件路径*/
#ifdef SYS_TYPE_VXWORKS
#define ZC_ID_CONFIG_DATA  "ZcId.config"    /*ZCID配置文件路径*/
#endif

#ifdef SYS_TYPE_WINDOWS
#define ZC_DATA_INFO       "FS\\ZC.bnf"     /*ZCID数据文件路径*/
#endif

#ifdef SYS_TYPE_VXWORKS
#define ZC_DATA_INFO       "ZC.bnf"     /*ZCID数据文件路径*/
#endif


#define EMAP_DATA_VERSION_TYPE          1U   /*电子地图版本号类型*/
#define SYS_CONFIG_DATA_VERSION_TYPE    2U   /*系统配置数据版本号类型*/

#define TIME_DIFF_1970                  0x83AA7E80U        /*本系统与NTP时间格式差：1970年至1900年的秒数 = 3600s*24h*(365days*70years+17days) */
#define TIME_MAX_WAIT_REC                 2              /*等待应答报文超时时长（ms），在所应用系统校时允许误差范围内即可*/


/*定义系统的运行周期*/
#define ZC_RUN_CYCLE_TIME               400U  /*定义系统运行的周期为400ms*/

/*定义错误码的数值*/
#define ZC_ERROR_CODE_1    0x0001U
#define ZC_ERROR_CODE_2    0x0002U
#define ZC_ERROR_CODE_3    0x0004U
#define ZC_ERROR_CODE_4    0x0008U
#define ZC_ERROR_CODE_5    0x0010U
#define ZC_ERROR_CODE_6    0x0020U
#define ZC_ERROR_CODE_7    0x0040U
#define ZC_ERROR_CODE_8    0x0080U
#define ZC_ERROR_CODE_9    0x0100U
#define ZC_ERROR_CODE_10   0x0200U
#define ZC_ERROR_CODE_11   0x0400U
#define ZC_ERROR_CODE_12   0x0800U
#define ZC_ERROR_CODE_13   0x1000U
#define ZC_ERROR_CODE_14   0x2000U
#define ZC_ERROR_CODE_15   0x4000U
#define ZC_ERROR_CODE_16   0x8000U

/* 定义应用软件的版本号 */
#define ZC_APP_VERSION V.0.0.6
#endif
