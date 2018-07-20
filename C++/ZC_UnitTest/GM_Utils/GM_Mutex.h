/**
* @file GM_Mutex.h
* @brief
* @author 
* @date 
* @version

*/
#ifndef _GM_MUTEX_H
#define _GM_MUTEX_H

#include "GM_Utils_Base.h"
#include "GM_Malloc.h"
#include "GM_Free.h"

#ifdef VXWORKS
#include <semLib.h>
#endif

#ifdef QNX
#include <pthread.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */

#ifdef WIN32
	typedef HANDLE          GM_MUTEX;
#endif
#ifdef QNX
	typedef pthread_mutex_t* GM_MUTEX;
#endif
#ifdef VXWORKS
	typedef SEM_ID          GM_MUTEX;
#endif

    /**
    * @brief GM_Mutex_Init
    *
    * ³õÊ¼»¯»¥³âÆ÷.
    * @param[out] mutex
    * @return GM_BOOL
    */
    GM_BOOL GM_Mutex_Init(GM_MUTEX* pMutex);

    /**
    * @brief GM_Mutex_Destroy
    *
    * Ïú»Ù»¥³âÆ÷.
    * @param[in] mutex
    * @return GM_BOOL
    */
 /*   GM_BOOL GM_Mutex_Destroy(GM_MUTEX mutex);*/

    /**
    * @brief GM_Mutex_Lock
    *
    * »ñµÃ»¥³âÆ÷×ÊÔ´.
    * @param[in] mutex
    * @return GM_BOOL
    */
    GM_BOOL GM_Mutex_Lock(GM_MUTEX mutex);

    /**
    * @brief GM_Mutex_Unlock
    *
    * ÊÍ·Å»¥³âÆ÷.
    * @param[in] mutex
    * @return GM_BOOL
    */
    GM_BOOL GM_Mutex_Unlock(GM_MUTEX mutex);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_MUTEX_H */
