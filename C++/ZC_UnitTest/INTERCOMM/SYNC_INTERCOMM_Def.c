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
#include "SYNC_INTERCOMM_Def.h"

SYNC_INTERCOM_Cfg_struct	g_Sync_Intercomm_Cfg;


SYNC_INTERCOM_Cfg_struct* SYNC_INTERCOMM_Get_Sync_Intercomm_Cfg()
{
	
	return (SYNC_INTERCOM_Cfg_struct*)(&g_Sync_Intercomm_Cfg);
	
}