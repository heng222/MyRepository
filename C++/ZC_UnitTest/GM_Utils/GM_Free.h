/**
* @file GM_Free.h
* @brief
* @author 
* @date 
* @version

*/
#ifndef _GM_FREE_H
#define _GM_FREE_H

#include "GM_Utils_Base.h"

#ifdef WIN32
#include <malloc.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */

    /**
    * @brief GM_free
    *
    * 释放指针所指向的内存,是对free的封装.
    * @param[in] p 指针
    */
    void GM_free(void* p);

 #ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_FREE_H */

