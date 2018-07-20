/**
* @file GM_Ini_File.c
* @brief initialization file read and write API implementation
* @authro Hao Liming
* @date 2009-9-18 16:22:00
* @version 0.3
* <pre><b>copyright: CASCO</b></pre>
* <pre><b>email: </b>haoliming@casco.com.cn</pre>
* <pre><b>company: </b>http://www.casco.com.cn</pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>Write modifications here.</pre>
*/

#include "GM_Ini_File.h"

#define PARTNAME_MAX_LENTH	100


#if 0
long GM_Get_File_Partly_Size(const char *filePathAndName, const char* PartName)
{
	long cur_pos = 0;
	long len     = 0;

	FILE* in = NULL;
	int ret = 0;
	int i    = 0;
	GM_BOOL rt   = GM_FALSE;
	char partNameBuff[PARTNAME_MAX_LENTH] = {0U};
	const GM_UINT8 * pName = (const GM_UINT8 *)(PartName);

	/*fileContentSize判断小于等于0, 1也应该排除掉 0930CR 需要 修改*/
	if ((NULL == filePathAndName) || (NULL == PartName))
	{
		return -1;
	}

	in = fopen(filePathAndName, "r");

	if (NULL == in)
	{
		return -1;
	}

	ret = fseek(in, 0, SEEK_SET);

	if (-1 == ret)
	{
		return -1;
	}

	partNameBuff[i] = (char)fgetc(in);

	while ((char)EOF != partNameBuff[i])
	{/*循环 一直读到文件末尾*/
		if ('{' == partNameBuff[i])
		{/*查找到partName头 { */
			do 
			{/*将{及其之后的内容放入 partNameBuff中， 直到}尾 */
				if (i < PARTNAME_MAX_LENTH)
				{
					partNameBuff[i] = (char)fgetc(in);
					++i;
				}
				else
				{/* {中内容过多 */
					fclose(in);
					return GM_FALSE;		
				}
			} while ((char)'}' != partNameBuff[i-1]);

			/*将读入的{内容}与PartName比较 */
			--i;
			if (0 == GM_memncomp(((const GM_UINT8*)(partNameBuff)), pName, (size_t)i))
			{/*若匹配，则开始读入文件内容  */
				i = 0;
				cur_pos = ftell(in);
				if (-1 == (int)cur_pos)
				{
					return -1;
				}

				partNameBuff[i] = (char)fgetc(in);

				while(((char)EOF != partNameBuff[i])
					&&((char)'{' != partNameBuff[i]))
				{/* 一直读到下一partName头 {  或者文件末尾 */

					++len;
					partNameBuff[i] = (char)fgetc(in);
				}

				len = ftell(in);

				ret = fclose(in);

				if (0 != ret)
				{
					return -1;
				}
				return (len - cur_pos + 1);
			}
			i = 0;
		}
		/*未找到partName头  继续读下一字符 */
		partNameBuff[i] = (char)fgetc(in);
	}

	fclose(in);
	return -1;
}


GM_BOOL GM_Ini_File_Partly_Load(const char* filePathAndName, const char* PartName, char* fileContent, int fileContentSize)
{
	FILE* in = NULL;
	int i    = 0;
	int ret = 0;
	GM_BOOL rt   = GM_FALSE;
	char partNameBuff[PARTNAME_MAX_LENTH] = {0U};
	const GM_UINT8 * pName = (const GM_UINT8 *)(PartName);

	/*fileContentSize判断小于等于0, 1也应该排除掉 0930CR 需要 修改*/
	if ((NULL == filePathAndName) 
		|| (NULL == fileContent) 
		|| (NULL == PartName) 
		|| (fileContentSize <= 1))
	{
		return GM_FALSE;
	}

	in = fopen(filePathAndName, "r");

	if (NULL == in)
	{
		return GM_FALSE;
	}

	partNameBuff[i] = (char)fgetc(in);

	while ((char)EOF != partNameBuff[i])
	{/*循环 一直读到文件末尾*/
		if ('{' == partNameBuff[i])
		{/*查找到partName头 { */
			do 
			{/*将{及其之后的内容放入 partNameBuff中， 直到}尾 */
				if (i < PARTNAME_MAX_LENTH)
				{
					partNameBuff[i] = (char)fgetc(in);
					++i;
				}
				else
				{/* {中内容过多 */
					fclose(in);
					return GM_FALSE;		
				}
			} while ((char)'}' != partNameBuff[i-1]);

			/*将读入的{内容}与PartName比较 */
			--i;
			if (0 == GM_memncomp(((const GM_UINT8*)(partNameBuff)), pName, (size_t)i))
			{/*若匹配，则开始读入文件内容  */
				i = 0;
				fileContent[i] = (char)fgetc(in);

				while(((char)EOF != fileContent[i])
					&&((char)'{' != fileContent[i]))
				{/* 一直读到下一partName头 {  或者文件末尾 */
					++i;
					if (i < fileContentSize)
					{
						fileContent[i] = (char)fgetc(in);
					}
					else
					{/*传入的buffer不够大*/
						fclose(in);
						return GM_FALSE;
					}
				}
				/* 读完就完成了*/
				fileContent[i] = (char)'\0';
				ret = fclose(in);
				if (0 != ret)
				{
					return GM_FALSE;
				}
				return GM_TRUE;
			}
			i = 0;
		}
		/*未找到partName头  继续读下一字符 */
		partNameBuff[i] = (char)fgetc(in);
		
	}

	fclose(in);
	return GM_FALSE;
}

