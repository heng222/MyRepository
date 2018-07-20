#ifndef _GM_RSSP1_APP_INTERFACE_H
#define _GM_RSSP1_APP_INTERFACE_H

#include "SFM/GM_RSSP1_SFM_Init.h"
#include "SFM/GM_RSSP1_SFM_Interface.h"

#include "CFM/GM_RSSP1_CFM_Init.h"
#include "CFM/GM_RSSP1_CFM_Interface.h"

#include "GM_RSSP1_MQ_Interface.h"

#ifdef __cplusplus
extern "C"
{
#endif

	#define    INTERFACE_TYPE_RSSP1         0x11        /* RSSP-I接口相关 */
	#define    INTERFACE_DAT_TYPE_RSSP1_DAT         0x11        /* RSSP1应用数据 */
	#define    INTERFACE_DAT_TYPE_RSSP1_COM_STATE   0x13        /* RSSP1连接状态 */
	#define    INTERFACE_DAT_TYPE_RSSP1_WARNING     0x15        /* RSSP1报警信息 */
	#define    INTERFACE_TYPE_SYN     0x55        /* 系间DVCOM同步接口相关 */
	#define    INTERFACE_DAT_TYPE_SYN_RSSP1_STATUS_DAT    0x43        /* 系间同步的RSSP1安全连接状态数据 */

	typedef enum
	{
		ABAS_Type_A_AS = 0x1111, /**< 自己为A机主机, Peer为备机 */
		ABAS_Type_A_SA = 0x2222, /**< 自己为A机备机, Peer为主机 */
		ABAS_Type_A_AA = 0x3333, /**< 自己为A机主机, Peer为主机 */
		ABAS_Type_A_SS = 0x4444, /**< 自己为A机备机, Peer为备机 */
		ABAS_Type_B_AS = 0x5555, /**< 自己为B机主机, Peer为备机 */
		ABAS_Type_B_SA = 0x6666, /**< 自己为B机备机, Peer为主机 */
		ABAS_Type_B_AA = 0x7777, /**< 自己为B机主机, Peer为主机 */
		ABAS_Type_B_SS = 0x8888, /**< 自己为B机备机, Peer为备机 */
		ASAS_Type_Unknow = 0x9999
	} GM_VLE_ABAS_Type_enum;


	typedef GM_UINT16(*GM_RSSP_GET_ABAS_FUN)(); /**< 获取应用主备状态 */

#ifdef PF2oo3
	#define RSSP1_MAX_MESSAGE_SIZE         1460

	typedef struct {
		GM_UINT16 PeripheralNumber; /*peripheral number identifier*/
		GM_UINT16 MsgSize; /*the message size*/
		GM_UINT8  Message[RSSP1_MAX_MESSAGE_SIZE]; /*the message size. Array of byte. Max size defined by MAXMSGSIZE*/
	}RSSP_Message_t;

#endif

	/**
    * @brief 处理FSFB模块的初始化
    * Detailed description.
    * @param[in] pSFM
    * @param[in] pCFM
    */
#if 0
	GM_BOOL GM_RSSP1_APP_Interface_Init_Addr(GM_RSSP_GET_ABAS_FUN fun, GM_UINT8* SFM_Addr, GM_UINT8* CFM_Addr, GM_UINT8* Addr);
#endif	
	/**
    * @brief 处理FSFB模块的初始化
    * Detailed description.
    * @param[in] pSFM
    * @param[in] pCFM
    */
#if 0
    GM_BOOL GM_RSSP1_APP_Interface_Init(GM_RSSP_GET_ABAS_FUN fun, char* path);
#endif
	/**
    * @brief 处理CSP FSFB模块的初始化
    * Detailed description.
    * @param[in] pSFM
    * @param[in] pCFM
    */
    GM_BOOL GM_RSSP1_APP_Interface_Init_CSP(GM_RSSP_GET_ABAS_FUN fun, char* pcfg, GM_UINT32 len);


    /**
    * @brief 获取主备机的信息
    * Detailed description.
    * @param[in] pSFM
    * @param[in] pCFM
    */
    GM_BOOL GM_RSSP1_APP_Interface_Get_Syn_AB_AS_Info(Local_Sys_AB_enum *p_sys_a_b , GM_BOOL *p_bactive);


    /**
    * @brief
    * Detailed description.
    * @param[in]
    * @param[in]
    */
    GM_BOOL GM_RSSP1_APP_Interface_Is_Local_ACTIVE(void);



    /**
    * @brief 向FSFB模块发送应用数据
    * Detailed description.
    * @param[in] pSFM
    * @param[in] pCFM
    */
    GM_BOOL GM_RSSP1_Send_App_Dat(GM_UINT8 *pDat , GM_UINT32 dat_len);


    /**
    * @brief 对FSFB模块接收到的数据进行预处理
    * Detailed description.
    * @param[in] pSFM
    * @param[in] pCFM
    */
    void GM_RSSP1_APP_Interface_Pre_Proc();

	/**
	* @brief 
	* 清空消息队列.
	* @param[in] p_dat
	* @param[in] dat_len
	*/
	GM_BOOL GM_RSSP1_APP_Clear_Msg_Queue(void);

	/**
	* @brief 
	* 安全层与应用层接口,提供接收数据
	* @param[in] p_dat
	* @param[in] dat_len
	*/
	GM_INT8 GM_RSSP1_APP_Interface_Rcv_App_Dat(GM_UINT8* buf, GM_UINT32* Src, GM_UINT32* len);

	/**
	* @brief 
	* 安全层与应用层接口,发送用户数据
	* @param[in] p_dat
	* @param[in] dat_len
	*/
	GM_BOOL GM_RSSP1_APP_Interface_Send_App_Dat(GM_UINT8* pData, GM_INT16 len, GM_UINT16 dest_addr);

#ifdef PF2oo3
	/**
	* @brief 
	* CFM安全层与通信层接口,提供接收数据
	* @param[in] p_dat
	* @param[in] dat_len
	*/
	GM_BOOL GM_RSSP1_2oo3_Conn_Send_Dat(RSSP_Message_t* msg, GM_UINT8 index, GM_UINT8 chn_index);

	/**
	* @brief 
	* CFM安全层与通信层接口,发送用户数据
	* @param[in] p_dat
	* @param[in] dat_len
	*/
	GM_BOOL GM_RSSP1_2oo3_Conn_Recv_Dat(RSSP_Message_t* msg, GM_UINT8 index, GM_UINT8 chn_index);
#endif

#ifdef __cplusplus
}

#endif

#endif /* _CILK_APP2_H_ */
