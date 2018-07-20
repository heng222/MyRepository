/*************************************************
  文件名   ：ConResSpeedData.c
  作者     ：董欣      
  创建时间 ：2016-8-11
  功能描述 ： ConResSpeedData数据管理
			DmuCommonData组件的ConResSpeedData功能可分解如下：
			1）	给BnfConResSpeedStruct结构体指针分配空间
			2）	获取ConResSpeed数据
			3）	获取ConResSpeed信息
			4）	获取统一限速表中的限速值

  备注    ：无。
 
*************************************************/

#include "ConResSpeedData.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/Copy.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"

static BnfConResSpeedStruct* ConResSpeedDataStru = NULL;   /*定义ConResSpeed数据结构体*/
static UINT16_S LineNumConResSpeed = 0u;/*表行数*/


/*
* 功能描述： 给BnfConResSpeedStruct结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocConResSpeedDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == ConResSpeedDataStru))
    {
        ConResSpeedDataStru = (BnfConResSpeedStruct*)MemoryMalloc((UINT32_S)sizeof(BnfConResSpeedStruct) * lineNum);
        LineNumConResSpeed = lineNum;
    }
}

/*
* 功能描述： 获取ConResSpeed数据
* 参数说明：
* 返回值  ： 
            BnfConResSpeedStruct*
*/
BnfConResSpeedStruct *GetConResSpeedData(void)
{
    return ConResSpeedDataStru;
}


/*
* 功能描述： 获取ConResSpeed信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfConResSpeedStruct*
*/
BnfConResSpeedStruct *GetConResSpeedDataInfo(UINT16_S* lineNum)
{

    BnfConResSpeedStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumConResSpeed;
        retVal =  ConResSpeedDataStru;

    }
    return retVal;
}

/*
* 功能描述： 获取统一限速表中的限速值
* 参数说明：无
* 返回值  ：0xFFFF 无效
            其他:有效
*/
UINT16_S GetConResSpeedValue(void)
{
    UINT16_S retVal = UINT16_NULL;
    if (NULL != ConResSpeedDataStru)
    {
        retVal = ConResSpeedDataStru[0].resSpeed;
    }

    return retVal;
}
