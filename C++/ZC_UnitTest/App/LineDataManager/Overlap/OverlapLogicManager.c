/********************************************************                                                                                                           
 文 件 名： OverlapLogicManager.c
 作    者： ZC组
 创建时间： 2015.04.18
 描述： 保护区段逻辑处理  
 备注： 无  
********************************************************/ 

#include "OverlapConfigData.h"
#include "OverlapLogicManager.h"
#include "OverlapStatusData.h"
#include "../AC/ACLogicManager.h"
#include "../../../Common/MemSet.h"

/*************************************************
  函数名:    InitFailureSingleOverlap  
  功能描述: 处理通信故障Ci对应的单个保护区段信息
  输入: const UINT16 overlapId，保护区段ID    
  输出: 无
  返回值: void  
*************************************************/
void InitFailureSingleOverlap(const UINT16_S overlapId)
{
	SetOverlapStatus(overlapId,OVERLAP_STATE_UNSET);
}

/*************************************************
  函数名:   InitFailureCiOverlap   
  功能描述: 处理通信故障Ci对应的保护区段信息
  输入: const UINT16 ciId，通信故障的CIID    
  输出: 无
  返回值: void  
*************************************************/
void InitFailureCiOverlap(const UINT16_S ciId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S overlapId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetOverlapSum();cycle++)
	{
		overlapId = GetOverlapId(cycle);

		if (ciId == GetOverlapBelongCiId(overlapId))
		{
			/*设置状态为安全态*/
			InitFailureSingleOverlap(overlapId);
		} 
		else
		{
            /*不处理*/
		}
	}
}

/*************************************************
  函数名:   InitFailureNZcOverlap   
  功能描述: 处理通信故障nZc对应的保护区段信息
  输入: const UINT16 nZcId，通信故障的nZcID    
  输出: 无
  返回值: void  
*************************************************/
void InitFailureNZcOverlap(const UINT16_S nZcId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S overlapId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetOverlapSum();cycle++)
	{
		overlapId = GetOverlapId(cycle);

		if ((nZcId == GetOverlapBelongZcId(overlapId))
			&& (FLAG_SET == GetOverlapChangeAttribute(overlapId)))
		{
			/*设置状态为安全态*/
			InitFailureSingleOverlap(overlapId);
		} 
		else
		{
            /*不处理*/
		}
	}
}

/*************************************************
  函数名:    CalulateSwtichStateOfOverlapIsNeed  
  功能描述: 计算输入的overlap是否满足道岔状态（锁闭和位置）
  输入: const UINT16 overlpId，保护区段ID   
  输出: 无
  返回值: 0:不满足条件
*            1:满足条件  
*************************************************/
UINT8_S CalulateSwtichStateOfOverlapIsNeed(const UINT16_S overlpId)
{
	UINT8_S overlapContainAcNum = DEFAULT_ZERO;                   
	UINT16_S overlapContainAcBuff[OVERLAP_OF_AC_SUM_MAX] = {0U};
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S breakFlag = DEFAULT_ZERO;
    UINT8_S getFlag = RETURN_ERROR;
	
	MemorySet(&overlapContainAcBuff[0],((UINT32_S)(SIZE_UINT16 * OVERLAP_OF_AC_SUM_MAX)),
                 0U,((UINT32_S)(SIZE_UINT16 * OVERLAP_OF_AC_SUM_MAX)));

	if (FLAG_SET == GetOverlapSwitchAttribute(overlpId))
	{
		overlapContainAcNum = GetOverlapContainAcNum(overlpId);
        getFlag = GetOverlapContainAcBuff(overlpId,OVERLAP_OF_AC_SUM_MAX,overlapContainAcBuff);
		
		if ((overlapContainAcNum > 0U)
			&& (RETURN_SUCCESS == getFlag))
		{
			for (cycle = DEFAULT_ZERO;cycle < overlapContainAcNum;cycle++)
			{
				/*获取计轴区段道岔信息*/
				if (RETURN_SUCCESS == CalulateSwtichStateOfAcIsNeed(overlapContainAcBuff[cycle]))
				{
                    /*不处理*/
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
	} 
	else
	{
		rtnValue = RETURN_SUCCESS;
	}

	return rtnValue;
}
