/************************************************************************
 文件名   ：  TrainInitManager.c
 创建时间 ：  2015.07.02
 作者     ：  ZC组
 描述 ：  列车初始化管理
 备注 ： 无
************************************************************************/
#include "TrainInitManager.h"
#include "TrainStatusData.h"

extern TrainInfoStruct gTrainStatusDataStruBuff[SIZE_MAX_CONTROLE_TRAIN];     /*引用本ZC控制范围内最大列车数量*/
extern UINT8_S gLocalTrainIndexBuff[SIZE_MAX_LINE_TRAIN];			          /*引用列车索引数组，数组长度为线路可能的最大列车ID*/
extern UINT8_S gTrainCurSum;									              /*引用本ZC当前列车数量*/

/*************************************************
  函数名:      InitTrainLocalInfo
  功能描述:    初始化本地管理的列车信息
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void InitTrainLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	/*初始化*/
	gTrainCurSum = 0U;

	for (cycle = DEFAULT_ZERO;cycle < SIZE_MAX_LINE_TRAIN;cycle++)
	{
		gLocalTrainIndexBuff[cycle] = RETURN_UINT8_MAX_VALUE;
	}
}
