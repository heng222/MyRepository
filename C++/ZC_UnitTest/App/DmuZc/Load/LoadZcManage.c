/*******************************************
 * 文件名	：  LoadZcManage.c
 * 作  者	：  ZC组
 * 创建时间	：  2015-5-25
 * 功能描述	：	载入ZC管理
 * 备  注	：  无
*******************************************/
#include "LoadZcManage.h"
#include "LoadZcCommConfig.h"
#include "LoadZcSignInfo.h"
#include "LoadZcSystemConfig.h"
#include "LoadZcTimeConfig.h"

static LoadZCObjectStruct LoadZcObjStru[LOADZC_OBJECT_MAX]; /*载入对象*/
static UINT8_S LoadZcObjCount = 0U; /*载入对象个数*/

/*******************************************
* 功能描述： 载入ZC相关数据管理
* 参数说明： void
* 返回值  ： void       
*/
void LoadZcManage(void)
{
	LoadZcObjStru[LoadZcObjCount].LoadData = &LoadZcCommConfigData;
    LoadZcObjCount = LoadZcObjCount + 1U;

	LoadZcObjStru[LoadZcObjCount].LoadData = &LoadZcSignInfoData;
    LoadZcObjCount = LoadZcObjCount + 1U;

	LoadZcObjStru[LoadZcObjCount].LoadData = &LoadZcSystemConfigData;
    LoadZcObjCount = LoadZcObjCount + 1U;

	LoadZcObjStru[LoadZcObjCount].LoadData = &LoadZcTimeConfigData;
    LoadZcObjCount = LoadZcObjCount + 1U;
}

/*******************************************
* 功能描述： 载入ZC数据
* 参数说明： void
* 返回值  ： 0:成功返回
*           -1:错误返回
*/
INT8_S LoadZcData(void)
{
	INT8_S retVal = 0;/*函数返回值*/
	UINT8_S ii = 0U;
	for (ii = 0U; ii < LoadZcObjCount; ii++)
	{
		if (LoadZcObjStru[ii].LoadData != NULL)
		{
			retVal = LoadZcObjStru[ii].LoadData();
			if (retVal != 0)
			{
				break;
			}
		}
		else
		{
			retVal = -1;
			break;
		}
	}
	return retVal;
}
