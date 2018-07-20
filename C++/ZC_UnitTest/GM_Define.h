/**
* @file GM_Utils_Define.h
* @brief 定义通用模块用到的宏
* @author Hao Liming
* @date 2010-11-2 15:56:31
* @version
* <pre><b>copyright: CASCO</b></pre>
* <pre><b>email: </b>haoliming@casco.com.cn</pre>
* <pre><b>company: </b>http://www.casco.com.cn</pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>Write modifications here.</pre>
*/
#ifndef _GM_DEFINE_H
#define _GM_DEFINE_H

/************  用户定义区1，选择操作系统  4选1 *********/
 /*若为windows，则定义:*/
#ifndef WIN32
#define WIN32
#endif



/*#define LINK_Part*/
#define SFM_Part
#define CFM_Part

#define GM_RSSP1_CHECK_CHN_NUM          2       /**< FSFB双通道校验 */

#define GM_RSSP1_MAX_USER_DAT_LEN       (480U)     /**< 为传输rssp2同步信息、GAL包组(20110218)而修改 */
/* 若为VXWORKS5_5，则定义:*/
#ifndef WIN32
#ifndef VXWORKS5_5
#define VXWORKS5_5
#endif
#endif
/* 若为VXWORKS6_6，则定义:
#ifndef VXWORKS6_6
#define VXWORKS6_6
#endif*/
/* 若为QNX，则定义:
#ifndef QNX
#define QNX
#endif
*/
/************  用户定义区2，选择 板卡  5选1*********/
/* 若为VIOC_UP板，则定义
#define _VIOC_6U_UP*/

/* 若为VIOC_DN板，则定义
#define _VIOC_6U_DN*/

/*若为VLE_6U_UP，则定义
#define _VLE_6U_UP*/

/*若为VLE_6U_DN，则定义
#define _VLE_6U_DN*/


/*若为DVCOM_6U板，则定义*/
/*#define _DVCOM_6U
*/
/*若为 爱默生 板，则定义
#define _EMERSON
*/
/*** 后板选择：如果使用VLE6U后板为VLE-2-RC板则定义，否则忽略此处选择 **
#define _VLE_6U_RC*/


/************  用户定义区3，选择当前项目以确定SACEM部分的支持方式 *********/
/*如果是3取2项目 
#define Platform_2oo3*/
/*如果是其它项目,无需额外宏定义*/

/************ 用户定义区4，先设定信息位的长度，再选择VSL 的应用端是否为PIC *********/
#define VSL_PACKET_INFO_LEN_RCV            (3U) /*接收的信息位长度，单位为4bytes*/
#define VSL_PACKET_INFO_LEN_SND            (1U) /*发送的信息位长度，单位为4bytes*/

/*如果是单片机接收端 则定义：
#define PIC16_RCV
*/

/************  用户定义区5， GM中的应用选择 *********/
/*定义要打印的log信息等级，
若定义为小于-10，则 调用 GM_Log_Msg的代码无效
若定义为大于等于-10的数，则代码中 小于等于n的log信息将被打印出来.GM本身代码定义的log范围是大于等于0*/
#define LOG_LEVEL    (-1)

/************  用户定义区6， FSFB2中的应用选择 *********/
/* 定义 FSFB2 SHB BUFFER 支持的最大码位数*/
#define GM_FSFB2_SHB_SIZE_MAX    256U
#define  GM_FSFB2_CON_NUM_MAX 100U
#define GM_FSFB2_VSNID 0U /*默认0与原始VSN一致*/
/************  用户定义区7， GM_MQ_FIXED中的应用选择 *********/
/* 定义GM_MQ_FIXED中消息队列最多存放的消息数 */
#define GM_MQ_FIXED_MSG_NUM        500U
/* 定义GM_MQ_FIXED中消息队列最多存放的消息数 */
#define GM_MQ_FIXED_MSG_SIZE    1480U
/*(GM_MQ_FIXED_MSG_SIZE + 2) * (GM_MQ_FIXED_MSG_NUM) 应小于 操作系统对数组的最大size限制 */


/************  用户定义区8， MR中的应用选择 *********/
/* 定义MR中最多存放的内存个数 */
#define GM_CHKW_MEMORY_NUM_MAX_EACHSLOT (30U) /**< add by kou on 11-04-20 定义各刷新时隙内内存块的最大个数 */
#define GM_CHKW_CREATE_CHKW_NUM_MAX (20U)   /**< add by kou on 11-04-21 定义合并生成某个校核字所需的最大校核字个数 */

/************  用户定义区9， MUDP中的应用选择 *********/
/* 定义MUDP中，接收端SN表的大小 */
#define GM_MUDP_RCV_SN_MAX_NUM (15U) /* sjz: 接收端SN表的大小 */

/************  用户定义区 结束 *********/
/*避免操作系统重复定义*/
/*当为VXWORKS时定义VXWORKS*/
#ifdef VXWORKS5_5
#ifndef VXWORKS
#define VXWORKS
#endif
#undef VXWORKS6_6
#undef WIN32
#undef QNX
#endif

#ifdef VXWORKS6_6
#ifndef VXWORKS
#define VXWORKS
#endif
#undef VXWORKS5_5
#undef WIN32
#undef QNX
#endif

#ifdef WIN32
#undef VXWORKS
#undef VXWORKS5_5
#undef VXWORKS6_6
#undef QNX
#endif

#ifdef QNX
#undef VXWORKS
#undef VXWORKS5_5
#undef VXWORKS6_6
#undef WIN32
#endif

/*避免板卡重复定义  
_VLE_6U_RC    仅BIOS Time时候需要，支持VLE RC板
_6U            VIOC VLE（UP DN） DVCOM板都需要        DRAM HD WD TIMER SYSTIMESTAMP
_VLE_6U        VLE(UP DN)需要，用于和VIOC区别开    DRAM
_EMERSON    CPCI6200需要                        HD WD Timer SYSTIMESTAMP BIOSTime
*/

/*为 _VLE_6U_UP板， 定义宏定义_6U,排除对_VIOC的定义*/
#ifdef _VLE_6U_UP
#define _VLE_6U
#define _6U_UP
#define _6U
#undef _EMERSON
#endif

/*为_VLE_6U_DN板*/
#ifdef _VLE_6U_DN
#define _VLE_6U
#define _6U_DN
#define _6U
#undef _EMERSON
#endif

/*为 VIOC板， VIOC与VLE_6U的驱动不一致*/
#ifdef _VIOC_6U_UP
#define _6U_UP
#define _6U
#undef _VLE_6U
#undef _EMERSON
#undef _VLE_6U_RC
#endif

/*为 VIOC板， VIOC与VLE_6U的驱动不一致*/
#ifdef _VIOC_6U_DN
#define _6U_DN
#define _6U
#undef _VLE_6U
#undef _EMERSON
#undef _VLE_6U_RC
#endif


/*为_DVCOM_6U 板*/
#ifdef _DVCOM_6U
#define _6U
#undef _VLE_6U
#undef _EMERSON
#undef _VLE_6U_RC
#endif

/*为_EMERSON 板*/
#ifdef _EMERSON
#undef _VLE_6U
#undef _6U
#undef _VLE_6U_RC
#endif

/*设置SACEM部分宏定义*/
#ifdef Platform_2oo3
#define NO_PRINTF
#else/*除2003其它项目支持malloc和读文件*/

#define GM_SACEM_Malloc_Used
#define GM_SACEM_Initial_From_File
#endif






#endif

