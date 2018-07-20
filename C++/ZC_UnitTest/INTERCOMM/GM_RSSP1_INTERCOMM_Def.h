/**
* @file GM_RSSP1_INTERCOMM_Def.h
* @brief ������ͨ�ſ�����ʹ�õ����ݽṹ�嶨�弰����
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

	#define GM_RSSP1_INTERCOMM_HEAD_LEN		(1U)	/* ����ͨ��ͷ������ */
	#define GM_RSSP1_INTERCOMM_HEAD_INDEX	(0U)	/* ����ͨ��ͷ���������� */

 	typedef enum
	{
 		GM_RSSP1_INTERCOMM_Type_IOB           = 1U, /* ����ͨ������-IO�� */
 		GM_RSSP1_INTERCOMM_Type_CPUB          = 2U, /* ����ͨ������-CPU�� */
	} INTERCOMM_Type_Enum;

	typedef struct
	{
		char					local_ip[20];     /**<  ����IP��ַ */
		GM_UINT16				local_port;       /**<  ���ض˿� */

		struct sockaddr_in		local_addr;

		char					remote_ip[20];     /**<  Զ��IP��ַ */
		GM_INT16				remote_port;       /**<  Զ�̶˿� */

		struct sockaddr_in  remote_addr;
	} GM_PACKED INTERCOMM_transport_config_struct;

	typedef struct
	{
		GM_INT16				sock;								/**< ����ͨ��socket */
		GM_INT16				max_socket_value;	
		INTERCOMM_transport_config_struct	addr_cfg;					/**< IP��port���� */
		GM_MQ_Fixed_Struct					stInDataQ;					/* ͨ�ſ������������ݶ���*/
		GM_MQ_Fixed_Struct					stOutDataQ;					/* ͨ�ſ������������ݶ���*/
	}INTERCOM_UDP_mng_struct;
	typedef struct
	{	
		INTERCOMM_Type_Enum	type;										/* ͨ�ſ���������:CPU�塢IO�� */
		INTERCOM_UDP_mng_struct			chnl_IOB[GM_RSSP1_MAX_LINK_CHANNEL];		/* IO��ͨ�ſ�����ͨ�� */
		INTERCOM_UDP_mng_struct			chnl_CPUB[GM_RSSP1_MAX_LINK_CHANNEL];		/* CPU��ͨ�ſ�����ͨ�� */
	}GM_PACKED INTERCOM_Cfg_struct;

	extern INTERCOM_Cfg_struct	g_stINTERCOMM;

	
	extern INTERCOM_Cfg_struct* GM_INTERCOMM_Get_Rssp1_Intercomm_Cfg();
	
#ifdef __cplusplus
}
#endif /* extern "C" */


#endif
