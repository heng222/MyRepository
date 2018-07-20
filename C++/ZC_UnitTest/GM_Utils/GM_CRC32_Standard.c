/**
 * Copyright(C)
 * 
 * @file:GM_CRC32_Standard.c
 * @brief:
 * @auther:
 * @create date:

 */

#include "GM_CRC32_Standard.h"


#if 0
//方法1，直接查询表+字节颠倒+CRC结果颠倒
GM_BOOL GM_CRC_Calculate_CRC32_Standard_H(GM_UINT8* Data, GM_UINT32 DataLen, GM_UINT32 Poly, GM_UINT32* pCRC)
{
	GM_UINT32 i = 0U;
	GM_UINT32 x = 0xFFFFFFFFU;
	GM_UINT8 y  = 0U;
	GM_BOOL rt = GM_FALSE;
	GM_UINT32 pCRCTable[256]={0U};

    rt = GM_CRC_Build_CRC32_Table_H(Poly, pCRCTable);

	for (i = (GM_UINT32)0U; i < DataLen; ++i)
	{
		y = GM_CRC_Reflect(Data[i] , 8);
		x = (x << 8U) ^ pCRCTable[((x>>24) ^ y) & 0xFFU];
	}

	*pCRC =GM_CRC_Reflect(x, 32)^0xFFFFFFFFU;

	return GM_TRUE;
}
#endif

/*方法2，逆序表+正常字节序+正常CRC结果*/
GM_BOOL GM_CRC_Calculate_CRC32_Standard(GM_UINT8 Data[], GM_UINT32 DataLen, GM_UINT32 Poly, const GM_UINT32 pCRC32Table[], GM_UINT32 pCRC[])
{
	GM_UINT32 i = 0U;
	GM_UINT32 x = 0xFFFFFFFFU;
	GM_UINT32 POLY = 0U;

	if ((NULL == Data) || (NULL == pCRC32Table) || (NULL == pCRC))
	{
		return GM_FALSE;
	}

	/*颠倒POLY,0x04C11DB7 to 0xEDB88320*/
	POLY = GM_CRC_Reflect(Poly,32U);

	if (pCRC32Table[128U]!= POLY)

	{
		return GM_FALSE;
	}

	for (i = (GM_UINT32)0U; i < DataLen; ++i)
	{
		x = (x >> 8U) ^ pCRC32Table[(x ^ Data[i]) & 0xFFU];
	}

	*pCRC = x^0xFFFFFFFFU;

	return GM_TRUE;
}

