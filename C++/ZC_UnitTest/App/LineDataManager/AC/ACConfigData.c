/********************************************************
*                                                                                                            
* 文 件 名： ACConfigData.c   
* 创建时间： 2015-05-01
* 作    者： 
* 功能描述： 计轴配置数据管理  
* 备  注  ：  无
*
********************************************************/ 

#include "ACConfigData.h"


AcConfigDataStruct gAcConfigDataStruBuff[LOCAL_AC_SUM_MAX];   /*定义本ZC计轴数据配置结构体*/
UINT16_S gLocalAcIndexBuff[AC_SUM_MAX] = {LOCAL_AC_SUM_MAX}; /*定义本ZC计轴下标数组*/
UINT16_S gAcCurSum = 0U;									 /*本ZC计轴当前总数*/

/*
* 功能描述： 获取指定ID计轴索引号
* 参数说明： const UINT16 acId, 计轴ID
* 返回值  ： LOCAL_AC_SUM_MAX 或 AC_SUM_MAX: 获取数据失败
*			<LOCAL_AC_SUM_MAX: 查找成功
*/
UINT16_S GetAcConfigBufIndex(const UINT16_S acId)
{
	UINT16_S rtnIndex = LOCAL_AC_SUM_MAX;

	if ((1U <= acId) && (acId < AC_SUM_MAX))
	{
		rtnIndex = gLocalAcIndexBuff[acId];
    }

	return rtnIndex;
}

/*
* 功能描述： 获取计轴当前总数
* 参数说明： void    
* 返回值  ： 0: 获取计轴数量失败
*			>0: 计轴当前总数
*/
UINT16_S GetAcCurSum(void)
{
	UINT16_S rtnSum = 0U;

    if (LOCAL_AC_SUM_MAX >= gAcCurSum)
    {
        rtnSum =  gAcCurSum;
    }

	return rtnSum;
}

/*
* 功能描述： 获取指定数组下标对应的计轴区段ID
* 参数说明： const UINT16 bufIndex, 数组下标    
* 返回值  ： 0: 获取数据失败
*			>0: ACID      
*/
UINT16_S GetAcId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (LOCAL_AC_SUM_MAX > GetAcCurSum())
	{
		rtnValue = gAcConfigDataStruBuff[bufIndex].AcId;
	} 

	return rtnValue;
}

/*
* 功能描述： 获取指定ID计轴所属联锁ID
* 参数说明： const UINT16 acId, 计轴ID    
* 返回值  ： 0: 获取数据失败
*			>0: 所属联锁ID      
*/
UINT16_S GetAcBelongCiId(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT16_S rtnCiId = 0U;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnCiId = gAcConfigDataStruBuff[bufIndex].BelongCiId;
	}

	return rtnCiId;
}

/*
* 功能描述： 获取指定ID计轴所属Zc ID
* 参数说明： const UINT16 acId, 计轴ID    
* 返回值  ： 0: 获取数据失败
*			>0: 所属ZC ID      
*/
UINT16_S GetAcBelongZcId(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT16_S rtnZcId = 0U;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnZcId = gAcConfigDataStruBuff[bufIndex].BelongZcId;
	}

	return rtnZcId;
}

/*
* 功能描述： 获取指定ID计轴所属类型
* 参数说明： const UINT16 acId, 计轴ID    
* 返回值  ： 0: 获取数据失败
*			 0x55-正线联锁计轴
*			 0xaa-车辆段联锁计轴   
*/
UINT8_S GetAcType(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtntype = 0U;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtntype = gAcConfigDataStruBuff[bufIndex].AcType;
	}

	return rtntype;
}

/*
* 功能描述： 获取指定ID计轴边界点属性
* 参数说明： const UINT16 acId, 计轴ID    
* 返回值  ： 0:不属于
*            FLAG_SET:属于
*/
UINT8_S GetAcBoundaryType(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtntype = 0U;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtntype = gAcConfigDataStruBuff[bufIndex].ChangeAttribute;
	}

	return rtntype;
}

/*
* 功能描述： 获取指定ID计轴包含的道岔数量
* 参数说明： const UINT16 acId, 计轴ID    
* 返回值  ： 0xff: 获取数据失败
*			 >=0: 道岔数量  
*/
UINT8_S GetAcSwitchNum(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S rtntype = 0xffU;

	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtntype = gAcConfigDataStruBuff[bufIndex].SwitchNum;
	}

	return rtntype;
}

/*
* 功能描述： 获取指定ID计轴包含的道岔信息
* 参数说明： const UINT16 acId, 计轴ID 
*            const UINT8_S bufSize,大小
*            SwitchInAcStruct switchInAcStruBuff[],道岔信息
* 返回值  ： 0: 获取数据失败
*			 1: 获取数据成功   
*/
UINT8_S GetAcSwitchInfo(const UINT16_S acId,const UINT8_S bufSize,SwitchInAcStruct switchInAcStruBuff[])
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S swtichNum = DEFAULT_ZERO;
	UINT8_S rtnValue = RETURN_ERROR;

	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/
	swtichNum = GetAcSwitchNum(acId);

	if ((bufIndex < LOCAL_AC_SUM_MAX)
		&& (bufSize >=  swtichNum) && (NULL != switchInAcStruBuff))
	{
		for (cycle = DEFAULT_ZERO;cycle < swtichNum;cycle++)
		{
			switchInAcStruBuff[cycle].SwitchId = gAcConfigDataStruBuff[bufIndex].SwitchInAcStru[cycle].SwitchId;
			switchInAcStruBuff[cycle].SwitchPostion = gAcConfigDataStruBuff[bufIndex].SwitchInAcStru[cycle].SwitchPostion;
		}
		rtnValue = RETURN_SUCCESS;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定计轴区段包含的逻辑区段数量
* 参数说明： const UINT16 acId, 计轴区段Id    
* 返回值  ： 0: 获取数据失败
*			>0: 数量      
*/
UINT16_S GetAcLogicSectionNum(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT16_S rtnValue = 0U;

	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = (UINT16_S)(gAcConfigDataStruBuff[bufIndex].LogicSectionNum);
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定计轴区段包含的逻辑区段Id数组
* 参数说明： const UINT16 bufIndex, 数组下标    
*            const UINT16_S bufSize,输出数组大小
*            UINT16_S logicSectionIdBuff[],输出数组
* 返回值  ： 0: 获取数据失败
*			 1: 获取成功      
*/
UINT8_S GetAcLogicSectionIdBuf(const UINT16_S acId,const UINT16_S bufSize,UINT16_S logicSectionIdBuff[])
{
	UINT16_S bufIndex = 0U;  /*数组下标*/
	UINT8_S cycle = DEFAULT_ZERO;
	UINT16_S logicSectionNum = DEFAULT_ZERO;
    UINT8_S  rtnValue = 0U;

	bufIndex = GetAcConfigBufIndex(acId);  /*获取区段数组下标*/
	logicSectionNum = GetAcLogicSectionNum(acId);

    if (NULL != logicSectionIdBuff)
    {
        if ((bufIndex < LOCAL_AC_SUM_MAX)
            && (bufSize >=  SIZE_MAX_SECTIONNUM))
        {
            for (cycle = DEFAULT_ZERO;cycle < logicSectionNum;cycle++)
            {
                logicSectionIdBuff[cycle] = gAcConfigDataStruBuff[bufIndex].LogicSectionIdBuff[cycle];
            }

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
