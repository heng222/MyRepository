/********************************************************                                                                                                            
 文 件 名： MAStatusData.c  
 作    者： ZC组
 创建时间： 2015-04-18
 描述： 列车状态数据管理  
 备注： 无  
********************************************************/
#include "MAStatusData.h"
#include "../../../Common/Copy.h"
#include "../../../Common/MemSet.h"

MaDataStruct gMaDataStruBuff[COMM_TRAIN_SUM_MAX];                                    /*定义本ZC控制范围内最大列车移动授权数量*/
UINT8_S gMaDataIndexBuff[LINE_MAX_TRAIN_ID] = {LINE_MAX_TRAIN_ID};			        /*定义列车移动授权索引数组，数组长度为线路可能的最大列车ID*/
UINT8_S gMaCurSum = 0U;									                            /*本ZC移动授权当前列车数量*/

NextZcMaDataStruct gNextZcDataStruBuff[COMM_TRAIN_SUM_MAX];               /*定义相邻ZC控制范围内最大列车移动授权数量*/
UINT8_S gNextZcMaDataIndexBuff[LINE_MAX_TRAIN_ID] = {LINE_MAX_TRAIN_ID};  /*定义相邻ZC列车移动授权索引数组，数组长度为线路可能的最大列车ID*/
UINT8_S gNextZcMaCurSum = 0U;                                             /*保存相邻ZC MA2数量*/

/*************************************************
  函数名:      GetNextZcMaStatusSum
  功能描述:    获取相邻ZC列车移动授权管理总数
  输入:        无
  输出:        无
  返回值:      0u: 获取数据失败
               >0u: 列车移动授权管理总数
*************************************************/
UINT16_S GetNextZcMaStatusSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;
		
	if ((gNextZcMaCurSum > DEFAULT_ZERO) && (gNextZcMaCurSum <= COMM_TRAIN_SUM_MAX))
	{
		rtnValue = gNextZcMaCurSum;
	} 
	else
	{
		rtnValue = 0U;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetNextZcMaStatusSum
  功能描述:    设置相邻ZC列车移动授权管理总数
  输入:        const UINT8 maCurSum  移动授权目前总数 
  输出:        无
  返回值:      RETURN_ERROR:    设置数据失败
               RETURN_SUCCESS: 设置数据成功
*************************************************/
UINT16_S SetNextZcMaStatusSum(const UINT8_S maCurSum)
{
	UINT16_S rtnValue = 0U;

	if ((gNextZcMaCurSum > DEFAULT_ZERO) && (gNextZcMaCurSum <= COMM_TRAIN_SUM_MAX))
	{
		gNextZcMaCurSum = maCurSum;
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetNextZcMaStatusBufIndex
  功能描述:    根据列车ID，获取相邻ZC列车移动授权管理数组下标
  输入:        const UINT16_S trainId  列车ID
  输出:        无
  返回值:      LINE_MAX_TRAIN_ID:      获取数据失败
               (0u,LINE_MAX_TRAIN_ID): 获取数据成功
*************************************************/
UINT8_S GetNextZcMaStatusBufIndex(const UINT16_S trainId)
{
	UINT8_S rtnValue = 0U;

	if ((trainId > DEFAULT_ZERO) && (trainId <= LINE_MAX_TRAIN_ID))
	{
		rtnValue = gNextZcMaDataIndexBuff[trainId];
	} 
	else
	{
		rtnValue = LINE_MAX_TRAIN_ID;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetNextZcHandOutType
  功能描述:    根据列车ID，获取计算该移动授权的相邻ZC输入类型
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE:    获取数据失败
               <RETURN_UINT8_MAX_VALUE:   相邻ZC输入类型
*************************************************/
UINT8_S GetNextZcHandOutType(const UINT16_S trainId)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].HandOutType;
	} 
	else
	{
		rtnValue = RETURN_UINT8_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetNextZcHandOutType
  功能描述:    根据列车ID，设置计算该移动授权的相邻ZC输入类型
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_ERROR: 设置数据失败
               RETURN_SUCCESS: 成功设置相邻ZC输入类型
*************************************************/
UINT8_S SetNextZcHandOutType(const UINT16_S trainId,const UINT8_S handOutType)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].HandOutType = handOutType;
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetNextZcId
  功能描述:    根据列车ID，获取计算该移动授权的相邻ZCID
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_UINT16_MAX_VALUE: 获取数据失败
               <RETURN_UINT16_MAX_VALUE: 相邻ZCID
*************************************************/
UINT16_S GetNextZcId(const UINT16_S trainId)
{
	UINT8_S trainIndex = 0U;
	UINT16_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].NextId;
	} 
	else
	{
		rtnValue = RETURN_UINT16_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetNextZcId
  功能描述:    根据列车ID，设置计算该移动授权的相邻ZCID
  输入:        const UINT16_S trainId  列车ID 
               const UINT16_S zcId  相邻ZC的编号
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT16_S SetNextZcId(const UINT16_S trainId,const UINT16_S zcId)
{
	UINT8_S trainIndex = 0U;
	UINT16_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].NextId = zcId;
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetNextZcMaInfoFlag
  功能描述:    根据列车ID，获取相邻ZC列车移动授权存在标志
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE: 获取数据失败
               FLAG_SET: 存在MA
               FLAG_UNSET:不存在MA
*************************************************/
UINT8_S GetNextZcMaInfoFlag(const UINT16_S trainId)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].MaInfoFlag;
	} 
	else
	{
		rtnValue = RETURN_UINT8_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetNextZcMaInfoFlag
  功能描述:    根据列车ID，设置相邻ZC列车移动授权存在标志
  输入:        const UINT16_S trainId  列车ID 
               const UINT8_S maInfoFlag  标识
  输出:        无
  返回值:      RETURN_ERROR:   设置数据失败
               RETURN_SUCCESS: 设置数据成功
*************************************************/
UINT8_S SetNextZcMaInfoFlag(const UINT16_S trainId,const UINT8_S maInfoFlag)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].MaInfoFlag = maInfoFlag;
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetNextZcMaExceedBoundaryFlag
  功能描述:    根据列车ID，获取相邻ZC列车移动授权越过分界点标志
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               FLAG_SET: 越过分界点
               FLAG_UNSET:未越过分界点
*************************************************/
UINT8_S GetNextZcMaExceedBoundaryFlag(const UINT16_S trainId)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].ExceedBoundaryFlag;
	} 
	else
	{
		rtnValue = RETURN_UINT8_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetNextZcMaStatusMaLength
  功能描述:    根据列车ID，获取相邻ZC列车移动授权长度
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE: 获取数据失败
               <RETURN_UINT8_MAX_VALUE:MA2长度
*************************************************/
UINT8_S GetNextZcMaStatusMaLength(const UINT16_S trainId)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].MaLength;
	} 
	else
	{
		rtnValue = RETURN_UINT8_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetNextZcMaStatusMaLength
  功能描述:    根据列车ID，获取相邻ZC列车移动授权长度
  输入:        const UINT16_S trainId  列车ID 
               const UINT8_S maLength  MA长度
  输出:        无
  返回值:      RETURN_ERROR:  设置数据失败
               RETURN_SUCCESS:设置数据成功
*************************************************/
UINT8_S SetNextZcMaStatusMaLength(const UINT16_S trainId,const UINT8_S maLength)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].MaLength = maLength;
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetNextZcMaHeadLink
  功能描述:    获取移动授权起点LINK
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_ERROR:  获取数据失败
               >0u: 起点LINK
