/**
* @file SYNC_INTERCOMM_Def.h
* @brief ˫ϵͬ��ʹ�õ����ݽṹ�嶨�弰����
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


#ifndef _SYNC_INTERCOMM_DEF_H_
#define _SYNC_INTERCOMM_DEF_H_

#include "GM_RSSP1_INTERCOMM_Def.h"



#ifdef __cplusplus
extern "C"
{
#endif

#define SYNC_INTERCOMM_MAX_LINK_CHANNEL   1U
#define SYNC_INTERCOMM_MAX_LINK_TIMEOUT_CYCLE   12U


	typedef struct
	{
		GM_INT16				sock;								/**< ����ͨ��socket */
		GM_INT16				max_socket_value;	
		GM_UINT32				timeout_cycle;			            /**< ͨ�ų�ʱ���� */
		INTERCOMM_transport_config_struct	addr_cfg;				/**< IP��port���� */
		GM_UINT32               InDataLen;
		GM_UINT8*               pInData;                            /**< ��������*/
		GM_UINT32               OutDataLen;		
		GM_UINT8*               pOutData;                           /**< ��������*/
		
	}SYNC_INTERCOMM_UDP_mng_struct;
	typedef struct
	{	
		INTERCOMM_Type_Enum	type;										/* ͨ�ſ���������:CPU�塢IO�� */
		SYNC_INTERCOMM_UDP_mng_struct	chnl_Sync[SYNC_INTERCOMM_MAX_LINK_CHANNEL];		/* IO��ͨ�ſ�����ͨ�� */

	}GM_PACKED SYNC_INTERCOM_Cfg_struct;

	
	extern SYNC_INTERCOM_Cfg_struct* SYNC_INTERCOMM_Get_Sync_Intercomm_Cfg();
	
#ifdef __cplusplus
}
#endif /* extern "C" */


#endif
