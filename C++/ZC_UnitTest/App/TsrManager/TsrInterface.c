/*******************************************
文件名	：TsrInterface.c
作者	：董欣
创建时间：2016-10
描述	：TSR接口
备注	：无
*******************************************/

#include "TsrInterface.h"

/*******************************************
函数名	：TsrInit
功能描述：Tsr初始化函数
输入	：无
输出	：无
返回值	：0:初始化失败；1：初始化成功。
*******************************************/
UINT8_S TsrInit(void)
{
	UINT8_S  rtnValue = TSR_SUCCESS;/*函数返回值*/
	rtnValue = InitialProcess();
	return rtnValue;
}

/*******************************************
函数名	: TsrIFGetZcWorkState
功能描述：获取工作状态
输入	：无
输出	：无
返回值	：ZC工作状态
*******************************************/
UINT8_S TsrIFGetZcWorkState(void)
{
	UINT8_S  rtnValue = TSR_SUCCESS;/*函数返回值*/
	rtnValue = GetZcWorkState();
	return rtnValue;
}

/*******************************************
函数名	: TsrIFSetZcWorkState
功能描述：设置工作状态
输入	：无
输出	：无
返回值	：无
*******************************************/
void TsrIFSetZcWorkState(UINT8_S workState)
{
	SetZcWorkState(workState);
}

/*******************************************
函数名	：ParseTsrCommandsFromAts
功能描述：解析ATS的输入数据
输入	：无
输出	：无
返回值	：retVal成功解析的数据包的数量
*******************************************/
UINT8_S ParseTsrCommandsFromAts(void)
{
	UINT8_S pktQuan = DEFAULT_ZERO;
	pktQuan = Tsr_ParseIncomingDatas();
	return pktQuan;
}

/*******************************************
函数名	：ProcessTsrCommandsFromAts
功能描述：处理 ATS发来数据
输入	：无
输出	：无
返回值	：0:处理失败,1:处理成功
*******************************************/
UINT8_S ProcessTsrCommandsFromAts(void)
{
	UINT8_S retVal = DEFAULT_ZERO;
	retVal = ProcessRcvFromAtsData();
	return retVal;
}

/*******************************************
函数名	：ProcessTsrCommandsToAts
功能描述：处理 回复到Ats数据
输入	：无
输出	：无
返回值	：0：失败；1：成功
*******************************************/
UINT8_S ProcessTsrCommandsToAts(void)
{
	UINT8_S retVal = DEFAULT_ZERO;
	retVal = ProcessReplyToAtsData();
	return retVal;
}

/*******************************************
函数名	：PackTsrCommandsToAts
功能描述：打包ATS输出数据
输入	：无
输出	：无
返回值	：无
*******************************************/

void PackTsrCommandsToAts(void)
{
	Tsr_PackOutletDatas();
}
