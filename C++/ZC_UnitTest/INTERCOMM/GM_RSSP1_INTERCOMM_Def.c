/**
* @file GM_RSSP1_INTERCOMM_Def.c
* @brief 内外网通信控制器使用的数据结构体定义及声明
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
#include "GM_RSSP1_INTERCOMM_Def.h"

INTERCOM_Cfg_struct	g_stINTERCOMM;

/**
* @brief 获取内网冗余协议配置信息 
*
* Detailed description.
* @return GM_BOOL
*
*/
INTERCOM_Cfg_struct* GM_INTERCOMM_Get_Rssp1_Intercomm_Cfg()
{
	
	return (INTERCOM_Cfg_struct*)(&g_stINTERCOMM);
	
}