*************************************************/
UINT16_S GetNextZcMaHeadLink(const UINT16_S trianId)
{
	UINT8_S trainIndex = 0U;     /*数组下标*/
	UINT16_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].MaHeadLink;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetNextZcMaHeadLink
  功能描述:    设置移动授权起点LINK
  输入:        const UINT16_S trainId  列车ID 
               const UINT16_S link MA起点link
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetNextZcMaHeadLink(const UINT16_S trianId, const UINT16_S link)
{
	UINT8_S trainIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].MaHeadLink = link;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetNextZcMaHeadOffset
  功能描述:    获取MA2移动授权起点offset
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_UINT32_MAX_VALUE: 获取数据失败
               <RETURN_UINT32_MAX_VALUE: 起点offset
*************************************************/
UINT32_S GetNextZcMaHeadOffset(const UINT16_S trianId)
{
	UINT8_S trainIndex = 0U;     /*数组下标*/
	UINT32_S rtnValue = 0U;

	trainIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].MaHeadOffset;
	}
	else
	{

		rtnValue = RETURN_UINT32_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetNextZcMaHeadOffset
  功能描述:    设置MA2移动授权起点offset
  输入:        const UINT16_S trainId  列车ID 
               const UINT32_S offset  起点偏移量
  输出:        无
  返回值:      RETURN_SUCCESS: 设置成功
               RETURN_ERROR:   设置失败
*************************************************/
UINT8_S SetNextZcMaHeadOffset(const UINT16_S trianId, const UINT32_S offset)
{
	UINT8_S trainIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = 0U;

	trainIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].MaHeadOffset = offset;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetNextZcMaHeadDir
  功能描述:    获取相邻ZC移动授权起点方向
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE: 设置成功
               <RETURN_UINT8_MAX_VALUE: 起点LINK方向
*************************************************/
UINT8_S GetNextZcMaHeadDir(const UINT16_S trainId)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].MaHeadDir;
	} 
	else
	{
		rtnValue = RETURN_UINT8_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetNextZcMaHeadDir
  功能描述:    设置相邻ZC移动授权起点方向
  输入:        const UINT16_S trainId  列车ID 
               const UINT8_S maHeadDir 起点MA方向
  输出:        无
  返回值:      RETURN_SUCCESS: 设置成功
               RETURN_ERROR:   设置失败
*************************************************/
UINT8_S SetNextZcMaHeadDir(const UINT16_S trainId,const UINT8_S maHeadDir)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].MaHeadDir = maHeadDir;
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetNextZcMaTailLink
  功能描述:    获取MA2移动授权终点LINK
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      DEFAULT_UINT16_VALUE: 获取数据失败
               >0u: 起点LINK
*************************************************/
UINT16_S GetNextZcMaTailLink(const UINT16_S trianId)
{
	UINT8_S trainIndex = 0U;     /*数组下标*/
	UINT16_S rtnValue = DEFAULT_UINT16_VALUE;


	trainIndex = GetNextZcMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].MaTailLink;
	}
	else
	{
		rtnValue = DEFAULT_UINT16_VALUE;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetNextZcMaTailLink
  功能描述:    设置移动授权终点LINK
  输入:        const UINT16_S trainId  列车ID 
               const UINT16_S link MA终点link
  输出:        无
  返回值:      RETURN_SUCCESS: 设置成功
               RETURN_ERROR:   设置失败
*************************************************/
UINT8_S SetNextZcMaTailLink(const UINT16_S trianId, const UINT16_S link)
{
	UINT8_S trainIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].MaTailLink = link;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetNextZcMaTailOffset
  功能描述:    获取MA2移动授权终点offset
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_UINT32_MAX_VALUE: 获取数据失败
               <RETURN_UINT32_MAX_VALUE: 起点offset
*************************************************/
UINT32_S GetNextZcMaTailOffset(const UINT16_S trianId)
{
	UINT8_S trainIndex = 0U;     /*数组下标*/
	UINT32_S rtnValue = RETURN_UINT32_MAX_VALUE;

	trainIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].MaTailOffset;
	}
	else
	{

		rtnValue = RETURN_UINT32_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetNextZcMaTailOffset
  功能描述:    设置MA2移动授权终点offset
  输入:        const UINT16_S trainId  列车ID 
               const UINT32_S offset MA终点offset
  输出:        无
  返回值:      RETURN_SUCCESS: 设置成功
               RETURN_ERROR:   设置失败
*************************************************/
UINT8_S SetNextZcMaTailOffset(const UINT16_S trianId, const UINT32_S offset)
{
	UINT8_S trainIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = 0U;

	trainIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].MaTailOffset = offset;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetNextZcMaTailDir
  功能描述:    获取相邻ZC移动授权终点方向
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE: 获取数据失败
               <RETURN_UINT8_MAX_VALUE: 终点LINK方向
*************************************************/
UINT8_S GetNextZcMaTailDir(const UINT16_S trainId)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].MaTailDir;
	} 
	else
	{
		rtnValue = RETURN_UINT8_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetNextZcMaTailDir
  功能描述:    获取相邻ZC移动授权终点方向
  输入:        const UINT16_S trainId  列车ID 
               const UINT8_S maTailDir 终点MA方向
  输出:        无
  返回值:      RETURN_SUCCESS: 设置成功
               RETURN_ERROR:   设置失败
*************************************************/
UINT8_S SetNextZcMaTailDir(const UINT16_S trainId,const UINT8_S maTailDir)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].MaTailDir = maTailDir;
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetNextZcMaEndAttribute
  功能描述:    获取相邻ZC移动授权终点属性
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE: 获取数据失败
               >0u:                    终点属性
