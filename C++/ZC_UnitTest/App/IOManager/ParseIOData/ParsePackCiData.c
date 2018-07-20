/************************************************************************
*
* 文件名   ：  ParsePackCiData.c
* 创建时间 ：  2015.08.14
* 作者     ：  ZC组
* 功能描述 ：  解析和打包联锁数据
* 备  注	：  无
*
************************************************************************/

#include "ParsePackCiData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../CommTarget/CommTargetConfigData.h"
#include "../CommTarget/CommTargetStatusData.h"
#include "../../../Common/Copy.h"
#include "../../../Common/MemSet.h"
#include "../../../Common/Convert.h"
#include "../../MaintainManager/MaintainManager.h"


ZcAndCiIODataStruct gToCiDataStruBuff[COMM_CI_SUM_MAX];                      /*zc给ci的数据结构*/
UINT16_S gToCiDataIdBuff[LINE_CI_SUM_MAX] = {LINE_CI_SUM_MAX};              /*ID索引数组*/
UINT8_S  gToCiCurSum = 0U;                                                  /*ZC输出CI的最大数量*/

ZcAndCiIODataStruct gCiInDataStruBuff[COMM_CI_SUM_MAX];                      /*ci输入的数据结构*/
UINT16_S gCiInDataIdBuff[LINE_CI_SUM_MAX] = {LINE_CI_SUM_MAX};              /*ID索引数组*/
UINT8_S  gCiInCurSum = 0U;                                                  /*CI输入的最大数量*/

