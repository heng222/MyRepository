/*******************************************
文件名	：TsrTransmitStateDataManage.c
作者	：董欣
创建时间：2016-10
描述	：通信状态数据管理文件
备注	：无
*******************************************/

#include "TsrTransmitStateDataManage.h"
#include "../TsrSystem/TsrSystemDefine.h"
#include "../TsrSystem/TsrSysConfigData.h"
/*#include "../TsrMaintenance/MaintainManager.h"*/
/*#include "../TsrMaintenance/EventCode.h"			*/
#include "../../../Common/MemSet.h"

static UINT8_S  g_ResReplyToAtsFlag = ANTI_RES_REPLYTO_ATS;/*向ATS发送应答信息标志变量*/

/*******************************************
函数名	：GetResReplyToAtsFlag
功能描述：获取 向ATS发送应答信息标志
输入	：无
输出	：无
返回值	：0: 获取数据失败
		  0xaau:收到ATS命令标志 0x55u:未收到ATS命令标志
*******************************************/
UINT8_S GetResReplyToAtsFlag()
{
	return g_ResReplyToAtsFlag;
}


/*******************************************
函数名	：SetResReplyToAtsFlag
功能描述：设置 向ATS发送应答信息标志
输入	：UINT8_S resReplyToAtsFlag, 应答信息标志
输出	：无
返回值	：无
*******************************************/
void SetResReplyToAtsFlag(UINT8_S resReplyToAtsFlag)
{
	g_ResReplyToAtsFlag = resReplyToAtsFlag;
}