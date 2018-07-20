/**
 * Copyright(C) 
 * 
 * @file:GM_CRC_Reflect.c
 * @brief:
 * @auther:
 */

#include "GM_CRC_Reflect.h"


/*比特颠倒,颠倒ch个比特*/
GM_UINT32 GM_CRC_Reflect(GM_UINT32 reflect, GM_UINT32 ch)
{
	GM_UINT32 i   = 0U;
	GM_UINT32 val = 0U;

	if (ch == 0U)
	{
	    val = reflect;
		return val;
	}

	else
	{
		for (i = 1U; i < (ch + 1U); ++i)
		{
			if ((GM_UINT32)0u != (reflect & (GM_UINT32)1))
			{
				val |= (1U << ((GM_UINT32)ch - (GM_UINT32)i));
			}

			reflect >>= 1U;
		}

		return val;
	}

}