GM_BOOL GM_Ini_File_Load(const char* filePathAndName, char* fileContent, int fileContentSize)
{
    FILE* in = NULL;
    int i    = 0;
    int rt   = 0;

	/*fileContentSize判断小于等于0, 1也应该排除掉 0930CR 需要 修改*/
    if ((NULL == filePathAndName) || (NULL == fileContent) || (fileContentSize <= 1))
    {
        return GM_FALSE;
    }

    in = fopen(filePathAndName, "r");

    if (NULL == in)
    {
        return GM_FALSE;
    }

    fileContent[i] = (char)fgetc(in);

    while (fileContent[i] != (char)EOF)
    {
        ++i;

        if (i < fileContentSize)
        {
            fileContent[i] = (char)fgetc(in);
        }
        else
        {
            fclose(in);
            return GM_FALSE;
        }
    }

    fileContent[i] = (char)'\0';

	rt = fclose(in);

    if (0 == rt)
    {
        return GM_TRUE;
    }
    else
    {
        return GM_FALSE;
    }
}

#endif

/*得到key和value的起止*/
static void GM_Ini_File_Parse_Sub1(int * key_s, int newline_start, int * key_e, unsigned int j, unsigned int *valid, const char * p, int * value_s, int * value_e, unsigned int i)
{
    if ((NULL == key_s) || (NULL == key_e) || (NULL == valid) || (NULL == p) || (NULL == value_s) || (NULL == value_e))
    {
        return;
    }

    /*find the key ok*/
    *key_s = newline_start;

    *key_e = (int)j - 1;

    *valid = (int)j + 1;

    while ((' ' == p[*valid]) || ('\t' == p[*valid]))
    {
        ++(*valid);
    }

    *value_s = (int)(*valid);

    *value_e = (int)i;

    return;
}
/*判断当前key是否有效 调用sub1得到key和value的 起止*/
static GM_BOOL GM_Ini_File_Parse_Sub2(const char * p, unsigned int j, int newline_start, const char * key, int * key_s, int * key_e, int valid, int * value_s, int * value_e, unsigned int i)
{
    size_t temp = 0U;

    if ((NULL == p) || (NULL == key) || (NULL == key_s) || (NULL == key_e) || (NULL == value_s) || (NULL == value_e))
    {
        return GM_FALSE;
    }

    if ('=' == p[j])
    {
        temp = (size_t)((int)j - newline_start);

        if ((temp == strlen(key)) && (0 == strncmp(key, p + newline_start, strlen(key))))
        {
            GM_Ini_File_Parse_Sub1(key_s, newline_start, key_e, j, (unsigned int*)(&valid), p, value_s, value_e, i);
            return GM_TRUE;
        }
    }

    return GM_FALSE;
}
/*处理等号之后的空格 tab 多余的=号*/
static void GM_Ini_File_Parse_Sub3(unsigned int *j, const char * p, int *valid)
{
    if ((NULL == j) || (NULL == p) || (NULL == valid))
    {
        return;
    }

    ++*j;

    if ((' ' != p[*j]) && ('\t' != p[*j]) && ('=' != p[*j]))
    {
        *valid = (int)(*j);
    }

    return;
}
/*判断=符号的存在和位置*/
static GM_BOOL GM_Ini_File_Parse_Sub4(unsigned int j, unsigned int i, const char * p, int valid, int newline_start, const char * key, int * key_s, int * key_e, int * value_s, int * value_e)
{
    GM_BOOL rt = GM_FALSE;

    if ((NULL == p) || (NULL == key) || (NULL == key_s) || (NULL == key_e) || (NULL == value_s) || (NULL == value_e))
    {
        return GM_FALSE;
    }

    while ((j < i) && (p[j] != '='))
    {
        GM_Ini_File_Parse_Sub3(&j, p, &valid);

        rt = GM_Ini_File_Parse_Sub2(p, j, newline_start, key, key_s, key_e, valid, value_s, value_e, i);

        if (GM_TRUE == rt)
        {
            return rt;
        }
    }

    return GM_FALSE;
}
/*找下一行的起位置*/
static unsigned int GM_Ini_File_Parse_Sub5(const char * p, unsigned int i)
{
    if (NULL == p)
    {
        return i;
    }

    while (('\n' != p[i]) && ('\r' != p[i]) && ('\0' != p[i]))
    {
        ++i;
    }

    return i;
}
/*找key，判断行首的注释符号#，如果存在注释符号，本行不找了*/
static GM_BOOL GM_Ini_File_Parse_Sub6(const char * p, unsigned int j, unsigned int i, int valid, int newline_start, const char * key, int * key_s, int * key_e, int * value_s, int * value_e)
{
    GM_BOOL rt = GM_FALSE;

    if ((NULL == p) || (NULL == key) || (NULL == key_s) || (NULL == key_e) || (NULL == value_s) || (NULL == value_e))
    {
        return GM_FALSE;
    }

    if (';' != p[j]) /*skip over comment*/
    {
        rt = GM_Ini_File_Parse_Sub4(j, i, p, valid, newline_start, key, key_s, key_e, value_s, value_e);

        if (GM_TRUE == rt)
        {
            return rt;
        }
    }

    return GM_FALSE;
}
/*sub5确定每行的起位置，sub6找key， 本函数确定 本section下面，key是否存在*/
static GM_BOOL GM_Ini_File_Parse_Sub7(const char * p, unsigned int *i, int *newline_start, const char * key, int * key_s, int * key_e, int * value_s, int * value_e)
{
    GM_BOOL rt  = GM_FALSE;
    unsigned int j = 0u;
    int valid      = 0;

    if ((NULL == p) || (NULL == i) || (NULL == newline_start) || (NULL == key) || (NULL == key_s) || (NULL == key_e) || (NULL == value_s) || (NULL == value_e))
    {
        return GM_FALSE;
    }

    while (!((('\n' == p[*i -1u]) || ('\r' == p[*i -1u])) && ('[' == p[*i])))
    {
        /*get a new line*/
        *newline_start = (int)( * i);

        *i = GM_Ini_File_Parse_Sub5(p, *i);

        /*now *i  is equal to end of the line*/
        j = (unsigned int)( * newline_start);
        valid = (int)j;

        rt = GM_Ini_File_Parse_Sub6(p, j, *i, valid, *newline_start, key, key_s, key_e, value_s, value_e);

        if (GM_TRUE == rt)
        {
            return rt;
        }

		if ('\0' == p[*i])
		{
			return GM_FALSE;
		}

        ++*i;
    }

    return GM_FALSE;
}
/*确定section是否匹配 得到section起止*/
static GM_BOOL GM_Ini_File_Parse_Sub8(unsigned int *i, int section_start, const char * section, const char * p, int *newline_start, int * sec_s, int * sec_e, const char * key, int * key_s, int * key_e, int * value_s, int * value_e)
{
    GM_BOOL rt = GM_FALSE;
    size_t temp = 0U;

    if ((NULL == i) || (NULL == section) || (NULL == p) || (NULL == newline_start) || (NULL == sec_s) || (NULL == sec_e) || (NULL == key) || (NULL == key_s) || (NULL == key_e) || (NULL == value_s) || (NULL == value_e))
    {
        return GM_FALSE;
    }

    temp = (int)(*i) - section_start;

    if ((temp == strlen(section)) && (0 == strncmp(p + section_start, section, strlen(section))))
    {
        *newline_start = 0;
        ++*i;

        /*Skip over space char after ']'*/

        while (0 != isspace(p[*i]))
        {
            ++*i;
        }

        /*find the section*/
        *sec_s = section_start;

        *sec_e = (int)(*i);

        rt = GM_Ini_File_Parse_Sub7(p, &*i, &*newline_start, key, key_s, key_e, value_s, value_e);

        if (GM_TRUE == rt)
        {
            return rt;
        }
    }

    return GM_FALSE;
}
/*最外层查找，返回section起止位置 key起止位置 value起止位置*/
static GM_BOOL GM_Ini_File_Parse(const char *section, const char *key, const char *buf, int *sec_s, int *sec_e,
                                 int *key_s, int *key_e, int *value_s, int *value_e)
{
    const char *p     = buf;
    unsigned int i    = 0u;
    int section_start = 0;
    int newline_start = 0;
    GM_BOOL rt     = GM_FALSE;

    if ((NULL == section) || (NULL == key) || (NULL == buf) || (NULL == sec_s)
        || (NULL == sec_e) || (NULL == key_s) || (NULL == key_e) || (NULL == value_s) || (NULL == value_e)
        || (0U == strlen(section)) || (0U == strlen(key)))
    {
        return GM_FALSE;
    }

    *sec_e   = -1;
    *sec_s   = -1;
    *key_e   = -1;
    *key_s   = -1;
    *value_s = -1;
    *value_e = -1;

    while ('\0' != p[i])
    {
        /*find the section*/
        if ((((unsigned int)0U == i) || (('\n' == p[i-1U]) || ('\r' == p[i-1U]))) && ('[' == p[i]))
        {
            section_start = (int)(i + 1U);

            /*find the ']'*/

            do
            {
                ++i;
            }
            while ((']' != p[i]) && ('\0' != p[i]));

            rt = GM_Ini_File_Parse_Sub8(&i, section_start, section, p, &newline_start, sec_s, sec_e, key, key_s, key_e, value_s, value_e);

            if (GM_TRUE == rt)
            {
                return rt;
            }
        }
        else
        {
            ++i;
        }
    }

    return GM_FALSE;
}