*************************************************/
UINT8_S GetNextZcMaEndAttribute(const UINT16_S trainId)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = RETURN_UINT8_MAX_VALUE;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].MaEndAttribute;
	}
	else
	{
		rtnValue = RETURN_UINT8_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetNextZcMaEndAttribute
  功能描述:    设置相邻ZC移动授权终点属性
  输入:        const UINT16_S trainId  列车ID 
               const UINT8_S endAttribute 终点属性
  输出:        无
  返回值:      RETURN_SUCCESS: 设置成功
               RETURN_ERROR:   设置失败
*************************************************/
UINT8_S SetNextZcMaEndAttribute(const UINT16_S trainId, const UINT8_S endAttribute)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].MaEndAttribute = endAttribute;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetNextZcMaObsNum
  功能描述:    获取相邻ZC移动授权对应障碍物数量
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE: 获取数据失败
               <RETURN_UINT8_MAX_VALUE: 障碍物数量
*************************************************/
UINT8_S GetNextZcMaObsNum(const UINT16_S trainId)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].ObsNum;
	}
	else
	{
		rtnValue = RETURN_UINT8_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetNextZcMaObsNum
  功能描述:    设置相邻ZC移动授权对应障碍物数量
  输入:        const UINT16_S trainId  列车ID 
               const UINT8_S obsNum 障碍物数量
  输出:        无
  返回值:      RETURN_SUCCESS: 设置成功
               RETURN_ERROR:   设置失败
*************************************************/
UINT8_S SetNextZcMaObsNum(const UINT16_S trainId, const UINT8_S obsNum)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].ObsNum = obsNum;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetNextZcObsOfMAStru
  功能描述:    获取相邻ZC移动授权障碍物信息
  输入:        const UINT16_S trainId  列车ID                
  输出:        ObsOfMAStruct obsStru[] 障碍物信息数组 
  返回值:      RETURN_SUCCESS: 获取成功
               RETURN_ERROR:   获取失败
