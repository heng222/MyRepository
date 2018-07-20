/**
* @file GM_RSSP1_INTERCOMM.h
* @brief 系间同步接口头文件
* @author 
* @date 2017-10-17 15:31:27
* @version
* <pre><b>copyright: </b></pre>
* <pre><b>email: </b></pre>
* <pre><b>company: </b></pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>Write modifications here.</pre>
*/


#ifndef _SYNC_INTERCOMM_H_
#define _SYNC_INTERCOMM_H_
#include "../GM_Define.h"
#include "../FSFB/GM_RSSP1_Lib_Def.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
* @brief 系间同步 维护处理接口
*
* Detailed description.
* @return GM_BOOL
*/
GM_BOOL SYNC_INTERCOMM_Matain_Proc(void);

/**
* @brief 系间同步 主处理接口
*
* Detailed description.
* @return GM_BOOL
*/
GM_BOOL SYNC_INTERCOMM_Recv_Proc(void);
/**
* @brief 系间同步 主发送处理接口
*
* Detailed description.
* @return GM_BOOL
*/
GM_BOOL SYNC_INTERCOMM_Send_Proc(void);


/**
* @brief 系间同步 获取发送缓存指针
*
* Detailed description.
* @return GM_BOOL
*/
GM_UINT8* SYNC_INTERCOMM_Get_Sync_Output_Ptr(void);

/**
* @brief 系间同步 获取接收缓存指针
*
* Detailed description.
* @return GM_BOOL
*/
GM_UINT8* SYNC_INTERCOMM_Get_Sync_Input_Ptr(void);

/**
* @brief 系间同步 设置发送数据长度
*
* Detailed description.
* @return GM_BOOL
*/
void SYNC_INTERCOMM_Set_Sync_Output_Length(GM_UINT32 Len);

/**
* @brief 系间同步 获取接收缓存中数据长度
*
* Detailed description.
* @return GM_BOOL
*/
GM_UINT32 SYNC_INTERCOMM_Get_Sync_Input_Length(void);



#ifdef __cplusplus
}
#endif /* extern "C" */

#endif