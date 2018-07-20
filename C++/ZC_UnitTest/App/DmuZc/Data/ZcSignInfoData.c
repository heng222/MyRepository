/*******************************************
* 文件名	：  ZcSignInfoData.c
* 作  者	：  ZC组
* 创建时间	：  2015-5-25
* 功能描述	：	载入ZcSignInfoData数据管理
* 备  注	：  无
*******************************************/

#include "ZcSignInfoData.h"
#include "../../../Dmu/Read/ReadDataTypeDefine.h"
#include "../../../Common/Malloc.h"

static BnfZcSignInfoStruct* gZcSignInfoDataStru = NULL;   /*定义ZcSignInfoData数据结构体*/
static UINT16_S gLineNumZcSignInfo = 0U;/*表行数*/



/*******************************************
* 函数名	：  MallocZcSignInfoDataStru
* 功能描述	：	分配 ZcSignInfoDataStru
* 输入：  无
* 输出：  无
* 返回值  :  NULL: 获取数据失败
*			!NULL: 成功
*******************************************/
void MallocZcSignInfoDataStru(UINT16_S lineNum)
{
	if ((lineNum > 0U)&&(NULL == gZcSignInfoDataStru))
	{
		gZcSignInfoDataStru = (BnfZcSignInfoStruct*)MemoryMalloc(((UINT32_S)(lineNum*sizeof(BnfZcSignInfoStruct))));
		gLineNumZcSignInfo = lineNum;
	}
}

/*******************************************
* 函数名	：  GetZcSignInfoData
* 功能描述	：	获取ZcSignInfoData数据
* 输入：  无
* 输出：  无
* 返回值  :  NULL: 获取数据失败
*			!NULL: 成功
*******************************************/
BnfZcSignInfoStruct *GetZcSignInfoData(void)
{
	return gZcSignInfoDataStru;
}


/*******************************************
* 函数名	：   
* 功能描述： 获取ZcSignInfoData信息
* 参数说明：输出参数:UINT16* lineNum  数据行数
* 返回值  ： 
			BnfZcSignInfoStruct*
*/
BnfZcSignInfoStruct *GetZcSignInfoDataInfo(UINT16_S* lineNum)
{
    if (NULL != lineNum)
    {
        (*lineNum) = gLineNumZcSignInfo;
    }
	
	return gZcSignInfoDataStru;
}
/*******************************************
* 函数名	：
** 功能描述： 获取指定IDZcSignInfoDataStru的结构体下标
* 参数说明： const UINT16 signId;信号机ID
* 返回值  :  0xFFFF: 获取数据失败
*			<0xFFFF: 查找成功
*/ 
UINT16_S GetZcSignInfoDataStruIndex(const UINT16_S signId)
{
	UINT16_S retVal = 0xFFFFU;/*函数返回值*/

	UINT16_S i = 0U;/*循环使用*/

	for ( i = 0U; i < gLineNumZcSignInfo; i++)
	{
		if (signId == gZcSignInfoDataStru[i].signId)
		{
			retVal = i;
			break;
		}
	}
	return retVal;
}

/*******************************************
* 函数名	：
** 功能描述： 获取指定IDZcSignInfoDataStru的结构体指针
* 参数说明： const UINT16 signId;信号机ID
* 返回值  :  NULL: 获取数据失败
*			!NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfZcSignInfoStruct* GetIndexIdZcSignInfoDataStru(const UINT16_S signId)
{
	BnfZcSignInfoStruct* retVal = NULL;/*函数返回值*/
	UINT16_S bufIndex = 0U;  /*数组下标*/
	bufIndex = GetZcSignInfoDataStruIndex(signId);/*获取结构体数组下标*/
	if (bufIndex < gLineNumZcSignInfo)
	{
		retVal = &gZcSignInfoDataStru[bufIndex];
	}
	else
	{
        /*Do nothing currently !*/
	}
	return retVal;
}

/*******************************************
* 函数名	：
** 功能描述： 获取指定IDZcSignInfoDataStru的闯信号标志
* 参数说明： const UINT16 signId;信号机ID
* 返回值  :  0: 获取数据失败
*			>0: 闯信号标志
*/ 
UINT16_S GetZcSignInfoDataStruthroughSignFlag(const UINT16_S signId)
{
	UINT16_S retVal = 0U;/*函数返回值*/
	UINT16_S bufIndex = 0U;  /*数组下标*/
	bufIndex = GetZcSignInfoDataStruIndex(signId);/*获取结构体数组下标*/
	if (bufIndex < gLineNumZcSignInfo)
	{
		retVal = gZcSignInfoDataStru[bufIndex].throughSignFlag;
	}
	else
	{
        /*Do nothing currently !*/
	}
	return retVal;
}

/*******************************************
* 函数名	：
** 功能描述： 获取指定IDZcSignInfoDataStru的亮灭标志
* 参数说明： const UINT16 signId;信号机ID
* 返回值  :  0: 获取数据失败
*			>0: 亮灭标志
*/ 
UINT16_S GetZcSignInfoDataStrulightFlag(const UINT16_S signId)
{
	UINT16_S retVal = 0U;/*函数返回值*/
	UINT16_S bufIndex = 0U;  /*数组下标*/
	bufIndex = GetZcSignInfoDataStruIndex(signId);/*获取结构体数组下标*/

	if (bufIndex < gLineNumZcSignInfo)
	{
		retVal = gZcSignInfoDataStru[bufIndex].lightFlag;
	}
	else
	{
        /*Do nothing currently !*/
	}
	return retVal;
}