*************************************************/
UINT8_S GetNextZcObsOfMAStru(const UINT16_S trainId, ObsOfMAStruct obsStru[])
{
	UINT8_S trainIndex = 0U;
	UINT8_S cycle = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if ((LINE_MAX_TRAIN_ID != trainIndex) && (NULL != obsStru))
	{
		for (cycle = DEFAULT_ZERO;cycle < MA_AREA_OBS_SUM_MAX;cycle++)
		{
			obsStru[cycle].ObsId = gNextZcDataStruBuff[trainIndex].ObsOfMAStru[cycle].ObsId;
			obsStru[cycle].ObsType = gNextZcDataStruBuff[trainIndex].ObsOfMAStru[cycle].ObsType;
			obsStru[cycle].ObsStatus = gNextZcDataStruBuff[trainIndex].ObsOfMAStru[cycle].ObsStatus;
			obsStru[cycle].ObsLockStatus = gNextZcDataStruBuff[trainIndex].ObsOfMAStru[cycle].ObsLockStatus;

		}
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetNextZcObsOfMAStru
  功能描述:    设置相邻ZC移动授权障碍物信息
  输入:        const UINT16_S trainId  列车ID                
               const ObsOfMAStruct obsStru[] 障碍物信息数组
               const UINT8_S obsNum 障碍物数量
  输出:        无
  返回值:      RETURN_SUCCESS: 获取成功
               RETURN_ERROR:   获取失败
*************************************************/
UINT8_S SetNextZcObsOfMAStru(const UINT16_S trainId,const ObsOfMAStruct obsStru[],const UINT8_S obsNum)
{
	UINT8_S trainIndex = 0U;
	UINT8_S cycle = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if ((LINE_MAX_TRAIN_ID != trainIndex) && (NULL != obsStru))
	{
		for (cycle = DEFAULT_ZERO;cycle < obsNum;cycle++)
		{
			gNextZcDataStruBuff[trainIndex].ObsOfMAStru[cycle].ObsId = obsStru[cycle].ObsId;
			gNextZcDataStruBuff[trainIndex].ObsOfMAStru[cycle].ObsType = obsStru[cycle].ObsType;
			gNextZcDataStruBuff[trainIndex].ObsOfMAStru[cycle].ObsStatus = obsStru[cycle].ObsStatus;
			gNextZcDataStruBuff[trainIndex].ObsOfMAStru[cycle].ObsLockStatus = obsStru[cycle].ObsLockStatus;
		}

		gNextZcDataStruBuff[trainIndex].ObsNum = obsNum;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetNextZcMaTsrNum
  功能描述:    获取相邻ZC移动授权对应Trs数量
  输入:        const UINT16_S trainId  列车ID                
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE: 获取数据失败
               <RETURN_UINT8_MAX_VALUE: 临时限速数量
*************************************************/
UINT8_S GetNextZcMaTsrNum(const UINT16_S trainId)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].TsrNum;
	}
	else
	{
		rtnValue = RETURN_UINT8_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetNextZcMaTsrNum
  功能描述:    设置移动授权对应临时限速数量
  输入:        const UINT16_S trainId  列车ID
               const UINT8_S tsrNum    临时限速数量
  输出:        无
  返回值:      RETURN_SUCCESS:  设置成功
               RETURN_ERROR:    设置失败
*************************************************/
UINT8_S SetNextZcMaTsrNum(const UINT16_S trainId, const UINT8_S tsrNum)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].TsrNum = tsrNum;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetNextZcTsrOfMAStru
  功能描述:    获取相邻ZC移动授权Tsr信息
  输入:        const UINT16_S trainId    列车ID
  输出:        TsrOfMAStruct ObsOfMAStru Tsr信息
  返回值:      RETURN_SUCCESS:  获取成功
               RETURN_ERROR:    获取失败
*************************************************/
UINT8_S GetNextZcTsrOfMAStru(const UINT16_S trainId, TsrOfMAStruct tsrOfMAStru[])
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;
	UINT8_S cycle = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if ((LINE_MAX_TRAIN_ID != trainIndex) && (NULL != tsrOfMAStru))
	{
		for (cycle = DEFAULT_ZERO;cycle < MA_AREA_TSR_SUM_MAX;cycle++)
		{
		    /*pbw 20161021 增加赋值ZCID */            
            tsrOfMAStru[cycle].BelongZcId = gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].BelongZcId;
			tsrOfMAStru[cycle].TsrHeadLink = gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].TsrHeadLink;
			tsrOfMAStru[cycle].TsrHeadOffset = gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].TsrHeadOffset;
			tsrOfMAStru[cycle].TsrTailLink = gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].TsrTailLink;
			tsrOfMAStru[cycle].TsrTailOffset = gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].TsrTailOffset;
			tsrOfMAStru[cycle].TsrSpeed = gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].TsrSpeed;
		}
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetNextZcTsrOfMAStru
  功能描述:    设置相邻ZC移动授权Tsr信息
  输入:        const UINT16_S trainId    列车ID
               const TsrOfMAStruct* tsrOfMAStru Tsr信息
               const UINT8_S tsrNum  TSR数量
  输出:        无
  返回值:      RETURN_SUCCESS:  设置成功
               RETURN_ERROR:    设置失败
*************************************************/
UINT8_S SetNextZcTsrOfMAStru(const UINT16_S trainId, const TsrOfMAStruct* tsrOfMAStru,const UINT8_S tsrNum)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;
	UINT8_S cycle = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if ((LINE_MAX_TRAIN_ID != trainIndex) && (tsrNum < MA_AREA_TSR_SUM_MAX) && (NULL != tsrOfMAStru))
	{
		for (cycle = DEFAULT_ZERO;cycle < tsrNum;cycle++)
		{
		    /*pbw 20161021 增加赋值ZCID */     
            gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].BelongZcId = tsrOfMAStru[cycle].BelongZcId;
			gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].TsrHeadLink = tsrOfMAStru[cycle].TsrHeadLink;
			gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].TsrHeadOffset = tsrOfMAStru[cycle].TsrHeadOffset;
			gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].TsrTailLink = tsrOfMAStru[cycle].TsrTailLink;
			gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].TsrTailOffset = tsrOfMAStru[cycle].TsrTailOffset;
			gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].TsrSpeed = tsrOfMAStru[cycle].TsrSpeed;
		}

		gNextZcDataStruBuff[trainId].TsrNum = tsrNum;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetNextZcMaStatusTrainId
  功能描述:    设置相邻ZC输入某下标对应的列车ID
  输入:        const UINT16_S trainId    列车ID
  输出:        无
  返回值:      RETURN_SUCCESS:  设置成功
               RETURN_ERROR:    设置失败
*************************************************/
UINT8_S SetNextZcMaStatusTrainId(const UINT16_S trainId)
{
	UINT16_S bufIndex = LINE_MAX_TRAIN_ID;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID == bufIndex)
	{
		/*新增*/
		if (gNextZcMaCurSum >= COMM_TRAIN_SUM_MAX)
		{
			/*不添加信息,返回失败*/
		} 
		else
		{
			/*移动授权信息*/
			gNextZcDataStruBuff[gNextZcMaCurSum].TrainID = trainId;
			gNextZcMaDataIndexBuff[trainId] = gNextZcMaCurSum;
			gNextZcMaCurSum++;
			rtnValue = RETURN_SUCCESS;
		}
	} 
	else
	{
		if (COMM_TRAIN_SUM_MAX <= bufIndex )
		{
            rtnValue = RETURN_ERROR;			
		} 
		else
		{
            gNextZcDataStruBuff[bufIndex].TrainID = trainId;
            rtnValue = RETURN_SUCCESS;
		}
	}

	return rtnValue;
}

