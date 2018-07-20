/**
* @file GM_RSSP1_Lib_Def.h
* @brief FSFBģ�鼰�����õĶ���
* @author JiangHongjun
* @date 2010-2-7 16:23:06
* @version
* <pre><b>copyright: CASCO</b></pre>
* <pre><b>email: </b>jianghongjun@casco.com.cn</pre>
* <pre><b>company: </b>http://www.casco.com.cn</pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>Write modifications here.</pre>
*/



/************************************************************************/
/* FSFB SFM��CFMģ�鶨��                               */
/************************************************************************/

#ifndef _GM_RSSP1_LIB_DEF_H_
#define _GM_RSSP1_LIB_DEF_H_

#include "GM_RSSP1_Utils.h"
#include "GM_RSSP1_Msg_Define.h"
#include "../GM_Utils/GM_Utils_Base.h"
#ifdef LINK_Part
#include "UDP/FSFB_LINK_Def.h"
#endif


#ifdef __cplusplus
extern "C"
{
#endif


		/** ������Ϣ : MD5У��������ա�����SSE��SSR������RSDУ�����ȱ�����Ϣ */
	#define GM_RSSP1_SFM_WARNING_TYPE_SEND_DAT_SAFE_CHECKSUM_ERR        0    /**< ���͵������ڽӿڽ��������У�У����� */
	#define GM_RSSP1_SFM_WARNING_TYPE_RECV_DAT_SAFE_CHECKSUM_ERR        1    /**< ���յ������ڽӿڽ��������У�У����� */
	#define GM_RSSP1_SFM_WARNING_TYPE_FSFB_CRCM_CHECK_ERR               2
	#define GM_RSSP1_SFM_WARNING_TYPE_RECV_SSE                          3
	#define GM_RSSP1_SFM_WARNING_TYPE_RECV_SSR                          4
	#define GM_RSSP1_SFM_WARNING_TYPE_SSE_BUILD_ERR                     5
	#define GM_RSSP1_SFM_WARNING_TYPE_RCVD_SSE_CRC_ERROR                6
	#define GM_RSSP1_SFM_WARNING_TYPE_RCVD_SSR_CRC_ERROR                7
	#define GM_RSSP1_SFM_WARNING_TYPE_RCVD_RSD_CRC_ERROR                8
	#define GM_RSSP1_SFM_WARNING_TYPE_RCVD_UNKNOW_TYPE_FRAME            9    /**< �յ�δ֪��������֡ */
	#define GM_RSSP1_SFM_WARNING_TYPE_RECV_NO_RSD_IN_DELTATIME          10   /**< deltatime��δ�յ�RSD */

		/** ״̬�����и���ֵ���趨��������Ӧ�ò�(VLE)�ӿ�����֡��ʽ�������ݣ���Ҫ��VLE�˱���һ�� */
	#define GM_RSSP1_REPORT_STATE_TO_APP_FSFB_OK        (0xf)
	#define GM_RSSP1_REPORT_STATE_TO_APP_FSFB_FAIL      (0x0)
	#define GM_RSSP1_REPORT_STATE_TO_APP_REMOTE_ACTIVE  (0xf)
	#define GM_RSSP1_REPORT_STATE_TO_APP_REMOTE_STANDBY (0x0)
	#define GM_RSSP1_REPORT_STATE_TO_APP_REMOTE_UNKOWN  (0xc)


    /** Ӧ�ò���������A������B�� */
    typedef enum
    {
        GM_RSSP1_Local_Sys_A = 0x80,      /**< A�����͵����� */
        GM_RSSP1_Local_Sys_B = 0x81,      /**< B�����͵����� */
        GM_RSSP1_Local_Sys_UNLOWN = 0
	} Local_Sys_AB_enum;

    /** Զ���豸��A������B�� */
    typedef enum
    {
        GM_RSSP1_Remote_Dev_Active  = 0x80,      /**< �յ����ǶԷ��������͵����� */
        GM_RSSP1_Remote_DEV_Standby = 0x81,      /**< �յ����ǶԷ��������͵����� */
        GM_RSSP1_Remote_DEV_Unknow  = 0xff       /**< ״̬δ֪����������û���յ��Է�RSD֮ǰ */
    } GM_RSSP1_Remote_Dev_AS_State_enum;

    typedef enum
    {
        GM_RSSP1_MSG_TYPE_SSE = 0 ,
        GM_RSSP1_MSG_TYPE_SSR = 1 ,
        GM_RSSP1_MSG_TYPE_RSD = 2 ,
        GM_RSSP1_MSG_TYPE_UNKNOW = 0xff
    } GM_RSSP1_Msg_Type_enum;

    typedef enum
    {
        GM_RSSP1_Layer_State_Unknow        = 9999,         /**< δ֪״̬, ������, ���뾭����ʼ�� */
        GM_RSSP1_Layer_State_Free          = 0,            /**< ������ʼ�����״̬, �ɽ�����һ������ */
        GM_RSSP1_Layer_State_Connecting    = 2222,         /**< �������� */
        GM_RSSP1_Layer_State_Connected     = 3333,         /**< ������, ��Ϊ�ϲ��ṩ���� */
        GM_RSSP1_Layer_State_Disconnecting = 4444          /**< ���ڶϿ����� */
    } GM_RSSP1_connection_state_enum;

    typedef enum
    {
        GM_RSSP1_Lib_State_Unknown     = 1010, /* δ��ʼ�� */
        GM_RSSP1_Lib_State_Operational = 1030, /* �ɹ���ʼ�� */
        GM_RSSP1_Lib_State_Failure     = 1040  /* ʧЧ */
    } GM_RSSP1_library_state_enum;


	typedef enum
	{
		GM_RSSP1_CFM_COMM_TYPE_UDP           = 0x1111, /* �ײ����udpͨ�� */
		GM_RSSP1_CFM_COMM_TYPE_SCOM           = 0x2222, /* �ײ���ô���ͨ�� */
	    
		GM_RSSP1_CFM_COMM_TYPE_UNKNOW           = 0xffff /* �ײ���ô���ͨ�� */
	} GM_RSSP1_CFM_Com_Type_Enum;
	/*typedef GM_RSSP1_CFM_Com_Type_Enum FSFB_LNK_Com_Type_Enum;*/


    /**SaCEPID�ṹ, ��������ÿ����ȫ�����նˡ�TODO:����Ψһȷ������Ҫ������Ϣ */

    typedef struct
    {
        GM_UINT16        source_addr;     /**< Դ��ַ */
        GM_UINT16        dest_addr;       /**< Ŀ�ĵ�ַ */
    } GM_PACKED GM_RSSP1_SACEPID_struct;



    /****************************************************************************/
    /*****                     FSFB SFM                       *****/
    /****************************************************************************/
    typedef enum
    {
        GM_RSSP1_Pri_Type_SFM_Data_req = 0x01,
        GM_RSSP1_Pri_Type_SFM_U2L_Unknow = 0x02
    } GM_RSSP1_SFM_U2L_pri_type_enum;

    typedef enum
    {
        GM_RSSP1_SFM_Data_Ind              = 0x1111,
        GM_RSSP1_SFM_Connection_State_Indi = 0x2222,
        GM_RSSP1_SFM_Warning_Indi          = 0x3333,
        GM_RSSP1_SFM_L2U_unknow            = 0xFFFF
    } GM_RSSP1_SFM_L2U_type_enum;

    /** ����Ӧ�ò�����ݷ�������ԭ�� */

    typedef struct
    {
        GM_UINT8               sys_A_or_B;                     /**< AB����ʶ */
        GM_UINT8               active_or_standby;              /**< ������ʶ */
        GM_UINT16              bytes_count;                    /**< Ҫ���͵��ֽ���*/
        GM_UINT8               byte[GM_RSSP1_MAX_USER_DAT_LEN];    /**< Ҫ���͵���������*/
    } GM_PACKED GM_RSSP1_SFM_U2L_dat_pri_struct;

    /** ��Ӧ�ò㱨����յ������� */

    typedef struct
    {
        GM_UINT16              bytes_count;                    /**< �յ����ֽ���*/
        GM_UINT8               byte[GM_RSSP1_MAX_USER_DAT_LEN];    /**< �յ�����������*/
    } GM_PACKED GM_RSSP1_SFM_L2U_dat_pri_struct;

    /** ��Ӧ�ò㱨�����FSFB��ȫ�����Լ���ײ��UDPͨ����� */

    typedef struct
    {
        GM_UINT16         connection_num;                         /**< ������ */

        struct GM_RSSP1_SFM_Connection_State_Report
        {
            GM_RSSP1_SACEPID_struct     sacepid;
            GM_UINT32             state;                          /**< ÿ�����ӵ�����״̬��4���ֽڱ�ʾ��λ��Ӹߵ��ͻ���Ϊ��index:8 , state:4(0xf:connected,0x0:free) , udp chn num:4(max udp chn= 16) , udp chn state:16 */
        } GM_PACKED connection_states[GM_RSSP1_MAX_SAFETY_CONNECTION_NUM];
    } GM_PACKED GM_RSSP1_SFM_L2U_connection_state_pri_struct;

    /** ��Ӧ�ò㱨�����FSFB��ȫ���ӳ��ֵı�����Ϣ */

    typedef struct
    {
        GM_UINT8                      type;               /**< ��������:MD5У��������ա�����SSE��SSR������RSDУ�����ȱ�����Ϣ */
        GM_UINT8                 index;               /**< ͨ���±��������ӣ��Լ�����SDMͨ��ʱ����������SDM�������ļ�ƥ�伴�� */
        GM_RSSP1_SACEPID_struct             SaCEPID;
    } GM_PACKED GM_RSSP1_SFM_L2U_warning_pri_struct;

    typedef struct
    {
        GM_RSSP1_SFM_U2L_pri_type_enum      type;
        GM_RSSP1_SACEPID_struct             SaCEPID;            /**< ��ȫ����ID */

        union
        {
            GM_RSSP1_SFM_U2L_dat_pri_struct data_req;           /**< ���Ͱ�ȫ���ݰ� */
        } GM_PACKED as;
    } GM_PACKED GM_RSSP1_SFM_U2L_pri_struct;

    typedef struct
    {
        GM_RSSP1_SFM_L2U_type_enum          type;
        GM_RSSP1_SACEPID_struct             SaCEPID;            /**< ��ȫ����ID */

        union
        {
            GM_RSSP1_SFM_L2U_dat_pri_struct                 data_indi;          /**< ���յ��İ�ȫ���ݰ� */
            GM_RSSP1_SFM_L2U_connection_state_pri_struct    connection_state;  /* ����״̬.ʹ�ô˽ṹʱ����Ϊ���������ӵ�״̬����װ���������ʹ��sacepid */
            GM_RSSP1_SFM_L2U_warning_pri_struct             warning;
        } GM_PACKED as;
    } GM_PACKED GM_RSSP1_SFM_L2U_pri_struct;


    /************* SFM ���á��������ļ����룬���ڳ�ʼ��SFM **********/
    /** ��ȫ��һ�����ӵ�FSFB�ؼ���ȫ�������� */

    /** һ��FSFB��ȫͨ���������������塣FSFBĬ��Ϊ˫ͨ��У�顣 */

    typedef struct
    {
        GM_UINT32                          local_sid;          /**< �����豸Դ��ʶ�� */
        GM_UINT32                          local_sinit;        /**< �����豸���г�ʼ������ */
        GM_UINT32                          local_dataVer;      /**< �����豸Ӧ��ظ�����SID������Ϣ */
        GM_UINT32                          local_sys_chk;              /**< ϵͳУ���� */

        GM_UINT32                          remote_sid;         /**< Զ���豸Դ��ʶ�� */
        GM_UINT32                          remote_sinit;       /**< Զ���豸���г�ʼ������ */
        GM_UINT32                          remote_dataVer;     /**< Զ���豸Ӧ��ظ�����SID������Ϣ */

        GM_UINT32                          *pLFSR_left_table;
        GM_UINT32                          *pLFSR_right_table;
        GM_UINT32                          *pCRC32_table;
        GM_UINT16                          *pCRC16_table;      /**< ϵͳ��ֻ��һ��CRC16������chn��ͬ */

    } GM_PACKED GM_RSSP1_SFM_fsfb_chn_cfg_struct;

    /** һ��FSFB��ȫģ�鱾�ذ�ȫ�����ṹ���塣 */

    typedef struct
    {
        GM_UINT32                          local_sid;          /**< �����豸Դ��ʶ�� */
        GM_UINT32                          local_sinit;        /**< �����豸���г�ʼ������ */
        GM_UINT32                          local_dataVer;      /**< �����豸Ӧ��ظ�����SID������Ϣ */
        GM_UINT32                          local_sys_chk;            /**< ϵͳУ���� */
    } GM_PACKED GM_RSSP1_SFM_fsfb_local_para_cfg_struct;

    /** ��ȫ��һ�����ӵĲ������ã��������ļ����� */

    typedef struct
    {
        GM_UINT16                         deltaTime;             /**< Ĭ�Ϲ涨 RSD ֡�Ŀ�ͬ�����̵����ʱ��ƫ��������.����Ϊ 2 �루��ϵͳ����Ϊ250ms����������Ϊ0x08������ʱ������������ͬ��Уʱ���� */
        GM_UINT16                         lifeTime;              /**< Ĭ�Ϲ涨��ȫ����ֵ����Ч����������������ʱ��Ϊ 3 �루��ϵͳ����Ϊ 250ms����������Ϊ0x0C������ʱ���轫��ȫ����λ����ȫֵ��0�� */
        GM_UINT8                          num_data_ver;          /**< ��ȫͨ��ʱ��У��SSR���ݵİ汾��.RSSP1 spe 2.2.2.1.3.3 */
        GM_UINT16                         torlerate_cycle_cfg;   /**< ��ˡ���ڣ�N����������δ�յ�RSD���ݣ���FSFB������δ�Ͽ�������һ����Ч���������ϲ㡣 */
        GM_UINT16                         dest_addr;             /**< Ŀ�ĵ�ַ��Ĭ�ϲ����豸��� */

        GM_RSSP1_SFM_fsfb_chn_cfg_struct        fsfb_chn_cfg[GM_RSSP1_CHECK_CHN_NUM];  /**< FSFB˫ͨ��У��������� */

        GM_BOOL                           b_enable_FSFB_on_chn;   /**< ��Ե��豸����UDPͨ����ʹ�ö�����FSFB�����ú��ϲ�ȡ���ݵķ�ʽ������ͬ */
        GM_UINT32                        Chn_apply_FSFB_ID;      /**< ����UDPͨ��ʹ�ö�����FSFBʱ����ID��ͬ�ĸ�FSFB������ʵ����ͬһ��Ӧ�ò㣬�ɺϲ��������ϲ���ȡ���ݡ� */
        GM_UINT32                         L2U_dat_Q_size;             /**< ����ȫ�������յ����ѽ��������ݰ� */
        GM_UINT32                         L2U_dat_Q_offset;

    } GM_PACKED GM_RSSP1_SFM_connection_cfg_struct;

    typedef struct
    {
        GM_UINT16                         source_addr;        /**< �����豸Դ��ַ��Ĭ�ϲ����豸��� */
        GM_RSSP1_SFM_fsfb_local_para_cfg_struct local_cfg[GM_RSSP1_CHECK_CHN_NUM];

        GM_UINT16                         connection_nums;    /* ��CFM�е�����һһ��Ӧ */
        GM_RSSP1_SFM_connection_cfg_struct      connection_cfg[GM_RSSP1_MAX_SAFETY_CONNECTION_NUM];

        GM_UINT32                         U2L_pri_Q_size;
        GM_UINT32                         U2L_pri_Q_offset;
        GM_UINT32                         L2U_pri_Q_size;
        GM_UINT32                         L2U_pri_Q_offset;

    } GM_PACKED GM_RSSP1_SFM_cfg_struct;



    /****************************************************************************/
    /*****                       FSFB CFM                       *****/
    /****************************************************************************/

    typedef enum
    {
        GM_RSSP1_CFM_Data_req = 0x01,
        GM_RSSP1_CFM_U2L_Unknow = 0x02
    } GM_RSSP1_CFM_U2L_pri_type_enum;

    typedef enum
    {
        GM_RSSP1_CFM_Data_Ind = 0x01,              /**< CFM���յ������� */
        GM_RSSP1_CFM_Indi_com_State = 0x02,        /**< CFM����״̬ */
        GM_RSSP1_CFM_Indi_Error_Noti = 0x03,       /**< CFM�����Ĵ��� */
        GM_RSSP1_CFM_L2U_Unknow = 0x04
    } GM_RSSP1_CFM_L2U_type_enum;

    /** �����ϲ�����ݷ�������ԭ�� */

    typedef struct
    {
        GM_RSSP1_Msg_Type_enum      type;                           /**< ���ݰ����� */
        GM_UINT32             TC;                             /**< ���ڼ���������CFMʶ���յ��ļ��������Ƿ����ڰ�ȫ��ͬһ���ڣ������Ƿ���Ҫ��װ���͡� */
        GM_UINT16             bytes_count;                    /**< Ҫ���͵��ֽ���*/
        GM_UINT8              byte[GM_RSSP1_MAX_SAFETY_DAT_LEN];  /**< Ҫ���͵���������*/
    } GM_PACKED GM_RSSP1_CFM_U2L_Dat_pri_struct;

    /** �����ϲ��SSE��������ԭ��.����CRSCD�������ʱ�ݴ档��ֹʹ��ͨ�����ݰ����¶�ջ��� */

    typedef struct
    {
        GM_RSSP1_Msg_Type_enum      type;                           /**< ���ݰ����� */
        GM_UINT32             TC;                             /**< ���ڼ���������CFMʶ���յ��ļ��������Ƿ����ڰ�ȫ��ͬһ���ڣ������Ƿ���Ҫ��װ���͡� */
        GM_UINT16             bytes_count;                    /**< Ҫ���͵��ֽ���*/
        GM_UINT8              byte[RSSP1_SSE_FRAME_LEN_WITH_CRC];  /**< Ҫ���͵���������*/
    } GM_PACKED GM_RSSP1_CFM_U2L_Dat_SSE_pri_struct;

    /** �����ϲ��SSR��������ԭ�����CRSCD�������ʱ�ݴ档��ֹʹ��ͨ�����ݰ����¶�ջ��� */

    typedef struct
    {
        GM_RSSP1_Msg_Type_enum      type;                           /**< ���ݰ����� */
        GM_UINT32             TC;                             /**< ���ڼ���������CFMʶ���յ��ļ��������Ƿ����ڰ�ȫ��ͬһ���ڣ������Ƿ���Ҫ��װ���͡� */
        GM_UINT16             bytes_count;                    /**< Ҫ���͵��ֽ���*/
        GM_UINT8              byte[RSSP1_SSR_FRAME_LEN_WITH_CRC];  /**< Ҫ���͵���������*/
    } GM_PACKED GM_RSSP1_CFM_U2L_Dat_SSR_pri_struct;

    /** ���ϲ㱨����յ������� */

    typedef struct
    {
        GM_UINT16              bytes_count;                    /**< �յ����ֽ���*/
        GM_UINT8               byte[GM_RSSP1_MAX_SAFETY_DAT_LEN];  /**< �յ�����������*/
    } GM_PACKED GM_RSSP1_CFM_L2U_Dat_pri_struct;

    /** ���ϲ㱨��CFM��UDP����״̬ */

    typedef struct
    {
        struct _GM_RSSP1_CFM_L2U_State_Noti_struct_
        {
            GM_BOOL           b_is_AS_module;
            GM_UINT8     index;                  /**< CFM �����±꣬��SFM�������±��Ӧ */
            GM_UINT8          chn_num;                /**< UDPͨ���������ϲ�SFMʹ�� */
            GM_UINT8          channel_state;              /**< ��ͨ��״̬��һ��bit�ɱ�ʾһ��ͨ����״̬�����ɱ�ʾ16��UDPͨ�� */
        }GM_PACKED GM_RSSP1_CFM_Channel_states[GM_RSSP1_MAX_SAFETY_CONNECTION_NUM];
    }GM_PACKED GM_RSSP1_CFM_L2U_State_Noti_struct;

    /** ���ϲ㱨��CFM�����Ĵ��� */

    typedef struct
    {
        GM_UINT32     reason;
        GM_UINT32     sub_reason;
    } GM_PACKED GM_RSSP1_CFM_L2U_Error_Noti_struct;


    typedef struct
    {
        GM_RSSP1_CFM_U2L_pri_type_enum      type;
        GM_UINT8                 index;              /**< �����±�� */

        union
        {
            GM_RSSP1_CFM_U2L_Dat_pri_struct data_req;           /**< ���Ͱ�ȫ���ݰ� */
        } GM_PACKED as;
    } GM_PACKED GM_RSSP1_CFM_U2L_pri_struct;

    typedef struct
    {
        GM_RSSP1_CFM_L2U_type_enum          type;
        GM_UINT8                 index;              /**<  �����±�� */

        union
        {
            GM_RSSP1_CFM_L2U_Dat_pri_struct         data_indi;          /**< ���յ��İ�ȫ���ݰ� */
            GM_RSSP1_CFM_L2U_State_Noti_struct  channel_state_indi;     /**< UDPͨ��״̬��unionʹ�ô˽ṹʱ��ʹ��index��Ĭ����Ϊ0 */
            GM_RSSP1_CFM_L2U_Error_Noti_struct      error_indi;         /**< ���� */
        }GM_PACKED as;
    }GM_PACKED GM_RSSP1_CFM_L2U_pri_struct;


    /* FSFB CFM ͨ�����ݰ����� */
    /**���ݰ��ṹ */

    typedef struct
    {
        GM_UINT16              bytes_count;                    /**< Ҫ���͵��ֽ���*/
        GM_UINT8               byte[GM_RSSP1_MAX_SAFETY_DAT_LEN];     /**< Ҫ���͵���������*/
    } GM_PACKED GM_RSSP1_com_pri_struct;

    /************* CFM ���á��������ļ����룬���ڳ�ʼ��CFM **********/

    typedef struct
    {
        GM_UINT32                     loc_ip;
        GM_UINT32                     rem_ip;
        GM_UINT32                     loc_port;
        GM_UINT32                     rem_port;
        GM_UINT32                     send_Q_size;
        GM_UINT32                     send_Q_offset;
        GM_UINT32                     recv_Q_size;
        GM_UINT32                     recv_Q_offset;
    } GM_PACKED GM_RSSP1_CFM_UDP_chn_cfg_struct;
		    
	typedef struct
	{
		GM_UINT32                     com_port_no;               /**< ���ں� */
		GM_UINT32                     send_Q_size;
		GM_UINT32                     send_Q_offset;
		GM_UINT32                     recv_Q_size;
		GM_UINT32                     recv_Q_offset;
	}GM_PACKED GM_RSSP1_CFM_SCOM_chn_cfg_struct;

    typedef struct
    {
        GM_BOOL                        b_enable_CRSCD_pack;    /**< ʹ��ͨ�����ԺTCC�������.�����һ����һ������ */
		GM_BOOL                        b_enable_FSFB_on_chn;/**< ��Ե��豸����UDPͨ����ʹ�ö�����FSFB�����ú��ϲ�ȡ���ݵķ�ʽ������ͬ������ͬһ���豸�ĸ�UDPͨ����FSFB���ӣ�CTCS-ID������ͬ!�ϲ���ȡ��һ�����ӵ����ݺ󣬽��������������ͬ�������е�L2U_dat_Q */
        GM_UINT16                     dest_addr;             /**< Ŀ�ĵ�ַ��Ĭ�ϲ����豸��� */

        GM_RSSP1_CFM_Com_Type_Enum          com_type;
        
        GM_UINT16                      chn_num;
        GM_RSSP1_CFM_UDP_chn_cfg_struct      UDP_chn_cfg[GM_RSSP1_CFM_MAX_CHANNEL_NUM];

        GM_RSSP1_CFM_SCOM_chn_cfg_struct        scom_chn_cfg[GM_RSSP1_CFM_MAX_CHANNEL_NUM];
    }GM_PACKED GM_RSSP1_CFM_connection_cfg_struct;

    /** �������� */
    typedef struct
    {
		GM_UINT16                     source_addr;
        GM_UINT16                     connection_nums;    /* ��SFM�е�����һһ��Ӧ */
        GM_RSSP1_CFM_connection_cfg_struct  connection_cfg[GM_RSSP1_MAX_SAFETY_CONNECTION_NUM];
        GM_UINT32                     U2L_pri_Q_size;
        GM_UINT32                     U2L_pri_Q_offset;   /**< ����ҪΪ���з�����ֽ��� = U2L_pri_Q_size * sizeof(GM_RSSP1_SFM_U2L_pri_struct) */
        GM_UINT32                     L2U_pri_Q_size;
        GM_UINT32                     L2U_pri_Q_offset;   /**< ����ҪΪ���з�����ֽ��� = L2U_pri_Q_size * sizeof(GM_RSSP1_SFM_L2U_pri_struct) */
    } GM_PACKED GM_RSSP1_CFM_cfg_struct;
    /** brief UDP���ݴ����������ýṹ�壬������ݴ����������շ�����
    * @warning ǰ��:SFM��CFMģ���Ѿ�Initialise_OK, ��ͨ����ʼ״̬Ϊ������\n
    ���ܽ����������������±��.�����ж�ͨ�������ú�ֱ�Ӻ���.
    */

    /************* FSFBͨ��ģ���ȫ�����á��������ļ����룬���ڳ�ʼ��SFM��CFM **********/

    typedef struct
    {
#ifdef SFM_Part
		GM_RSSP1_SFM_cfg_struct             SFM_cfg;
#endif
#ifdef CFM_Part
		GM_RSSP1_CFM_cfg_struct             CFM_cfg;
#endif
#ifdef LINK_Part
		FSFB_LNK_cfg_struct				LNK_cfg;
#endif
    } GM_PACKED GM_RSSP1_comm_cfg_struct;

#ifdef __cplusplus
}
#endif

#endif