GM_BOOL GM_Ini_File_Read_String(const char *section, const char *key, char* value, int size, const char* iniFileContent)
{
    int sec_s     = 0;
    int sec_e     = 0;
    int key_s     = 0;
    int key_e     = 0;
    int value_s   = 0;
    int value_e   = 0;
    GM_BOOL rt = GM_FALSE;

    /*check parameters*/

    if ((NULL == section) || (NULL == key) || (NULL == value) || (NULL == iniFileContent)
        || (0U == strlen(section)) || (0U == strlen(key)) || (size <= 0))
    {
        return GM_FALSE;
    }

    rt = GM_Ini_File_Parse(section, key, iniFileContent, &sec_s, &sec_e, &key_s, &key_e, &value_s, &value_e);

    if (GM_FALSE == rt)
    {
        return GM_FALSE; /*not find the key*/
    }
    else
    {
        int cpcount = value_e - value_s;

        if ((size - 1) < cpcount)
        {
            return GM_FALSE;/*size必须要大于cpcount+1,因为地址空间的最后还要加上'\0'*/
        }

        GM_memset((void*)value, (GM_UINT8)0, (size_t)size);

        GM_memcpy((void*)value, (const void*)(iniFileContent + value_s), (size_t)cpcount);
        value[cpcount] = (char)'\0';
		


        return GM_TRUE;
    }
}