/*************************************************
  函数名:      DeleteNextZcSingleTrainMaInfo
  功能描述:    删除相邻ZC输入单个列车移动授权信息
  输入:        const UINT16_S trainId    列车ID
  输出:        无
  返回值:      无
*************************************************/
void DeleteNextZcSingleTrainMaInfo(const UINT16_S trainId)
{
	UINT8_S bufIndex = 0U;
	UINT8_S cycle = DEFAULT_ZERO;

	bufIndex = GetNextZcMaStatusBufIndex(trainId);

	/**/
	if (LINE_MAX_TRAIN_ID == bufIndex)
	{
		/*不处理*/
	} 
	else
	{
		/*清除信息*/
		if (bufIndex == (GetNextZcMaStatusSum() - 1U))
		{
			MemorySet(&gNextZcDataStruBuff[bufIndex],((UINT32_S)(sizeof(NextZcMaDataStruct))),
                        0U,((UINT32_S)(sizeof(NextZcMaDataStruct))));
		} 
		else
		{
			for (cycle = bufIndex + 1U;cycle < GetNextZcMaStatusSum();cycle++)
			{
				MemoryCpy(&gNextZcDataStruBuff[cycle - 1U],((UINT32_S)(sizeof(NextZcMaDataStruct))),
                            &gNextZcDataStruBuff[cycle],((UINT32_S)(sizeof(NextZcMaDataStruct))));

				/*更新索引数组*/
				gNextZcMaDataIndexBuff[gNextZcDataStruBuff[cycle - 1U].TrainID] = cycle - 1U;
			}

			MemorySet(&gNextZcDataStruBuff[gNextZcMaCurSum - 1U],((UINT32_S)(sizeof(NextZcMaDataStruct))),
                         0U,((UINT32_S)(sizeof(NextZcMaDataStruct))));
		}

		if (gNextZcMaCurSum > 0U)
		{
			gNextZcMaCurSum--;
		} 
		else
		{
			gNextZcMaCurSum = 0U;
		}

		gNextZcMaDataIndexBuff[trainId] = LINE_MAX_TRAIN_ID;
	}
}

/*************************************************
  函数名:      ClearNextZcSingleTrainMaInfo
  功能描述:    清除相邻ZC输入单个列车移动授权信息
  输入:        const UINT16_S trainId    列车ID
  输出:        无
  返回值:      无
*************************************************/
void ClearNextZcSingleTrainMaInfo(const UINT16_S trainId)
{
	UINT8_S bufIndex = 0U;

	bufIndex = GetNextZcMaStatusBufIndex(trainId);

	/**/
	if (LINE_MAX_TRAIN_ID == bufIndex)
	{
		/*不处理*/
	} 
	else
	{
		/*清除信息*/
		MemorySet(&gNextZcDataStruBuff[bufIndex],((UINT32_S)(sizeof(NextZcMaDataStruct))),
                     0U,((UINT32_S)(sizeof(NextZcMaDataStruct))));
		gNextZcDataStruBuff[bufIndex].TrainID = trainId;
	}
}

/*************************************************
  函数名:      GetMaStatusData
  功能描述:    获取移动授权数据
  输入:        无
  输出:        无
  返回值:      移动授权结构体数组的首地址
*************************************************/
MaDataStruct* GetMaStatusData(void)
{
	return gMaDataStruBuff;
}

