/************************************************************************
*
* 文件名   ：  ParsePackProcessManager.c
* 创建时间 ：  2015.08.14
* 作者     ：  ZC组
* 功能描述 ：  解析和组包ZC数据管理  
* 备  注	：  无
*
************************************************************************/

#include "ParsePackProcessManager.h"
#include "../../../Common/CircQueueStruct.h"
#include "../IOInterfaceProcess/IOInterfaceProcess.h"
#include "../../SysDataManager/SysDefine.h"
#include "ParsePackCiData.h"
#include "ParsePackAtsData.h"
#include "ParsePackTrainData.h"
#include "ParsePackZcData.h"
#include "ParsePackNtpData.h"
#include "../../TsrManager/TsrInterface.h"/*-bye-*/
#include "../../../Common/MemSet.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/Convert.h"

/*
* 功能描述： 解析输入数据
* 参数说明： void
* 返回值  ： void      
*/
void ParseInputData(void)
{
	/*清空上周期输入数据*/
	ClearInputDataProcess();

	/*解析Ats输入数据*/
	ParseAtsToZcData();/*-bye-*/

	/*解析CI输入数据*/
	ParseCiToZcData();

	/*解析车载ATP输入数据*/
	ParseTrainToZcData();

	/*解析CI输入数据*/
	ParseNZcToZcData();

	/*解析Ntp输入数据*/
	ParseNtpToZcData();
}

/*
* 功能描述： 清空输入数据处理
* 参数说明： 无
* 返回值  ： 无      
*/
void ClearInputDataProcess(void)
{
	/*清空ATS输入数据*/
	ClearCycleAtsOutputData();/*-bye-*/

	/*清空联锁输入数据*/
	ClearCycleCiInputData();

	/*清空车载Atp输入的数据*/
	ClearCycleTrainInputData();

	/*清空相邻ZC输入的数据*/
	ClearCycleNZcInputData();

	/*清空NTP输入的数据*/
	ClearCycleNtpInputData();
}

