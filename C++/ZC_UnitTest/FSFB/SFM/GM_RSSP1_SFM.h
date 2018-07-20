/**
* @file GM_RSSP1_SFM.h
* @brief SFM模块结构定义、相关接口、处理函数定义
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
		GM_UINT32   local_TC;       /*最近收到数据包时自己计数器的数值*/
		GM_UINT32   remote_TC;      /*最近收到数据包时数据包中计数器数值*/
		GM_UINT32   sseTS;          /*发送SSE时自己的TS数值*/
		GM_UINT32   sseTC;          /*发送SSE时自己的TC数值*/
		GM_UINT32   dynamicKey;     /*sint+(sid^T(n))*/
		GM_UINT8   bSendSSE;       /*是否发送SSE 0x00表示未发送sse, 0xff表示发送了sse但未收到ssr*/
	} GM_PACKED GM_RSSP1_CHN_ENV;



    /** 应用层向SFM注入服务请求原语的结果 */
    typedef enum
    {
        GM_RSSP1_User_Put_Pri_OK                    = 10100, /*< 成功           */
        GM_RSSP1_User_Put_Pri_MQ_FULL               = 10112, /*< 成功，原语请求队列已满，有数据覆盖  */

        GM_RSSP1_User_Put_Pri_INVALID_U2L           = 10102, /*< pU2L为NULL, 或原语内容不正确 */
        GM_RSSP1_User_Put_Pri_LIB_NOT_OPERATIONAL   = 10104, /*< SFM未初始化    */
        GM_RSSP1_User_Put_Pri_INVALID_REQ_TYPE      = 10105, /*< pU2L->Type未知.*/
        GM_RSSP1_User_Put_Pri_INVALID_CONNECTION_ID = 10108  /*< id非法         */
    } GM_RSSP1_User_Put_Pri_To_SFM_Result_enum;

    /** 应用层获取SFM状态事件、数据报告原语的结果 */
    typedef enum
    {
        GM_RSSP1_User_Get_Pri_OK                    = 10200, /*< 成功 */
        GM_RSSP1_User_Get_Pri_UNAVAILABLE           = 10210, /*< 原语无效(类型未知, 数据长度超长等..) */
        GM_RSSP1_User_Get_Pri_INVALID_L2U           = 10230, /*< pL2U 为NULL. */
        GM_RSSP1_User_Get_Pri_LIB_NOT_OPERATIONAL   = 10240  /*< SFM未初始化. */
    } GM_RSSP1_User_Get_Pri_From_SFM_Result_enum;

    /** 一个FSFB通道结构定义 */

    typedef struct
    {
        GM_RSSP1_SFM_fsfb_chn_cfg_struct        chn_cfg;

        GM_UINT32                      PREC_SINIT[GM_RSSP1_MAX_DELTATIME_ARRAY_SIZE];
        GM_UINT32                      POST_RXDATA[GM_RSSP1_MAX_DELTATIME_ARRAY_SIZE];
        GM_UINT32                      PREC_FIRSTSINIT;

    } GM_PACKED GM_RSSP1_SFM_fsfb_chn_struct;

    /** 一个FSFB安全连接结构定义 */

    typedef struct
    {
        GM_UINT8                         index;
        GM_RSSP1_connection_state_enum              state;                  /**< 连接状态。判断通断的依据：FSFB失步/lifetime时间内仍没有获得校验成功的数据 */
        GM_RSSP1_Remote_Dev_AS_State_enum           remote_dev_AS_state;    /**< 如果收到RSD，根据RSD判断此FSFB连接对应的远程设备是主机还是备机 */
        GM_INT8                                     state_check_counter1;    /**< 连接检查周期计数 */
        GM_INT8                                     state_check_counter2;    /**< 连接检查周期计数.多计数器增加相异性 jianghongjun 20110825 safety enhancement*/

        GM_RSSP1_SACEPID_struct                     SaCEPID;                /**< 安全连接ID */
        GM_UINT16                             source_addr;            /**< 本地设备源地址。默认采用设备编号 */
        GM_UINT16                             dest_addr;              /**< 目的地址。默认采用设备编号 */
        GM_UINT16                             deltaTime;              /**< 默认规定 RSD 帧的可同步容忍的最大时序偏差周期数.例如为 2 秒（若系统周期为250ms，则周期数为0x08），超时后需启动请求同步校时机制 */
        GM_UINT16                             lifeTime;               /**< 默认规定安全数据值的有效保持周期数。例如时间为 3 秒（若系统周期为 250ms，则周期数为0x0C），超时后需将安全数据位导向安全值“0” */
        GM_UINT8                              num_data_ver;           /**< 安全通信时序校验SSR数据的版本号.RSSP1 spe 2.2.2.1.3.3 */

        GM_RSSP1_TIME                               time;                               /**< 时序相关变量管理，如TC等，由主任务周期驱动 */
        GM_RSSP1_SFM_fsfb_chn_struct                fsfb_chn[GM_RSSP1_CHECK_CHN_NUM];       /**< FSFB通道参数，包括从文件直接读入的参数以及经过计算后得到的参数 */
        GM_RSSP1_CHN_ENV                            env[GM_RSSP1_CHECK_CHN_NUM];            /**< 通道计算用相关变量 */

        GM_BOOL                               b_RSD_Already_Sent;               /**< 本周期已经发送过rsd,不能发超过一包rsd */

        GM_BOOL                               b_enable_FSFB_on_chn;   /**< 与对等设备各个UDP通道均使用独立的FSFB。启用后，上层取数据的方式有所不同：属于同一个设备的各UDP通道的FSFB连接，CTCS-ID必须相同!上层提取到一个连接的数据后，将根据清空其他相同的连接中的L2U_dat_Q */
        GM_UINT32                            Chn_apply_FSFB_ID;      /**< 启用UDP通道使用独立的FSFB时，此ID相同的各FSFB连接其实属于同一个应用层，可合并，用于上层提取数据。 */
        GM_RSSP1_Msg_Queue_struct                   L2U_dat_Q;                  /**< 本安全连接内收到的已解析的数据包.用于单个UDP也使用独立FSFB校验的情况 */
									
        GM_UINT16                             torlerate_cycle_cfg;        /**< 宽恕周期：N个主周期内未收到RSD数据，但FSFB连接尚未断开，则将上一次有效数据送往上层。 */
		GM_INT8                                     torlerate_cycle_count1;      /**< 宽恕计数。 */
        GM_INT8                                     torlerate_cycle_count2;      /**< 宽恕计数。增加计数器，jianghongjun 20110825 safety enhancement */
        GM_RSSP1_SFM_L2U_pri_struct                 last_valid_dat_pri;         /**< 上一次有效的数据包，用于宽恕 */
        GM_BOOL                               b_rcvd_new_dat_in_cycle;    /**< 本周期新收到了数据 */
        GM_BOOL                               b_torlerant_dat_valid;      /**< 宽恕的数据是否合法 */

    } GM_PACKED GM_RSSP1_SFM_connection_struct;

    /** 安全层模块定义 */

    typedef struct
    {
        GM_RSSP1_library_state_enum         lib_state;
        GM_UINT16                     source_addr;        /**< 本地设备源地址。默认采用设备编号 */
        GM_UINT32                     cycle_cout;
        GM_RSSP1_SFM_fsfb_local_para_cfg_struct local_cfg[GM_RSSP1_CHECK_CHN_NUM];

        GM_UINT16                     connection_nums;
        GM_RSSP1_SFM_connection_struct      connection[GM_RSSP1_MAX_SAFETY_CONNECTION_NUM];
    } GM_PACKED GM_RSSP1_SFM_object_struct;
	
	/**fulintai**/
	typedef enum
	{
		GM_RSSP1_SFM_Get_Pri_OK = 10200,  /*< 成功 */
		GM_RSSP1_SFM_Get_Pri_FAIL = 10240,  /*< CFM未初始化 */
		GM_RSSP1_SFM_Get_Pri_INVALID_L2U = 10250,  /*< pL2U=NULL*/
	} GM_RSSP1_SFM_Get_Pri_From_CFM_Result_enum;

	/**< SFM向CFM注入服务请求原语的结果 */
	typedef enum
	{
		GM_RSSP1_SFM_Put_Pri_OK                       = 10100, /*< 成功. */
		GM_RSSP1_SFM_Put_Pri_MQ_FULL                  = 10112, /*< 成功，原语请求队列已满，有数据覆盖 */

		GM_RSSP1_SFM_Put_Pri_INVALID_U2L              = 10102, /*< 原语无效, 为NULL. */
		GM_RSSP1_SFM_Put_Pri_LIB_NOT_OPERATIONAL      = 10104, /*< CFM未初始化. */
		GM_RSSP1_SFM_Put_Pri_INVALID_REQ_TYPE         = 10105, /*< 原语类型未知. */
		GM_RSSP1_SFM_Put_Pri_INVALID_CONNECTION_INDEX = 10108, /*< 原语中的通道下标非法. */
	} GM_RSSP1_SFM_Put_Pri_To_CFM_Result_enum;/**< SFM从CFM获取服务请求原语的结果 */

    /************************************************************************/
    /* 接口                                         */
    /************************************************************************/

    /**
    * @brief 获取本机是否是主机
    *
    * Detailed description.
    * @return GM_BOOL
    */
    GM_BOOL SYS_Is_Local_Sys_Active(void);

    /**
    * @brief 获取SFM模块
    *
    * Detailed description.
    * @return GM_RSSP1_SFM_object_struct*
    */
    GM_RSSP1_SFM_object_struct *GM_RSSP1_Get_SFM_Object(void);


    /**
    * @brief  初始化FSFB校验通道的离线参数
    *
    * Detailed description.
    * @param[in] pSFM_conn
    * @param[in] pSFM
    * @return GM_BOOL GM_RSSP1_SFM_Ini_FSFB_Offline_Const
    */
    GM_BOOL GM_RSSP1_SFM_Ini_FSFB_Offline_Const(GM_RSSP1_SFM_connection_struct *pSFM_conn , GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief FSFB校验周期步进
    *
    * Detailed description.
    * @param[in] pSFM
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_SFM_Update_Time(GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief 获取SFM模块的状态
    *
    * Detailed description.
    * @param[in] pSFM
    * @return GM_RSSP1_library_state_enum
    */
    GM_RSSP1_library_state_enum GM_RSSP1_SFM_Get_Library_Status(GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief 根据SACEPID获取一个安全连接
    *
    * Detailed description.
    * @param[in] pSaCEPID
    * @param[in] pSFM
    * @return GM_RSSP1_SFM_connection_struct*
    */
    GM_RSSP1_SFM_connection_struct *GM_RSSP1_SFM_Get_Connection_BY_SaCEPID(GM_RSSP1_SACEPID_struct *pSaCEPID , GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief 判断两个SACEPID是否相等
    *
    * Detailed description.
    * @param[in] pSaCEPID1
    * @param[in] pSaCEPID2
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_SFM_Is_SaCEPID_Equal(GM_RSSP1_SACEPID_struct *pSaCEPID1 , GM_RSSP1_SACEPID_struct *pSaCEPID2);

    /**
    * @brief 应用层向SFM模块放入请求原语
    *
    * Detailed description.
    * @param[in] pU2L
    * @param[in] pSFM
    * @return GM_RSSP1_User_Put_Pri_To_SFM_Result_enum
    */
    GM_RSSP1_User_Put_Pri_To_SFM_Result_enum GM_RSSP1_User_Put_Pri_To_SFM(GM_RSSP1_SFM_U2L_pri_struct *pU2L , GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief 应用层从SFM模块获取原语
    *
    * Detailed description.
    * @param[in] pL2U
    * @param[in] pSFM
    * @return GM_RSSP1_User_Get_Pri_From_SFM_Result_enum
    */
    GM_RSSP1_User_Get_Pri_From_SFM_Result_enum GM_RSSP1_User_Get_Pri_From_SFM(GM_RSSP1_SFM_L2U_pri_struct *pL2U , GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief 应用层发送数据
    *
    * 通过SACEPID标识数据接收方.
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
    * @brief SFM发送RSD数据包
    *
    * Detailed description.
    * @param[in] pDat_pri
    * @param[in] pSFM_conn
    * @param[in] pSFM
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_SFM_Send_RSD(GM_RSSP1_SFM_U2L_pri_struct *pDat_pri , GM_RSSP1_SFM_connection_struct *pSFM_conn , GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief SFM发送SSE数据包
    *
    * Detailed description.
    * @param[in] pSFM_conn
    * @param[in] pSFM
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_SFM_Send_SSE(GM_RSSP1_SFM_connection_struct *pSFM_conn , GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief SFM发送SSR数据包
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
    * @brief SFM处理应用层的消息
    *
    * Detailed description.
    * @param[in] pSFM
    */
    void GM_RSSP1_SFM_Process_User_Req(GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief SFM向应用层报告消息
    *
    * SFM向目的sacepid相同的所有安全连接都发送数据，用于两个设备通过多条FSFB连接相连的情况.
    * @param[in] pL2U_pri
    * @param[in] pSFM
    */
    void GM_RSSP1_SFM_Report_indi_To_User(GM_RSSP1_SFM_L2U_pri_struct *pL2U_pri , GM_RSSP1_SFM_object_struct *pSFM);

    void GM_RSSP1_SFM_Report_Connection_State_To_User(GM_RSSP1_SFM_object_struct *pSFM , GM_RSSP1_CFM_L2U_pri_struct *pIndi_pri);
    void GM_RSSP1_SFM_Report_Warning_To_User(GM_RSSP1_SFM_connection_struct *pSFM_con , GM_RSSP1_SFM_object_struct *pSFM , GM_UINT8 warning_type);

    /**
    * @brief SFM处理CFM收到的消息
    *
    * Detailed description.
    * @param[in] pSFM
    */
    void GM_RSSP1_SFM_Process_CFM_Ind(GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief SFM监视各个安全连接的状态，并决定是否要进行宽恕。
    *
    * 通过各个连接可配置的时间值，在此时间内未收到校验正确的数据包，即视为断开.
    * @param[in] pSFM
    */
    void GM_RSSP1_SFM_Proc_Connection_Monit_And_Tolerate(GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief SFM处理各个安全连接通道内的数据队列
    *
    * 因为应用层只关心具体的设备，不关系本地设备与远程设备通过几个安全连接通道相连。
    * 启用b_enable_FSFB_on_chn选项UDP通道的FSFB连接，CFM将数据先送到相应FSFB连接中的L2U队列，Dispatch后才送到SFM中的L2U队列
    * 其他正常的FSFB连接，CFM处理完的数据将直接送到SFM的L2U队列.
    * @param[in] pSFM
    */
    void GM_RSSP1_SFM_Dispatch_Dat_Indi(GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief SFM处理接收到的SSE包
    *
    * Detailed description.
    * @param[in] pSFM_conn
    * @param[in] pDat_indi
    * @param[in] pSFM
    */
    void GM_RSSP1_SFM_Proc_Rcvd_SSE(GM_RSSP1_SFM_connection_struct *pSFM_conn , GM_RSSP1_CFM_L2U_Dat_pri_struct *pDat_indi , GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief SFM处理接收到的SSR包
    *
    * Detailed description.
    * @param[in] pSFM_conn
    * @param[in] pDat_indi
    * @param[in] pSFM
    */
    void GM_RSSP1_SFM_Proc_Rcvd_SSR(GM_RSSP1_SFM_connection_struct *pSFM_conn , GM_RSSP1_CFM_L2U_Dat_pri_struct *pDat_indi , GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief SFM处理接收到的RSD包
    *
    * Detailed description.
    * @param[in] pSFM_conn
    * @param[in] pDat_indi
    * @param[in] pSFM
    * @param[in] pCFM
    */
    void GM_RSSP1_SFM_Proc_Rcvd_RSD(GM_RSSP1_SFM_connection_struct *pSFM_conn , GM_RSSP1_CFM_L2U_Dat_pri_struct *pDat_indi , GM_RSSP1_SFM_object_struct *pSFM);

    /**
    * @brief SFM周期检查关键配置，防止越界等导致关键安全配置被修改。jianghongjun 20110825 safety enhancement
    *
    * Detailed description.
    * @param[in] pSFM
    */
    void GM_RSSP1_Check_Vital_Cfg(GM_RSSP1_SFM_object_struct *pSFM);

	/**
	* @brief SFM从CFM获取事件
	*
	* 此接口由CFM向SFM提供
	* @param[in] pL2U
	* @return GM_RSSP1_SFM_Get_Pri_From_CFM_Result_enum
	*/
	GM_RSSP1_SFM_Get_Pri_From_CFM_Result_enum GM_RSSP1_SFM_Get_Pri_From_CFM(GM_RSSP1_CFM_L2U_pri_struct *pL2U);

		/**
	* @brief SFM向CFM请求服务
	*
	* 此接口由CFM向SFM提供.
	* @param[in] pU2L
	* @param[in] pSFM
	* @return GM_RSSP1_SFM_Put_Pri_To_CFM_Result_enum
	*/
	GM_RSSP1_SFM_Put_Pri_To_CFM_Result_enum GM_RSSP1_SFM_Put_Pri_To_CFM(GM_RSSP1_CFM_U2L_pri_struct *pU2L, GM_RSSP1_SFM_object_struct *pSFM);

#ifdef __cplusplus
}
#endif

#endif
