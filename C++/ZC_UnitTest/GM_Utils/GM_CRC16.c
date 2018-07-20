/**
* @file GM_CRC16.c
* @brief
* @author 
* @date 
* @version
* <pre><b>copyright: 

*/
#include "GM_CRC16.h"


GM_BOOL GM_CRC_Calculate_CRC16(const GM_UINT8 pBuffer[], GM_UINT32 bufferLen, GM_UINT16 pCRC[], const GM_UINT16 pCRCTable[])
{
	/** @brief ´ý´¦Àí */
	GM_UINT32 i = 0U;
	GM_UINT16 x = 0U;

	if ((NULL == pBuffer) || (NULL == pCRCTable) || (NULL == pCRC))
	{
		return GM_FALSE;
	}

	for (i = (GM_UINT32)0u; i < bufferLen; ++i)
	{
		x = pCRCTable[((1U << 8U) - 1U) & (x ^ (GM_UINT16)(pBuffer[i]))] ^((x >> 8U) & 0xFFFFU);
	}

	*pCRC = (GM_UINT16)(0xFFFFU & x);

	return GM_TRUE;
}


