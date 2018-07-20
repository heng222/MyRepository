/**
* @file GM_CFG_INTERCOMM_TCP_Object.h
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


#ifndef _GM_CFG_INTERCOMM_TCP_OBJ_H_
#define _GM_CFG_INTERCOMM_TCP_OBJ_H_
#include "../GM_Define.h"
#include "../GM_Utils/GM_MQ_Fixed.h"
#include "../GM_Utils/GM_Utils_Base.h"
#include "../FSFB/GM_RSSP1_Utils.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define MAX_SERVER_SOCK_NUM         6U           /**< 服务器的最大套接数*/
#define MAX_CONNECTION_NUM          6U           /**< 应用层最大连接数目 */
#define MAX_CHANNEL_CONNECTIONS     1U            /**< 默认D服务为双通道 */
#define RSSP2_SOCKET                 int
#define RSSP2_INVALID_SOCKET  (-1)
#define RSSP2_SOCKET_OK              0
#define RSSP2_SOCKET_ERROR           (-1)


    typedef enum TCP_Initialize_Library_Result_Enum_
    {
        TCP_Initialize_Library_OK             = 3000U,
        TCP_Initialize_Library_ERROR          = 3001U
    } TCP_Initialize_Library_Result_Enum;
		
	
	
    typedef enum
    {
        Library_State_Unknown     = 1010U, /* Object not initialized or NULL pointer. */
        Library_State_Operational = 1030U, /* All API funtions are enabled. */
        Library_State_Failure     = 1040U  /* Failure */
    } Library_State_Enum;    
    
    
    typedef enum
    {
        Layer_State_Unknow        = 9999U,         /**< 未知状态, 不可用, 必须经过初始化 */
        Layer_State_Free          = 1111U,         /**< 经过初始化后的状态, 可进行下一步操作 */
        Layer_State_Connecting    = 2222U,         /**< 正在连接 */
        Layer_State_Connected     = 3333U/*,*/         /**< 已连接, 可为上层提供服务 */
        /*Layer_State_Disconnecting = 4444U*/          /**< 正在断开连接 */
    } Layer_State_Enum;    
    
    typedef enum
    {
        Role_Client         = 0xaaU,    /**< 主动连接, 即本机为客户端*/
        Role_Server         = 0x55U      /**< 被动连接, 即本机为服务器端*/
    } Role_enum;    

    typedef struct
    {
        char             ip_str[64U];
        GM_UINT32        IP;         /**<  IP地址 */
        GM_UINT16        port;       /**<  端口 */
    } GM_PACKED Transport_Config_struct;

    typedef struct
    {
        GM_UINT8                *p_rcv_buf;         /**< 接收到的TCP数据缓冲区 */
        GM_UINT32                buf_size;           /**< 给缓冲区分配的容量:字节数 */

        GM_UINT32                buf_head_pos;       /**< 当前有效数据部分相对于缓冲区头的偏移量 */
        GM_UINT32                valid_dat_len;      /**< 当前有效数据长度 */
    } GM_PACKED TCP_Rcv_PKT_Buf_struct;	


    typedef struct
    {
        GM_INT32                index;                  /**< 连接下标*/
        Role_enum               Role;                   /**< 通道的通信角色:主动/被动 */
		Layer_State_Enum        TCP_State;              /**< TCP状态, 即冗余连接的状态*/
	    RSSP2_SOCKET            socket;                 /**< 接受套接字 */	
		TCP_Rcv_PKT_Buf_struct  rcv_buf;   /**< 接收缓冲区 */
		TCP_Rcv_PKT_Buf_struct  send_buf;   /**< 发送缓冲区 */

    } GM_PACKED TCP_Connection_struct;


    typedef struct
    {
        Library_State_Enum      libraryState;               /**< 库状态 */
        GM_BOOL                 is_server;                  /**< 本设备是否作为服务器 */
        RSSP2_SOCKET            server_socket[MAX_SERVER_SOCK_NUM]; /**< 服务器端监听套接字 */		
        Transport_Config_struct server_IP_port[MAX_SERVER_SOCK_NUM];/**< IP、端口配置 */
        Transport_Config_struct local_IP_port[MAX_SERVER_SOCK_NUM];/**< IP、端口配置 */		
        RSSP2_SOCKET            max_socket_value;           /**< 系统启动的socket的最大值, 初始化为0 */		
        GM_UINT32               sock_check_counter;         /**检测server socket的maintain()周期数 */

        GM_UINT16               connection_nums;            /**< 连接数*/
        TCP_Connection_struct   connection[MAX_CONNECTION_NUM];         /**< 各连接 */

    } GM_PACKED TCP_Object_struct;



#ifdef __cplusplus
}
#endif /* extern "C" */


#endif
