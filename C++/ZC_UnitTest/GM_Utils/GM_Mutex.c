/**
* @file GM_Mutex.c
* @brief
* @author
* @date
* @version

*/
#include "GM_Mutex.h"

#ifdef WIN32

GM_BOOL GM_Mutex_Init(GM_MUTEX* pMutex)
{
    if (NULL == pMutex)
    {
        return GM_FALSE;
    }

    *pMutex = CreateMutex(NULL, GM_FALSE, NULL);

    if (0 == (*pMutex))
    {
        return GM_FALSE;
    }
    else
    {
        return GM_TRUE;
    }
}

GM_BOOL GM_Mutex_Destroy(GM_MUTEX mutex)
{
    int rt = 0;

    rt = CloseHandle(mutex);

    if (0 == rt)
    {
        return GM_FALSE;
    }
    else
    {
        return GM_TRUE;
    }
}

GM_BOOL GM_Mutex_Lock(GM_MUTEX mutex)
{
    DWORD rt = 0;

    rt = WaitForSingleObject(mutex, INFINITE);

    if (WAIT_OBJECT_0 == rt)
    {
        return GM_TRUE;
    }
    else
    {
        return GM_FALSE;
    }
}

GM_BOOL GM_Mutex_Unlock(GM_MUTEX mutex)
{
    int rt = 0;

    rt = ReleaseMutex(mutex);

    if (0 == rt)
    {
        return GM_FALSE;
    }
    else
    {
        return GM_TRUE;
    }
}
#endif
#ifdef QNX
GM_BOOL GM_Mutex_Init(GM_MUTEX* pMutex)
{
    int rt = 0;

    if (NULL == pMutex)
    {
        return GM_FALSE;
    }
    *pMutex = (pthread_mutex_t*)GM_malloc(sizeof(pthread_mutex_t));
    rt = pthread_mutex_init(*pMutex, NULL);

    if (0 == rt)
    {
        return GM_TRUE;
    }
    else
    {
        return GM_FALSE;
    }
}

GM_BOOL GM_Mutex_Destroy(GM_MUTEX mutex)
{
    int rt = 0;

    rt = pthread_mutex_destroy(mutex);

    GM_free((void *)mutex);
    if (0 == rt)
    {
        return GM_TRUE;
    }
    else
    {
        return GM_FALSE;
    }
}

GM_BOOL GM_Mutex_Lock(GM_MUTEX mutex)
{
    int rt = 0;
    rt = pthread_mutex_lock(mutex);

    if (0 == rt)
    {
        return GM_TRUE;
    }
    else
    {
        return GM_FALSE;
    }
}

GM_BOOL GM_Mutex_Unlock(GM_MUTEX mutex)
{
    int rt = 0;

    rt = pthread_mutex_unlock(mutex);

    if (0 == rt)
    {
        return GM_TRUE;
    }
    else
    {
        return GM_FALSE;
    }
}
#endif

#ifdef VXWORKS
/*
*
*
*
*
*
*/
GM_BOOL GM_Mutex_Init(GM_MUTEX* pMutex)
{
    if (NULL == pMutex)
    {
        return GM_FALSE;
    }

    *pMutex = semBCreate(SEM_Q_FIFO, SEM_FULL);

    if (NULL == (*pMutex))
    {
        return GM_FALSE;
    }
    else
    {
        return GM_TRUE;
    }
}
/*
GM_BOOL GM_Mutex_Destroy(GM_MUTEX mutex)
{
    STATUS rt = OK;

    rt = semTake(mutex, WAIT_FOREVER);

    if (OK == rt)
    {
       semDelete(mutex);
       return GM_TRUE;
    }
    else
    {
        return GM_FALSE;
    }
}
*/

/*
*
*
*
*
*
*/
GM_BOOL GM_Mutex_Lock(GM_MUTEX mutex)
{
    STATUS rt = OK;

    rt = semTake(mutex, (int)WAIT_FOREVER);

    if (OK == rt)
    {
        return GM_TRUE;
    }
    else
    {
        return GM_FALSE;
    }
}

/*
*
*
*
*
*
*/
GM_BOOL GM_Mutex_Unlock(GM_MUTEX mutex)
{
    STATUS rt = OK;

    rt = semGive(mutex);

    if (OK == rt)
    {
        return GM_TRUE;
    }
    else
    {
        return GM_FALSE;
    }
}

#endif

