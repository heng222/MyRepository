/**
* @file GM_Memncomp.c
* @brief
* @author 
* @date 
* @version


*/
#include "GM_Memncomp.h"

/**
* @brief GM_memncomp
*
* �����������������ݽ��бȽ�. ���ֽ� ��λ�Ƚ�
* @param[in] pBufA
* @param[in] pBufB
* @param[in] size
* @return GM_INT16 
* ���� 0��ʾ pBufA = pBufB
* ���� -1��ʾ pBufA < pBufB
* ���� 1��ʾ pBufA > pBufB
* ����-256 ��ʾ�����pBufA��pBufB == NULL��size==0
*/
GM_INT16 GM_memncomp(const GM_UINT8* pBufA, const GM_UINT8* pBufB, size_t size)
{
    size_t i = 0U;

	if ((NULL == pBufA) || (NULL == pBufB) || (size == (size_t)0))
    {
        return -256;
    }

    for (i = (size_t)0u; i < size; ++i)
    {
        if (*(pBufA + i) > *(pBufB + i))
        {
            return 1;
        }
		
		if(*(pBufA + i) < *(pBufB + i))
		{
			return -1;
		}
    }

	return 0;
}

	/**
* @brief GM_memcmp
*
* �����������������ݽ��бȽ�.����ϵͳ�� memcmp����
* @param[in] pBufA
* @param[in] pBufB
* @param[in] size
* @return GM_INT32 
* ����ֵ��memcmp�����ķ���ֵ�������һ�����������ڣ�����-256 ��ʾ�����pBufA��pBufB == NULL��size==0
*/
GM_INT32 GM_memcmp(const void* pBufA, const void* pBufB, size_t size)
{
	if ((pBufA == NULL)||(pBufB == NULL) || (size == (size_t)0))
	{
		return (GM_INT32)-256;
	}

	return (GM_INT32)memcmp(pBufA, pBufB, size);

}
