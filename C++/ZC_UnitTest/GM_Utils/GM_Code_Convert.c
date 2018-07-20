/**
* @file GM_Code_Convert.c
* @brief
* @author 
* @date 
* @version

*/

#include "GM_Code_Convert.h"

/*
*
*
*
*
*
*
*/
GM_BOOL GM_Code_BYTE2BIT(const char pIn[], GM_UINT32 bits, int pOut[])
{
    int i = 0;

    if ((NULL == pOut) || (NULL == pIn) || ((GM_UINT32)0U == (GM_UINT32)bits))
    {
        return GM_FALSE;
    }

    for (i = 0; (GM_UINT32)i < bits; ++i)
    {
        pOut[i] = ((int)(pIn[i >> 3U]) >> (i & 7U)) & 1U;
    }

    return GM_TRUE;
}

/*
*
*
*
*
*
*
*/
GM_BOOL GM_Code_BIT2BYTE(const int pIn[], GM_UINT32 bits, char pOut[])
{
    int i = 0;
	int size = 0;

    if ((NULL == pOut) || (NULL == pIn) || ((GM_UINT32)0U ==(GM_UINT32)bits))
    {
        return GM_FALSE;
    }

	if ((int)bits % 8U == 0U)
	{
		size = ((int)bits) / 8U;
	}
	else
	{
		size = ((int)bits)/8U + 1U;
	}

	GM_memset((void*)pOut, (GM_UINT8)0U, (size_t)size);

    for (i = 0U; (GM_UINT32)i < bits; ++i)
    {
        pOut[i>>3] |= (char)(pIn[i] << (i & 7U));
    }

    return GM_TRUE;
}



/*
*
*
*
*
*
*
*/
int GM_Code_BCD2DEC(int BCDcode)
{
	int DECcode = -1;
	if ((BCDcode <= 39321)&&(BCDcode >= 0))
	{
		DECcode = (BCDcode & 0xF000) / 4096 * 1000 + (BCDcode & 0xF00) / 256 * 100 + (BCDcode & 0xF0) / 16 * 10 + (BCDcode & 0xF);
	}
	return DECcode;
}

/*
*
*
*
*
*
*
*/
int GM_Code_DEC2BCD(int DECcode)
{
	int BCDcode = -1;
	if ((DECcode <= 9999)&&(DECcode >= 0))
	{
		BCDcode = DECcode / 1000 * 4096 + (DECcode - DECcode / 1000 * 1000) / 100 * 256 + (DECcode - DECcode / 100 * 100) / 10 * 16 + (DECcode - DECcode / 10 * 10);
	}
    return BCDcode;
}

/*
*
*
*
*
*
*
*/
GM_BOOL GM_Code_HEX2INT(const char pHEX[], GM_UINT8 len, int pDEC[])
{
    int i   = 0U;
    int mid = 0U;

    if ((NULL == pHEX) || (NULL == pDEC) || (8 < len))
    {
        return GM_FALSE;
    }
	/*当出错时，返回的指针内容 为 0 */
	*pDEC = 0U;

    mid = 0U;


    for (i = 0U; i < (int)len; ++i)
    {
        if ((pHEX[i] >= (char)'0') && (pHEX[i] <= (char)'9'))
        {
            mid = (int)(pHEX[i] - (char)'0');
        }
		else
		{
	         if ((pHEX[i] >= (char)'a') && (pHEX[i] <= (char)'f'))
	        {
	            mid = (int)(pHEX[i] - (char)'a') + 10U;
	        }
			 else
			 {
		        if ((pHEX[i] >= (char)'A') && (pHEX[i] <= (char)'F'))
		        {
		            mid = (int)(pHEX[i] - (char)'A') + 10U;
		        }
		        else
		        {
					*pDEC = 0U;
		            return GM_FALSE;
		        }
			 }
		}
        mid <<= (((int)len - i - 1) << 2);

        *pDEC |= mid;
    }

    return GM_TRUE;
}

/*
*
*
*
*
*
*
*/
GM_BOOL GM_Code_Is_Big_Endian(void)
{
    GM_BOOL isBigEndian		   = GM_FALSE;
    GM_UINT16 value            = 0x55AAU;
	GM_UINT8 valuetemp = *((GM_UINT8*)(&value));

    if (0x55U == valuetemp)
    {
        isBigEndian = GM_TRUE;
    }
    else
    {
        isBigEndian = GM_FALSE;
    }

    return isBigEndian;
}

/*
*
*
*
*
*
*
*/
GM_UINT16 GM_Code_Big_Little_Endian16(GM_UINT16 x)
{
    GM_UINT16 y = 0U;
    GM_UINT16 z = 0U;

    z = x & 0x00FFU;
    y = z << 8U;
    z = x & 0xFF00U;
    y += (z >> 8U);
    return y;
}

/*
*
*
*
*
*
*
*/
GM_UINT32 GM_Code_Big_Little_Endian32(GM_UINT32 x)
{
    GM_UINT32 y = 0U;
    GM_UINT32 z = 0U;

    z = x & 0x000000FFU;
    y = z << 24U;
    z = x & 0x0000FF00U;
    y += (z << 8U);
    z = x & 0x00FF0000U;
    y += (z >> 8U);
    z = x & 0xFF000000U;
    y += (z >> 24U);
    return y;
}

/*
*
*
*
*
*
*
*/
GM_UINT64 GM_Code_Big_Little_Endian64(GM_UINT64 x)
{
    GM_UINT64 y = 0U;
    GM_UINT64 z = 0U;
	GM_UINT64 temp =0U ;
	int i = 0U;

	for(i = 0U; i < 8; ++i)
	{/*temp下面这一步骤很重要，括号不能变 应先把0xff变为无符号的数再移位，否则会出现高位被置1的情况*/
		temp = (GM_UINT64)(((GM_UINT64)0xFF) << (i*8U));
		z = x & temp;
		if (i < 4)
		{/*低位向高位变化*/
			temp = z << ((7U - 2U * (GM_UINT64)i)*8U);
			y = y + temp;
		}
		else
		{/*高位向地位变化*/
			temp = z >> ((2U * (GM_UINT64)i - 7U)*8U);
			y = y + temp;
		}
	}

    return y;
}

/*
*
*
*
*
*
*
*/
GM_BOOL GM_nByte_Endian_Transfer(GM_UINT8 * pData,GM_UINT8 byteNum)
{
	GM_UINT8 result[GM_UINT8_MAX] = {0};
	GM_UINT8 index = (GM_UINT8)0U;
	GM_UINT8 posoff = (GM_UINT8)0U;

	if ((pData == NULL)||(byteNum <= (GM_UINT8)1U))
	{
		return GM_FALSE;
	}

	for(; index < byteNum; ++index)
	{
		posoff = byteNum - index - (GM_UINT8)1;
		result[index] = *(pData + posoff);
	}

	GM_memcpy((void*)pData, (const void*)result, (size_t)byteNum);

	return GM_TRUE;
}

