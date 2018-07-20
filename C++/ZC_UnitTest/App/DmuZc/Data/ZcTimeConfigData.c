/*******************************************
 * 文件名	：  ZcTimeConfigData.c
 * 版本号	：  1.0  
 * 创建时间	：  2015-5-25
 * 功能描述	：	载入ZcTimeConfigData数据管理
 * 使用注意	：  
 * 修改记录	：	
*******************************************/

#include "ZcTimeConfigData.h"
#include "../../../Dmu/Read/ReadDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Dmu/DmuComm/DataHandle/DmuCommDataTypeDefine.h"

static BnfZcTimeConfigStruct* gZcTimeConfigDataStru = NULL;   /*定义ZcTimeConfigData数据结构体*/
static UINT16_S gLineNumZcTimeConfig = 0U;/*表行数*/


/*
* 功能描述： 给ZcTimeConfigDataStru结构体指针分配空间
* 参数说明： UINT16 lineNum 表的数据行数
* 返回值  ： void
*/
void MallocZcTimeConfigDataStru(UINT16_S lineNum)
{
	if ((lineNum > 0U)&&(NULL == gZcTimeConfigDataStru))
	{
		gZcTimeConfigDataStru = (BnfZcTimeConfigStruct*)MemoryMalloc(((UINT32_S)(lineNum*sizeof(BnfZcTimeConfigStruct))));
		gLineNumZcTimeConfig = lineNum;
	}
}

/*
* 功能描述： 获取ZcTimeConfigData数据
* 参数说明：
* 返回值  ： 
			BnfZcTimeConfigStruct*
*/
BnfZcTimeConfigStruct *GetZcTimeConfigData(void)
{
	return gZcTimeConfigDataStru;
}


/*
* 功能描述： 获取ZcTimeConfigData信息
* 参数说明：输出参数:UINT16* lineNum  数据行数
* 返回值  ： 
			BnfZcTimeConfigStruct*
*/
BnfZcTimeConfigStruct *GetZcTimeDataInfo(UINT16_S* lineNum)
{
    if (NULL != lineNum)
    {
        (*lineNum) = gLineNumZcTimeConfig;
    }
	
	return gZcTimeConfigDataStru;
}
/*
** 功能描述： 获取NTP校时误差时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*			<UINT32_NULL: NTP校时误差时间(ms)
*/ 
UINT32_S GetZcTimeNtprrorTime(void)
{
	UINT32_S retVal = UINT32_NULL;/*函数返回值*/

	if (NULL != gZcTimeConfigDataStru)
	{
		retVal = gZcTimeConfigDataStru[0].errorTime;
	}
	else
	{
        /*Do nothing currently !*/
	}
	return retVal;
}

/*
** 功能描述： 获取本系统与时钟服务器校时的时长（ms）
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*			<UINT32_NULL: 本系统与时钟服务器校时的时长（ms）
*/ 
UINT32_S GetZcTimeSystemDuration(void)
{
	UINT32_S retVal = UINT32_NULL;/*函数返回值*/
	if (NULL != gZcTimeConfigDataStru)
	{
		retVal = gZcTimeConfigDataStru[0].duration;
	}
	else
	{
        /*Do nothing currently !*/
	}
	return retVal;
}

