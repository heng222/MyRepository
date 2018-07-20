/**
* @file GM_Memcpy.h
* @brief
* @author 
* @date 
* @version

*/
#ifndef _GM_MEMCPY_H
#define _GM_MEMCPY_H

#include "GM_Utils_Base.h"

#ifdef WIN32
#include <malloc.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */

    /**
    * @brief
    *
    * ·â×°ÁËmemcpy.
    * @param[in] destination
    * @param[in] source
    * @param[in] dim
    * @return void GM_memcpy
    */
    void GM_memcpy(void* destination, const void* source, size_t dim);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_MEMCPY_H */

