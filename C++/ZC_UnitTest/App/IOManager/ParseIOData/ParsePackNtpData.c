/************************************************************************
*
* 文件名   ：  ParsePackNtpData.c
* 创建时间 ：  2014.04.14
* 作者     ：  ZC组
* 功能描述 ：  解析组包Ntp数据管理  
* 备  注	：  无
*
************************************************************************/

#include "ParsePackNtpData.h"
#include "../../SysDataManager/SysDefine.h"
#include "../CommTarget/CommTargetStatusData.h"
#include "../CommTarget/CommTargetConfigData.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/MemSet.h"
#include "../../SysDataManager/SysConfigData.h"

ZcAndNtpIODataStruct gNtpToZcDataStru;            /*Ntp发送给ZC的数据*/
ZcAndNtpIODataStruct gZcToNtpDataStru;            /*ZC发送给Ntp的数据*/

/*
* 功能描述： 获取Ntp输入给ZC的数据长度
* 参数说明： 无
* 返回值  ： 0: 获取失败
*			 >0: 数据长度      
*/
UINT16_S GetNtpToZcDataLen(void)
{
	return gNtpToZcDataStru.ValueBuffLen;
}

/*
* 功能描述： 获取Ntp输入给ZC的数据信息
* 参数说明： 无
* 返回值  ：  NULL: 获取失败
*			 !NULL: 获取成功     
*/
UINT8_S* GetNtpToZcDataBuff(void)
{
	return gNtpToZcDataStru.ValueBuff;
}


/*
* 功能描述： 获取ZC输出给Ntp的数据长度
* 参数说明： 无
* 返回值  ： 0: 数据解析失败
*			 >0: 数据长度      
*/
UINT16_S GetZcToNtpDataLen(void)
{
	return gZcToNtpDataStru.ValueBuffLen;
}

/*
* 功能描述： 获取ZC输出给Ntp的数据信息
* 参数说明： 无
* 返回值  ： NULL: 获取失败
*			 !NULL: 获取成功      
*/
UINT8_S* GetZcToNtpDataBuff(void)
{
	return gZcToNtpDataStru.ValueBuff;
}

/*
* 功能描述： 解析Ntp输入的单帧数据
* 参数说明： const UINT8_S dataBuff[], 数据缓冲区
*            const UINT16_S dataLength, 数据长度
* 返回值  ： 0: 数据解析失败
*			 1: 数据解析成功      
*/
UINT8_S ParseNtpToZcFrameData(const UINT8_S dataBuff[], UINT16_S dataLength)
{
	UINT8_S sourceId = DEFAULT_ZERO;
	UINT8_S tempRtn = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S rtnCpy = DEFAULT_ZERO;

	if ((dataBuff != NULL) && (dataLength > 0U))
	{
		/*解析帧头,Ntp默认ID为1*/
		sourceId = 1U;

		tempRtn = GetCommTargetIdInConfigData(INNER_DEVTYPE_NTP,((UINT16_S)sourceId));

		if (RETURN_SUCCESS == tempRtn)
		{
			/*获取通信数据*/
			gNtpToZcDataStru.NtpId = sourceId;

			gNtpToZcDataStru.ValueBuffLen = dataLength;

			rtnCpy = MemoryCpy(gNtpToZcDataStru.ValueBuff,((UINT32_S)(ZC_NTP_COM_BYTE_SUM_MAX)),&dataBuff[0],((UINT32_S)dataLength));

			if (0U == rtnCpy)
			{
				/*属于本ZC通信NTP, 更新通信状态*/
				SetCommTargetStatus(INNER_DEVTYPE_NTP,((UINT16_S)sourceId),COMM_STATUS_NORMAL);
				SetCommTargetCycle(INNER_DEVTYPE_NTP,((UINT16_S)sourceId),DEFAULT_ZERO);
				rtnValue = RETURN_SUCCESS;
			} 
			else
			{
				gNtpToZcDataStru.ValueBuffLen = 0U;
				rtnValue = RETURN_ERROR;
			}
		} 
		else
		{
			/*数据无效*/
			rtnValue = RETURN_ERROR;
		}
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}
	
	return rtnValue;
}

/*
* 功能描述： 组Ntp帧数据
* 参数说明： UINT8* dataBuff,数据数组   
*            const UINT16_S dataLen,数据长度
*            const UINT16_S commNtpId,通信的NtpId(预留)
* 返回值  ： 0:组数据失败
*			 1:组数据成功      
*/
UINT8_S PackZcToNtpFrameData(const UINT8_S* dataBuff,const UINT16_S dataLen,const UINT16_S commNtpId)
{
	UINT16_S index = 0U;/*游标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

    gZcToNtpDataStru.ValueBuff[index]= INNER_DEVTYPE_ZC;
    index = index + 1U;

	gZcToNtpDataStru.ValueBuff[index]= (UINT8_S)GetLocalZcId();
    index = index + 1U;

	gZcToNtpDataStru.ValueBuff[index]= INNER_DEVTYPE_NTP;
    index = index + 1U;

	gZcToNtpDataStru.ValueBuff[index]= 1U;
    index = index + 1U;
	
	if (dataBuff != NULL)
	{
		/*拷贝接口数据*/
		if (0U == MemoryCpy(&gZcToNtpDataStru.ValueBuff[index],((UINT32_S)(ZC_NTP_COM_BYTE_SUM_MAX - (UINT32_S)index)),dataBuff,((UINT32_S)dataLen)))
		{
			/*填写长度信息*/
			gZcToNtpDataStru.ValueBuffLen = index + dataLen;

            rtnValue = RETURN_SUCCESS;
		} 
		else
		{
			/*清除输出数据*/
			gZcToNtpDataStru.ValueBuffLen = 0U;

			rtnValue = RETURN_ERROR;
		}

		
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 清空本周期所有输入的Ntp输入信息
* 参数说明： 无
* 返回值  ： 无      
*/
void ClearCycleNtpInputData(void)
{
	MemorySet(&gNtpToZcDataStru,((UINT32_S)(sizeof(ZcAndNtpIODataStruct))),
                 DEFAULT_ZERO,((UINT32_S)(sizeof(ZcAndNtpIODataStruct))));
}

/*
* 功能描述： 清空本周期所有输出给Ntp输入信息
* 参数说明： 无
* 返回值  ： 无      
*/
void ClearCycleNtpOutputData(void)
{
	MemorySet(&gZcToNtpDataStru,((UINT32_S)(sizeof(ZcAndNtpIODataStruct))),
                 DEFAULT_ZERO,((UINT32_S)(sizeof(ZcAndNtpIODataStruct))));
}
