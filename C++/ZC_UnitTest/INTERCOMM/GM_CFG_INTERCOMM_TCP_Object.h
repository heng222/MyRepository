/**
* @file GM_CFG_INTERCOMM_TCP_Object.h
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

#define MAX_SERVER_SOCK_NUM         6U           /**< ������������׽���*/
#define MAX_CONNECTION_NUM          6U           /**< Ӧ�ò����������Ŀ */
#define MAX_CHANNEL_CONNECTIONS     1U            /**< Ĭ��D����Ϊ˫ͨ�� */
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
        Layer_State_Unknow        = 9999U,         /**< δ֪״̬, ������, ���뾭����ʼ�� */
        Layer_State_Free          = 1111U,         /**< ������ʼ�����״̬, �ɽ�����һ������ */
        Layer_State_Connecting    = 2222U,         /**< �������� */
        Layer_State_Connected     = 3333U/*,*/         /**< ������, ��Ϊ�ϲ��ṩ���� */
        /*Layer_State_Disconnecting = 4444U*/          /**< ���ڶϿ����� */
    } Layer_State_Enum;    
    
    typedef enum
    {
        Role_Client         = 0xaaU,    /**< ��������, ������Ϊ�ͻ���*/
        Role_Server         = 0x55U      /**< ��������, ������Ϊ��������*/
    } Role_enum;    

    typedef struct
    {
        char             ip_str[64U];
        GM_UINT32        IP;         /**<  IP��ַ */
        GM_UINT16        port;       /**<  �˿� */
    } GM_PACKED Transport_Config_struct;

    typedef struct
    {
        GM_UINT8                *p_rcv_buf;         /**< ���յ���TCP���ݻ����� */
        GM_UINT32                buf_size;           /**< �����������������:�ֽ��� */

        GM_UINT32                buf_head_pos;       /**< ��ǰ��Ч���ݲ�������ڻ�����ͷ��ƫ���� */
        GM_UINT32                valid_dat_len;      /**< ��ǰ��Ч���ݳ��� */
    } GM_PACKED TCP_Rcv_PKT_Buf_struct;	


    typedef struct
    {
        GM_INT32                index;                  /**< �����±�*/
        Role_enum               Role;                   /**< ͨ����ͨ�Ž�ɫ:����/���� */
		Layer_State_Enum        TCP_State;              /**< TCP״̬, ���������ӵ�״̬*/
	    RSSP2_SOCKET            socket;                 /**< �����׽��� */	
		TCP_Rcv_PKT_Buf_struct  rcv_buf;   /**< ���ջ����� */
		TCP_Rcv_PKT_Buf_struct  send_buf;   /**< ���ͻ����� */

    } GM_PACKED TCP_Connection_struct;


    typedef struct
    {
        Library_State_Enum      libraryState;               /**< ��״̬ */
        GM_BOOL                 is_server;                  /**< ���豸�Ƿ���Ϊ������ */
        RSSP2_SOCKET            server_socket[MAX_SERVER_SOCK_NUM]; /**< �������˼����׽��� */		
        Transport_Config_struct server_IP_port[MAX_SERVER_SOCK_NUM];/**< IP���˿����� */
        Transport_Config_struct local_IP_port[MAX_SERVER_SOCK_NUM];/**< IP���˿����� */		
        RSSP2_SOCKET            max_socket_value;           /**< ϵͳ������socket�����ֵ, ��ʼ��Ϊ0 */		
        GM_UINT32               sock_check_counter;         /**���server socket��maintain()������ */

        GM_UINT16               connection_nums;            /**< ������*/
        TCP_Connection_struct   connection[MAX_CONNECTION_NUM];         /**< ������ */

    } GM_PACKED TCP_Object_struct;



#ifdef __cplusplus
}
#endif /* extern "C" */


#endif
