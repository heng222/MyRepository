/**
 * Copyright(C) 2012
 * 
 * @file:GM_Utils_Other.h
 * @brief:
 * @auther:
 * @create date:

 */


#ifndef _GM_UTILS_OTHER_H
#define _GM_UTILS_OTHER_H

#include "../GM_Define.h"
#include "GM_Utils_Base.h"

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */


    /**
    * @brief GM_Get_Random_Number
    *
    * �õ���������Բ�ͬ����ϵͳrandom�����ķ�װ
    * @return int
    */
 /*   int GM_Get_Random_Number(void);*/

    /**
    * @brief GM_IsHexNumber
    *
    * �ж��Ƿ���ʮ����������.
    * @param[in] pBuf
    * @param[in] bufSize
    * @return GM_BOOL
    */
    GM_BOOL GM_IsHexNumber(const char* pBuf, GM_UINT32 bufSize);

    /**
    * @brief GM_IsNumber
    *
    * �ж��Ƿ���ʮ��������.
    * @param[in] pBuf
    * @param[in] bufSize
    * @return GM_BOOL
    */
    GM_BOOL GM_IsNumber(const char *pBuf, GM_UINT32 bufSize);

    /**
    * @brief GM_atoi
    *
    * �ַ���ת���������ķ�װ����ת�������ַ�Χ[-2147483648��2147483647]
    * @param[in] pBuf Ҫת�����ַ���
    * @param[in] bufSize Ҫת�����ַ�������
    * @param[out] pVal ת�����ֵ
    * @return GM_BOOL ת���Ƿ�ɹ�
    */
    GM_BOOL GM_atoi(const char* pBuf, GM_UINT32 bufSize, int* pVal);

	/**
    * @brief GM_atoui
    *
    * �ַ���ת���������ķ�װ����ת�������ַ�Χ[0��4294967295]
    * @param[in] pBuf Ҫת�����ַ���
    * @param[in] bufSize Ҫת�����ַ�������
    * @param[out] pVal ת�����ֵ
    * @return GM_BOOL ת���Ƿ�ɹ�
    */
    GM_BOOL GM_atoui(const char* pBuf, GM_UINT32 bufSize, unsigned int* pVal);

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
#if(LOG_LEVEL < -10)/*��-10��-1��ɿɶ����level�ȼ���GM������С��0���û��������*/
#define GM_Log_Msg(X,Y,Z1,Z2,Z3,Z4,Z5,Z6) NULL
#else
    void GM_Log_Msg(int level, const char* fmt, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
#endif
    
	
/**
* @name:GM_Log_String
* 
* @param[in]:const GM_UINT8* buf
* @param[in]:GM_UINT16 size
* @return:void
* @modify info:2012��12��6��  By wtt
**/
	void GM_Log_String(const GM_UINT8* buf, GM_UINT16 size);


    void GM_OutputDebugString(char *format, ...);

	/**
    * @brief GM_Log_Err
    *
    * GM�ڲ�����ص�����.
	* @param[in] errNo
    * @param[in] fmt
    * @param[in] arg1
    * @param[in] arg2
	* @param[in] arg3
	* @param[in] arg4
	* @param[in] arg5
	* @param[in] arg6
	*/
	void GM_Log_Err(unsigned int errNo, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);

	/**
    * @brief GM_Log_Usr
    *
    * GM�ڲ�����ص�����.
	* @param[in] errNo
    * @param[in] fmt
    * @param[in] arg1
    * @param[in] arg2
	* @param[in] arg3
	* @param[in] arg4
	* @param[in] arg5
	* @param[in] arg6
	*/
	void GM_Log_Usr(unsigned int errNo, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);



#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_UTILS_BASE_H */

