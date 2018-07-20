/**
 * Copyright(C) 
 * 
 * @file:GM_Utils_Other.c
 * @brief:
 * @auther:
 * @create date:

 */


#include "GM_Utils_Other.h"

/*
int GM_Get_Random_Number(void)
{
    int ran = 0;
#ifdef WIN32
    ran = rand();
#endif

#ifdef QNX
	ran = random();
#endif

#ifdef VXWORKS
#ifdef VXWORKS5_5
	ran = random();
#endif
#ifdef VXWORKS6_6
	ran = rand();
#endif

#endif
    return ran;
}
*/


/**
* @brief GM_IsHexNumber
*
* �ж��Ƿ���ʮ����������.
* @param[in] pBuf
* @param[in] bufSize
* @return GM_BOOL
*/
GM_BOOL GM_IsHexNumber(const char* pBuf, GM_UINT32 bufSize)
{
    GM_UINT32 i = 0U;

    if ((NULL == pBuf) || ((GM_UINT32)0U == (GM_UINT32)bufSize))
    {
        return GM_FALSE;
    }

    for (i = (GM_UINT32)0u; i < bufSize; ++i)
    {
        if ((('0' > *(pBuf+i)) || ('9' < *(pBuf+i)))
            && (('A' > *(pBuf+i)) || ('F' < *(pBuf+i)))
            && (('a' > *(pBuf+i)) || ('f' < *(pBuf+i))))
        {
            return GM_FALSE;
        }
    }

    return GM_TRUE;
}


/**
* @brief GM_IsNumber
*
* �ж��Ƿ���ʮ��������.
* @param[in] pBuf
* @param[in] bufSize
* @return GM_BOOL
*/
GM_BOOL GM_IsNumber(const char *pBuf, GM_UINT32 bufSize)
{
    GM_UINT32 i = 0U;

    if ((NULL == pBuf) || ((GM_UINT32)0U == (GM_UINT32)bufSize))
    {
        return GM_FALSE;
    }

    for (i = (GM_UINT32)0u; i < bufSize; ++i)
    {
        if (('0' > *(pBuf+i)) || ('9' < *(pBuf+i)))
        {
            return GM_FALSE;
        }
    }

    return GM_TRUE;
}

/* @brief GM_atoi
*
* �ַ���ת���������ķ�װ����ת�������ַ�Χ[-2147483648��2147483647]
* @param[in] pBuf Ҫת�����ַ���
* @param[in] bufSize Ҫת�����ַ�������
* @param[out] pVal ת�����ֵ
* @return GM_BOOL ת���Ƿ�ɹ�
*/
GM_BOOL GM_atoui(const char* pBuf, GM_UINT32 bufSize, unsigned int* pVal)
{
	GM_UINT32 i     = 0U;
	int cmpRt = 0;

	if ((NULL == pVal) || (NULL == pBuf) || ((GM_UINT32)0U == (GM_UINT32)bufSize))
	{
		return GM_FALSE;
	}

	*pVal = 0U;
	for (i = (GM_UINT32)0u; i < bufSize; ++i)
	{
		if ('\0' == *(pBuf + i))
		{
			bufSize = i;
		}
	}

	if ((GM_UINT32)0U == (GM_UINT32)bufSize)
	{
		return GM_FALSE;
	}

	if ((GM_UINT32)bufSize > (GM_UINT32)10U)
	{/*ֻ�з���λ�� λ������ 4294967295*/
		return GM_FALSE;
	}
	if ((GM_UINT32)bufSize == (GM_UINT32)10U)
	{
		cmpRt = strncmp(pBuf, "4294967295", 10);
	}

	for (i = (GM_UINT32)0u; i < bufSize; ++i)
	{
		if ((*(pBuf + i) < '0') || (*(pBuf + i) > '9'))
		{
			return GM_FALSE;
		}
	}

	if (cmpRt > 0)
	{
		return GM_FALSE;
	}
#ifdef Platform_2oo3
	return GM_FALSE;
#else
	*pVal = (unsigned int)strtoul(pBuf, NULL, 10);
	return GM_TRUE;
#endif

}
/*�����ַ������жϣ����ų�*/

