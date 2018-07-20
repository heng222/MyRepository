/**
* @file GM_PD.c
* @brief 通过查表法实现PD运算，主要用于生成校核字
* @author 
* @date 
* @version

*/
#include "GM_PD.h"


static GM_UINT32 GM_PD(GM_BOOL isAlgorithmA, GM_UINT32 data)
{
    register GM_UINT32 result = 0U;
    register GM_UINT32 temp1  = (data & 0x007FFFFF) << 9;
    register GM_UINT32 temp2  = data >> 23;

    if (GM_TRUE == isAlgorithmA)
    {
        result = GM_PD_Channel1_Table[temp2] ^ temp1;
    }
    else
    {
        result = GM_PD_Channel2_Table[temp2] ^ temp1;
    }

    return result;
}

static GM_UINT32 GM_PD2(GM_UINT32 data, GM_UINT32 add_num)
{
    register GM_UINT32 result = data << 1;

    if ((GM_UINT32)0u != (data & 0x80000000))
    {
        result |= 0x00000001U;
    }

    result = ~(result ^(~add_num));

    return result;
}

static GM_UINT32 GM_PD_Converse(GM_BOOL isAlgorithmA, GM_UINT32 data)
{
    int i       = 0;
    register GM_UINT32 result = data;
    GM_UINT32 temp = 0U;

    for (i = 0; i < 9; ++i)
    {
        temp = result & (GM_UINT32)0x00000001;

        if ((GM_UINT32)1U == (GM_UINT32)temp)
        {
            result = (result >> 1U) | 0x80000000U;
        }
        else
        {
            if (GM_TRUE == isAlgorithmA)
            {
                result = ((~result) ^ GM_PD_CRC_CHANEL_1) >> 1U;
            }
            else
            {
                result = ((~result) ^ GM_PD_CRC_CHANEL_2) >> 1U;
            }
        }
    }

    return result;
}

static GM_UINT32 GM_PD_Converse2(GM_UINT32 data, GM_UINT32 add_num)
{
    register GM_UINT32 result = (~data) ^(~add_num);
    GM_UINT32 temp = 0U;

    temp = result & (GM_UINT32)0x00000001;

    if ((GM_UINT32)1U == (GM_UINT32)temp)
    {
        result = (result >> 1U) | 0x80000000U;
    }
    else
    {
        result >>= 1U;
    }

    return result;
}
/*主程序中调用的PD运算函数*/
GM_BOOL GM_PD_Operation(GM_BOOL isAlgorithmA, GM_UINT32 VSN1, GM_UINT32 VSN2, GM_UINT32 *pPDPara, GM_UINT32 paraNum, GM_UINT32* pResult)
{
    register GM_UINT32 result = 0U;
    GM_UINT16 i               = 0U;
    GM_UINT32 tmpVSN          = 0U;

    if ((NULL == pPDPara) || (NULL == pResult) || ((GM_UINT32)0U == (GM_UINT32)paraNum) /**< 数组的大小不能为0 */)
    {
        return GM_FALSE;
    }

    /** @brief 如果采用算法A,则为算法A的VSN,否则为算法B的VSN */

    if (GM_TRUE == isAlgorithmA)
    {
        tmpVSN = VSN1;
    }
    else if (GM_FALSE == isAlgorithmA)
    {
        tmpVSN = VSN2;
    }
    else
    {
        return GM_FALSE;
    }

    result = GM_PD(isAlgorithmA, ~(tmpVSN ^(*pPDPara)));


    for (i = (GM_UINT16)1u; i < (GM_UINT16)paraNum; ++i)
    {
        ++pPDPara;
        result = GM_PD2(result, (tmpVSN ^(*pPDPara)));
        result = GM_PD(isAlgorithmA, result);
    }

    result = tmpVSN ^(~result);

    *pResult = result;

    return GM_TRUE;
}
GM_BOOL GM_PD_Operation2(GM_BOOL isAlgorithmA, GM_UINT32 VSN1, GM_UINT32 VSN2, GM_UINT32 *pPDPara, GM_UINT32 paraNum, GM_UINT32* pResult)
{
	register GM_UINT32 result = 0U;
	GM_UINT16 i               = 0U;
	GM_UINT32 tmpVSN          = 0U;

	if ((NULL == pPDPara) || (NULL == pResult) || ((GM_UINT32)0U == (GM_UINT32)paraNum) /**< 数组的大小不能为0 */)
	{
		return GM_FALSE;
	}

	/** @brief 如果采用算法A,则为算法A的VSN,否则为算法B的VSN */

	if (GM_TRUE == isAlgorithmA)
	{
		tmpVSN = VSN1;
	}
	else if (GM_FALSE == isAlgorithmA)
	{
		tmpVSN = VSN2;
	}
	else
	{
		return GM_FALSE;
	}

    result = ~(tmpVSN ^(*pPDPara));

	for (i = (GM_UINT16)1u; i < (GM_UINT16)paraNum; ++i)
	{
		++pPDPara;
		result = GM_PD2(result, (tmpVSN ^(*pPDPara)));
		result = GM_PD(isAlgorithmA, result);
	}

	result = tmpVSN ^(~result);

	*pResult = result;

	return GM_TRUE;
}
GM_BOOL GM_PD_Inverse(GM_BOOL isAlgorithmA, GM_UINT32 VSN1, GM_UINT32 VSN2, GM_UINT32 *pPDPara, GM_UINT32 paraNum, GM_UINT32* pResult)
{
    register GM_UINT32 result = 0U;
    GM_UINT32 i               = 0U;
    GM_UINT32 tmpVSN          = 0U;

    if ((NULL == pPDPara) || (NULL == pResult)|| ((GM_UINT32)0U == (GM_UINT32)paraNum))
    {
        return GM_FALSE;
    }

    /** @brief 如果采用算法A,则为算法A的VSN,否则为算法B的VSN */

    if (GM_TRUE == isAlgorithmA)
    {
        tmpVSN = VSN1;
    }
    else if (GM_FALSE == isAlgorithmA)
    {
        tmpVSN = VSN2;
    }
    else
    {
        return GM_FALSE;
    }

	result = GM_PD_Converse(isAlgorithmA, ~(tmpVSN ^(*pPDPara)));

    for (i = (GM_UINT32)1u; i < paraNum; ++i)
    {
        ++pPDPara;
        result = GM_PD_Converse2(result, (tmpVSN ^(*pPDPara)));
        result = GM_PD_Converse(isAlgorithmA, result);
    }

    result = tmpVSN ^(~result);

    *pResult = result;

    return GM_TRUE;
}

/*
测试用, 通过data算出的PD值存放到data1中的第一个值中，然后对data1进行逆运算,正好得到data中的第一个值
int main()
{
    GM_UINT32 data[4] = {100, 0x0264c013, 0x24480120, 0xd3f8bee5};
    GM_UINT32 data1[4] = {0, 0xd3f8bee5, 0x24480120, 0x0264c013};
    GM_UINT32 r;

    GM_PD_Operation(1, data, 4, data1);

    GM_PD_Inverse(1, data1, 4, &r);

    printf("%x, %d", data1[0], r);
}
*/

