
#include "GM_RSSP1_INTERCOMM_Socket.h"
#include "../FSFB/GM_RSSP1_Utils.h"

/**
* @brief 内网通信套接字创建 
*
* Detailed description.
* @return GM_BOOL
*
*/
GM_INT32 INTERCOMM_Socket_Create(GM_INT32 type, GM_INT16 *max_socket_value)
{
    GM_INT32 new_socket = INTERCOMM_INVALID_SOCKET;

    if (NULL == max_socket_value)
    {
        return INTERCOMM_INVALID_SOCKET;
    }

    new_socket = socket(AF_INET, (GM_INT32)type, 0);

    if (new_socket < 0)
    {
        return INTERCOMM_INVALID_SOCKET;
    }

    if (*max_socket_value < (GM_INT16)new_socket)
    {
        *max_socket_value = (GM_INT16)new_socket;
    }

    return new_socket;
}

/**
* @brief 内网通信套接字关闭 
*
* Detailed description.
* @return GM_BOOL
*
*/
GM_INT32 INTERCOMM_Socket_Close(GM_INT16 *pSock)
{
    GM_INT32 rt = -1;

    if (NULL == pSock)
    {
        return -1;
    }

    if (0 > (*pSock))
    {
        return -1;
    }

#ifdef WIN32
    shutdown(*pSock, 2);

    rt = closesocket(*pSock);

#else
    shutdown(*pSock, 2);

    rt = (GM_INT32)close(*pSock);

#endif

    *pSock = INTERCOMM_INVALID_SOCKET;

    return rt;
}

/**
* @brief 内网通信套接字设置 
*
* Detailed description.
* @return GM_BOOL
*
*/
GM_INT32 INTERCOMM_Socket_Set_Option(GM_INT16 sock, GM_INT32 socket_send_buf_len , GM_INT32 socket_recv_buf_len)
{
    GM_UINT32 arg                      = 1U;
    GM_INT32 bReuseaddr                  = 1; /* 0: 不允许端口重用 .1 允许 */
    GM_INT32 bReuseport                  = 1;
    GM_INT32 len                         = 0;
    GM_INT32 opt_send_buf_len            = 0;
    GM_INT32 opt_recv_buf_len            = 0;
    GM_INT32 opt_tcp_send_no_delay       = 1;
    struct timeval opt_send_timeout;
    struct timeval opt_recv_timeout;
	GM_BOOL bNewBehavior			= GM_FALSE;
	GM_INT32 dwBytesReturned				= 0;

    if (0 > sock)
    {
        return GM_RSSP1_ERROR;
    }
    /* 公共属性设置 TODO:vxworks下需要设置最大文件描述符数目,默认为50.可通过iosFdShow查看. */
    /* 设置非阻塞 */
#ifdef WIN32
    if (GM_RSSP1_ERROR == ioctlsocket(sock, FIONBIO, &arg))
    {
        return GM_RSSP1_ERROR;
    }
	WSAIoctl(sock, _WSAIOW(IOC_VENDOR, 12), &bNewBehavior, sizeof(bNewBehavior), NULL, 0, &dwBytesReturned, NULL, NULL);
#endif
#ifndef WIN32    
    if (((GM_INT32)GM_RSSP1_ERROR) == ioctl(sock, FIONBIO, (GM_INT32)&arg))
    {
        return GM_RSSP1_ERROR;
    }

#endif


    /*  注意：在Linux系统中,如果一个socket绑定了某个端口,该socket正常关闭或程序退出后,在一段时间内该端口依然保持被绑定的状态,其他程序（或者重新启动的原程序）无法绑定该端口.可以通过调用以下语句避免该问题  */
    if (GM_RSSP1_ERROR == setsockopt(sock, SOL_SOCKET , SO_REUSEADDR, (char *)&bReuseaddr, sizeof(bReuseaddr)))
    {
 /*       GM_Log_Msg(0,"Fatal GM_RSSP1_ERROR! set server socket SO_REUSEADDR option fail! errno:%d.\n", FSFB_GET_LAST_ERRNO, 0, 0, 0, 0, 0);*/
 /*       printf("Fatal GM_RSSP1_ERROR! set server socket SO_REUSEADDR option fail!\n");  	*/	
    }
#ifndef WIN32    
    /* 允许重复绑定端口 */
    if (GM_RSSP1_ERROR == setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, (char *)&bReuseport, sizeof(bReuseport)))
    {
/*        GM_Log_Msg(0,"Fatal GM_RSSP1_ERROR! set server socket SO_REUSEPORT option fail! errno:%d.\n", FSFB_GET_LAST_ERRNO, 0, 0, 0, 0, 0); */
 /*       printf("Fatal GM_RSSP1_ERROR! set server socket SO_REUSEPORT option fail\n");  */
    }
