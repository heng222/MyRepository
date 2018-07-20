/************************************************************************
*
* 文件名   ：  ParsePackTrainData.c
* 创建时间 ：  2015.04.14
* 作者     ：  ZC组
* 功能描述 ：  解析组包列车数据管理  
* 备  注	：  无
*
************************************************************************/

#include "ParsePackTrainData.h"
#include "../../SysDataManager/SysDefine.h"
#include "../../TrainManager/Train/TrainDefine.h"
#include "../CommTarget/CommTargetStatusData.h"
#include "../CommTarget/CommTargetConfigData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../../Common/Convert.h"
#include "../../LineDataManager/DR/DRDefine.h"
#include "../../../Common/MemSet.h"
#include "../../../Common/Copy.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Dmu/DmuComm/Data/SegData.h"
#include "../../TrainManager/Train/TrainStatusData.h"

ZcAndTrainIODataStruct gToTrainDataStruBuff[SIZE_MAX_LINE_TRAIN];               /*zc给车载ATP的数据结构*/
UINT16_S gToTrainDataIdBuff[SIZE_MAX_LINE_TRAIN+1U] = {SIZE_MAX_LINE_TRAIN+1U};  /*ID索引数组*/
UINT8_S  gToTrainCurSum = 0U;                                                  /*ZC输出车载ATP的最大数量*/

ZcAndTrainIODataStruct TrainInDataStruBuff[SIZE_MAX_LINE_TRAIN];               /*车载ATP输入的数据结构*/
UINT16_S gTrainInDataIdBuff[SIZE_MAX_LINE_TRAIN+1U] = {SIZE_MAX_LINE_TRAIN+1U};  /*ID索引数组*/
UINT8_S  gTrainInCurSum = 0U;                                                  /*车载ATP输入的最大数量*/

/*
* 功能描述： 获取车载ATP输入的最大数量
* 参数说明： void
* 返回值  ： SIZE_MAX_LINE_TRAIN+1: 失败
*			>=0: 数量      
*/
UINT8_S GetTrainToZcCurSum(void)
{
	UINT8_S rtnValue = DEFAULT_ZERO;

	if (gTrainInCurSum <= SIZE_MAX_LINE_TRAIN)
	{
		rtnValue = gTrainInCurSum;
	} 
	else
	{
		rtnValue = SIZE_MAX_LINE_TRAIN+1U;
	}

	return rtnValue;
}

/*
* 功能描述：获取车载ATP输入Zc的Id对应列车ID
* 参数说明： const UINT8 trainIdOfIndex
* 返回值  ： 0: 失败
*			 >0: 成功      
*/
UINT16_S GetTrainToZcBuffIndexOfTrainId(const UINT8_S trainIdOfIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

    if (SIZE_MAX_LINE_TRAIN < trainIdOfIndex)
    {
        rtnValue = DEFAULT_ZERO;
    } 
    else
    {
        rtnValue = TrainInDataStruBuff[trainIdOfIndex].TrainId;
    }

	return rtnValue;
}

/*
* 功能描述：获取车载ATP输入Zc的Id对应数据长度
* 参数说明： const UINT8 ciIdOfIndex
* 返回值  ： 0: 失败
*			 >0: 成功      
*/
UINT16_S GetTrainToZcIdDataBufLen(const UINT8_S trainIdOfIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

    if (SIZE_MAX_LINE_TRAIN < trainIdOfIndex)
    {
        rtnValue = DEFAULT_ZERO;
    } 
    else
    {        
        rtnValue = TrainInDataStruBuff[trainIdOfIndex].ValueBuffLen;
    }

	return rtnValue;
}

