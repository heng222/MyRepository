/************************************************************************
 文件名：  MAInitManager.c
 作者  ：  ZC组
 创建时间 ：  2015-04-18
 描述 ：  移动授权初始化管理
 备注 ： 无
************************************************************************/
#include "MAInitManager.h"
#include "MAStatusData.h"

extern MaDataStruct gMaDataStruBuff[COMM_TRAIN_SUM_MAX];                  /*引用本ZC控制范围内最大列车移动授权数量*/
extern UINT8_S gMaDataIndexBuff[LINE_MAX_TRAIN_ID];			              /*引用列车移动授权索引数组，数组长度为线路可能的最大列车ID*/
extern UINT8_S gMaCurSum;									              /*引用本ZC移动授权当前列车数量*/

extern NextZcMaDataStruct gNextZcDataStruBuff[COMM_TRAIN_SUM_MAX];        /*引用相邻ZC控制范围内最大列车移动授权数量*/
extern UINT8_S gNextZcMaDataIndexBuff[LINE_MAX_TRAIN_ID];                 /*引用相邻ZC列车移动授权索引数组，数组长度为线路可能的最大列车ID*/
extern UINT8_S gNextZcMaCurSum;                                           /*引用保存相邻ZC MA2数量*/

/*************************************************
  函数名:      InitMaLocalInfo
  功能描述:    初始化本地管理的移动授权信息
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void InitMaLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	/*初始化*/
	gMaCurSum = 0U;

	for (cycle = DEFAULT_ZERO;cycle < LINE_MAX_TRAIN_ID;cycle++)
	{
		gMaDataIndexBuff[cycle] = LINE_MAX_TRAIN_ID;
	}

	gNextZcMaCurSum = 0U;

	for (cycle = DEFAULT_ZERO;cycle < LINE_MAX_TRAIN_ID;cycle++)
	{
		gNextZcMaDataIndexBuff[cycle] = LINE_MAX_TRAIN_ID;
	}
}
