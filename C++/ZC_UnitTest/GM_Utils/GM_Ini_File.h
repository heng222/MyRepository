/**
* @file GM_Ini_File.h
* @brief ��ȡini�����ļ�
* -'='֮���ֵ����Ϊ��char
* -֧��';'ע��ǰ׺
* -��֧�ֿ���
* @author Hao Liming
* @date 2009-9-18 16:22:00
* @version 0.3
* <pre><b>copyright: CASCO</b></pre>
* <pre><b>email: </b>haoliming@casco.com.cn</pre>
* <pre><b>company: </b>http://www.casco.com.cn</pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>�������޸ĳ�ֻ��ʼ��һ��, ����˶�ȡ����ֵ��ʮ�����Ƶķ���, ������keyǰ׺��ͬ��ȡ�����bug.</pre>
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
    * ���������ļ���fileContent��.
    * @param[in] filePathAndName �����ļ�·��
    * @param[out] fileContent �����ļ�������
    * @param[in] fileContent ��������ļ����ݵĴ�С
    * @return GM_BOOL
    */
	
#if 0	
    GM_BOOL GM_Ini_File_Load(const char* filePathAndName, char* fileContent, int fileContentSize);
#endif 

    /**
    * @brief GM_Ini_File_Read_String
    *
    * ��section�ж�ȡ����key��ֵ��value��.
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
    * ��section�ж�ȡ����key��ֵ��value��.
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
    * ��section�ж�ȡ����key��ֵ��value��.
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
    * ��section�ж�ȡ����key��ֵ��value��.
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
    * ��section�ж�ȡ����key��ֵ��value��,0x01����дΪ0x1.
	* key��ֻ��һ��16������ʱ������key1=0x11��key���ж��16������ʱ������key1=0x11 0x22 0x34
    * @param[in] section
    * @param[in] key
    * @param[out] value
    * @param[in] size 16�������ĸ���
    * @param[out] outSize
    * @param[in] iniFileContent
    * @return GM_BOOL
    */
    GM_BOOL GM_Ini_File_Read_Hex(const char *section, const char *key, char* value, int size, int* outSize,  const char* iniFileContent);

    /**
    * @brief GM_Ini_File_Read_Hex_32
    *
    * ��section�ж�ȡ����key��ֵ��value��. ��16�������ø�ʽΪ0x1��0x112345678��ʽ�Կ�
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
    * �����ļ�������ļ���С.
    * @param[in] filePathAndName
    * @return int
    */
    /*sjz: ��Windows��Ƕ��ʽ����ϵͳ��VxworksǶ��ʽ����ϵͳ�£���ȡ���ļ���С����ͬ�ģ����س���������ϵͳ�У�����"\n" */
	
#if 0	
    long GM_Get_File_Size(const char *filePathAndName);
#endif 
	/**
    * @brief GM_Get_File_Size
    * ���ܻ��ǰ�س� ��س�
    * �����ļ�������ļ���С.
    * @param[in] filePathAndName
	* @param[in] PartName		 ���ֶ�ȡ�ļ�ʱ�Ĳ����ֶ���Ϣ
    * @return int
    */
	
#if 0	
    long GM_Get_File_Partly_Size(const char *filePathAndName, const char* PartName);
#endif
		/**
    * @brief GM_Ini_File_Load
    *
    * ���ز��������ļ����ݵ�fileContent��.
    * @param[in] filePathAndName �����ļ�·��
	* @param[in] PartName		 ���ֶ�ȡ�ļ�ʱ�Ĳ����ֶ���Ϣ
    * @param[out] fileContent �����ļ�������
    * @param[in] fileContent ��������ļ����ݵĴ�С
    * @return GM_BOOL
    */
	
#if 0	
    GM_BOOL GM_Ini_File_Partly_Load(const char* filePathAndName, const char* PartName, char* fileContent, int fileContentSize);
#endif	
	/**
	* @GM_Ini_File_Read_IntORHex8
	*
	* ��ȡ8λʮ���ƻ�ʮ��������.key1=16 ����key1=0x10
	* @param[in] section �ֶ�
	* @param[in] key �ؼ���
	* @param[in] fileContent �����ļ�������
	* @param[out] pValue �ֶιؼ��ֺ��ֵ
	* @return GM_BOOL
	*/
	GM_BOOL GM_Ini_File_Read_IntORHex8(const char *section, const char *key, GM_UINT8* pValue,const char *iniFileContent);

	/**
	* @GM_Ini_File_Read_IntORHex16
	*
	* ��ȡ16λʮ���ƻ�ʮ��������. key1=16 ����key1=0x0010
	* @param[in] section �ֶ�
	* @param[in] key �ؼ���
	* @param[in] fileContent �����ļ�������
	* @param[out] pValue �ֶιؼ��ֺ��ֵ
	* @return GM_BOOL
	*/
	GM_BOOL GM_Ini_File_Read_IntORHex16(const char *section, const char *key, GM_UINT16* pValue,const char *iniFileContent);

	/**
	* @GM_Ini_File_Read_IntORHex32
	*
	* ��ȡ32λʮ���ƻ�ʮ��������.key1=16 ����key1=0x00000010
	* @param[in] section �ֶ�
	* @param[in] key �ؼ���
	* @param[in] fileContent �����ļ�������
	* @param[out] pValue �ֶιؼ��ֺ��ֵ
	* @return GM_BOOL
	*/
	GM_BOOL GM_Ini_File_Read_IntORHex32(const char *section, const char *key,GM_UINT32* pValue, const char *iniFileContent);


#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_INI_FILE_H */

