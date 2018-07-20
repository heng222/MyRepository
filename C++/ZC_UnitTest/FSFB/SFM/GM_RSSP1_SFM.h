/**
* @file GM_RSSP1_SFM.h
* @brief SFMģ��ṹ���塢��ؽӿڡ�����������
* @author JiangHongjun
* @date 2010-2-7 16:17:44
* @version
* <pre><b>copyright: CASCO</b></pre>
* <pre><b>email: </b>jianghongjun@casco.com.cn</pre>
* <pre><b>company: </b>http://www.casco.com.cn</pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>Write modifications here.</pre>
*/

#ifndef _GM_RSSP1_SFM_H_
#define _GM_RSSP1_SFM_H_

#include "GM_RSSP1_TIME.h"

#include "../GM_RSSP1_Lib_Def.h"
#include "../GM_RSSP1_Msg_Queue.h"

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct _GM_RSSP1_CHN_ENV_
	{
		GM_UINT32   TC;
		GM_UINT32   TS;
		GM_UINT32   local_TC;       /*����յ����ݰ�ʱ�Լ�����������ֵ*/
		GM_UINT32   remote_TC;      /*����յ����ݰ�ʱ���ݰ��м�������ֵ*/
		GM_UINT32   sseTS;          /*����SSEʱ�Լ���TS��ֵ*/
		GM_UINT32   sseTC;          /*����SSEʱ�Լ���TC��ֵ*/
		GM_UINT32   dynamicKey;     /*sint+(sid^T(n))*/
		GM_UINT8   bSendSSE;       /*�Ƿ���SSE 0x00��ʾδ����sse, 0xff��ʾ������sse��δ�յ�ssr*/
	} GM_PACKED GM_RSSP1_CHN_ENV;



    /** Ӧ�ò���SFMע���������ԭ��Ľ�� */
    typedef enum
    {
        GM_RSSP1_User_Put_Pri_OK                    = 10100, /*< �ɹ�           */
        GM_RSSP1_User_Put_Pri_MQ_FULL               = 10112, /*< �ɹ���ԭ��������������������ݸ���  */

        GM_RSSP1_User_Put_Pri_INVALID_U2L           = 10102, /*< pU2LΪNULL, ��ԭ�����ݲ���ȷ */
        GM_RSSP1_User_Put_Pri_LIB_NOT_OPERATIONAL   = 10104, /*< SFMδ��ʼ��    */
        GM_RSSP1_User_Put_Pri_INVALID_REQ_TYPE      = 10105, /*< pU2L->Typeδ֪.*/
        GM_RSSP1_User_Put_Pri_INVALID_CONNECTION_ID = 10108  /*< id�Ƿ�         */
    } GM_RSSP1_User_Put_Pri_To_SFM_Result_enum;

    /** Ӧ�ò��ȡSFM״̬�¼������ݱ���ԭ��Ľ�� */
    typedef enum
    {
        GM_RSSP1_User_Get_Pri_OK                    = 10200, /*< �ɹ� */
        GM_RSSP1_User_Get_Pri_UNAVAILABLE           = 10210, /*< ԭ����Ч(����δ֪, ���ݳ��ȳ�����..) */
        GM_RSSP1_User_Get_Pri_INVALID_L2U           = 10230, /*< pL2U ΪNULL. */
        GM_RSSP1_User_Get_Pri_LIB_NOT_OPERATIONAL   = 10240  /*< SFMδ��ʼ��. */
    } GM_RSSP1_User_Get_Pri_From_SFM_Result_enum;

    /** һ��FSFBͨ���ṹ���� */

    typedef struct
    {
        GM_RSSP1_SFM_fsfb_chn_cfg_struct        chn_cfg;

        GM_UINT32                      PREC_SINIT[GM_RSSP1_MAX_DELTATIME_ARRAY_SIZE];
        GM_UINT32                      POST_RXDATA[GM_RSSP1_MAX_DELTATIME_ARRAY_SIZE];
        GM_UINT32                      PREC_FIRSTSINIT;

    } GM_PACKED GM_RSSP1_SFM_fsfb_chn_struct;

    /** һ��FSFB��ȫ���ӽṹ���� */

    typedef struct
    {
        GM_UINT8                         index;
        GM_RSSP1_connection_state_enum              state;                  /**< ����״̬���ж�ͨ�ϵ����ݣ�FSFBʧ��/lifetimeʱ������û�л��У��ɹ������� */
        GM_RSSP1_Remote_Dev_AS_State_enum           remote_dev_AS_state;    /**< ����յ�RSD������RSD�жϴ�FSFB���Ӷ�Ӧ��Զ���豸���������Ǳ��� */
        GM_INT8                                     state_check_counter1;    /**< ���Ӽ�����ڼ��� */
        GM_INT8                                     state_check_counter2;    /**< ���Ӽ�����ڼ���.����������������� jianghongjun 20110825 safety enhancement*/

        GM_RSSP1_SACEPID_struct                     SaCEPID;                /**< ��ȫ����ID */
        GM_UINT16                             source_addr;            /**< �����豸Դ��ַ��Ĭ�ϲ����豸��� */
        GM_UINT16                             dest_addr;              /**< Ŀ�ĵ�ַ��Ĭ�ϲ����豸��� */
        GM_UINT16                             deltaTime;              /**< Ĭ�Ϲ涨 RSD ֡�Ŀ�ͬ�����̵����ʱ��ƫ��������.����Ϊ 2 �루��ϵͳ����Ϊ250ms����������Ϊ0x08������ʱ������������ͬ��Уʱ���� */
        GM_UINT16                             lifeTime;               /**< Ĭ�Ϲ涨��ȫ����ֵ����Ч����������������ʱ��Ϊ 3 �루��ϵͳ����Ϊ 250ms����������Ϊ0x0C������ʱ���轫��ȫ����λ����ȫֵ��0�� */
        GM_UINT8                              num_data_ver;           /**< ��ȫͨ��ʱ��У��SSR���ݵİ汾��.RSSP1 spe 2.2.2.1.3.3 */

        GM_RSSP1_TIME                               time;                               /**< ʱ����ر���������TC�ȣ����������������� */
        GM_RSSP1_SFM_fsfb_chn_struct                fsfb_chn[GM_RSSP1_CHECK_CHN_NUM];       /**< FSFBͨ���������������ļ�ֱ�Ӷ���Ĳ����Լ����������õ��Ĳ��� */
        GM_RSSP1_CHN_ENV                            env[GM_RSSP1_CHECK_CHN_NUM];            /**< ͨ����������ر��� */

        GM_BOOL                               b_RSD_Already_Sent;               /**< �������Ѿ����͹�rsd,���ܷ�����һ��rsd */

        GM_BOOL                               b_enable_FSFB_on_chn;   /**< ��Ե��豸����UDPͨ����ʹ�ö�����FSFB�����ú��ϲ�ȡ���ݵķ�ʽ������ͬ������ͬһ���豸�ĸ�UDPͨ����FSFB���ӣ�CTCS-ID������ͬ!�ϲ���ȡ��һ�����ӵ����ݺ󣬽��������������ͬ�������е�L2U_dat_Q */
        GM_UINT32                            Chn_apply_FSFB_ID;      /**< ����UDPͨ��ʹ�ö�����FSFBʱ����ID��ͬ�ĸ�FSFB������ʵ����ͬһ��Ӧ�ò㣬�ɺϲ��������ϲ���ȡ���ݡ� */
        GM_RSSP1_Msg_Queue_struct                   L2U_dat_Q;                  /**< ����ȫ�������յ����ѽ��������ݰ�.���ڵ���UDPҲʹ�ö���FSFBУ������ */
									
        GM_UINT16                             torlerate_cycle_cfg;        /**< ��ˡ���ڣ�N����������δ�յ�RSD���ݣ���FSFB������δ�Ͽ�������һ����Ч���������ϲ㡣 */
		GM_INT8                                     torlerate_cycle_count1;      /**< ��ˡ������ */
        GM_INT8                                     torlerate_cycle_count2;      /**< ��ˡ���������Ӽ�������jianghongjun 20110825 safety enhancement */
        GM_RSSP1_SFM_L2U_pri_struct                 last_valid_dat_pri;         /**< ��һ����Ч�����ݰ������ڿ�ˡ */
        GM_BOOL                               b_rcvd_new_dat_in_cycle;    /**< ���������յ������� */
        GM_BOOL                               b_torlerant_dat_valid;      /**< ��ˡ�������Ƿ�Ϸ� */

    } GM_PACKED GM_RSSP1_SFM_connection_struct;

    /** ��ȫ��ģ�鶨�� */

    typedef struct
    {
        GM_RSSP1_library_state_enum         lib_state;
        GM_UINT16                     source_addr;        /**< �����豸Դ��ַ��Ĭ�ϲ����豸��� */
        GM_UINT32                     cycle_cout;
        GM_RSSP1_SFM_fsfb_local_para_cfg_struct local_cfg[GM_RSSP1_CHECK_CHN_NUM];

        GM_UINT16                     connection_nums;
        GM_RSSP1_SFM_connection_struct      connection[GM_RSSP1_MAX_SAFETY_CONNECTION_NUM];
    } GM_PACKED GM_RSSP1_SFM_object_struct;
	
	/**fulintai**/
	typedef enum
	{
		GM_RSSP1_SFM_Get_Pri_OK = 10200,  /*< �ɹ� */
		GM_RSSP1_SFM_Get_Pri_FAIL = 10240,  /*< CFMδ��ʼ�� */
		GM_RSSP1_SFM_Get_Pri_INVALID_L2U = 10250,  /*< pL2U=NULL*/
	} GM_RSSP1_SFM_Get_Pri_From_CFM_Result_enum;

	/**< SFM��CFMע���������ԭ��Ľ�� */
	typedef enum
	{
		GM_RSSP1_SFM_Put_Pri_OK                       = 10100, /*< �ɹ�. */
		GM_RSSP1_SFM_Put_Pri_MQ_FULL                  = 10112, /*< �ɹ���ԭ��������������������ݸ��� */

		GM_RSSP1_SFM_Put_Pri_INVALID_U2L              = 10102, /*< ԭ����Ч, ΪNULL. */
		GM_RSSP1_SFM_Put_Pri_LIB_NOT_OPERATIONAL      = 10104, /*< CFMδ��ʼ��. */
		GM_RSSP1_SFM_Put_Pri_INVALID_REQ_TYPE         = 10105, /*< ԭ������δ֪. */
		GM_RSSP1_SFM_Put_Pri_INVALID_CONNECTION_INDEX = 10108, /*< ԭ���е�ͨ���±�Ƿ�. */
	} GM_RSSP1_SFM_Put_Pri_To_CFM_Result_enum;/**< SFM��CFM��ȡ��������ԭ��Ľ�� */

    /************************************************************************/
    /* �ӿ�                                         */
    /************************************************************************/

    /**
    * @brief ��ȡ�����Ƿ�������
    *
    * Detailed description.
    * @return GM_BOOL
    */
    GM_BOOL SYS_Is_Local_Sys_Active(void);

    /**
    * @brief ��ȡSFMģ��
    *
    * Detailed description.
    * @return GM_RSSP1_SFM_object_struct*
    */
    GM_RSSP1_SFM_object_struct *GM_RSSP1_Get_SFM_Object(void);


    /**
    * @brief  ��ʼ��FSFBУ��ͨ�������߲���
    *
    * Detailed description.
    * @param[in] pSFM_conn
    * @param[in] pSFM
    * @return GM_BOOL GM_RSSP1_SFM_Ini_FSFB_Offline_Const
    */
    GM_BOOL GM_RSSP1_SFM_Ini_FSFB_Offline_Const(GM_RSSP1_SFM_connection_struct *pSFM_conn , GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief FSFBУ�����ڲ���
    *
    * Detailed description.
    * @param[in] pSFM
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_SFM_Update_Time(GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief ��ȡSFMģ���״̬
    *
    * Detailed description.
    * @param[in] pSFM
    * @return GM_RSSP1_library_state_enum
    */
    GM_RSSP1_library_state_enum GM_RSSP1_SFM_Get_Library_Status(GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief ����SACEPID��ȡһ����ȫ����
    *
    * Detailed description.
    * @param[in] pSaCEPID
    * @param[in] pSFM
    * @return GM_RSSP1_SFM_connection_struct*
    */
    GM_RSSP1_SFM_connection_struct *GM_RSSP1_SFM_Get_Connection_BY_SaCEPID(GM_RSSP1_SACEPID_struct *pSaCEPID , GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief �ж�����SACEPID�Ƿ����
    *
    * Detailed description.
    * @param[in] pSaCEPID1
    * @param[in] pSaCEPID2
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_SFM_Is_SaCEPID_Equal(GM_RSSP1_SACEPID_struct *pSaCEPID1 , GM_RSSP1_SACEPID_struct *pSaCEPID2);

    /**
    * @brief Ӧ�ò���SFMģ���������ԭ��
    *
    * Detailed description.
    * @param[in] pU2L
    * @param[in] pSFM
    * @return GM_RSSP1_User_Put_Pri_To_SFM_Result_enum
    */
    GM_RSSP1_User_Put_Pri_To_SFM_Result_enum GM_RSSP1_User_Put_Pri_To_SFM(GM_RSSP1_SFM_U2L_pri_struct *pU2L , GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief Ӧ�ò��SFMģ���ȡԭ��
    *
    * Detailed description.
    * @param[in] pL2U
    * @param[in] pSFM
    * @return GM_RSSP1_User_Get_Pri_From_SFM_Result_enum
    */
    GM_RSSP1_User_Get_Pri_From_SFM_Result_enum GM_RSSP1_User_Get_Pri_From_SFM(GM_RSSP1_SFM_L2U_pri_struct *pL2U , GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief Ӧ�ò㷢������
    *
    * ͨ��SACEPID��ʶ���ݽ��շ�.
    * @param[in] pSaCEPID
    * @param[in] pDat
    * @param[in] dat_len
    * @param[in] sysAORB
    * @param[in] bSysActive
    * @param[in] pMD5
    * @param[in] pSFM
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_User_Send_Dat(GM_RSSP1_SACEPID_struct *pSaCEPID , GM_UINT8 *pDat , GM_UINT32 dat_len , Local_Sys_AB_enum sysAORB , GM_BOOL bSysActive, GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief SFM����RSD���ݰ�
    *
    * Detailed description.
    * @param[in] pDat_pri
    * @param[in] pSFM_conn
    * @param[in] pSFM
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_SFM_Send_RSD(GM_RSSP1_SFM_U2L_pri_struct *pDat_pri , GM_RSSP1_SFM_connection_struct *pSFM_conn , GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief SFM����SSE���ݰ�
    *
    * Detailed description.
    * @param[in] pSFM_conn
    * @param[in] pSFM
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_SFM_Send_SSE(GM_RSSP1_SFM_connection_struct *pSFM_conn , GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief SFM����SSR���ݰ�
    *
    * Detailed description.
    * @param[in] rcvd_SEQENQ_1
    * @param[in] rcvd_SEQENQ_2
    * @param[in] rcvd_TC
    * @param[in] pSFM_conn
    * @param[in] pSFM
    * @param[in] pCFM
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_SFM_Send_SSR(GM_UINT32 rcvd_SEQENQ_1 , GM_UINT32 rcvd_SEQENQ_2 , GM_UINT32 rcvd_TC , GM_RSSP1_SFM_connection_struct *pSFM_conn , GM_RSSP1_SFM_object_struct *pSFM);

    void GM_RSSP1_SFM_Reset_Connection_RSD_Sent_Flag(GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief SFM����Ӧ�ò����Ϣ
    *
    * Detailed description.
    * @param[in] pSFM
    */
    void GM_RSSP1_SFM_Process_User_Req(GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief SFM��Ӧ�ò㱨����Ϣ
    *
    * SFM��Ŀ��sacepid��ͬ�����а�ȫ���Ӷ��������ݣ����������豸ͨ������FSFB�������������.
    * @param[in] pL2U_pri
    * @param[in] pSFM
    */
    void GM_RSSP1_SFM_Report_indi_To_User(GM_RSSP1_SFM_L2U_pri_struct *pL2U_pri , GM_RSSP1_SFM_object_struct *pSFM);

    void GM_RSSP1_SFM_Report_Connection_State_To_User(GM_RSSP1_SFM_object_struct *pSFM , GM_RSSP1_CFM_L2U_pri_struct *pIndi_pri);
    void GM_RSSP1_SFM_Report_Warning_To_User(GM_RSSP1_SFM_connection_struct *pSFM_con , GM_RSSP1_SFM_object_struct *pSFM , GM_UINT8 warning_type);

    /**
    * @brief SFM����CFM�յ�����Ϣ
    *
    * Detailed description.
    * @param[in] pSFM
    */
    void GM_RSSP1_SFM_Process_CFM_Ind(GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief SFM���Ӹ�����ȫ���ӵ�״̬���������Ƿ�Ҫ���п�ˡ��
    *
    * ͨ���������ӿ����õ�ʱ��ֵ���ڴ�ʱ����δ�յ�У����ȷ�����ݰ�������Ϊ�Ͽ�.
    * @param[in] pSFM
    */
    void GM_RSSP1_SFM_Proc_Connection_Monit_And_Tolerate(GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief SFM���������ȫ����ͨ���ڵ����ݶ���
    *
    * ��ΪӦ�ò�ֻ���ľ�����豸������ϵ�����豸��Զ���豸ͨ��������ȫ����ͨ��������
    * ����b_enable_FSFB_on_chnѡ��UDPͨ����FSFB���ӣ�CFM���������͵���ӦFSFB�����е�L2U���У�Dispatch����͵�SFM�е�L2U����
    * ����������FSFB���ӣ�CFM����������ݽ�ֱ���͵�SFM��L2U����.
    * @param[in] pSFM
    */
    void GM_RSSP1_SFM_Dispatch_Dat_Indi(GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief SFM������յ���SSE��
    *
    * Detailed description.
    * @param[in] pSFM_conn
    * @param[in] pDat_indi
    * @param[in] pSFM
    */
    void GM_RSSP1_SFM_Proc_Rcvd_SSE(GM_RSSP1_SFM_connection_struct *pSFM_conn , GM_RSSP1_CFM_L2U_Dat_pri_struct *pDat_indi , GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief SFM������յ���SSR��
    *
    * Detailed description.
    * @param[in] pSFM_conn
    * @param[in] pDat_indi
    * @param[in] pSFM
    */
    void GM_RSSP1_SFM_Proc_Rcvd_SSR(GM_RSSP1_SFM_connection_struct *pSFM_conn , GM_RSSP1_CFM_L2U_Dat_pri_struct *pDat_indi , GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief SFM������յ���RSD��
    *
    * Detailed description.
    * @param[in] pSFM_conn
    * @param[in] pDat_indi
    * @param[in] pSFM
    * @param[in] pCFM
    */
    void GM_RSSP1_SFM_Proc_Rcvd_RSD(GM_RSSP1_SFM_connection_struct *pSFM_conn , GM_RSSP1_CFM_L2U_Dat_pri_struct *pDat_indi , GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief SFM���ڼ��ؼ����ã���ֹԽ��ȵ��¹ؼ���ȫ���ñ��޸ġ�jianghongjun 20110825 safety enhancement
    *
    * Detailed description.
    * @param[in] pSFM
    */
    void GM_RSSP1_Check_Vital_Cfg(GM_RSSP1_SFM_object_struct *pSFM);

	/**
	* @brief SFM��CFM��ȡ�¼�
	*
	* �˽ӿ���CFM��SFM�ṩ
	* @param[in] pL2U
	* @return GM_RSSP1_SFM_Get_Pri_From_CFM_Result_enum
	*/
	GM_RSSP1_SFM_Get_Pri_From_CFM_Result_enum GM_RSSP1_SFM_Get_Pri_From_CFM(GM_RSSP1_CFM_L2U_pri_struct *pL2U);

		/**
	* @brief SFM��CFM�������
	*
	* �˽ӿ���CFM��SFM�ṩ.
	* @param[in] pU2L
	* @param[in] pSFM
	* @return GM_RSSP1_SFM_Put_Pri_To_CFM_Result_enum
	*/
	GM_RSSP1_SFM_Put_Pri_To_CFM_Result_enum GM_RSSP1_SFM_Put_Pri_To_CFM(GM_RSSP1_CFM_U2L_pri_struct *pU2L, GM_RSSP1_SFM_object_struct *pSFM);

#ifdef __cplusplus
}
#endif

#endif