GM_BOOL GM_Ini_File_Read_UInt(const char *section, const char *key, unsigned int* value, const char *iniFileContent)
{
	GM_BOOL rt  = GM_FALSE;
	char valueStr[64] = {0};

	/*check parameters*/

	if ((NULL == section) || (NULL == key) || (NULL == value) || (NULL == iniFileContent))
	{
		return GM_FALSE;
	}

	rt = GM_Ini_File_Read_String(section, key, valueStr, sizeof(valueStr), iniFileContent);

	if (GM_FALSE == rt)
	{
		return GM_FALSE;
	}
	else
	{
		rt = GM_atoui(valueStr, sizeof(valueStr), value);
		return rt;
	}
}

GM_BOOL GM_Ini_File_Read_Int(const char *section, const char *key, int* value, const char *iniFileContent)
{
    GM_BOOL rt  = GM_FALSE;
    char valueStr[64] = {0};

    /*check parameters*/

    if ((NULL == section) || (NULL == key) || (NULL == value) || (NULL == iniFileContent))
    {
        return GM_FALSE;
    }

    rt = GM_Ini_File_Read_String(section, key, valueStr, sizeof(valueStr), iniFileContent);

    if (GM_FALSE == rt)
    {
        return GM_FALSE;
    }
    else
    {
        rt = GM_atoi(valueStr, sizeof(valueStr), value);
        return rt;
    }
}