/*
* 功能描述： 解析CI输入的单帧数据
* 参数说明： const UINT8 dataBuff[], 数据缓冲区
*            const UINT16_S dataLength, 数据长度
* 返回值  ： 0: 数据解析失败
*			 1: 数据解析成功      
*/
UINT8_S ParseCiToZcFrameData(const UINT8_S dataBuff[], UINT16_S dataLength)
{
	UINT8_S sourceId = DEFAULT_ZERO;
	UINT8_S tempRtn = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S copyRtn = DEFAULT_ZERO;
    UINT8_S checkRtn = DEFAULT_ZERO;

	if ((dataBuff != NULL) && (dataLength > 0U))
	{
		/*解析帧头,判断是否为本ZC通信的CI*/
		sourceId = dataBuff[1];
		tempRtn = GetCommTargetIdInConfigData(INNER_DEVTYPE_CI,((UINT16_S)sourceId));
		checkRtn = CiInputDataValidityCheck(dataBuff,dataLength);

		if ((RETURN_SUCCESS == tempRtn) && (1U == checkRtn))
		{
			/*获取通信数据*/
			if ((LINE_CI_SUM_MAX == gCiInDataIdBuff[sourceId]) && (LINE_CI_SUM_MAX > gCiInCurSum))
			{
				/*填写Id信息*/
				gCiInDataStruBuff[gCiInCurSum].CiId = sourceId;

				/*获取数据长度*/
				gCiInDataStruBuff[gCiInCurSum].MaskValueBuffLen = dataLength - 4U;
				
				copyRtn = MemoryCpy(gCiInDataStruBuff[gCiInCurSum].MaskValueBuff,((UINT32_S)(ZC_TO_CI_MASK_SUM_MAX)),&dataBuff[4],((UINT32_S)gCiInDataStruBuff[gCiInCurSum].MaskValueBuffLen));

				if (0U == copyRtn)
				{
					/*建立索引*/
					gCiInDataIdBuff[sourceId] = gCiInCurSum;

					/*增加数量*/
					gCiInCurSum++;

					/*属于本ZC通信Ci, 更新通信状态*/
					SetCommTargetStatus(INNER_DEVTYPE_CI,((UINT16_S)sourceId),COMM_STATUS_NORMAL);
					SetCommTargetCycle(INNER_DEVTYPE_CI,((UINT16_S)sourceId),DEFAULT_ZERO);

					rtnValue = RETURN_SUCCESS;
				} 
				else
				{
					/*清空信息*/
					gCiInDataIdBuff[sourceId] = LINE_CI_SUM_MAX;
					gCiInDataStruBuff[gCiInCurSum].CiId = DEFAULT_ZERO;
					gCiInDataStruBuff[gCiInCurSum].MaskValueBuffLen = DEFAULT_ZERO;
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
			/*数据无效*/
			rtnValue = RETURN_ERROR;
		}
	}
	else
	{
		/*数据无效*/
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 校验CI输入的数据正确性
* 参数说明： const UINT8_S dataBuff[],数据数组   
*            const UINT16_S dataLen,数据长度
* 返回值  ： 0:合法性校验失败
*			 1:合法性校验成功      
*/
UINT8_S CiInputDataValidityCheck(const UINT8_S dataBuff[], UINT16_S dataLen)
{
    UINT8_S rtnValue = 0U;

    if((NULL != dataBuff) && (dataLen > 0U))
    {
        if ((INNER_DEVTYPE_CI == dataBuff[0]) && (INNER_DEVTYPE_ZC == dataBuff[2]))
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
        rtnValue = 0U;
    }

    return rtnValue;
}
/*
* 功能描述： 获取Ci输入Zc的最大数量
* 参数说明： void
* 返回值  ： 0: 失败
*			 >0: 数量      
*/
UINT8_S GetCiToZcCurSum(void)
{
	UINT8_S rtnValue = DEFAULT_ZERO;

	if ((gCiInCurSum > 0U) && (COMM_CI_SUM_MAX >= gCiInCurSum))
	{
		rtnValue = gCiInCurSum; 
	} 
	else
	{
		rtnValue = DEFAULT_ZERO;
	}

	return rtnValue;
}

/*
* 功能描述：获取Ci输入Zc的Id对应CIid
* 参数说明： const UINT8 ciIdOfIndex
* 返回值  ： COMM_CI_SUM_MAX: 失败
*			 >=0U: 成功      
*/
UINT16_S GetCiToZcBuffIndexOfCiId(const UINT8_S ciIdOfIndex)
{
	UINT16_S rtnValue = COMM_CI_SUM_MAX;

    if (COMM_CI_SUM_MAX <= ciIdOfIndex)
    {
        rtnValue = COMM_CI_SUM_MAX;
    } 
    else
    {
        rtnValue = (UINT16_S)gCiInDataStruBuff[ciIdOfIndex].CiId;
    }

	return rtnValue;
}
/*
* 功能描述：获取Ci输入Zc的Id对应数据长度
* 参数说明： const UINT8 ciIdOfIndex
* 返回值  ： 0: 失败
*			 >0: 成功      
*/
UINT16_S GetCiToZcIdDataBuffLen(const UINT8_S ciIdOfIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (COMM_CI_SUM_MAX <= ciIdOfIndex)
	{
        rtnValue = DEFAULT_ZERO;
    } 
	else
	{
        rtnValue = gCiInDataStruBuff[ciIdOfIndex].MaskValueBuffLen;
	}

	return rtnValue;
}

/*
* 功能描述： 获取Ci输入Zc的Id对应下标
* 参数说明： const UINT8 ciIdOfIndex
* 返回值  ： NULL: 失败
*			 非NULL: 成功      
*/
UINT8_S* GetCiToZcDataBuffByIndex(const UINT8_S ciIdOfIndex)
{
	UINT8_S *pRtnBuff = NULL;

    if (COMM_CI_SUM_MAX <= ciIdOfIndex)
    {
        pRtnBuff = NULL;
    } 
    else
    {
        pRtnBuff = gCiInDataStruBuff[ciIdOfIndex].MaskValueBuff;
    }

	return pRtnBuff;
}

/*
* 功能描述： 组包输出给Ci的单帧数据
* 参数说明：  const UINT8_S dataBuff[], 数据缓冲区
*             UINT16_S dataLength, 数据长度
*             UINT16_S destId, 目标CI设备ID
* 返回值  ： 0: 数据打包失败
*			 1: 数据打包成功      
*/
UINT8_S PackZcToCiFrameData(const UINT8_S dataBuff[], UINT16_S dataLength,UINT16_S destId)
{
	UINT16_S index = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S copyRtn = 1U;

	if ((dataBuff != NULL) && (dataLength > 0U))
	{
		/*填写码位信息并组帧头*/
		if (LINE_CI_SUM_MAX <= gToCiCurSum)
		{
            /*数据无效*/
            rtnValue = RETURN_ERROR;			
		}
		else
		{			
            gToCiDataStruBuff[gToCiCurSum].CiId = (UINT8_S)destId;

            /*建立索引*/
            gCiInDataIdBuff[destId] = gToCiCurSum;

            /*填写信息帧头信息*/
            /*填写源设备*/
            gToCiDataStruBuff[gToCiCurSum].MaskValueBuff[index] = INNER_DEVTYPE_ZC;
            index = index + 1U;

            gToCiDataStruBuff[gToCiCurSum].MaskValueBuff[index] = (UINT8_S)GetLocalZcId();
            index = index + 1U;

            /*填写目标设备*/
            gToCiDataStruBuff[gToCiCurSum].MaskValueBuff[index] = INNER_DEVTYPE_CI;
            index = index + 1U;

            gToCiDataStruBuff[gToCiCurSum].MaskValueBuff[index] = (UINT8_S)destId;
            index = index + 1U;

            gToCiDataStruBuff[gToCiCurSum].MaskValueBuffLen = dataLength + index;

            /*复制数据*/
            copyRtn = MemoryCpy(&gToCiDataStruBuff[gToCiCurSum].MaskValueBuff[index],((UINT32_S)(ZC_TO_CI_MASK_SUM_MAX)),dataBuff,((UINT32_S)dataLength));

            if (1U == copyRtn)
            {
                /*清空信息*/
                gToCiDataStruBuff[gToCiCurSum].CiId = 0U;		
                gCiInDataIdBuff[destId] = LINE_CI_SUM_MAX;
                gToCiDataStruBuff[gToCiCurSum].MaskValueBuffLen = DEFAULT_ZERO;

                rtnValue = RETURN_ERROR;
            } 
            else
            {
                /*增加数量*/
                gToCiCurSum++;
                rtnValue = RETURN_SUCCESS;
            }
		}	
	}
	else
	{
		/*数据无效*/
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取ZC输出CI的最大数量
* 参数说明： void
* 返回值  ： 0: 失败
*			 >0: 成功     
*/
UINT8_S GetToCiCurSum(void)
{
	UINT8_S rtnValue = DEFAULT_ZERO;

	if ((gToCiCurSum > 0U) && (COMM_CI_SUM_MAX >= gToCiCurSum))
	{
		rtnValue = gToCiCurSum; 
	} 
	else
	{
		rtnValue = DEFAULT_ZERO;
	}

	return rtnValue;
}

/*
* 功能描述： 获取ZC输出CI的Id数据长度
* 参数说明： const UINT8 ciIdOfIndex
* 返回值  ： 0: 失败
*			 >0: 成功      
*/
UINT16_S GetToCiIdDataBuffLen(const UINT8_S ciIdOfIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if ((COMM_CI_SUM_MAX <= ciIdOfIndex))
	{
        rtnValue = DEFAULT_ZERO;
	} 
	else
	{       
        rtnValue = gToCiDataStruBuff[ciIdOfIndex].MaskValueBuffLen;
	}

	return rtnValue;
}

/*
* 功能描述： 获取ZC输出CI的Id对应下标数据
* 参数说明： const UINT8 ciIdOfIndex
* 返回值  ： NULL: 失败
*			 非NULL: 成功      
*/
UINT8_S* GetToCiDataBuffByIndex(const UINT8_S ciIdOfIndex)
{
	UINT8_S *pRtnBuff = NULL;

    if (COMM_CI_SUM_MAX <= ciIdOfIndex)
    {
        pRtnBuff = NULL;
    } 
    else
    {
        pRtnBuff = gToCiDataStruBuff[ciIdOfIndex].MaskValueBuff;
    }

	return pRtnBuff;
}


/*
* 功能描述： 清空本周期所有输入的CI输入信息
* 参数说明： 无
* 返回值  ： 无      
*/
void ClearCycleCiInputData(void)
{
	UINT8_S cycle = DEFAULT_ZERO;

	/*清空数据*/
	for (cycle = 0U;cycle < COMM_CI_SUM_MAX;cycle++)
	{
		MemorySet(&gCiInDataStruBuff[cycle],((UINT32_S)(sizeof(ZcAndCiIODataStruct))),
                   DEFAULT_ZERO,((UINT32_S)(sizeof(ZcAndCiIODataStruct))));
	}
	
	/*清空输入数量*/
	gCiInCurSum = 0U;

	/*清空管理数组*/
	for (cycle = 0U;cycle < LINE_CI_SUM_MAX;cycle++)
	{
		gCiInDataIdBuff[cycle] = LINE_CI_SUM_MAX;
	}
}

/*
* 功能描述： 清空本周期所有输出给CI输入信息
* 参数说明： 无
* 返回值  ： 无      
*/
void ClearCycleCiOutputData(void)
{
	UINT8_S cycle = DEFAULT_ZERO;

	/*清空数据*/
	for (cycle = 0U;cycle < COMM_CI_SUM_MAX;cycle++)
	{
		MemorySet(&gToCiDataStruBuff[cycle],((UINT32_S)(sizeof(ZcAndCiIODataStruct))),
                     DEFAULT_ZERO,((UINT32_S)(sizeof(ZcAndCiIODataStruct))));
	}

	/*清空输出数量*/
	gToCiCurSum = 0U;

	/*清空管理数组*/
	for (cycle = 0U;cycle < LINE_CI_SUM_MAX;cycle++)
	{
		gToCiDataIdBuff[cycle] = LINE_CI_SUM_MAX;
	}
}
