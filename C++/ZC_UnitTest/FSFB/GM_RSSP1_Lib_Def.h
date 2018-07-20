/**
* @file GM_RSSP1_Lib_Def.h
* @brief FSFB模块及其配置的定义
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
/* FSFB SFM，CFM模块定义                               */
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


		/** 报警信息 : MD5校验出错、接收、发送SSE、SSR报警、RSD校验出错等报警信息 */
	#define GM_RSSP1_SFM_WARNING_TYPE_SEND_DAT_SAFE_CHECKSUM_ERR        0    /**< 发送的数据在接口交换过程中，校验出错 */
	#define GM_RSSP1_SFM_WARNING_TYPE_RECV_DAT_SAFE_CHECKSUM_ERR        1    /**< 接收的数据在接口交换过程中，校验出错 */
	#define GM_RSSP1_SFM_WARNING_TYPE_FSFB_CRCM_CHECK_ERR               2
	#define GM_RSSP1_SFM_WARNING_TYPE_RECV_SSE                          3
	#define GM_RSSP1_SFM_WARNING_TYPE_RECV_SSR                          4
	#define GM_RSSP1_SFM_WARNING_TYPE_SSE_BUILD_ERR                     5
	#define GM_RSSP1_SFM_WARNING_TYPE_RCVD_SSE_CRC_ERROR                6
	#define GM_RSSP1_SFM_WARNING_TYPE_RCVD_SSR_CRC_ERROR                7
	#define GM_RSSP1_SFM_WARNING_TYPE_RCVD_RSD_CRC_ERROR                8
	#define GM_RSSP1_SFM_WARNING_TYPE_RCVD_UNKNOW_TYPE_FRAME            9    /**< 收到未知类型数据帧 */
	#define GM_RSSP1_SFM_WARNING_TYPE_RECV_NO_RSD_IN_DELTATIME          10   /**< deltatime内未收到RSD */

		/** 状态报告中各种值的设定。属于与应用层(VLE)接口数据帧格式定义内容，需要与VLE端保持一致 */
	#define GM_RSSP1_REPORT_STATE_TO_APP_FSFB_OK        (0xf)
	#define GM_RSSP1_REPORT_STATE_TO_APP_FSFB_FAIL      (0x0)
	#define GM_RSSP1_REPORT_STATE_TO_APP_REMOTE_ACTIVE  (0xf)
	#define GM_RSSP1_REPORT_STATE_TO_APP_REMOTE_STANDBY (0x0)
	#define GM_RSSP1_REPORT_STATE_TO_APP_REMOTE_UNKOWN  (0xc)


    /** 应用层数据来自A机还是B机 */
    typedef enum
    {
        GM_RSSP1_Local_Sys_A = 0x80,      /**< A机发送的数据 */
        GM_RSSP1_Local_Sys_B = 0x81,      /**< B机发送的数据 */
        GM_RSSP1_Local_Sys_UNLOWN = 0
	} Local_Sys_AB_enum;

    /** 远程设备是A机还是B机 */
    typedef enum
    {
        GM_RSSP1_Remote_Dev_Active  = 0x80,      /**< 收到的是对方主机发送的数据 */
        GM_RSSP1_Remote_DEV_Standby = 0x81,      /**< 收到的是对方备机发送的数据 */
        GM_RSSP1_Remote_DEV_Unknow  = 0xff       /**< 状态未知，常出现在没有收到对方RSD之前 */
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
        GM_RSSP1_Layer_State_Unknow        = 9999,         /**< 未知状态, 不可用, 必须经过初始化 */
        GM_RSSP1_Layer_State_Free          = 0,            /**< 经过初始化后的状态, 可进行下一步操作 */
        GM_RSSP1_Layer_State_Connecting    = 2222,         /**< 正在连接 */
        GM_RSSP1_Layer_State_Connected     = 3333,         /**< 已连接, 可为上层提供服务 */
        GM_RSSP1_Layer_State_Disconnecting = 4444          /**< 正在断开连接 */
    } GM_RSSP1_connection_state_enum;

    typedef enum
    {
        GM_RSSP1_Lib_State_Unknown     = 1010, /* 未初始化 */
        GM_RSSP1_Lib_State_Operational = 1030, /* 成功初始化 */
        GM_RSSP1_Lib_State_Failure     = 1040  /* 失效 */
    } GM_RSSP1_library_state_enum;


	typedef enum
	{
		GM_RSSP1_CFM_COMM_TYPE_UDP           = 0x1111, /* 底层采用udp通信 */
		GM_RSSP1_CFM_COMM_TYPE_SCOM           = 0x2222, /* 底层采用串口通信 */
	    
		GM_RSSP1_CFM_COMM_TYPE_UNKNOW           = 0xffff /* 底层采用串口通信 */
	} GM_RSSP1_CFM_Com_Type_Enum;
	/*typedef GM_RSSP1_CFM_Com_Type_Enum FSFB_LNK_Com_Type_Enum;*/


    /**SaCEPID结构, 用于区分每个安全连接终端。TODO:必须唯一确定，需要增加信息 */

    typedef struct
    {
        GM_UINT16        source_addr;     /**< 源地址 */
        GM_UINT16        dest_addr;       /**< 目的地址 */
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

    /** 来自应用层的数据发送请求原语 */

    typedef struct
    {
        GM_UINT8               sys_A_or_B;                     /**< AB机标识 */
        GM_UINT8               active_or_standby;              /**< 主机标识 */
        GM_UINT16              bytes_count;                    /**< 要发送的字节数*/
        GM_UINT8               byte[GM_RSSP1_MAX_USER_DAT_LEN];    /**< 要发送的数据内容*/
    } GM_PACKED GM_RSSP1_SFM_U2L_dat_pri_struct;

    /** 向应用层报告接收到的数据 */

    typedef struct
    {
        GM_UINT16              bytes_count;                    /**< 收到的字节数*/
        GM_UINT8               byte[GM_RSSP1_MAX_USER_DAT_LEN];    /**< 收到的数据内容*/
    } GM_PACKED GM_RSSP1_SFM_L2U_dat_pri_struct;

    /** 向应用层报告各个FSFB安全连接以及其底层的UDP通断情况 */

    typedef struct
    {
        GM_UINT16         connection_num;                         /**< 连接数 */

        struct GM_RSSP1_SFM_Connection_State_Report
        {
            GM_RSSP1_SACEPID_struct     sacepid;
            GM_UINT32             state;                          /**< 每个连接的所有状态用4个字节表示，位域从高到低划分为：index:8 , state:4(0xf:connected,0x0:free) , udp chn num:4(max udp chn= 16) , udp chn state:16 */
        } GM_PACKED connection_states[GM_RSSP1_MAX_SAFETY_CONNECTION_NUM];
    } GM_PACKED GM_RSSP1_SFM_L2U_connection_state_pri_struct;

    /** 向应用层报告各个FSFB安全连接出现的报警信息 */

    typedef struct
    {
        GM_UINT8                      type;               /**< 报警类型:MD5校验出错、接收、发送SSE、SSR报警、RSD校验出错等报警信息 */
        GM_UINT8                 index;               /**< 通过下标区分连接，以减少与SDM通信时的数据量，SDM与配置文件匹配即可 */
        GM_RSSP1_SACEPID_struct             SaCEPID;
    } GM_PACKED GM_RSSP1_SFM_L2U_warning_pri_struct;

    typedef struct
    {
        GM_RSSP1_SFM_U2L_pri_type_enum      type;
        GM_RSSP1_SACEPID_struct             SaCEPID;            /**< 安全连接ID */

        union
        {
            GM_RSSP1_SFM_U2L_dat_pri_struct data_req;           /**< 发送安全数据包 */
        } GM_PACKED as;
    } GM_PACKED GM_RSSP1_SFM_U2L_pri_struct;

    typedef struct
    {
        GM_RSSP1_SFM_L2U_type_enum          type;
        GM_RSSP1_SACEPID_struct             SaCEPID;            /**< 安全连接ID */

        union
        {
            GM_RSSP1_SFM_L2U_dat_pri_struct                 data_indi;          /**< 接收到的安全数据包 */
            GM_RSSP1_SFM_L2U_connection_state_pri_struct    connection_state;  /* 连接状态.使用此结构时，因为将所有连接的状态都封装在这里，不再使用sacepid */
            GM_RSSP1_SFM_L2U_warning_pri_struct             warning;
        } GM_PACKED as;
    } GM_PACKED GM_RSSP1_SFM_L2U_pri_struct;


    /************* SFM 配置。由配置文件读入，用于初始化SFM **********/
    /** 安全层一个连接的FSFB关键安全参数配置 */

    /** 一个FSFB安全通道参数及变量定义。FSFB默认为双通道校验。 */

    typedef struct
    {
        GM_UINT32                          local_sid;          /**< 本地设备源标识符 */
        GM_UINT32                          local_sinit;        /**< 本地设备序列初始化常量 */
        GM_UINT32                          local_dataVer;      /**< 本地设备应答回复方的SID掩码信息 */
        GM_UINT32                          local_sys_chk;              /**< 系统校核字 */

        GM_UINT32                          remote_sid;         /**< 远程设备源标识符 */
        GM_UINT32                          remote_sinit;       /**< 远程设备序列初始化常量 */
        GM_UINT32                          remote_dataVer;     /**< 远程设备应答回复方的SID掩码信息 */

        GM_UINT32                          *pLFSR_left_table;
        GM_UINT32                          *pLFSR_right_table;
        GM_UINT32                          *pCRC32_table;
        GM_UINT16                          *pCRC16_table;      /**< 系统中只有一个CRC16表。两个chn相同 */

    } GM_PACKED GM_RSSP1_SFM_fsfb_chn_cfg_struct;

    /** 一个FSFB安全模块本地安全参数结构定义。 */

    typedef struct
    {
        GM_UINT32                          local_sid;          /**< 本地设备源标识符 */
        GM_UINT32                          local_sinit;        /**< 本地设备序列初始化常量 */
        GM_UINT32                          local_dataVer;      /**< 本地设备应答回复方的SID掩码信息 */
        GM_UINT32                          local_sys_chk;            /**< 系统校核字 */
    } GM_PACKED GM_RSSP1_SFM_fsfb_local_para_cfg_struct;

    /** 安全层一个连接的参数配置，由配置文件读入 */

    typedef struct
    {
        GM_UINT16                         deltaTime;             /**< 默认规定 RSD 帧的可同步容忍的最大时序偏差周期数.例如为 2 秒（若系统周期为250ms，则周期数为0x08），超时后需启动请求同步校时机制 */
        GM_UINT16                         lifeTime;              /**< 默认规定安全数据值的有效保持周期数。例如时间为 3 秒（若系统周期为 250ms，则周期数为0x0C），超时后需将安全数据位导向安全值“0” */
        GM_UINT8                          num_data_ver;          /**< 安全通信时序校验SSR数据的版本号.RSSP1 spe 2.2.2.1.3.3 */
        GM_UINT16                         torlerate_cycle_cfg;   /**< 宽恕周期：N个主周期内未收到RSD数据，但FSFB连接尚未断开，则将上一次有效数据送往上层。 */
        GM_UINT16                         dest_addr;             /**< 目的地址。默认采用设备编号 */

        GM_RSSP1_SFM_fsfb_chn_cfg_struct        fsfb_chn_cfg[GM_RSSP1_CHECK_CHN_NUM];  /**< FSFB双通道校验参数配置 */

        GM_BOOL                           b_enable_FSFB_on_chn;   /**< 与对等设备各个UDP通道均使用独立的FSFB。启用后，上层取数据的方式有所不同 */
        GM_UINT32                        Chn_apply_FSFB_ID;      /**< 启用UDP通道使用独立的FSFB时，此ID相同的各FSFB连接其实属于同一个应用层，可合并，用于上层提取数据。 */
        GM_UINT32                         L2U_dat_Q_size;             /**< 本安全连接内收到的已解析的数据包 */
        GM_UINT32                         L2U_dat_Q_offset;

    } GM_PACKED GM_RSSP1_SFM_connection_cfg_struct;

    typedef struct
    {
        GM_UINT16                         source_addr;        /**< 本地设备源地址。默认采用设备编号 */
        GM_RSSP1_SFM_fsfb_local_para_cfg_struct local_cfg[GM_RSSP1_CHECK_CHN_NUM];

        GM_UINT16                         connection_nums;    /* 与CFM中的连接一一对应 */
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
        GM_RSSP1_CFM_Data_Ind = 0x01,              /**< CFM接收到的数据 */
        GM_RSSP1_CFM_Indi_com_State = 0x02,        /**< CFM连接状态 */
        GM_RSSP1_CFM_Indi_Error_Noti = 0x03,       /**< CFM产生的错误 */
        GM_RSSP1_CFM_L2U_Unknow = 0x04
    } GM_RSSP1_CFM_L2U_type_enum;

    /** 来自上层的数据发送请求原语 */

    typedef struct
    {
        GM_RSSP1_Msg_Type_enum      type;                           /**< 数据包类型 */
        GM_UINT32             TC;                             /**< 周期计数。用于CFM识别收到的几包数据是否属于安全层同一周期，决定是否需要组装后发送。 */
        GM_UINT16             bytes_count;                    /**< 要发送的字节数*/
        GM_UINT8              byte[GM_RSSP1_MAX_SAFETY_DAT_LEN];  /**< 要发送的数据内容*/
    } GM_PACKED GM_RSSP1_CFM_U2L_Dat_pri_struct;

    /** 来自上层的SSE发送请求原语.用于CRSCD组包方案时暂存。防止使用通用数据包导致堆栈溢出 */

    typedef struct
    {
        GM_RSSP1_Msg_Type_enum      type;                           /**< 数据包类型 */
        GM_UINT32             TC;                             /**< 周期计数。用于CFM识别收到的几包数据是否属于安全层同一周期，决定是否需要组装后发送。 */
        GM_UINT16             bytes_count;                    /**< 要发送的字节数*/
        GM_UINT8              byte[RSSP1_SSE_FRAME_LEN_WITH_CRC];  /**< 要发送的数据内容*/
    } GM_PACKED GM_RSSP1_CFM_U2L_Dat_SSE_pri_struct;

    /** 来自上层的SSR发送请求原语。用于CRSCD组包方案时暂存。防止使用通用数据包导致堆栈溢出 */

    typedef struct
    {
        GM_RSSP1_Msg_Type_enum      type;                           /**< 数据包类型 */
        GM_UINT32             TC;                             /**< 周期计数。用于CFM识别收到的几包数据是否属于安全层同一周期，决定是否需要组装后发送。 */
        GM_UINT16             bytes_count;                    /**< 要发送的字节数*/
        GM_UINT8              byte[RSSP1_SSR_FRAME_LEN_WITH_CRC];  /**< 要发送的数据内容*/
    } GM_PACKED GM_RSSP1_CFM_U2L_Dat_SSR_pri_struct;

    /** 向上层报告接收到的数据 */

    typedef struct
    {
        GM_UINT16              bytes_count;                    /**< 收到的字节数*/
        GM_UINT8               byte[GM_RSSP1_MAX_SAFETY_DAT_LEN];  /**< 收到的数据内容*/
    } GM_PACKED GM_RSSP1_CFM_L2U_Dat_pri_struct;

    /** 向上层报告CFM的UDP连接状态 */

    typedef struct
    {
        struct _GM_RSSP1_CFM_L2U_State_Noti_struct_
        {
            GM_BOOL           b_is_AS_module;
            GM_UINT8     index;                  /**< CFM 连接下标，与SFM中连接下标对应 */
            GM_UINT8          chn_num;                /**< UDP通道数，由上层SFM使用 */
            GM_UINT8          channel_state;              /**< 各通道状态，一个bit可表示一个通道的状态，最大可表示16个UDP通道 */
        }GM_PACKED GM_RSSP1_CFM_Channel_states[GM_RSSP1_MAX_SAFETY_CONNECTION_NUM];
    }GM_PACKED GM_RSSP1_CFM_L2U_State_Noti_struct;

    /** 向上层报告CFM发生的错误 */

    typedef struct
    {
        GM_UINT32     reason;
        GM_UINT32     sub_reason;
    } GM_PACKED GM_RSSP1_CFM_L2U_Error_Noti_struct;


    typedef struct
    {
        GM_RSSP1_CFM_U2L_pri_type_enum      type;
        GM_UINT8                 index;              /**< 连接下标号 */

        union
        {
            GM_RSSP1_CFM_U2L_Dat_pri_struct data_req;           /**< 发送安全数据包 */
        } GM_PACKED as;
    } GM_PACKED GM_RSSP1_CFM_U2L_pri_struct;

    typedef struct
    {
        GM_RSSP1_CFM_L2U_type_enum          type;
        GM_UINT8                 index;              /**<  连接下标号 */

        union
        {
            GM_RSSP1_CFM_L2U_Dat_pri_struct         data_indi;          /**< 接收到的安全数据包 */
            GM_RSSP1_CFM_L2U_State_Noti_struct  channel_state_indi;     /**< UDP通道状态，union使用此结构时不使用index，默认置为0 */
            GM_RSSP1_CFM_L2U_Error_Noti_struct      error_indi;         /**< 错误 */
        }GM_PACKED as;
    }GM_PACKED GM_RSSP1_CFM_L2U_pri_struct;


    /* FSFB CFM 通信数据包定义 */
    /**数据包结构 */

    typedef struct
    {
        GM_UINT16              bytes_count;                    /**< 要发送的字节数*/
        GM_UINT8               byte[GM_RSSP1_MAX_SAFETY_DAT_LEN];     /**< 要发送的数据内容*/
    } GM_PACKED GM_RSSP1_com_pri_struct;

    /************* CFM 配置。由配置文件读入，用于初始化CFM **********/

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
		GM_UINT32                     com_port_no;               /**< 串口号 */
		GM_UINT32                     send_Q_size;
		GM_UINT32                     send_Q_offset;
		GM_UINT32                     recv_Q_size;
		GM_UINT32                     recv_Q_offset;
	}GM_PACKED GM_RSSP1_CFM_SCOM_chn_cfg_struct;

    typedef struct
    {
        GM_BOOL                        b_enable_CRSCD_pack;    /**< 使用通号设计院TCC组包方案.多包合一包、一包拆多包 */
		GM_BOOL                        b_enable_FSFB_on_chn;/**< 与对等设备各个UDP通道均使用独立的FSFB。启用后，上层取数据的方式有所不同：属于同一个设备的各UDP通道的FSFB连接，CTCS-ID必须相同!上层提取到一个连接的数据后，将根据清空其他相同的连接中的L2U_dat_Q */
        GM_UINT16                     dest_addr;             /**< 目的地址。默认采用设备编号 */

        GM_RSSP1_CFM_Com_Type_Enum          com_type;
        
        GM_UINT16                      chn_num;
        GM_RSSP1_CFM_UDP_chn_cfg_struct      UDP_chn_cfg[GM_RSSP1_CFM_MAX_CHANNEL_NUM];

        GM_RSSP1_CFM_SCOM_chn_cfg_struct        scom_chn_cfg[GM_RSSP1_CFM_MAX_CHANNEL_NUM];
    }GM_PACKED GM_RSSP1_CFM_connection_cfg_struct;

    /** 其他配置 */
    typedef struct
    {
		GM_UINT16                     source_addr;
        GM_UINT16                     connection_nums;    /* 与SFM中的连接一一对应 */
        GM_RSSP1_CFM_connection_cfg_struct  connection_cfg[GM_RSSP1_MAX_SAFETY_CONNECTION_NUM];
        GM_UINT32                     U2L_pri_Q_size;
        GM_UINT32                     U2L_pri_Q_offset;   /**< 共需要为队列分配的字节数 = U2L_pri_Q_size * sizeof(GM_RSSP1_SFM_U2L_pri_struct) */
        GM_UINT32                     L2U_pri_Q_size;
        GM_UINT32                     L2U_pri_Q_offset;   /**< 共需要为队列分配的字节数 = L2U_pri_Q_size * sizeof(GM_RSSP1_SFM_L2U_pri_struct) */
    } GM_PACKED GM_RSSP1_CFM_cfg_struct;
    /** brief UDP数据传输任务配置结构体，主任务据此启动网络收发任务
    * @warning 前提:SFM、CFM模块已经Initialise_OK, 各通道初始状态为不可用\n
    才能将任务和连接数组的下标绑定.任务判断通道不可用后直接忽略.
    */

    /************* FSFB通信模块的全局配置。由配置文件读入，用于初始化SFM、CFM **********/

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

