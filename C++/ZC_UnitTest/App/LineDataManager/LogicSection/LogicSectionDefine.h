/************************************************************************
*
* 文件名   ：  LogicSectionDefine.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  逻辑区段宏定义
* 备  注   ：  无
*
************************************************************************/
#ifndef LOGIC_SECTION_DEFINE_H_
#define LOGIC_SECTION_DEFINE_H_

#include "../../SysDataManager/SysDefine.h"

/*逻辑区段总数最大值*/
#define LOGIC_SECTION_SUM_MAX                5000U    /*定义逻辑区段最大值*/

/*本地管理的逻辑区段总数最大值*/
#define LOGIC_SECTION_LOCAL_SUM_MAX          500U     /*定义本地管理的逻辑区段最大值*/

/*逻辑区段状态*/
#define LOGIC_SECTION_STATE_UT               1U       /*逻辑区段非通信列车占用状态*/
#define LOGIC_SECTION_STATE_CT               2U       /*逻辑区段通信列车占用状态*/
#define LOGIC_SECTION_STATE_FREE             3U       /*逻辑区段空闲状态*/

/*发送给ATS的逻辑区段占用类型*/
#define TO_ATS_LOGIC_SECTION_CT_OCC          1U       /*cbtc列车占用状态*/
#define TO_ATS_LOGIC_SECTION_UT_OCC          2U       /*非cbtc列车占用状态*/

#define SIZE_MAX_LS_TRAIN                    20U      /*列车占压逻辑区段最大数量*/

#endif