GM_BOOL GM_Ini_File_Read_BOOL(const char *section, const char *key, GM_BOOL* value, const char *iniFileContent)
{
    GM_BOOL rt = GM_FALSE;
    int valueInt  = -1;

    /*check parameters*/

    if ((NULL == section) || (NULL == key) || (NULL == value) || (NULL == iniFileContent))
    {
        return GM_FALSE;
    }

    rt = GM_Ini_File_Read_Int(section, key, &valueInt, iniFileContent);

    if (GM_TRUE == rt)
    {
        if (0 == valueInt)
        {
            *value = GM_FALSE;
            return GM_TRUE;
        }
        else if (1 == valueInt)
        {
            *value = GM_TRUE;
            return GM_TRUE;
        }
        else
        {
            return GM_FALSE;
        }
    }
    else
    {
        return GM_FALSE;
    }
}

static GM_BOOL GM_Ini_File_Read_Hex_Parse_Sub1(const char * iniFileContent, int value_s, int i, char* value, int j)
{
    if ((NULL == iniFileContent) || (NULL == value))/*1125 code verification*/
    {
        return GM_FALSE;
    }

    if ((iniFileContent[value_s + i + 2] >= '0') && (iniFileContent[value_s + i + 2] <= '9'))
    {/*变换0-9*/
        value[j] = (char)(iniFileContent[value_s + i + 2] - '0');
    }
    else if ((iniFileContent[value_s + i + 2] >= 'a') && (iniFileContent[value_s + i + 2] <= 'f'))
    {
        value[j] = (char)((int)(iniFileContent[value_s + i + 2] - 'a') + 10);
    }
    else if ((iniFileContent[value_s + i + 2] >= 'A') && (iniFileContent[value_s + i + 2] <= 'F'))
    {
        value[j] = (char)((int)(iniFileContent[value_s + i + 2] - 'A') + 10);
    }
    else
    {
        return GM_FALSE;
    }

    return GM_TRUE;
}

static GM_BOOL GM_Ini_File_Read_Hex_Parse_Sub2( const char* iniFileContent, int value_s, int i, char* value, int j)
{
	char buffer = 0x00;

    if ((NULL == iniFileContent) || (NULL == value))/*1125 code verification*/
	{
        return GM_FALSE;
    }

	buffer = iniFileContent[value_s + i + 3];

    if ((buffer >= '0') && (buffer <= '9'))
    {
        value[j] = (char)((int)value[j] * 16 + (int)buffer - (int)'0');
    }
    else if ((buffer >= 'a') && (buffer <= 'f'))
    {
        value[j] = (char)((int)value[j] * 16 + (int)buffer - (int)'a' + 10);
    }
    else if ((buffer >= 'A') && (buffer <= 'F'))
    {
        value[j] = (char)((int)value[j] * 16 + (int)buffer - (int)'A' + 10);
    }
    else
    {
        return GM_FALSE;
    }

    return GM_TRUE;
}

static GM_BOOL GM_Ini_File_Read_Hex_Parse(int value_e, int value_s, char* value, int size, int* outSize, const char*  iniFileContent)
{
    int i         = 0;
    int j         = 0;
    int cpcount   = 0;
    int tempindex1 = 0;
    int tempindex2 = 0;
    GM_BOOL rt = GM_TRUE; /**< 这里必须为初始化为TRUE, 否则会出错 */

    if ((NULL == value) || (NULL == iniFileContent))
    {
        return GM_FALSE;
    }

    cpcount = value_e - value_s;

    GM_memset((void*)value, (GM_UINT8)0u, (size_t)size);

    for (i = 0; i < cpcount; )
    {/*i表示配置文件中值域的位置  j表示读取的十六进制数的个数*/
        tempindex1 = value_s + i;
        tempindex2 = value_s + i + 1;

        if (('0' == (iniFileContent[tempindex1]))
            && (('x' == (iniFileContent[tempindex2])) || ('X' == (iniFileContent[tempindex2]))))
        {
            if ((j < size) && (GM_TRUE == rt))
            {/*sub1是十六进制数的第一位解析  sub2第二位解析*/
                rt = GM_Ini_File_Read_Hex_Parse_Sub1(iniFileContent, value_s, i, value, j);

                if (GM_FALSE == rt)
                {
                    return GM_FALSE;
                }

                rt = GM_Ini_File_Read_Hex_Parse_Sub2(iniFileContent, value_s, i, value, j);

                if (GM_FALSE == rt)
                {
                    return GM_FALSE;
                }

				i = i + 5;
                ++j;
            }
            else
            {
                return GM_FALSE;
            }
        }
		else
		{/*配置文件中格式不对*/
			return GM_FALSE;
		}
    }

    if (NULL != outSize)
    {
        *outSize = j;
    }

    return GM_TRUE;
}

