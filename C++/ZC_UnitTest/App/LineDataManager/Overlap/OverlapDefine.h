
/********************************************************                                                                                                           
 文 件 名： OverlapDefine.h  
 作    者： ZC组
 创建时间： 2015.04.18
 描述： 保护区段宏定义  
 备注： 无  
********************************************************/ 

#ifndef OVERLAP_DEFINE_H_
#define OVERLAP_DEFINE_H_

#include "../../SysDataManager/SysDefine.h"

/*保护区段总数最大值*/
#define OVERLAP_SUM_MAX                           500U    /*定义保护区段最大值*/

/*本地管理的保护区段总数最大值*/
#define OVERLAP_LOCAL_SUM_MAX                     50U     /*定义本地管理的保护区段最大值*/

/*单个保护区段包含的最大计轴区段数量*/
#define OVERLAP_OF_AC_SUM_MAX                     5U      /*保护区段包含的最大计轴区段数量*/

/*保护区段状态*/
#define OVERLAP_STATE_SET                         0x55U   /*保护区段已设置*/
#define OVERLAP_STATE_UNSET                       0xaaU   /*保护区段未设置*/

#endif
