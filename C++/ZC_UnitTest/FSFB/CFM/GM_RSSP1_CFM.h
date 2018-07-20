/**
* @file GM_RSSP1_CFM.h
* @brief CFMģ��ṹ���塢��ؽӿڡ�����������
* @author JiangHongjun
* @date 2010-2-7 16:21:23
* @version
* <pre><b>copyright: CASCO</b></pre>
* <pre><b>email: </b>jianghongjun@casco.com.cn</pre>
* <pre><b>company: </b>http://www.casco.com.cn</pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>Write modifications here.</pre>
*/


#ifndef _GM_RSSP1_CFM_H_
#define _GM_RSSP1_CFM_H_

#include "../GM_RSSP1_Lib_Def.h"
#include "../GM_RSSP1_Msg_Queue.h"


#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum
	{
		GM_RSSP1_CFM_Get_SFM_Req_AVAILABLE           = 3300, /* pL2U parameters has been filled with a Pri. */
		GM_RSSP1_CFM_Get_SFM_Req_UNAVAILABLE         = 3301, /* No  Pri available. pU2L is meaningless. */
		GM_RSSP1_CFM_Get_SFM_Req_INVALID_OBJ         = 3302, /* The object pointed by pFSFB_CFM is invalid (NULL). */
		GM_RSSP1_CFM_Get_SFM_Req_INVALID_L2U         = 3303, /* The object pointed by pL2U is invalid (NULL). */
		GM_RSSP1_CFM_Get_SFM_Req_LIB_NOT_OPERATIONAL = 3304, /* The library is not in operational state (FSFB_CFM_Library_State_Operational). */
		GM_RSSP1_CFM_Get_SFM_Req_UNPROTECTED_OBJ     = 3305  /* The object pointed by pSFM has an invalid protection. */
	} GM_RSSP1_CFM_Get_SFM_Req_Result_Enum;


	/** һ��UDPͨ���Ľṹ���� */

	typedef struct
	{
		GM_BOOL                       b_connected;
        GM_UINT32                     loc_ip;
        GM_UINT32                     rem_ip;
        GM_UINT32                     loc_port;
        GM_UINT32                     rem_port;
	}GM_PACKED GM_RSSP1_CFM_chn_mng_struct;

	typedef struct
	{
		GM_UINT8                 index;
		GM_RSSP1_connection_state_enum      state;                  /**< ����״̬ */

		GM_RSSP1_SACEPID_struct              SaCEPID;                /**< ��ȫ����ID */
		GM_BOOL                       b_enable_CRSCD_pack;    /**< ʹ��ͨ�����ԺTCC�������.�����һ����һ������ */
		GM_RSSP1_CFM_Com_Type_Enum          com_type;               /**< �ײ�����ͨ�ŷ�ʽ  */   	    
		GM_UINT16                     chn_num;                            /**< ����ͨ������������GM_RSSP1_CFM_MAX_CHANNEL_NUM */
		GM_RSSP1_CFM_chn_mng_struct     com_chn[GM_RSSP1_CFM_MAX_CHANNEL_NUM];  /**< ��������ͨ�� */
	}GM_PACKED GM_RSSP1_CFM_connection_struct;

	/** ͨ�Ų�ģ�鶨�� */

	typedef struct
	{
		GM_RSSP1_library_state_enum         lib_state;
		GM_UINT16                     connection_nums;
		GM_RSSP1_CFM_connection_struct      connection[GM_RSSP1_MAX_SAFETY_CONNECTION_NUM];
	} GM_PACKED GM_RSSP1_CFM_object_struct;


	/************************************************************************/
	/* �ӿ�                                         */
	/************************************************************************/

	/**
	* @brief ��ȡ��̬CFM������ָ����ʽ���ء�
	*
	* Detailed description.
	* @return GM_RSSP1_CFM_object_struct*
	*/
	GM_RSSP1_CFM_object_struct *GM_RSSP1_Get_CFM_Object(void);

	/**
	* @brief ��ȡCFMģ��״̬
	*
	* Detailed description.
	* @param[in] pCFM
	* @return GM_RSSP1_library_state_enum
	*/
	GM_RSSP1_library_state_enum GM_RSSP1_CFM_Get_Library_Status(GM_RSSP1_CFM_object_struct *pCFM);

	/**
	* @brief �ж�����SACEPID�Ƿ����
	*
	* Detailed description.
	* @param[in] pSaCEPID1
	* @param[in] pSaCEPID2
	* @return GM_BOOL
	*/
	GM_BOOL GM_RSSP1_CFM_Is_SaCEPID_Equal(GM_RSSP1_SACEPID_struct *pSaCEPID1 , GM_RSSP1_SACEPID_struct *pSaCEPID2);

	/**
	* @brief ����SACEPID��ȡһ����ȫ����
	*
	* Detailed description.
	* @param[in] pSaCEPID
	* @param[in] pSFM
	* @return GM_RSSP1_CFM_connection_struct*
	*/
	GM_RSSP1_CFM_connection_struct *GM_RSSP1_CFM_Get_Connection_BY_SaCEPID(GM_RSSP1_SACEPID_struct *pSaCEPID , GM_RSSP1_CFM_object_struct *pCFM);

	/**
	* @brief CFM��SFM�����¼�
	*
	* �˽ӿ�ΪCFM�ڲ��ӿ�.
	* @param[in] pL2U_pri
	* @param[in] pCFM
	* @return GM_BOOL
	*/
	GM_BOOL GM_RSSP1_CFM_Report_indi_To_SFM(GM_RSSP1_CFM_L2U_pri_struct *pL2U_pri, GM_RSSP1_CFM_object_struct *pCFM);

	/**
	* @brief  CFM��������SFM����Ϣ
	*
	* Detailed description.
	* @param[in] pCFM
	*/
	void GM_RSSP1_CFM_Proc_SFM_Req(GM_RSSP1_CFM_object_struct *pCFM);

	/**
	* @brief CFM��������SFMģ��İ�ȫ���ݰ�
	*
	* ��Ҫ��SSE��SSE��SSR�������ݰ���
	* @param[in] pDat
	* @param[in] dat_len
	* @param[in] pCFM_con
	* @param[in] pCFM
	* @return GM_BOOL
	*/
	GM_BOOL GM_RSSP1_CFM_Send_Dat(GM_UINT8 *pDat , GM_UINT16 dat_len , GM_RSSP1_CFM_connection_struct *pCFM_con , GM_RSSP1_CFM_object_struct *pCFM, GM_UINT8 index);

	/**
	* @brief CFM���������ϲ�����ݰ�
	*
	* ��Ҫ����ֻ��CFM�����
	* @param[in] psacepid
	* @param[in] pDat
	* @param[in] len
	* @param[in] pCFM
	* @return GM_BOOL
	
	GM_BOOL GM_RSSP1_CFM_User_Send_Dat(GM_RSSP1_SACEPID_struct *psacepid , GM_UINT8 *pDat , GM_UINT16 len , GM_RSSP1_CFM_object_struct *pCFM);
	
	GM_BOOL GM_RSSP1_CFM_User_Send_Dat_By_Index(GM_UINT8 index , GM_RSSP1_SACEPID_struct *psacepid , GM_UINT8 *pDat , GM_UINT16 len , GM_RSSP1_CFM_object_struct *pCFM);
	*/
	GM_BOOL GM_RSSP1_CFM_Proc_Con_Rcvd_Dat(GM_RSSP1_CFM_connection_struct *pCFM_con , GM_RSSP1_CFM_object_struct * pCFM, GM_UINT8 index);

	/**
	* @brief CFMģ�鴦����յ������ݰ�
	*
	* Detailed description.
	* @param[in] pCFM
	*/
	void GM_RSSP1_CFM_Proc_Recvd_Dat(GM_RSSP1_CFM_object_struct * pCFM);

	void GM_RSSP1_CFM_Report_com_State_To_SFM(GM_RSSP1_CFM_object_struct *pCFM);

#ifdef __cplusplus
}
#endif

#endif
