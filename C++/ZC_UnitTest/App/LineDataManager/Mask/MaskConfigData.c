/************************************************************************
*
* 文件名   ：  MaskConfigData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  码位配置数据
* 备  注   ：  无
*
************************************************************************/
#include "MaskConfigData.h"

ZcCiMaskConfigDataStruct gZcToCiMaskConfigDataStruBuff[COMM_CI_SUM_MAX];                              /*ZC-CI码位信息结构体*/
UINT16_S gZcToCiIdBuff[LINE_CI_SUM_MAX] = {LINE_CI_SUM_MAX};                                         /*定义ZC与Ci通信ID索引数组*/
UINT8_S  gZcToCiCurSum = 0U;                                                                         /*ZC输出CI的最大数量*/

ZcCiMaskConfigDataStruct gCiToZcMaskConfigDataStruBuff[COMM_CI_SUM_MAX];                              /*CI-ZC码位信息结构体*/
UINT16_S gCiToZiIdBuff[LINE_CI_SUM_MAX] = {LINE_CI_SUM_MAX};                                         /*CI输入的最大数量*/
UINT8_S  gCiToZcCurSum = 0U;

UINT16_S gToCiConfigSignalCrossIdBuff[SINGLE_ZC_TO_CI_MASK_SUM_MAX] = {DEFAULT_ZERO};              /*定义本ZC需要计算的信号机跨压*/
UINT16_S gSignalCrossNum = 0U;

UINT16_S gToCiConfigSignalLightOffIdBuff[SINGLE_ZC_TO_CI_MASK_SUM_MAX] = {DEFAULT_ZERO};           /*定义本ZC需要计算的信号机亮灭*/
UINT16_S gSignalLightOffNum = 0U;

