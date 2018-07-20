/**
* @file GM_LFSR.c
* @brief 采用小端编码
* @author 
* @date 
* @version
* <pre><b>copyright: 

*/

#include "GM_LFSR.h"

/**
* @brief FSFB_LFSR_LShift
*
* 快速左移运算.
* @param[in] This LFSR运算中间数据结构
* @return GM_BOOL
*/
static GM_BOOL GM_LFSR_LShift(GM_LFSR* This)
{
    int i           = 0;
    GM_UINT32 nTmp = 0U;

    if (NULL == This)
    {
        return GM_FALSE;
    }

    for (i = 0U; i < 4U; ++i)
    {
        nTmp = ((This->reg) & 0xFF000000U) >> 24U;
        This->reg <<= 8U;
        This->reg ^= This->leftTable[nTmp];
    }

    return GM_TRUE;
}

/**
* @brief FSFB_LFSR_RShift
*
* 快速右移运算.
* @param[in] This LFSR运算中间数据结构
* @return GM_BOOL
*/
static GM_BOOL GM_LFSR_RShift(GM_LFSR* This)
{
    int i           = 0;
    GM_UINT32 nTmp = 0U;

    if (NULL == This)
    {
        return GM_FALSE;
    }

    for (i = 0; i < 4; ++i)
    {
        nTmp = (This->reg) & 0xFFU;
        This->reg >>= 8U;
        This->reg ^= This->rightTable[nTmp];
    }

    return GM_TRUE;
}
/**
* @brief GM_LFSR_Init
*
* 初始化LFSR运算中间数据结构.
* @param[in] This LFSR运算中间数据结构
* @param[in] pLeftTable 左移运算表
* @param[in] pRightTable 右移运算表
* @return GM_BOOL
*/
GM_BOOL GM_LFSR_Init(GM_LFSR* This, const GM_UINT32* pLeftTable, const GM_UINT32* pRightTable)
{
    if ((NULL == This) || (NULL == pLeftTable) || (NULL == pRightTable))
    {
        return GM_FALSE;
    }

    This->leftTable  = pLeftTable;

    This->rightTable = pRightTable;
    This->reg        = 0U;

    return GM_TRUE;
}

/**
 * @brief GM_LFSR_Load
 *
 * 加载进行LFSR运算的数据.
 * @param[in] This LFSR运算中间数据结构
 * @param[in] data 运算数据
 * @return GM_BOOL
 */
GM_BOOL GM_LFSR_Load(GM_LFSR* This, GM_UINT32 data)
{
    if (NULL == This)
    {
        return GM_FALSE;
    }

    This->reg = data;

    return GM_TRUE;
}

/**
  * @brief GM_LFSR_Read
  *
  * 获取运算结果.
  * @param[in] This LFSR运算中间数据结构
  * @param[out] pData 寄存器中的值
  * @return GM_BOOL
  */
GM_BOOL GM_LFSR_Read(GM_LFSR* This, GM_UINT32* pData)
{
    if ((NULL == This) || (NULL == pData))
    {
        return GM_FALSE;
    }

    *pData = This->reg;

    return GM_TRUE;
}

/**
  * @brief GM_LFSR_Add
  *
  * 进行Add运算.
  * @param[in] This LFSR运算中间数据结构
  * @param[in] data 运算数据
  * @return GM_BOOL
  */
GM_BOOL GM_LFSR_Add(GM_LFSR* This, GM_UINT32 data)
{
    GM_BOOL rt = GM_FALSE;

    if (NULL == This)
    {
        return GM_FALSE;
    }

    /** @brief 先异或 */
    This->reg ^= data;

    /** @brief 再左移 */
    rt = GM_LFSR_LShift(This);

    return rt;
}

/**
* @brief GM_LFSR_Sub
*
* 进行Sub运算.
* @param[in] This LFSR运算中间数据结构
* @param[in] data 运算数据
* @return GM_BOOL
*/
GM_BOOL GM_LFSR_Sub(GM_LFSR* This, GM_UINT32 data)
{
    GM_BOOL rt = GM_FALSE;

    if (NULL == This)
    {
        return GM_FALSE;
    }

    rt = GM_LFSR_RShift(This);

    if (GM_FALSE == rt)
    {
        return GM_FALSE;
    }

    This->reg ^= data;

    return GM_TRUE;
}

/**
* @brief GM_LFSR_Post
*
* 进行Post运算.
* @param[in] This LFSR运算中间数据结构
* @param[in] data 运算数据
* @return GM_BOOL
*/
GM_BOOL GM_LFSR_Post(GM_LFSR* This, GM_UINT32 data)
{
    GM_UINT32 temp = 0U;
    GM_BOOL rt     = GM_FALSE;

    if (NULL == This)
    {
        return GM_FALSE;
    }

    temp = This->reg;

    This->reg = data;

    rt = GM_LFSR_RShift(This);

    if (GM_FALSE == rt)
    {
        return GM_FALSE;
    }

    This->reg ^= temp;

    return GM_TRUE;
}

/**
* @brief GM_LFSR_Xor
*
* 进行Xor运算.
* @param[in] This LFSR运算中间数据结构
* @param[in] data 运算数据
* @return GM_BOOL
*/
GM_BOOL GM_LFSR_Xor(GM_LFSR* This, GM_UINT32 data)
{
    if (NULL == This)
    {
        return GM_FALSE;
    }

    This->reg ^= data;

    return GM_TRUE;
}

