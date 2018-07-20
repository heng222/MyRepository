/********************************************************
*                                                                                                            
* 文 件 名： ACStatusData.c   
* 创建时间： 2015-05-01
* 作    者： 
* 功能描述： 计轴状态数据管理  
* 备  注  ：  无
*
********************************************************/ 
#include "ACStatusData.h"
#include "ACConfigData.h"
#include "../../SysDataManager/SysDefine.h"
#include "../../../Common/MemSet.h"

AcStatusDataStruct gAcStatusDataStruBuff[LOCAL_AC_SUM_MAX];   /*定义本ZC计轴数据状态结构体*/
/*
* 功能描述： 获取指定ID计轴锁闭方向
* 参数说明： const UINT16 acId, 计轴ID    
* 返回值  ： RETURN_ERROR: 获取数据失败或者无方向
*			 0x55: 锁闭方向与逻辑正方向相同
			 0xaa: 锁闭方向与逻辑正方向相反
*/
UINT8_S GetAcDirection(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].AcDirection;
	}

	return rtnValue;
}

/*
* 功能描述： 设置指定ID计轴锁闭方向
* 参数说明： const UINT16 acId, 计轴ID  
*            const UINT8_S acDirection
* 返回值  ： RETURN_ERROR: 获取数据失败或者无方向
*			 RETURN_SUCCESS: 成功
*/
UINT8_S SetAcDirection(const UINT16_S acId,const UINT8_S acDirection)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		if ((AC_DIR_UP_STATUS == acDirection)
			|| (AC_DIR_DOWN_STATUS == acDirection)
			|| (DEFAULT_ZERO == acDirection))
		{
			gAcStatusDataStruBuff[bufIndex].AcDirection = acDirection;
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
* 功能描述： 获取指定ID计轴锁闭状态
* 参数说明： const UINT16 acId, 计轴ID    
* 返回值  ： RETURN_ERROR: 获取数据失败或者默认值
*			 0x55: 锁闭
*			 0xaa: 未锁闭
*/
UINT8_S GetAcBelock(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].AcBelock;
	}

	return rtnValue;
}

/*
* 功能描述： 设置指定ID计轴锁闭状态
* 参数说明： const UINT16 acId, 计轴ID 
*            const UINT8_S acBelock
* 返回值  ： RETURN_ERROR: 获取数据失败
*			 RETURN_SUCCESS: 成功
*/
UINT8_S SetAcBelock(const UINT16_S acId,const UINT8_S acBelock)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		if ((AC_LOCK_STATUS == acBelock)
			|| (AC_UNLOCK_STATUS == acBelock))
		{
			gAcStatusDataStruBuff[bufIndex].AcBelock = acBelock;
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
* 功能描述： 获取指定ID计轴占用状态
* 参数说明： const UINT16 acId, 计轴ID    
* 返回值  ： RETURN_ERROR: 获取数据失败或者默认值
*			 0x55: 占用
*			 0xaa: 空闲
*/
UINT8_S GetAcStatusNow(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].AcStatusNow;
	}

	return rtnValue;
}

/*
* 功能描述： 设置指定ID计轴当前占用状态
* 参数说明： const UINT16 acId, 计轴ID 
*            const UINT8_S acStatus
* 返回值  ： RETURN_ERROR: 获取数据失败
*			 RETURN_SUCCESS: 成功
*/
UINT8_S SetAcStatusNow(const UINT16_S acId,const UINT8_S acStatus)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		if ((AC_OCC_STATUS == acStatus)
			|| (AC_FREE_STATUS == acStatus))
		{
			gAcStatusDataStruBuff[bufIndex].AcStatusNow = acStatus;
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
* 功能描述： 获取指定ID计轴UT标志
* 参数说明： const UINT16 acId, 计轴ID    
* 返回值  ： 0: 获取数据失败
*			 0x55: UT
*			 0xaa: 非UT
*/
UINT8_S GetAcUtFlag(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].AcUtFlag;
	}

	return rtnValue;
}