GM_BOOL GM_Ini_File_Read_Hex(const char *section, const char *key, char* value, int size, int* outSize, const char* iniFileContent)
{
    int sec_s     = 0;
    int sec_e     = 0;
    int key_s     = 0;
    int key_e     = 0;
    int value_s   = 0;
    int value_e   = 0;
    GM_BOOL rt = GM_FALSE;

    /*check parameters*/

    if ((NULL == section) || (NULL == key) || (NULL == value) || (NULL == iniFileContent)
        || (0U == strlen(section)) || (0U == strlen(key)) || (size <= 0) ||  (NULL == outSize))
    {
        return GM_FALSE;
    }

    rt = GM_Ini_File_Parse(section, key, iniFileContent, &sec_s, &sec_e, &key_s, &key_e, &value_s, &value_e);

    if (GM_FALSE == rt)
    {
        return GM_FALSE; /*not find the key*/
    }
    else
    {
        rt = GM_Ini_File_Read_Hex_Parse(value_e, value_s, value, size, outSize, iniFileContent);
    }

	if (GM_FALSE == rt)
	{
		GM_memset((void*)value, (GM_UINT8)0u, (size_t)size);
	}

    return rt;
}

static GM_BOOL GM_Ini_File_Read_Hex_32_Parse(int value_e, int value_s, GM_UINT32* pValue, const char * iniFileContent)
{
    int i         = 0;
    int cpcount   = 0;
    GM_UINT8 value[8] = {0};
    int tempindex1 = 0;
    int tempindex2 = 0;

    if ((NULL == pValue) || (NULL == iniFileContent))
    {
        return GM_FALSE;
    }

    cpcount = value_e - value_s;

    tempindex1 = value_s + i;
    tempindex2 = value_s + i + 1;

    if ((10 < cpcount) || (2 > cpcount) || ('0' != iniFileContent[tempindex1])
        || (!(('x' == iniFileContent[tempindex2]) || ('X' == iniFileContent[tempindex2]))))
    {
        return GM_FALSE;
    }

    for (i = 2; i < cpcount; ++i)
    {
        tempindex1 = value_s + i;
        tempindex2 = 8 - cpcount + i;

        if ((iniFileContent[tempindex1] >= '0') && (iniFileContent[tempindex1] <= '9'))
        {
            value[tempindex2] = (GM_UINT8)(iniFileContent[tempindex1] - '0');
        }
        else if ((iniFileContent[tempindex1] >= 'a') && (iniFileContent[tempindex1] <= 'f'))
        {
            value[tempindex2] = (GM_UINT8)((int)(iniFileContent[tempindex1] - 'a') + 10);
        }
        else if ((iniFileContent[tempindex1] >= 'A') && (iniFileContent[tempindex1] <= 'F'))
        {
            value[tempindex2] = (GM_UINT8)((int)(iniFileContent[tempindex1] - 'A') + 10);
        }
        else
        {
            return GM_FALSE;
        }
    }

    *pValue = (GM_UINT32)0;

    for (i = 0; i < 8; ++i)
    {
        *pValue <<= 4U;
        *pValue |= (GM_UINT32)value[i];
    }

    return GM_TRUE;
}

GM_BOOL GM_Ini_File_Read_Hex_32(const char *section, const char *key, GM_UINT32* pValue, const char *iniFileContent)
{
    int sec_s     = 0;
    int sec_e     = 0;
    int key_s     = 0;
    int key_e     = 0;
    int value_s   = 0;
    int value_e   = 0;
    GM_BOOL rt = GM_FALSE;

    /*check parameters*/

    if ((NULL == section) || (NULL == key) || (NULL == pValue) || (NULL == iniFileContent)
        || (0U == strlen(section)) || (0U == strlen(key)))
    {
        return GM_FALSE;
    }

	*pValue = 0x00000000U;

    rt = GM_Ini_File_Parse(section, key, iniFileContent, &sec_s, &sec_e, &key_s, &key_e, &value_s, &value_e);

    if (GM_FALSE == rt)
    {
        return GM_FALSE; /*not find the key*/
    }
    else
    {
        rt = GM_Ini_File_Read_Hex_32_Parse(value_e, value_s, pValue, iniFileContent);
    }

    return rt;
}