/*
* 功能描述： 获取车载ATP输入Zc的Id对应数据信息
* 参数说明： const UINT8 trainIdOfIndex
* 返回值  ： NULL: 失败
*			 !NULL: 成功      
*/
UINT8_S* GetTrainToZcBufDataOfIndex(const UINT8_S trainIdOfIndex)
{
	UINT8_S *pRtnValue = NULL;

    if (SIZE_MAX_LINE_TRAIN < trainIdOfIndex)
    {
        pRtnValue = NULL;
    } 
    else
    {        
        pRtnValue = TrainInDataStruBuff[trainIdOfIndex].ValueBuff;
    }

	return pRtnValue;
}

/*
* 功能描述： 解析车载ATP输入的单帧数据
* 参数说明： const UINT8_S dataBuff[], 数据缓冲区
*            const UINT16_S dataLength, 数据长度
* 返回值  ： 0: 数据解析失败
*			 1: 数据解析成功      
*/
UINT8_S ParseTrainToZcFrameData(const UINT8_S dataBuff[], UINT16_S dataLength)
{
	UINT8_S sourceId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S copyRtn = DEFAULT_ZERO;
	UINT16_S headTest = DEFAULT_ZERO;
	UINT32_S headTestOffset = DEFAULT_ZERO;
	UINT16_S tailTest = DEFAULT_ZERO;
	UINT32_S tailTestOffset = DEFAULT_ZERO;
	/*
    UINT16_S controlZcId = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    */

	if ((dataBuff != NULL) && (dataLength > 0U))
	{
		/*解析帧头,判断是否为本ZC通信的车载ATP*/
		sourceId = dataBuff[1];

		if (sourceId < SIZE_MAX_LINE_TRAIN)
		{
			/*获取通信数据,判断输入数据是否合法*/
			if (RETURN_SUCCESS == TrainInputDataValidityCheck(&dataBuff[0],dataLength))
			{
				/* 待接口确定后写入数据 */
				/*填写列车Id*/
				TrainInDataStruBuff[gTrainInCurSum].TrainId = sourceId;

				/*获取数据长度*/
				TrainInDataStruBuff[gTrainInCurSum].ValueBuffLen = dataLength;
				copyRtn = MemoryCpy(TrainInDataStruBuff[gTrainInCurSum].ValueBuff,((UINT32_S)(ZC_TRAIN_COM_BYTE_SUM_MAX)),&dataBuff[0],((UINT32_S)TrainInDataStruBuff[gTrainInCurSum].ValueBuffLen));

				if (DEFAULT_ZERO == copyRtn)
				{
					gTrainInDataIdBuff[sourceId] = gTrainInCurSum;

					/*打印接收数据*/
					headTest = ShortFromChar(&TrainInDataStruBuff[gTrainInCurSum].ValueBuff[5]);
					headTestOffset = LongFromChar(&TrainInDataStruBuff[gTrainInCurSum].ValueBuff[7]);
					tailTest = ShortFromChar(&TrainInDataStruBuff[gTrainInCurSum].ValueBuff[11]);
					tailTestOffset = LongFromChar(&TrainInDataStruBuff[gTrainInCurSum].ValueBuff[13]);

#ifdef SYS_TYPE_WINDOWS
                    LogPrintf(1U,"2.1 Train[%d]Input,Loc:%d,%d;%d,%d;InType=%d,%d,len=%d\n",sourceId,headTest,headTestOffset,tailTest,tailTestOffset,TrainInDataStruBuff[gTrainInCurSum].ValueBuff[4],gTrainInCurSum,dataLength); 
#endif					
					gTrainInCurSum++;

					/*属于本ZC通信ATP, 更新通信状态*/
					SetCommTargetStatus(INNER_DEVTYPE_TRAIN,((UINT16_S)sourceId),COMM_STATUS_NORMAL);
#if 0
					/*11.30,dnw,增加不受本ZC控制的列车,不更新通信计时位*/
                    controlZcId = GetTrainControlZc((UINT16_S)sourceId);
                    localZcId = GetLocalZcId();

					if (localZcId == controlZcId)
					{
						SetCommTargetCycle(INNER_DEVTYPE_TRAIN,((UINT16_S)sourceId),DEFAULT_ZERO);
					} 
					else
					{
						/* 不处理 */
					}
#endif
                    SetCommTargetCycle(INNER_DEVTYPE_TRAIN,((UINT16_S)sourceId),DEFAULT_ZERO);

					rtnValue = RETURN_SUCCESS;
				} 
				else
				{
					gTrainInDataIdBuff[sourceId] = SIZE_MAX_LINE_TRAIN + 1U;
					TrainInDataStruBuff[gTrainInCurSum].TrainId = DEFAULT_ZERO;
					TrainInDataStruBuff[gTrainInCurSum].ValueBuffLen = DEFAULT_ZERO;
					rtnValue = RETURN_ERROR;
				}
			} 
			else
			{
				LogPrintf(1U,"Train Data Check Error!\n");
				rtnValue = RETURN_ERROR;
			}
		} 
		else
		{
			/*大于150号ID的列车不添加*/
		}
	}
	else
	{
		rtnValue =  RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 校验车载ATP输入的数据正确性
* 参数说明： const UINT8_S dataBuff[],数据数组   
*            const UINT16_S dataLen,数据长度
* 返回值  ： 0:合法性校验失败
*			 1:合法性校验成功      
*/
UINT8_S TrainInputDataValidityCheck(const UINT8_S dataBuff[], UINT16_S dataLen)
{
    UINT16_S addIndex = DEFAULT_ZERO;
	UINT16_S trainId = DEFAULT_ZERO;
	UINT16_S  trainHeadLink = DEFAULT_ZERO;        
	UINT32_S  trainHeadOffset = DEFAULT_ZERO;        
	UINT16_S  trainTailLink = DEFAULT_ZERO;         
	UINT32_S  trainTailOffset = DEFAULT_ZERO;        
	UINT8_S  trainRealDir = DEFAULT_ZERO;  
	UINT8_S trainUnSafeDir = DEFAULT_ZERO;
	UINT16_S checkErrorFlag = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
    UINT16_S trainLength = DEFAULT_ZERO;
	UINT16_S twoPointDist = DEFAULT_ZERO;
    UINT16_S lineMaxSpeed = DEFAULT_ZERO;
    UINT32_S lineMaxTSRSpeed = DEFAULT_ZERO;
	UINT32_S headLinkLen = DEFAULT_ZERO;
    UINT32_S tailLinkLen = DEFAULT_ZERO;

	if ((dataBuff != NULL) && (dataLen > 0U))
	{
		/*获取列车ID*/
		trainId = (UINT16_S)(ShortFromChar(&dataBuff[addIndex]) & ((UINT16_S)0x00ffU));
		addIndex = addIndex + 2U;

		/*跳过ZCId*/
		addIndex = addIndex + 2U;

		/*校验列车运行信息*/		
		if ((TRAIN_IN_APPLY_MA == dataBuff[addIndex])
			|| (TRAIN_IN_CHANGED == dataBuff[addIndex])
			|| (TRAIN_IN_HANDOVERTOCANCEL == dataBuff[addIndex])
			|| (TRAIN_IN_REVERSETOCANCEL == dataBuff[addIndex])
			|| (TRAIN_IN_TOEXITCBTC == dataBuff[addIndex]))
		{
			addIndex++;
		} 
		else
		{
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_1);
            addIndex++;
		}

		/*校验列车位置信息*/
		trainHeadLink = ShortFromChar(&dataBuff[addIndex]);
		addIndex = addIndex + 2U;

		trainHeadOffset = LongFromChar(&dataBuff[addIndex]);
		addIndex = addIndex + 4U;

		trainTailLink = ShortFromChar(&dataBuff[addIndex]);
		addIndex = addIndex + 2U;

		trainTailOffset = LongFromChar(&dataBuff[addIndex]);
		addIndex = addIndex + 4U;

        headLinkLen = GetSegDataStrulength(trainHeadLink);

        tailLinkLen = GetSegDataStrulength(trainTailLink);

        if ((headLinkLen >= trainHeadOffset) && (tailLinkLen >= trainTailOffset))
        {
            /* 输入位置信息合法 */
        } 
        else
        {
            checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_2);
        }
        
        /* 期望运行方向 */
        trainUnSafeDir = dataBuff[addIndex];
        addIndex = addIndex + 1U;
        
        /* 实际运行方向 */
        trainRealDir = dataBuff[addIndex];
        addIndex = addIndex + 1U;

		if (((TRAIN_UNSAFE_DIR_UP == trainUnSafeDir) || ((TRAIN_UNSAFE_DIR_DOWN == trainUnSafeDir))) &&
			((TRAIN_UNSAFE_DIR_UP == trainRealDir) || ((TRAIN_UNSAFE_DIR_DOWN == trainRealDir))))
		{
            /* 不处理 */
		} 
		else
		{
			/* 运行方向信息校验失败 */
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_3);
		}
         
		/*查询列车长度是否符合线路实际配置情况*/
		trainLength = GetTrainLength(trainId); 
		twoPointDist = (UINT16_S)CheckDistanceBetweenTwoPoints(trainTailLink,trainTailOffset,trainHeadLink,trainHeadOffset,trainUnSafeDir);
		if (trainLength >= twoPointDist)
		{
			/*车长信息校验成功*/
		} 
		else
		{
			/*车长信息校验失败*/
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_4);
		}	
        
		/*校验驾驶模式*/
		if ((TRAIN_IN_MODE_RM == dataBuff[addIndex])
			|| (TRAIN_IN_MODE_RD == dataBuff[addIndex])
			|| (TRAIN_IN_MODE_AM == dataBuff[addIndex])
			|| (TRAIN_IN_MODE_CM == dataBuff[addIndex])
			|| (TRAIN_IN_MODE_EUM == dataBuff[addIndex]))
		{
			addIndex++;
		} 
		else
		{
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_5);
            addIndex++;
		}

		/*校验运行级别*/
		if ((TRAIN_IN_LEVEL_BLOC == dataBuff[addIndex])
			|| (TRAIN_IN_LEVEL_CBTC == dataBuff[addIndex])
			|| (TRAIN_IN_LEVEL_IL == dataBuff[addIndex]))
		{
			addIndex++;
		} 
		else
		{
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_6);
            addIndex++;
		}

		/*校验列车速度*/
        lineMaxSpeed = GetLineMaxSpeed();
		if (ShortFromChar(&dataBuff[addIndex]) <= lineMaxSpeed)
		{
			addIndex = addIndex + 2U;
		} 
		else
		{
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_7);
            addIndex = addIndex + 2U;
		}

		/*校验停稳信息*/
		if ((FLAG_SET == dataBuff[addIndex])
			|| (FLAG_UNSET == dataBuff[addIndex]))
		{
			addIndex++;
		} 
		else
		{
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_8);
            addIndex++;
		}

		/*跳过不确定性误差和倒溜偏差*/
		addIndex = addIndex + 4U;

		/*校验列车限制速度*/
        lineMaxTSRSpeed = (((((UINT32_S)GetLineMaxTSRSpeed()) * 1000U) / 36U) & ((UINT32_S)0x0000ffffU));
		if (ShortFromChar(&dataBuff[addIndex]) <= lineMaxTSRSpeed)
		{
			addIndex = addIndex + 2U;
		} 
		else
		{
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_9);
            addIndex = addIndex + 2U;
		}

		/*校验列车完整性信息*/
		if ((FLAG_SET == dataBuff[addIndex])
			|| (FLAG_UNSET == dataBuff[addIndex]))
		{
			addIndex++;
		} 
		else
		{
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_10);
            addIndex++;
		}

		/*校验列车紧急制动信息*/
		if ((FLAG_SET == dataBuff[addIndex])
			|| (FLAG_UNSET == dataBuff[addIndex]))
		{
			addIndex++;
		} 
		else
		{
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_11);
            addIndex++;
		}

		/*跳过无人折返灯ID*/
		addIndex = addIndex + 2U;

		/*校验无人折返灯状态*/
		if ((DR_LAMP_TWINKLE_STATUS == dataBuff[addIndex])
			|| (DR_LAMP_STEADY_STATUS == dataBuff[addIndex])
			|| (DEFAULT_0XFF == dataBuff[addIndex]))
		{
			addIndex++;
		} 
		else
		{
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_12);
            addIndex++;
		}

		/*跳过保留字节*/
		addIndex = addIndex + 10U;

		if (addIndex == dataLen)
		{
            /*不处理*/
		} 
		else
		{
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_13);
		}
	}
	else
	{
		checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_14);
	}

	if (DEFAULT_ZERO == checkErrorFlag)
	{
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
        LogPrintf(1U,"TrainCheck[%d],%d,%d,%d\n",trainId,checkErrorFlag,addIndex,dataLen);
	}

	return rtnValue;
}

