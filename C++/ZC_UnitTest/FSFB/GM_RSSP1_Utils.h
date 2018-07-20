/**
* @file GM_RSSP1_Utils.h
* @brief �ṩ��FSFBЭ����ʹ�õĹ�������
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

	/** �������ݴ�С���ƶ��� */
#ifndef GM_RSSP1_CHECK_CHN_NUM
	#define GM_RSSP1_CHECK_CHN_NUM          2       /**< FSFB˫ͨ��У�� */
#endif

#ifndef GM_RSSP1_MAX_USER_DAT_LEN
	#define GM_RSSP1_MAX_USER_DAT_LEN       (480)     /**< Ϊ����rssp2ͬ����Ϣ��GAL����(20110218)���޸� */
#endif

	/*    #define GM_RSSP1_MAX_USER_DAT_LEN       478  */  /**< ��ȫ��ɽ��ܵ�����Ӧ�ò��������ݳ���RSSP-I p10. ����Ϊż���ֽ� */
	#define GM_RSSP1_MAX_SAFETY_DAT_LEN     GM_RSSP1_MAX_USER_DAT_LEN     /**< ͨ�Ų�ɽ��ܵ����԰�ȫ���������ݳ���RSSP-I p10. */
	#define GM_RSSP1_MAX_SND_DAT_LEN        GM_RSSP1_MAX_SAFETY_DAT_LEN

	#define GM_RSSP1_MAX_DELTATIME_ARRAY_SIZE       128    /**< ΪPREC_SINIT[]��POST_RXDATA[]�����������������ʵ��ʹ��ʱ�Ը�ͨ�����õ�deltaTimeΪ���� */
	#define GM_RSSP1_MAX_SAFETY_CONNECTION_NUM      128   /**< ���֧�ֵ�FSFB��ȫ������ */
	#define GM_RSSP1_CFM_MAX_CHANNEL_NUM        2      /**< �ײ�����ͨ�������ֵ */
	#define GM_RSSP1_MAX_PKT_NUM_PER_CYCLE          5     /**< ÿ���ڿ��ܲ�����ÿ�����ݰ��������������RSD��SSE��SSR */

		/*  CFM ���ò������� */
	#define GM_RSSP1_MAX_TOLERATE_CYCLE             20  /**< FSFB��ˡ��������ܳ���10�롣jianghongjun 20110825 safety enhancement */


	/*fulintai*/
	#define GM_RSSP1_MAX_LINK_CHANNEL        GM_RSSP1_CFM_MAX_CHANNEL_NUM
	
	

	
	
#ifdef __cplusplus
}
#endif

#endif

