/**
* @file GM_Utils_Base.h
* @brief
* @author 
* @date 
* @version

*/

#ifndef _GM_UTILS_BASE_H
#define _GM_UTILS_BASE_H

#include "../GM_Define.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifndef WIN32
#define WIN32
#endif

#ifdef WIN32
#define OS_WINDOWS WIN32
#include <winsock2.h>
#endif

#ifdef VXWORKS
#include <vxworks.h>
#ifdef VXWORKS6_6
#include <ioLib.h>
#include <sioLibCommon.h>
#endif

#ifdef VXWORKS5_5
#endif
#endif
#ifdef QNX
#include <errno.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */
    /**
    * @BasicType
    * @brief �������Ͷ���
    *
    * Detailed description.
    * @{
    */

#ifdef WIN32
#define GM_Get_Error_No() GetLastError()
#endif
#ifdef VXWORKS
#define GM_Get_Error_No() errno
#endif
#ifdef QNX
#define GM_Get_Error_No() errno
#endif

#ifndef NULL
#define NULL 0U
#endif


    typedef unsigned char      GM_UINT8;
    typedef unsigned short     GM_UINT16;
    typedef unsigned long      GM_UINT32;
    typedef signed char        GM_INT8;
    typedef signed short int   GM_INT16;
    typedef signed long int    GM_INT32;
    typedef float              GM_FLOAT;
    typedef double             GM_DOUBLE;
    typedef int                GM_BOOL;

#define GM_TRUE   (GM_BOOL)1
#define GM_FALSE  (GM_BOOL)0
#define GM_ERROR  ((GM_INT32)(-1))
#define GM_OK (0)
    
#ifdef WIN32
    typedef ULONGLONG          GM_UINT64;
    typedef LONGLONG           GM_INT64;
#else/*��������ϵͳ*/
    typedef unsigned long long GM_UINT64;
    typedef long long          GM_INT64;
#endif

#define GM_UINT32_MAX (4294967295U) /**< GM_UINT32���ֵ */
#define GM_UINT16_MAX (65535U)        /**< GM_UINT16���ֵ */
#define GM_UINT8_MAX  (255)          /**< GM_UINT8���ֵ */
#define GM_LONG_MIN   (-2147483647L - 1)
#define GM_LONG_MAX   (2147483647L)
    /** @} */

#ifdef WIN32
	#pragma pack(1) /**< �Ե��ֽڶ��� */
	#define GM_PACKED
#else/*��������ϵͳ*/

#define GM_PACKED  __attribute__((__packed__))

#endif

    /**
    * @main
    * @brief ���ݲ�ͬ�Ĳ���ϵͳ������Ӧ������ļ�
    *
    * ֧��Windowx��Linux��VxWorks.
    * @{
    */
#ifdef WIN32
#undef QNX
#undef VXWORKS
#define GM_MAIN_ENTRY void main
#endif

#ifdef QNX
#undef WIN32
#undef VXWORKS
#define GM_MAIN_ENTRY void main
#endif

#ifdef VXWORKS
#undef QNX
#undef WIN32
#define GM_MAIN_ENTRY void usrAppInit
#endif

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_UTILS_BASE_H */

