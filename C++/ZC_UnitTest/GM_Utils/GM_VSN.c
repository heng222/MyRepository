/**
* @file GM_VSN.c
* @brief
* @author 
* @date 
* @version

*/

#include "GM_VSN.h"

#define GM_VSN_POST1 (0xC6C272F5U) /* (M01 ^ M11) + POST1 = 0xAAAAAAAA */
#define GM_VSN_POST2 (0x42215AACU) /* (M12 ^ M02) + POST2 = 0x77777777 */

typedef struct
{
    GM_UINT32 VSN0;
    GM_UINT32 VSN1;
    GM_UINT32 VSN2;
    GM_UINT32 VSNSeed1;
    GM_UINT32 VSNSeed2;
    GM_UINT32 oldVSN1;
    GM_UINT32 oldVSN2;
    GM_LFSR   channel1;
    GM_LFSR   channel2;
}GM_PACKED GM_VSN_Struct;/*原GM_VSN的结构，无VSNID*/

typedef struct
{
	GM_UINT8  VSNID;	/*每套VSN的唯一标志*/
	GM_UINT32 VSN0;
	GM_UINT32 VSN1;
	GM_UINT32 VSN2;
}GM_PACKED GM_VSN_Info_Struct;/*新GM_VSN的结构，增加VSNID，不需要OLDVSN VSNSeed Channel */

typedef struct
{
	GM_UINT8			 VSN_Num;
	GM_VSN_Info_Struct   VSNArry[GM_VSN_MAX];
}GM_PACKED GM_VSN_Mgr_Struct;

static const GM_VSN_Struct GM_VSN_Ini0 =
{
	0x0, 0x0, 0x0, GM_VSN_SEED1, GM_VSN_SEED2, 0x0, 0x0, {0x00, NULL, NULL}, {0x00, NULL, NULL}
};
/*管理新增加的4套GM_VSN*/
static GM_VSN_Mgr_Struct sGM_VSN_Mgr = {0};
/*原GM_VSN*/
static GM_VSN_Struct	 GM_VSN_Info;

GM_BOOL GM_VSN_Init(void)
{
    GM_BOOL rt = GM_FALSE;

	GM_memcpy((void*)(&GM_VSN_Info), (void*)(&GM_VSN_Ini0),(size_t)sizeof(GM_VSN_Info));

    rt = GM_LFSR_Init((GM_LFSR*)(&(GM_VSN_Info.channel1)), GM_LFSR_LEFT_CHN1_TABLE, GM_LFSR_RIGHT_CHN1_TABLE);

    if ((GM_BOOL)GM_FALSE == (GM_BOOL)rt)
    {
        return GM_FALSE;
    }

    rt = GM_LFSR_Init((GM_LFSR*)(&(GM_VSN_Info.channel2)), GM_LFSR_LEFT_CHN2_TABLE, GM_LFSR_RIGHT_CHN2_TABLE);

    if ((GM_BOOL)GM_FALSE == (GM_BOOL)rt)
    {
        return GM_FALSE;
    }

    GM_VSN_Info.VSN0 = (GM_UINT32)0U;

    GM_VSN_Info.VSN1 = (GM_UINT32)GM_VSN_M01;

    GM_VSN_Info.VSN2 = (GM_UINT32)GM_VSN_M02;

    GM_VSN_Info.VSN1 ^= GM_VSN_Info.VSNSeed1;

    GM_VSN_Info.VSN2 ^= GM_VSN_Info.VSNSeed2;

    return GM_TRUE;
}

void GM_VSN_Update(void)
{
	GM_UINT32 temp = 0U;

    ++GM_VSN_Info.VSN0;
    GM_VSN_Info.oldVSN1 = GM_VSN_Info.VSN1;
    GM_VSN_Info.oldVSN2 = GM_VSN_Info.VSN2;

    GM_LFSR_Load((GM_LFSR*)(&(GM_VSN_Info.channel1)), (GM_UINT32)(GM_VSN_Info.VSN1 ^ (GM_UINT32)GM_VSN_M01));

    GM_LFSR_Add((GM_LFSR*)(&(GM_VSN_Info.channel1)), (GM_UINT32)0u);

    /*GM_LFSR_Read((GM_LFSR*)(&(GM_VSN_Info.channel1)), (GM_UINT32*)(&(GM_VSN_Info.VSN1)));*/
	GM_LFSR_Read((GM_LFSR*)(&(GM_VSN_Info.channel1)), &temp);
	GM_VSN_Info.VSN1 = temp;

    GM_VSN_Info.VSN1 ^= (GM_UINT32)(GM_VSN_M01);

    GM_LFSR_Load((GM_LFSR*)(&(GM_VSN_Info.channel2)), (GM_UINT32)(GM_VSN_Info.VSN2 ^ (GM_UINT32)GM_VSN_M02));

    GM_LFSR_Add((GM_LFSR*)(&(GM_VSN_Info.channel2)), (GM_UINT32)0u);

    GM_LFSR_Read((GM_LFSR*)(&(GM_VSN_Info.channel2)), &temp);
	GM_VSN_Info.VSN2 = temp;

    GM_VSN_Info.VSN2 ^= (GM_UINT32)GM_VSN_M02;

    return;
}

