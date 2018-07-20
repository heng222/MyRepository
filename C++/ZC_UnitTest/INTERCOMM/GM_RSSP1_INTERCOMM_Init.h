/**
* @file GM_RSSP1_INTERCOMM_Init.h
* @brief 内外网通信控制器初始化头文件
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


#ifndef _GM_RSSP1_INTERCOMM_INIT_H_
#define _GM_RSSP1_INTERCOMM_INIT_H_

#include "GM_RSSP1_INTERCOMM_Def.h"
#include "../FSFB/GM_RSSP1_Lib_Def.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
    * @brief 通信控制器相关数据结构初始化
    *
    * Detailed description.
	* @param[in] pINTERCOMM:通信控制器结构体指针
	* @param[in] type:通信控制器内网主体类型，请参考GM_RSSP1_INTERCOMM_Type_Enum
    * @return GM_BOOL
    */
    extern GM_BOOL GM_RSSP1_INTERCOMM_Init(INTERCOM_Cfg_struct* pINTERCOMM, int type);
	/**
    * @brief 检查通信控制器的类型是否合法
    *
    * Detailed description.
	* @param[in] type:通信控制器的类型
    * @return GM_BOOL
    */
	GM_BOOL GM_RSSP1_INTERCOMM_Type_Vaild(int type);
	/**
    * @brief 通信控制器相关数据结构初始化是否完成
    *
    * Detailed description.
    * @return GM_BOOL
    */
	GM_BOOL GM_RSSP1_INTERCOMM_Init_Finished();
		/**
    * @brief 获取通信控制器相关数据结构体指针
    *
    * Detailed description.
    * @return GM_BOOL
    */
	INTERCOM_Cfg_struct* GM_RSSP1_INTERCOMM_Get_Stru();
#ifdef __cplusplus
}
#endif /* extern "C" */


#endif