/*************************************************
  函数名:      GetMaStatusSum
  功能描述:    获取列车移动授权管理总数
  输入:        无
  输出:        无
  返回值:      列车移动授权管理总数
*************************************************/
UINT16_S GetMaStatusSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if ((gMaCurSum > DEFAULT_ZERO) && (gMaCurSum <= COMM_TRAIN_SUM_MAX))
	{
		rtnValue = gMaCurSum;
	} 
	else
	{
		rtnValue = 0U;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetMaStatusTrainId
  功能描述:    获取某下标对应的列车ID
  输入:        const UINT16_S bufIndex, 数组下标 
  输出:        无
  返回值:      0u:  获取数据失败
               >0u: 列车ID 
*************************************************/
UINT16_S GetMaStatusTrainId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (COMM_TRAIN_SUM_MAX <= bufIndex)
	{
		rtnValue = 0U;
	} 
	else
	{	
        rtnValue = gMaDataStruBuff[bufIndex].TrainID;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetMaStatusTrainId
  功能描述:    设置某下标对应的列车ID
  输入:        const UINT16_S trainId, 列车Id  
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetMaStatusTrainId(const UINT16_S trainId)
{
	UINT16_S bufIndex = LINE_MAX_TRAIN_ID;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID == bufIndex)
	{
		/*新增*/
		if (gMaCurSum >= COMM_TRAIN_SUM_MAX)
		{
			/*不添加信息,返回失败*/
		} 
		else
		{
			/*移动授权信息*/
			gMaDataStruBuff[gMaCurSum].TrainID = trainId;
			gMaDataIndexBuff[trainId] = gMaCurSum;
			gMaCurSum++;
			rtnValue = RETURN_SUCCESS;
		}
	} 
	else
	{
		if (COMM_TRAIN_SUM_MAX <= bufIndex)
		{
            rtnValue = RETURN_ERROR;		
		} 
		else
		{
            gMaDataStruBuff[bufIndex].TrainID = trainId;
            rtnValue = RETURN_SUCCESS;
		}
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetMaStatusBufIndex
  功能描述:    获取指定列车ID索引号
  输入:        const UINT16_S trainId, 列车Id  
  输出:        无
  返回值:      LINE_MAX_TRAIN_ID:      获取失败
               [1u,LINE_MAX_TRAIN_ID): 获取成功
*************************************************/
UINT8_S GetMaStatusBufIndex(const UINT16_S trainId)
{
	UINT8_S rtnValue = DEFAULT_ZERO;

	if ((trainId > DEFAULT_ZERO) && (trainId < LINE_MAX_TRAIN_ID))
	{
		rtnValue = gMaDataIndexBuff[trainId];
	} 
	else
	{
		rtnValue = LINE_MAX_TRAIN_ID;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GeSingleMaInfo
  功能描述:    获取指定列车ID的MA信息
  输入:        const UINT16_S trainId, 列车Id  
  输出:        MaDataStruct *singleMaInfo ,MA结构体指针
  返回值:      RETURN_ERROR:  获取失败
               RETURN_SUCESS: 获取成功
*************************************************/
UINT8_S GeSingleMaInfo(const UINT16_S trainId,MaDataStruct *singleMaInfo)
{
	UINT8_S bufIndex = 0U;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trainId);

	if ((LINE_MAX_TRAIN_ID != bufIndex) && (NULL != singleMaInfo))
	{
		MemoryCpy(singleMaInfo,sizeof(MaDataStruct),&gMaDataStruBuff[bufIndex],sizeof(MaDataStruct));
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetMaType
  功能描述:    获取移动授权类型
  输入:        const UINT16_S trainId, 列车Id  
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE:  获取失败
               >0u:                     获取成功
*************************************************/
UINT8_S GetMaType(const UINT16_S trianId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].MaType;
	}
	else
	{
		rtnValue = RETURN_UINT8_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetMaType
  功能描述:    设置移动授权类型
  输入:        const UINT16_S trainId, 列车Id  
               const UINT8_S maType, MA类型
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetMaType(const UINT16_S trianId,const UINT8_S maType)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		if ((NORMAL_MA_TYPE == maType)
			|| (ABNORMAL_MA_TYPE == maType)
			|| (CANCELLATION_MA_TYPE == maType)
			|| (NO_MA_TYPE == maType))
		{
			gMaDataStruBuff[bufIndex].MaType = maType;
		} 
		else
		{
			gMaDataStruBuff[bufIndex].MaType = DEFAULT_ZERO;
		}
		
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetMaHeadLink
  功能描述:    获取移动授权起点LINK
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      RETURN_UINT16_MAX_VALUE:    获取失败
               >0u:  获取成功
*************************************************/
UINT16_S GetMaHeadLink(const UINT16_S trianId)
{
	UINT16_S bufIndex = RETURN_UINT16_MAX_VALUE;     /*数组下标*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].MaHeadLink;
	}
	else
	{
		rtnValue = RETURN_UINT16_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetMaHeadLink
  功能描述:    设置移动授权起点LINK
  输入:        const UINT16_S trainId, 列车Id
               const UINT16_S link, MA起点link
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetMaHeadLink(const UINT16_S trianId, const UINT16_S link)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].MaHeadLink = link;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetMaHeadOffset
  功能描述:    获取移动授权起点offset
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      RETURN_UINT32_MAX_VALUE:  获取失败
               >0u:                      获取成功
*************************************************/
UINT32_S GetMaHeadOffset(const UINT16_S trianId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT32_S rtnValue = DEFAULT_ZERO; 

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].MaHeadOffset;
	}
	else
	{
		rtnValue = RETURN_UINT32_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetMaHeadOffset
  功能描述:    设置移动授权起点offset
  输入:        const UINT16_S trainId, 列车Id
               const UINT32_S offset,  MA起点offset
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetMaHeadOffset(const UINT16_S trianId, const UINT32_S offset)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].MaHeadOffset = offset;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetMaHeadDir
  功能描述:    获取移动授权起点方向
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      DEFAULT_UINT8_VALUE:  获取失败
               >0u:                  获取成功
*************************************************/
UINT8_S GetMaHeadDir(const UINT16_S trianId)
{
	UINT16_S bufIndex = DEFAULT_UINT8_VALUE;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].MaHeadDir;
	}
	else
	{
		rtnValue = DEFAULT_UINT8_VALUE;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetMaHeadDir
  功能描述:    设置移动授权起点方向
  输入:        const UINT16_S trainId, 列车Id
               const UINT8_S dir,      MA起点方向
  输出:        无
  返回值:      RETURN_ERROR:       设置失败
               RETURN_SUCCESS:     设置成功
*************************************************/
UINT8_S SetMaHeadDir(const UINT16_S trianId, const UINT8_S dir)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].MaHeadDir = dir;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetMaTailLink
  功能描述:    获取移动授权终点LINK
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      0:    获取失败
               >0u:  获取成功
*************************************************/
UINT16_S GetMaTailLink(const UINT16_S trianId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].MaTailLink;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetMaTailLink
  功能描述:    设置移动授权终点LINK
  输入:        const UINT16_S trainId, 列车Id
               const UINT16_S link, MA终点link
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetMaTailLink(const UINT16_S trianId, const UINT16_S link)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].MaTailLink = link;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetMaTailOffset
  功能描述:    获取移动授权终点offset
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      RETURN_UINT32_MAX_VALUE:  获取失败
               [0u,RETURN_UINT32_MAX_VALUE): 获取成功
*************************************************/
UINT32_S GetMaTailOffset(const UINT16_S trianId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT32_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].MaTailOffset;
	}
	else
	{
		rtnValue = RETURN_UINT32_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetMaTailOffset
  功能描述:    设置移动授权终点offset
  输入:        const UINT16_S trainId, 列车Id
               const UINT32_S offset,  MA终点offset
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetMaTailOffset(const UINT16_S trianId, const UINT32_S offset)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].MaTailOffset = offset;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetMaTailDir
  功能描述:    获取移动授权终点方向
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      RETURN_ERROR:  获取失败
               >0u:                  获取成功
*************************************************/
UINT8_S GetMaTailDir(const UINT16_S trianId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].MaTailDir;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetMaTailDir
  功能描述:    设置移动授权终点方向
  输入:        const UINT16_S trainId, 列车Id
               const UINT8_S dir,      MA终点方向
  输出:        无
  返回值:      RETURN_ERROR:       设置失败
               RETURN_SUCCESS:     设置成功
*************************************************/
UINT8_S SetMaTailDir(const UINT16_S trianId, const UINT8_S dir)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].MaTailDir = dir;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetMaEndObsId
  功能描述:    获取移动授权终点障碍物Id
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      RETURN_ERROR:  获取失败
               >0u:                  获取成功
*************************************************/
UINT16_S GetMaEndObsId(const UINT16_S trianId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].MaEndObsId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetMaEndObsId
  功能描述:    设置移动授权终点障碍物Id
  输入:        const UINT16_S trainId, 列车Id
               const UINT8_S endObstacleId, 终点障碍物Id
  输出:        无
  返回值:      RETURN_ERROR:         设置失败
               RETURN_SUCCESS:       获取成功
*************************************************/
UINT8_S SetMaEndObsId(const UINT16_S trianId, const UINT8_S endObstacleId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].MaEndObsId = endObstacleId;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetMaEndObsType
  功能描述:    获取移动授权终点障碍物类型
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      RETURN_ERROR:  获取失败
               >0u:           获取成功
*************************************************/
UINT8_S GetMaEndObsType(const UINT16_S trianId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].MaEndObsType;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetMaEndObsType
  功能描述:    设置移动授权终点障碍物类型
  输入:        const UINT16_S trainId, 列车Id
               const UINT8_S endObstacleType, 终点障碍物类型
  输出:        无
  返回值:      RETURN_ERROR:         设置失败
               RETURN_SUCCESS:       获取成功
*************************************************/
UINT8_S SetMaEndObsType(const UINT16_S trianId, const UINT8_S endObstacleType)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].MaEndObsType = endObstacleType;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetMaEndAttribute
  功能描述:    获取移动授权终点属性
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      RETURN_ERROR:  获取失败
               >0u:           获取成功
*************************************************/
UINT8_S GetMaEndAttribute(const UINT16_S trianId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].MaEndAttribute;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetMaEndAttribute
  功能描述:    设置移动授权终点属性
  输入:        const UINT16_S trainId, 列车Id
               const UINT8_S endAttribute, 终点属性
  输出:        无
  返回值:      RETURN_ERROR:         设置失败
               RETURN_SUCCESS:       获取成功
*************************************************/
UINT8_S SetMaEndAttribute(const UINT16_S trianId, const UINT8_S endAttribute)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].MaEndAttribute = endAttribute;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetMaObsNum
  功能描述:    获取移动授权对应障碍物数量
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      RETURN_ERROR:  获取失败
               >0u:           获取成功
