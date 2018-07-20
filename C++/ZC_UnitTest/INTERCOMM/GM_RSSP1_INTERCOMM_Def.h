/**
* @file GM_RSSP1_INTERCOMM_Def.h
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


#ifndef _GM_RSSP1_INTERCOMM_DEF_H_
#define _GM_RSSP1_INTERCOMM_DEF_H_
#include "../GM_Define.h"
#include "../GM_Utils/GM_MQ_Fixed.h"
#include "../GM_Utils/GM_Utils_Base.h"
#include "../FSFB/GM_RSSP1_Utils.h"

#ifdef __cplusplus
extern "C"
{
#endif

    #define GM_RSSP1_INVALID_SOCKET (-1)

	#define GM_RSSP1_INTERCOMM_HEAD_LEN		(1U)	/* 内网通信头部长度 */
	#define GM_RSSP1_INTERCOMM_HEAD_INDEX	(0U)	/* 内网通信头部长度索引 */

 	typedef enum
	{
 		GM_RSSP1_INTERCOMM_Type_IOB           = 1U, /* 内网通信主体-IO板 */
 		GM_RSSP1_INTERCOMM_Type_CPUB          = 2U, /* 内网通信主体-CPU板 */
	} INTERCOMM_Type_Enum;

	typedef struct
	{
		char					local_ip[20];     /**<  本地IP地址 */
		GM_UINT16				local_port;       /**<  本地端口 */

		struct sockaddr_in		local_addr;

		char					remote_ip[20];     /**<  远程IP地址 */
		GM_INT16				remote_port;       /**<  远程端口 */

		struct sockaddr_in  remote_addr;
	} GM_PACKED INTERCOMM_transport_config_struct;

	typedef struct
	{
		GM_INT16				sock;								/**< 内网通信socket */
		GM_INT16				max_socket_value;	
		INTERCOMM_transport_config_struct	addr_cfg;					/**< IP，port配置 */
		GM_MQ_Fixed_Struct					stInDataQ;					/* 通信控制器接收数据队列*/
		GM_MQ_Fixed_Struct					stOutDataQ;					/* 通信控制器发送数据队列*/
	}INTERCOM_UDP_mng_struct;
	typedef struct
	{	
		INTERCOMM_Type_Enum	type;										/* 通信控制器类型:CPU板、IO板 */
		INTERCOM_UDP_mng_struct			chnl_IOB[GM_RSSP1_MAX_LINK_CHANNEL];		/* IO板通信控制器通道 */
		INTERCOM_UDP_mng_struct			chnl_CPUB[GM_RSSP1_MAX_LINK_CHANNEL];		/* CPU板通信控制器通道 */
	}GM_PACKED INTERCOM_Cfg_struct;

	extern INTERCOM_Cfg_struct	g_stINTERCOMM;

	
	extern INTERCOM_Cfg_struct* GM_INTERCOMM_Get_Rssp1_Intercomm_Cfg();
	
#ifdef __cplusplus
}
#endif /* extern "C" */


#endif