void GM_VSN_Get(GM_UINT32* pVSN0, GM_UINT32* pVSN1, GM_UINT32* pVSN2)
{
    if ((NULL == pVSN0) || (NULL == pVSN1) || (NULL == pVSN2))
    {
        return;
    }

    *pVSN0 = GM_VSN_Info.VSN0;

    *pVSN1 = GM_VSN_Info.VSN1;
    *pVSN2 = GM_VSN_Info.VSN2;

    return;
}

GM_BOOL GM_VSN_Get_Old(GM_UINT32* pVSN0, GM_UINT32* pVSN1, GM_UINT32* pVSN2)
{
    if ((NULL == pVSN0)
		|| (NULL == pVSN1)
		|| (NULL == pVSN2)
		|| ((GM_UINT32)0U == GM_VSN_Info.VSN0))
    {
        return GM_FALSE;
    }

    *pVSN0 = GM_VSN_Info.VSN0 - (GM_UINT32)1u;

    *pVSN1 = GM_VSN_Info.oldVSN1;
    *pVSN2 = GM_VSN_Info.oldVSN2;

    return GM_TRUE;
}

void GM_VSN_Set(GM_UINT32 VSN0, GM_UINT32 VSN1, GM_UINT32 VSN2)
{
    GM_VSN_Info.VSN0 = VSN0;
    GM_VSN_Info.VSN1 = VSN1;
    GM_VSN_Info.VSN2 = VSN2;

    return;
}

void GM_VSN_Set_Old(GM_UINT32 VSN1, GM_UINT32 VSN2)
{
    GM_VSN_Info.oldVSN1 = VSN1;
    GM_VSN_Info.oldVSN2 = VSN2;

    return;
}

GM_BOOL GM_VSN_Cal_Check_Word_VSN1(GM_UINT32 VSN1, GM_UINT32 otherVSN1, GM_UINT32* pCHKW)
{
    GM_UINT32 val = VSN1 ^ otherVSN1;

    if (NULL == pCHKW)
    {
        return GM_FALSE;
    }

    GM_LFSR_Load((GM_LFSR*)(&(GM_VSN_Info.channel1)), val);

    GM_LFSR_Add((GM_LFSR*)(&(GM_VSN_Info.channel1)), (GM_UINT32)GM_VSN_POST1);

    GM_LFSR_Read((GM_LFSR*)(&(GM_VSN_Info.channel1)), pCHKW);

    if (GM_VSN1_CHECK_WORD == *pCHKW)
    {
        return GM_TRUE;
    }
    else
    {
        return GM_FALSE;
    }
}

GM_BOOL GM_VSN_Cal_Check_Word_VSN2(GM_UINT32 VSN2, GM_UINT32 otherVSN2, GM_UINT32* pCHKW)
{
    GM_UINT32 val = VSN2 ^ otherVSN2;

    if (NULL == pCHKW)
    {
        return GM_FALSE;
    }

    GM_LFSR_Load((GM_LFSR*)(&(GM_VSN_Info.channel2)), val);

    GM_LFSR_Add(((GM_LFSR*)(&(GM_VSN_Info.channel2))), ((GM_UINT32)GM_VSN_POST2));

    GM_LFSR_Read((GM_LFSR*)(&(GM_VSN_Info.channel2)), pCHKW);

    if (GM_VSN2_CHECK_WORD == *pCHKW)
    {
        return GM_TRUE;
    }
    else
    {
        return GM_FALSE;
    }
}