*************************************************/
UINT8_S GetMaObsNum(const UINT16_S trianId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].ObsNum;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetMaObsNum
  功能描述:    设置移动授权对应障碍物数量
  输入:        const UINT16_S trainId, 列车Id
               const UINT8_S obsNum, 障碍物数量
  输出:        无
  返回值:      RETURN_ERROR:         设置失败
               RETURN_SUCCESS:       获取成功
*************************************************/
UINT8_S SetMaObsNum(const UINT16_S trianId, const UINT8_S obsNum)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].ObsNum = obsNum;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetObsOfMAStru
  功能描述:    获取移动授权障碍物信息
  输入:        const UINT16_S trainId, 列车Id
               const UINT8_S bufSize,输出障碍物结构数组大小(预留)
  输出:        ObsOfMAStruct obsOfMaStrBuff[],输出障碍物结构数组
  返回值:      RETURN_ERROR:     获取失败
               RETURN_SUCCESS:   获取成功
*************************************************/
UINT8_S GetObsOfMAStru(const UINT16_S trianId,const UINT8_S bufSize,ObsOfMAStruct obsOfMaStrBuff[])
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = 0U;
	UINT8_S cycle = 0U;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if ((LINE_MAX_TRAIN_ID != bufIndex) && (NULL != obsOfMaStrBuff))
	{
		for (cycle = DEFAULT_ZERO;cycle < GetMaObsNum(trianId);cycle++)
		{
			obsOfMaStrBuff[cycle].ObsId = gMaDataStruBuff[bufIndex].ObsOfMAStru[cycle].ObsId;
			obsOfMaStrBuff[cycle].ObsType = gMaDataStruBuff[bufIndex].ObsOfMAStru[cycle].ObsType;
			obsOfMaStrBuff[cycle].ObsStatus = gMaDataStruBuff[bufIndex].ObsOfMAStru[cycle].ObsStatus;
			obsOfMaStrBuff[cycle].ObsLockStatus = gMaDataStruBuff[bufIndex].ObsOfMAStru[cycle].ObsLockStatus;
		}

		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetObsOfMAStru
  功能描述:    设置移动授权障碍物信息
  输入:        const UINT16_S trainId, 列车Id
               const ObsOfMAStruct obsOfMABuff[],障碍物信息数组
               const UINT8_S obsNum,障碍物数量
  输出:        无
  返回值:      RETURN_ERROR:     设置失败
               RETURN_SUCCESS:   设置成功
*************************************************/
UINT8_S SetObsOfMAStru(const UINT16_S trianId, const ObsOfMAStruct obsOfMABuff[],const UINT8_S obsNum)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S cycle = 0U;
	UINT8_S index = 0U;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if ((LINE_MAX_TRAIN_ID != bufIndex) && (obsNum < MA_AREA_OBS_SUM_MAX) && (NULL != obsOfMABuff))
	{
		for (cycle = DEFAULT_ZERO;cycle < obsNum;cycle++)
		{
			gMaDataStruBuff[bufIndex].ObsOfMAStru[cycle].ObsId = obsOfMABuff[index].ObsId;
			gMaDataStruBuff[bufIndex].ObsOfMAStru[cycle].ObsType = obsOfMABuff[index].ObsType;
			gMaDataStruBuff[bufIndex].ObsOfMAStru[cycle].ObsStatus = obsOfMABuff[index].ObsStatus;
			gMaDataStruBuff[bufIndex].ObsOfMAStru[cycle].ObsLockStatus = obsOfMABuff[index].ObsLockStatus;

			index++;
		}

		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

    return rtnValue;
}

/*************************************************
  函数名:      GetMaTsrNum
  功能描述:    获取移动授权对应Tsr数量
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      RETURN_ERROR:     获取失败
               >0u:   Tsr数量
*************************************************/
UINT8_S GetMaTsrNum(const UINT16_S trianId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].TsrNum;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetMaTsrNum
  功能描述:    设置移动授权对应临时限速数量
  输入:        const UINT16_S trainId, 列车Id
               const UINT8_S tsrNum, 临时限速数量
  输出:        无
  返回值:      RETURN_ERROR:     设置失败
               RETURN_SUCCESS:   设置成功
*************************************************/
UINT8_S SetMaTsrNum(const UINT16_S trianId, const UINT8_S tsrNum)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].TsrNum = tsrNum;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      GetTsrOfMAStru
  功能描述:    获取移动授权Tsr信息
  输入:        const UINT16_S trainId, 列车Id
               const UINT8_S bufSize,输出障碍物结构数组大小(预留)
  输出:        TsrOfMAStruct tsrOfMaStrBuff[],输出临时限速结构数组
  返回值:      RETURN_ERROR:     获取失败
               RETURN_SUCCESS:   获取成功
