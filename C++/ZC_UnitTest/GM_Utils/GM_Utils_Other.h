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
    * 得到随机数，对不同操作系统random函数的封装
    * @return int
    */
 /*   int GM_Get_Random_Number(void);*/

    /**
    * @brief GM_IsHexNumber
    *
    * 判断是否是十六进制数字.
    * @param[in] pBuf
    * @param[in] bufSize
    * @return GM_BOOL
    */
    GM_BOOL GM_IsHexNumber(const char* pBuf, GM_UINT32 bufSize);

    /**
    * @brief GM_IsNumber
    *
    * 判断是否是十进制数字.
    * @param[in] pBuf
    * @param[in] bufSize
    * @return GM_BOOL
    */
    GM_BOOL GM_IsNumber(const char *pBuf, GM_UINT32 bufSize);

    /**
    * @brief GM_atoi
    *
    * 字符串转换成整数的封装，可转换的数字范围[-2147483648，2147483647]
    * @param[in] pBuf 要转换的字符串
    * @param[in] bufSize 要转换的字符串长度
    * @param[out] pVal 转换后的值
    * @return GM_BOOL 转换是否成功
    */
    GM_BOOL GM_atoi(const char* pBuf, GM_UINT32 bufSize, int* pVal);

	/**
    * @brief GM_atoui
    *
    * 字符串转换成整数的封装，可转换的数字范围[0，4294967295]
    * @param[in] pBuf 要转换的字符串
    * @param[in] bufSize 要转换的字符串长度
    * @param[out] pVal 转换后的值
    * @return GM_BOOL 转换是否成功
    */
    GM_BOOL GM_atoui(const char* pBuf, GM_UINT32 bufSize, unsigned int* pVal);

    /**
    * @brief GM_Log_Msg
    *
    * 封装了logMsg.
    * @param[in] fmt
    * @param[in] arg1
    * @param[in] arg2
    * @param[in] arg3
    * @param[in] arg4
    * @param[in] arg5
    * @param[in] arg6
    */
#if(LOG_LEVEL < -10)/*将-10到-1变成可定义的level等级，GM代码最小到0，用户可用这段*/
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
* @modify info:2012年12月6日  By wtt
**/
	void GM_Log_String(const GM_UINT8* buf, GM_UINT16 size);


    void GM_OutputDebugString(char *format, ...);

	/**
    * @brief GM_Log_Err
    *
    * GM内部错误回调函数.
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
    * GM内部错误回调函数.
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