/*
* 功能描述： 设置指定ID计轴UT标志
* 参数说明： const UINT16 acId, 计轴ID 
*            const UINT8_S acUtFlag
* 返回值  ： RETURN_ERROR: 获取数据失败
*			 RETURN_SUCCESS: 成功
*/
UINT8_S SetAcUtFlag(const UINT16_S acId,const UINT8_S acUtFlag)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		if ((AC_UT_OCC_STATUS == acUtFlag)
			|| (AC_UT_FREE_STATUS == acUtFlag))
		{
			gAcStatusDataStruBuff[bufIndex].AcUtFlag = acUtFlag;
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
* 功能描述： 获取指定ID计轴ARB标志
* 参数说明： const UINT16 acId, 计轴ID    
* 返回值  ： 0: 获取数据失败
*			 0x55: ARB
*			 0xaa: 非ARB
*/
UINT8_S GetAcArbFlag(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].AcArbFlag;
	}

	return rtnValue;
}

/*
* 功能描述： 设置指定ID计轴ARB标志
* 参数说明： const UINT16 acId, 计轴ID    
*            const UINT8_S acArbFlag
* 返回值  ： RETURN_ERROR: 获取数据失败
*			 RETURN_SUCCESS: 成功
*/
UINT8_S SetAcArbFlag(const UINT16_S acId,const UINT8_S acArbFlag)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		if ((AC_ARB_FREE_STATUS == acArbFlag)
			|| (AC_ARB_OCC_STATUS == acArbFlag))
		{
			gAcStatusDataStruBuff[bufIndex].AcArbFlag = acArbFlag;
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
* 功能描述： 获取指定ID计轴最后一辆进入过列车ID
* 参数说明： const UINT16 acId, 计轴ID    
* 返回值  ： 0: 获取数据失败
*			 1: 获取数据成功
*/
UINT8_S GetAcLastTrain(const UINT16_S acId,UINT16_S *trainId)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = RETURN_ERROR;
	
    if (NULL != trainId)
    {
        /*初始化输出数据*/
        (*trainId) = DEFAULT_ZERO;

        bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

        if (bufIndex < LOCAL_AC_SUM_MAX)
        {
            (*trainId) = gAcStatusDataStruBuff[bufIndex].LastTrainEnterAc;
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
* 功能描述： 设置指定ID计轴最后一辆进入过列车ID
* 参数说明： const UINT16 acId, 计轴ID   
*            const UINT16_S acLastTrainId，最后一列车
* 返回值  ： RETURN_ERROR: 获取数据失败
*			 RETURN_SUCCESS: 成功
*/
UINT8_S SetAcLastTrain(const UINT16_S acId,const UINT16_S acLastTrainId)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		if (acLastTrainId < LINE_MAX_TRAIN_ID)
		{
			gAcStatusDataStruBuff[bufIndex].LastTrainEnterAc = acLastTrainId;
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
* 功能描述： 获取指定ID计轴UT冗余计时位
* 参数说明： const UINT16 acId, 计轴ID    
* 返回值  ： 0: 获取数据失败
*			 >=0:冗余计时位
*/
UINT8_S GetAcUtRedundance(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].AcUtRedundance;
	}

	return rtnValue;
}

/*
* 功能描述： 设置指定ID计轴UT冗余标志位
* 参数说明： const UINT16 acId, 计轴ID  
*            const UINT8_S acUtRedundance
* 返回值  ： RETURN_ERROR: 获取数据失败
*			 RETURN_SUCCESS: 成功
*/
UINT8_S SetAcUtRedundance(const UINT16_S acId,const UINT8_S acUtRedundance)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		 gAcStatusDataStruBuff[bufIndex].AcUtRedundance = acUtRedundance;
		 rtnValue = RETURN_SUCCESS;
	}

	return rtnValue;
}


/*
* 功能描述： 获取指定ID计轴ARB冗余计时位
* 参数说明： const UINT16 acId, 计轴ID    
* 返回值  ： 0: 获取数据失败
*			 >=0:冗余计时位
*/
UINT8_S GetAcArbRedundance(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].AcArbRedundance;
	}

	return rtnValue;
}

/*
* 功能描述： 设置指定ID计轴ARB冗余标志位
* 参数说明： const UINT16 acId, 计轴ID  
*            const UINT8_S acArbRedundance
* 返回值  ： RETURN_ERROR: 获取数据失败
*			 RETURN_SUCCESS: 成功
*/
UINT8_S SetAcArbRedundance(const UINT16_S acId,const UINT8_S acArbRedundance)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		 gAcStatusDataStruBuff[bufIndex].AcArbRedundance = acArbRedundance;
		 rtnValue = RETURN_SUCCESS;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID计轴列车数量
