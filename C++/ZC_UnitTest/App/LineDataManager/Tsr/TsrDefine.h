/************************************************************************
*
* 文件名   ：  TsrDefine.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  临时限速宏定义
* 备  注   ：  无
*
************************************************************************/
#ifndef TSR_DEFINE_H_
#define TSR_DEFINE_H_

#include "../../SysDataManager/SysDefine.h"

/*本ZC对应的最大的临时限速区域（包含本ZC的临时限速和相邻ZC的临时限速）总数最大值*/
#define TSR_BUFF_SUM_MAX                          (COMM_ZC_SUM_MAX+1U)    /*临时限速最大值*/

/*单个ZC包含的最大临时限速数量*/
#define SINGLE_ZC_TSR_SUM_MAX                     20U                   /*定义单个ZC包含的最大临时限速数量*/

/*单个临时限速内包含的最大逻辑区段数量*/
#define SINGLE_TSR_SECTION_SUM_MAX                25U                   /*定义单个临时限速内包含的最大逻辑区段数量*/

#endif
