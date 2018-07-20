/*******************************************
文件名	：TsrSystemDefine.h
作者	：董欣
创建时间：2016-10
描述	：系统参数定义头文件
备注	：无
*******************************************/

#ifndef TSR_SYSTEM_DEFINE_H_
#define TSR_SYSTEM_DEFINE_H_

#include "..\..\..\PlatformAdapter\AppItf\AdptAppCommonDef.h"

#define MAX_SECTION_ID_NUM  1000u   /*最大逻辑区段ID*/

#define MAX_ATS_QUAN 16u            /*最大ATS数量*/

/*主动汇报TSR的周期数固定是汇报列车位置周期数的25倍，例如后者是0.8S则前者是20S，后者是1.2S则前者是30S*/
#define AUTOREPTSR_TIMESOVER_REPTRNPOS 25u

/*****返回值定义*****/
#define TSR_ERROR               0x00u	    /*函数返回失败*/
#define TSR_SUCCESS             0x01u	    /*函数返回成功*/
#define DEFAULT_ZERO            0u
#define SIGNED_DEFAULT_ZERO     0

/*ZC工作状态*/
#define ZC_WORK_POP          0x55u         /*上电*/
#define ZC_WORK_NORMAL       0xaau         /*正常*/

#define AUTO_REPLYTO_ATS    1u            /*自主汇报TSR标志,包括重启汇报TSR和正常汇报TSR两种*/

#define ANTI_RES_REPLYTO_ATS                   0x55u      /*未收到ATS命令标志*/
#define RES_REPLYTO_ATS                  0xaau      /*收到ATS命令标志*/

/*应用类型定义*/
#define APP_TYPE_ATS    DEVTYPE_ATS          /*ATS*/
/*#define APP_TYPE_LOG    DEVTYPE_MAINTAIN*/     /* 调试日志设备类型 */
/*#define APP_TYPE_RECORD DEVTYPE_RECORD*/       /* 记录仪设备类型 */

#endif