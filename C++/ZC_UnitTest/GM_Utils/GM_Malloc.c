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
* ��װ��malloc.
* @param[in] size
* @return void* GM_malloc
*/
void* GM_malloc(size_t size)
{
    void* rt = NULL;

	/*���Ӷ�size=0ʱ�򣬷���null */
	if (size != (size_t)0)
	{
		rt = malloc(size);
	}

    return rt;
}

