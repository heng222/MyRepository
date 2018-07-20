/**
* @file GM_Memset.c
* @brief
* @author
* @date 
* @version

*/
#include "GM_Memset.h"

/**
* @brief
*
* ¡¤a¡Á¡ã¨¢?memset.
* @param[in] destination
* @param[in] value
* @param[in] dim
* @return void GM_memset
*/
void GM_memset(void* destination, GM_UINT8 value, size_t size)
{
    if ((NULL == destination) || (size == (size_t)0))
    {
        return;
    }

    memset(destination, (int)value, size);

    return;
}