#endif

    /* 设定发送缓冲区大小 = 1k左右,约等于MTU */
    len = sizeof(len);
    opt_send_buf_len = socket_send_buf_len;
    opt_recv_buf_len = socket_recv_buf_len;
    if (GM_RSSP1_ERROR == setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (const char *)&opt_send_buf_len, sizeof(len)))
    {
/*        GM_Log_Msg(0,"Fatal GM_RSSP1_ERROR! set server socket SO_SNDBUF option fail!errno:%d.\n", FSFB_GET_LAST_ERRNO, 0, 0, 0, 0 , 0); */
/*        printf("Set server socket SO_SNDBUF option fail\n");  */		

    }

    if (GM_RSSP1_ERROR == setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (const char *)&opt_recv_buf_len, sizeof(len)))
    {
/*        GM_Log_Msg(0,"Fatal GM_RSSP1_ERROR! set server socket SO_RCVBUF option fail!errno:%d.\n", FSFB_GET_LAST_ERRNO , 0, 0, 0, 0, 0);*/
 /*       printf("Set server socket SO_RCVBUF option fail\n");  	*/	

    }

    /* set send/recv timeout */
    opt_send_timeout.tv_sec     = 0;
    opt_send_timeout.tv_usec    = 0;
    if (GM_RSSP1_ERROR == setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char *)(&opt_send_timeout), (int)sizeof(opt_send_timeout)))
    {
/*        GM_Log_Msg(0,"Fatal GM_RSSP1_ERROR! set server socket SO_SNDTIMEO option fail! errno:%d\n", FSFB_GET_LAST_ERRNO, 0, 0, 0, 0, 0);*/
        printf("Set server socket SO_SNDTIMEO option fail\n");  		
    }

    opt_recv_timeout.tv_sec     = 0;
    opt_recv_timeout.tv_usec    = 0;
    if (GM_RSSP1_ERROR == setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)(&opt_recv_timeout), (int)sizeof(opt_recv_timeout)))
    {
/*        GM_Log_Msg(0,"Fatal GM_RSSP1_ERROR! set server socket SO_RCVTIMEO option fail! errno:%d\n", FSFB_GET_LAST_ERRNO, 0, 0, 0, 0, 0);*/
        printf("Set server socket SO_RCVTIMEO option fail\n");  		
    }

    return GM_RSSP1_OK;
}

/**
* @brief 内网通信套接字初始化 
*
* Detailed description.
* @return GM_BOOL
*
*/
GM_INT32 INTERCOMM_Socket_Init( GM_INT16 *pSock , GM_INT32 type , struct sockaddr_in *pAddr , GM_INT32 socket_send_buf_len , GM_INT32 socket_recv_buf_len , GM_INT16 *pMax_socket_value)
{
    char str[100U] = { 0 };
    
    if ((NULL == pSock) || (NULL == pAddr) || (NULL == pMax_socket_value))
    {
        return GM_RSSP1_ERROR;
    }

    if (0 <= *pSock)
    {
        INTERCOMM_Socket_Close(pSock);
    }

    *pSock = (GM_INT16)INTERCOMM_Socket_Create(type , pMax_socket_value);

    if (0 > *pSock)
    {
        return GM_RSSP1_ERROR;
    }

    if (GM_RSSP1_ERROR == INTERCOMM_Socket_Set_Option(*pSock , socket_send_buf_len , socket_recv_buf_len))
    {
        INTERCOMM_Socket_Close(pSock);
        return GM_RSSP1_ERROR;
    }

    /* bind socket */
    if (0 > bind(*pSock , (struct sockaddr *)pAddr , sizeof(struct sockaddr_in)))
    {
 
/*        if(FSFB_SOKC_ERR_EADDRINUSE != errno)*/
        {
            INTERCOMM_Socket_Close(pSock);
            return GM_RSSP1_ERROR;
        }	
    }
    else
    {

    }

    return GM_RSSP1_OK;
}

/**
* @brief 内网通信套接字是否可读 
*
* Detailed description.
* @return GM_BOOL
*
*/
GM_BOOL INTERCOMM_Socket_Is_Readable(GM_INT16 sock, GM_INT16 max_socket_value, GM_INT32 time_Out)
{
     int ret = -1;
    
    UINT32 l_len = 0U;    
    
    if (0 > sock)
    {
        return GM_FALSE;
    }    
    
    
    ret = ioctl(sock,FIONREAD,(int)(&l_len));  
    
    
    if (((UINT32)0) >= l_len)
    {
        return GM_FALSE;
    }
    else
    {
		
		return GM_TRUE;
		
    }	
}

/**
* @brief 内网通信套接字是否可写 
*
* Detailed description.
* @return GM_BOOL
*
*/
GM_BOOL INTERCOMM_Socket_Is_Writable(GM_INT16 sock, GM_INT16 max_socket_value, GM_INT32 time_Out)
{

    GM_INT32 ret = -1;

    if (0 > sock)
    {
        return GM_FALSE;
    }

	
    return GM_TRUE;	
	
}