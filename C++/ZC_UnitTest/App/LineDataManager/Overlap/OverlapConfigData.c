
/********************************************************                                                                                                           
 文 件 名： OverlapConfigData.c   
 作    者： ZC组
 创建时间： 2015.04.18
 描述： 保护区段配置数据  
 备注： 无  
********************************************************/ 


#include "OverlapConfigData.h"

OverlapConfigDataStruct gOverlapConfigDataStruBuff[OVERLAP_LOCAL_SUM_MAX];            /*本地管理的保护区段配置信息*/
UINT16_S gOverlapIdBuff[OVERLAP_SUM_MAX] = {0U};                                      /*定义保护区段映射数组*/
UINT16_S gOverlapCurSum = 0U;                                                        /*保护区段当前总数*/

/*************************************************
  函数名:   GetOverlapSum   
  功能描述: 获取保护区段管理总数
  输入: void    
  输出: 无
  返回值: 0: 获取数据失败
			>0: 保护区段当前总数
*************************************************/
UINT16_S GetOverlapSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gOverlapCurSum >= OVERLAP_LOCAL_SUM_MAX)
	{
		rtnValue = 0U;
	} 
	else
	{
		rtnValue = gOverlapCurSum;
	}

	return rtnValue;
}

/*************************************************
  函数名:   GetOverlapId   
  功能描述: 获取指定数组下标对应的保护区段ID
  输入: const UINT16 bufIndex, 数组下标  
  输出: 无
  返回值: 0: 获取数据失败
			>0: 保护区段ID      
*************************************************/
UINT16_S GetOverlapId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (bufIndex < GetOverlapSum())
	{
		rtnValue = gOverlapConfigDataStruBuff[bufIndex].OverlapId;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:   GetOverlapConfigBufIndex   
  功能描述: 获取指定ID保护区段索引号
  输入: const UINT16 overlapId,保护区段ID
  输出: 无
  返回值:  OVERLAP_SUM_MAX;获取数据失败
			  >0;查找索引成功
*************************************************/
UINT16_S GetOverlapConfigBufIndex(const UINT16_S overlapId)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if ((overlapId >= 1U)&&(overlapId < OVERLAP_SUM_MAX))
	{
		rtnValue = gOverlapIdBuff[overlapId];
	}
	else
	{
		rtnValue = OVERLAP_SUM_MAX;
	}

	return rtnValue;
}

/*************************************************
  函数名:   GetOverlapBelongCiId   
  功能描述: 获取指定ID站台保护区段所属联锁ID
  输入: const UINT16 overlapId,保护区段ID    
  输出: 无
  返回值: 0: 获取数据失败
			>0: 所属联锁ID      
*************************************************/
UINT8_S GetOverlapBelongCiId(const UINT16_S overlapId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetOverlapConfigBufIndex(overlapId);  /*获取数组下标*/

	if (bufIndex < GetOverlapSum())
	{
		rtnValue = gOverlapConfigDataStruBuff[bufIndex].BelongCiId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:   GetOverlapBelongZcId   
  功能描述: 获取指定ID保护区段所属ZC的ID
  输入: const UINT16 overlapId, 保护区段ID    
  输出: 无
  返回值: 0: 获取数据失败
			>0: 所属ZcID      
*************************************************/
UINT8_S GetOverlapBelongZcId(const UINT16_S overlapId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetOverlapConfigBufIndex(overlapId);  /*获取数组下标*/

	if (bufIndex < GetOverlapSum())
	{
		rtnValue = gOverlapConfigDataStruBuff[bufIndex].BelongZcId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:   GetOverlapChangeAttribute   
  功能描述: 获取指定ID保护区段共管区域属性
  输入: const UINT16 overlapId, 保护区段ID   
  输出: 无
  返回值: 0: 获取数据失败
			>0: 获取成功      
*************************************************/
UINT16_S GetOverlapChangeAttribute(const UINT16_S overlapId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetOverlapConfigBufIndex(overlapId);  /*获取数组下标*/

	if (bufIndex < GetOverlapSum())
	{
		rtnValue = gOverlapConfigDataStruBuff[bufIndex].ChangeAttribute;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:    GetOverlapSwitchAttribute  
  功能描述: 获取指定ID保护区段道岔属性
  输入: const UINT16 overlapId, 保护区段ID   
  输出: 无
  返回值: 0: 获取数据失败
			>0: 获取成功      
*************************************************/
UINT16_S GetOverlapSwitchAttribute(const UINT16_S overlapId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetOverlapConfigBufIndex(overlapId);  /*获取数组下标*/

	if (bufIndex < GetOverlapSum())
	{
		rtnValue = gOverlapConfigDataStruBuff[bufIndex].SwitchAttribute;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:  GetOverlapContainAcNum    
  功能描述: 获取指定ID保护区段包含计轴区段数量
  输入: const UINT16 overlapId, 保护区段ID     
  输出: 无
  返回值: 0: 获取数据失败
			>0: 获取数量      
*************************************************/
UINT8_S GetOverlapContainAcNum(const UINT16_S overlapId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetOverlapConfigBufIndex(overlapId);  /*获取数组下标*/

	if (bufIndex < GetOverlapSum())
	{
		rtnValue = gOverlapConfigDataStruBuff[bufIndex].ContainAcNum;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:   GetOverlapContainAcBuff   
  功能描述: 获取指定ID保护区段包含计轴区段数组
  输入: const UINT16 overlapId, 保护区段ID    
            const UINT8_S bufSzie, 输出数组大小
            UINT16_S containAcIdBuff[]，输出数组
  输出: UINT16_S containAcIdBuff[] 包含的计轴区段数量
  返回值: 0: 获取数据失败
			>0: 获取计轴区段数组      
*************************************************/
UINT8_S GetOverlapContainAcBuff(const UINT16_S overlapId,const UINT8_S bufSzie,UINT16_S containAcIdBuff[])
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S cycle = 0U;
	UINT8_S rtnValue = 0U;
    UINT16_S overlapSum = 0U;

	bufIndex = GetOverlapConfigBufIndex(overlapId);  /*获取数组下标*/
    overlapSum = GetOverlapSum();

	if ((bufIndex < overlapSum)
		&& (OVERLAP_OF_AC_SUM_MAX <= bufSzie)
		&& (containAcIdBuff != NULL))
	{
		for (cycle = 0U;cycle < GetOverlapContainAcNum(overlapId);cycle++)
		{
			containAcIdBuff[cycle] = gOverlapConfigDataStruBuff[bufIndex].ContainAcBuff[cycle];
		}
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
