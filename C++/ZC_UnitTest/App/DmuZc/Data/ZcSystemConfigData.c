/*******************************************
* 文件名	：  ZcSystemConfigData.c
* 作  者	：  ZC组
* 创建时间	：  2015-5-25
* 功能描述	：	载入ZcSystemConfigData数据管理
* 备  注	：  无
*******************************************/

#include "ZcSystemConfigData.h"
#include "../../../Dmu/Read/ReadDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Dmu/DmuComm/DataHandle/DmuCommDataTypeDefine.h"

static BnfZcSystemConfigStruct* gZcSystemConfigDataStru = NULL;   /*定义ZcSystemConfigData数据结构体*/
static UINT16_S gLineNumZcSystemConfig = 0U;/*表行数*/


/*******************************************
* 函数名	：
* 功能描述： 给ZcSystemConfigDataStru结构体指针分配空间
* 参数说明： UINT16 lineNum 表的数据行数
* 返回值  ： void
*/
void MallocZcSystemConfigDataStru(UINT16_S lineNum)
{
	if ((lineNum > 0U)&&(NULL == gZcSystemConfigDataStru))
	{
		gZcSystemConfigDataStru = (BnfZcSystemConfigStruct*)MemoryMalloc(((UINT32_S)(lineNum*sizeof(BnfZcSystemConfigStruct))));
		gLineNumZcSystemConfig = lineNum;
	}
}

/*******************************************
* 函数名	：
* 功能描述： 获取ZcSystemConfigData数据
* 参数说明：
* 返回值  ： 
			BnfZcSystemConfigStruct*
*/
BnfZcSystemConfigStruct *GetZcSystemConfigData(void)
{
	return gZcSystemConfigDataStru;
}


/*******************************************
* 函数名	：
* 功能描述： 获取ZcSystemConfigData信息
* 参数说明：输出参数:UINT16* lineNum  数据行数
* 返回值  ： 
			BnfZcSystemConfigStruct*
*/
BnfZcSystemConfigStruct *GetZcSystemConfigDataInfo(UINT16_S* lineNum)
{
    if (NULL != lineNum)
    {
        (*lineNum) = gLineNumZcSystemConfig;
    }
	
	return gZcSystemConfigDataStru;
}
/*******************************************
* 函数名	：
** 功能描述： 获取指定IDZcSystemConfigDataStru的列车最大退行距离（ms）
* 参数说明:  无
* 返回值  :  UINT16_NULL: 获取数据失败
*			<UINT16_NULL: 列车最大退行距离（ms）
*/ 
UINT16_S GetZcSystemConfigDataStrutrainMaxRecedeDis(void)
{
	UINT16_S retVal = UINT16_NULL;/*函数返回值*/
	if (NULL != gZcSystemConfigDataStru)
	{
		retVal = gZcSystemConfigDataStru[0].trainMaxRecedeDis;
	}
	else
	{
        /*不处理*/
	}
	return retVal;
}

/*******************************************
* 函数名	：
** 功能描述： 获取指定IDZcSystemConfigDataStru的线路最小可能车长(cm)
* 参数说明:  无
* 返回值  :  UINT16_NULL: 获取数据失败
*			<UINT16_NULL: 线路最小可能车长(cm)
*/ 
UINT16_S GetZcSystemConfigDataStrulineMinTrainLength(void)
{
	UINT16_S retVal = UINT16_NULL;/*函数返回值*/
	if (NULL != gZcSystemConfigDataStru)
	{
		retVal = gZcSystemConfigDataStru[0].lineMinTrainLength;
	}
	else
	{
        /*不处理*/
	}
	return retVal;
}

/*******************************************
* 函数名	：
** 功能描述： 获取运营要求的点灯区段长度(cm)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*			<UINT32_NULL: 运营要求的点灯区段长度(cm)
*/ 
UINT32_S GetZcSystemSectionLength(void)
{
	UINT32_S retVal = UINT32_NULL;/*函数返回值*/
	if (NULL != gZcSystemConfigDataStru)
	{
		retVal = gZcSystemConfigDataStru[0].sectionLength;
	}
	else
	{
        /*不处理*/
	}
	return retVal;
}