#if 0
long GM_Get_File_Size(const char *filePathAndName)
{
    long cur_pos = 0;
    long len     = 0;
    FILE *fp     = NULL;
    int rt       = 0;

    if (NULL == filePathAndName)
    {
        return -1;
    }

    fp = fopen(filePathAndName, "r");

    if (NULL == fp)
    {
        return -1;
    }

    /* 取得当前文件流的读取位置 */
    cur_pos = ftell(fp);

	if (-1 == (int)cur_pos)
	{
		return -1;
	}

    /* 将文件流的读取位置设为文件末尾 */
    rt = fseek(fp, 0, SEEK_END);

    if (0 != rt)
    {
        fclose(fp);

        return -1;
    }

    /* 获取文件末尾的读取位置, 即文件大小 */
    len = ftell(fp);

    /* 将文件流的读取位置还原为原先的值 */
    rt = fseek(fp, cur_pos, SEEK_SET);

	if (0 != rt)
	{
		return -1;
	}

    rt = fclose(fp);

	if (0 != rt)
	{
		return -1;
	}
    /*增加 EOF的计数*/
    return (len + 1);
}

#endif 

/*读取8位十进制或十六进制数*/
GM_BOOL GM_Ini_File_Read_IntORHex8(const char *section, const char *key, GM_UINT8* pValue,const char *iniFileContent)
{
	int sec_s     = 0;
	int sec_e     = 0;
	int key_s     = 0;
	int key_e     = 0;
	int value_s   = 0;
	int value_e   = 0;
	GM_BOOL rt = GM_FALSE;
	int cpcount   = 0;
	int value = 0;
	char valueStr[64] = {0};


	if ((NULL == section) || (NULL == key) || (NULL == iniFileContent)||(NULL == pValue)
		|| (0U == strlen(section)) || (0U == strlen(key)))
	{
		return GM_FALSE;
	}

	*pValue = 0x00U;

	rt = GM_Ini_File_Parse(section, key, iniFileContent, &sec_s, &sec_e, &key_s, &key_e, &value_s, &value_e);

	if (GM_FALSE == rt)
	{
		return GM_FALSE; /*not find the key*/
	}
	else
	{
		cpcount = value_e - value_s;

		if (('0' == iniFileContent[value_s])&&(('x' == iniFileContent[value_s+1]) ||('X' == iniFileContent[value_s+1])))
		{/*是十六进制形式*/
			if((3>cpcount)||(4<cpcount))
			{
				return GM_FALSE;
			}
			else
			{
/**start**  CR:GM00001278  add by txj  2013年1月17日 8:57  **/
				rt = GM_Ini_File_Read_Hex_32_Parse(value_e,value_s,(GM_UINT32*)&value,iniFileContent);

				if (GM_FALSE == rt)
				{
					return GM_FALSE;
				}
/**end** add by txj  2013年1月17日 8:57  **/
			}
		}
		else
		{/*是十进制形式*/
			if((1>cpcount)||(3<cpcount))
			{
				return GM_FALSE;
			}
			else
			{
/**start**  CR:GM00001278  add by txj  2013年1月17日 8:57  **/
				GM_memcpy((void*)valueStr,((const void*)&(iniFileContent[value_s])), (size_t)(value_e-value_s));

				rt = GM_atoui((const char*)valueStr, (GM_UINT32)sizeof(valueStr), (unsigned int*)&value);

				if (GM_FALSE == rt)
				{
					return GM_FALSE;
				}
/**end** add by txj  2013年1月17日 8:57  **/
			}
		}

		/*判断是否超过255*/
		if(GM_UINT8_MAX < value)
		{
			return GM_FALSE;
		}

		*pValue = (GM_UINT8)value;

		return GM_TRUE;

	}
}