GM_BOOL GM_VSN_Add(GM_UINT8 VSNID)
{
	GM_UINT8 i = 0U;

	if (0U == VSNID)
	{
		return GM_FALSE;
	}
	/*judge if the input VSNID has existed*/
	for (i=0U; i< sGM_VSN_Mgr.VSN_Num ; ++i)
	{
		if (VSNID == sGM_VSN_Mgr.VSNArry[i].VSNID)
		{
			return GM_FALSE;
		}
	}
	/*judge if the VSN_Num is too large */
	if (sGM_VSN_Mgr.VSN_Num == GM_VSN_MAX)
	{
		return GM_FALSE;
	}
	else
	{
		/*initial the new VSN of input VSNID*/
		sGM_VSN_Mgr.VSNArry[sGM_VSN_Mgr.VSN_Num].VSNID = VSNID;
		(sGM_VSN_Mgr.VSNArry[sGM_VSN_Mgr.VSN_Num]).VSN0 = (GM_UINT32)0U;
		(sGM_VSN_Mgr.VSNArry[sGM_VSN_Mgr.VSN_Num]).VSN1 = (GM_UINT32)GM_VSN_M01;
		(sGM_VSN_Mgr.VSNArry[sGM_VSN_Mgr.VSN_Num]).VSN2 = (GM_UINT32)GM_VSN_M02;
		(sGM_VSN_Mgr.VSNArry[sGM_VSN_Mgr.VSN_Num]).VSN1 ^= GM_VSN_SEED1;
		(sGM_VSN_Mgr.VSNArry[sGM_VSN_Mgr.VSN_Num]).VSN2 ^= GM_VSN_SEED2;

		++sGM_VSN_Mgr.VSN_Num;
		return GM_TRUE;
	}
}
GM_BOOL GM_VSN_Update_S(GM_UINT8 VSNID)
{
	GM_UINT32 temp = 0U;
	GM_UINT8 i = 0U;

	if (0U == VSNID)
	{/*if input 0, means update the GM_VSN_Info*/
		GM_VSN_Update();
		return GM_TRUE;
	}

	/*search the input VSNID*/
	for (i=0U; i< sGM_VSN_Mgr.VSN_Num; ++i)
	{
		if (VSNID == sGM_VSN_Mgr.VSNArry[i].VSNID)
		{
			break;
		}
	}

	if (i == sGM_VSN_Mgr.VSN_Num)
	{
		return GM_FALSE;
	}

	/*update the sGM_VSN_Mgr.VSNArry[i].VSN*/
	++(sGM_VSN_Mgr.VSNArry[i].VSN0);

	GM_LFSR_Load((GM_LFSR*)(&(GM_VSN_Info.channel1)), (GM_UINT32)(sGM_VSN_Mgr.VSNArry[i].VSN1 ^ (GM_UINT32)GM_VSN_M01));

	GM_LFSR_Add((GM_LFSR*)(&(GM_VSN_Info.channel1)), (GM_UINT32)0u);

	GM_LFSR_Read((GM_LFSR*)(&(GM_VSN_Info.channel1)), &temp);
	sGM_VSN_Mgr.VSNArry[i].VSN1 = temp;

	sGM_VSN_Mgr.VSNArry[i].VSN1 ^= (GM_UINT32)(GM_VSN_M01);

	GM_LFSR_Load((GM_LFSR*)(&(GM_VSN_Info.channel2)), (GM_UINT32)(sGM_VSN_Mgr.VSNArry[i].VSN2 ^ (GM_UINT32)GM_VSN_M02));

	GM_LFSR_Add((GM_LFSR*)(&(GM_VSN_Info.channel2)), (GM_UINT32)0u);

	GM_LFSR_Read((GM_LFSR*)(&(GM_VSN_Info.channel2)), &temp);

	sGM_VSN_Mgr.VSNArry[i].VSN2 = temp;

	sGM_VSN_Mgr.VSNArry[i].VSN2 ^= (GM_UINT32)GM_VSN_M02;

	return GM_TRUE;
}
GM_BOOL GM_VSN_Get_S(GM_UINT8 VSNID, GM_UINT32* pVSN0, GM_UINT32* pVSN1, GM_UINT32* pVSN2)
{
	GM_UINT8 i = 0U;

	if ((NULL == pVSN0) || (NULL == pVSN1) || (NULL == pVSN2))
	{
		return GM_FALSE;
	}

	if (0U == VSNID)
	{/*if input 0, means get the GM_VSN_Info*/
		GM_VSN_Get(pVSN0, pVSN1, pVSN2);
		return GM_TRUE;
	}

	/*search the input VSNID*/
	for (i=0U; i< sGM_VSN_Mgr.VSN_Num; ++i)
	{
		if (VSNID == sGM_VSN_Mgr.VSNArry[i].VSNID)
		{
			break;
		}
	}

	if (i == sGM_VSN_Mgr.VSN_Num)
	{
		return GM_FALSE;
	}

	*pVSN0 = sGM_VSN_Mgr.VSNArry[i].VSN0;
	*pVSN1 = sGM_VSN_Mgr.VSNArry[i].VSN1;
	*pVSN2 = sGM_VSN_Mgr.VSNArry[i].VSN2;

	return GM_TRUE;
}


/** @brief 测试
上模块:
1 0x8bceedbe 0xcfafd011
2 0xed6b0631 0xe1f49564

下模块:
1 0x1e9facab 0xd8bcd541
2 0x783a4724 0xf6e79034


void main()
{
    GM_UINT32 CHKW;
    GM_BOOL rt;
    GM_VSN_Init();

    rt = GM_VSN_Cal_Check_Word_VSN1(0x8bceedbe, 0x1e9facab, &CHKW);

    rt = GM_VSN_Cal_Check_Word_VSN2(0xcfafd011, 0xd8bcd541, &CHKW);

    rt = GM_VSN_Cal_Check_Word_VSN1(0xed6b0631, 0x783a4724, &CHKW);

    rt = GM_VSN_Cal_Check_Word_VSN2(0xe1f49564, 0xf6e79034, &CHKW);

    return;
}
*/

