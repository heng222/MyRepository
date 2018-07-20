/*************************************************
  文件名   ：StaticResSpeedData.c
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： StaticResSpeedData数据管理
			DmuCommonData组件的StaticResSpeedData功能可分解如下：
			1）	给StaticResSpeedDataStru结构体指针分配空间
			2）	获取StaticResSpeedData数据
			3）	获取StaticResSpeedData信息
			4）	获取指定IDStaticResSpeedDataStru的结构体下标
			5）	 获取指定IDStaticResSpeedDataStru的结构体指针
			6）	获取指定IDStaticResSpeedDataStru的该限速区域所处Seg编号
			7）	获取指定IDStaticResSpeedDataStru的起点所处Seg偏移量(cm)
			8）	 获取指定IDStaticResSpeedDataStru的终点所处Seg偏移量(cm)
			9）	获取指定IDStaticResSpeedDataStru的静态限速值
			10）	获取指定的SEGID获取相关信息
  备注    ：无。
 
*************************************************/

#include "StaticResSpeedData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"

static BnfStaticResSpeedStruct* StaticResSpeedDataStru = NULL;   /*定义StaticResSpeedData数据结构体*/
static UINT16_S LineNumStaticResSpeed = 0u;/*表行数*/


/*
* 功能描述： 给StaticResSpeedDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocStaticResSpeedDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == StaticResSpeedDataStru))
    {
        StaticResSpeedDataStru = (BnfStaticResSpeedStruct*)MemoryMalloc((UINT32_S)sizeof(BnfStaticResSpeedStruct) * lineNum);
        LineNumStaticResSpeed = lineNum;
    }
}

/*
* 功能描述： 获取StaticResSpeedData数据
* 参数说明：
* 返回值  ： 
            BnfStaticResSpeedStruct*
*/
BnfStaticResSpeedStruct *GetStaticResSpeedData(void)
{
    return StaticResSpeedDataStru;
}


/*
* 功能描述： 获取StaticResSpeedData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfStaticResSpeedStruct*
*/
BnfStaticResSpeedStruct *GetStaticResSpeedDataInfo(UINT16_S* lineNum)
{

    BnfStaticResSpeedStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumStaticResSpeed;
        retVal = StaticResSpeedDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDStaticResSpeedDataStru的结构体下标
* 参数说明： const UINT16_S staticResSpeedId;编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetStaticResSpeedDataStruIndex(const UINT16_S staticResSpeedId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumStaticResSpeed; i++)
    {
        if (staticResSpeedId == StaticResSpeedDataStru[i].staticResSpeedId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStaticResSpeedDataStru的结构体指针
* 参数说明： const UINT16_S staticResSpeedId;编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfStaticResSpeedStruct* GetIndexIdStaticResSpeedDataStru(const UINT16_S staticResSpeedId)
{
    BnfStaticResSpeedStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStaticResSpeedDataStruIndex(staticResSpeedId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStaticResSpeed)
    {
        retVal = &StaticResSpeedDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStaticResSpeedDataStru的该限速区域所处Seg编号
* 参数说明： const UINT16_S staticResSpeedId;编号
* 返回值  :  0: 获取数据失败
*            >0: 该限速区域所处Seg编号
*/ 
UINT16_S GetStaticResSpeedDataStrusegId(const UINT16_S staticResSpeedId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStaticResSpeedDataStruIndex(staticResSpeedId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStaticResSpeed)
    {
        retVal = StaticResSpeedDataStru[bufIndex].segId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStaticResSpeedDataStru的起点所处Seg偏移量(cm)
* 参数说明： const UINT16_S staticResSpeedId;编号
* 返回值  :  0: 获取数据失败
*            >0: 起点所处Seg偏移量(cm)
*/ 
UINT32_S GetStaticResSpeedDataStruorgnSegOfst(const UINT16_S staticResSpeedId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStaticResSpeedDataStruIndex(staticResSpeedId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStaticResSpeed)
    {
        retVal = StaticResSpeedDataStru[bufIndex].orgnSegOfst;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStaticResSpeedDataStru的终点所处Seg偏移量(cm)
* 参数说明： const UINT16_S staticResSpeedId;编号
* 返回值  :  0: 获取数据失败
*            >0: 终点所处Seg偏移量(cm)
*/ 
UINT32_S GetStaticResSpeedDataStrutmnlSegOfst(const UINT16_S staticResSpeedId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStaticResSpeedDataStruIndex(staticResSpeedId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStaticResSpeed)
    {
        retVal = StaticResSpeedDataStru[bufIndex].tmnlSegOfst;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStaticResSpeedDataStru的静态限速值
* 参数说明： const UINT16_S staticResSpeedId;编号
* 返回值  :  0: 获取数据失败
*            >0: 静态限速值
*/ 
UINT16_S GetStaticResSpeedDataStrustaticSpeed(const UINT16_S staticResSpeedId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStaticResSpeedDataStruIndex(staticResSpeedId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStaticResSpeed)
    {
        retVal = StaticResSpeedDataStru[bufIndex].staticSpeed;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* 功能描述： 获取指定的SEGID获取相关信息
* 参数说明： 输入参数:const UINT16_S segId;编号
*                      const UINT32_S startOffset  起点偏移量
*                      const UINT32_S endOffset    终点偏移量
*             输出参数:UINT16_S* limitSpeed  限速值
* 返回值  :  0: 获取数据失败
*             1: 查找成功
*/ 
UINT8_S GetSegIdOfLimitSpeed(const UINT16_S segId,const UINT32_S startOffset,const UINT32_S endOffset,UINT16_S* limitSpeed)
{
    UINT8_S retVal = 0u;

    UINT16_S i = 0u;/*循环使用*/

    UINT16_S tempLimitSpeedBuff[SEG_INCLUDE_LIMITSPEED_MAX_NUM] = {0};
    UINT8_S limitSpeedNum = 0u;/*同一SEG限速个数*/

    if(NULL != limitSpeed)
    {
        for ( i = 0u; i < LineNumStaticResSpeed; i++)
        {
            if (segId == StaticResSpeedDataStru[i].segId)
            {
                if (((startOffset>= StaticResSpeedDataStru[i].orgnSegOfst)&&(endOffset <= StaticResSpeedDataStru[i].tmnlSegOfst))
                    ||((startOffset < StaticResSpeedDataStru[i].orgnSegOfst)&&(endOffset>StaticResSpeedDataStru[i].tmnlSegOfst)))
                {
                    tempLimitSpeedBuff[limitSpeedNum] = StaticResSpeedDataStru[i].staticSpeed;
                    limitSpeedNum=limitSpeedNum+1;
                }
            }
        }

        if (limitSpeedNum > 0u)
        {
            *limitSpeed = tempLimitSpeedBuff[0];
            for (i = 1u; i < limitSpeedNum; i++)
            {
                if (tempLimitSpeedBuff[i] < *limitSpeed)
                {
                    *limitSpeed = tempLimitSpeedBuff[i];
                }
            }
            retVal = 1u;
        }

    }

    return retVal;
}

