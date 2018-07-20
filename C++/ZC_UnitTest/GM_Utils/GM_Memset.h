/**
* @file GM_Memset.h
* @brief
* @author 
* @date 2010-9-30 13:33:06
* @version
*/
#ifndef _GM_MEMSET_H
#define _GM_MEMSET_H

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
    * ·â×°ÁËmemset.
    * @param[in] destination
    * @param[in] value
    * @param[in] dim
    * @return void GM_memset
    */
    void GM_memset(void* destination, GM_UINT8 value, size_t dim);
  
#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_MEMSET_H */

