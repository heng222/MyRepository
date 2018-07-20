/**
* @file GM_RSSP1_INTERCOMM_Socket.h
* @brief 通信控制器UDP网络处理
* @author 
* @date 2017-10-18 19:43:56
* @version
* <pre><b>copyright: </b></pre>
* <pre><b>email: </b></pre>
* <pre><b>company: </b>h</pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>Write modifications here.</pre>
*/

#ifndef _GM_RSSP1_INTERCOMM_SOCKET_H_
#define _GM_RSSP1_INTERCOMM_SOCKET_H_
#include "../GM_Utils/GM_Utils_Base.h"
#include "../FSFB/GM_RSSP1_Utils.h"

#ifdef __cplusplus
extern "C"
{
#endif
	#define INTERCOMM_INVALID_SOCKET  (-1)
    /**
    * @brief 创建socket
    *
    * Detailed description.
    * @param[in] type
    * @param[in] max_socket_value
    * @return GM_INT32
    */
    GM_INT32 INTERCOMM_Socket_Create(GM_INT32 type, GM_INT16 *max_socket_value);

    /**
    * @brief 关闭socket
    *
    * Detailed description.
    * @param[in] pSock
    * @return GM_INT32
    */
    GM_INT32 INTERCOMM_Socket_Close(GM_INT16 *pSock);

    /**
    * @brief 设置socket属性
    *
    * Detailed description.
    * @param[in] sock
    * @param[in] socket_send_buf_len
    * @param[in] socket_recv_buf_len
    * @return GM_INT32
    */
    GM_INT32 INTERCOMM_Socket_Set_Option(GM_INT16 sock, GM_INT32 socket_send_buf_len , GM_INT32 socket_recv_buf_len);

    /**
    * @brief 初始化UDP socket
    *
    * Detailed description.
    * @param[in] pSock
    * @param[in] type
    * @param[in] pAddr
    * @param[in] socket_send_buf_len
    * @param[in] socket_recv_buf_len
    * @param[in] pMax_socket_value
    * @return GM_INT32
    */
GM_INT32 INTERCOMM_Socket_Init( GM_INT16 *pSock , GM_INT32 type , struct sockaddr_in *pAddr , GM_INT32 socket_send_buf_len , GM_INT32 socket_recv_buf_len , GM_INT16 *pMax_socket_value);

    /**
    * @brief 判断socket是否可读
    *
    * @param[in] socket
    * @param[in] max_socket_value 系统socket描述符的最大值
    * @param[in] time_Out 等待超时, 等待后仍不可读才返回.单位:ms,
    * @return GM_BOOL
    */
    GM_BOOL INTERCOMM_Socket_Is_Readable(GM_INT16 sock, GM_INT16 max_socket_value, GM_INT32 time_Out);


    /**
    * @brief 判断socket是否可写
    *
    * @param[in] socket
    * @param[in] max_socket_value 系统socket描述符的最大值
    * @param[in] time_Out 等待超时, 等待后仍不可写才返回.单位:ms,
    * @return GM_BOOL
    */
    GM_BOOL INTERCOMM_Socket_Is_Writable(GM_INT16 sock, GM_INT16 max_socket_value, GM_INT32 time_Out);
#ifdef __cplusplus
}
#endif

#endif