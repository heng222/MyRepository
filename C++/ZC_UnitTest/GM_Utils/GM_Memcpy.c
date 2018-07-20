/**
* @file GM_Memcpy.c
* @brief
* @author 
* @date 
* @version
* <pre><b>copyright: 

*/
#include "GM_Memcpy.h"

/**
* @brief
*
* ·â×°ÁËmemcpy.
* @param[in] destination
* @param[in] source
* @param[in] dim
* @return void GM_memcpy
*/
void GM_memcpy(void* destination, const void* source, size_t size)
{
    if ((NULL == destination) || (NULL == source) || (size == (size_t)0))
    {
        return;
    }

    memcpy(destination, source, size);

    return;
}
