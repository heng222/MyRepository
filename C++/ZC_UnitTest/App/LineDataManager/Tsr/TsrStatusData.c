/************************************************************************
*
* 文件名   ：  TsrStatusData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  临时限速状态管理
* 备  注   ：  无
*
************************************************************************/
#include "TsrDefine.h"
#include "TsrStatusData.h"
#include "../../SysDataManager/SysConfigData.h"

TsrDataStruct gTsrDataStruBuff[TSR_BUFF_SUM_MAX];                  /*本地管理的临时限速配置信息*/
UINT16_S gTsrOfZcIdBuff[LINE_ZC_SUM_MAX] = {TSR_BUFF_SUM_MAX};    /*定义临时限速（ZC）映射数组*/
UINT16_S gTsrOfZcCurSum = 0U;                                     /*临时限速（ZC）当前总数*/

/*
* 功能描述： 获取本ZC管理范围内当前临时限速数量总数
*	        （包含相邻ZC发送过来的切换区域内的临时限速）
* 参数说明： void    
* 返回值  ： TSR_BUFF_SUM_MAX: 获取数据失败
*			>=0: 当前ZC数量总数
*/
UINT16_S GetTsrOfZcSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gTsrOfZcCurSum >= TSR_BUFF_SUM_MAX)
	{
		rtnValue = TSR_BUFF_SUM_MAX;
	} 
	else
	{
		rtnValue = gTsrOfZcCurSum;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定数组下标对应的所属ZCID
* 参数说明： const UINT16 bufIndex, 数组下标    
* 返回值  ： 0: 获取数据失败
*			>0: ZCID      
*/
UINT16_S GeTsrOfBelongZcId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (bufIndex < GetTsrOfZcSum())
	{
		rtnValue = gTsrDataStruBuff[bufIndex].BelongZcId;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定数组下标对应的临时限速信息
* 参数说明： const UINT16 bufIndex, 数组下标    
* 返回值  ： NULL: 获取数据失败
*			!NULL: 信息      
*/
TsrDataStruct* GeTsrDataStructOfIndex(const UINT16_S bufIndex)
{
	TsrDataStruct* pRtnValue = DEFAULT_ZERO;

	if (bufIndex < GetTsrOfZcSum())
	{
		pRtnValue = &gTsrDataStruBuff[bufIndex];
	} 
	else
	{
		pRtnValue = NULL;
	}

	return pRtnValue;
}

/*
* 功能描述： 获取指定ZCID临时限速下标
* 参数说明： const UINT16 zcId,zcID
* 返回值  ： TSR_BUFF_SUM_MAX; 获取数据失败
*			 >0;查找索引成功
*/
UINT8_S GeZcIdOfTsrBufIndex(const UINT16_S zcId)
{
	UINT8_S rtnValue = DEFAULT_ZERO;

	if ((zcId >= 1U)&&(zcId < LINE_ZC_SUM_MAX))
	{
		rtnValue = (UINT8_S)(gTsrOfZcIdBuff[zcId]);
	}
	else
	{
		rtnValue = TSR_BUFF_SUM_MAX;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ZCID临时限速数量
* 参数说明： const UINT16 zcId,zcID    
* 返回值  ： 0: 获取数据失败
*			>0: 数量信息     
*/
UINT8_S GetZcIdOfTsrNum(const UINT16_S zcId)
{
	UINT8_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GeZcIdOfTsrBufIndex(zcId);  /*获取数组下标*/

	if (bufIndex < GetTsrOfZcSum())
	{
		rtnValue = gTsrDataStruBuff[bufIndex].TsrNum;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 设置指定ZC下标临时限速数量
* 参数说明： const UINT8 tsrOfZcBufIndex,临时限速对应的ZC下标 
*            const UINT8_S tsrNum,临时限速数量
* 返回值  ： 0: 失败
*			>0: 成功     
*/
UINT8_S SetZcIdOfTsrNum(const UINT8_S tsrOfZcBufIndex,const UINT8_S tsrNum)
{
	UINT8_S rtnValue = DEFAULT_ZERO;

	if (tsrOfZcBufIndex < TSR_BUFF_SUM_MAX)
	{
		gTsrDataStruBuff[tsrOfZcBufIndex].TsrNum = tsrNum;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ZCID对应的某个下标下的临时限速对应的速度值
* 参数说明： const UINT16 zcId, ZCID
*	         const UINT16_S singleBufIndex buf下标   
* 返回值  ： 0: 获取数据失败
*			>0: 某条临时限速信息(以逻辑区段ID数组为返回值)      
*/
UINT8_S GetSingleTsrDataOfSpeed(const UINT16_S zcId,const UINT16_S singleBufIndex)
{
	UINT8_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GeZcIdOfTsrBufIndex(zcId);  /*获取数组下标*/

	if (bufIndex < GetTsrOfZcSum())
	{
		if (singleBufIndex < gTsrDataStruBuff[bufIndex].TsrNum)
		{
			rtnValue = gTsrDataStruBuff[bufIndex].SingleTsrDataStru[singleBufIndex].Speed;
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
* 功能描述： 设置指定ZCID对应的某个下标下的临时限速对应的速度值
* 参数说明： const UINT8 tsrOfZcBufIndex,存储临时限速关联的ZCid对应下标
*	         const UINT16_S singleBufIndex,单个ZC临时限速buf下标
*            const UINT16_S speed,临时限速速度
* 返回值  ： 0: 获取数据失败
*			>0: 某条临时限速信息(以逻辑区段ID数组为返回值)      
*/
UINT8_S SetSingleTsrDataOfSpeed(const UINT8_S tsrOfZcBufIndex,const UINT16_S singleBufIndex, const UINT16_S speed)
{
	UINT8_S rtnValue = DEFAULT_ZERO;
    UINT16_S lineMaxTSRSpeed = DEFAULT_ZERO;
	
	lineMaxTSRSpeed = GetLineMaxTSRSpeed();
	
	if ((tsrOfZcBufIndex < TSR_BUFF_SUM_MAX)
		&& (speed <= lineMaxTSRSpeed))
	{
		gTsrDataStruBuff[tsrOfZcBufIndex].SingleTsrDataStru[singleBufIndex].Speed = (UINT8_S)(speed);

		rtnValue = RETURN_SUCCESS ;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ZCID对应的某个下标下临时限速对应的逻辑区段数量
* 参数说明： const UINT16 zcId, ZCID
*	         const UINT16_S singleBufIndex buf下标   
* 返回值  ： 0: 获取数据失败
*			>0: 数量      
*/
UINT8_S GetSingleTsrDataOfSectionNum(const UINT16_S zcId,const UINT16_S singleBufIndex)
{
	UINT8_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GeZcIdOfTsrBufIndex(zcId);  /*获取数组下标*/

	if (bufIndex < GetTsrOfZcSum())
	{
		if (singleBufIndex < gTsrDataStruBuff[bufIndex].TsrNum)
		{
			rtnValue = gTsrDataStruBuff[bufIndex].SingleTsrDataStru[singleBufIndex].SectionNum;
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
* 功能描述： 获取指定ZCID对应的某个下标下的临时限速对应的逻辑区段buff
* 参数说明： const UINT16 zcId, ZCID
*			 const UINT16_S bufIndex buf下标   
*			 const UINT8_S bufSize,数组大小
*            UINT16_S sectionIdBuff[],输出数组
* 返回值  ： 0: 获取数据失败
*			 1: 获取成功      
*/
UINT8_S GetSingleTsrDataOfSectionBuff(const UINT16_S zcId,const UINT16_S singleBufIndex,const UINT8_S bufSize,UINT16_S sectionIdBuff[])
{
	UINT8_S bufIndex = 0U;     /*数组下标*/
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GeZcIdOfTsrBufIndex(zcId);  /*获取数组下标*/

	if ((bufIndex < GetTsrOfZcSum())
		&& (bufSize >= SINGLE_TSR_SECTION_SUM_MAX) && (NULL != sectionIdBuff))
	{
		if (singleBufIndex < gTsrDataStruBuff[bufIndex].TsrNum)
		{
			for (cycle = DEFAULT_ZERO;cycle < GetSingleTsrDataOfSectionNum(zcId,singleBufIndex);cycle++)
			{
				sectionIdBuff[cycle] = gTsrDataStruBuff[bufIndex].SingleTsrDataStru[singleBufIndex].SectionIdBuff[cycle];
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

	return rtnValue;
}

/*
* 功能描述： 设置指定ZCID对应的某个下标下的临时限速的逻辑区段buff
* 参数说明： const UINT8 tsrOfZcBufIndex,存储临时限速关联的ZCid对应下标
*	         const UINT16_S singleBufIndex,单个ZC临时限速buf下标  
*            const UINT8_S sectionNum,设置的临时限速数量
*            const UINT16_S sectionIdBuff[],设置的临时限速对应的逻辑区段Id数组
* 返回值  ： 0: 设置数据失败
*			 1: 设置数据成功      
*/
UINT8_S SetSingleTsrDataOfSectionInfo(const UINT8_S tsrOfZcBufIndex,const UINT8_S singleBufIndex,const UINT8_S sectionNum,const UINT16_S sectionIdBuff[])
{
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	if ((tsrOfZcBufIndex < TSR_BUFF_SUM_MAX)
		&& (sectionNum <= SINGLE_TSR_SECTION_SUM_MAX) && (NULL !=sectionIdBuff))
	{
		gTsrDataStruBuff[tsrOfZcBufIndex].SingleTsrDataStru[singleBufIndex].SectionNum = sectionNum;

		for (cycle = DEFAULT_ZERO;cycle < sectionNum;cycle++)
		{
			gTsrDataStruBuff[tsrOfZcBufIndex].SingleTsrDataStru[singleBufIndex].SectionIdBuff[cycle] = sectionIdBuff[cycle];
		}

		rtnValue = RETURN_SUCCESS ;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 申请临时限速对应的ZC下标
* 参数说明： const UINT16 zcId, zcId    
* 返回值  ： 0: 设置失败
*			>0: 设置成功      
*/
UINT8_S AplyTsrIndexOfZcId(const UINT16_S zcId)
{
	UINT16_S bufIndex = LINE_MAX_TRAIN_ID;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GeZcIdOfTsrBufIndex(zcId);

	if (TSR_BUFF_SUM_MAX == bufIndex)
	{
		/*新增*/
		if (gTsrOfZcCurSum >= TSR_BUFF_SUM_MAX)
		{
			/*不添加信息,返回失败*/
		} 
		else
		{
			/*增加信息*/
			gTsrDataStruBuff[gTsrOfZcCurSum].BelongZcId = zcId;
			gTsrOfZcIdBuff[zcId] = gTsrOfZcCurSum;
			gTsrOfZcCurSum++;
			rtnValue = RETURN_SUCCESS;
		}
	} 
	else
	{
		if (TSR_BUFF_SUM_MAX >= bufIndex)
		{
            rtnValue = RETURN_ERROR;			
		} 
		else
		{
            gTsrDataStruBuff[bufIndex].BelongZcId = zcId;
            rtnValue = RETURN_SUCCESS;
		}
	}

	return rtnValue;
}