/*
* 功能描述： 获取ZC输出车载Atp的最大数量
* 参数说明： void
* 返回值  ： SIZE_MAX_LINE_TRAIN+1: 失败
*			 >0: 成功      
*/
UINT8_S GetToTrainCurSum(void)
{
	UINT8_S rtnValue = DEFAULT_ZERO;

	if (gToTrainCurSum <= SIZE_MAX_LINE_TRAIN)
	{
		rtnValue =  gToTrainCurSum;
	} 
	else
	{
		rtnValue =  SIZE_MAX_LINE_TRAIN + 1U;
	}

	return rtnValue;
}

/*
* 功能描述： 获取ZC输出车载ATP的Id对应数据长度
* 参数说明： const UINT8 trainIdOfIndex
* 返回值  ： 0: 失败
*			 >0: 成功      
*/
UINT16_S GetToTrainIdDataBufLen(const UINT8_S trainIdOfIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

    if (SIZE_MAX_LINE_TRAIN < trainIdOfIndex)
    {
        rtnValue = DEFAULT_ZERO;
    } 
    else
    {
        rtnValue = gToTrainDataStruBuff[trainIdOfIndex].ValueBuffLen;
    }

	return rtnValue;
}

/*
* 功能描述： 获取ZC输出车载Atp的Id下标对应缓存区
* 参数说明： const UINT8 trainIdOfIndex
* 返回值  ： NULL: 失败
*			 !NULL: 成功      
*/
UINT8_S* GetToTrainBufDataOfIndex(const UINT8_S trainIdOfIndex)
{
	UINT8_S *pRtnValue = NULL;

	if (SIZE_MAX_LINE_TRAIN < trainIdOfIndex)
	{
		pRtnValue = NULL;
	} 
	else
	{
        pRtnValue = gToTrainDataStruBuff[trainIdOfIndex].ValueBuff;
	}

	return pRtnValue;
}

