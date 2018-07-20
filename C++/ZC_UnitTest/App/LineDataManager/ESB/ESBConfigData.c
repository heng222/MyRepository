/************************************************************************
*
* 文件名   ：  ESBConfigData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  紧急停车按钮配置数据
* 备  注   ：  无
*
************************************************************************/
#include "ESBConfigData.h"


EsbConfigDataStruct gEsbConfigDataStruBuff[ESB_LOCAL_SUM_MAX];          /*本地管理的紧急停车按钮配置信息*/
UINT16_S gEsbIdBuff[ESB_SUM_MAX] = {0U};                                /*定义紧急停车按钮映射数组*/
UINT16_S gEsbCurSum = 0U;                                              /*紧急停车按钮当前总数*/


/*
* 功能描述： 获取紧急停车按钮管理总数
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 紧急停车按钮当前总数
*/
UINT16_S GetEsbSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gEsbCurSum >= ESB_LOCAL_SUM_MAX)
	{
		rtnValue = 0U;
	} 
	else
	{
		rtnValue = gEsbCurSum;
	}	

	return rtnValue;
}

/*
* 功能描述： 获取指定数组下标对应的紧急停车按钮ID
* 参数说明： const UINT16 bufIndex, 数组下标    
* 返回值  ： 0: 获取数据失败
*			>0: 紧急停车按钮ID      
*/
UINT16_S GetEsbId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (bufIndex < GetEsbSum())
	{
		rtnValue = gEsbConfigDataStruBuff[bufIndex].EsbId;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID紧急停车按钮索引号
* 参数说明： const UINT16 esbId,紧急停车按钮ID
* 返回值  ： ESB_LOCAL_SUM_MAX: 获取数据失败
*			<ESB_LOCAL_SUM_MAX: 查找成功
*/
UINT16_S GetEsbConfigBufIndex(const UINT16_S esbId)
{
	UINT16_S rtnValue = ESB_LOCAL_SUM_MAX;

	if ((esbId >= 1U)&&(esbId < ESB_SUM_MAX))
	{
		rtnValue = gEsbIdBuff[esbId];
	}
	else
	{
		rtnValue = ESB_LOCAL_SUM_MAX;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID站台紧急停车按钮所属联锁ID
* 参数说明： const UINT16 esbId,紧急停车按钮ID    
* 返回值  ： 0: 获取数据失败
*			>0: 所属联锁ID      
*/
UINT8_S GetEsbBelongCiId(const UINT16_S esbId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetEsbConfigBufIndex(esbId);  /*获取数组下标*/

	if (bufIndex < GetEsbSum())
	{
		rtnValue = gEsbConfigDataStruBuff[bufIndex].BelongCiId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID紧急停车按钮所属ZCID
* 参数说明： const UINT16 esbId, 紧急停车按钮ID    
* 返回值  ： 0: 获取数据失败
*			>0: 所属zcID      
*/
UINT8_S GetEsbBelongZcId(const UINT16_S esbId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetEsbConfigBufIndex(esbId);  /*获取数组下标*/

	if (bufIndex < GetEsbSum())
	{
		rtnValue = gEsbConfigDataStruBuff[bufIndex].BelongZcId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID紧急停车按钮共管区域属性
* 参数说明： const UINT16 esbId, 紧急停车按钮ID     
* 返回值  ： 0: 不属于
*			 FLAG_SET: 属于       
*/
UINT8_S GetEsbChangeAttribute(const UINT16_S esbId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetEsbConfigBufIndex(esbId);  /*获取数组下标*/

	if (bufIndex < GetEsbSum())
	{
		rtnValue = gEsbConfigDataStruBuff[bufIndex].ChangeAttribute;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
