/**
* @file GM_Malloc.c
* @brief
* @author 
* @date 
* @version
* <pre><b>copyright: 

*/
#include "GM_Malloc.h"

/* @brief
*
*
* 封装了malloc.
* @param[in] size
* @return void* GM_malloc
*/
void* GM_malloc(size_t size)
{
    void* rt = NULL;

	/*增加对size=0时候，返回null */
	if (size != (size_t)0)
	{
		rt = malloc(size);
	}

    return rt;
}