* 参数说明： const UINT16 acId, 计轴ID    
* 返回值  ： DEFAULT_UINT8_VALUE: 获取数据失败
*			 >=0:列车数量
*/
UINT8_S GetAcTrainOfAcNum(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = DEFAULT_UINT8_VALUE;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].TrainOfAcNum;
	}
	else
	{
		rtnValue = DEFAULT_UINT8_VALUE;
	}

	return rtnValue;
}

/*
* 功能描述： 设置指定ID计轴列车数量
* 参数说明： const UINT16 acId, 计轴ID   
*            const UINT8_S acTrainOfAcNum
* 返回值  ： RETURN_ERROR: 获取数据失败
*			 RETURN_SUCCESS: 成功
*/
UINT8_S SetAcTrainOfAcNum(const UINT16_S acId,const UINT8_S acTrainOfAcNum)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		if (SIZE_MAX_TRAINOFAC >= acTrainOfAcNum)
		{
			gAcStatusDataStruBuff[bufIndex].TrainOfAcNum = acTrainOfAcNum;
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
* 功能描述： 获取指定ID计轴列车序列信息
* 参数说明： const UINT16 acId, 计轴ID    
*            const UINT8_S bufSzie,数组大小
*            UINT16_S trainIdSequBuff[],输出数组
* 返回值  ： RETURN_ERROR: 获取数据失败
*			 RETURN_SUCCESS:成功
*/
UINT8_S GetAcTrainSequenceBuff(const UINT16_S acId,const UINT8_S bufSzie,UINT16_S trainIdSequBuff[])
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = 0U;
	UINT8_S cycle =0U;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if ((bufIndex < LOCAL_AC_SUM_MAX)
		&& (bufSzie >= SIZE_MAX_TRAINOFAC)
		&& (NULL != trainIdSequBuff))
	{
		for (cycle = 0U; cycle < GetAcTrainOfAcNum(acId);cycle++)
		{
			trainIdSequBuff[cycle] = gAcStatusDataStruBuff[bufIndex].TrainSequenceBuff[cycle];
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
* 功能描述： 设置指定ID计轴列车序列信息
* 参数说明： const UINT16 acId,
*            const UINT16_S trainIdSequBuff[],序列ID
*            const UINT8_S trainNum,列车数量    
* 返回值  ： RETURN_ERROR: 获取数据失败
*			 RETURN_SUCCESS:成功
*/
UINT8_S SetAcTrainSequenceBuff(const UINT16_S acId,const UINT16_S trainIdSequBuff[],const UINT8_S trainNum)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = 0U;
	UINT8_S i =0U;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if ((bufIndex < LOCAL_AC_SUM_MAX)
		&& (SIZE_MAX_TRAINOFAC >= trainNum) && (NULL != trainIdSequBuff))
	{
		gAcStatusDataStruBuff[bufIndex].TrainOfAcNum = trainNum;

		if(DEFAULT_ZERO == trainNum)
		{
			for(i=0U;i<SIZE_MAX_TRAINOFAC;i++)
			{
				gAcStatusDataStruBuff[bufIndex].TrainSequenceBuff[i] = trainIdSequBuff[i];	
			}
		}
		else
		{
			for(i=0U;i<trainNum;i++)
			{
				gAcStatusDataStruBuff[bufIndex].TrainSequenceBuff[i] = trainIdSequBuff[i];	
			}
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
* 功能描述： 判断指定列车ID位于计轴列车序列的位置
* 参数说明： const UINT16 acId 计轴Id
*            const UINT16_S trainId，列车Id
* 返回值  ： 0xff: 没有在该计轴列车序列中
*			 0>=: 序列位置    
*/
UINT8_S GetTrainIdInTrainSequence(const UINT16_S acId,const UINT16_S trainId)
{
	UINT16_S trainIdSequBuff[SIZE_MAX_TRAINOFAC] ={DEFAULT_ZERO};
	UINT8_S cycle = DEFAULT_UINT8_VALUE;
	UINT8_S rtnIndex = DEFAULT_ZERO;

	if (GetAcTrainSequenceBuff(acId,SIZE_MAX_TRAINOFAC,trainIdSequBuff))
	{
		rtnIndex = DEFAULT_UINT8_VALUE;

		for (cycle = DEFAULT_ZERO;cycle < GetAcTrainOfAcNum(acId);cycle++)
		{
			if (trainIdSequBuff[cycle] == trainId)
			{
				rtnIndex = cycle;
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
		rtnIndex = DEFAULT_UINT8_VALUE;
	}

	return rtnIndex;
}

/*
* 功能描述： 查询指定计轴区段内的指定下标对应的列车Id
* 参数说明： const UINT16 acId 计轴Id
*            const UINT8_S index，索引下表
*            UINT16_S *trainIdInAC，输出列车ID
* 返回值  ： RETURN_ERROR: 查询失败
*			 RETURN_SUCCESS: 查询成功    
*/
UINT8_S GetTrainIdInTrainSequenceOfIndex(const UINT16_S acId,const UINT8_S index,UINT16_S *trainIdInAC)
{
	UINT16_S trainIdSequBuff[SIZE_MAX_TRAINOFAC];
	UINT8_S rtnValue = DEFAULT_ZERO;

	MemorySet(&trainIdSequBuff[0],sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC,DEFAULT_ZERO,sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC);

    if (NULL != trainIdInAC)
    {
        if (GetAcTrainSequenceBuff(acId,SIZE_MAX_TRAINOFAC,trainIdSequBuff))
        {
            if (SIZE_MAX_TRAINOFAC <= index)
            {
                rtnValue = RETURN_ERROR;
            } 
            else
            {
                *trainIdInAC = trainIdSequBuff[index];
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
        rtnValue = RETURN_ERROR;
    }
	
	return rtnValue;
}

/*
* 功能描述： 获取上周期指定ID计轴列车数量
* 参数说明： const UINT16 acId, 计轴ID    
* 返回值  ： -1: 获取数据失败
*			 >=0:列车数量
*/
UINT8_S GetLastTrainOfAcNum(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = 0U;

	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].LastTrainOfAcNum;
	}
	else
	{
		rtnValue = DEFAULT_0XFF;
	}

	return rtnValue;
}

/*
* 功能描述： 设置上周期指定ID计轴列车数量
* 参数说明： const UINT16 acId, 计轴ID  
*            const UINT8_S acTrainOfAcNum
* 返回值  ： RETURN_ERROR: 获取数据失败
*			 RETURN_SUCCESS: 成功
*/
UINT8_S SetLastTrainOfAcNum(const UINT16_S acId,const UINT8_S acTrainOfAcNum)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = RETURN_ERROR;

	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		gAcStatusDataStruBuff[bufIndex].LastTrainOfAcNum = acTrainOfAcNum;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取上周期指定ID计轴列车序列信息
* 参数说明： const UINT16 acId, 计轴ID    
*            const UINT8_S bufSzie,数组大小
*            const UINT16_S trainIdSequBuff[],输出数组
* 返回值  ： RETURN_ERROR: 获取数据失败
*			 RETURN_SUCCESS:成功
*/
UINT8_S GetLastTrainSequenceBuf(const UINT16_S acId,const UINT8_S bufSzie,UINT16_S trainIdSequBuff[])
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = 0U;
	UINT8_S cycle =0U;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if ((bufIndex < LOCAL_AC_SUM_MAX)
		&& (bufSzie >= SIZE_MAX_TRAINOFAC)
		&& (NULL != trainIdSequBuff))
	{
		for (cycle = 0U; cycle < GetLastTrainOfAcNum(acId);cycle++)
		{
			trainIdSequBuff[cycle] = gAcStatusDataStruBuff[bufIndex].LastTrainSequenceBuff[cycle];
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
* 功能描述： 设置上周期指定ID计轴列车序列信息
* 参数说明： const UINT16 acId,
*            const UINT16_S trainIdSequBuff[],序列ID
*            const UINT8_S trainNum,列车数量    
* 返回值  ： RETURN_ERROR: 获取数据失败
*			 RETURN_SUCCESS:成功
*/
UINT8_S SetLastTrainSequenceBuf(const UINT16_S acId,const UINT16_S trainIdSequBuff[],const UINT8_S trainNum)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = 0U;
	UINT8_S i =0U;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if ((bufIndex < LOCAL_AC_SUM_MAX)
		&& (SIZE_MAX_TRAINOFAC >= trainNum) && (NULL != trainIdSequBuff))
	{
		gAcStatusDataStruBuff[bufIndex].TrainOfAcNum = trainNum;

		for(i=0U;i<trainNum;i++)
		{
			gAcStatusDataStruBuff[bufIndex].LastTrainSequenceBuff[i] = trainIdSequBuff[i];	
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
* 功能描述： 获取指定ID计轴列车已清扫标志
* 参数说明： const UINT16 acId, 计轴ID    
* 返回值  ： RETURN_UINT8_MAX_VALUE: 获取数据失败
*			 FLAG_SET:已清扫
*			 FLAG_UNSET:未清扫
*/
UINT8_S GetAcTrainCleanFlag(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = RETURN_UINT8_MAX_VALUE;

	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].TrainCleanFlag;
	}

	return rtnValue;
}
/*
* 功能描述： 设置指定ID计轴列车已清扫标志
* 参数说明： const UINT16 acId, 计轴ID    
* 返回值  ： RETURN_SUCCESS: 设置成功
*			 RETURN_ERROR:设置失败			 
*/
UINT8_S SetAcTrainCleanFlag(const UINT16_S acId,const UINT8_S cleanFlag)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = RETURN_ERROR;

	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{		
		gAcStatusDataStruBuff[bufIndex].TrainCleanFlag = cleanFlag;
		rtnValue = RETURN_SUCCESS;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID计轴已清扫列车ID
* 参数说明： const UINT16 acId, 计轴ID    
* 返回值  ： 0: 获取数据失败
*			 >0:清扫列车ID
*/
UINT16_S GetAcCleanTrainId(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT16_S rtnValue = RETURN_ERROR;

	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].CleanTrainId;
	}

	return rtnValue;
}

/*
* 功能描述： 设置指定ID计轴已清扫列车ID
* 参数说明： const UINT16 acId, 计轴ID    
* 返回值  ： RETURN_ERROR: 设置数据失败
*			 RETURN_SUCCESS:设置成功
*/
UINT8_S SetAcCleanTrainId(const UINT16_S acId,const UINT16_S cleanTrainId)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtnValue = RETURN_ERROR;

	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{		 
		gAcStatusDataStruBuff[bufIndex].CleanTrainId = cleanTrainId;
		rtnValue = RETURN_SUCCESS;
	}

	return rtnValue;
}

/*
* 功能描述： 获取计轴区段内的第一列车
* 参数说明： const UINT16 acId, 计轴ID    
* 返回值  ： RETURN_UINT16_MAX_VALUE: 获取数据失败
*			>0: 第一列列车ID
*/
UINT16_S GetFirstIdInTrainSequence(const UINT16_S acId)
{
	UINT8_S trainNum = 0U;
	UINT16_S rtnValue = 0U;
	UINT16_S acIndex = 0U;
	/*获取列车数量*/
	trainNum = GetAcTrainOfAcNum(acId);
	acIndex = GetAcConfigBufIndex(acId);

	if ((RETURN_UINT8_MAX_VALUE != trainNum) && (0U != trainNum))
	{
		rtnValue = gAcStatusDataStruBuff[acIndex].TrainSequenceBuff[0];
	}
	else
	{
		rtnValue = RETURN_UINT16_MAX_VALUE;
	}

	return rtnValue;
}

/*
* 功能描述： 获取计轴区段内的最后一列车
* 参数说明： const UINT16 acId, 计轴ID    
* 返回值  ： RETURN_UINT16_MAX_VALUE: 获取数据失败
*			>0: 最后一列列车ID
*/
UINT16_S GetLastIdInTrainSequence(const UINT16_S acId)
{
	UINT8_S trainNum = 0U;
	UINT16_S rtnValue = 0U;
	UINT16_S acIndex = 0U;
	/*获取列车数量*/
	trainNum = GetAcTrainOfAcNum(acId);
	acIndex = GetAcConfigBufIndex(acId);

	if ((RETURN_UINT8_MAX_VALUE != trainNum) && (0U != trainNum))
	{
		rtnValue = gAcStatusDataStruBuff[acIndex].TrainSequenceBuff[trainNum - 1U];
	}
	else
	{
		rtnValue = RETURN_UINT16_MAX_VALUE;
	}

	return rtnValue;
}