/*******************************************
* 函数名	：
** 功能描述： 获取前端筛选计轴区段数量
* 参数说明:  无
* 返回值  :  UINT16_NULL: 获取数据失败
*			<UINT16_NULL: 前端筛选计轴区段数量
*/ 
UINT16_S GetZcSystemAxleSectionNum(void)
{
	UINT16_S retVal = UINT16_NULL;/*函数返回值*/
	if (NULL != gZcSystemConfigDataStru)
	{
		retVal = gZcSystemConfigDataStru[0].axleSectionNum;
	}
	else
	{
        /*不处理*/
	}
	return retVal;
}

/*******************************************
* 函数名	：
** 功能描述： 获取计轴区段非通信车占用冗余判断时间（ms）
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*			<UINT32_NULL: 计轴区段非通信车占用冗余判断时间（ms）
*/ 
UINT32_S GetZcSystemRedunJudgmentTime(void)
{
	UINT32_S retVal = UINT32_NULL;/*函数返回值*/
	if (NULL != gZcSystemConfigDataStru)
	{
		retVal = gZcSystemConfigDataStru[0].redunJudgmentTime;
	}
	else
	{
        /*不处理*/
	}
	return retVal;
}

/*******************************************
* 函数名	：
** 功能描述： 获取逻辑区段占用空闲码位个数开关
* 参数说明:  无
* 返回值  :  UINT8_NULL: 获取数据失败
*			<UINT8_NULL: ZC-CI逻辑区段占用空闲码位个数开关
*/ 
UINT8_S GetZcSystemFreeCodeNumSwitch(void)
{
	UINT8_S retVal = UINT8_NULL;/*函数返回值*/
	if (NULL != gZcSystemConfigDataStru)
	{
		retVal = gZcSystemConfigDataStru[0].freeCodeNumSwitch;
	}
	else
	{
        /*不处理*/
	}
	return retVal;
}

/*******************************************
* 函数名	：
** 功能描述： 获取列车CBTC折返时间（ms）
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*			<UINT32_NULL: 列车CBTC折返时间（ms）
*/ 
UINT32_S GetZcSystemTrainCbtcBackTime(void)
{
	UINT32_S retVal = UINT32_NULL;/*函数返回值*/
	if (NULL != gZcSystemConfigDataStru)
	{
		retVal = gZcSystemConfigDataStru[0].trainCbtcBackTime;
	}
	else
	{
        /*不处理*/
	}
	return retVal;
}

/*******************************************
* 函数名	：
** 功能描述： 判断信号机跨压距离
* 参数说明:  无
* 返回值  :  UINT16_NULL: 获取数据失败
*			<UINT16_NULL: 判断信号机跨压距离
*/ 
UINT16_S GetZcSystemSignPressureDis(void)
{
	UINT16_S retVal = UINT16_NULL;/*函数返回值*/
	if (NULL != gZcSystemConfigDataStru)
	{
		retVal = gZcSystemConfigDataStru[0].signPressureDis;
	}
	else
	{
        /*不处理*/
	}
	return retVal;
}

/*******************************************
* 函数名	：
** 功能描述： 追踪不带后方检查标记RM列车方式
* 参数说明:  无
* 返回值  :  UINT8_NULL: 获取数据失败
*			<UINT8_NULL: 追踪不带后方检查标记RM列车方式
*/ 
UINT8_S GetZcTrackRmTrainType(void)
{
	UINT8_S retVal = UINT8_NULL;/*函数返回值*/
	if (NULL != gZcSystemConfigDataStru)
	{
		retVal = gZcSystemConfigDataStru[0].zcTrackRmTrainType;
	}
	else
	{
        /*不处理*/
	}
	return retVal;
}