/*
* 功能描述： 获取输出设备总个数
* 参数说明： const UINT8 destSystemType 目标系统类型  
* 返回值  ： 0: 获取数据失败
*			>0: 设备当前总数
*/
UINT8_S GetSendCommTargetNum(const UINT8_S destSystemType)
{
	UINT8_S returnValue = 0U;

	switch (destSystemType)
	{
	case INNER_DEVTYPE_CI:
		if (gZcToCiCurSum >= COMM_CI_SUM_MAX)
		{
			returnValue = 0U;
		} 
		else
		{
			returnValue = gZcToCiCurSum;
		}
		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* 功能描述： 获取某个设备对应的访问下标
* 参数说明： const UINT8 destSystemType 目标系统类型  
			 const UINT16_S destSystemId 目标ID
* 返回值  ： 0: 获取数据失败
*			>0: 通信设备的下标
*/
UINT8_S GetSendCommTargetIndex(const UINT8_S destSystemType,const UINT16_S destSystemId)
{
	UINT8_S returnValue = 0U;

	switch (destSystemType)
	{
		case INNER_DEVTYPE_CI:
            if ((destSystemId >= 1U)&&(destSystemId < LINE_CI_SUM_MAX ))
			{
				returnValue = (UINT8_S)gZcToCiIdBuff[destSystemId];
			}
			else
			{
				returnValue = COMM_CI_SUM_MAX;
			}
			break;

		default:
			returnValue = COMM_CI_SUM_MAX;
			break;
	}

	return returnValue;
}

/*
* 功能描述： 获取码位信息管理总数
* 参数说明： const UINT8 destSystemType 目标系统类型 
*			 const UINT16_S destSystemId 目标系统Id
* 返回值  ： 0: 获取数据失败
*			>0: 码位信息当前总数
*/
UINT16_S GetSendToOtherMaskSum(const UINT8_S destSystemType,const UINT16_S destSystemId)
{
	UINT16_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;

	switch (destSystemType)
	{
		case INNER_DEVTYPE_CI:
			commTargetIndex = GetSendCommTargetIndex(destSystemType,destSystemId);

			if (commTargetIndex < GetSendCommTargetNum(destSystemType))
			{
				returnValue = gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskCurSum;
			} 
			else
			{
				returnValue = 0U;
			}
			
			break;

		default:
			returnValue = 0U;
			break;
	}

	return returnValue;
}

/*
* 功能描述： 获取码位ID最大值
* 参数说明： const UINT8 destSystemType 目标系统类型
*			 const UINT16_S destSystemId 目标系统Id
* 返回值  ： 0: 获取数据失败
*			>0: 码位ID最大值
*/
UINT16_S GetSendToOtherMaskIdMax(const UINT8_S destSystemType,const UINT16_S destSystemId)
{
	UINT16_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;

	switch (destSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetSendCommTargetIndex(destSystemType,destSystemId);

		if (commTargetIndex < GetSendCommTargetNum(destSystemType))
		{
			returnValue = gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskIdMax;
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* 功能描述： 获取指定ZC接收指定系统码位总数
* 参数说明： const UINT8 sourceSystemType, 源系统类型
*			 const UINT16_S sourceSystemId 源系统ID
* 返回值  ： 0: 获取数据失败
*			>0: 码位总数      
*/
UINT16_S GetReceiveToZcMaskSum(const UINT8_S sourceSystemType,const UINT16_S sourceSystemId)
{
	UINT16_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;

	switch (sourceSystemType)
	{
		case INNER_DEVTYPE_CI:
			commTargetIndex = GetReceiveCommTargetIndex(sourceSystemType,sourceSystemId);

			if (commTargetIndex < GetReceiveCommTargetNum(sourceSystemType))
			{
				returnValue = gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskCurSum;
			} 
			else
			{
				returnValue = 0U;
			}

			break;

		default:
			returnValue = 0U;
			break;
	}

	return returnValue;
}

/*
* 功能描述： 获取码位ID最大值
* 参数说明： const UINT8 destSystemType 源系统类型  
*			 const UINT16_S sourceSystemId 源系统ID
* 返回值  ： 0: 获取数据失败
*			>0: 码位ID最大值
*/
UINT16_S GetReceiveToZcMaskIdMax(const UINT8_S sourceSystemType,const UINT16_S sourceSystemId)
{
	UINT16_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;

	switch (sourceSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetReceiveCommTargetIndex(sourceSystemType,sourceSystemId);

		if (commTargetIndex < GetReceiveCommTargetNum(sourceSystemType))
		{
			returnValue = gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskIdMax;
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* 功能描述： 获取发送给其他子系统指定数组下标对应的码位下标
* 参数说明： const UINT16 bufIndex, 数组下标
			 const UINT8_S destSystemType, 目标系统类型
			 const UINT16_S destSystemId 目标系统Id
* 返回值  ： 0: 获取数据失败
*			>0: 码位下标     
*/
UINT16_S GetSendMaskId(const UINT16_S bufIndex,const UINT8_S destSystemType,const UINT16_S destSystemId)
{
	UINT16_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;

	switch (destSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetSendCommTargetIndex(destSystemType,destSystemId);

		if (commTargetIndex < GetSendCommTargetNum(destSystemType))
		{		
			if (bufIndex < GetSendToOtherMaskSum(destSystemType,destSystemId))
			{
				returnValue = gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].MaskId;
			}
			else
			{
				returnValue = RETURN_ERROR;
			}
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* 功能描述： 获取指定ID码位索引号
* 参数说明： const UINT16 maskId,码位ID
*			 const UINT8_S destSystemType, 目标系统类型
*		     const UINT16_S destSystemId 目标系统Id
* 返回值  ： ZC_TO_CI_MASK_SUM_MAX; 获取数据失败
*			 >=0U;查找索引成功
*/
UINT16_S GetSendMaskBufIndex(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId)
{
	UINT16_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;

	switch (destSystemType)
	{
		case INNER_DEVTYPE_CI:
			commTargetIndex = GetSendCommTargetIndex(destSystemType,destSystemId);

			if (commTargetIndex < GetSendCommTargetNum(destSystemType))
			{
				if ((maskId >= 1U)&&(maskId < ZC_TO_CI_MASK_SUM_MAX))
				{
					returnValue = gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskIdBuff[maskId];
				}
				else
				{
					returnValue = ZC_TO_CI_MASK_SUM_MAX;
				}
			} 
			else
			{
				returnValue = ZC_TO_CI_MASK_SUM_MAX;
			}

			break;

		default:
			returnValue = ZC_TO_CI_MASK_SUM_MAX;
			break;
	}

	return returnValue;
}

/*
* 功能描述： 获取指定ID码位的码位类型
* 参数说明： const UINT16 maskId,码位ID
*			 const UINT8_S destSystemType, 目标系统类型
*			 const UINT16_S destSystemId 目标系统Id
* 返回值  ： 0 : 获取数据失败
*			 >0U; 码位类型信息
*/
UINT8_S GetSendMaskType(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId)
{
	UINT8_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;
	UINT16_S bufIndex = 0U;     /*数组下标*/

	switch (destSystemType)
	{
		case INNER_DEVTYPE_CI:
			commTargetIndex = GetSendCommTargetIndex(destSystemType,destSystemId);

			if (commTargetIndex < GetSendCommTargetNum(destSystemType))
			{
				bufIndex = GetSendMaskBufIndex(maskId,destSystemType,destSystemId);  /*获取数组下标*/			

				if (bufIndex < GetSendToOtherMaskSum(destSystemType,destSystemId))
				{
					returnValue = gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].MaskType;
				}
				else
				{
					returnValue = RETURN_ERROR;
				}
			} 
			else
			{
				returnValue = 0U;
			}

			break;

		default:
			returnValue = 0U;
			break;
	}

	return returnValue;
}

/*
* 功能描述： 获取指定ID码位的设备类型
* 参数说明： const UINT16 maskId,码位ID
*			 const UINT8_S destSystemType, 目标系统类型
*			 const UINT16_S destSystemId 目标系统Id
* 返回值  ： 0: 获取数据失败
*			 >0 设备类型信息
*/
UINT8_S GetSendDeviceType(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId)
{
	UINT8_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;
	UINT16_S bufIndex = 0U;     /*数组下标*/

	switch (destSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetSendCommTargetIndex(destSystemType,destSystemId);

		if (commTargetIndex < GetSendCommTargetNum(destSystemType))
		{
			bufIndex = GetSendMaskBufIndex(maskId,destSystemType,destSystemId);  /*获取数组下标*/			

			if (bufIndex < GetSendToOtherMaskSum(destSystemType,destSystemId))
			{
				returnValue = gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].DeviceType;
			}
			else
			{
				returnValue = RETURN_ERROR;
			}
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* 功能描述： 获取指定ID码位的设备数量
* 参数说明： const UINT16 maskId,码位ID
*				const UINT8_S destSystemType, 目标系统类型
*				const UINT16_S destSystemId 目标系统Id
* 返回值  ： 0: 获取数据失败
*			 >0 设备数量
*/
UINT8_S GetSendDeviceSum(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId)
{
	UINT8_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;
	UINT16_S bufIndex = 0U;     /*数组下标*/

	switch (destSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetSendCommTargetIndex(destSystemType,destSystemId);

		if (commTargetIndex < GetSendCommTargetNum(destSystemType))
		{
			bufIndex = GetSendMaskBufIndex(maskId,destSystemType,destSystemId);  /*获取数组下标*/			

			if (bufIndex < GetSendToOtherMaskSum(destSystemType,destSystemId))
			{
				returnValue = gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].DeviceSum;
			}
			else
			{
				returnValue = RETURN_ERROR;
			}
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* 功能描述： 获取指定ID码位的设备ID数组
* 参数说明： const UINT16 maskId,码位ID
*		     const UINT8_S destSystemType, 目标系统类型
*			 const UINT16_S destSystemId 目标系统Id
*			 const UINT8_S bufSize,数组大小
*			 UINT16_S deviceIdBuff[],输出数组
* 返回值  ： 0: 获取数据失败
*			 1: 成功
*/
UINT8_S GetSendDeviceIdBuff(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId,const UINT8_S bufSize,UINT16_S deviceIdBuff[])
{
	UINT8_S commTargetIndex = 0U;
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = 0U;
	UINT8_S cycle = 0U;

	switch (destSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetSendCommTargetIndex(destSystemType,destSystemId);

		if (commTargetIndex < GetSendCommTargetNum(destSystemType))
		{
			bufIndex = GetSendMaskBufIndex(maskId,destSystemType,destSystemId);  /*获取数组下标*/			

			if ((bufIndex < GetSendToOtherMaskSum(destSystemType,destSystemId))
				&& (bufSize >= SINGLE_MASK_DEVICE_SUM_MAX)
				&& (deviceIdBuff != NULL))
			{
				for (cycle = 0U;cycle < GetSendDeviceSum(maskId,destSystemType,destSystemId);cycle++)
				{
					deviceIdBuff[cycle] = gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].DeviceIdBuff[cycle];
				}
				rtnValue = RETURN_SUCCESS ;
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

		break;

	default:
		rtnValue = RETURN_ERROR;
		break;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID码位的关联码位Id
* 参数说明： const UINT16 maskId,码位ID
*			 const UINT8_S destSystemType, 目标系统类型
*			 const UINT16_S destSystemId 目标系统Id
* 返回值  ： 0: 获取数据失败
*			 >0 关联码位ID
*/
UINT16_S GetSendRelevanceMaskId(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId)
{
	UINT16_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;
	UINT16_S bufIndex = 0U;     /*数组下标*/

	switch (destSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetSendCommTargetIndex(destSystemType,destSystemId);

		if (commTargetIndex < GetSendCommTargetNum(destSystemType))
		{
			bufIndex = GetSendMaskBufIndex(maskId,destSystemType,destSystemId);  /*获取数组下标*/			

			if (bufIndex < GetSendToOtherMaskSum(destSystemType,destSystemId))
			{
				returnValue = gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].RelevanceMaskId;
			}
			else
			{
				returnValue = RETURN_ERROR;
			}
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* 功能描述： 获取输入设备总个数
* 参数说明： const UINT8 sourceSystemId 源系统ID  
* 返回值  ： 0: 获取数据失败
*			>0: 设备当前总数
*/
UINT8_S GetReceiveCommTargetNum(const UINT8_S sourceSystemId)
{
	UINT8_S returnValue = 0U;

	switch (sourceSystemId)
	{
	case INNER_DEVTYPE_CI:
		if (gCiToZcCurSum >= COMM_CI_SUM_MAX)
		{
			returnValue = 0U;
		} 
		else
		{
			returnValue = gCiToZcCurSum;
		}
		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* 功能描述： 获取接受某个设备的下标
* 参数说明： const UINT8 sourceSystemType 源系统类型  
*			 const UINT16_S sourceSystemId 源目标ID
* 返回值  ： COMM_CI_SUM_MAX: 获取数据失败
*			>0: 通讯对象的下标
*/
UINT8_S GetReceiveCommTargetIndex(const UINT8_S sourceSystemType,const UINT16_S sourceSystemId)
{
	UINT8_S returnValue = 0U;

	switch (sourceSystemType)
	{
	case INNER_DEVTYPE_CI:
		if ((sourceSystemId >= 1U)&&(sourceSystemId < LINE_CI_SUM_MAX))
		{
			returnValue = (UINT8_S)gCiToZiIdBuff[sourceSystemId];
		}
		else
		{
			returnValue = COMM_CI_SUM_MAX;
		}
		break;

	default:
		returnValue = COMM_CI_SUM_MAX;
		break;
	}

	return returnValue;
}

/*
* 功能描述： 获取指定接受数组下标对应的码位下标
* 参数说明： const UINT16 bufIndex, 数组下标
*			 const UINT8_S sourceSystemType, 源系统类型
*			 const UINT8_S sourceSystemId 源系统ID
* 返回值  ： 0: 获取数据失败
*			>0: 码位ID     
*/
UINT16_S GetReceiveMaskId(const UINT16_S bufIndex,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId)
{
	UINT16_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;

	switch (sourceSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetReceiveCommTargetIndex(sourceSystemType,sourceSystemId);

		if (commTargetIndex < GetReceiveCommTargetNum(sourceSystemType))
		{			
			if (bufIndex < GetReceiveToZcMaskSum(sourceSystemType,sourceSystemId))
			{
				returnValue = gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].MaskId;
			}
			else
			{
				returnValue = RETURN_ERROR;
			}
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* 功能描述： 获取指定ID码位索引号
* 参数说明： const UINT16 maskId,码位ID
*			 const UINT8_S sourceSystemType, 源系统类型
*			 const UINT16_S sourceSystemId 源系统ID
* 返回值  ： CI_TO_ZC_MASK_SUM_MAX: 获取数据失败
*			 >0 查找索引成功
*/
UINT16_S GetReceiveMaskBufIndex(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId)
{
	UINT16_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;

	switch (sourceSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetReceiveCommTargetIndex(sourceSystemType,sourceSystemId);

		if (commTargetIndex < GetReceiveCommTargetNum(sourceSystemType))
		{
			if ((maskId >= 1U)&&(maskId < CI_TO_ZC_MASK_SUM_MAX))
			{
				returnValue = gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskIdBuff[maskId];
			}
			else
			{
				returnValue = CI_TO_ZC_MASK_SUM_MAX;
			}
		} 
		else
		{
			returnValue = CI_TO_ZC_MASK_SUM_MAX;
		}

		break;

	default:
		returnValue = CI_TO_ZC_MASK_SUM_MAX;
		break;
	}

	return returnValue;
}

/*
* 功能描述： 获取指定ID码位的码位类型
* 参数说明： const UINT16 maskId,码位ID
*			const UINT8_S sourceSystemType, 源系统类型
*			const UINT16_S sourceSystemId 源系统ID
* 返回值  ： 0: 获取数据失败
*			 >0 码位类型信息
*/
UINT8_S GetReceiveMaskType(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId)
{
	UINT8_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;
	UINT16_S bufIndex = 0U;     /*数组下标*/

	switch (sourceSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetReceiveCommTargetIndex(sourceSystemType,sourceSystemId);

		if (commTargetIndex < GetReceiveCommTargetNum(sourceSystemType))
		{
			bufIndex = GetReceiveMaskBufIndex(maskId,sourceSystemType,sourceSystemId);  /*获取数组下标*/			

			if (bufIndex < GetReceiveToZcMaskSum(sourceSystemType,sourceSystemId))
			{
				returnValue = gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].MaskType;
			}
			else
			{
				returnValue = RETURN_ERROR;
			}
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* 功能描述： 获取指定ID码位的设备类型
* 参数说明： const UINT16 maskId,码位ID
*			 const UINT8_S sourceSystemType, 源系统类型
*			 const UINT16_S sourceSystemId 源系统ID
* 返回值  ： 0: 获取数据失败
*			 >0:设备类型信息
*/
UINT8_S GetReceiveDeviceType(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId)
{
	UINT8_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;
	UINT16_S bufIndex = 0U;     /*数组下标*/

	switch (sourceSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetReceiveCommTargetIndex(sourceSystemType,sourceSystemId);

		if (commTargetIndex < GetReceiveCommTargetNum(sourceSystemType))
		{
			bufIndex = GetReceiveMaskBufIndex(maskId,sourceSystemType,sourceSystemId);  /*获取数组下标*/			

			if (bufIndex < GetReceiveToZcMaskSum(sourceSystemType,sourceSystemId))
			{
				returnValue = gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].DeviceType;
			}
			else
			{
				returnValue = RETURN_ERROR;
			}
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* 功能描述： 获取指定ID码位的设备数量
* 参数说明： const UINT16 maskId,码位ID
*			 const UINT8_S sourceSystemType, 源系统类型
*			 const UINT16_S sourceSystemId 源系统ID
* 返回值  ： 0: 获取数据失败
*			 >0 设备数量
*/
UINT8_S GetReceiveDeviceSum(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId)
{
	UINT8_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;
	UINT16_S bufIndex = 0U;     /*数组下标*/

	switch (sourceSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetReceiveCommTargetIndex(sourceSystemType,sourceSystemId);

		if (commTargetIndex < GetReceiveCommTargetNum(sourceSystemType))
		{
			bufIndex = GetReceiveMaskBufIndex(maskId,sourceSystemType,sourceSystemId);  /*获取数组下标*/			

			if (bufIndex < GetReceiveToZcMaskSum(sourceSystemType,sourceSystemId))
			{
				returnValue = gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].DeviceSum;
			}
			else
			{
				returnValue = RETURN_ERROR;
			}
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* 功能描述： 获取指定ID码位的设备ID数组
* 参数说明： const UINT16 maskId,码位ID
*			 const UINT8_S sourceSystemType, 源系统类型
*			 const UINT16_S sourceSystemId 源系统ID
*			 const UINT8_S bufSize,数组大小
*			 UINT16_S deviceIdBuff[],输出数组
* 返回值  ： 0: 获取数据失败
*			 1: 获取数据成功
*/
UINT8_S GetReceiveDeviceIdBuff(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId,const UINT8_S bufSize,UINT16_S deviceIdBuff[])
{
	UINT8_S commTargetIndex = 0U;
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S cycle = 0U;
	UINT8_S rtnValue = 0U;

	switch (sourceSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetReceiveCommTargetIndex(sourceSystemType,sourceSystemId);

		if (commTargetIndex < GetReceiveCommTargetNum(sourceSystemType))
		{
			bufIndex = GetReceiveMaskBufIndex(maskId,sourceSystemType,sourceSystemId);  /*获取数组下标*/			

			if ((bufIndex < GetReceiveToZcMaskSum(sourceSystemType,sourceSystemId))
				&& (bufSize >= SINGLE_MASK_DEVICE_SUM_MAX)
				&& (deviceIdBuff != NULL))
			{
				for (cycle = 0U;cycle < GetReceiveDeviceSum(maskId,sourceSystemType,sourceSystemId);cycle++)
				{
					deviceIdBuff[cycle] = gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].DeviceIdBuff[cycle];
				}
				rtnValue = RETURN_SUCCESS ;
			}
			else
			{
				rtnValue = RETURN_ERROR ;
			}
		} 
		else
		{
			rtnValue = RETURN_ERROR ;
		}

		break;

	default:
		rtnValue = RETURN_ERROR ;
		break;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID码位的关联码位Id
* 参数说明： const UINT16 maskId,码位ID
*			 const UINT8_S sourceSystemType, 源系统类型
*			 const UINT16_S sourceSystemId 源系统ID
* 返回值  ： 0: 获取数据失败
*			 >0 关联码位ID
*/
UINT16_S GetReceiveRelevanceMaskId(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId)
{
	UINT16_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;
	UINT16_S bufIndex = 0U;     /*数组下标*/

	switch (sourceSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetReceiveCommTargetIndex(sourceSystemType,sourceSystemId);

		if (commTargetIndex < GetReceiveCommTargetNum(sourceSystemType))
		{
			bufIndex = GetReceiveMaskBufIndex(maskId,sourceSystemType,sourceSystemId);  /*获取数组下标*/			

			if (bufIndex < GetReceiveToZcMaskSum(sourceSystemType,sourceSystemId))
			{
				returnValue = gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].RelevanceMaskId;
			}
			else
			{
				returnValue = RETURN_ERROR;
			}
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* 功能描述： 获取本ZC关联的信号机跨压命令信号机数
* 参数说明： 无
* 返回值  ： 0: 获取数据失败
*			>0: 数量
*/
UINT16_S GetMaskOfSignalCorssNum(void)
{
    UINT16_S rtnValue = DEFAULT_ZERO;

	if (gSignalCrossNum < SINGLE_ZC_TO_CI_MASK_SUM_MAX)
	{
		rtnValue = gSignalCrossNum;
	} 
	else
	{
		rtnValue = DEFAULT_ZERO;
	}

    return rtnValue;
}

/*
* 功能描述： 获取本ZC关联的信号机跨压命令信号机Id信息
* 参数说明： const UINT16 buffSize,buff大小
*            UINT16_S signalIdBuff[],信号机IdBuff
* 返回值  ： 0: 获取数据失败
*			>0: 获取数据成功
*/
UINT8_S GetMaskOfSignalCorssIdBuff(const UINT16_S buffSize,UINT16_S signalIdBuff[])
{
	UINT16_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO; 

	if ((buffSize >= SINGLE_ZC_TO_CI_MASK_SUM_MAX) && (NULL != signalIdBuff))
	{
		for (cycle = DEFAULT_ZERO;cycle < GetMaskOfSignalCorssNum();cycle++)
		{
			signalIdBuff[cycle] = gToCiConfigSignalCrossIdBuff[cycle];
		}

		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

    return rtnValue;
}

/*
* 功能描述： 获取本ZC关联的信号机亮灭命令信号机数
* 参数说明： 无
* 返回值  ： 0: 获取数据失败
*			>0: 数量
*/
UINT16_S GetMaskOfSignalLightOffNum(void)
{
    UINT16_S rtnValue = DEFAULT_ZERO;

	if (gSignalLightOffNum < SINGLE_ZC_TO_CI_MASK_SUM_MAX)
	{
		rtnValue = gSignalLightOffNum;
	} 
	else
	{
		rtnValue = DEFAULT_ZERO;
	}

    return rtnValue;
}

/*
* 功能描述： 获取本ZC关联的信号机亮灭命令信号机Id信息
* 参数说明： const UINT16 buffSize,buff大小
*            UINT16_S signalIdBuff[],信号机IdBuff
* 返回值  ： 0: 获取数据失败
*			>0: 获取数据成功
*/
UINT8_S GetMaskOfSignalLightOffIdBuff(const UINT16_S buffSize,UINT16_S signalIdBuff[])
{
	UINT16_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

	if ((buffSize >= SINGLE_ZC_TO_CI_MASK_SUM_MAX) && (NULL != signalIdBuff))
	{
		for (cycle = DEFAULT_ZERO;cycle < GetMaskOfSignalLightOffNum();cycle++)
		{
			signalIdBuff[cycle] = gToCiConfigSignalLightOffIdBuff[cycle];
		}

		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

    return rtnValue;
}