/**
* @brief GM_atoui
*
* �ַ���ת���������ķ�װ����ת�������ַ�Χ[0��4294967295]
* @param[in] pBuf Ҫת�����ַ���
* @param[in] bufSize Ҫת�����ַ�������
* @param[out] pVal ת�����ֵ
* @return GM_BOOL ת���Ƿ�ɹ�
*/
GM_BOOL GM_atoi(const char* pBuf, GM_UINT32 bufSize, int* pVal)
{
    GM_UINT32 i     = 0U;
    GM_BOOL Bnegtive = GM_FALSE;
	int cmpRt = 0;

    if ((NULL == pVal) || (NULL == pBuf) || ((GM_UINT32)0U == (GM_UINT32)bufSize))
    {
        return GM_FALSE;
    }

	*pVal = 0;
    for (i = (GM_UINT32)0u; i < bufSize; ++i)
    {
        if ('\0' == *(pBuf + i))
        {
            bufSize = i;
        }
    }

	if ((GM_UINT32)0U == (GM_UINT32)bufSize)
	{
		return GM_FALSE;
	}
    /** @brief �ж����������Ǹ��� */
    if ('-' == *pBuf)
    {
        Bnegtive = GM_TRUE;
    }

    if (GM_TRUE == Bnegtive)/*�Ǹ���*/
    {
        if (((GM_UINT32)1U == (GM_UINT32)bufSize)||((GM_UINT32)bufSize > (GM_UINT32)11U))
		{/*ֻ�з���λ�� λ������ -2147483648*/
            return GM_FALSE;
        }
		if ((GM_UINT32)bufSize == (GM_UINT32)11U)
		{
			cmpRt = strncmp(pBuf, "-2147483648", 11);
		}


        for (i = (GM_UINT32)1u; i < bufSize; ++i)
        {
            if ((*(pBuf + i) < '0') || (*(pBuf + i) > '9'))
            {
                return GM_FALSE;
            }
        }
    }
    else
    {
		if ((GM_UINT32)bufSize > (GM_UINT32)10U)
		{/*λ������ 2147483647*/
			return GM_FALSE;
		}
		if ((GM_UINT32)bufSize == (GM_UINT32)10U)
		{/*��2147483647���Ƚϣ�wtt�޸�2011-11-30*/
			cmpRt = strncmp(pBuf, "2147483647", 10);
		}

		for (i = (GM_UINT32)0u; i < bufSize; ++i)
        {
            if ((*(pBuf + i) < '0') || (*(pBuf + i) > '9'))
            {
                return GM_FALSE;
            }
        }
	}

	if (cmpRt > 0)
	{
		return GM_FALSE;
	}
#ifdef Platform_2oo3
	return GM_FALSE;
#else
	*pVal = (int)strtol(pBuf, NULL, 10);
	/*	*pVal = atoi(pBuf); �����Ϊstrtol������atoi���ݲ�ͬ����ϵͳ�����������ڳ�����Χʱ��õ���ͬ��� wtt 20111116*/
	return GM_TRUE;
#endif
}

/**
* @brief GM_Log_Msg
*
* ��װ��logMsg.
* @param[in] fmt
* @param[in] arg1
* @param[in] arg2
* @param[in] arg3
* @param[in] arg4
* @param[in] arg5
* @param[in] arg6
*/
#if(LOG_LEVEL >= -10)/*��-10��-1��ɿɶ����level�ȼ���GM������С��0���û��������*/
void GM_Log_Msg(
    int level,
    const char* fmt,  /* format string for print */
    int    arg1, /* first of six required args for fmt */
    int    arg2,
    int    arg3,
    int    arg4,
    int    arg5,
    int    arg6
)
{
    if (level <= LOG_LEVEL)
    {
#ifdef VXWORKS
        logMsg(
            fmt,
            arg1,
            arg2,
            arg3,
            arg4,
            arg5,
            arg6
        );
#endif

#ifdef WIN32
#ifndef NO_PRINTF
        printf(
            fmt,
            arg1,
            arg2,
            arg3,
            arg4,
            arg5,
            arg6
        );
#endif

    if (level <= -4)
    GM_OutputDebugString(
        fmt,  /* format string for print */
        arg1, /* first of six required args for fmt */
        arg2,
        arg3,
        arg4,
        arg5,
        arg6
    );

#endif
#ifdef QNX
#ifndef NO_PRINTF
        printf(
            fmt,
            arg1,
            arg2,
            arg3,
            arg4,
            arg5,
            arg6
        );
#endif
#endif
    }

    return;
}
#endif
	
/**
* @name:GM_Log_String
* 
* @param[in]:const GM_UINT8* buf
* @param[in]:GM_UINT16 size
* @return:void
* @modify info:2012��12��6��  By wtt
**/
void GM_Log_String(const GM_UINT8* buf, GM_UINT16 size)
{
    GM_UINT16 i = 0U;

	if (NULL == buf)
	{
		return;
	}

    for (i = (GM_UINT16)0; i < size; ++i)
    {
        GM_Log_Msg(0, "%x ", (int)(*(buf+i)), 0, 0, 0, 0, 0);
    }

    GM_Log_Msg(0, "\n", 0, 0, 0, 0, 0, 0);

    return;
}


void GM_OutputDebugString(char *format, ...)
{

    return;
}

void GM_Log_Err(unsigned int errNo, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
	return;
}

void GM_Log_Usr(unsigned int errNo, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
	return;
}
