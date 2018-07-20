/*******************************************
文件名	：TsrParsePackInterface.c
作者	：董欣
创建时间：2016-10
描述	：解析组包
备注	：无
*******************************************/
#include"TsrParsePackInterface.h"
/*#include"../TsrMaintenance/MaintainManager.h"*/
/*#include "../TsrMaintenance/EventCode.h"*/
/*#include "../TsrMaintenance/EventCode.h"*/
#include"TsrParsePackAtsData.h"
#include "../../../Common/MemSet.h"
#include "../../IOManager/IOInterfaceProcess/IOInterfaceProcess.h"
/*#ifdef SYS_TYPE_WINDOWS*/
#include "../../../Common/CommonTypes.h"
#include "../../IOManager/ParseIOData/ParsePackIODefine.h"
/*#endif*/

static UINT8_S ParseOneFrameData(const UINT8_S dataBuf[], UINT16_S dataLen);

/*******************************************
函数名	：Tsr_ParseIncomingDatas
功能描述：解析外部通信设备的输入数据
输入	：无
输出	：无
返回值	：retVal成功解析的数据包的数量
*******************************************/
UINT8_S Tsr_ParseIncomingDatas(void)
{
	CirQueueStruct *pAtsToZcDataQueueStru = NULL;
    UINT32_S dataLen = DEFAULT_ZERO; /*数据帧长度*/
    UINT8_S tmpDataBuf[DEV_TOTAL_FRAME_LEN] = {DEFAULT_ZERO}; /* 临时数据缓冲区 */
    UINT8_S retVal = DEFAULT_ZERO;
	UINT32_S pkgQuan = DEFAULT_ZERO;
	UINT32_S iCyc = DEFAULT_ZERO;

    MemorySet(tmpDataBuf, DEV_TOTAL_FRAME_LEN, DEFAULT_ZERO, DEV_TOTAL_FRAME_LEN);

	/*获取ats到ZC的输入数据*/
	pAtsToZcDataQueueStru = GetAtsToZcDataQueueStru();

	/*判断是否*/
	if (pAtsToZcDataQueueStru != NULL)
	{
		pkgQuan = GetQueuePkgCount(pAtsToZcDataQueueStru); /*获取队列数据包个数*/

		for (iCyc = DEFAULT_ZERO; iCyc < pkgQuan; iCyc++)
		{
			/*清空长度*/
			dataLen = DEFAULT_ZERO;
			MemorySet(tmpDataBuf,((UINT32_S)(DEV_TOTAL_FRAME_LEN)),DEFAULT_ZERO,((UINT32_S)(DEV_TOTAL_FRAME_LEN)));

			/*获取一帧数据*/
			dataLen = GetQueuePkgData(pAtsToZcDataQueueStru, tmpDataBuf, DATA_LEN_MAX); 

			if (dataLen > 0U)
			{ 				
				/*获取成功,处理数据*/
				ParseOneFrameData(tmpDataBuf,(UINT16_S)dataLen);
				retVal++;
			}
			else
			{
				break;
			}
		}
	}

    return retVal;

}
/*******************************************
函数名	：ParseOneFrameData
功能描述：解析一包外部通信设备的输入数据
输入	：dataBuf输入数据帧，dataLen输入数据帧长度，devType设备类型
输出	：无
返回值	：0：成功；1：解析ATS数据失败；
*******************************************/
static UINT8_S ParseOneFrameData(const UINT8_S dataBuf[], UINT16_S dataLen)
{
    UINT8_S retVal = DEFAULT_ZERO;

    if(dataLen > DEFAULT_ZERO)
    {
		/*LogBuff("RevAtsData:",dataBuf,dataLen);*/

		if (TSR_ERROR == ParseRcvFromAtsDataFrame(&dataBuf[ATS_FRAME_OFFSET], dataLen))/*解析ATS数据*/
		{
			
			/*LogMsgString(1, "ParseAtsToDmsData error\n");*/
			/*SetEventLogList(DMS_ATS_PARSE_ERROR,LOG_EVENT_ERROR,1u,0u);*/
			retVal = 1u;
		}
        else
        {
            /*do nothing*/
        }
    }

    return retVal;

}
/*******************************************
函数名	：Tsr_PackOutletDatas
功能描述：打包ATS输出数据
输入	：无
输出	：无
返回值	：无
*******************************************/
void Tsr_PackOutletDatas(void)
{
	PackReplyToAtsData();
	/*PacklogData();*/
}