/*读取16位十进制或十六进制数*/
GM_BOOL GM_Ini_File_Read_IntORHex16(const char *section, const char *key, GM_UINT16* pValue,const char *iniFileContent)
{
	int sec_s     = 0;
	int sec_e     = 0;
	int key_s     = 0;
	int key_e     = 0;
	int value_s   = 0;
	int value_e   = 0;
	GM_BOOL rt = GM_FALSE;
	int cpcount   = 0;
	int value = 0;
	char valueStr[64] = {0};

	if ((NULL == section) || (NULL == key) || (NULL == iniFileContent)||(NULL == pValue)
		|| (0U == strlen(section)) || (0U == strlen(key)))
	{
		return GM_FALSE;
	}

	*pValue = 0x0000U;

	rt = GM_Ini_File_Parse(section, key, iniFileContent, &sec_s, &sec_e, &key_s, &key_e, &value_s, &value_e);

	if (GM_FALSE == rt)
	{
		return GM_FALSE;
	}
	else
	{
		cpcount = value_e - value_s;

		if (('0' == iniFileContent[value_s])&&(('x' == iniFileContent[value_s+1]) ||('X' == iniFileContent[value_s+1])))
		{
			if((3>cpcount)||(6<cpcount))
			{
				return GM_FALSE;
			}
			else
			{
/**start** CR:GM00001278    add by txj 2013年1月17日 8:54  **/
				rt = GM_Ini_File_Read_Hex_32_Parse(value_e,value_s,(GM_UINT32*)&value,iniFileContent);

				if (GM_FALSE == rt)
				{
					return GM_FALSE;
				}
			}
/**end** add by txj 2013年1月17日 8:54  **/

		}
		else
		{
			if((1>cpcount)||(5<cpcount))
			{
				return GM_FALSE;
			}
			else
			{
/**start** CR:GM00001278   add by txj2013年1月17日 8:54  **/
				GM_memcpy((void*)valueStr,((const void*)&(iniFileContent[value_s])), (size_t)(value_e-value_s));

				rt = GM_atoui((const char*)valueStr, (GM_UINT32)sizeof(valueStr), (unsigned int*)&value);

				if (GM_FALSE == rt)
				{
					return GM_FALSE;
				}
/**end** add by txj 2013年1月17日 8:54  **/

			}
		}

		/*判断是否超过65535*/
		if(GM_UINT16_MAX < value)
		{
			return GM_FALSE;
		}

		*pValue = (GM_UINT16)value;

		return GM_TRUE;
	}
}

/*读取32位十进制或十六进制数*/
GM_BOOL GM_Ini_File_Read_IntORHex32(const char *section, const char *key,GM_UINT32* pValue, const char *iniFileContent)
{
	int sec_s     = 0;
	int sec_e     = 0;
	int key_s     = 0;
	int key_e     = 0;
	int value_s   = 0;
	int value_e   = 0;
	GM_BOOL rt = GM_FALSE;
	int cpcount   = 0;

/**start**  CR:CR:GM00001359 add by txj  2013年3月29日   **/
	GM_UINT32 value = 0U;
/**end** add by txj  2013年3月29日 **/

	char valueStr[64] = {0};

	if ((NULL == section) || (NULL == key) || (NULL == iniFileContent)||(NULL == pValue)
		|| (0U == strlen(section)) || (0U == strlen(key)))
	{
		return GM_FALSE;
	}

	*pValue = 0x00000000U;

	rt = GM_Ini_File_Parse(section, key, iniFileContent, &sec_s, &sec_e, &key_s, &key_e, &value_s, &value_e);

	if (GM_FALSE == rt)
	{
		return GM_FALSE;
	}
	else
	{
		cpcount = value_e - value_s;

		if (('0' == iniFileContent[value_s])&&(('x' == iniFileContent[value_s+1]) ||('X' == iniFileContent[value_s+1])))
		{
			if((3>cpcount)||(10<cpcount))
			{
				return GM_FALSE;
			}
			else
			{
/**start**  CR:CR:GM00001278  add by txj  2013年1月17日 8:59  **/
				rt = GM_Ini_File_Read_Hex_32_Parse(value_e,value_s,&value,iniFileContent);

				if (GM_FALSE == rt)
				{
					return GM_FALSE;
				}
/**end** add by txj  2013年1月17日 8:59  **/

			}

		}
		else
		{
			if((1>cpcount)||(10<cpcount))
			{
				return GM_FALSE;
			}
			else
			{
/**start**  CR:CR:GM00001278  add by txj  2013年1月17日 8:59  **/
				GM_memcpy((void*)valueStr,((const void*)&(iniFileContent[value_s])), (size_t)(value_e-value_s));

				rt = GM_atoui((const char*)valueStr, (GM_UINT32)sizeof(valueStr), (unsigned int*)&value);

				if (GM_FALSE == rt)
				{
					return GM_FALSE;
				}
/**end** add by txj  2013年1月17日 8:59  **/

			}
		}

		*pValue = value;

		return GM_TRUE;
	}
}


