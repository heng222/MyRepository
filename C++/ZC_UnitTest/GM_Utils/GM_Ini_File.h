/**
* @file GM_Ini_File.h
* @brief 读取ini配置文件
* -'='之后的值不能为空char
* -支持';'注释前缀
* -不支持跨行
* @author Hao Liming
* @date 2009-9-18 16:22:00
* @version 0.3
* <pre><b>copyright: CASCO</b></pre>
* <pre><b>email: </b>haoliming@casco.com.cn</pre>
* <pre><b>company: </b>http://www.casco.com.cn</pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>将代码修改成只初始化一次, 添加了读取布尔值、十六进制的方法, 修正了key前缀相同读取错误的bug.</pre>
*/

#ifndef _GM_INI_FILE_H
#define _GM_INI_FILE_H

#include "GM_Utils_Other.h"
#include "GM_Memset.h"
#include "GM_Memcpy.h"
#include "GM_Memncomp.h"
#include<ctype.h>

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */

    /**
    * @brief GM_Ini_File_Load
    *
    * 加载配置文件到fileContent中.
    * @param[in] filePathAndName 配置文件路径
    * @param[out] fileContent 配置文件的内容
    * @param[in] fileContent 存放配置文件内容的大小
    * @return GM_BOOL
    */
	
#if 0	
    GM_BOOL GM_Ini_File_Load(const char* filePathAndName, char* fileContent, int fileContentSize);
#endif 

    /**
    * @brief GM_Ini_File_Read_String
    *
    * 在section中读取键名key的值到value中.
    * @param[in] section
    * @param[in] key
    * @param[out] value
    * @param[in] size
    * @param[in] iniFileContent
    * @return GM_BOOL
    */
    GM_BOOL GM_Ini_File_Read_String(const char *section, const char *key, char *value, int size, const char* iniFileContent);

	/**
    * @brief GM_Ini_File_Read_UInt
    *
    * 在section中读取键名key的值到value中.
    * @param[in] section
    * @param[in] key
    * @param[out] value
    * @param[in] iniFileContent
    * @return GM_BOOL
    */
	GM_BOOL GM_Ini_File_Read_UInt(const char *section, const char *key, unsigned int* value, const char *iniFileContent);

    /**
    * @brief GM_Ini_File_Read_Int
    *
    * 在section中读取键名key的值到value中.
    * @param[in] section
    * @param[in] key
    * @param[out] value
    * @param[in] iniFileContent
    * @return GM_BOOL
    */
	
    GM_BOOL GM_Ini_File_Read_Int(const char *section, const char *key, int* value, const char *iniFileContent);

    /**
    * @brief GM_Ini_File_Read_BOOL
    *
    * 在section中读取键名key的值到value中.
    * @param[in] section
    * @param[in] key
    * @param[out] value
    * @param[in] iniFileContent
    * @return GM_BOOL
    */
    GM_BOOL GM_Ini_File_Read_BOOL(const char *section, const char *key, GM_BOOL* value, const char *iniFileContent);

    /**
    * @brief GM_Ini_File_Read_Hex
    *
    * 在section中读取键名key的值到value中,0x01不能写为0x1.
	* key中只有一个16进制数时，形如key1=0x11；key中有多个16进制数时，形如key1=0x11 0x22 0x34
    * @param[in] section
    * @param[in] key
    * @param[out] value
    * @param[in] size 16进制数的个数
    * @param[out] outSize
    * @param[in] iniFileContent
    * @return GM_BOOL
    */
    GM_BOOL GM_Ini_File_Read_Hex(const char *section, const char *key, char* value, int size, int* outSize,  const char* iniFileContent);

    /**
    * @brief GM_Ini_File_Read_Hex_32
    *
    * 在section中读取键名key的值到value中. 其16进制配置格式为0x1，0x112345678格式皆可
    * @param[in] section
    * @param[in] key
    * @param[out] pValue
    * @param[in] iniFileContent
    * @return GM_BOOL
    */
    GM_BOOL GM_Ini_File_Read_Hex_32(const char *section, const char *key, GM_UINT32* pValue, const char *iniFileContent);

    /**
    * @brief GM_Get_File_Size
    *
    * 根据文件名获得文件大小.
    * @param[in] filePathAndName
    * @return int
    */
    /*sjz: 在Windows非嵌入式操作系统和Vxworks嵌入式操作系统下，获取的文件大小是相同的，即回车在这两个系统中，均是"\n" */
	
#if 0	
    long GM_Get_File_Size(const char *filePathAndName);
#endif 
	/**
    * @brief GM_Get_File_Size
    * 可能会多前回车 后回车
    * 根据文件名获得文件大小.
    * @param[in] filePathAndName
	* @param[in] PartName		 部分读取文件时的部分字段信息
    * @return int
    */
	
#if 0	
    long GM_Get_File_Partly_Size(const char *filePathAndName, const char* PartName);
#endif
		/**
    * @brief GM_Ini_File_Load
    *
    * 加载部分配置文件内容到fileContent中.
    * @param[in] filePathAndName 配置文件路径
	* @param[in] PartName		 部分读取文件时的部分字段信息
    * @param[out] fileContent 配置文件的内容
    * @param[in] fileContent 存放配置文件内容的大小
    * @return GM_BOOL
    */
	
#if 0	
    GM_BOOL GM_Ini_File_Partly_Load(const char* filePathAndName, const char* PartName, char* fileContent, int fileContentSize);
#endif	
	/**
	* @GM_Ini_File_Read_IntORHex8
	*
	* 读取8位十进制或十六进制数.key1=16 或者key1=0x10
	* @param[in] section 字段
	* @param[in] key 关键字
	* @param[in] fileContent 配置文件的内容
	* @param[out] pValue 字段关键字后的值
	* @return GM_BOOL
	*/
	GM_BOOL GM_Ini_File_Read_IntORHex8(const char *section, const char *key, GM_UINT8* pValue,const char *iniFileContent);

	/**
	* @GM_Ini_File_Read_IntORHex16
	*
	* 读取16位十进制或十六进制数. key1=16 或者key1=0x0010
	* @param[in] section 字段
	* @param[in] key 关键字
	* @param[in] fileContent 配置文件的内容
	* @param[out] pValue 字段关键字后的值
	* @return GM_BOOL
	*/
	GM_BOOL GM_Ini_File_Read_IntORHex16(const char *section, const char *key, GM_UINT16* pValue,const char *iniFileContent);

	/**
	* @GM_Ini_File_Read_IntORHex32
	*
	* 读取32位十进制或十六进制数.key1=16 或者key1=0x00000010
	* @param[in] section 字段
	* @param[in] key 关键字
	* @param[in] fileContent 配置文件的内容
	* @param[out] pValue 字段关键字后的值
	* @return GM_BOOL
	*/
	GM_BOOL GM_Ini_File_Read_IntORHex32(const char *section, const char *key,GM_UINT32* pValue, const char *iniFileContent);


#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_INI_FILE_H */