/*
* 功能描述： 解析CI输入数据
* 参数说明： void
* 返回值  ： 1,添加成功
*            0,添加失败     
*/
UINT8_S ParseCiToZcData(void)
{
	CirQueueStruct *ciToZcDataQueueStru = NULL;
	UINT32_S pkgCount = DEFAULT_ZERO;
	UINT8_S cycle = DEFAULT_ZERO;
	UINT32_S dataLen = DEFAULT_ZERO;
	UINT8_S tempDataBuff[ZC_CI_COM_BYTE_SUM_MAX] = {0U};
	UINT8_S breakFlag = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*获取CI到ZC的输入数据*/
	ciToZcDataQueueStru = GetCiToZcDataQueueStru();

	/*判断是否*/
	if (ciToZcDataQueueStru != NULL)
	{
		pkgCount = GetQueuePkgCount(ciToZcDataQueueStru); /*获取队列数据包个数*/

		for (cycle = 0U; cycle < pkgCount; cycle++)
		{
			/*清空长度*/
			dataLen = DEFAULT_ZERO;
			MemorySet(tempDataBuff,((UINT32_S)(ZC_CI_COM_BYTE_SUM_MAX)),0U,((UINT32_S)(ZC_CI_COM_BYTE_SUM_MAX)));

			/*获取一帧数据*/
			dataLen = GetQueuePkgData(ciToZcDataQueueStru, tempDataBuff, DATA_LEN_MAX); 

			if (dataLen > 0U)
			{ 
				/*获取成功*/
				ParseCiToZcFrameData(tempDataBuff, (UINT16_S)dataLen); 

				/*打印收到CI数据*/
				/*LogPrintf(1U,"29.001 CI [%d] Input,len=%d!!!\n",tempDataBuff[1],dataLen);*/
			}
			else
			{
				breakFlag = FLAG_SET;
				break;
			}
		}

		if (FLAG_SET == breakFlag)
		{
			rtnValue = RETURN_ERROR;
		} 
		else
		{
			rtnValue = RETURN_SUCCESS;
		}
		
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 解析车载ATP输入数据
* 参数说明： void
* 返回值  ： 1,添加成功
*            0,添加失败      
*/
UINT8_S ParseTrainToZcData(void)
{
	CirQueueStruct *pTrainToZcDataQueueStru = NULL;
	UINT32_S pkgCount = DEFAULT_ZERO;
	UINT8_S cycle = DEFAULT_ZERO;
	UINT32_S dataLen = DEFAULT_ZERO;
	UINT8_S tempDataBuff[ZC_TRAIN_COM_BYTE_SUM_MAX] = {0U};
	UINT8_S breakFlag = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*获取车载ATP到ZC的输入数据*/
	pTrainToZcDataQueueStru = GetTrainToZcDataQueueStru();

	/*判断是否*/
	if (pTrainToZcDataQueueStru != NULL)
	{
		pkgCount = GetQueuePkgCount(pTrainToZcDataQueueStru); /*获取队列数据包个数*/

		for (cycle = 0U; cycle < pkgCount; cycle++)
		{
			/*清空长度*/
			dataLen = DEFAULT_ZERO;
			MemorySet(tempDataBuff,((UINT32_S)(ZC_TRAIN_COM_BYTE_SUM_MAX)),DEFAULT_ZERO,((UINT32_S)(ZC_TRAIN_COM_BYTE_SUM_MAX)));

			/*获取一帧数据*/
			dataLen = GetQueuePkgData(pTrainToZcDataQueueStru, tempDataBuff, DATA_LEN_MAX); 

			if (dataLen > 0U)
			{ 
				/*获取成功*/
				ParseTrainToZcFrameData(tempDataBuff, (UINT16_S)dataLen); 
			}
			else
			{
				breakFlag = FLAG_SET;
				break;
			}
		}

		if (FLAG_SET == breakFlag)
		{
			rtnValue = RETURN_ERROR;
		} 
		else
		{
			rtnValue = RETURN_SUCCESS;
		}
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 解析NZc输入数据
* 参数说明： void
* 返回值  ： 1,添加成功
*            0,添加失败      
*/
/*解析CI输入数据*/
UINT8_S ParseNZcToZcData(void)
{
	CirQueueStruct *pNzcToZcDataQueueStru = NULL;
	UINT32_S pkgCount = DEFAULT_ZERO;
	UINT8_S cycle = DEFAULT_ZERO;
	UINT32_S dataLen = DEFAULT_ZERO;
	UINT8_S tempDataBuff[ZC_NZC_COM_BYTE_SUM_MAX];
	UINT8_S breakFlag = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*获取车载ATP到ZC的输入数据*/
	pNzcToZcDataQueueStru = GetNZcToZcDataQueueStru();

	/*判断是否*/
	if (pNzcToZcDataQueueStru != NULL)
	{
		pkgCount = GetQueuePkgCount(pNzcToZcDataQueueStru); /*获取队列数据包个数*/

		for (cycle = DEFAULT_ZERO; cycle < pkgCount; cycle++)
		{
			/*清空长度*/
			dataLen = DEFAULT_ZERO;
			MemorySet(tempDataBuff,((UINT32_S)(ZC_NZC_COM_BYTE_SUM_MAX)),DEFAULT_ZERO,((UINT32_S)(ZC_NZC_COM_BYTE_SUM_MAX)));

			/*获取一帧数据*/
			dataLen = GetQueuePkgData(pNzcToZcDataQueueStru, tempDataBuff, DATA_LEN_MAX); 

			if (dataLen > 0U)
			{ 
				/*获取成功*/
				ParseNzcToZcFrameData(tempDataBuff,(UINT16_S)dataLen); 
				/*LogPrintf(1U,"29.201  ParseNZc=%d,Input Data!\n",tempDataBuff[16]);*/
			}
			else
			{
				breakFlag = FLAG_SET;
				break;
			}
		}

		if (FLAG_SET == breakFlag)
		{
			rtnValue = RETURN_ERROR;
		} 
		else
		{
			rtnValue = RETURN_SUCCESS;
		}

	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 解析ats输入数据
* 参数说明： void
* 返回值  ： 成功解析的数据包的数量    
*/
UINT8_S ParseAtsToZcData(void)/*-bye-*/
{
	UINT8_S pktQuan = DEFAULT_ZERO;
	pktQuan = Tsr_ParseIncomingDatas();/*-bye-*/
	return pktQuan;
}


/*
* 功能描述： 解析Ntp输入数据
* 参数说明： void
* 返回值  ： 1,添加成功
*            0,添加失败      
*/
UINT8_S ParseNtpToZcData(void)
{
	CirQueueStruct *pNtpToZcDataQueueStru = NULL;
	UINT32_S pkgCount = DEFAULT_ZERO;
	UINT8_S cycle = DEFAULT_ZERO;
	UINT32_S dataLen = DEFAULT_ZERO;
	UINT8_S tempDataBuff[ZC_NTP_COM_BYTE_SUM_MAX] = {DEFAULT_ZERO};
	UINT8_S breakFlag = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*获取Ntp到ZC的输入数据*/
	pNtpToZcDataQueueStru = GetNtpToZcDataQueueStru();

	/*判断是否*/
	if (pNtpToZcDataQueueStru != NULL)
	{
		pkgCount = GetQueuePkgCount(pNtpToZcDataQueueStru); /*获取队列数据包个数*/

		for (cycle = DEFAULT_ZERO; cycle < pkgCount; cycle++)
		{
			/*清空长度*/
			dataLen = DEFAULT_ZERO;
			MemorySet(tempDataBuff,((UINT32_S)(ZC_NTP_COM_BYTE_SUM_MAX)),DEFAULT_ZERO,((UINT32_S)(ZC_NTP_COM_BYTE_SUM_MAX)));

			/*获取一帧数据*/
			dataLen = GetQueuePkgData(pNtpToZcDataQueueStru, tempDataBuff, DATA_LEN_MAX); 

			if (dataLen > 0U)
			{ 
				/*获取成功,处理数据*/
				ParseNtpToZcFrameData(tempDataBuff, (UINT16_S)dataLen); 
			}
			else
			{
				breakFlag = FLAG_SET;
				break;
			}
		}

		if (FLAG_SET == breakFlag)
		{
			rtnValue = RETURN_ERROR;
		} 
		else
		{
			rtnValue = RETURN_SUCCESS;
		}

	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 组帧输出数据
* 参数说明： void
* 返回值  ： void      
*/
void PackOutputData(void)
{
	/*组帧输出给CI的数据*/
	PackZcToCiData();

	/*组帧输出给ATS的数据*/
	PackZcToAtsData();

	/*组帧输出给车载ATP的数据*/
	PackZcToTrainData();

	/*组帧输出给NZc的数据*/
	PackZcToNZcData();

	/*组帧输出给Ntp的数据*/
	PackZcToNtpData();
	
	/*清空本周期输出数据*/
	ClearOutputDataProcess();
}

/*
* 功能描述： 清空输出数据处理
* 参数说明： 无
* 返回值  ： 无      
*/
void ClearOutputDataProcess(void)
{
	/*清空联锁输出数据*/
	ClearCycleCiOutputData();

	/*清空车载Atp输出的数据*/
	ClearCycleTrainOutputData();

	/*清空相邻ZC输出的数据*/
	ClearCycleNZcOutputData();

	/*清空Ats输出的数据*/
	ClearCycleAtsOutputData();

	/*清空Ntp输出的数据*/
	ClearCycleNtpOutputData();
}

/*
* 功能描述： 组帧输出给CI的数据
* 参数说明： void
* 返回值  ： 1,添加成功
*            0,添加失败
*/
UINT8_S PackZcToCiData(void)
{
	UINT8_S cycle = DEFAULT_ZERO;
	CirQueueStruct* pZcToCiQueueStru = NULL;            /*接收数据队列*/
	UINT32_S realDataLen = DEFAULT_ZERO;
	UINT8_S *pTempDataBuff = NULL;                     /*临时数据缓冲区*/
    UINT8_S rtnValue = 0U;

	pZcToCiQueueStru = GetZcToCiDataQueueStru();

	for (cycle = 0U;cycle < GetToCiCurSum();cycle++)
	{
		realDataLen = (UINT32_S)GetToCiIdDataBuffLen(cycle);
		pTempDataBuff = GetToCiDataBuffByIndex(cycle);

		if ((realDataLen > 0U) && (NULL != pTempDataBuff))
		{
			if(0 == AddQueueData(pZcToCiQueueStru, pTempDataBuff, realDataLen))
            {
                rtnValue = 1U;
            }
            else
            {
                rtnValue = 0U;
            }
		}
		else
		{
            /*不处理*/
		}	
	}

	return rtnValue;
}

/*
* 功能描述： 组帧输出给车载ATP的数据
* 参数说明： void
* 返回值  ： 1,添加成功
*            0,添加失败     
*/
UINT8_S PackZcToTrainData(void)
{
	UINT8_S cycle = DEFAULT_ZERO;
	CirQueueStruct* pZcToTrainQueueStru = NULL;            /*接收数据队列*/
	UINT32_S realDataLen = DEFAULT_ZERO;
	UINT8_S *pTempDataBuff = NULL;                     /*临时数据缓冲区*/
    UINT8_S rtnValue = 0U;

	pZcToTrainQueueStru = GetZcToTrainDataQueueStru();

	for (cycle = 0U;cycle < GetToTrainCurSum();cycle++)
	{
		realDataLen = (UINT32_S)GetToTrainIdDataBufLen(cycle);
		pTempDataBuff = GetToTrainBufDataOfIndex(cycle);

		if ((realDataLen > 0U) && (NULL != pTempDataBuff))
		{
			if (0 == AddQueueData(pZcToTrainQueueStru, pTempDataBuff, realDataLen))
			{
                rtnValue = 1U;
			} 
			else
			{
                rtnValue = 0U;
			}
			
		}
		else
		{
            /*不处理*/
		}	
	}

	return rtnValue;
}

/*
* 功能描述： 组帧输出给Ntp的数据
* 参数说明： void
* 返回值  ： 1,添加成功
*            0,添加失败      
*/
UINT8_S PackZcToNtpData(void)
{
	CirQueueStruct* pZcToNtpQueueStru = NULL;            /*接收数据队列*/
	UINT32_S realDataLen = DEFAULT_ZERO;
	UINT8_S *tempDataBuf = NULL;                     /*临时数据缓冲区*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	pZcToNtpQueueStru = GetZcToNtpDataQueueStru();
	realDataLen = (UINT32_S)GetZcToNtpDataLen();
	tempDataBuf = GetZcToNtpDataBuff();
    
	if ((realDataLen > 0U) 
		&& (NULL != tempDataBuf)
		&& (NULL != pZcToNtpQueueStru))
	{
		if (0 == AddQueueData(pZcToNtpQueueStru, tempDataBuf, realDataLen))
		{
            rtnValue = RETURN_SUCCESS;
		} 
		else
		{
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
* 功能描述： 组帧输出给NZc的数据
* 参数说明： void
* 返回值  ： 1,添加成功
*            0,添加失败      
*/
UINT8_S PackZcToNZcData(void)
{
	UINT8_S cycle = DEFAULT_ZERO;
	CirQueueStruct* pZcToNZcQueueStru = NULL;            /*接收数据队列*/
	UINT32_S realDataLen = DEFAULT_ZERO;
	UINT8_S *pTempDataBuff = NULL;                     /*临时数据缓冲区*/
    UINT8_S rtnValue = DEFAULT_ZERO;

	pZcToNZcQueueStru = GetZcToNZcDataQueueStru();

	for (cycle = DEFAULT_ZERO;cycle < GetZcToNZcCurSum();cycle++)
	{
		realDataLen = (UINT32_S)GetZcToNZcIdDataBufLen(cycle);
		pTempDataBuff = GetZcToNZcBufDataOfIndex(cycle);

		if ((realDataLen > 0U) && (NULL != pTempDataBuff))
		{
			if(0 == AddQueueData(pZcToNZcQueueStru, pTempDataBuff, realDataLen))
            {
                rtnValue = RETURN_SUCCESS;
            }
            else
            {
                rtnValue = RETURN_ERROR;
            }
		}
		else
		{
            rtnValue = RETURN_ERROR;
		}	
	}

	return rtnValue;
}

/*
* 功能描述： 组帧输出给Ats的数据
* 参数说明： void
* 返回值  ：  void   
*/
void PackZcToAtsData(void)/*-bye-*/
{
	PackTsrCommandsToAts();/*-bye-*/
}