*************************************************/
UINT8_S GetTsrOfMAStru(const UINT16_S trianId,const UINT8_S bufSize,TsrOfMAStruct tsrOfMaStrBuff[])
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = 0U;
	UINT8_S cycle = 0U;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if ((LINE_MAX_TRAIN_ID != bufIndex) && (NULL != tsrOfMaStrBuff))
	{
		for (cycle = DEFAULT_ZERO;cycle < GetMaTsrNum(trianId);cycle++)
		{
			tsrOfMaStrBuff[cycle].TsrSpeed = gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].TsrSpeed;
			tsrOfMaStrBuff[cycle].TsrHeadLink = gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].TsrHeadLink;
			tsrOfMaStrBuff[cycle].TsrHeadOffset = gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].TsrHeadOffset;
			tsrOfMaStrBuff[cycle].TsrTailLink = gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].TsrTailLink;
			tsrOfMaStrBuff[cycle].TsrTailOffset = gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].TsrTailOffset;
			tsrOfMaStrBuff[cycle].BelongZcId = gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].BelongZcId;
		}

		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      SetTsrOfMAStru
  功能描述:    设置移动授权Tsr信息
  输入:        const UINT16_S trainId, 列车Id
               const TsrOfMAStruct tsrOfMAStru[],Tsr信息
               const UINT8_S tsrNum,Tsr数量
  输出:        无
  返回值:      RETURN_ERROR:     设置失败
               RETURN_SUCCESS:   设置成功
*************************************************/
UINT8_S SetTsrOfMAStru(const UINT16_S trianId, const TsrOfMAStruct tsrOfMAStru[],const UINT8_S tsrNum)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S cycle = 0U;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*获取数组下标*/

	if ((LINE_MAX_TRAIN_ID != bufIndex) && (tsrNum < MA_AREA_TSR_SUM_MAX) && (NULL != tsrOfMAStru))
	{
		for (cycle = DEFAULT_ZERO;cycle < tsrNum;cycle++)
		{
		    /*pbw 20161021增加赋值ZCID */
            gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].BelongZcId = tsrOfMAStru[cycle].BelongZcId;
			gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].TsrHeadLink = tsrOfMAStru[cycle].TsrHeadLink;
			gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].TsrHeadOffset = tsrOfMAStru[cycle].TsrHeadOffset;
			gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].TsrTailLink = tsrOfMAStru[cycle].TsrTailLink;
			gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].TsrTailOffset = tsrOfMAStru[cycle].TsrTailOffset;
			gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].TsrSpeed = tsrOfMAStru[cycle].TsrSpeed;
		}

		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:      DeleteSingleTrainMaInfo
  功能描述:    删除单个列车移动授权信息
  输入:        const UINT16_S trainId, 列车Id             
  输出:        无
  返回值:      无
*************************************************/
void DeleteSingleTrainMaInfo(const UINT16_S trainId)
{
	UINT8_S bufIndex = 0U;
	UINT8_S cycle = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trainId);

	/**/
	if (LINE_MAX_TRAIN_ID == bufIndex)
	{
		/*不处理*/
	} 
	else
	{
		/*清除信息*/
		if (bufIndex == (GetMaStatusSum()-1U))
		{
			MemorySet(&gMaDataStruBuff[bufIndex],((UINT32_S)(sizeof(MaDataStruct))),0U,((UINT32_S)(sizeof(MaDataStruct))));
		} 
		else
		{
			for (cycle = bufIndex + 1U;cycle < GetMaStatusSum();cycle++)
			{
				MemoryCpy(&gMaDataStruBuff[cycle - 1U],((UINT32_S)(sizeof(MaDataStruct))),
                            &gMaDataStruBuff[cycle],((UINT32_S)(sizeof(MaDataStruct))));

				/*更新索引数组*/
				gMaDataIndexBuff[gMaDataStruBuff[cycle - 1U].TrainID] = cycle - 1U;
			}

			MemorySet(&gMaDataStruBuff[gMaCurSum - 1U],((UINT32_S)(sizeof(MaDataStruct))),
                        0U,((UINT32_S)(sizeof(MaDataStruct))));
		}

		if (gMaCurSum > 0U)
		{
			gMaCurSum--;
		} 
		else
		{
			gMaCurSum = 0U;
		}

		gMaDataIndexBuff[trainId] = LINE_MAX_TRAIN_ID;
	}
}

/*************************************************
  函数名:      ClearSingleTrainMaInfo
  功能描述:    清除单个列车移动授权信息
  输入:        const UINT16_S trainId, 列车Id             
  输出:        无
  返回值:      无
*************************************************/
void ClearSingleTrainMaInfo(const UINT16_S trainId)
{
	UINT8_S bufIndex = 0U;

	bufIndex = GetMaStatusBufIndex(trainId);

	/**/
	if (LINE_MAX_TRAIN_ID == bufIndex)
	{
		/*不处理*/
	} 
	else
	{
		/*清除信息*/
		MemorySet(&gMaDataStruBuff[bufIndex],((UINT32_S)(sizeof(MaDataStruct))),0U,((UINT32_S)(sizeof(MaDataStruct))));
		gMaDataStruBuff[bufIndex].TrainID = trainId;
	}
}
