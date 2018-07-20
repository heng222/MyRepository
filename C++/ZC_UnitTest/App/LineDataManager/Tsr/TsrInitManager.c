/************************************************************************
*
* 文件名   ：  TsrInitManager.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  临时限速初始化管理
* 备  注   ：  无
*
************************************************************************/
#include "../../SysDataManager/SysConfigData.h"
#include "TsrStatusData.h"
#include "TsrInitManager.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

extern TsrDataStruct gTsrDataStruBuff[TSR_BUFF_SUM_MAX];                  /*引用本地管理的临时限速配置信息*/
extern UINT16_S gTsrOfZcIdBuff[LINE_ZC_SUM_MAX];                         /*引用临时限速（ZC）映射数组*/
extern UINT16_S gTsrOfZcCurSum;                                         /*引用临时限速（ZC）当前总数*/

/*
* 功能描述： 初始化本地管理的临时限速信息
* 参数说明： 无   
* 返回值  ： 无     
*/
void InitTsrLocalInfo(void)
{
	UINT8_S cycle = DEFAULT_ZERO;

	gTsrOfZcCurSum = 0U;

	for (cycle = DEFAULT_ZERO;cycle < LINE_ZC_SUM_MAX;cycle++)
	{
		gTsrOfZcIdBuff[cycle] = TSR_BUFF_SUM_MAX;
	}
}
