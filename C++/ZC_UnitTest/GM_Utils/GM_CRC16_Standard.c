/**
* @file GM_CRC.c
* @brief
* @author 
* @date 2009-12-22 15:35:46
* @version
* <pre><b>copyright: 

*/
#include "GM_CRC16_Standard.h"

/*isHighFirst=1,多项式0x1021，正序CRC
isHighFirst=0,多项式0x1021，逆序CRC，传入多项式0x1021*/
GM_BOOL GM_CRC_Calculate_CRC16_Standard_Seed(GM_UINT8 Data[], GM_UINT16 DataLen, GM_UINT16 Seed, GM_UINT16 Poly, GM_BOOL isHighFirst, const GM_UINT16 pCRC16Table[], GM_UINT16 pCRC[])
{
	
	GM_UINT32 i = 0U;
	GM_UINT16 x = Seed;
	GM_UINT16 POLY = 0U;

	if ((NULL == Data) || (NULL == pCRC16Table) || (NULL == pCRC))
	{
		return GM_FALSE;
	}

    if (isHighFirst == GM_TRUE)
	{
		if (pCRC16Table[1U]!= Poly)
		{
			return GM_FALSE;
		}

		for (i = (GM_UINT32)0u; i < DataLen; ++i)
		{
			x = pCRC16Table[(GM_UINT8)(x>>8) ^ Data[i]] ^((x << 8U) & 0xFFFFU);
		}

		*pCRC = (GM_UINT16)(0xFFFFU & x);
	}
	else
	{
		/*颠倒POLY,0x1021 to 0x8408*/
	    POLY = (GM_UINT16)GM_CRC_Reflect((GM_UINT32)Poly,16U);

	    if (pCRC16Table[128U]!= POLY)
	    {
		    return GM_FALSE;
	    }

	    for (i = (GM_UINT32)0u; i < DataLen; ++i)
	    {
		    x = (x >> 8U) ^ pCRC16Table[(x ^ Data[i]) & 0xff];
	    }

	    *pCRC = (GM_UINT16)(0xFFFFU & x);
	}

	return GM_TRUE;
}

