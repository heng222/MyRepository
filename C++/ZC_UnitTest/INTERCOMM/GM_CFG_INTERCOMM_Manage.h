/**
* @file GM_CFG_INTERCOMM_Manage.h
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


#ifndef _GM_CFG_INTERCOMM_MANAGE_H_
#define _GM_CFG_INTERCOMM_MANAGE_H_
#include "../GM_Define.h"
#include "../GM_Utils/GM_MQ_Fixed.h"
#include "../GM_Utils/GM_Utils_Base.h"
#include "../FSFB/GM_RSSP1_Utils.h"
#include "GM_CFG_INTERCOMM_TCP_Object.h"

#ifdef __cplusplus
extern "C"
{
#endif
         


GM_BOOL GM_CFG_INTERCOMM_Is_Sock_Readable(RSSP2_SOCKET sock);

void GM_CFG_INTERCOMM_TCP_Accept_Socket(TCP_Object_struct *pTCP);
GM_INT32 GM_CFG_INTERCOMM_Set_Socket_Option(RSSP2_SOCKET sock);
int GM_CFG_INTERCOMM_Close_Socket(RSSP2_SOCKET *sock);
int GM_CFG_INTERCOMM_Create_Socket(int type, RSSP2_SOCKET *max_socket_value);


void GM_CFG_INTERCOMM_Maintain_Server_Sockets(TCP_Object_struct *pTCP);
void GM_CFG_INTERCOMM_Maintain_Client_Sockets(TCP_Object_struct *pTCP);

extern TCP_Initialize_Library_Result_Enum GM_CFG_INTERCOM_TCP_Initialize_Library(TCP_Object_struct *pTCP);
extern GM_BOOL GM_CFG_INTERCOMM_TCP_Socket_Maintain(TCP_Object_struct *pTCP);
extern GM_INT32 GM_CFG_INTERCOMM_TCP_Conn_Recv_Sock_Dat(TCP_Object_struct *pTCP);
extern GM_INT32 GM_CFG_INTERCOMM_TCP_Conn_Send_Sock_Dat(TCP_Object_struct *pTCP);

extern TCP_Object_struct* GM_CFG_INTERCOM_Get_TCPObject();

#ifdef __cplusplus
}
#endif /* extern "C" */


#endif
