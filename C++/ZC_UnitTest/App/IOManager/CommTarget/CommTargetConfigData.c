/************************************************************************
*
* 文件名   ：  CommTargetConfigData.c
* 作  者	：  ZC组
* 创建时间 ：  2015.07.14
* 功能描述 ：  通讯目标配置 
* 备  注	：  无
*
************************************************************************/

#include "CommTargetConfigData.h"

CommTargetConfigDataStruct gCommTargetConfigDataStru[COMM_TYPE_SUM_MAX];               /*定义通信对象配置信息*/
UINT8_S gCommTargetTypeCurSum = DEFAULT_ZERO;                                                       /*定义通信对象总数*/

/*
* 函数名称： GetCommTargetTypeBuffIndex
* 功能描述： 获取通信类型存储下表
* 输入参数： const UINT8 commTargetType 通信设备类型    
* 输出参数： 无
* 返回值  ： 0: 获取数据失败
*			>0: 当前总数
*/
UINT8_S GetCommTargetTypeBuffIndex(const UINT8_S commTargetType)
{
	UINT8_S rtnValue = COMM_TYPE_SUM_MAX;
	UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S allCommTargetSum = DEFAULT_ZERO;

    allCommTargetSum = GetCommTargetTypeSum();
	for (cycle = DEFAULT_ZERO;cycle < allCommTargetSum;cycle++)
	{
		if (gCommTargetConfigDataStru[cycle].CommTargetType == commTargetType)
		{
			rtnValue = cycle;
			break;
		} 
		else
		{
            /*不处理*/
		}
	}

	return rtnValue;
}

/*
* 函数名称： GetCommTargetTypeSum
* 功能描述： 获取通信类型就总数
* 输入参数： void    
* 输出参数： 无
* 返回值  ： 0: 获取数据失败
*			>0: 当前总数
*/
UINT8_S GetCommTargetTypeSum(void)
{
	UINT8_S rtnValue = DEFAULT_ZERO;

	if (gCommTargetTypeCurSum >= COMM_TYPE_SUM_MAX)
	{
		rtnValue = DEFAULT_ZERO;
	} 
	else
	{
		rtnValue = gCommTargetTypeCurSum;
	}	

	return rtnValue;
}

/*
* 函数名称：GetSingleCommTargetTypeSum
* 功能描述： 获取某类通信设备总数
* 输入参数： const UINT8 commTargetType 通信设备类型 
* 输出参数： 无
* 返回值  ： 0: 获取数据失败
*			>0: 当前总数
*/
UINT8_S GetSingleCommTargetTypeSum(const UINT8_S commTargetType)
{
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S commTypeIndex = DEFAULT_ZERO;
    UINT8_S allCommTargetSum = DEFAULT_ZERO;

    allCommTargetSum = GetCommTargetTypeSum();
	commTypeIndex = GetCommTargetTypeBuffIndex(commTargetType);

	if (commTypeIndex < allCommTargetSum)
	{
		rtnValue = gCommTargetConfigDataStru[commTypeIndex].CommTargetNum;
	}
	else
	{
        /*不处理*/
	}
	
	return rtnValue;
}

/*
* 函数名称： GetSingleCommTargetIdBuff
* 功能描述： 获取某类设备的通信ID数组
* 输入参数： const UINT8 commTargetType 通信设备类型   
*            const UINT8_S bufSize 数组大小
* 输出参数： UINT16_S commTargetIdBuff[] 输出数组
* 返回值  ： 0u: 获取数据失败
*			 1u: 获取数据成功
*/
UINT8_S GetSingleCommTargetIdBuff(const UINT8_S commTargetType,const UINT8_S bufSize,UINT16_S commTargetIdBuff[])
{
	UINT8_S commTypeIndex = DEFAULT_ZERO;
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S allCommTargetSum = DEFAULT_ZERO;
    UINT8_S singleCommTargetSum = DEFAULT_ZERO;

    allCommTargetSum = GetCommTargetTypeSum();
	commTypeIndex = GetCommTargetTypeBuffIndex(commTargetType);   
    singleCommTargetSum = GetSingleCommTargetTypeSum(commTargetType);

	if ((commTypeIndex < allCommTargetSum)
		&& (bufSize >= SINGLE_TYPE_COMM_TARGET_SUM_MAX)
		&& (commTargetIdBuff != NULL))
	{
		for (cycle = DEFAULT_ZERO;cycle < singleCommTargetSum;cycle++)
		{
			commTargetIdBuff[cycle] = gCommTargetConfigDataStru[commTypeIndex].CommTargetIdBuff[cycle];
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
* 函数名称： GetSingleCommProtocolType
* 功能描述： 获取某类通信对象使用的协议类型
* 输入参数： const UINT8 commTargetType 通信设备类型    
* 输出参数： 无
* 返回值  ： 0: 获取数据失败
*			>0: 当前总数
*/
UINT8_S GetSingleCommProtocolType(const UINT8_S commTargetType)
{
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S commTypeIndex = DEFAULT_ZERO;
    UINT8_S allCommTargetSum = DEFAULT_ZERO;

    allCommTargetSum = GetCommTargetTypeSum();
	commTypeIndex = GetCommTargetTypeBuffIndex(commTargetType);

	if (commTypeIndex < allCommTargetSum)
	{
		rtnValue = gCommTargetConfigDataStru[commTypeIndex].CommProtocolType;
	}
	else
	{
        /*不处理*/
	}

	return rtnValue;
}

/*
* 函数名称： GetCommTargetIdInConfigData
* 功能描述： 获取通信对象Id是否属于本ZC通信范围
* 输入参数： const UINT8 commTargetType, 通讯目标的类型    
*            const UINT16_S commTargetId,通讯目标的编号
* 输出参数： 无
* 返回值  ： 0u: 不属于
*			 1u: 属于      
*/
UINT8_S GetCommTargetIdInConfigData(const UINT8_S commTargetType, const UINT16_S commTargetId)
{
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S commTypeIndex = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S findFlag = DEFAULT_ZERO;
    UINT8_S allCommTargetSum = DEFAULT_ZERO;

    allCommTargetSum = GetCommTargetTypeSum();
	commTypeIndex = GetCommTargetTypeBuffIndex(commTargetType);

	if (commTypeIndex < allCommTargetSum)
	{
		for (cycle = DEFAULT_ZERO; cycle < gCommTargetConfigDataStru[commTypeIndex].CommTargetNum;cycle++)
		{
			if (gCommTargetConfigDataStru[commTypeIndex].CommTargetIdBuff[cycle] == commTargetId)
			{
				findFlag = FLAG_SET;
				break;
			} 
			else
			{
                /*不处理*/
			}
		}
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	if (FLAG_SET == findFlag)
	{
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
