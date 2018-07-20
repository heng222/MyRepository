/**
* @file SYNC_INTERCOMM_Init.h
* @brief 双系同步初始化头文件
* @author 
* @date 2017-10-17 14:56:35
* @version
* <pre><b>copyright: </b></pre>
* <pre><b>email: </b></pre>
* <pre><b>company: </b></pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>Write modifications here.</pre>
*/


#ifndef _SYNC_INTERCOMM_INIT_H_
#define _SYNC_INTERCOMM_INIT_H_

#include "SYNC_INTERCOMM_Def.h"
#include "../FSFB/GM_RSSP1_Lib_Def.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
    * @brief SYNC相关数据结构初始化
    *
    * Detailed description.
	* @param[in] pCfg:SYNC结构体指针
	* @param[in] type:通信控制器内网主体类型，请参考GM_RSSP1_INTERCOMM_Type_Enum
    * @return GM_BOOL
    */
    extern GM_BOOL SYNC_INTERCOMM_Init(void);

	/**
    * @brief SYNC相关数据结构初始化是否完成
    *
    * Detailed description.
    * @return GM_BOOL
    */
	GM_BOOL SYNC_INTERCOMM_Init_Finished();
	void SYNC_INTERCOMM_Csp_Safety_Layer_Statistics(void);

#ifdef __cplusplus
}
#endif /* extern "C" */


#endif
