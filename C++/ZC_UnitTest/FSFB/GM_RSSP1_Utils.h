/**
* @file GM_RSSP1_Utils.h
* @brief 提供了FSFB协议中使用的公共数据
* @author JiangHongjun
* @date 2010-2-7 16:27:30
* @version
* <pre><b>copyright: CASCO</b></pre>
* <pre><b>email: </b>jianghongjun@casco.com.cn</pre>
* <pre><b>company: </b>http://www.casco.com.cn</pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>Write modifications here.</pre>
*/
#ifndef _GM_RSSP1_UTILS_H
#define _GM_RSSP1_UTILS_H



#include "../GM_Utils/GM_Utils_Base.h"
#include "../GM_Utils/GM_Free.h"
#include "../GM_Utils/GM_Memcpy.h"
#include "../GM_Utils/GM_Memset.h"
#include "../GM_Utils/GM_Malloc.h"
#include "../GM_Utils/GM_CRC16.h"
#include "../GM_Utils/GM_CRC32.h"
#include "../GM_Utils/GM_CRC_Table16.h"
#include "../GM_Utils/GM_CRC_Table32.h"
#include "../GM_Utils/GM_LFSR.h"
#include "../GM_Utils/GM_Mutex.h"
/*
#ifndef PF2oo3
#include "../GM_Utils/GM_Ini_File.h"
#endif
*/
#ifdef WIN32
#include <winsock2.h>
#include "process.h"
#pragma comment(lib, "Ws2_32.lib")
#endif
#ifdef LINUX
#include <unistd.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <netinet/tcp.h>
#endif
#ifdef OS_VXWORKS
#include <vxworks.h>
/*#include <config.h>*/
#include <netinet/in.h>
#include <inetLib.h>
#include <tickLib.h>
#include <sysLib.h>
#include <logLib.h>
#include <ioLib.h>
#include <taskLib.h>
#include <semLib.h>
#include <hostLib.h>
#include <sockLib.h>
#include <taskLib.h>
#include <errnoLib.h>
#include <wdLib.h>
#include <sioLib.h>
#include <intLib.h>
#include <symLib.h>
/*#include <loadLib.h>*/
#include <dosFsLib.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/tcp.h>
/*#include <fldrvvxw.h>*/
#endif


#ifdef __cplusplus
extern "C"
{
#endif

	#define GM_RSSP1_OK 1
	#define GM_RSSP1_ERROR (-1)
	#define GM_RSSP1_RETURN_RESERVED  (-2)

	/** 常用数据大小限制定义 */
#ifndef GM_RSSP1_CHECK_CHN_NUM
	#define GM_RSSP1_CHECK_CHN_NUM          2       /**< FSFB双通道校验 */
#endif

#ifndef GM_RSSP1_MAX_USER_DAT_LEN
	#define GM_RSSP1_MAX_USER_DAT_LEN       (480)     /**< 为传输rssp2同步信息、GAL包组(20110218)而修改 */
#endif

	/*    #define GM_RSSP1_MAX_USER_DAT_LEN       478  */  /**< 安全层可接受的来自应用层的最大数据长度RSSP-I p10. 必须为偶数字节 */
	#define GM_RSSP1_MAX_SAFETY_DAT_LEN     GM_RSSP1_MAX_USER_DAT_LEN     /**< 通信层可接受的来自安全层的最大数据长度RSSP-I p10. */
	#define GM_RSSP1_MAX_SND_DAT_LEN        GM_RSSP1_MAX_SAFETY_DAT_LEN

	#define GM_RSSP1_MAX_DELTATIME_ARRAY_SIZE       128    /**< 为PREC_SINIT[]和POST_RXDATA[]数组分配的最大容量。实际使用时以各通道配置的deltaTime为依据 */
	#define GM_RSSP1_MAX_SAFETY_CONNECTION_NUM      128   /**< 最多支持的FSFB安全连接数 */
	#define GM_RSSP1_CFM_MAX_CHANNEL_NUM        2      /**< 底层冗余通道数最大值 */
	#define GM_RSSP1_MAX_PKT_NUM_PER_CYCLE          5     /**< 每周期可能产生的每种数据包最大数量。包括RSD、SSE、SSR */

		/*  CFM 常用参数定义 */
	#define GM_RSSP1_MAX_TOLERATE_CYCLE             20  /**< FSFB宽恕配置最大不能超过10秒。jianghongjun 20110825 safety enhancement */


	/*fulintai*/
	#define GM_RSSP1_MAX_LINK_CHANNEL        GM_RSSP1_CFM_MAX_CHANNEL_NUM
	
	

	
	
#ifdef __cplusplus
}
#endif

#endif

