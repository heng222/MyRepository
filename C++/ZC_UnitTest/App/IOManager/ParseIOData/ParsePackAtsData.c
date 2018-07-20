/************************************************************************
*
* 文件名   ：  ParsePackAtsData.c
* 创建时间 ：  2014.04.14
* 作者     ：  ZC组
* 功能描述 ：  解析组包ATS数据管理  
* 备  注   ：  无
*
************************************************************************/

#include "ParsePackAtsData.h"
#include "../../SysDataManager/SysDefine.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../CommTarget/CommTargetConfigData.h"
#include "../../../Common/Copy.h"
#include "../../../Common/MemSet.h"

ZcAndAtsIODataStruct gZcToAtsDataStru;                     /*ZC到ATS数据*/

/*
* 功能描述：获取输出给ATS数据数组下标对应的数据长度
* 参数说明： 无
* 返回值  ： ZC给ATS的数据长度     
*/
UINT16_S GetZcToAtsIdDataBufLen(void)
{
	return gZcToAtsDataStru.ValueBuffLen;
}

/*
* 功能描述： 获取输出给Ats数据数组下标对应的数据信息
* 参数说明： 无
* 返回值  ：ZC给ATS的数组的首地址      
*/
UINT8_S* GetZcToAtsDataBuff(void)
{
	return gZcToAtsDataStru.ValueBuff;
}

/*
* 功能描述： 组ZC给ATS数据
* 参数说明： const UINT8* dataBuf,数据数组   
*            const UINT16_S dataLen,数据长度
* 返回值  ： 0:组数据失败
*			 1:组数据成功      
*/
UINT8_S PackZcToAtsFrameData(const UINT8_S* dataBuf,const UINT16_S dataLen)/*-bye- 删除了第三个参数*/
{
	UINT8_S rtnValue= DEFAULT_ZERO;

	if (dataBuf != NULL)
	{
		/*-bye- 按照《ZC-ATS接口说明书》修改代码*/

		/*拷贝接口数据*/
		if (0U == MemoryCpy(&gZcToAtsDataStru.ValueBuff[DEFAULT_ZERO],(UINT32_S)ZC_ATS_COM_BYTE_SUM_MAX,dataBuf,((UINT32_S)dataLen)))
		{
			/*填写长度信息*/
			gZcToAtsDataStru.ValueBuffLen = dataLen;

            rtnValue = RETURN_SUCCESS;
		} 
		else
		{
			/*清除输出数据*/
			gZcToAtsDataStru.ValueBuffLen = 0U;

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
* 功能描述： 清空本周期Ats输出信息
* 参数说明： 无
* 返回值  ： 无      
*/
void ClearCycleAtsOutputData(void)
{
	MemorySet(&gZcToAtsDataStru,((UINT32_S)(sizeof(ZcAndAtsIODataStruct))),
                DEFAULT_ZERO,((UINT32_S)(sizeof(ZcAndAtsIODataStruct))));
}
