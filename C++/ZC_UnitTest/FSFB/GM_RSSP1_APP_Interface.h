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

	#define    INTERFACE_TYPE_RSSP1         0x11        /* RSSP-I�ӿ���� */
	#define    INTERFACE_DAT_TYPE_RSSP1_DAT         0x11        /* RSSP1Ӧ������ */
	#define    INTERFACE_DAT_TYPE_RSSP1_COM_STATE   0x13        /* RSSP1����״̬ */
	#define    INTERFACE_DAT_TYPE_RSSP1_WARNING     0x15        /* RSSP1������Ϣ */
	#define    INTERFACE_TYPE_SYN     0x55        /* ϵ��DVCOMͬ���ӿ���� */
	#define    INTERFACE_DAT_TYPE_SYN_RSSP1_STATUS_DAT    0x43        /* ϵ��ͬ����RSSP1��ȫ����״̬���� */

	typedef enum
	{
		ABAS_Type_A_AS = 0x1111, /**< �Լ�ΪA������, PeerΪ���� */
		ABAS_Type_A_SA = 0x2222, /**< �Լ�ΪA������, PeerΪ���� */
		ABAS_Type_A_AA = 0x3333, /**< �Լ�ΪA������, PeerΪ���� */
		ABAS_Type_A_SS = 0x4444, /**< �Լ�ΪA������, PeerΪ���� */
		ABAS_Type_B_AS = 0x5555, /**< �Լ�ΪB������, PeerΪ���� */
		ABAS_Type_B_SA = 0x6666, /**< �Լ�ΪB������, PeerΪ���� */
		ABAS_Type_B_AA = 0x7777, /**< �Լ�ΪB������, PeerΪ���� */
		ABAS_Type_B_SS = 0x8888, /**< �Լ�ΪB������, PeerΪ���� */
		ASAS_Type_Unknow = 0x9999
	} GM_VLE_ABAS_Type_enum;


	typedef GM_UINT16(*GM_RSSP_GET_ABAS_FUN)(); /**< ��ȡӦ������״̬ */

#ifdef PF2oo3
	#define RSSP1_MAX_MESSAGE_SIZE         1460

	typedef struct {
		GM_UINT16 PeripheralNumber; /*peripheral number identifier*/
		GM_UINT16 MsgSize; /*the message size*/
		GM_UINT8  Message[RSSP1_MAX_MESSAGE_SIZE]; /*the message size. Array of byte. Max size defined by MAXMSGSIZE*/
	}RSSP_Message_t;

#endif

	/**
    * @brief ����FSFBģ��ĳ�ʼ��
    * Detailed description.
    * @param[in] pSFM
    * @param[in] pCFM
    */
#if 0
	GM_BOOL GM_RSSP1_APP_Interface_Init_Addr(GM_RSSP_GET_ABAS_FUN fun, GM_UINT8* SFM_Addr, GM_UINT8* CFM_Addr, GM_UINT8* Addr);
#endif	
	/**
    * @brief ����FSFBģ��ĳ�ʼ��
    * Detailed description.
    * @param[in] pSFM
    * @param[in] pCFM
    */
#if 0
    GM_BOOL GM_RSSP1_APP_Interface_Init(GM_RSSP_GET_ABAS_FUN fun, char* path);
#endif
	/**
    * @brief ����CSP FSFBģ��ĳ�ʼ��
    * Detailed description.
    * @param[in] pSFM
    * @param[in] pCFM
    */
    GM_BOOL GM_RSSP1_APP_Interface_Init_CSP(GM_RSSP_GET_ABAS_FUN fun, char* pcfg, GM_UINT32 len);


    /**
    * @brief ��ȡ����������Ϣ
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
    * @brief ��FSFBģ�鷢��Ӧ������
    * Detailed description.
    * @param[in] pSFM
    * @param[in] pCFM
    */
    GM_BOOL GM_RSSP1_Send_App_Dat(GM_UINT8 *pDat , GM_UINT32 dat_len);


    /**
    * @brief ��FSFBģ����յ������ݽ���Ԥ����
    * Detailed description.
    * @param[in] pSFM
    * @param[in] pCFM
    */
    void GM_RSSP1_APP_Interface_Pre_Proc();

	/**
	* @brief 
	* �����Ϣ����.
	* @param[in] p_dat
	* @param[in] dat_len
	*/
	GM_BOOL GM_RSSP1_APP_Clear_Msg_Queue(void);

	/**
	* @brief 
	* ��ȫ����Ӧ�ò�ӿ�,�ṩ��������
	* @param[in] p_dat
	* @param[in] dat_len
	*/
	GM_INT8 GM_RSSP1_APP_Interface_Rcv_App_Dat(GM_UINT8* buf, GM_UINT32* Src, GM_UINT32* len);

	/**
	* @brief 
	* ��ȫ����Ӧ�ò�ӿ�,�����û�����
	* @param[in] p_dat
	* @param[in] dat_len
	*/
	GM_BOOL GM_RSSP1_APP_Interface_Send_App_Dat(GM_UINT8* pData, GM_INT16 len, GM_UINT16 dest_addr);

#ifdef PF2oo3
	/**
	* @brief 
	* CFM��ȫ����ͨ�Ų�ӿ�,�ṩ��������
	* @param[in] p_dat
	* @param[in] dat_len
	*/
	GM_BOOL GM_RSSP1_2oo3_Conn_Send_Dat(RSSP_Message_t* msg, GM_UINT8 index, GM_UINT8 chn_index);

	/**
	* @brief 
	* CFM��ȫ����ͨ�Ų�ӿ�,�����û�����
	* @param[in] p_dat
	* @param[in] dat_len
	*/
	GM_BOOL GM_RSSP1_2oo3_Conn_Recv_Dat(RSSP_Message_t* msg, GM_UINT8 index, GM_UINT8 chn_index);
#endif

#ifdef __cplusplus
}

#endif

#endif /* _CILK_APP2_H_ */