/*
* 功能描述： 组车载ATP数据
* 参数说明： const UINT8* dataBuff,数据缓存
*            const UINT16_S dataLength,数据长度
*            const UINT16_S destId, 目标ID   
* 返回值  ： 0:组数据失败
*			 1:组数据成功      
*/
UINT8_S PackZcToTrainFrameData(const UINT8_S* dataBuff,const UINT16_S dataLength,const UINT16_S destId)
{
	UINT16_S index = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S copyRtn = 1U;

	if ((dataBuff != NULL) && (dataLength > 0U))
	{
		/*填写码位信息并组帧头*/
        if (SIZE_MAX_LINE_TRAIN <= gToTrainCurSum)
        {
            /*数据无效*/
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            gToTrainDataStruBuff[gToTrainCurSum].TrainId = (UINT8_S)destId;

            /*建立索引*/
            gToTrainDataIdBuff[destId] = gToTrainCurSum;

            /*填写信息帧头信息*/
            /*填写源设备*/
            gToTrainDataStruBuff[gToTrainCurSum].ValueBuff[index] = INNER_DEVTYPE_ZC;
            index = index + 1U;

            gToTrainDataStruBuff[gToTrainCurSum].ValueBuff[index] = (UINT8_S)GetLocalZcId();
            index = index + 1U;

            /*填写目标设备*/
            gToTrainDataStruBuff[gToTrainCurSum].ValueBuff[index] = INNER_DEVTYPE_TRAIN;
            index = index + 1U;

            gToTrainDataStruBuff[gToTrainCurSum].ValueBuff[index] = (UINT8_S)destId;
            index = index + 1U;

            gToTrainDataStruBuff[gToTrainCurSum].ValueBuffLen = dataLength;   /*dataLength + index*/

            /*复制数据*/
            /* 统一数据中已经把源类型、源ID、目的类型、目的ID共4个字节填写了,故下标从0开始 */
            copyRtn = MemoryCpy(&gToTrainDataStruBuff[gToTrainCurSum].ValueBuff[0],((UINT32_S)(ZC_TRAIN_COM_BYTE_SUM_MAX - (UINT32_S)index)),dataBuff,((UINT32_S)dataLength));

            if (1U == copyRtn)
            {
                /*清空信息*/
                gToTrainDataStruBuff[gToTrainCurSum].TrainId = 0U;		
                gToTrainDataIdBuff[destId] = LINE_CI_SUM_MAX;
                gToTrainDataStruBuff[gToTrainCurSum].ValueBuffLen = DEFAULT_ZERO;

                rtnValue = RETURN_ERROR;
            } 
            else
            {
                /*增加数量*/
                gToTrainCurSum++;
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
* 功能描述： 清空本周期所有车载Atp输入信息
* 参数说明： 无
* 返回值  ： 无      
*/
void ClearCycleTrainInputData(void)
{
	UINT8_S cycle = DEFAULT_ZERO;

	/*清空数据*/
	for (cycle = DEFAULT_ZERO;cycle < SIZE_MAX_LINE_TRAIN;cycle++)
	{
		MemorySet(&TrainInDataStruBuff[cycle],((UINT32_S)(sizeof(ZcAndTrainIODataStruct))),
                    DEFAULT_ZERO,((UINT32_S)(sizeof(ZcAndTrainIODataStruct))));
	}

	/*清空输入数量*/
	gTrainInCurSum = 0U;

	/*清空管理数组*/
	for (cycle = 0U;cycle < (SIZE_MAX_LINE_TRAIN + 1U);cycle++)
	{
		gTrainInDataIdBuff[cycle] = SIZE_MAX_LINE_TRAIN + 1U;
	}
}

/*
* 功能描述： 清空本周期所有输出给车载Atp信息
* 参数说明： 无
* 返回值  ： 无      
*/
void ClearCycleTrainOutputData(void)
{
	UINT8_S cycle = DEFAULT_ZERO;

	/*清空数据*/
	for (cycle = DEFAULT_ZERO;cycle < SIZE_MAX_LINE_TRAIN;cycle++)
	{
		MemorySet(&gToTrainDataStruBuff[cycle],((UINT32_S)(sizeof(ZcAndTrainIODataStruct))),
                     DEFAULT_ZERO,((UINT32_S)(sizeof(ZcAndTrainIODataStruct))));
	}

	/*清空输出数量*/
	gToTrainCurSum = 0U;

	/*清空管理数组*/
	for (cycle = 0U;cycle < (SIZE_MAX_LINE_TRAIN + 1U);cycle++)
	{
		gToTrainDataIdBuff[cycle] = SIZE_MAX_LINE_TRAIN + 1U;
	}
}
